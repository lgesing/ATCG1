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
//  CLASS CSurfacePlane
//
//=============================================================================

#ifndef RAYTRACER_SURFACEPLANE_H
#define RAYTRACER_SURFACEPLANE_H

//== INCLUDES =================================================================
#include "Surface.h"


//== NAMESPACE ================================================================
namespace RAYTRACER {


//== CLASS DEFINITION =========================================================
/*!
	A plane 

	\author Gero Mueller
*/
class CPlane: public CSurface
{
//-------------------------------------------------------------- private data
private:	
	VectorType3 m_v3Normal;
	VectorType3 m_v3Point;

	VectorType3 m_v3X, m_v3Y;
//-------------------------------------------------------------- private methods
private:
	void ConstructONB(const VectorType3& v, VectorType3& x, VectorType3& y, VectorType3& z ) const;

public:
//-------------------------------------------------------------- constructors
	//! standard constructor
	CPlane(): m_v3Normal(0.0), m_v3Point(0.0) {};

	//! initializing constructor 
	CPlane(const VectorType3& v3Normal, const VectorType3& v3Point): m_v3Point(v3Point)
	{
		SetNormal(v3Normal);
	};

	virtual ~CPlane(){}
//-------------------------------------------------------------- element access
	void  SetNormal(const VectorType3& v3Normal) 
	{ 
		ConstructONB(v3Normal, m_v3X, m_v3Y, m_v3Normal);
	};
	const VectorType3& GetNormal() const { return m_v3Normal; };

	void  SetPoint(const VectorType3& v3Point) {	m_v3Point = v3Point; };
	const VectorType3& GetPoint() const { return m_v3Point; };

	CAABBox GetAABB() const { return CAABBox(); };


//--------------------------------------------------------------- intersections

    bool Intersect( const CRay&        clRay, 
	   			    const RealType     t0, 
					const RealType     t1, 
				    TTracingContext&   tContext ) const;

};


//=============================================================================
} // END_NS_RAYTRACER
//=============================================================================

//=============================================================================
#endif // RAYTRACER_SURFACEPLANE_H
//=============================================================================

