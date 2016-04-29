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
//  CLASS CSphere
//
//=============================================================================

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

//== INCLUDES =================================================================
#include "Surface.h"


//== NAMESPACE ================================================================
namespace RAYTRACER {

//== CLASS DEFINITION =========================================================

/*!
	A sphere. The typical first raytracing-surface!

	\author Gero Mueller
*/
class CSphere: public CSurface
{
//-------------------------------------------------------------- private data
private:	
  VectorType3 m_v3Center;
  RealType    m_rRadius;

//-------------------------------------------------------------- private methods
private:
	VectorType2 Cartesian2Polar(VectorType3& v) const;

public:
//-------------------------------------------------------------- constructors
	//! standard constructor
	CSphere()  {};
	//! initializing constructor 
	CSphere(const VectorType3& v3Center, const RealType& rRadius): 
	                                               m_v3Center(  v3Center  ), 
												   m_rRadius (  rRadius   ) {};
	virtual ~CSphere(){}

//-------------------------------------------------------------- element access

	void  SetCenter(const VectorType3& v3Center) { m_v3Center = v3Center; };
    const VectorType3& GetCenter() const { return m_v3Center; };

	void  SetRadius(const RealType& rRadius) { m_rRadius = rRadius; };
	const RealType GetRadius() const  { return m_rRadius; };

	CAABBox GetAABB() const
	{ 
		VectorType3 v3_offset = VectorType3::vectorized(m_rRadius);
		return CAABBox( m_v3Center-v3_offset, m_v3Center+v3_offset); 
	};

//--------------------------------------------------------------- intersections

    bool Intersect( const CRay&       clRay, 
	   			    const RealType    t0, 
					const RealType    t1, 
				    TTracingContext&  tContext ) const;

};


//=============================================================================
} // END_NS_RAYTRACER
//=============================================================================

//=============================================================================
#endif // RAYTRACER_SPHERE_H
//=============================================================================
