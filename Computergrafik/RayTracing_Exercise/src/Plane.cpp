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

#include "Plane.h"
#include <float.h>


//== CLASS DEFINITION =========================================================



Plane::Plane(const vec3& _center, const vec3& _normal)
: center(_center), normal(_normal)
{
}


//-----------------------------------------------------------------------------


bool
Plane::
intersect(const Ray& _ray,
          vec3&      _intersection_point,
          vec3&      _intersection_normal,
          double&    _intersection_t ) const
{

/** \todo
 \li compute the intersection of the plane with \c _ray
 \li if ray and plane are parallel there is no intersection
 \li otherwise compute intersection data and store it in 
 \c _intersection_point, \c _intersection_normal, and \c _intersection_t.
 \li return whether there is an intersection for t>1e-5 (avoids "shadow acne").
*/
    
    return false;
}


//=============================================================================
