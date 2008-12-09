/////////////////////////////////////////////////////////////////////////
// Program  : poly.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 10/01/2004

#include "cmatrix.h"

// finds the polynomial from REAL roots 
RVECTOR Poly(RVECTOR &p)
{
	int i, j, n= p.num, np1= n+1;
	RVECTOR a(np1);
	CVECTOR c(np1), d(np1);

	for(i=0; i<np1; i++) 
		c(i)= (i==0) ? 1:0;

	for(j=0; j<n; j++)
	{
		for(i=1; i<=j+1; i++)
			d(i)= c(i)-p(j)*c(i-1);
		for(i=1; i<=j+1; i++)
			c(i)= d(i);
	}
	for(i=0; i<np1; i++)
		a(i)= c(i).Re;
	return a;
}

// finds the polynomial from COMPLEX roots 
RVECTOR Poly(CVECTOR &p)
{
	int i, j, n= p.num, np1= n+1;
	RVECTOR a(np1);
	CVECTOR c(np1), d(np1);

	for(i=0; i<np1; i++) 
		c(i)= (i==0) ? 1:0;

	for(j=0; j<n; j++)
	{
		for(i=1; i<=j+1; i++)
			d(i)= c(i)-p(j)*c(i-1);
		for(i=1; i<=j+1; i++)
			c(i)= d(i);
	}
	for(i=0; i<np1; i++)
		a(i)= c(i).Re;
	return a;
}
