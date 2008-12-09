/////////////////////////////////////////////////////////////////////////
// Program  : locate.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include "rmatrix.h"

/////////////////////////////////////////////////////////////////////////
// finds j such that x is between xx[j] and xx[j+1]
long ms_Locate(REAL xx[], long n, REAL x)
{
	long ju,jm,jl;
	int ascnd;

	jl= -1; //modified
	ju= n-1; //modified
	if(x < xx[0]) return jl; //modified
	if(x > xx[n-1]) return ju; //modified
	ascnd= (xx[n-1] > xx[0]);
	while(ju-jl > 1) 
	{
		jm=(ju+jl) >> 1;
		if(x > xx[jm] == ascnd)
			jl=jm;
		else
			ju=jm;
	}
	return jl;
}

/////////////////////////////////////////////////////////////////////////
// finds j such that x is between xx[j] and xx[j+1]
long ms_Locate(const RVECTOR &xx, REAL x)
{
	long ju,jm,jl,n=xx.num;
	int ascnd;

	jl= -1; //modified
	ju= n-1; //modified
	if(x < xx(0)) return jl; //modified
	if(x > xx(n-1)) return ju; //modified
	ascnd= (xx(n-1) > xx(0));
	while(ju-jl > 1) 
	{
		jm=(ju+jl) >> 1;
		if(x > xx(jm) == ascnd)
			jl=jm;
		else
			ju=jm;
	}
	return jl;
}
