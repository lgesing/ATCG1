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
//  CLASS CSurfaceList
//
//=============================================================================

#ifndef RAYTRACER_SURFACELIST_H
#define RAYTRACER_SURFACELIST_H

//== INCLUDES =================================================================
#include "Types.h"
#include "Surface.h"
#include <list>

//== NAMESPACE ================================================================
namespace RAYTRACER {

//== CLASS DEFINITION =========================================================

/*!
	Simple linear list of surfaces

	\author Gero Mueller
*/
class CSurfaceList: public CSurface
{
//-------------------------------------------------------------- private types


//-------------------------------------------------------------- private data
private:	
	typedef std::list<CSurface*> SurfaceContainerType;

	SurfaceContainerType m_SurfaceContainer;
	CAABBox  m_bbox;

	bool  m_bOwnsSurfaces;
//-------------------------------------------------------------- constructors
public:
	//! constructor
	CSurfaceList(bool bOwnsSurfaces=true) : m_bOwnsSurfaces(bOwnsSurfaces) {};

	//! destructor
	virtual ~CSurfaceList() 
	{
		RemoveAllSurfaces();
	};
//-------------------------------------------------------------- element access

	CAABBox GetAABB() const { return m_bbox; };

//-------------------------------------------------------------- interface

	void AddSurface(CSurface* pclSurface)
	{
	    m_SurfaceContainer.push_back(pclSurface);
		m_bbox.ExtendBy( pclSurface->GetAABB() );
	};

	void RemoveAllSurfaces();

//--------------------------------------------------------------- intersections

    bool Intersect( const CRay&         clRay, 
	   			    const RealType      t0, 
				    const RealType      t1, 
					TTracingContext&    tContext ) const;

};


//=============================================================================
} // END_NS_RAYTRACER
//=============================================================================

//=============================================================================
#endif // RAYTRACER_SURFACELIST_H
//=============================================================================
