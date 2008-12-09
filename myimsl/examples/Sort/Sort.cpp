/////////////////////////////////////////////////////////////////////////
// Program  : sort.cpp
//            sorts a vector in increasing order
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 22/12/2003
//
#include "stdafx.h"
#include "imsl.h"

void main(void)
{
	int i, n= 5, idx[20];
	REAL v[20];

	SRand(123);
	for(i=0; i<n; i++)
		v[i]= UnifRnd(-5,5);
	printf("Original data \n");
	VOut(v,n);
	Sort(v,n);  // v is modified on return
	printf("Sorted data \n");
	VOut(v,n);

	printf("hit any key\n");
	getchar();

	for(i=0; i<n; i++)
		v[i]= UnifRnd(-5,5);
	printf("Original data \n");
	VOut(v,n);
	Sort(v,n,idx); // v is not modified but order is storaged in idx 
	printf("Sorted data \n");
	for(i=0; i<n; i++)
		printf("%11.6lf %3d \n",v[idx[i]],idx[i]);
	return;
}