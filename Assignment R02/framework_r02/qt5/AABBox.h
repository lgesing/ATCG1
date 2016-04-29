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
//  CLASS CAABBox
//
//=============================================================================

#ifndef RAYTRACER_AABBOX_H
#define RAYTRACER_AABBOX_H

//== INCLUDES =================================================================
#include <cfloat>
#include "Ray.h"

//== NAMESPACE ================================================================
namespace RAYTRACER {

//== CLASS DEFINITION =========================================================

/*!
	Axis-aligned bounding box.

	\author Gero Mueller
*/
class CAABBox
{
//-------------------------------------------------------------- private data
private:
	VectorType3 m_v3Min;
	VectorType3 m_v3Max;

//-------------------------------------------------------------- private methods
private:

public:
//-------------------------------------------------------------- constructors
	//! standard constructor
	CAABBox(): m_v3Min(FLT_MAX, FLT_MAX, FLT_MAX),
	           m_v3Max(-FLT_MAX, -FLT_MAX, -FLT_MAX) {};
	//! initializing constructor
	CAABBox(const VectorType3& v3Min,
		    const VectorType3& v3Max):
					m_v3Min(v3Min),
					m_v3Max(v3Max) {};

	//! destructor
	~CAABBox() {};

//----------------------------------------------------------- element access
	void  SetMin(const VectorType3& v3Min) {	m_v3Min = v3Min;	};
	const VectorType3& GetMin() const {	return m_v3Min; 	};

	void  SetMax(const VectorType3& v3Max) {	m_v3Max = v3Max;	};
	const VectorType3& GetMax() const { return m_v3Max;	};


//----------------------------------------------------------- operators
	CAABBox& operator+=(const VectorType3& v3Offset)
	{
		m_v3Min += v3Offset;
		m_v3Max += v3Offset;
		return (*this);
	};

	CAABBox& operator*=(const VectorType3& v3Scale)
	{
		m_v3Min *= v3Scale;
		m_v3Max *= v3Scale;
		return (*this);
	};

	CAABBox& operator*=(const RealType fScale)
	{
		m_v3Min *= fScale;
		m_v3Max *= fScale;
		return (*this);
	};

//----------------------------------------------------------- functionality
public:
	const VectorType3 GetCenter() {	return ( m_v3Min + m_v3Max ) * 0.5;	};
	const VectorType3 GetSize() { return (m_v3Max - m_v3Min);  };

	void Reset()
	{
		m_v3Min[0] = m_v3Min[1] = m_v3Min[2] = FLT_MAX;
		m_v3Max[0] = m_v3Max[1] = m_v3Max[2] = -FLT_MAX;
	};

	//!Translate
 	void Translate(const VectorType3& v3Translate)
 	{
 		m_v3Min += v3Translate;
 		m_v3Max += v3Translate;
 	};

 	//!Scale
 	void Scale(const VectorType3& v3Scale)
 	{
 		m_v3Min *= v3Scale;
 		m_v3Max *= v3Scale;
 	};

	//!Extend by point.
	void ExtendBy(const VectorType3& v3Point);

	//!Extend by box.
	void ExtendBy(const CAABBox& clBox);

	//!	Intersect?
	bool Intersect(const CRay& clRay) const;
};


//=============================================================================
} // END_NS_RAYTRACER
//=============================================================================

//=============================================================================
#endif // RAYTRACER_AABBOX_H
//=============================================================================
