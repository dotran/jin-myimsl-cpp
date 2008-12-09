/////////////////////////////////////////////////////////////////////////
// Program  : fmin.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include "realtype.h"

/////////////////////////////////////////////////////////////////////////
// local minimizer of f(x)
#define EPS     1.0e-6
#define MAXLOOP 100000
REAL ms_FMin(REAL (*func)(REAL x), REAL p1, REAL dp)
{
	long int i;
	REAL p2, p3, pn, pmin, f1, f2, f3, fpn, fmin, a1, a2;

	f1= (*func)(p1);
	p2= p1+dp;
	f2= (*func)(p2);
	if(f1 > f2) 
	{
		p3= p1+2.0*dp;
		fmin= f2;
		pmin= p2;
	}
	else
	{
		p3= p1-dp;
		fmin= f1;
		pmin= p1;
	}
	f3= (*func)(p3);
	if(f3 < fmin) 
	{
		fmin= f3;
		pmin= p3;
	}
	for(i= 0; i< MAXLOOP; i++) 
	{
		a1= (f2-f1)/(p2-p1);
		a2= ((f3-f1)/(p3-p1)-a1)/(p3-p2);
		pn= 0.5*(p1+p2-a1/a2);
		fpn= (*func)(pn);
		if(ABS(pmin-pn) <= EPS && ABS(fmin-fpn) <= EPS) 
			return pn;
		p3= p2;
		f3= f2;
		p2= pn;
		f2= fpn;
		pmin= p2;
		fmin= f2;
	}
	ErrorMsg("Error in 'FMin': exceeds maximum iterations");
	return pn;
}
#undef EPS
#undef MAXLOOP
