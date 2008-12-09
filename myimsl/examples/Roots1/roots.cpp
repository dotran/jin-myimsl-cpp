/////////////////////////////////////////////////////////////////////////
// Program  : roots1.cpp
//            finds the roots of a polynomial with real coefficients
//            R(p)= Pns^n+Pn-1s^n-1 +...+a1P1+a0= 0
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 22/12/2003
//
#include <stdio.h>
#include "cmatrix.h"

void main(void)
{
	int n=4, np1=n+1;
	CVECTOR root(n);
	RVECTOR p(np1,"1 3 1 7 1");

	root= Roots(p); 
	printf("Complex roots\n");
	VOut(root);

	return;
}