/////////////////////////////////////////////////////////////////////////
// Program  : filter.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 9/1/2004

#include "rmatrix.h"

/////////////////////////////////////////////////////////////////////////
//   Y = FILTER(B,A,X) filters the data in vector X with the
//   filter described by vectors A and B to create the filtered
//   data Y.  The filter is the form of
//   a(1)*y(n) = b(1)*x(n) + b(2)*x(n-1) + ... + b(nb+1)*x(n-nb)
//                         - a(2)*y(n-1) - ... - a(na+1)*y(n-na)
RVECTOR Filter(const RVECTOR &b, const RVECTOR &a, const RVECTOR &x) 
{
	int i,j,k;
	int na= a.num-1, nb= b.num-1, nx= x.num;
	REAL sum;
	RVECTOR y(nx);

	if(na<0||nb<0||nx<1) ErrorMsg("Error in 'Filter': check the dimension of vectors");
	if(a(0)==0) ErrorMsg("Error in 'Filter': check a(0)");

	for(i=0; i<nx; i++)
	{
		sum= 0;
		k= IMIN(nb, i);
		for(j=0; j<=k; j++)	sum+= b(j)*x(i-j);

		k= IMIN(na, i);
		for(j=1; j<=k; j++)	sum-= a(j)*y(i-j);
		y(i)= sum/a(0);
	}
	return y;
}
