/////////////////////////////////////////////////////////////////////////
// Program  : poly.cpp
//            finds the polynomial from given roots
//            R(P)= Pnx^n+Pn-1x^n-1 +...+P1x1+P0= 0
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 22/12/2003
//
#include "cmatrix.h"

void main(void)
{
	int n=4;
	RVECTOR v(n+1,"1 4.1 3.8 40 -1"),w(n+1);
	CVECTOR p(n);

	VOut(v);
	p= Roots(v);
	VOut(p);
	w= Poly(p);
	VOut(w);

	return;
}
