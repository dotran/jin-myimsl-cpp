////////////////////////////////////////////////////////////////////////
// Program  : roots.cpp
//            finds the roots of an nth-order polynomial with real coefficients
//            f(x)= an*x^n+an-1*x^n-1 +...+a1*x+a0= 0
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 22/12/2003
//
#include "stdafx.h"
#include "imsl.h"

void main(void)
{

	int i, n= 4;
	static double a[]={1,3,1,7,1};
	double rootr[10], rooti[10];

	Roots(a,n,rootr,rooti); // computes the roots of f(x)= x^4+3x^3+x^2+7x+1= 0
	for(i=0; i<n; i++)
		printf("%8d %15.6lf %15.6lf\n",i,rootr[i],rooti[i]);
	printf("\n");
	return;
}

