/////////////////////////////////////////////////////////////////////////
// Program  : RMatrix.h
// Version 15.3

#ifndef __RMATRIX_H_
#define __RMATRIX_H_

#include <strstrea.h>
#include <iostream.h>
#include "realtype.h"

#ifndef dimension_of_space
#define dimension_of_space 4
#endif

/////////////////////////////////////////////////////////////////////////
// Declaration of class RMATRIX
class RMATRIX
{
	protected:
		REAL *elem;

	public:
		int n,m;           // n rows, m columns
		int num;           // num= nxm
		RMATRIX(void);     // 4x4 default matrix
		RMATRIX(int,int);
		RMATRIX(int,int,char*);
		RMATRIX(const RMATRIX &);
		~RMATRIX(void);

		RMATRIX operator = (const RMATRIX &);
		RMATRIX operator = (char*);

		REAL& operator () (int, int);
		REAL& operator () (int);
		REAL operator () (int, int) const;
		REAL operator () (int) const;

	  RMATRIX operator - ();
		RMATRIX operator - () const;

		RMATRIX operator += (const RMATRIX &);
		RMATRIX operator += (REAL);
		RMATRIX operator -= (const RMATRIX &);
		RMATRIX operator -= (REAL);
		RMATRIX operator *= (const RMATRIX &);
		RMATRIX operator *= (REAL);
		RMATRIX operator /= (const RMATRIX &);
		RMATRIX operator /= (REAL);

		void SwapRow(int,int);
		void SwapCol(int,int);

		friend ostream& operator << (ostream&, const RMATRIX &);
		friend istream& operator >> (istream&, RMATRIX&);
};

/////////////////////////////////////////////////////////////////////////
// Declaration of class RVECTOR
class RVECTOR : public RMATRIX
{
	public:
		RVECTOR (void);
		RVECTOR (int n);
		RVECTOR (int n, char* str);
		RVECTOR (const RVECTOR& a);
		~RVECTOR (void);

		RVECTOR operator = (const RMATRIX &);
		RVECTOR operator = (const RVECTOR &);
		RVECTOR operator = (char*);
};

/////////////////////////////////////////////////////////////////////////
// Declaration of operators of class RMATRIX and RVECTOR
REAL operator += (REAL &, const RMATRIX &);
REAL operator -= (REAL &, const RMATRIX &);
REAL operator *= (REAL &, const RMATRIX &);
REAL operator /= (REAL &, const RMATRIX &);

RMATRIX operator + (const RMATRIX &, const RMATRIX &);
RMATRIX operator + (const RMATRIX &, REAL);
RMATRIX operator + (REAL, const RMATRIX &);
RMATRIX operator - (const RMATRIX &, const RMATRIX &);
RMATRIX operator - (const RMATRIX &, REAL);
RMATRIX operator - (REAL, const RMATRIX &);
RMATRIX operator / (const RMATRIX &, const RMATRIX &);
RMATRIX operator / (const RMATRIX &, REAL);
RMATRIX operator / (REAL, const RMATRIX &);
RMATRIX operator * (const RMATRIX &, const RMATRIX &);
RMATRIX operator * (const RMATRIX &, REAL);
RMATRIX operator * (REAL, const RMATRIX &);
RMATRIX operator ^ (const RMATRIX &, int);
RMATRIX operator ^ (const RMATRIX &, const RMATRIX &);

int operator == (const RMATRIX &, const RMATRIX &);
int operator != (const RMATRIX &, const RMATRIX &);

RVECTOR operator - (const RVECTOR &);
RVECTOR operator *= (const RVECTOR &, const RMATRIX &);
REAL operator + (const RVECTOR &, REAL);
REAL operator + (REAL, const RVECTOR &);
REAL operator - (const RVECTOR &, REAL);
REAL operator - (REAL, const RVECTOR &);
RVECTOR operator + (const RMATRIX &, const RVECTOR &);
RVECTOR operator + (const RVECTOR &, const RMATRIX &);
RVECTOR operator + (const RVECTOR &, const RVECTOR &);
RVECTOR operator - (const RVECTOR &, const RVECTOR &);
RVECTOR operator - (const RMATRIX &, const RVECTOR &);
RVECTOR operator - (const RVECTOR &, const RMATRIX &);
RVECTOR operator * (const RMATRIX &, const RVECTOR &);
RVECTOR operator * (const RVECTOR &, REAL);
RVECTOR operator * (REAL, const RVECTOR &);
RVECTOR operator * (const RVECTOR &, const RVECTOR &);
REAL operator / (REAL, const RVECTOR &);
RVECTOR operator / (const RVECTOR &, const RMATRIX &);
RVECTOR operator / (const RVECTOR &, REAL);

/////////////////////////////////////////////////////////////////////////
// Declarations of Functions
void ms_MOut(const RMATRIX &a);
void ms_VOut(const RVECTOR &v);
void ms_Eye(RMATRIX &);
void ms_Zeros(RMATRIX &);
void ms_Ones(RMATRIX &);
void ms_Eye(RMATRIX &a);
RMATRIX ms_Zeros(int n, int m=0);
RMATRIX ms_Ones(int n, int m=0);
RMATRIX ms_Eye(int=dimension_of_space);
RMATRIX ms_Inv(const RMATRIX &a0);
REAL ms_Det(const RMATRIX &a0);
REAL ms_Trace(const RMATRIX &);
RMATRIX ms_Trans(const RMATRIX &);
RMATRIX ms_Minor(const RMATRIX &,int,int);
REAL ms_Norm1(const RVECTOR &x);
REAL ms_Norm1(const RMATRIX &a);
REAL ms_Norm2(const RVECTOR &x);
REAL ms_Norm2(const RMATRIX &a);
REAL ms_Norm8(const RVECTOR &x);
REAL ms_Norm8(const RMATRIX &a);
void ms_Sort(RVECTOR &v);
void ms_Sort(const RVECTOR &v, int pos[]);
RVECTOR ms_CumSum(const RVECTOR &v);
REAL ms_Sum(const RVECTOR &v);
REAL ms_VMax(const RVECTOR &v);
REAL ms_VMin(const RVECTOR &v);
REAL ms_VMax(const RVECTOR &v, int &iv);
REAL ms_VMin(const RVECTOR &v, int &iv);
REAL ms_Mean(const RVECTOR &v);
RVECTOR ms_Poly(RVECTOR &p);
RVECTOR ms_LinSpace(REAL x1, REAL x2, int n);
RVECTOR ms_LogSpace(int d1, int d2, int n);
RVECTOR ms_LinSol(const RMATRIX &a, const RVECTOR &b);
void ms_TStats(const RVECTOR &t,const RVECTOR &y,REAL yr,REAL &mp,REAL &tp,REAL &tr,REAL &ts,REAL &ess, int opts=0);
long ms_Locate(const RVECTOR &xx, REAL x);
RVECTOR ms_Filter(const RVECTOR &b, const RVECTOR &a, const RVECTOR &x); 
RVECTOR ms_Conv(const RVECTOR &a, const RVECTOR &b);

void Array2Vector(REAL a[], RVECTOR &b);
void Array2Matrix(REAL **a, RMATRIX &b);
void Vector2Array(const RVECTOR &a, REAL b[]);
void Matrix2Array(const RMATRIX &a, REAL **b);

#endif // __RMATRIX_H_
