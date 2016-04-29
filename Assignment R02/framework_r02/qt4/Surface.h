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
//  CLASS CSurface
//
//=============================================================================

#ifndef RAYTRACER_SURFACE_H
#define RAYTRACER_SURFACE_H

//== INCLUDES =================================================================
#include "Types.h"
#include "AABBox.h"
#include "Ray.h"
#include "Shader.h"


//== NAMESPACE ================================================================
namespace RAYTRACER {

//== CLASS DEFINITION =========================================================

/*!
	Abstract base class for all objects, that could be hit by a ray.

	\author Gero Mueller
	\author Manuel Massing
*/
class CSurface
{

//-------------------------------------------------------------- private data
private:	
	const CShader* m_pclShader;

//-------------------------------------------------------------- private methods
private:


public:
//-------------------------------------------------------------- constructors
	//! standard constructor
	CSurface(): m_pclShader(0) {};
	virtual ~CSurface(){}

//-------------------------------------------------------------- element access
	virtual void  SetShader(const CShader* pclShader) { m_pclShader = pclShader;  };
	virtual const CShader* GetShader() const { return m_pclShader; };

	//! Return an AABB for this surface.
	virtual CAABBox GetAABB() const = 0;

//--------------------------------------------------------------- intersections

    //! intersection in [t0, t1)?. 
    virtual bool Intersect( const CRay&      clRay, 
	   					    const RealType   t0, 
						    const RealType   t1, 
						    TTracingContext& tContext ) const = 0;

};


//=============================================================================
} // END_NS_RAYTRACER
//=============================================================================

//=============================================================================
#endif // RAYTRACER_SURFACE_H
//=============================================================================
