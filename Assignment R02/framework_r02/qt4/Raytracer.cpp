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
//  CLASS CWhitted - IMPLEMENTATION
//
//=============================================================================

#define RAYTRACER_WHITTED_CPP


//== INCLUDES =================================================================

#include <omp.h>
#include <QtGui/QApplication>
#include "Raytracer.h"

//== NAMESPACE ===============================================================

namespace RAYTRACER {

//== IMPLEMENTATION ==========================================================

void
CWhitted::Render(const CSurface*    pclScene,
				 unsigned int       uiMaxDepth,
				 QImage&            clQImage,
				 QProgressDialog*   pclQProgressDialog)
{
	ColorType col(0);
	CRay cl_ray;
	int y, x;

	int i_width = clQImage.width();
	int i_height= clQImage.height();

	//correct aspect ratio
	m_clPinholeCamera.SetAspectRatio(i_width/(RealType)i_height);

	/*

		Implement:

		for all pixels
			generate ray
			trace ray through scene and obtain color
			set color in clQImage

		Hint: Use the methods Clamp() and GetPacked() of class ColorType
			  to convert the floating point colors to integer
				 as needed by the method QImage.setPixel().

		Hint: A progress bar can be created using the following code snippet:
				if (pclQProgressDialog)
				{
  					pclQProgressDialog->setProgress( y );
					qApp->processEvents();
					if ( pclQProgressDialog->wasCancelled() ) break;
				}
	*/

}

//-----------------------------------------------------------------------------


ColorType
CWhitted::TraceRay(const CSurface*   pclScene,
				   const CRay&	     crclRay,
				   unsigned int      uiDepth )
{
	ColorType col(0);
	if (0 == uiDepth) return col;
	--uiDepth;


	/*
		Implement:

		(i)  compute the nearest intersection point of the ray with the scene
		(ii) evaluate the local light model at the intersection point (method Shade())
		(iii)if surface hit by the ray is specular (CShader.IsSpecular()), compute and trace the reflected ray
		(iv) if surface is transparent (CShader.IsTransparent()), compute and trace the refracted ray
		(v)  add the weighted (CShader.GetSpecularColor(), CShader.GetRefractiveColor())
		     radiances of the secondary rays to the result of the local light model
        (vi) if no surface is hit, return the background color

		Hint: You will need an instance of the structure TTracingContext, which contains all necessary arguments for tracing rays
	*/

	return 0;
}


//-----------------------------------------------------------------------------

ColorType
CWhitted::Shade( const CSurface*   pclScene,
				 TTracingContext&  tContext )
{
	/*
		Implement:

		set ambient part of the color
		for all light sources
			compute shadow ray and intensity
			intersect shadow ray with scene
			if no intersected surface between surface and light source
				evaluate local light model (CShader.Shade())
				add result to final color

		Hints:

		The local light model is defined by the classes derived from CShader.
		The methods ShadeAmbient() and Shade() should be used here. The current shader
		can be taken from argument tContext.
		The light sources can be found in the STL-container m_LightList.
		Light sources are derived from class CLight and implement the method ShadowFeeler()
		which can be used to compute ray direction, domain and intensity.
		Use these to initialize the variables tContext.v3Incoming and tContext.colLightIntensity
		before evaluating the local light model using Shade()
	*/

	ColorType color(0);

	return color;
}

//-----------------------------------------------------------------------------

void
CWhitted::RemoveAllLights()
{
	if (m_bOwnsLights)
	{
		LightListType::iterator it     = m_LightList.begin();
		LightListType::iterator it_end = m_LightList.end();
		for( ;it != it_end; ++it)
		{
			delete (*it);
		}
	}
	m_LightList.clear();
}

//=============================================================================
}; // namespace RAYTRACER
//=============================================================================


