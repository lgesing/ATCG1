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
//  CLASS CMatrix33T
//
//=============================================================================

#ifndef MATRIX33T_H
#define MATRIX33T_H


//== INCLUDES =================================================================
#include <limits>
#include "MatrixT.h"



//== CLASS DEFINITION =========================================================

/*! 
	3x3-Specialization of CMatrixT.

	\author Gero Mueller
*/
template <typename Scalar>
class CMatrix33T : public CMatrixT<Scalar, 3>
{

  typedef typename CMatrixT<Scalar, 3>::VectorType VectorType;
  

//---------------------------------------------------------------- typedefs
public:
	typedef CMatrix33T<Scalar>  Matrix33Type;
	typedef CMatrixT<Scalar, 3> AncestorType;
  

//-------------------------------------------------------------- constructors
public:

  //! default constructor creates uninitialized values.
  inline CMatrix33T() {};

  //! constructor for uniform initialization
  explicit inline CMatrix33T(const Scalar& v) : AncestorType(v) {};

  //! construct from a value array (explicit)
  explicit inline CMatrix33T(const Scalar values[9]) : AncestorType(values) {};

  //! construct from ancestor
  explicit inline CMatrix33T(const AncestorType& other) : AncestorType(other) {};

  //! construct from rotation axis and angle (explicit)
  explicit inline CMatrix33T(const typename CMatrixT<Scalar, 3>::VectorType& vecAxis, const Scalar& angle )
  {
	  MakeRotation( vecAxis, angle );
  };
  //! copy & cast constructor (explicit)
   template<typename otherScalarType>
   explicit inline CMatrix33T(const CMatrix33T<otherScalarType>& other) : CMatrixT<otherScalarType,3>(other) {};

//--------------------------------------------------------------------- casts

  //! cast from matrix with a different scalar type
  template<typename otherScalarType>
  inline Matrix33Type& operator=(const CMatrix33T<otherScalarType>& other) 
  {
    for (int i=0; i<9; ++i) this->m_values[i] = (Scalar) other.m_values[i];
    return *this; 
  };

  //! cast from ancestor
  inline Matrix33Type& operator=(const AncestorType& other) 
  {
    for (int i=0; i<9; ++i) this->m_values[i] = other[i];
    return *this; 
  };

//------------------------------------------------------------------ set
  void Set( Scalar s00, Scalar s01, Scalar s02,
	        Scalar s10, Scalar s11, Scalar s12,
	        Scalar s20, Scalar s21, Scalar s22 )
  {
	  this->m_values[0] = s00;
	  this->m_values[1] = s01;
	  this->m_values[2] = s02;
	  this->m_values[3] = s10;
	  this->m_values[4] = s11;
	  this->m_values[5] = s12;
	  this->m_values[6] = s20;
	  this->m_values[7] = s21;
	  this->m_values[8] = s22;
  };
//------------------------------------------------------------ misc functions	   
  //! make rotation around axis
  void MakeRotation( const VectorType& v3Axis, const Scalar& angle )
  {
    Scalar f_cos = (Scalar) cos((Scalar) angle);
    Scalar f_sin = (Scalar) sin((Scalar) angle);
    Scalar f_one_minus_cos = Scalar(1.0)-f_cos;
    Scalar f_x2 = v3Axis[0]*v3Axis[0];
    Scalar f_y2 = v3Axis[1]*v3Axis[1];
    Scalar f_z2 = v3Axis[2]*v3Axis[2];
    Scalar f_xy_m = v3Axis[0]*v3Axis[1]*f_one_minus_cos;
    Scalar f_xz_m = v3Axis[0]*v3Axis[2]*f_one_minus_cos;
    Scalar f_yz_m = v3Axis[1]*v3Axis[2]*f_one_minus_cos;
    Scalar f_x_sin = v3Axis[0]*f_sin;
    Scalar f_y_sin = v3Axis[1]*f_sin;
    Scalar f_z_sin = v3Axis[2]*f_sin;
    
    this->m_values[0] = f_x2*f_one_minus_cos+f_cos;
    this->m_values[1] = f_xy_m-f_z_sin;
    this->m_values[2] = f_xz_m+f_y_sin;
    this->m_values[3] = f_xy_m+f_z_sin;
    this->m_values[4] = f_y2*f_one_minus_cos+f_cos;
    this->m_values[5] = f_yz_m-f_x_sin;
    this->m_values[6] = f_xz_m-f_y_sin;
    this->m_values[7] = f_yz_m+f_x_sin;
    this->m_values[8] = f_z2*f_one_minus_cos+f_cos;
  };

  //! make rotation from euler-orientation
  void MakeRotation( Scalar fAlpha, Scalar fBeta, Scalar fGamma )
  {
	  Scalar f_sin_alpha = sin( (double) fAlpha );
	  Scalar f_sin_beta  = sin( (double) fBeta );
	  Scalar f_sin_gamma = sin( (double) fGamma );
	  Scalar f_cos_alpha = cos( (double) fAlpha );
	  Scalar f_cos_beta  = cos( (double) fBeta );
	  Scalar f_cos_gamma = cos( (double) fGamma );

	  this->m_values[0] = f_cos_beta * f_cos_gamma;
	  this->m_values[1] = f_cos_alpha* f_sin_gamma + f_sin_alpha*f_sin_beta*f_cos_gamma;
	  this->m_values[2] = f_sin_alpha* f_sin_gamma - f_cos_alpha*f_sin_beta*f_cos_gamma;
	  this->m_values[3] = -f_cos_beta* f_sin_gamma;
	  this->m_values[4] = f_cos_alpha* f_cos_gamma - f_sin_alpha*f_sin_beta*f_sin_gamma;
	  this->m_values[5] = f_sin_alpha* f_cos_gamma + f_cos_alpha*f_sin_beta*f_sin_gamma;
	  this->m_values[6] = f_sin_beta;
	  this->m_values[7] = -f_sin_alpha*f_cos_beta;
	  this->m_values[8] = f_cos_alpha *f_cos_beta;
  };

  void ToAxisRotation(VectorType& v3Axis, Scalar& rfAngle) const
  {
    // Let (x,y,z) be the unit-length axis and let A be an angle of rotation.
    // The rotation matrix is R = I + sin(A)*P + (1-cos(A))*P^2 where
    // I is the identity and
    //
    //       +-        -+
    //   P = |  0 -z +y |
    //       | +z  0 -x |
    //       | -y +x  0 |
    //       +-        -+
    //
    // If A > 0, R represents a counterclockwise rotation about the axis in
    // the sense of looking from the tip of the axis vector towards the
    // origin.  Some algebra will show that
    //
    //   cos(A) = (trace(R)-1)/2  and  R - R^t = 2*sin(A)*P
    //
    // In the event that A = pi, R-R^t = 0 which prevents us from extracting
    // the axis through P.  Instead note that R = I+2*P^2 when A = pi, so
    // P^2 = (R-I)/2.  The diagonal entries of P^2 are x^2-1, y^2-1, and
    // z^2-1.  We can solve these for axis (x,y,z).  Because the angle is pi,
    // it does not matter which sign you choose on the square roots.

      Scalar fTrace = this->m_values[0] + this->m_values[4] + this->m_values[8];
      Scalar fCos = ((Scalar)0.5)*(fTrace-((Scalar)1.0));
      rfAngle = acos(fCos);  // in [0,PI]

      if ( rfAngle > (Scalar)0.0 )
      {
          if ( rfAngle < M_PI )
          {
              v3Axis[0] = this->m_values[7]-this->m_values[5];
              v3Axis[1] = this->m_values[2]-this->m_values[6];
              v3Axis[2] = this->m_values[3]-this->m_values[1];
              v3Axis.normalize();
          }
          else
          {
              // angle is PI
              Scalar fHalfInverse;
              if ( this->m_values[0] >= this->m_values[4] )
              {
                  // r00 >= r11
                  if ( this->m_values[0] >= this->m_values[8] )
                  {
                      // r00 is maximum diagonal term
                      v3Axis[0] = ((Scalar)0.5)*sqrt(this->m_values[0] - this->m_values[4] - this->m_values[8] + (Scalar)1.0);
                      fHalfInverse = ((Scalar)0.5)/v3Axis[0];
                      v3Axis[1] = fHalfInverse*this->m_values[1];
                      v3Axis[2] = fHalfInverse*this->m_values[2];
                  }
                  else
                  {
                      // r22 is maximum diagonal term
                      v3Axis[2] = ((Scalar)0.5)*sqrt(this->m_values[8] - this->m_values[0] - this->m_values[4] + (Scalar)1.0);
                      fHalfInverse = ((Scalar)0.5)/v3Axis[2];
                      v3Axis[0] = fHalfInverse*this->m_values[2];
                      v3Axis[1] = fHalfInverse*this->m_values[5];
                  }
              }
              else
              {
                  // r11 > r00
                  if ( this->m_values[4] >= this->m_values[8] )
                  {
                      // r11 is maximum diagonal term
                      v3Axis[1] = ((Scalar)0.5)*sqrt(this->m_values[4] - this->m_values[0] - this->m_values[8] + (Scalar)1.0);
                      fHalfInverse  = ((Scalar)0.5)/v3Axis[1];
                      v3Axis[0] = fHalfInverse*this->m_values[1];
                      v3Axis[2] = fHalfInverse*this->m_values[5];
                  }
                  else
                  {
                      // r22 is maximum diagonal term
                      v3Axis[2] = ((Scalar)0.5)*sqrt(this->m_values[8] - this->m_values[0] - this->m_values[4] + (Scalar)1.0);
                      fHalfInverse = ((Scalar)0.5)/v3Axis[2];
                      v3Axis[0] = fHalfInverse*this->m_values[2];
                      v3Axis[1] = fHalfInverse*this->m_values[5];
                  }
              }
          }
      }
      else
      {
          // The angle is 0 and the matrix is the identity.  Any axis will
          // work, so just use the x-axis.
          v3Axis[0] = (Scalar)1.0;
          v3Axis[1] = (Scalar)0.0;
          v3Axis[2] = (Scalar)0.0;
      }
  };

  //! return inverse
  Matrix33Type Inverse() const
  {
    Matrix33Type result;

    result(0, 0) = this->m_values[4]*this->m_values[8] - this->m_values[5]*this->m_values[7];
    result(0, 1) = this->m_values[2]*this->m_values[7] - this->m_values[1]*this->m_values[8];
    result(0, 2) = this->m_values[1]*this->m_values[5] - this->m_values[2]*this->m_values[4];
    result(1, 0) = this->m_values[5]*this->m_values[6] - this->m_values[3]*this->m_values[8];
    result(1, 1) = this->m_values[0]*this->m_values[8] - this->m_values[2]*this->m_values[6];
    result(1, 2) = this->m_values[2]*this->m_values[3] - this->m_values[0]*this->m_values[5];
    result(2, 0) = this->m_values[3]*this->m_values[7] - this->m_values[4]*this->m_values[6];
    result(2, 1) = this->m_values[1]*this->m_values[6] - this->m_values[0]*this->m_values[7];
    result(2, 2) = this->m_values[0]*this->m_values[4] - this->m_values[1]*this->m_values[3];

    Scalar fDet = this->m_values[0]*result(0,0) + this->m_values[1]*result(1, 0)+
        this->m_values[2]*result(2,0);

	if ( fDet <= std::numeric_limits<float>::epsilon )
        return Matrix33Type(0.0);

    result *= 1/fDet;
    return result;

  };

};

//== TYPEDEFS =================================================================

/*! float 33-matrix */
typedef CMatrix33T<float> Matrix33f;
/*! double 33-matrix */
typedef CMatrix33T<double> Matrix33d;

#endif // MATRIX33T_H
//=============================================================================

