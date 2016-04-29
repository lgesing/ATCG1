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
//  CLASS CDirectionalLight - IMPLEMENTATION
//
//=============================================================================

#define RAYTRACER_POINTLIGHT_CPP


//== INCLUDES =================================================================
#include <cfloat>
#include "DirectionalLight.h"

//== NAMESPACE =============================================================== 

namespace RAYTRACER {
   
//== IMPLEMENTATION ========================================================== 

/*!

*/
void 
CDirectionalLight::ShadowFeeler( unsigned int      uiNumSample,
		                         CRay&             clRay,
				                 RealType&         rRayDomain,
				                 ColorType&        colIntensity) const
{
	clRay.SetDir( m_v3Direction );
	rRayDomain = FLT_MAX;
	colIntensity = m_colIntensity;
};


//=============================================================================
}; // namespace RAYTRACER
//=============================================================================


