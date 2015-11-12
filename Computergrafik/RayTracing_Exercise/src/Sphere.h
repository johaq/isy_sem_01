//=============================================================================
//                                                                            
//   Exercise code for the lecture
//   "Introduction to Computer Graphics"
//   by Prof. Dr. Mario Botsch, Bielefeld University
//
//   Copyright (C) Computer Graphics Group, Bielefeld University.
//                                                                            
//=============================================================================

#ifndef SPHERE_H
#define SPHERE_H


//== INCLUDES =================================================================

#include "Object.h"
#include "vec3.h"


//== CLASS DEFINITION =========================================================


/// \class Sphere Sphere.h
/// This class implements a sphere object, which is specified by its center
/// and its radius. This class overrides the intersection method Object::intersect().
class Sphere : public Object
{
public:

    /// Construct a sphere by specifying center and radius
    Sphere(const vec3& _center=vec3(0,0,0), double _radius=1);

    /// Compute the intersection of the sphere with \c _ray. Return whether
    /// there is an intersection. If there is one, return the intersection data.
    /// This function overrides \c Object::intersect().
	/// \param[in] _ray the ray to intersect the plane with
	/// \param[out] _intersection_point position of the intersection
	/// \param[out] _intersection_normal normal vector at the intersection point
	/// \param[out] _intersection_t ray parameter at the intersection point
    virtual bool intersect(const Ray&  _ray,
                           vec3&       _intersection_point,
                           vec3&       _intersection_normal,
                           double&     _intersection_t) const;


public:
    
	/// center position of the sphere
    vec3   center;

	/// radius of the sphere
    double radius;
};


//-----------------------------------------------------------------------------

/// read sphere from stream
inline std::istream& operator>>(std::istream& is, Sphere& s)
{
    is >> s.center >> s.radius >> s.material;
    return is;
}


//=============================================================================
#endif // SPHERE_H defined
//=============================================================================
