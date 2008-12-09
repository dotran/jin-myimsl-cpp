/////////////////////////////////////////////////////////////////////////
// Program  : norm1.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include <math.h>
#include "cmatrix.h"

/////////////////////////////////////////////////////////////////////////
// 1-norm of a REAL vector x, |x[0]|+..+|x[n-1]|
REAL ms_Norm1(REAL x[], int n)
{
	REAL norm= 0;

	for(int i=0; i<n; i++)
		norm+= ABS(x[i]);
	return norm;
}

/////////////////////////////////////////////////////////////////////////
// 1-norm of a REAL vector x, |x[0]|+..+|x[n-1]|
REAL ms_Norm1(const RVECTOR &x)
{
	REAL norm= 0;

	for(int i=0; i<x.num; i++)
		norm+= ABS(x(i));
	return norm;
}

/////////////////////////////////////////////////////////////////////////
// 1-norm of a COMPLEX vector x, |x[0]|+..+|x[n-1]|
REAL ms_Norm1(const CVECTOR &x)
{
	REAL norm= 0;

	for(int i=0; i<x.num; i++)
		norm+= abs(x(i));
	return norm;
}

/////////////////////////////////////////////////////////////////////////
// 1-norm of a REAL matrix, the largest column sum
REAL ms_Norm1(REAL** a, int n, int m)
{
	REAL norm= 0, sum;

	for(int j=0; j<m; j++)
	{
		sum= 0;
		for(int i=0; i<n; i++)
			sum+= ABS(a[i][j]);
		norm= MAX(norm, sum);
	}
	return norm;
}

/////////////////////////////////////////////////////////////////////////
// 1-norm of a REAL matrix, the largest column sum
REAL ms_Norm1(const RMATRIX &a)
{
	REAL norm= 0, sum;

	for(int j=0; j<a.m; j++)
	{
		sum= 0;
		for(int i=0; i<a.n; i++)
			sum+= ABS(a(i,j));
		norm= MAX(norm, sum);
	}
	return norm;
}

/////////////////////////////////////////////////////////////////////////
// 1-norm of a REAL matrix, the largest column sum
REAL ms_Norm1(const CMATRIX &a)
{
	REAL norm= 0, sum;

	for(int j=0; j<a.m; j++)
	{
		sum= 0;
		for(int i=0; i<a.n; i++)
			sum+= abs(a(i,j));
		norm= MAX(norm, sum);
	}
	return norm;
}

