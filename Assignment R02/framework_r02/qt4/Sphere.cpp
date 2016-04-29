//=============================================================================
//
//       Copyright (C) 2010 by Computer Graphics Group, University of Bonn
//                           cg.cs.uni-bonn.de
//
//-----------------------------------------------------------------------------
//
//	part of RMI1, SS10, Excercise 1
//
//
//=============================================================================

//=============================================================================
//
//  CLASS CSphere - IMPLEMENTATION
//
//=============================================================================

#define RAYTRACER_SPHERE_CPP
#define _USE_MATH_DEFINES

//== INCLUDES =================================================================
#include <cmath>
#include "Sphere.h"

//== NAMESPACE ===============================================================

namespace RAYTRACER {

//== IMPLEMENTATION ==========================================================

VectorType2
CSphere::Cartesian2Polar(VectorType3& v) const
{
	RealType z = (v[2]>1) ? 1 : (v[2]<-1) ? -1 : v[2];
	RealType theta = (RealType) acos(z);
	RealType phi =   (RealType) atan2(v[1], v[0]);
	if (phi<0) phi = phi+2*(RealType)M_PI;
	return VectorType2( theta, phi );
}

//-----------------------------------------------------------------------------

bool
CSphere::Intersect(const CRay& clRay, RealType t0, RealType t1, TTracingContext& tContext ) const
{
	/*
		Implement ray-sphere intersection.
		You must set the following member of the TTracingContext struct:
		t          - ray parameter of intersection point
		v3Normal   - Normal of surface at intersection point
		v3HitPoint - Coordinate of intersection point
		v2TexCoord - 2D-Texture coordinate of intersection point (use polar coordinates (method Cartesian2Polar), not needed currently)
		pclShader  - Material of sphere
	*/

  //  clRay.GetOrigin(); // origin of the ray
  //  clRay.GetDir();    // direction of the ray
  //  clRay.GetPower(); // ray color ?

  //  VectorType3 m_v3Center;  // sphere center
  //  RealType    m_rRadius;  // sphere radius
/*
    VectorType3 L = m_v3Center - clRay.GetOrigin(); // vector between ray origin and sphere center

    RealType tca = L |  clRay.GetDir(); // projection on the ray direction

    if(tca < 0)
        return false; // negative direction (=> behinde the rays origin is not needed)

    RealType d = sqrt(L | L - tca * tca);

    if (d > m_rRadius)  // ray misses the sphere and there's no intersection
        return false;



    RealType thc = sqrt(m_rRadius*m_rRadius - d*d);

    t0 = tca - thc;
    t1 = tca + thc;

    */
    RealType t = -1;

    if (t0 > 0 || t1 > 0) {
          if(t0 < t1)
              t = t0;
          else
              t = t1;
    } else {
        return false; // both t0 and t1 are negative
    }


        tContext.t            = t;
        tContext.v3HitPoint   = clRay.Evaluate(t);
        tContext.v3Normal     = tContext.v3HitPoint - m_v3Center;
        tContext.v3Normal.normalize();


       // tContext.v2TexCoord    = ;

        tContext.pclShader    = GetShader();
        return true;




}

//=============================================================================
}; // namespace RAYTRACER
//=============================================================================


