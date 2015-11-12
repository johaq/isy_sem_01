//=============================================================================
//                                                                            
//   Exercise code for the lecture
//   "Introduction to Computer Graphics"
//   by Prof. Dr. Mario Botsch, Bielefeld University
//
//   Copyright (C) Computer Graphics Group, Bielefeld University.
//                                                                            
//=============================================================================

//== INCLUDES =================================================================

#include "Mesh.h"
#include <fstream>
#include <string>


//== IMPLEMENTATION ===========================================================


Mesh::Mesh(Draw_mode _draw_mode, const char* _filename)
{
    // set draw mode
    draw_mode_ = _draw_mode;

    // load mesh from file
    if (_filename) read(_filename);
}


//-----------------------------------------------------------------------------


bool Mesh::read(const char* _filename)
{
    // read a mesh in OFF format

    
    // open file
    std::ifstream ifs(_filename);
    if (!ifs)
    {
        std::cerr << "Can't open " << _filename << "\n";
        return false;
    }


    // read OFF header
    std::string s;
    unsigned int nV, nF, dummy, i;
    ifs >> s;
    if (s != "OFF")
    {
        std::cerr << "No OFF file\n";
        return false;
    }
    ifs >> nV >> nF >> dummy;
    std::cout << "\n  read " << _filename << ": " << nV << " vertices, " << nF << " triangles";


    // read vertices
    Vertex v;
    vertices_.clear();
    vertices_.reserve(nV);
    for (i=0; i<nV; ++i)
    {
        ifs >> v.position;
        vertices_.push_back(v);
    }


    // read triangles
    Triangle t;
    triangles_.clear();
    triangles_.reserve(nF);
    for (i=0; i<nF; ++i)
    {
        ifs >> dummy >> t.i0 >> t.i1 >> t.i2;
        triangles_.push_back(t);
    }


    // close file
    ifs.close();

    
    // compute face and vertex normals
    compute_normals();

    // compute bounding box
    compute_bounding_box();
    
    
    return true;
}


//-----------------------------------------------------------------------------


void Mesh::compute_normals()
{
    /** \todo
     
	 In some scenes (e.g the office scene) some objects have to be flat
     shaded (e.g. the desk) while other objects should be Phong shaded to appear 
     realistic (e.g. chairs). We provide code to compute triangle normals. You have to 
     implement the following:
     \li Compute vertex normals by averaging the normals of their incident triangles. Incident triangles around the vertex. 
	 \li Store the vertex normals in the Vertex::normal member variable.
	 \li Tip: It is possible to compute the contribution of the face normals to the vertex normals within the triangles_ loop.
     */
    
    
    // initialize vertex normals to zero
    for (Vertex& v: vertices_)
    {
        v.normal = vec3(0,0,0);
    }
    
    // compute triangle normals
    for (Triangle& t: triangles_)
    {
        const vec3& p0 = vertices_[t.i0].position;
        const vec3& p1 = vertices_[t.i1].position;
        const vec3& p2 = vertices_[t.i2].position;
        t.normal = normalize(cross(p1-p0, p2-p0));
    }

}


//-----------------------------------------------------------------------------


void Mesh::compute_bounding_box()
{
    bb_min_ = vec3( DBL_MAX,  DBL_MAX,  DBL_MAX);
    bb_max_ = vec3(-DBL_MAX, -DBL_MAX, -DBL_MAX);
    
    for (Vertex v: vertices_)
    {
        bb_min_ = min(bb_min_, v.position);
        bb_max_ = max(bb_max_, v.position);
    }
}


//-----------------------------------------------------------------------------


bool Mesh::intersect_bounding_box(const Ray& _ray) const
{
    /** \todo
     Intersect the ray \c _ray with the axis-aligned bounding box of the mesh.
     Note that the minimum and maximum point of the bounding box are stored
     in the member variables bb_min_ and bb_max_. Return whether the ray
     intersects the bounding box.
     \sa Mesh::intersect()
     \sa Mesh::compute_bounding_box()
     */
    

    
    return true;
}


//-----------------------------------------------------------------------------


bool Mesh::intersect(const Ray& _ray,
                     vec3&      _intersection_point,
                     vec3&      _intersection_normal,
                     double&    _intersection_t ) const
{
    // check bounding box intersection
    if (!intersect_bounding_box(_ray))
    {
        return false;
    }

    vec3   p, n;
    double t;

    _intersection_t = DBL_MAX;

    // for each triangle
    for (const Triangle& triangle : triangles_)
    {
        // does ray intersect triangle?
        if (intersect_triangle(triangle, _ray, p, n, t))
        {
            // is intersection closer than previous intersections?
            if (t < _intersection_t)
            {
                // store data of this intersection
                _intersection_t      = t;
                _intersection_point  = p;
                _intersection_normal = n;
            }
        }
    }
    
    return (_intersection_t != DBL_MAX);
}


//-----------------------------------------------------------------------------


bool 
Mesh::
intersect_triangle(const Triangle&  _triangle,
                   const Ray&       _ray,
                   vec3&            _intersection_point,
                   vec3&            _intersection_normal,
                   double&          _intersection_t) const
{
    /** \todo
     \li compute the intersection point of the _ray with the _triangle by solving a small linear system. This solution is an alternative to the solution in the lecture. 
	 \li Hint: The intersection point is defined either by a _intersection_t for a ray or the barycentric coordinates in a triangle. 
	 All barycentric coordinates sum to one. You can apply Cramer's rule for solving the final linear system.
     \li store intersection point in \c _intersection_point
     \li store ray parameter in \c _intersection_t
     \li store normal at intersection point in \c _intersection_normal. 
     Depending on the member variable \c draw_mode_, use either the triangle 
     normal (Triangle::normal) or interpolate the vertex normals (Vertex::normal).
     \li return true if there is an intersection with t > 1e-5 (avoid "shadow acne")
     */
    
    const vec3& p0 = vertices_[_triangle.i0].position;
    const vec3& p1 = vertices_[_triangle.i1].position;
    const vec3& p2 = vertices_[_triangle.i2].position;



    return true;
}


//=============================================================================
