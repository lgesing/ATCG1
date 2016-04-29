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
//  CLASS CPointLight
//
//=============================================================================

#ifndef RAYTRACER_POINTLIGHT_H
#define RAYTRACER_POINTLIGHT_H

//== INCLUDES =================================================================
#include "Light.h"


//== NAMESPACE ================================================================
namespace RAYTRACER {

//== CLASS DEFINITION =========================================================

/*!
	PointLight
	
	\author Gero Mueller
*/
class CPointLight: public CLight
{

//-------------------------------------------------------------- private data
private:	
	VectorType3 m_v3Position;
	ColorType   m_colIntensity;

public:
//-------------------------------------------------------------- constructors
	//! standard constructor
	CPointLight() {};

	//! initializing constructor
	CPointLight(const VectorType3& v3Position,
		        const ColorType&   colIntensity): m_v3Position(v3Position),
	                                          m_colIntensity(colIntensity) {};
	
	//! destructor	
	~CPointLight() {};
	

//----------------------------------------------------------- access elements

	void SetPosition(const VectorType3& v3Position) { m_v3Position = v3Position; };
	const VectorType3& GetPosition() const { return m_v3Position; };

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
#endif // RAYTRACER_POINTLIGHT_H
//=============================================================================

