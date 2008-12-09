/////////////////////////////////////////////////////////////////////////
// Program  : Complex.h
// Version 15.3

#ifndef __COMPLEX_H_
#define __COMPLEX_H_

#include <iostream.h>
#include <math.h>
#include "realtype.h"

class COMPLEX
{
	public:
		REAL Re,Im;

		COMPLEX (REAL a=0, REAL b=0): Re(a),Im(b) {}
		~COMPLEX () {}
		REAL GetRe ()               { return Re; }
		REAL GetIm ()               { return Im; }
		void SetRe (REAL a)         { Re = a; }
		void SetIm (REAL a)         { Im = a; }
		void Set (REAL a, REAL b) { Re = a; Im = b; }
		void SetPolar (REAL, REAL);
		void SetAbs (REAL);
		void SetArg (REAL);
		COMPLEX operator !  () const;
		COMPLEX operator !  ();
		COMPLEX operator +  () const;
		COMPLEX operator +  ();
		COMPLEX operator -  () const;
		COMPLEX operator -  ();
		COMPLEX operator += (const COMPLEX &);
		COMPLEX operator += (REAL);
		COMPLEX operator -= (const COMPLEX &);
		COMPLEX operator -= (REAL);
		COMPLEX operator *= (const COMPLEX &);
		COMPLEX operator *= (REAL);
		COMPLEX operator /= (const COMPLEX &);
		COMPLEX operator /= (REAL);

		friend ostream& operator << (ostream&, const COMPLEX &);
		friend istream& operator >> (istream&, COMPLEX &);
};

	const COMPLEX ImUnit(0,1);

	void Zero (COMPLEX &);
	REAL  real (const COMPLEX &);
	REAL  imag (const COMPLEX &);
	COMPLEX conj (const COMPLEX &);
	COMPLEX Polar (REAL, REAL);
	REAL  Arg  (const COMPLEX &);
	REAL  phase(const COMPLEX &);
	REAL  abs  (const COMPLEX &);
  void Solve2 (COMPLEX*, const COMPLEX&, const COMPLEX&);
  void Solve3 (COMPLEX*, const COMPLEX&, const COMPLEX&, const COMPLEX&);
  void Solve4 (COMPLEX*, const COMPLEX&, const COMPLEX&, const COMPLEX&, const COMPLEX&);
  COMPLEX Solve2 (const COMPLEX&, const COMPLEX&, int RootNumber=0);
  COMPLEX Solve3 (const COMPLEX&, const COMPLEX&, const COMPLEX&, int RootNumber=0);
  COMPLEX Solve4 (const COMPLEX&, const COMPLEX&, const COMPLEX&, const COMPLEX&, int RootNumber=0);

  COMPLEX Gamma(COMPLEX);
  COMPLEX Beta(COMPLEX,COMPLEX);
  COMPLEX BesselJ(COMPLEX, int);
  COMPLEX BesselJ(COMPLEX, COMPLEX);
  COMPLEX BesselY(COMPLEX, int);
  REAL  Besselj(REAL, int);  //it use COMPLEX inside.

	COMPLEX sqr(const COMPLEX &);
	COMPLEX sqrt(const COMPLEX &, int=0);
	COMPLEX pow(const COMPLEX &, int);
	COMPLEX pow(const COMPLEX &, REAL);
	COMPLEX pow(const COMPLEX &, const COMPLEX &);
	COMPLEX root(const COMPLEX &, int, int=0);
	COMPLEX exp(const COMPLEX &);
	COMPLEX log(const COMPLEX &);
	COMPLEX sin(const COMPLEX &);
	COMPLEX cos(const COMPLEX &);
	COMPLEX tan(const COMPLEX &);
	COMPLEX cot(const COMPLEX &);
	COMPLEX sec(const COMPLEX &);
	COMPLEX csc(const COMPLEX &);
	COMPLEX sinh(const COMPLEX &);
	COMPLEX cosh(const COMPLEX &);
	COMPLEX tanh(const COMPLEX &);
	COMPLEX coth(const COMPLEX &);
	COMPLEX sech(const COMPLEX &);
	COMPLEX csch(const COMPLEX &);
	COMPLEX asin(const COMPLEX &, int=0);
	COMPLEX acos(const COMPLEX &, int=0);
	COMPLEX atan(const COMPLEX &);
	COMPLEX acot(const COMPLEX &);
	COMPLEX asec(const COMPLEX &, int=0);
	COMPLEX acsc(const COMPLEX &, int=0);
	COMPLEX asinh(const COMPLEX &, int=0);
	COMPLEX acosh(const COMPLEX &, int=0);
	COMPLEX atanh(const COMPLEX &);
	COMPLEX acoth(const COMPLEX &);
	COMPLEX asech(const COMPLEX &, int=0);
	COMPLEX acsch(const COMPLEX &, int=0);

	COMPLEX operator ^  (const COMPLEX &, int);
	COMPLEX operator ^  (const COMPLEX &, REAL);
	COMPLEX operator ^  (const COMPLEX &, const COMPLEX &);

	REAL operator += (REAL&, const COMPLEX &);
	REAL operator -= (REAL&, const COMPLEX &);
	REAL operator *= (REAL&, const COMPLEX &);
	REAL operator /= (REAL&, const COMPLEX &);

	COMPLEX operator +  (const COMPLEX &, const COMPLEX &);
	COMPLEX operator +  (const COMPLEX &, REAL);
	COMPLEX operator +  (REAL, const COMPLEX &);
	COMPLEX operator -  (const COMPLEX &, const COMPLEX &);
	COMPLEX operator -  (const COMPLEX &, REAL);
	COMPLEX operator -  (REAL, const COMPLEX &);
	COMPLEX operator *  (const COMPLEX &, const COMPLEX &);
	COMPLEX operator *  (const COMPLEX &, REAL);
	COMPLEX operator *  (REAL, const COMPLEX &);
	COMPLEX operator /  (const COMPLEX &, const COMPLEX &);
	COMPLEX operator /  (const COMPLEX &, REAL);
	COMPLEX operator /  (REAL, const COMPLEX &);

	int operator == (const COMPLEX &, REAL);
	int operator == (REAL, const COMPLEX &);
	int operator == (const COMPLEX &, const COMPLEX &);
	int operator != (const COMPLEX &, REAL);
	int operator != (REAL, const COMPLEX &);
	int operator != (const COMPLEX &, const COMPLEX &);
	int operator >= (const COMPLEX &, REAL);
	int operator >= (REAL, const COMPLEX &);
	int operator >= (const COMPLEX &, const COMPLEX &);
	int operator <= (const COMPLEX &, REAL);
	int operator <= (REAL, const COMPLEX &);
	int operator <= (const COMPLEX &, const COMPLEX &);
	int operator > (const COMPLEX &, REAL);
	int operator > (REAL, const COMPLEX &);
	int operator > (const COMPLEX &, const COMPLEX &);
	int operator < (const COMPLEX &, REAL);
	int operator < (REAL, const COMPLEX &);
	int operator < (const COMPLEX &, const COMPLEX &);

////////////////////////////////////////////////
// Inline Functions

inline COMPLEX COMPLEX::operator + () const
{
	return *this;
}

inline COMPLEX COMPLEX::operator + ()
{
	return *this;
}

inline COMPLEX COMPLEX::operator - () const
{
	return COMPLEX (-Re, -Im);
}

inline COMPLEX COMPLEX::operator - ()
{
	return COMPLEX (-Re, -Im);
}

inline COMPLEX COMPLEX::operator ! () const  //  complex conjugate  //
{
	return COMPLEX (Re, -Im);
}

inline COMPLEX COMPLEX::operator ! ()       //  complex conjugate  //
{
	return COMPLEX (Re, -Im);
}

inline COMPLEX COMPLEX::operator += (const COMPLEX &a)
{
	Re+=a.Re;
	Im+=a.Im;
	return *this;
}

inline COMPLEX COMPLEX::operator += (REAL a)
{
	Re+=a;
	return *this;
}

inline COMPLEX COMPLEX::operator -= (const COMPLEX &a)
{
	Re-=a.Re;
	Im-=a.Im;
	return *this;
}

inline COMPLEX COMPLEX::operator -= (REAL a)
{
	Re-=a;
	return *this;
}

inline COMPLEX COMPLEX::operator *= (REAL a)
{
	Re*=a;
	Im*=a;
	return *this;
}

inline COMPLEX COMPLEX::operator /= (REAL a)
{
	Re/=a;
	Im/=a;
	return *this;
}

inline COMPLEX operator + (const COMPLEX &a, const COMPLEX &b)
{
	return COMPLEX (a.Re+b.Re, a.Im+b.Im);
}

inline COMPLEX operator + (const COMPLEX &a, REAL b)
{
	return COMPLEX (a.Re+b, a.Im);
}

inline COMPLEX operator + (REAL b, const COMPLEX &a)
{
	return COMPLEX (a.Re+b, a.Im);
}

inline COMPLEX operator - (const COMPLEX &a, const COMPLEX &b)
{
	return COMPLEX (a.Re-b.Re, a.Im-b.Im);
}

inline COMPLEX operator - (const COMPLEX &a, REAL b)
{
	return COMPLEX (a.Re-b, a.Im);
}

inline COMPLEX operator - (REAL b, const COMPLEX &a)
{
	return COMPLEX (b-a.Re, -a.Im);
}

inline COMPLEX operator * (const COMPLEX &a, REAL b)
{
	return COMPLEX (a.Re*b, a.Im*b);
}

inline COMPLEX operator * (REAL b, const COMPLEX &a)
{
	return COMPLEX (a.Re*b, a.Im*b);
}

inline COMPLEX operator / (const COMPLEX &a, REAL b)
{
	return COMPLEX (a.Re/b, a.Im/b);
}

inline COMPLEX operator / (REAL b, const COMPLEX &a)
{
	return (COMPLEX (b,0)) / a;
}

inline int operator == (const COMPLEX &a, REAL b)
{
	return abs(a-b) < Precision;
}

inline int operator == (REAL b, const COMPLEX &a)
{
	return abs(a-b) < Precision;
}

inline int operator == (const COMPLEX &a, const COMPLEX &b)
{
	return abs(a-b) < Precision;
}

inline int operator != (const COMPLEX &a, REAL b)
{
	return abs(a-b) > Precision;
}

inline int operator != (REAL b, const COMPLEX &a)
{
	return abs(a-b) > Precision;
}

inline int operator != (const COMPLEX &a, const COMPLEX &b)
{
	return abs(a-b) > Precision;
}

inline int operator >= (const COMPLEX &a, REAL b)
{
	return abs(a) >= fabs(b);
}

inline int operator >= (REAL b, const COMPLEX &a)
{
	return fabs(b) >= abs(a);
}

inline int operator >= (const COMPLEX &a, const COMPLEX &b)
{
	return abs(a) >= abs(b);
}

inline int operator <= (const COMPLEX &a, REAL b)
{
	return abs(a) <= fabs(b);
}

inline int operator <= (REAL b, const COMPLEX &a)
{
	return fabs(b) <= abs(a);
}

inline int operator <= (const COMPLEX &a, const COMPLEX &b)
{
	return abs(a) <= abs(b);
}

inline int operator > (const COMPLEX &a, REAL b)
{
	return abs(a) > fabs(b);
}

inline int operator > (REAL b, const COMPLEX &a)
{
	return fabs(b) > abs(a);
}

inline int operator > (const COMPLEX &a, const COMPLEX &b)
{
	return abs(a) > abs(b);
}

inline int operator < (const COMPLEX &a, REAL b)
{
	return abs(a) < fabs(b);
}

inline int operator < (REAL b, const COMPLEX &a)
{
	return fabs(b) < abs(a);
}

inline int operator < (const COMPLEX &a, const COMPLEX &b)
{
	return abs(a) < abs(b);
}

inline void Zero (COMPLEX &a) { a.Re=a.Im=0; }
inline REAL  real (const COMPLEX &z) { return z.Re; }
inline REAL  imag (const COMPLEX &z) { return z.Im; }
inline COMPLEX conj (const COMPLEX &z) { return !z; }
inline COMPLEX sqr (const COMPLEX &a) { return a*a; }

///////////////////////////////////////////////////////////////////////
//
void ms_COut(const COMPLEX &v);

#endif  // __COMPLEX_H_
