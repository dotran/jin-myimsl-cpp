/////////////////////////////////////////////////////////////////////////
// Program  : conv.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 9/1/2004

#include "rmatrix.h"

/////////////////////////////////////////////////////////////////////////
// Convolution and polynomial multiplication. The resulting
// vector is length LENGTH(a)+LENGTH(b)-1
RVECTOR Conv(const RVECTOR &a, const RVECTOR &b) 
{
	int i, na= a.num, nb= b.num;

	if(na<1||nb<1) ErrorMsg("Error in 'Conv': check the dimension of two vectors");
	RVECTOR c(na+nb-1), x(na+nb-1), aa(1,"1");

	if(na > nb)
	{
		for(i=0; i<na;i++) x(i)= a(i);
		if(nb > 1)
			for(i=na; i<na+nb-1;i++) x(i)= 0;
    c= Filter(b, aa, x);
	}
	else
	{
		for(i=0; i<nb;i++) x(i)= b(i);
    if(na > 1)
			for(i=nb; i<na+nb-1;i++) x(i)= 0;
    c= Filter(a, aa, x);
	}
	return c;
}