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
//  CLASS CPhongShader
//
//=============================================================================

#ifndef RAYTRACER_PHONGSHADER_H
#define RAYTRACER_PHONGSHADER_H

//== INCLUDES =================================================================
#include "Shader.h"


//== NAMESPACE ================================================================
namespace RAYTRACER {

//== CLASS DEFINITION =========================================================


/*!
	Simpe Phong shader

	\author Gero Mueller
*/
class CPhongShader: public CShader
{
//-------------------------------------------------------------- protected data
protected:	
	// Members
	ColorType            m_colDiffuse;
	ColorType            m_colHighLight;
	RealType             m_rShininess;
//-------------------------------------------------------------- private methods
private:

public:
//-------------------------------------------------------------- constructors
	//! standard constructor
	CPhongShader() {};
	//! initializing constructor
	CPhongShader(const ColorType& colAmbient,
		         const ColorType& colSpecular, 
	             const ColorType& colRefractive,
			     const RealType   fRefractiveIndex,
			     const ColorType& colDiffuse,
				 const ColorType& colHighLight,
				 const RealType   fShininess ):
	                                        CShader(colAmbient, colSpecular, colRefractive, fRefractiveIndex),
										    m_colDiffuse(  colDiffuse ),
											m_colHighLight( colHighLight ),
											m_rShininess(  fShininess )
	{};

	//! destructor	
	~CPhongShader() {};
	
//----------------------------------------------------------- element access
public:
	void  SetDiffuseColor(const ColorType& colDiffuse)  {  m_colDiffuse = colDiffuse;  };
	const ColorType& GetDiffuseColor() const { return m_colDiffuse; };

	void  SetHighLightColor(const ColorType& colHighLight)  {  m_colHighLight = colHighLight;  };
	const ColorType& GetHighLightColor() const { return m_colHighLight; };

	void  SetShininess(const RealType rShininess)  {  m_rShininess = rShininess;  };
	const RealType GetShininess() const { return m_rShininess; };
	
//----------------------------------------------------------- functionality
public:

	ColorType Shade( const TTracingContext& tContext ) const;
};
	
//=============================================================================
} // END_NS_RAYTRACER
//=============================================================================

//=============================================================================
#endif // RAYTRACER_PHONGSHADER_H
//=============================================================================
