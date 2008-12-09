/////////////////////////////////////////////////////////////////////////
// Program  : eigen1.cpp
//            finds the eigenvalues of a real or complex matrix
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 22/12/2003
//
#include <stdio.h>
#include "cmatrix.h"

void main(void)
{
	int n=3;

// Eigenvalues of a real matrix
	CVECTOR root(n);
	RMATRIX a(n,n,"1 2 0 0 1 3 1 1 -1");
	MOut(a);
	root= Eigen(a);
	VOut(root);

// Eigenvalues of a complex matrix
	CMATRIX b(n,n,"1 0 2 0 0 1 1 1 0 -1 0 0 0 0 -1 -1 2 2");
	MOut(b);
	root= Eigen(b);
	VOut(root);
	return;
}