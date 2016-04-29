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
//  CLASS CPinholeCamera - IMPLEMENTATION
//
//=============================================================================

#define RAYTRACER_PINHOLECAMERA_CPP

//== INCLUDES =================================================================
#include "PinholeCamera.h"

//== NAMESPACE ===============================================================

namespace RAYTRACER {


//== IMPLEMENTATION ==========================================================

void
CPinholeCamera::MakeONB()
{
  VectorType3 w = (m_v3LookAt-m_v3Eye).normalize();
  VectorType3 u = (w%m_v3Up).normalize();
  VectorType3 v =  u%w;

  m_m33ONB.SetRow(0, u);
  m_m33ONB.SetRow(1, v);
  m_m33ONB.SetRow(2, w);
}

//-----------------------------------------------------------------------------

CRay
CPinholeCamera::GenerateRay(RealType x, RealType y, RealType rWidth, RealType rHeight) const
{
	/*
	You have to implement the generation of a ray throuh the eye point and the center of the given pixel (x,y) on an image plane of size (rWidth,rHeight)
	You can use the 3x3 matrix m_m33ONB which contains an orthonormal basis of the camera coordinate system with axes (right, up, view).
	m_rFocalLength contains the distance from the eye point to the image plane and (m_rLeft, m_rBottom, m_rRight, m_rTop) the size of
	the image on the image plane in the orthonormal basis.
	*/

	CRay ray;
	return ray;
};



//=============================================================================
}; // namespace RAYTRACER
//=============================================================================
