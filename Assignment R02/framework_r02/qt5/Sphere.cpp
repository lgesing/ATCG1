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

    VectorType3 vecDiff(m_v3Center - clRay.GetOrigin());


    RealType t_ca = vecDiff | clRay.GetDir();

    if (t_ca < 0)
        return false;

    RealType d2 = (vecDiff | vecDiff) - t_ca * t_ca;
    RealType r2 = m_rRadius * m_rRadius ;

    if (d2 > r2) {
        return false;
    }

    RealType desc = sqrt(r2 - d2);

    RealType t = (t_ca - desc) ;

    if (t < 0.0) {
        t = (t_ca + desc);
    }

    if (t > tContext.t) {
        return false;
    }
    tContext.t = t;

    tContext.v3HitPoint = clRay.Evaluate(tContext.t);
    tContext.v3Normal = (tContext.v3HitPoint - m_v3Center).normalize();

    tContext.pclShader = GetShader();

    return true;

}

//=============================================================================
}; // namespace RAYTRACER
//=============================================================================


