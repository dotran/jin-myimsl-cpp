/////////////////////////////////////////////////////////////////////////
// Program  : cumsum.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include "rmatrix.h"

/////////////////////////////////////////////////////////////////////////
// Cummulated sum
void ms_CumSum(REAL v[], int n, REAL cumv[])
{
	cumv[0]= v[0];
	for(int i=1; i<n; i++)
		cumv[i]= cumv[i-1]+v[i];
}

/////////////////////////////////////////////////////////////////////////
// Cummulated sum of a REAL vector
RVECTOR ms_CumSum(const RVECTOR &v)
{
	RVECTOR cumv(v);

	for(int i=1; i<v.num; i++)
		cumv(i)+= cumv(i-1);
	return cumv;
}