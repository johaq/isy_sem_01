//=============================================================================
//                                                                            
//   Exercise code for the lecture
//   "Introduction to Computer Graphics"
//   by Prof. Dr. Mario Botsch, Bielefeld University
//
//   Copyright (C) Computer Graphics Group, Bielefeld University.
//                                                                            
//=============================================================================


//== includes =================================================================

#include "StopWatch.h"
#include "Sphere.h"
#include "Plane.h"
#include "Mesh.h"
#include "Light.h"
#include "Ray.h"
#include "Material.h"
#include "Image.h"
#include "Camera.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <float.h>


/// \file raytrace.cpp
/// In this file the main raytracing routines are implemented.


//== function declarations ====================================================

/// reads the scene to raytrace from the given filename (\c _filename)
void  read_scene(const char* _filename);

/// writes the resulting image in tga format to a given filename (\c _filename)
void  write_image(const char* _filename);

/// main function where the image is allocated and the raytracing is started
void  compute_image();

/// finds the closest collision point for the passed Ray and returns the computed color for 
/// this object. \c _depth is the current recursion depth.
vec3  trace(const Ray& _ray, int _depth);

/// computes the intersection between a ray and the object
/// \param[in] _ray for the intersection
/// \param[out] _object that has the closest intersection of the ray
/// \param[out] _ point intersection point of the ray
/// \param[out] _normal normal at the intersection point
/// \param[out] _t value of the ray, where the intersection happens
bool  intersect(const Ray& _ray, Object_ptr& _object, vec3& _point, vec3& _normal, double& _t);

/// computes the phong lighting 
/// \param[in] _point - lighting point in 3d space
/// \param[in] _normal - normal at \c _point
/// \param[in] _view - view vector pointing from \c _point to the camera
/// \param[in] _material - saved colors and other properties needed for the phong material
vec3  lighting(const vec3& _point, const vec3& _normal, const vec3& _view, const Material& _material);


//== global variables =========================================================


/// camera stores eye position, view direction, and can generate primary rays
Camera camera;

/// our image is just a large array of color values
Image image;

/// array for all lights in the scene
std::vector<Light> lights;

/// array for all the objects in the scene
std::vector<Object_ptr> objects;

/// max recursion depth for mirroring
int max_depth;

/// background color
vec3 background;

/// global ambient light
vec3 ambience;


//== implementation ===========================================================


int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << "  input.sce output.tga\n\n";
        exit(1);
    }


    // read scene from file
    std::cout << "Read scene...";
    read_scene(argv[1]);
    std::cout << "done (" << objects.size() << " objects)\n";
    

    // raytrace image
    StopWatch timer;
    timer.start();
    std::cout << "Ray tracing..." << std::flush;
    compute_image();
    timer.stop();
    std::cout << "done (" << timer << ")\n";
    
    
    // write the resulting image
    std::cout << "Write image...";
    image.write(argv[2]);
    std::cout << "done\n";
    

    // clean up
    for (Object_ptr o: objects)
    {
        delete o;
    }
}


//-----------------------------------------------------------------------------


void read_scene(const char* _filename)
{
    std::ifstream ifs(_filename);
    if (!ifs)
    {
        std::cerr << "Cannot open file " << _filename << std::endl;
        exit(1);
    }
    
    
    char          line[200];
    std::string   token;
    
    
    // parse file
    while (ifs && (ifs >> token) && (!ifs.eof()))
    {
        if (token[0] == '#')
        {
            ifs.getline(line, 200);
        }
        
        else if (token == "depth")
        {
            ifs >> max_depth;
        }
        
        else if (token == "camera")
        {
            ifs >> camera;
        }
        
        else if (token == "background")
        {
            ifs >> background;
        }
        
        else if (token == "ambience")
        {
            ifs >> ambience;
        }
        
        else if (token == "light")
        {
            Light light;
            ifs >> light;
            lights.push_back(light);
        }
        
        else if (token == "plane")
        {
            Plane *p = new Plane;
            ifs >> (*p);
            objects.push_back(p);
        }
        
        else if (token == "sphere")
        {
            Sphere *sphere = new Sphere();
            ifs >> (*sphere);
            objects.push_back(sphere);
        }

        else if (token == "mesh")
        {
            
            std::string filename, mode;
            ifs >> filename >> mode;

            // add path of scene-file to mesh's filename
            std::string path(_filename);
#ifdef _WIN32
            path = path.substr(0, path.find_last_of('\\')+1);
#else
            path = path.substr(0, path.find_last_of('/')+1);
#endif
            filename = path+filename;
            
            Mesh *mesh = new Mesh((mode=="FLAT" ? Mesh::FLAT : Mesh::PHONG),
                                  filename.c_str());

            ifs >> mesh->material;

            objects.push_back(mesh);
        }
    }
    
    
    ifs.close();
}


//-----------------------------------------------------------------------------


void compute_image()
{
    // allocate memory by resizing image
    image.resize(camera.width, camera.height);
    

    // here comes the main ray tracing loop
    // uncomment the following line in order to use OpenMP
//#pragma omp parallel for schedule(dynamic)
    for (unsigned int x=0; x<camera.width; ++x)
    {
        for (unsigned int y=0; y<camera.height; ++y)
        {
            Ray ray = camera.primary_ray(x,y);
            
            // compute color by tracing this ray
            vec3 color = trace(ray, 0);
            
            // avoid over-saturation
            color = min(color, vec3(1, 1, 1));
            
            // store pixel color
            image(x,y) = color;
        }
    }
}


//-----------------------------------------------------------------------------


vec3 trace(const Ray& _ray, int _depth)
{
    // stop if recursion depth (=number of reflection) is too large
    if (_depth > max_depth) return vec3(0,0,0);
    
    
    // Find first intersection with an object. If an intersection is found,
    // it is stored in object, point, normal, and t.
    Object_ptr  object;
    vec3        point;
    vec3        normal;
    double      t;
    if (!intersect(_ray, object, point, normal, t))
    {
        return background;
    }
    

    // compute local Phong lighting (ambient+diffuse+specular)
    vec3 color = lighting(point, normal, -_ray.direction, object->material);
    
    
    /** \todo
     Compute reflections by recursive ray tracing:
     \li check whether \c object is reflective by checking its \c material.mirror
     \li check recursion depth
     \li generate reflected ray, compute the reflected color, and mix it with
     the color computed by local Phong lighthing (use \c object->material.mirror for weighting the reflected color)
     */

    
    return color;
}


//-----------------------------------------------------------------------------


bool intersect(const Ray& _ray, Object_ptr& _object, vec3& _point, vec3& _normal, double& _t)
{
    double  t, tmin(DBL_MAX);
    vec3    p, n;
    
    for (Object_ptr o: objects) // for each object
    {
        if (o->intersect(_ray, p, n, t)) // does ray intersect object?
        {
            if (t < tmin) // is intersection point the currently closest one?
            {
                tmin = t;
                _object = o;
                _point  = p;
                _normal = n;
                _t      = t;
            }
        }
    }
    
    return (tmin < DBL_MAX);
}


//-----------------------------------------------------------------------------


vec3 lighting(const vec3& _point, const vec3& _normal, const vec3& _view, const Material& _material)
{
    /** \todo
     Compute the Phong lighting:
     \li start with global ambient contribution
     \li for each light source (stored in vector \c lights) add diffuse and specular contribution
	 \li make sure that all vectors point towards the desired direction
     \li only add diffuse and specular light if object is not in shadow
     \sa Light
     \sa Material
	 \sa vec3::reflect()
	 */

    
    // start with global ambient term
    vec3 color = ambience * _material.ambient;
    

    
    return color;
}


//=============================================================================
