/////////////////////////////////////////////////////////////////////////
// Program  : mean.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include "rmatrix.h"

/////////////////////////////////////////////////////////////////////////
// mean
REAL ms_Mean(REAL v[], int n)
{
	REAL s=0;

	for(int i=0; i<n; i++)
		s+= v[i];
	return s/n;
}

/////////////////////////////////////////////////////////////////////////
// mean
REAL ms_Mean(const RVECTOR &v)
{
	int n=v.num;
	REAL s=0;

	for(int i=0; i<n; i++)
		s+= v(i);
	return s/n;
}