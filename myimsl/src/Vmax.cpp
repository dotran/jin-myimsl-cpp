/////////////////////////////////////////////////////////////////////////
// Program  : vmax.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 02/03/2003
//

#include "rmatrix.h"

/////////////////////////////////////////////////////////////////////////
// max
REAL ms_VMax(REAL v[], int n)
{
	REAL maxv= v[0];

	for(int i= 1; i < n; i++)
		if(v[i] > maxv)
			maxv= v[i];
	return maxv;
}

/////////////////////////////////////////////////////////////////////////
// max
REAL ms_VMax(const RVECTOR &v)
{
	REAL maxv= v(0);

	for(int i= 1; i < v.num; i++)
		if(v(i) > maxv)
			maxv= v(i);
	return maxv;
}

/////////////////////////////////////////////////////////////////////////
// max
REAL ms_VMax(REAL v[], int n, int &iv)
{
	REAL maxv= v[0];
	iv= 0;
	for(int i= 1; i < n; i++)
		if(v[i] > maxv)
		{
			iv= i;
			maxv= v[i];
		}
	return maxv;
}

/////////////////////////////////////////////////////////////////////////
// max
REAL ms_VMax(const RVECTOR &v, int &iv)
{
	REAL maxv= v(0);
	iv= 0;
	for(int i= 1; i < v.num; i++)
		if(v(i) > maxv)
		{
			iv= i;
			maxv= v(i);
		}
	return maxv;
}
