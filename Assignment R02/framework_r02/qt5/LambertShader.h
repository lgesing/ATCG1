//=============================================================================
//                                                                            
//       Copyright (C) 2010 by Computer Graphics Group, University of Bonn
//                           cg.cs.uni-bonn.de
//                                                                            
//-----------------------------------------------------------------------------
//   
//	part of RMI1, SS10, Excercise 1 
//  
//=============================================================================

//=============================================================================
//
//  CLASS CLambertShader
//
//=============================================================================

#ifndef RAYTRACER_LAMBERTSHADER_H
#define RAYTRACER_LAMBERTSHADER_H

//== INCLUDES =================================================================
#include "Shader.h"


//== NAMESPACE ================================================================
namespace RAYTRACER {

//== CLASS DEFINITION =========================================================


/*!
	Simpe Lambert shader

	\author Gero Mueller
	\author Roland Ruiters
	\author Martin Rump
*/
class CLambertShader: public CShader
{
//-------------------------------------------------------------- protected data
protected:	
	// Members
	ColorType            m_colDiffuse;
//-------------------------------------------------------------- private methods
private:

public:
//-------------------------------------------------------------- constructors
	//! standard constructor
	CLambertShader() {};
	//! initializing constructor
	CLambertShader(const ColorType& colAmbient, const ColorType& colDiffuse ):
	                                        CShader(colAmbient),
										    m_colDiffuse(  colDiffuse )
	{};

	//! destructor	
	~CLambertShader() {};
	
//----------------------------------------------------------- element access
public:
	void  SetColor(const ColorType& colDiffuse)  {  m_colDiffuse = colDiffuse;  };
	const ColorType& GetColor() const { return m_colDiffuse; };
	
//----------------------------------------------------------- functionality
public:

	ColorType Shade( const TTracingContext& tContext ) const;
};
	
//=============================================================================
} // END_NS_RAYTRACER
//=============================================================================

//=============================================================================
#endif // RAYTRACER_LAMBERTSHADER_H
//=============================================================================
