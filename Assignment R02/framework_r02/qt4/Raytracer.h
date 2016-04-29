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
//  CLASS CWhitted
//
//=============================================================================

#ifndef RAYTRACER_WHITTED_H
#define RAYTRACER_WHITTED_H

//== INCLUDES =================================================================
#include <list>
#include <QtGui/QImage>
#include <QtGui/QProgressDialog>

#include "Types.h"
#include "PinholeCamera.h"
#include "Light.h"
#include "Surface.h"


//== NAMESPACE ================================================================
namespace RAYTRACER {


//== CLASS DEFINITION =========================================================

/*!
 *  Whitted-style raytracer
 *
 *	
 */
class CWhitted
{
//-------------------------------------------------------------- private data
private:		
	CPinholeCamera  m_clPinholeCamera;
	ColorType       m_colBackground;
	ColorType       m_colAmbient;

	typedef std::list<CLight*> LightListType;
	LightListType m_LightList;
	bool  m_bOwnsLights;
//-------------------------------------------------------------- private methods
private:
	ColorType  TraceRay( const CSurface*   pclScene, 
		                 const CRay&	   clRay, 
					     unsigned int      uiDepth );
	
	ColorType  Shade( const CSurface*     pclScene,
		              TTracingContext&    tContext );

//-------------------------------------------------------------- constructors
public:
	//! default constructor
	CWhitted() : m_colBackground(0),
				 m_colAmbient(0),
				 m_bOwnsLights(true)
	{};
	
	//! destructor
	~CWhitted()
	{
		RemoveAllLights();
	};
//----------------------------------------------------------- element access
public:
	//@{
	//!Background color
	void  SetBackgroundColor(const ColorType& colBackground) { m_colBackground = colBackground; };
	const ColorType& GetBackgroundColor() const  { return m_colBackground; };
	//@}

	//@{ 
	//!Ambient color
	void  SetAmbientColor(const ColorType& colAmbient) { m_colAmbient = colAmbient; };
	const ColorType& GetAmbientColor() const  { return m_colAmbient; };
	//@}

	//@{ 
	//!Manage lights
	void AddLight(CLight* pclLight) { m_LightList.push_back( pclLight ); };
	void RemoveAllLights();
	//@}

	//!Manage camera
	CPinholeCamera& GetCamera() { return m_clPinholeCamera; };

//----------------------------------------------------------- functionality

	//! Render scene with the classic algorithm
	void Render(const CSurface*    pclScene, 
				unsigned int       uiMaxDepth,
				QImage&            clQImage,
				QProgressDialog*   pclQProgressDialog = 0 );

};

//=============================================================================
} // END_NS_RAYTRACER
//=============================================================================

//=============================================================================
#endif // RAYTRACER_WHITTED_H
//=============================================================================
