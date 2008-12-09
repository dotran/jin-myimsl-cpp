/////////////////////////////////////////////////////////////////////////
// Program  : minor.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include "cmatrix.h"
#include "imsl.h"

/////////////////////////////////////////////////////////////////////////
// outputs a minor of a matrix at the iith row and jjth column
RMATRIX ms_Minor(const RMATRIX &a, int ii, int jj)
{
	if ((ii<0)  || (ii>=a.n) || (jj<0) || (jj>=a.m))
		ErrorMsg ("Error in 'Minor': wrong arguments\n");
	int an=a.n, am=a.m;
	int s=0;
	RMATRIX c(an-1,am-1);
	for (int i=0; i<(an-1)*(am-1); i++)
	{
		if (i+s==ii*am) s+=an;
		if ((i+s)%an==jj) s++;
		if (i+s==ii*am) s+=an;
		c(i)=a(i+s);
	}
	return c;
}

CMATRIX ms_Minor(const CMATRIX &a, int ii, int jj)
{
	if ((ii<0)  || (ii>=a.n) || (jj<0) || (jj>=a.m))
		ErrorMsg ("Error in 'Minor': wrong arguments\n");
	int an=a.n, am=a.m;
	int s=0;
	CMATRIX c(an-1,am-1);
	for (int i=0; i<(an-1)*(am-1); i++)
	{
		if (i+s==ii*am) s+=an;
		if ((i+s)%an==jj) s++;
		if (i+s==ii*am) s+=an;
		c(i)=a(i+s);
	}
	return c;
}

RMATRIX ms_Trans(const RMATRIX &a)
{
	RMATRIX c(a.m,a.n);
	for (int i=0;i<a.m;i++)
		for (int j=0;j<a.n;j++)  c(i,j)=a(j,i);
	return c;
}

CMATRIX ms_Trans(const CMATRIX &a)
{
	CMATRIX c(a.m,a.n);
	for (int i=0;i<a.m;i++)
		for (int j=0;j<a.n;j++)  c(i,j)=a(j,i);
	return c;
}

CMATRIX ms_Hermit(const CMATRIX &a)
{
	return !a;
}
