/////////////////////////////////////////////////////////////////////////
// Program  : sum.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include "cmatrix.h"

/////////////////////////////////////////////////////////////////////////
// sum of a REAL vector
REAL ms_Sum(REAL v[], int n)
{
	REAL s=0;

	for(int i=0; i<n; i++)
		s+= v[i];
	return s;
}

/////////////////////////////////////////////////////////////////////////
// sum of a REAL vector
REAL ms_Sum(const RVECTOR &v)
{
	REAL s=0;

	for(int i=0; i<v.num; i++)
		s+= v(i);
	return s;
}

/////////////////////////////////////////////////////////////////////////
// Sum of a COMPLEX vector
COMPLEX ms_Sum(const CVECTOR &v)
{
	COMPLEX s=0;

	for(int i=0; i<v.num; i++)
		s+= v(i);
	return s;
}