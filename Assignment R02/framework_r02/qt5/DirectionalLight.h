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
//  CLASS CDirectionalLight
//
//=============================================================================

#ifndef RAYTRACER_DIRECTIONALLIGHT_H
#define RAYTRACER_DIRECTIONALLIGHT_H

//== INCLUDES =================================================================
#include "Light.h"


//== NAMESPACE ================================================================
namespace RAYTRACER {

//== CLASS DEFINITION =========================================================

/*!
	PointLight
	
	\author Gero Mueller
*/
class CDirectionalLight: public CLight
{

//-------------------------------------------------------------- private data
private:	
	VectorType3 m_v3Direction;
	ColorType   m_colIntensity;

public:
//-------------------------------------------------------------- constructors
	//! standard constructor
	CDirectionalLight() {};

	//! initializing constructor
	CDirectionalLight(const VectorType3& v3Direction,
		              const ColorType&   colIntensity): m_v3Direction(v3Direction),
	                                                    m_colIntensity(colIntensity) {};
	
	//! destructor	
	~CDirectionalLight() {};
	

//----------------------------------------------------------- access elements

	void SetDirection(const VectorType3& v3Direction) { m_v3Direction = v3Direction; };
	const VectorType3& GetDirection() const { return m_v3Direction; };

	void SetIntensity(const ColorType& colIntensity) { m_colIntensity = colIntensity; };
	const ColorType& GetIntensity() const { return m_colIntensity; };

//----------------------------------------------------------- functionality
public:
	void ShadowFeeler(unsigned int      uiNumSample,
		              CRay&             clRay,
				      RealType&         rRayDomain,
				      ColorType&        colIntensity) const;
};


//=============================================================================
} // END_NS_RAYTRACER
//=============================================================================

//=============================================================================
#endif // RAYTRACER_DIRECTIONALLIGHT_H
//=============================================================================

