/////////////////////////////////////////////////////////////////////////
// Program  : vout.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include <stdio.h>
#include "cmatrix.h"

/////////////////////////////////////////////////////////////////////////
// outputs an INTEGER vector v[nl..nh]
void ms_VOut(int v[], long n1, long n2)
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
		printf("%d\n", v[i]);
	printf("\n");
	return;
}

/////////////////////////////////////////////////////////////////////////
// outputs a REAL vector v[nl..nh]
void ms_VOut(REAL v[], long n1, long n2)
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
#ifdef TDFL
		printf("%f\n", v[i]);
#else
		printf("%lf\n", v[i]);
#endif
	printf("\n");
	return;
}

/////////////////////////////////////////////////////////////////////////
// outputs a REAL vector v(0..n-1)
void ms_VOut(const RVECTOR &v)
{	
	for(int i=0; i<v.n; i++)
		printf("%f\n",v(i));
	printf("\n");
	return;
}
/////////////////////////////////////////////////////////////////////////
// outputs a COMPLEX vector v(0..n-1)
void ms_VOut(const CVECTOR &v)
{	
	for(int i=0; i<v.n; i++)
		if(v(i).Im >=0)
			printf("%f+j%f\n",v(i).Re,v(i).Im);
		else
			printf("%f-j%f\n",v(i).Re,-v(i).Im);
	printf("\n");
	return;
}