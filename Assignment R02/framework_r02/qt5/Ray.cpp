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
//  CLASS CRay - IMPLEMENTATION
//
//=============================================================================

#define RAYTRACER_RAY_CPP


//== INCLUDES =================================================================
#include "Ray.h"

//== NAMESPACE ===============================================================

namespace RAYTRACER {

//== IMPLEMENTATION ==========================================================

CRay
CRay::ReflectedRay(const VectorType3& v3Point,  const VectorType3& v3Normal) const
{
	/*
		Implement the construction of the reflected ray at point v3Point and with normal vector v3Normal
	*/

	VectorType3 r = m_v3Dir - 2.0 * (v3Normal | m_v3Dir) * v3Normal;


	CRay result;
	
	result.SetOrigin(v3Point);
	result.SetDir(r);

	return result;
};


//-----------------------------------------------------------------------------

bool
CRay::RefractedRay(const VectorType3& v3Point,
			       const VectorType3& v3Normal,
				   RealType          rRefractiveIndex,
				   CRay&             clRefractedRay ) const
{
	/*
		Implement the calculation of the refracted ray at point v3Point, with normal vector v3Normal and
		refractive index of the material rRefractiveIndex.
		Return false in case of total internal reflection.

		Hint: We assume that the refraction occurs between a material with the given refractive index and air (refractive index ~1).
	*/

	// using rRefrectiveIndex as eta
	RealType eta = rRefractiveIndex;

	RealType desc = 1.0 - (1.0 / (eta * eta) * (1.0 - (v3Normal | m_v3Dir) * (v3Normal | m_v3Dir)));

	if (desc < 0) {
		return false;
	}

	RealType cn, cd;
	cn = -(1.0 / eta) * (v3Normal | m_v3Dir) - sqrt(desc);
	cd = 1.0 / eta;

	clRefractedRay.SetOrigin(v3Point);
	clRefractedRay.SetDir(cn * v3Normal + cd * m_v3Dir);

	return true;
};


//=============================================================================
}; // namespace RAYTRACER
//=============================================================================


