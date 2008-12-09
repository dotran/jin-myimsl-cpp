/////////////////////////////////////////////////////////////////////////
// Program  : testmv.cpp
//            allocates, frees, reads and writes matrices and vectors
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 20/10/2003
//
#include <stdio.h>
#include "imsl.h"

void main(void)
{
	int n=2,m=3,*iv,**ia;
	REAL *v, **a;

	iv= IVector(n);
	VInpt(iv,n);
	VOut(iv,n);
	Free_IVector(iv);

	v= RVector(n);
	VInpt(v,n);
	VOut(v,n);
	Free_RVector(v);

	ia= IMatrix(n,m);
	MInpt(ia,n,m);
	MOut(ia,n,m);
	Free_IMatrix(ia);

	a= RMatrix(n,n);
	MInpt(a,n,n);
	MOut(a,n,n);
	Free_RMatrix(a);

	return;
}
