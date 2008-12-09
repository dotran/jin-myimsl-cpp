/////////////////////////////////////////////////////////////////////////
// Program  : norm8.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include <math.h>
#include "cmatrix.h"

/////////////////////////////////////////////////////////////////////////
// infinity norm of a REAL vector x, max(|x[0],..,x[n-1])
REAL ms_Norm8(REAL x[], int n)
{
	REAL norm;

	norm= ABS(x[0]);
	for(int i=1; i<n; i++)
		norm= MAX(norm, ABS(x[i]));
	return norm;
}

/////////////////////////////////////////////////////////////////////////
// infinity norm of a REAL vector x, max(|x[0],..,x[n-1])
REAL ms_Norm8(const RVECTOR &x)
{
	REAL norm;

	norm= ABS(x(0));
	for(int i=1; i<x.num; i++)
		norm= MAX(norm, ABS(x(i)));
	return norm;
}

/////////////////////////////////////////////////////////////////////////
// infinity norm of a COMPLEX vector x, max(|x[0],..,x[n-1])
REAL ms_Norm8(const CVECTOR &x)
{
	REAL norm;

	norm= abs(x(0));
	for(int i=1; i<x.num; i++)
		norm= MAX(norm, abs(x(i)));
	return norm;
}

/////////////////////////////////////////////////////////////////////////
// infinity norm of a REAL matrix, the largest row sum
REAL ms_Norm8(REAL** a, int n, int m)
{
	int i,j;
	REAL norm= 0, sum;

	for(i=0; i<n; i++)
	{
		sum= 0;
		for(j=0; j<m; j++)
			sum+= ABS(a[i][j]);
		norm= MAX(norm, sum);
	}
	return norm;
}

/////////////////////////////////////////////////////////////////////////
// infinity norm of a REAL matrix, the largest row sum
REAL ms_Norm8(const RMATRIX &a)
{
	REAL norm= 0, sum;

	for(int i=0; i<a.n; i++)
	{
		sum= 0;
		for(int j=0; j<a.m; j++)
			sum+= ABS(a(i,j));
		norm= MAX(norm, sum);
	}
	return norm;
}

/////////////////////////////////////////////////////////////////////////
// infinity norm of a COMPLEX matrix, the largest row sum
REAL ms_Norm8(const CMATRIX &a)
{
	REAL norm= 0, sum;

	for(int i=0; i<a.n; i++)
	{
		sum= 0;
		for(int j=0; j<a.m; j++)
			sum+= abs(a(i,j));
		norm= MAX(norm, sum);
	}
	return norm;
}

