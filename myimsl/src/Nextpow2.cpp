/////////////////////////////////////////////////////////////////////////
// Program  : nextpow2.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include <math.h>
#include "realtype.h"

/////////////////////////////////////////////////////////////////////////
// generates the nearst integer number of n which is a power of 2
long ms_NextPow2(long n)
{
	int nu;
	long nn;

	double p= frexp((double)n, &nu);
	if(p >= 0.75)
		nn= (long)pow(2, nu);
	else
		nn= (long)pow(2, nu-1);
	return nn;
}
