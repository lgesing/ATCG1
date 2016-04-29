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


#ifndef RAYTRACER_TYPES_H
#define RAYTRACER_TYPES_H

//== INCLUDES =================================================================
#include "Matrix33T.h"
#include "ColorT.h"
#include <vector>

//== NAMESPACE ================================================================
namespace RAYTRACER {

	
//== FORWARD REFS =============================================================
class CShader;


//== TYPEDEFS =========================================================

typedef   double                  RealType;
typedef   CVectorT<RealType, 4>  VectorType4;
typedef   CVectorT<RealType, 3>  VectorType3;
typedef   CVectorT<RealType, 2>  VectorType2;
typedef   CColor3T<RealType>     ColorType;
typedef   CMatrix33T<RealType>   MatrixType33;
typedef   std::vector<RealType>  RealArrayType;
	
  /*!
    Holds all information concerning intersection
  */
  struct TTracingContext
  {
    /*!
      Ray parameter at intersection point
      Filled by CSurface.Intersect() 
    */
    RealType             t;

    /*!
      3D-coordinate of intersection point.
      Filled by CSurface.Intersect()
    */
    VectorType3          v3HitPoint;

    /*!
      Normal at intersection point
      Filled by CSurface.Intersect()
    */
    VectorType3          v3Normal;
    /*!
      Texture-coordinate at intersection point
      Filled by CSurface.Intersect()
    */
    VectorType2          v2TexCoord;
		
    /*!
      Incoming (light) direction at intersection point
      Filled by CLight.ShadowFeeler()
    */
    VectorType3          v3Incoming;
    /*!
      outgoing (view) direction at intersection point
      Filled by CWhitted.TraceRay()
    */
    VectorType3          v3Outgoing;

    /*!
      Rgb-power of light at intersection point
    */
    ColorType            colLightIntensity;

    /*! Reference to shader at intersection point
      Filled by CSurface.Intersect()
    */
    const CShader*       pclShader;
  };
	


  static const RealType    SELF_ISECT_OFFSET = 1.0e-3;


//=============================================================================
} // END_NS_RAYTRACER
//=============================================================================

//=============================================================================
#endif // RAYTRACER_TYPES_H
//=============================================================================
