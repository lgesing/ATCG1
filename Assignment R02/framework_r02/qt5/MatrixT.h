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
//  CLASS CMatrixT
//
//=============================================================================

#ifndef MATRIXT_H
#define MATRIXT_H


//== INCLUDES =================================================================

#include "VectorT.h"


//== CLASS DEFINITION =========================================================

#define unrollsqr(expr)      for (int i=0; i<DIM*DIM; ++i) expr(i)

template <typename Scalar, int DIM>
class CMatrixT;


template<typename Scalar,int DIM>
typename CMatrixT<Scalar,DIM>::VectorType operator*(const typename CMatrixT<Scalar,DIM>::VectorType& v,
						    const CMatrixT<Scalar,DIM>& m); 



/*! 
	A matrix is an square 2D-array of <DIM>*<DIM> values of type <Scalar>.
*/
template <typename Scalar, int DIM>
class CMatrixT
{
//---------------------------------------------------------------- typedefs
public:

  //! type of this matrix
  typedef CMatrixT<Scalar,DIM>  MatrixType;

  //! type of vector
  typedef CVectorT<Scalar,DIM>  VectorType;

  //! returns dimension of the vector
  static inline int dim() { return DIM; };

//---------------------------------------------------------------- protected data
protected:
	Scalar m_values[DIM*DIM];

//-------------------------------------------------------------- private methods
public:
	static inline unsigned int Index(unsigned int uiRow, unsigned int uiCol)
	{
#define STORAGE_ROW_WISE
#ifdef  STORAGE_ROW_WISE
		return uiRow*DIM+uiCol;
#else
		return uiCol*DIM+uiRow;
#endif
	};
	static inline void IncIndexRow(unsigned int& ruiIndex)
	{
#ifdef  STORAGE_ROW_WISE
		ruiIndex+=DIM;
#else
		ruiIndex+=1;
#endif
	};
	static inline void IncIndexCol(unsigned int& ruiIndex)
	{
#ifdef  STORAGE_ROW_WISE
		ruiIndex+=1;
#else
		ruiIndex+=DIM;
#endif
	};


//-------------------------------------------------------------- constructors
public:

  //! default constructor creates uninitialized values.
  inline CMatrixT() {};

  //! constructor for uniform initialization
  explicit inline CMatrixT(const Scalar& v) 
  {
#define expr(i) (m_values[i]=v);
    unrollsqr(expr);
#undef expr
  };

  //! construct from a value array (explicit)
  explicit inline CMatrixT(const Scalar values[DIM*DIM]) 
  {
	memcpy(m_values, values, DIM*DIM*sizeof(Scalar)); 
  };

  //! copy & cast constructor (explicit)
  template<typename otherScalarType>
  explicit inline CMatrixT(const CMatrixT<otherScalarType,DIM>& other) 
  { 
    operator=(other); 
  };

//--------------------------------------------------------------------- casts

  //! cast from matrix with a different scalar type
  template<typename otherScalarType>
  inline MatrixType& operator=(const CMatrixT<otherScalarType,DIM>& other) 
  {
#define expr(i)  m_values[i] = (Scalar)other.m_values[i];
    unrollsqr(expr);
#undef expr
    return *this; 
  };

  //! cast to Scalar array
  inline operator Scalar*() { return m_values; };

  //! cast to const Scalar array
  inline operator const Scalar*() const { return m_values; };


//----------------------------------------------------------- element access

   //! get (row,col)-component read-write
   inline Scalar& operator() (unsigned int uiRow, unsigned int uiCol) 
   {
	  assert(uiRow<DIM && uiCol<DIM); return m_values[Index(uiRow, uiCol)]; 
   };

  //! get (row,col)-component read-only
  inline const Scalar& operator() (unsigned int uiRow, unsigned int uiCol) const 
  {
	  assert(uiRow<DIM && uiCol<DIM); return m_values[Index(uiRow, uiCol)]; 
  };

  //! set i-th row
  void  SetRow(unsigned int uiRow, const VectorType& crRow)
  {
	  for (unsigned int i=0, j=Index(uiRow,0); i<DIM; ++i, IncIndexCol(j) ) m_values[j]=crRow[i];
  };
   
  //!get i-th row
  VectorType GetRow(unsigned int uiRow) const
  {
	  VectorType row;
	  for (unsigned int i=0, j=Index(uiRow,0); i<DIM; ++i, IncIndexCol(j) ) row[i] = m_values[j];
	  return row;
  };
  //!set i-th col
  void SetCol(unsigned int uiCol, const VectorType& crCol)
  {
	  for (unsigned int i=0, j=Index(0,uiCol); i<DIM; ++i, IncIndexRow(j) ) m_values[j]=crCol[i];
  };

//!get i-th col
  VectorType GetCol(unsigned int uiCol)
  {
	  VectorType col;
	  for (unsigned int i=0, j=Index(0,uiCol); i<DIM; ++i, IncIndexRow(j) ) col[i] = m_values[j];
	  return col;
  };

//---------------------------------------------------------------- comparison

  //! component-wise comparison
  inline bool operator==(const MatrixType& other) const 
  {
#define expr(i) if(m_values[i]!=other.m_values[i]) return false;
    unrollsqr(expr);
#undef expr
    return true; 
  };

  //! component-wise comparison
  inline bool operator!=(const MatrixType& other) const 
  {
    return !(*this == other);
  };


//---------------------------------------------------------- scalar operators

  //! component-wise self-multiplication with scalar
  inline MatrixType& operator*=(const Scalar& s) 
  {
#define expr(i) m_values[i] *= s; 
    unrollsqr(expr);
#undef expr
    return *this; 
  };

  //! component-wise self-division by scalar
  inline MatrixType& operator/=(const Scalar& s) 
  {
#define expr(i) m_values[i] /= s; 
    unrollsqr(expr);
#undef expr
    return *this; 
  };


  //! component-wise multiplication with scalar
  inline MatrixType operator*(const Scalar& s) const 
  {
    return MatrixType(*this) *= s;
  };

  //! component-wise division by with scalar
  inline MatrixType operator/(const Scalar& s) const 
  {
    return MatrixType(*this) /= s;
  };

//---------------------------------------------------------- matrix operators

  //! matrix self-product 
  inline MatrixType& operator*=(const MatrixType& other) 
  {
    (*this) = (*this) * other;
	return (*this);
  };

  //! matrix product 
  inline MatrixType operator*(const MatrixType& other) 
  {
	MatrixType result;
    for (unsigned int ui_row = 0; ui_row < DIM; ++ui_row)
    {
        for (unsigned int ui_col = 0; ui_col < DIM; ++ui_col)
        {
			unsigned int ui_index = Index(ui_row, ui_col);
            result.m_values[ui_index] = (Scalar)0.0;
			for (unsigned int ui_mid = 0; ui_mid < DIM; ++ui_mid)
            {
                result.m_values[ui_index] +=
                    this->m_values[Index(ui_row,ui_mid)]*other.m_values[Index(ui_mid,ui_col)];
            }
        }
    }
    return result;   
  };

  //! vector difference from this
  inline MatrixType& operator-=(const MatrixType& other) 
  {
#define expr(i) m_values[i] -= other.m_values[i]; 
    unrollsqr(expr);
#undef expr
    return *this; 
  };

  //! matrix self-addition
  inline MatrixType& operator+=(const MatrixType& other) 
  {
#define expr(i) m_values[i] += other.m_values[i]; 
    unrollsqr(expr);
#undef expr
    return *this; 
  };
  

  //! matrix product
  inline MatrixType operator*(const MatrixType& other) const 
  {
    return MatrixType(*this) *= other;
  };

  //! matrix addition
  inline MatrixType operator+(const MatrixType& other) const 
  {
    return MatrixType(*this) += other;
  };

  //! matrix difference
  inline MatrixType operator-(const MatrixType& other) const 
  {
    return MatrixType(*this) -= other;
  };

  //! unary minus
  inline MatrixType operator-(void) const 
  {
    MatrixType result;
#define expr(i) result.m_values[i] = -m_values[i];
    unrollsqr(expr);
#undef expr
    return result; 
  };

//------------------------------------------------------------ matrix-vector operators
  //matrix-vector multiplication
  inline VectorType operator*(const VectorType& vec) const
  {
	  VectorType result;
	  for (unsigned int ui_row = 0; ui_row < DIM; ++ui_row)
      {
		 result[ui_row] = 0;
		 unsigned int ui_index = Index(ui_row, 0);
		 for (unsigned int ui_col = 0; ui_col < DIM; ++ui_col, IncIndexCol(ui_index) )
         {
		     result[ui_row]+=this->m_values[ui_index] * vec[ui_col];
		 }
	  }
	  return result;
  };

//------------------------------------------------------------ norm

  //! compute frobenius norm 
  inline Scalar NormFrobenius() const { return (Scalar)sqrt(SumOfSquares()); };

  //! compute sum of squares
  inline Scalar SumOfSquares() const 
  {
    Scalar s(0);
#define expr(i) s += m_values[i] * m_values[i]; 
    unrollsqr(expr);
#undef expr
    return s;
  };
  
//------------------------------------------------------------ max, min, mean

  //! return the maximal component
  inline Scalar Max() const 
  {
    Scalar m(m_values[0]);
    for(int i=1; i<DIM*DIM; ++i) if(m_values[i]>m) m=m_values[i];
    return m; 
  };
    
  //! return the minimal component
  inline Scalar Min() const 
  {
    Scalar m(m_values[0]); 
    for(int i=1; i<DIM*DIM; ++i) if(m_values[i]<m) m=m_values[i];
    return m; 
  };
    
  //! return arithmetic mean
  inline Scalar Mean() const 
  {
    Scalar m(m_values[0]); 
    for(int i=1; i<DIM*DIM; ++i) m+=m_values[i];
    return m/Scalar(DIM); 
  };
  
//------------------------------------------------------------ misc functions
  //!return transpose
  inline MatrixType Transpose() const
  {
	  MatrixType result;
	  for (unsigned int ui_row = 0; ui_row < DIM; ++ui_row)
      {
		 for (unsigned int ui_col = 0; ui_col < DIM; ++ui_col)
         {
			 result.m_values[Index(ui_row, ui_col)] = this->m_values[Index(ui_col, ui_row)];
		 }
	  }	  
	  return result;
  };

  //!zero all elements
  inline MatrixType& MakeZero()
  {
#define expr(i) m_values[i]=0;
    unrollsqr(expr);
#undef expr
	return *this;
  };

  //!Make identity
  inline MatrixType& MakeIdentity()
  {
    MakeZero();
    for(unsigned int ui=0; ui<DIM*DIM; IncIndexRow(ui)) m_values[ui++]=1;
	return *this;
  };

  //! component-wise apply function object with Scalar operator()(Scalar).
  template<typename Functor>
  inline MatrixType Apply(const Functor& func) const 
  {
    MatrixType result;
#define expr(i) result[i] = func(m_values[i]);
    unrollsqr(expr);
#undef expr
    return result; 
  };

//------------------------------------------------------------ friend functions

//  friend CVectorT<Scalar,DIM> operator* <Scalar,Dim> (const typename CMatrixT<Scalar,DIM>::VectorType& v, const CMatrixT<Scalar,DIM>& m);

};


//== GLOBAL FUNCTIONS =========================================================

//! read the space-separated components of a matrix from a stream
template <typename Scalar, int DIM>
inline std::istream& 
operator>>(std::istream& is, CMatrixT<Scalar,DIM>& m)
{
	typename CMatrixT<Scalar,DIM>::VectorType row;
	for (int i=0; i<DIM; ++i)
	{
		is >> row;
		m.SetRow(i, row );
	}
    return is;
}


//! output a matrix by printing its space-separated compontens
template <typename Scalar, int DIM>
inline std::ostream& 
operator<<(std::ostream& os, const CMatrixT<Scalar,DIM>& m) 
{
	for (unsigned int i=0; i<DIM; ++i)
	{
		os << m.GetRow(i) << std::endl;
	}
    return os;
};

//! scalar * matrix
template<typename Scalar,int DIM>
inline CMatrixT<Scalar,DIM> operator*(Scalar s, const CMatrixT<Scalar,DIM>& m) 
{
  return CMatrixT<Scalar,DIM>(m) *= s;
};

  
//! vector * matrix
template<typename Scalar,int DIM>
inline typename CMatrixT<Scalar,DIM>::VectorType operator*(const typename CMatrixT<Scalar,DIM>::VectorType& v,
							   const CMatrixT<Scalar,DIM>& m) 
{
  typename CMatrixT<Scalar,DIM>::VectorType result;
  const Scalar* values = (const Scalar*)m;
  for (unsigned int ui_col = 0; ui_col < DIM; ++ui_col)
    {
      result[ui_col] = 0;
      unsigned int ui_index = CMatrixT<Scalar,DIM>::Index(0, ui_col);
      for (unsigned int ui_row = 0; ui_row < DIM; ++ui_row, CMatrixT<Scalar,DIM>::IncIndexRow(ui_index) )
        {
	  result[ui_col]+=values[ui_index] * v[ui_row];
	}
    }
  return result;
};

//=============================================================================
#endif // MATRIXT_H
//=============================================================================
