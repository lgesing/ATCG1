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
	RealType t;

	CVectorT<RealType, 3> vecDiff(clRay.GetOrigin() - m_v3Center);

	CVectorT<RealType, 3> vecB(2.0 * (clRay.GetDir() * vecDiff));
	CVectorT<RealType, 3> vecC(vecDiff * vecDiff);

	RealType B = vecB[0] + vecB[1] + vecB[2];
	RealType C = vecC[0] + vecC[1] + vecC[2] - m_rRadius * m_rRadius;

	RealType desc = B * B - 4 * C;

	if (desc < 0.0) {
		return false;
	}

	desc = sqrt(desc);

	if ((tContext.t = ((-B - desc) / 2.0)) > 0.0) {}
	else {
		tContext.t = ((-B + desc) / 2.0);
	}

	tContext.v3HitPoint = clRay.Evaluate(tContext.t);
	tContext.v3Normal = tContext.v3HitPoint - m_v3Center;

	tContext.pclShader = GetShader();

	return true;
}

//=============================================================================
}; // namespace RAYTRACER
//=============================================================================


