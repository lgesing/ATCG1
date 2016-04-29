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
//  CLASS CShader
//
//=============================================================================

#ifndef RAYTRACER_SHADER_H
#define RAYTRACER_SHADER_H

//== INCLUDES =================================================================
#include "Types.h"
#include "Ray.h"


//== NAMESPACE ================================================================
namespace RAYTRACER {


//== CLASS DEFINITION =========================================================


/*!
	Abstract base class for shaders

	\author Gero Mueller
*/
class CShader
{
//-------------------------------------------------------------- protected data
protected:	
	ColorType m_colAmbient;
	ColorType m_colSpecular;
	ColorType m_colRefractive;
	RealType  m_rRefractiveIndex;

//-------------------------------------------------------------- private methods
private:

public:
//-------------------------------------------------------------- constructors

	//! initializing constructor
	CShader(const ColorType& colAmbient   =ColorType(0),
		    const ColorType& colSpecular  =ColorType(0), 
	        const ColorType& colRefractive=ColorType(0),
			const RealType   rRefractiveIndex=1) : 
	                             m_colAmbient    (   colAmbient    ),
								 m_colSpecular   (   colSpecular   ),
								 m_colRefractive (   colRefractive ),
								 m_rRefractiveIndex( rRefractiveIndex )
	{};

	//! destructor	
	virtual ~CShader() {};
	
//----------------------------------------------------------- element access
public:
	void  SetAmbientColor(const ColorType& colAmbient) { m_colAmbient = colAmbient; }
	const ColorType& GetAmbientColor() const           { return m_colAmbient; }

	void  SetSpecularColor(const ColorType& colSpecular) { m_colSpecular = colSpecular; }
	const ColorType& GetSpecularColor() const              { return m_colSpecular; }

	void  SetRefractiveColor(const ColorType &colRefractive) {	m_colRefractive = colRefractive; };
	const ColorType &GetRefractiveColor() const { return m_colRefractive; };

	void  SetRefractiveIndex(const RealType rRefractiveIndex)   { m_rRefractiveIndex = rRefractiveIndex; }
	const RealType GetRefractiveIndex() const       { return m_rRefractiveIndex; };


//----------------------------------------------------------- class info
public:
	bool IsSpecular() const   { return (m_colSpecular.GetEnergy() > (RealType)0.0); };
	bool IsRefractive() const { return (m_rRefractiveIndex != 1);    };
	
//----------------------------------------------------------- functionality
public:
	/*!
		Shade.
		Evaluate the BRDF times Light weighted by the cosine of the incoming direction
	*/
	virtual ColorType Shade( const TTracingContext& tContext ) const = 0;

	/*!
		Evaluate ambient term for Whitted-Style ray tracing
	*/
	virtual ColorType ShadeAmbient( const ColorType& colAmbient ) const { return colAmbient * m_colAmbient; };

};
	
//=============================================================================
} // END_NS_RAYTRACER
//=============================================================================

//=============================================================================
#endif // RAYTRACER_SHADER_H
//=============================================================================
