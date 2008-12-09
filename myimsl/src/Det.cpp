/////////////////////////////////////////////////////////////////////////
// Program  : det.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include "cmatrix.h"

/////////////////////////////////////////////////////////////////////////
// Deteminant of a matrix
REAL ms_Det(REAL** a0, int n)
{
	int i, j, *indx;
	REAL **a, d;
	void ludcmp(REAL **a, int n, int *indx, REAL *d);

	a= ms_RMatrix(1,n,1,n);
	indx= ms_IVector(1,n);
	for(i=0; i<n; i++)
		for(j=0; j<n; j++) 
			a[i+1][j+1]= a0[i][j];
	ludcmp(a, n, indx, &d);
	for(i=0;i<n;i++) 
		d*= a[i+1][i+1];
	ms_Free_RMatrix(a,1,n,1,n);
	ms_Free_IVector(indx,1,n);
	return d;
}

/////////////////////////////////////////////////////////////////////////
// Deteminant of a matrix
REAL ms_Det(const RMATRIX &a0)
{
	int i, j, *indx, n=a0.n;
	REAL **a, d;
	void ludcmp(REAL **a, int n, int *indx, REAL *d);

	a= ms_RMatrix(1,n,1,n);
	indx= ms_IVector(1,n);
	for(i=0; i<n; i++)
		for(j=0; j<n; j++) 
			a[i+1][j+1]= a0(i,j);
	ludcmp(a, n, indx, &d);
	for(i=0;i<n;i++) 
		d*= a[i+1][i+1];
	ms_Free_RMatrix(a,1,n,1,n);
	ms_Free_IVector(indx,1,n);
	return d;
}

/////////////////////////////////////////////////////////////////////////
// Deteminant of a matrix
COMPLEX ms_Det(const CMATRIX &a)
{
	if (a.num==1) return a(0);
		if (a.n!=a.m)
			ErrorMsg ("Error in 'Det(CMATRIX)': Matrix is not square");
	int an=a.n, sign=1;
	CMATRIX c(a);
	COMPLEX t(1), k, kt;
	for (int l=0; l<an-1; l++)
	{
		if (c.SortMatrix(l)) sign=-sign;
		kt=c(l,l);
		t*=kt;
		if (t==0) return t;
		for (int i=l+1; i<an; i++)
		{
			k=c(i,l)/kt;
			c(i,l)=0;
			for(int j=l+1; j<an; j++) c(i,j)-=k*c(l,j);
		}
	}
	return sign*t*c(c.num-1);
}
