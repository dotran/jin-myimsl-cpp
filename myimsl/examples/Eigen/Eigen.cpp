/////////////////////////////////////////////////////////////////////////
// Program  : eigen.cpp
//            finds the eigenvalues of a matrix with real coefficients
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 22/12/2003
//
#include "stdafx.h"
#include "imsl.h"

void main(void)
{
	int i, n;
	REAL **a, *rootr, *rooti;

	printf("n= ");
	scanf_s("%d",&n);
	a= RMatrix(n,n);
	rootr= RVector(n);
	rooti= RVector(n);
	MInpt(a,n,n);
	printf("\nInput matrix=\n");
	MOut(a,n,n);

	Eigen(a,n,rootr,rooti);  // computes the eigenvalues of A

	printf("Eigenvalues=\n");
	for(i=0; i<n; i++)
		printf("%2d %13.6lf %13.6lf\n",i,rootr[i],rooti[i]);
	Free_RMatrix(a);
	Free_RVector(rootr);
	Free_RVector(rooti);
	return;
}