/////////////////////////////////////////////////////////////////////////
// Program  : fzero.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include <math.h>
#include "realtype.h"

/////////////////////////////////////////////////////////////////////////
// Returns the solution of f(x)=0 in the interval x1 < x < x2 
#define MAXIT 60
#define UNUSED (-1.11e30)
REAL ms_FZero(REAL (*func)(REAL), REAL x1, REAL x2)
{
	int j;
	REAL ans,fh,fl,fm,fnew,s,xh,xl,xm,xnew, xacc= 1.0e-6;

	fl= (*func)(x1);
	fh= (*func)(x2);
	if((fl > 0.0 && fh < 0.0) || (fl < 0.0 && fh > 0.0)) 
	{
		xl= x1;
		xh= x2;
		ans= UNUSED;
		for(j=1;j<=MAXIT;j++) 
		{
			xm= 0.5*(xl+xh);
			fm= (*func)(xm);
			s= sqrt(fm*fm-fl*fh);
			if(s == 0.0) return ans;
			xnew= xm+(xm-xl)*((fl >= fh ? 1.0 : -1.0)*fm/s);
			if(fabs(xnew-ans) <= xacc) return ans;
			ans= xnew;
			fnew= (*func)(ans);
			if(fnew == 0.0) return ans;
			if(SIGN(fm,fnew) != fm) 
			{
				xl= xm;
				fl= fm;
				xh= ans;
				fh= fnew;
			} 
			else if(SIGN(fl,fnew) != fl) 
			{
				xh= ans;
				fh= fnew;
			} 
			else if(SIGN(fh,fnew) != fh) 
			{
				xl= ans;
				fl= fnew;
			} 
			else ErrorMsg("Error in 'Fzero': never get here");
			if(fabs(xh-xl) <= xacc) return ans;
		}
		ErrorMsg("Error in 'Fzero': exceeds maximum iterations");
	}
	else 
	{
		if (fl == 0.0) return x1;
		if (fh == 0.0) return x2;
		ErrorMsg("Error in 'Fzero': root must be bracketed");
	}
	return 0.0;
}
#undef MAXIT
#undef UNUSED
