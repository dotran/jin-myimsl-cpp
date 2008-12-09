/////////////////////////////////////////////////////////////////////////
// Program  : CMatrix.h
// Version 15.3

#ifndef __CMATRIX_H_
#define __CMATRIX_H_

#include "complex.h"
#include "rmatrix.h"

//###################### Declarations #######################//

class CMATRIX
{
	protected:
		COMPLEX *elem;

	public:
		int n,m;           //  m-number of rows
		int num;
		CMATRIX(void);     //  4x4 matrix by default
		CMATRIX(int,int);
		CMATRIX(int,int,char*);
		CMATRIX(const CMATRIX &);
		~CMATRIX(void);

		CMATRIX operator = (const CMATRIX &);
		CMATRIX operator = (char*);

		COMPLEX& operator () (int, int);
		COMPLEX& operator () (int);
		COMPLEX operator () (int, int) const;
		COMPLEX operator () (int) const;

		CMATRIX operator ! ();
		CMATRIX operator ! () const;
		CMATRIX operator - ();
		CMATRIX operator - () const;

		CMATRIX operator += (const CMATRIX &);
		CMATRIX operator += (const COMPLEX &);
		CMATRIX operator += (REAL);
		CMATRIX operator -= (const CMATRIX &);
		CMATRIX operator -= (const COMPLEX &);
		CMATRIX operator -= (REAL);
		CMATRIX operator *= (const CMATRIX &);
		CMATRIX operator *= (const COMPLEX &);
		CMATRIX operator *= (REAL);
		CMATRIX operator /= (const CMATRIX &);
		CMATRIX operator /= (const COMPLEX &);
		CMATRIX operator /= (REAL);

		void SwitchLines (int,int);
		void SwitchColumns (int,int);
		int SortMatrix (int);      //For internal purposes.

		friend ostream& operator << (ostream&, const CMATRIX &);
		friend istream& operator >> (istream&, CMATRIX&);
};

//////////////////// CVECTOR as Matrix ////////////////////

class CVECTOR : public CMATRIX
{
	public:
		CVECTOR (void);
		CVECTOR (int n);
		CVECTOR (int n, char* str);
		CVECTOR (const CVECTOR& a);
		~CVECTOR (void);

		CVECTOR operator = (const CMATRIX &);
		CVECTOR operator = (const CVECTOR &);
		CVECTOR operator = (char*);
};

//////////////////// Declarations of Functions ///////////////////

REAL operator += (REAL &, const CMATRIX &);
REAL operator -= (REAL &, const CMATRIX &);
REAL operator *= (REAL &, const CMATRIX &);
REAL operator /= (REAL &, const CMATRIX &);
COMPLEX operator += (COMPLEX &, const CMATRIX &);
COMPLEX operator -= (COMPLEX &, const CMATRIX &);
COMPLEX operator *= (COMPLEX &, const CMATRIX &);
COMPLEX operator /= (COMPLEX &, const CMATRIX &);

CMATRIX operator + (const CMATRIX &, const CMATRIX &);
CMATRIX operator + (const CMATRIX &, const COMPLEX &);
CMATRIX operator + (const COMPLEX &, const CMATRIX &);
CMATRIX operator + (const CMATRIX &, REAL);
CMATRIX operator + (REAL, const CMATRIX &);
CMATRIX operator - (const CMATRIX &, const CMATRIX &);
CMATRIX operator - (const CMATRIX &, const COMPLEX &);
CMATRIX operator - (const COMPLEX &, const CMATRIX &);
CMATRIX operator - (const CMATRIX &, REAL);
CMATRIX operator - (REAL, const CMATRIX &);
CMATRIX operator / (const CMATRIX &, const CMATRIX &);
CMATRIX operator / (const CMATRIX &, const COMPLEX &);
CMATRIX operator / (const COMPLEX &, const CMATRIX &);
CMATRIX operator / (const CMATRIX &, REAL);
CMATRIX operator / (REAL, const CMATRIX &);
CMATRIX operator * (const CMATRIX &, const CMATRIX &);
CMATRIX operator * (const CMATRIX &, const COMPLEX &);
CMATRIX operator * (const COMPLEX &, const CMATRIX &);
CMATRIX operator * (const CMATRIX &, REAL);
CMATRIX operator * (REAL, const CMATRIX &);

CMATRIX operator ^ (const CMATRIX &, int);
CMATRIX operator ^ (const CMATRIX &, const CMATRIX &);

int operator == (const CMATRIX &, const CMATRIX &);
int operator != (const CMATRIX &, const CMATRIX &);


////////////////////////////////////////

CVECTOR operator - (const CVECTOR &);
CVECTOR operator *= (const CVECTOR &, const CMATRIX &);

COMPLEX operator + (const CVECTOR &, const COMPLEX &);
COMPLEX operator + (const CVECTOR &, REAL);
COMPLEX operator + (const COMPLEX &, const CVECTOR & );
COMPLEX operator + (REAL, const CVECTOR &);
CVECTOR operator + (const CMATRIX &, const CVECTOR &);
CVECTOR operator + (const CVECTOR &, const CMATRIX &);
CVECTOR operator + (const CVECTOR &, const CVECTOR &);
COMPLEX operator - (const CVECTOR &, const COMPLEX &);
COMPLEX operator - (const CVECTOR &, REAL);
COMPLEX operator - (const COMPLEX &, const CVECTOR & );
COMPLEX operator - (REAL, const CVECTOR &);
CVECTOR operator - (const CVECTOR &, const CVECTOR &);
CVECTOR operator - (const CMATRIX &, const CVECTOR &);
CVECTOR operator - (const CVECTOR &, const CMATRIX &);
CVECTOR operator * (const CMATRIX &, const CVECTOR &);
CVECTOR operator * (const CVECTOR &, const COMPLEX &);
CVECTOR operator * (const CVECTOR &, REAL);
CVECTOR operator * (const COMPLEX &, const CVECTOR &);
CVECTOR operator * (REAL, const CVECTOR &);
CVECTOR operator * (const CVECTOR &, const CVECTOR &);
COMPLEX operator / (const COMPLEX &, const CVECTOR & );
COMPLEX operator / (REAL, const CVECTOR &);
CVECTOR operator / (const CVECTOR &, const CMATRIX &);
CVECTOR operator / (const CVECTOR &, const COMPLEX &);
CVECTOR operator / (const CVECTOR &, REAL);


/////////////////////////////////////////////////////////////////////////
// Declarations of Functions
void ms_VOut(const CVECTOR &v);
void ms_MOut(CMATRIX a);
void ms_Zeros(CMATRIX &a);
void ms_Ones(CMATRIX &a);
void ms_Eye(CMATRIX &a);
CMATRIX ms_Inv(const CMATRIX &);
COMPLEX ms_Det(const CMATRIX &);
CVECTOR ms_Eigen(const RMATRIX &a);
CVECTOR ms_Eigen(const CMATRIX &f);
CMATRIX ms_Hermit(const CMATRIX &);
COMPLEX ms_Trace(const CMATRIX &);
CMATRIX ms_Trans(const CMATRIX &);
CMATRIX ms_Minor(const CMATRIX &,int,int);
REAL ms_Norm1(const CVECTOR &x);
REAL ms_Norm1(const CMATRIX &a);
REAL ms_Norm2(const CVECTOR &x);
REAL ms_Norm2(const CMATRIX &a);
REAL ms_Norm8(const CVECTOR &x);
REAL ms_Norm8(const CMATRIX &a);
void ms_Sort(CVECTOR &b);
COMPLEX ms_Sum(const CVECTOR &v);
CVECTOR ms_Roots(const RVECTOR &a);
RVECTOR ms_Poly(CVECTOR &p);
CVECTOR ms_Fft(const RVECTOR &data, REAL fs=0);

//REAL Abs (const CVECTOR &);
void Array2Vector(REAL a[], CVECTOR &b);
void Vector2Array(const CVECTOR &a, REAL b[]);

#endif // __CMATRIX_H_
