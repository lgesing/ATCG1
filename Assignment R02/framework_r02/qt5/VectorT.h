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
//  CLASS CVectorT
//
//=============================================================================

#ifndef VECTOR_H
#define VECTOR_H


//== INCLUDES =================================================================


#include <iostream>
#include <assert.h>
#include <math.h>


//== CLASS DEFINITION =========================================================

#define unroll(expr)      for (int i=0; i<DIM; ++i) expr(i)

/*! 
	A vector is an array of <DIM> values of type <Scalar>.
    The actual data is stored in an VectorDataT, this class just adds
    the necessary operators.
	Inspired by OpenSG.
	
	\author Gero Mueller
*/
template <typename Scalar, int DIM>
class CVectorT 
{
public:

  //---------------------------------------------------------------- class info

  //! type of this vector
  typedef CVectorT<Scalar,DIM>  VectorType;

  //! returns dimension of the vector
  static inline unsigned int size() { return DIM; }
  
  static const unsigned int m_size = DIM;

//---------------------------------------------------------------- protected data
protected:
	Scalar m_values[DIM];

  //-------------------------------------------------------------- constructors
public:

  //! default constructor creates uninitialized values.
  inline CVectorT() {};

  //! special constructor for 1D vectors
  explicit inline CVectorT(const Scalar& v0) 
  {
    assert(DIM==1);
    m_values[0] = v0; 
  };

  //! special constructor for 2D vectors
  inline CVectorT(const Scalar& v0, const Scalar& v1) 
  {
    assert(DIM==2);
    m_values[0] = v0; m_values[1] = v1; 
  };

  //! special constructor for 3D vectors
  inline CVectorT(const Scalar& v0, const Scalar& v1, const Scalar& v2) 
  {
    assert(DIM==3);
    m_values[0]=v0; m_values[1]=v1; m_values[2]=v2; 
  };

  //! special constructor for 4D vectors
  inline CVectorT(const Scalar& v0, const Scalar& v1, 
		 const Scalar& v2, const Scalar& v3) 
  {
    assert(DIM==4); 
    m_values[0]=v0; m_values[1]=v1; m_values[2]=v2; m_values[3]=v3; 
  };


  //! construct from a value array (explicit)
  explicit inline CVectorT(const Scalar values[DIM]) 
  {
    memcpy(m_values, values, DIM*sizeof(Scalar)); 
  };


  //! copy & cast constructor (explicit)
  template<typename otherScalarType>
  explicit inline CVectorT(const CVectorT<otherScalarType,DIM>& other) 
  { 
    operator=(other); 
  };


  //--------------------------------------------------------------------- casts

  //! cast from vector with a different scalar type
  template<typename otherScalarType>
  inline VectorType& operator=(const CVectorT<otherScalarType,DIM>& other) 
  {
#define expr(i)  m_values[i] = (Scalar)other[i];
    unroll(expr);
#undef expr
    return *this; 
  };

  //! cast to Scalar array
  inline operator Scalar*() { return m_values; };

  //! cast to const Scalar array
  inline operator const Scalar*() const { return m_values; };


   //----------------------------------------------------------- element access

   //! get i'th element read-write
  inline Scalar& operator[](int uiIndex) 
  {
    assert(uiIndex>=0 && uiIndex<DIM); return m_values[uiIndex]; 
  };

  //! get i'th element read-only
  inline const Scalar& operator[](int uiIndex) const 
  {
    assert(uiIndex>=0 && uiIndex<DIM); return m_values[uiIndex]; 
  };

   //! get i'th element read-write
  inline Scalar& operator[](unsigned int uiIndex) 
  {
    assert(uiIndex<DIM); return m_values[uiIndex]; 
  };

  //! get i'th element read-only
  inline const Scalar& operator[](unsigned int uiIndex) const 
  {
    assert(uiIndex<DIM); return m_values[uiIndex]; 
  };




  //---------------------------------------------------------------- comparison

  //! component-wise comparison
  inline bool operator==(const VectorType& other) const 
  {
#define expr(i) if(m_values[i]!=other.m_values[i]) return false;
    unroll(expr);
#undef expr
    return true; 
  };

  //! component-wise comparison
  inline bool operator!=(const VectorType& other) const 
  {
    return !(*this == other);
  };



  //---------------------------------------------------------- scalar operators

  //! component-wise self-multiplication with scalar
  inline VectorType& operator*=(const Scalar& s)
  {
#define expr(i) m_values[i] *= s; 
    unroll(expr);
#undef expr
    return *this; 
  };

  //! component-wise self-division by scalar
  inline VectorType& operator/=(const Scalar& s)
  {
#define expr(i) m_values[i] /= s; 
    unroll(expr);
#undef expr
    return *this; 
  };


  //! component-wise multiplication with scalar
  inline VectorType operator*(const Scalar& s) const 
  {
#if DIM==DIM
    return VectorType(*this) *= s;
#else
#define expr(i) m_values[i] * s
    return VectorType(unroll_csv(expr));
#undef expr
#endif
  };


  //! component-wise division by with scalar
  inline VectorType operator/(const Scalar& s) const 
  {
#if DIM==DIM
    return VectorType(*this) /= s;
#else
#define expr(i) m_values[i] / s
    return VectorType(unroll_csv(expr));
#undef expr
#endif
  };

  //---------------------------------------------------------- vector operators

  //! component-wise self-multiplication 
  inline VectorType& operator*=(const VectorType& other) 
  {
#define expr(i) m_values[i] *= other[i]; 
    unroll(expr);
#undef expr
    return *this; 
  };

  //! component-wise self-division
  inline VectorType& operator/=(const VectorType& other) 
  {
#define expr(i) m_values[i] /= other[i]; 
    unroll(expr);
#undef expr
    return *this; 
  };

  //! vector difference from this
  inline VectorType& operator-=(const VectorType& other) 
  {
#define expr(i) m_values[i] -= other[i]; 
    unroll(expr);
#undef expr
    return *this; 
  };

  //! vector self-addition
  inline VectorType& operator+=(const VectorType& other) 
  {
#define expr(i) m_values[i] += other[i]; 
    unroll(expr);
#undef expr
    return *this; 
  };
  

  //! component-wise vector multiplication
  inline VectorType operator*(const VectorType& _v) const 
  {
    return VectorType(*this) *= _v;
  };

  //! component-wise vector division
  inline VectorType operator/(const VectorType& _v) const 
  {
    return VectorType(*this) /= _v;
  };

  //! component-wise vector addition
  inline VectorType operator+(const VectorType& _v) const 
  {
    return VectorType(*this) += _v;
  };

  //! component-wise vector difference
  inline VectorType operator-(const VectorType& _v) const 
  {
    return VectorType(*this) -= _v;
  };


  //! unary minus
  inline VectorType operator-(void) const 
  {
    VectorType v;
#define expr(i) v.m_values[i] = -m_values[i];
    unroll(expr);
#undef expr
    return v; 
  };

  //! cross product: only defined for Vec3* as specialization
  inline CVectorT<Scalar,3> operator%(const CVectorT<Scalar,3>& other) const 
#if DIM==3
  {
    return 
      CVectorT<Scalar,3>(m_values[1]*other.m_values[2]-m_values[2]*other.m_values[1],
			m_values[2]*other.m_values[0]-m_values[0]*other.m_values[2],
			m_values[0]*other.m_values[1]-m_values[1]*other.m_values[0]);
  };
#else
  ;
#endif


  //! compute scalar product
  inline Scalar operator|(const VectorType& other) const 
  {
  Scalar p(0);
#define expr(i) p += m_values[i] * other.m_values[i]; 
  unroll(expr);
#undef expr
    return p; 
  };



  //------------------------------------------------------------ euclidean norm

  //! Euclidean norm 
  inline Scalar norm() const { return (Scalar)sqrt(sqrnorm()); };
  //! Euclidean length
  inline Scalar length() const { return norm(); };

  //! compute squared euclidean norm
  inline Scalar sqrnorm() const 
  {
    Scalar s(0);
#define expr(i) s += m_values[i] * m_values[i]; 
    unroll(expr);
#undef expr
    return s;
  };

  //! normalize vector, return normalized vector
  inline VectorType& normalize() 
  {
#ifdef NDEBUG
    operator*=(((Scalar)1.0)/norm());
#else
    Scalar n = norm();
    if (n != (Scalar)0.0)
      *this *= Scalar(1.0/n);
#endif
    return *this;
  };
  
  //------------------------------------------------------------ max, min, mean

  //! return the maximal component
  inline Scalar max() const 
  {
    Scalar m(m_values[0]);
    for(int i=1; i<DIM; ++i) if(m_values[i]>m) m=m_values[i];
    return m; 
  };
    
  //! return the minimal component
  inline Scalar min() const 
  {
    Scalar m(m_values[0]); 
    for(int i=1; i<DIM; ++i) if(m_values[i]<m) m=m_values[i];
    return m; 
  };
  
  //! return index of maximal component
  inline int argmax() const 
  {
    Scalar m(m_values[0]);
	int result = 0;
	for(int i=1; i<DIM; ++i) if(m_values[i]>m) { m=m_values[i]; result=i; };
    return result; 
  };


  //! return arithmetic mean
  inline Scalar mean() const 
  {
    Scalar m(m_values[0]); 
    for(int i=1; i<DIM; ++i) m+=m_values[i];
    return m/Scalar(DIM); 
  };


  //------------------------------------------------------------ misc functions


  //! store the same value in each component (e.g. to clear all entries)
  VectorType& vectorize(const Scalar& s) 
  {
#define expr(i) m_values[i] = s;
    unroll(expr);
#undef expr
    return *this;
  };


  //! store the same value in each component
  static VectorType vectorized(const Scalar& s) 
  {
    return VectorType().vectorize(s);
  };


  //! lexicographical comparison
  bool operator<(const VectorType& other) const 
  {
#define expr(i) if (m_values[i] != other.m_values[i]) \
                   return (m_values[i] < other.m_values[i]);
    unroll(expr);
#undef expr
    return false;
   };
};


//! read the space-separated components of a vector from a stream
template <typename Scalar, int DIM>
inline std::istream& 
operator>>(std::istream& is, CVectorT<Scalar,DIM>& vec)
{
#define expr(i) is >> vec[i];
  unroll(expr);
#undef expr
  return is;
}


//! output a vector by printing its space-separated compontens
template <typename Scalar, int DIM>
inline std::ostream& 
operator<<(std::ostream& os, const CVectorT<Scalar,DIM>& vec) 
{
  for(int i=0; i<DIM-1; ++i) os << vec[i] << " ";
  os << vec[DIM-1];

  return os;
}

#undef  unroll


#  ifndef DOXY_IGNORE_THIS

//! cross product for Vec3f
template<>
inline CVectorT<float,3>
CVectorT<float,3>::operator%(const CVectorT<float,3>& other) const 
{
   return 
     CVectorT<float,3>(m_values[1]*other.m_values[2]-m_values[2]*other.m_values[1],
		      m_values[2]*other.m_values[0]-m_values[0]*other.m_values[2],
		      m_values[0]*other.m_values[1]-m_values[1]*other.m_values[0]);
}
  

//! cross product for Vec3d
template<>
inline CVectorT<double,3>
CVectorT<double,3>::operator%(const CVectorT<double,3>& other) const
{
 return 
   CVectorT<double,3>(m_values[1]*other.m_values[2]-m_values[2]*other.m_values[1],
		     m_values[2]*other.m_values[0]-m_values[0]*other.m_values[2],
		     m_values[0]*other.m_values[1]-m_values[1]*other.m_values[0]);
}

#  endif // DOXY_IGNORE_THIS



//== GLOBAL FUNCTIONS =========================================================


//! scalar * vector
template<typename Scalar,int DIM>
inline CVectorT<Scalar,DIM> operator*(Scalar s, const CVectorT<Scalar,DIM>& _v) 
{
  return CVectorT<Scalar,DIM>(_v) *= s;
};


//! symmetric version of the dot product
template<typename Scalar, int DIM>
inline Scalar 
dot(const CVectorT<Scalar,DIM>& _v1, const CVectorT<Scalar,DIM>& _v2) 
{
  return (_v1 | _v2); 
};


//! symmetric version of the cross product
template<typename Scalar, int DIM>
inline CVectorT<Scalar,DIM> 
cross(const CVectorT<Scalar,DIM>& _v1, const CVectorT<Scalar,DIM>& _v2) 
{
  return (_v1 % _v2);
};


//== TYPEDEFS =================================================================

typedef CVectorT<float,3> Vec3f;
typedef CVectorT<double,3> Vec3d;

typedef CVectorT<float,4> Vec4f;
typedef CVectorT<double,4> Vec4d;

//=============================================================================
#endif //VECTORT_H
//=============================================================================
