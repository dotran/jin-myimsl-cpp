/////////////////////////////////////////////////////////////////////////
// Program  : testmv2.cpp
//            Operations of COMPLEX matrices and vectors
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 20/10/2003
//
#include <stdio.h>
#include "cmatrix.h"

void main(void)
{

// Basic operations of COMPLEX variables
	printf("Basic operations of COMPLEX variables\n");
	COMPLEX c1,c2(-2,2),c3;
	REAL r1,r2;

	c1.Set(1,1);
	c3= conj(c1)+10*c2;
	c2= 1/c3;
	c2= cos(c2);
	COut(c2);
	r1=abs(c2);
	r2=phase(c2);
	printf("%f %f\n\n",r1,r2);

// Basic operations of COMPLEX vectors
	printf("Basic operations of COMPLEX vectors\n");
	CVECTOR z1(3,"1 2 3 0 1.2 -2.3"), z2(3), z3(3);
	RVECTOR v1(4,"1 2 4 1"), v2(3);

	z2="4.1 3.4 0 0 2 2";
	z3= 2*z1-z2;
	z3+= z1;
	for(int i=0;i<v2.num;i++)
		v2(i)=abs(z3(i));
	VOut(z3);
	VOut(v2);

	z3= Roots(v1); // R(s)= s^3 + 2s^2 + 4s + 1= 0
	VOut(z3);
	RMATRIX b(3,3,"0 1 0 0 0 1 -1 -4 -2");
	z3= Eigen(b);
	VOut(z3);

	// Basic operations of COMPLEX matrices
	CMATRIX c(2,2,"1 1 0 -1 1 0 2 -1"), cc(2,2);
	MOut(c);
	cc= Inv(c);
	MOut(cc);
	MOut(cc*c);

	c2= Trace(c);
	COut(c2);

	return;
}
