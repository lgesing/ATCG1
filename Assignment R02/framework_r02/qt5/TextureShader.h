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
//  CLASS CTextureShader
//
//=============================================================================

#ifndef RAYTRACER_TEXTURESHADER_H
#define RAYTRACER_TEXTURESHADER_H

//== INCLUDES =================================================================
#include "Shader.h"
#include <QtGui/QImage>

//== NAMESPACE ================================================================

namespace RAYTRACER {

//== CLASS DEFINITION =========================================================


/*!
	Simple Texture Shader

	\author Gero Mueller
*/
class CTextureShader: public CShader
{
//-------------------------------------------------------------- protected data
protected:	
	// Members
	QImage       m_clTexture;	
	VectorType2  m_v2Scale;

//-------------------------------------------------------------- private methods
private:

public:
//-------------------------------------------------------------- constructors
	//! standard constructor
	CTextureShader() : m_v2Scale(1, 1) {};
	//! initializing constructor
	CTextureShader(const ColorType& colAmbient,
		           const ColorType& colSpecular, 
	               const ColorType& colRefractive,
			       const RealType   fRefractiveIndex,
				   const VectorType2& v2Scale):
	                                        CShader(colAmbient, colSpecular, colRefractive, fRefractiveIndex),
											m_v2Scale(v2Scale)
	{};

	//! destructor	
	virtual ~CTextureShader() {};
	
//----------------------------------------------------------- element access
public:
	void LoadTexture(const std::string& sFilename);
	void SetTexture(const QImage& clQImage) { m_clTexture = clQImage.copy(); };

	void SetScale(const VectorType2& v2Scale) { m_v2Scale = v2Scale; };
	VectorType2 GetScale() const { return m_v2Scale; };
	
//----------------------------------------------------------- functionality
public:
	/*!
		Shade.
		Assume spatially varying diffuse.
	*/
	ColorType Shade( const TTracingContext& tContext ) const;

};
	
//=============================================================================
} // END_NS_RAYTRACER
//=============================================================================

//=============================================================================
#endif // RAYTRACER_TEXTURESHADER_H
//=============================================================================
