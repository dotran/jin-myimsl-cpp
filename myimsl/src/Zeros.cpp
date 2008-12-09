/////////////////////////////////////////////////////////////////////////
// Program  : zeros.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include "imsl.h"
#include "cmatrix.h"

/////////////////////////////////////////////////////////////////////////
// Generates a REAL zeros matrix
RMATRIX ms_Zeros(int n, int m)
{
	if(m!=0)
	{
		RMATRIX a(n,m);
		for (int i=0;i<a.num;i++) a(i)=0;
		return a;
	}
	else
	{
		RMATRIX a(n,n);
		for (int i=0;i<a.num;i++) a(i)=0;
		return a;
	}
}

/////////////////////////////////////////////////////////////////////////
// Generates a REAL zeros matrix
void ms_Zeros(RMATRIX &a)
{
	for (int i=0;i<a.num;i++) a(i)=0;
}

/////////////////////////////////////////////////////////////////////////
// Generates a COMPLEX zeros matrix
void ms_Zeros(CMATRIX &a)
{
	for(int i=0;i<a.num;i++) a(i)=0;
}
