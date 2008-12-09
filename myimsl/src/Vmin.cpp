/////////////////////////////////////////////////////////////////////////
// Program  : vmin.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include "rmatrix.h"

/////////////////////////////////////////////////////////////////////////
// min
REAL ms_VMin(REAL v[], int n)
{
	REAL minv= v[0];
	for(int i= 1; i < n; i++)
		if(v[i] < minv)
			minv= v[i];
	return minv;
}

/////////////////////////////////////////////////////////////////////////
// min
REAL ms_VMin(const RVECTOR &v)
{
	REAL minv= v(0);
	for(int i= 1; i < v.num; i++)
		if(v(i) < minv)
			minv= v(i);
	return minv;
}

/////////////////////////////////////////////////////////////////////////
// min
REAL ms_VMin(REAL v[], int n, int &iv)
{
	REAL minv;

	iv= 0;
	minv= v[0];
	for(int i= 1; i < n; i++)
		if(v[i] < minv)
		{
			iv= i;
			minv= v[i];
		}
	return minv;
}
/////////////////////////////////////////////////////////////////////////
// min
REAL ms_VMin(const RVECTOR &v, int &iv)
{
	REAL minv= v(0);
	iv= 0;
	for(int i= 1; i < v.num; i++)
		if(v(i) < minv)
		{
			iv= i;
			minv= v(i);
		}
	return minv;
}
