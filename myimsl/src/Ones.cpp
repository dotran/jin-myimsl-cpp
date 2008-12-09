/////////////////////////////////////////////////////////////////////////
// Program  : ones.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include "imsl.h"
#include "cmatrix.h"

/////////////////////////////////////////////////////////////////////////
// generates ones matrices
void ms_Ones(RMATRIX &a)
{
	for (int i=0;i<a.num;i++) a(i)=1;
}

/////////////////////////////////////////////////////////////////////////
// generates ones matrices
RMATRIX ms_Ones(int n, int m)
{
	if(m!=0)
	{
		RMATRIX a(n,m);
		for (int i=0;i<a.num;i++) a(i)=1;
		return a;
	}
	else
	{
		RMATRIX a(n,n);
		for (int i=0;i<a.num;i++) a(i)=1;
		return a;
	}
}

/////////////////////////////////////////////////////////////////////////
// generates ones matrices
void ms_Ones(CMATRIX &a)
{
	for(int i=0;i<a.num;i++) a(i)=1;
}
