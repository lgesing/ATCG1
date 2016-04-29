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
//  CLASS CColor3T
//
//=============================================================================

#ifndef COLOR3T_H
#define COLOR3T_H

//== INCLUDES =================================================================


//== CLASS DEFINITION =========================================================

/*!
	Simple 3-component-color
	
	\author Gero Mueller
*/
template <typename Scalar>
class CColor3T
{
//-------------------------------------------------------------- typedefs
public:
	//!Pack 3-component-color into integer
	typedef unsigned int Packed;
	//!abbreviation	
	typedef CColor3T<Scalar>  ColorType;

//-------------------------------------------------------------- private data
private:	
	Scalar m_rgb[3];

//-------------------------------------------------------------- private methods
private:

public:
//-------------------------------------------------------------- constructors
	//! standard constructor
	inline CColor3T() {};
	//! copy constructor
	template<typename otherScalarType>
	explicit inline CColor3T(const CColor3T<otherScalarType>& other) 
	{ 
		operator=(other); 
	};    
	//!initializing constructor version 0
    inline CColor3T( const Scalar red, 
					 const Scalar green, 
			         const Scalar blue )
	{
		m_rgb[0] = red; m_rgb[1] = green; m_rgb[2] = blue;
	};

	//!initializing constructor version 1
    inline CColor3T( const Scalar gray )
	{
		m_rgb[0] = m_rgb[1] = m_rgb[2] = gray;
	};
	//! destructor	
	~CColor3T() {};

//--------------------------------------------------------------------- casts

    //! cast from color with a different scalar type
	template<typename otherScalarType>
	inline ColorType& operator=(const CColor3T<otherScalarType>& other) 
	{
		m_rgb[0] = (Scalar)other.m_rgb[0];
		m_rgb[1] = (Scalar)other.m_rgb[1];
		m_rgb[2] = (Scalar)other.m_rgb[2];
	    return *this; 
	};

	//! cast to Scalar array
	inline operator Scalar*() { return m_rgb; };

	//! cast to const Scalar array
	inline operator const Scalar*() const { return m_rgb; };

//----------------------------------------------------------- element access
	//!Set RGB-components
	inline void SetRgb( const Scalar red, 
		                const Scalar green, 
				        const Scalar blue )
	{
		m_rgb[0] = red; m_rgb[1] = green; m_rgb[2] = blue;
	};
	//!Set components from packed color
	inline void SetRgbPacked( Packed packedColor )
	{
		m_rgb[0] = Scalar( ((packedColor >> 16) & 0xff) / 255. ); 
		m_rgb[1] = Scalar( ((packedColor >>  8) & 0xff) / 255. ); 
		m_rgb[2] = Scalar( ((packedColor      ) & 0xff) / 255. ); 
	};
	
	//!Pack color in integer
	inline Packed GetPacked() const
	{
		Packed ret = int(m_rgb[0]*255) & 0xff;
		ret<<=8;
		ret|= int(m_rgb[1]*255) & 0xff;
		ret<<=8;
		ret|= int(m_rgb[2]*255) & 0xff;
		return ret;
	};

	//!Get red component
	inline Scalar red()   const { return m_rgb[0]; };
	//!Get green component
	inline Scalar green() const { return m_rgb[1]; };
	//!Get blue component
	inline Scalar blue()  const { return m_rgb[2]; };

	//!Get graylevel value
	inline Scalar gray() const { return Scalar( (red()*11+green()*16+blue()*5)/32. ); };

//----------------------------------------------------------- operators	
	//!color equals other
    inline bool  operator==(const ColorType& other ) const
	{
		return m_rgb[0]==other.m_rgb[0] && m_rgb[1]==other.m_rgb[1] && m_rgb[2]==other.m_rgb[2];
	};
	//!color not equals other
    inline bool    operator!=(const ColorType& other ) const
	{
		return !( (*this) == other );
	};

	//!add color to self
	inline ColorType& operator+=(const ColorType& other) 
	{
		m_rgb[0] += other.m_rgb[0];
		m_rgb[1] += other.m_rgb[1];
		m_rgb[2] += other.m_rgb[2];
		return (*this);
	};

	//!self-multiply with color
	inline ColorType& operator*=(const ColorType& other) 
	{
		m_rgb[0] *= other.m_rgb[0];
		m_rgb[1] *= other.m_rgb[1];
		m_rgb[2] *= other.m_rgb[2];
		return (*this);
	};

	//!self-multiply with scalar
	inline ColorType& operator*=(const Scalar val)
	{
	    m_rgb[0] *= val;
	    m_rgb[1] *= val;
	    m_rgb[2] *= val;
		return *this;
	};

	//!add colors
	inline ColorType operator+(const ColorType& other) const
	{
		return ColorType(*this)+=other;
	};

	//!multiply colors
	inline ColorType operator*(const ColorType& other) const
	{
		return ColorType(*this)*=other;
	};

	//!Multiply with scalar
    inline ColorType operator*( const Scalar val ) const
	{
		return ColorType(*this) *= val ;
	};
//----------------------------------------------------------- functionality
	//!Clamp to range
	inline void Clamp( Scalar lb, Scalar hb )
	{
		if (m_rgb[0]<lb) m_rgb[0] = lb;
		if (m_rgb[1]<lb) m_rgb[1] = lb;
		if (m_rgb[2]<lb) m_rgb[2] = lb;
		if (m_rgb[0]>hb) m_rgb[0] = hb;
		if (m_rgb[1]>hb) m_rgb[1] = hb;
		if (m_rgb[2]>hb) m_rgb[2] = hb;
	};

	//!Get energy
	inline Scalar GetEnergy() const
	{
		return m_rgb[0]*m_rgb[0]+m_rgb[1]*m_rgb[1]+m_rgb[2]*m_rgb[2];
	};
};

//== TYPEDEFS =================================================================

/*! float color */
typedef CColor3T<float> Color3f;

/*! double color */
typedef CColor3T<double> Color3d;

//=============================================================================
#endif // COLOR3T_H
//=============================================================================
