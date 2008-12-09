/////////////////////////////////////////////////////////////////////////
// Program  : mout.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include <stdio.h>
#include "cmatrix.h"

/////////////////////////////////////////////////////////////////////////
// outputs an INTEGER matrix a[nrl..nrh][ncl..nch]
void ms_MOut(int** a, long n1, long n2, long n3, long n4)
{
	long nrl, nrh, ncl, nch;

	if(n3 == 0 || n4 == 0)
	{
		nrl=0; nrh= n1;
		ncl=0; nch= n2;
	}
	else
	{
		nrl= n1; nrh= n2+1;	
		ncl= n3; nch= n4+1;	
	}
	for(long i= nrl; i < nrh; i++)
	{
		for(long j= ncl; j < nch; j++)
			printf("%d ", a[i][j]);
		printf("\n");
	}
	printf("\n");		
	return;
}
/////////////////////////////////////////////////////////////////////////
// outputs a REAL atrix a[nrl..nrh][ncl..nch]
void ms_MOut(REAL** a, long n1, long n2, long n3, long n4)
{
	long nrl, nrh, ncl, nch;

	if(n3 == 0 || n4 == 0)
	{
		nrl=0; nrh= n1;
		ncl=0; nch= n2;
	}
	else
	{
		nrl= n1; nrh= n2+1;	
		ncl= n3; nch= n4+1;	
	}
	for(long i= nrl; i < nrh; i++)
	{
		for(long j= ncl; j < nch; j++)
#ifdef TDFL
			printf("%f ", a[i][j]);
#else
			printf("%lf ", a[i][j]);
#endif
		printf("\n");
	}
	printf("\n");	
	return;
}
/////////////////////////////////////////////////////////////////////////
// outputs a REAL matrix a(0..n-1,0..m-1)
void ms_MOut(const RMATRIX &a)
{	
	for(int i=0; i<a.n; i++)
	{
		for(int j=0; j<a.m; j++)
			printf("%f ",a(i,j));
		printf("\n");
	}
	printf("\n");
	return;
}

/////////////////////////////////////////////////////////////////////////
// outputs a COMPLEX matrix a(0..n-1,0..m-1)
void ms_MOut(CMATRIX a)
{	
	for(int i=0; i<a.n; i++)
	{
		for(int j=0; j<a.m; j++)
			if(a(i,j).Im >=0)
				printf("%f+j%f ",a(i,j).Re, a(i,j).Im);
			else
				printf("%f-j%f ",a(i,j).Re, -a(i,j).Im);
		printf("\n");
	}
	printf("\n");
	return;
}