/////////////////////////////////////////////////////////////////////////
// Program  : sort1.cpp
//            sorts a vector in increasing order
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 22/12/2003
//
#include <stdio.h>
#include "imsl.h"
#include "rmatrix.h"

void main(void)
{
	int i, n=10, idx[20];
	RVECTOR v(n);

	SRand(123);
	for(i=0; i<n; i++)
		v(i)= UnifRnd(-5,5);
	VOut(v);
	Sort(v);  // v is modified
	VOut(v);

	printf("hit any key\n");
	getchar();

	for(i=0; i<n; i++)
		v(i)= UnifRnd(-5,5);
	VOut(v);
	Sort(v,idx); // v is not modified
	for(i=0; i<n; i++)
		printf("%15.6lf %8d %15.6lf \n",v(i),idx[i],v(idx[i]));
	return;
}