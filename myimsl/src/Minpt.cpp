/////////////////////////////////////////////////////////////////////////
// Program  : minpt.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include <stdio.h>
#include "realtype.h"
#include "imsl.h"

/////////////////////////////////////////////////////////////////////////
// inputs an INTEGER matrix a[nrl..nrh][ncl..nch]
void ms_MInpt(int** a, long n1, long n2, long n3, long n4)
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
		for(long j= ncl; j < nch; j++)
		{
			printf("mat[%ld][%ld]=", i, j);
			scanf("%d", &a[i][j]);
		}
	return;
}

/////////////////////////////////////////////////////////////////////////
// inputs a REAL matrix a[nrl..nrh][ncl..nch]
void ms_MInpt(REAL** a, long n1, long n2, long n3, long n4)
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
		for(long j= ncl; j < nch; j++)
		{
			printf("mat[%ld][%ld]=", i, j);
#ifdef TDFL
			scanf("%f", &a[i][j]);
#else
			scanf("%lf", &a[i][j]);
#endif
		}
	return;
}
