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
//  CLASS CGlassShader
//
//=============================================================================

#ifndef RAYTRACER_GLASSSHADER_H
#define RAYTRACER_GLASSSHADER_H

//== INCLUDES =================================================================
#include "Shader.h"


//== NAMESPACE ================================================================
namespace RAYTRACER {

//== CLASS DEFINITION =========================================================


/*!
	Simpe Glass shader

	\author Gero Mueller
	\author Roland Ruiters
	\author Martin Rump
*/
class CGlassShader: public CShader
{
//-------------------------------------------------------------- protected data
protected:	
	// Members
//-------------------------------------------------------------- private methods
private:

public:
//-------------------------------------------------------------- constructors
	//! initializing constructor
	CGlassShader(const ColorType& colAmbient = ColorType(0) ):
	                                        CShader(colAmbient,ColorType(0.12),ColorType(0.8),1.4)
	{};

	//! destructor	
	~CGlassShader() {};
	
//----------------------------------------------------------- element access
public:
	
//----------------------------------------------------------- functionality
public:

	ColorType Shade( const TTracingContext& tContext ) const;
};
	
//=============================================================================
} // END_NS_RAYTRACER
//=============================================================================

//=============================================================================
#endif // RAYTRACER_GLASSSHADER_H
//=============================================================================
