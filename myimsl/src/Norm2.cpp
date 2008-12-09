/////////////////////////////////////////////////////////////////////////
// Program  : norm2.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include <math.h>
#include "imsl.h"
#include "cmatrix.h"

/////////////////////////////////////////////////////////////////////////
// 2-norm of a REAL vector x, sqrt(x[0]^2+..+x[n-1]^2)
REAL ms_Norm2(REAL x[], int n)
{
	REAL norm= 0;

	for(int i=0; i<n; i++)
		norm+= SQR(x[i]);
	return sqrt(norm);
}

/////////////////////////////////////////////////////////////////////////
// 2-norm of a REAL vector x, sqrt(x[0]^2+..+x[n-1]^2)
REAL ms_Norm2(const RVECTOR &x)
{
	REAL norm= 0;

	for(int i=0; i<x.num; i++)
		norm+= SQR(x(i));
	return sqrt(norm);
}

/////////////////////////////////////////////////////////////////////////
// 2-norm of a COMPLEX vector x, sqrt(x[0]^2+..+x[n-1]^2)
REAL ms_Norm2(const CVECTOR &x)
{
	REAL norm= 0;

	for(int i=0; i<x.num; i++)
		norm+= SQR(abs(x(i)));
	return sqrt(norm);
}

/////////////////////////////////////////////////////////////////////////
// 2-norm of a REAL matrix, sqrt(max|eig(a'*a)|)
REAL ms_Norm2(REAL** a, int n, int m)
{
	int i,j,k;
	REAL norm= 0, **b, *rr, *ri;
	void ms_Eigen(REAL **a, int m, REAL rootr[], REAL rooti[]);

	b= RMatrix(m,m);
	rr= RVector(m);
	ri= RVector(m);

	for(i=0; i<m; i++)
		for(j=0; j<m; j++)
		{
			b[i][j]=0;
			for(k=0; k<n; k++)
				b[i][j]+= a[k][i]*a[k][j];
		}
	ms_Eigen(b,m,rr,ri);
	for(i=0; i<m; i++)
		norm= MAX(norm, ABS(rr[i]));
	Free_RMatrix(b);
	Free_RVector(rr);
	Free_RVector(ri);
	return sqrt(norm);
}

/////////////////////////////////////////////////////////////////////////
// 2-norm of a REAL matrix, sqrt(max|eig(a'*a)|)
REAL ms_Norm2(const RMATRIX &a)
{
	REAL norm= 0;
	CVECTOR v(a.m);
	RMATRIX b(a.m,a.m);

	b= ms_Trans(a)*a;
	v= ms_Eigen(b);
	for(int i=0; i<a.m; i++)
		norm= MAX(norm, abs(v(i)));
	return sqrt(norm);
}

/////////////////////////////////////////////////////////////////////////
// 2-norm of a REAL matrix, sqrt(max|eig(a'*a)|)
REAL ms_Norm2(const CMATRIX &a)
{
	REAL norm= 0;
	CVECTOR v(a.m);
	CMATRIX b(a.m,a.m);

	b= ms_Hermit(a)*a;
	v= ms_Eigen(b);
	for(int k=0; k<a.m; k++)
		norm= MAX(norm, abs(v(k)));
	return sqrt(norm);
}
