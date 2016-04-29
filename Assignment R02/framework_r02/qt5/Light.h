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
//  CLASS CLight
//
//=============================================================================

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H

//== INCLUDES =================================================================
#include "Types.h"
#include "Ray.h"


//== NAMESPACE ================================================================
namespace RAYTRACER {

//== CLASS DEFINITION =========================================================

/*!
	Abstract base for light emitting objects
	
	\author Gero Mueller
*/
class CLight
{
//-------------------------------------------------------------- typedefs
public:

//-------------------------------------------------------------- private data
private:	

//-------------------------------------------------------------- private methods
private:

public:
//-------------------------------------------------------------- constructors
	//! standard constructor
	CLight() {};
	
	//! destructor	
	virtual ~CLight() {};
	

//----------------------------------------------------------- functionality
public:
	/*!
		Get a ray to light source and its valid domain and intensity of the light source.
		
		\param uiNumSample Reserved for Monte-Carlo raytracing.
	*/
	virtual void ShadowFeeler(unsigned int      uiNumSample,
		                      CRay&             clRay,
				              RealType&         rRayDomain,
							  ColorType&        colIntensity) const = 0;

};


//=============================================================================
} // END_NS_RAYTRACER
//=============================================================================

//=============================================================================
#endif // RAYTRACER_LIGHT_H
//=============================================================================

