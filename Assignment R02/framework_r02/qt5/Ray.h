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
//  CLASS CRay
//
//=============================================================================

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

//== INCLUDES =================================================================

#include "Types.h"

//== NAMESPACE ================================================================

namespace RAYTRACER {

//== CLASS DEFINITION =========================================================

/*!
	Simple ray: A point and a direction.
	
	\author Gero Mueller
*/
class CRay 
{
//-------------------------------------------------------------- private data
private:	
	VectorType3  m_v3Origin;
	VectorType3  m_v3Dir;
	ColorType    m_colPower;

//-------------------------------------------------------------- private methods
private:

public:
//-------------------------------------------------------------- constructors
	//! standard constructor
	CRay():  m_v3Origin(  0, 0, 0 ),
	         m_v3Dir   (  0, 0, 0 ),
	         m_colPower(  0.0 ) {};

	//! Constructor with initializing values
	CRay( const VectorType3  origin, 
		  const VectorType3  dir,
		  const ColorType   power ) : 
	                        m_v3Origin(  origin  ), 
							m_v3Dir   (  dir     ), 
							m_colPower(  power   ) {};

	//! destructor	
	~CRay() {};
	
//----------------------------------------------------------- element access
	//! Set ray origin
	void SetOrigin(const VectorType3& origin) {	m_v3Origin = origin; };
	//! Get ray origin
	const VectorType3& GetOrigin() const {  return m_v3Origin; 	};
	
	//! Set ray direction
	void SetDir(const VectorType3& dir) { m_v3Dir = dir; };
	//! Get ray direction
	const VectorType3& GetDir() const  { return m_v3Dir;  };

	//! Set ray power (color)
	void SetPower(const ColorType& power) { 	m_colPower = power; };
	//! Get ray power (color)
	const ColorType& GetPower() const { return m_colPower; 	};


//----------------------------------------------------------- operators


//----------------------------------------------------------- functionality
	//!	Evaluate ray at parameter t 
	VectorType3 Evaluate(RealType t) const {return m_v3Origin + t*m_v3Dir; };

	//! Reflect ray at point around normal.
	CRay  ReflectedRay(const VectorType3& v3Point,  const VectorType3& v3Normal) const;

	//!	Refract ray at point given normal and refractive index.
	bool  RefractedRay(const VectorType3& v3Point, 
			           const VectorType3& v3Normal,
					   RealType          rRefractiveIndex,
					   CRay&             clRefractedRay ) const;

};


//=============================================================================
} // END_NS_RAYTRACER
//=============================================================================

//=============================================================================
#endif // RAYTRACER_RAY_H
//=============================================================================
