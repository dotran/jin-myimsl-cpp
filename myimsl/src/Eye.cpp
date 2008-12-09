/////////////////////////////////////////////////////////////////////////
// Program  : eye.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include "cmatrix.h"

/////////////////////////////////////////////////////////////////////////
// generates a REAL identity matrix
void ms_Eye(RMATRIX &a)
{
	if (a.n!=a.m)
		ErrorMsg ("Error in 'Eye(RMATRIX)': matrix is not square\n");
	for(int i=0;i<a.n;i++) 
		for(int j=0; j<a.n; j++)
			a(i,j)= (i==j) ? 1:0;
	return;
}

/////////////////////////////////////////////////////////////////////////
// generates a REAL identity matrix
RMATRIX ms_Eye(int n)
{
	RMATRIX a(n,n);
	for(int i=0;i<n;i++) 
		for(int j=0; j<n; j++)
			a(i,j)= (i==j) ? 1:0;
	return a;
}

/////////////////////////////////////////////////////////////////////////
// generates a COMPLEX identity matrix
void ms_Eye(CMATRIX &a)
{
	if (a.n!=a.m)
		ErrorMsg ("Error in 'Eye(CMATRIX)': matrix is not square\n");
	for(int i=0;i<a.n;i++) 
		for(int j=0; j<a.n; j++)
			a(i,j)= (i==j) ? 1:0;
		return;
}