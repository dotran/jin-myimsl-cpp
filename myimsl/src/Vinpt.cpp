/////////////////////////////////////////////////////////////////////////
// Program  : vinpt.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include <stdio.h>
#include "realtype.h"
#include "imsl.h"

/////////////////////////////////////////////////////////////////////////
// inputs an INTEGER vector v[nl..nh]
void ms_VInpt(int v[], long n1, long n2)
{
	long nl, nh;

	if(n2 == 0)
	{
		nl=0; nh= n1;
	}
	else
	{
		nl= n1; nh= n2+1;	
	}
	for(long i= nl; i < nh; i++)
	{
		printf("v[%ld]=", i);
		scanf("%d", &v[i]);
	}
	return;
}

/////////////////////////////////////////////////////////////////////////
// inputs a REAL vector v[nl..nh]
void ms_VInpt(REAL v[], long n1, long n2)
{
	long nl, nh;

	if(n2 == 0)
	{
		nl=0; nh= n1;
	}
	else
	{
		nl= n1; nh= n2+1;	
	}
	for(long i= nl; i < nh; i++)
	{
		printf("v[%ld]=", i);
#ifdef TDFL
		scanf("%f", &v[i]);
#else
		scanf("%lf", &v[i]);
#endif
	}
	return;
}
