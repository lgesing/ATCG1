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
//  CLASS CPinholeCamera
//
//=============================================================================

#ifndef RAYTRACER_PINHOLECAMERA_H
#define RAYTRACER_PINHOLECAMERA_H

//== INCLUDES =================================================================

#include "Types.h"
#include "Ray.h"

//== NAMESPACE ================================================================
namespace RAYTRACER {


//== CLASS DEFINITION =========================================================

/*!
	Simple pinholecamera-simulation which defines an image- (or film) plane 
	in space. It uses Eye, LookAt and Up to define
	orientation and focal length for the imageplane's distance from the eye.

	\author Gero Mueller
*/
class CPinholeCamera
{
//-------------------------------------------------------------- private data
private:
	VectorType3            m_v3Eye, m_v3LookAt, m_v3Up;
	RealType			   m_rFocalLength;
	RealType			   m_rLeft, m_rBottom, m_rRight, m_rTop;

    MatrixType33           m_m33ONB;

    void MakeONB();

//-------------------------------------------------------------- constructors
public:
	/*!
	  Constructor with initializing values
	*/
	CPinholeCamera( const VectorType3& v3Eye     = VectorType3(0, 0, 0), 
		            const VectorType3& v3LookAt  = VectorType3(0, 0, -1),
		            const VectorType3& v3Up      = VectorType3(0, 1, 0),
		            const RealType rFocalLength = 1,
		            const RealType rLeft        = -1,
		            const RealType rBottom      = -1,
		            const RealType rRight       = 1,
		            const RealType rTop         = 1) : 
	                            m_v3Eye       ( v3Eye      ), 
		                        m_v3LookAt    ( v3LookAt  ),
								m_v3Up        ( v3Up      ),
								m_rFocalLength( rFocalLength ),
								m_rLeft       ( rLeft     ),
								m_rBottom     ( rBottom    ),
								m_rRight      ( rRight    ),
								m_rTop        ( rTop       )
	{
		MakeONB(); 
	};

//----------------------------------------------------------- element access
public:
	//@{
	//!Eye-vector
	void SetEye( const VectorType3& v3Eye ) 
	{
		m_v3Eye = v3Eye;
		MakeONB();
	};
	const VectorType3& GetEye() const { 	return m_v3Eye; };
	//@}

	//@{
	//!LookAt-vector
	void SetLookAt(const VectorType3& v3LookAt) 
	{
		m_v3LookAt = v3LookAt;
		MakeONB();
	};
	const VectorType3& GetLookAt() const { return m_v3LookAt; };
	//@}

	//@{
	//!Up-vector
	void SetUp(const VectorType3& v3Up) 
	{ 
		m_v3Up = v3Up; 		
		MakeONB();
	};
	const VectorType3& GetUp() const { return m_v3Up; };
	//@}

	//@{
	//!Focal length
	void SetFocalLength(const RealType rFocalLength) { m_rFocalLength = rFocalLength;};
	RealType GetFocalLength() const { return m_rFocalLength;  };
	//@}

	//@{
	//!viewing window corners
	void SetWindow(RealType rLeft, RealType rBottom, RealType rRight, RealType rTop) 
	{
		m_rLeft = rLeft;
		m_rBottom = rBottom;
		m_rRight = rRight;
		m_rTop = rTop;
	};
	void GetWindow(RealType& rLeft, RealType& rBottom, RealType& rRight, RealType& rTop ) 
	{
		rLeft = m_rLeft;
		rBottom = m_rBottom;
		rRight = m_rRight;
		rTop = m_rTop;
	};
	//!force aspect-ratio and center imageplane
	void SetAspectRatio(RealType rAspect)
	{
		RealType r_width = fabs(m_rRight - m_rLeft);
		RealType r_height = r_width/rAspect;
		
		m_rLeft = -r_width/2.;
		m_rRight=  r_width/2.;
		m_rBottom = -r_height/2.;
		m_rTop = r_height/2.;
	};
	//@}

//----------------------------------------------------------- functionality

	//! generateRay for pixel (x, y) 
	CRay  GenerateRay(RealType x, RealType y, RealType rWidth, RealType rHeight) const;

	//! set to canonical position
	void Reset()
	{
		m_v3Eye = VectorType3(0, 0, 1);
		m_v3LookAt = VectorType3(0, 0, 0);
		m_v3Up = VectorType3(0, 1, 0);
		m_rFocalLength = 2;
		SetWindow(-1, -1, 1, 1);
	};
};


//=============================================================================
} // END_NS_RAYTRACER
//=============================================================================

//=============================================================================
#endif // RAYTRACER_PINHOLECAMERA_H
//=============================================================================
