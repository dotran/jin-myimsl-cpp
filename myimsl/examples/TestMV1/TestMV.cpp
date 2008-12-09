/////////////////////////////////////////////////////////////////////////
// Program  : testmv1.cpp
//            allocates, frees, reads and writes matrices and vectors
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 20/10/2003
//
#include <stdio.h>
#include "imsl.h"
#include "rmatrix.h"

void main(void)
{
	REAL ymax, ymin, nm1, nm2, nm8, det;

// Basic operations of REAL vectors
	printf("Basic operations of REAL vectors\n");
	RVECTOR v1(3,"1 2 3"), v2(3), v3(3);
	v2="4.1 3.4 0";
	v3= 2*v1-v2;
	v3+= v1;
	VOut(v3);
	ymax= VMax(v3);
	ymin= VMin(v3);
	printf("ymax= %f  ymin= %f\n", ymax, ymin);
	nm1= Norm1(v3); nm2= Norm2(v3); nm8= Norm8(v3);
	printf("Norm1= %f  Norm2= %f  Inf Norm= %f\n", nm1, nm2, nm8);

// Basic operations of REAL matrices
	printf("Basic operations of REAL matrices\n");
	RMATRIX a1(2,2,"1 3 5 7"), a2(2,2),a3(a1);
	a2= Eye(2)+a3;
	a2-= a1;
	a2= a2/a2;
	a2="4 3 2 1";
	nm1= Norm1(a2); nm2= Norm2(a2); nm8= Norm8(a2);
	printf("Norm1= %f  Norm2= %f  Inf Norm= %f\n", nm1, nm2, nm8);
	MOut(a2);
	printf("inverse matrix\n");
	a3= Inv(a2);
	MOut(a3);
	det= Det(a3);
	printf("determinant= %f\n",det);
	a2= Zeros(2,2);
	MOut(a2);
	a3= Ones(2,2);
	MOut(a3);
	a2= Eye(2);
	MOut(a2);

// conversion of REAL vectors and matrices into array and vice versa
	int n=3, m=2;
	REAL *v, **p;
	RVECTOR vv(n);
	RMATRIX pp(n,m,"1 2 3 4 5 6");

	v= RVector(n);
	VInpt(v,n);
	Array2Vector(v,vv);
	VOut(v,n);
	VOut(vv);
	Free_RVector(v);

	p= RMatrix(n,m);
	Matrix2Array(pp,p);
	MOut(p,n,m);
	MOut(pp);
	Free_RMatrix(p);

	return;
}
