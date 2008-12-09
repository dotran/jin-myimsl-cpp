/////////////////////////////////////////////////////////////////////////
// Program  : trace.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include "cmatrix.h"

/////////////////////////////////////////////////////////////////////////
// Trace of a matrix
double ms_Trace (const RMATRIX &a)
{
	if (a.n!=a.m)
		ErrorMsg ("Error in 'Trace(RMATRIX)': matrix is not square");
	double c=0;
	for (int i=0;i<a.n;i++) c+=a(i,i);
	return c;
}

/////////////////////////////////////////////////////////////////////////
// Trace of a matrix
COMPLEX ms_Trace(const CMATRIX &a)
{
	if (a.n!=a.m)
		ErrorMsg ("Error in 'Trace(CMATRIX)': matrix is not square");
	COMPLEX c=0;
	for (int i=0;i<a.n;i++) c+=a(i,i);
	return c;
}
