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

#include "Sphere.h"
#include <float.h>


//== CLASS DEFINITION =========================================================


Sphere::Sphere(const vec3& _center, double _radius)
: center(_center), radius(_radius)
{
}


//-----------------------------------------------------------------------------


bool
Sphere::
intersect(const Ray&  _ray,
          vec3&       _intersection_point,
          vec3&       _intersection_normal,
          double&     _intersection_t) const
{
    
    const vec3 dir = _ray.direction;
    const vec3 oc  = _ray.origin - center;
    
    double a = dot(dir, dir);
    double b = 2.0*dot(dir, oc);
    double c = dot(oc, oc) - radius*radius;
    double d = b*b - 4.0*a*c;
    
    // is there an intersection?
    if (d >= 0.0)
    {
        d = sqrt(d);

        // the two intersection parameters
        double t1 = (-b-d) / (2.0*a);
        double t2 = (-b+d) / (2.0*a);

        // find closer intersection
        _intersection_t = DBL_MAX;
        if (t1 > 1e-5 && t1 < _intersection_t) _intersection_t = t1;
        if (t2 > 1e-5 && t2 < _intersection_t) _intersection_t = t2;

        // was the intersection not just a numerical problem?
        if (_intersection_t != DBL_MAX)
        {
            // return intersection data
            _intersection_point   = _ray(_intersection_t);
            _intersection_normal  = (_intersection_point - center) / radius;
            return true;
        }
    }

    return false;
}


//=============================================================================
