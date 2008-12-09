/////////////////////////////////////////////////////////////////////////
// Program  : simode.cpp
//            Step response of a 2nd-order continuous-time system
//            using the Runge-Kutta method directly
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 20/10/2003
//
#include "stdafx.h"
#include "plplot.h"
#include "diffeqs.h"
void plant(REAL u, REAL x[],REAL t, REAL xdot[]);

void main(void)
{
	int i, n= 2, ndata= 1000, nd, s= 0, s1= 0, s2= 0, s3= 0;
	REAL pa[]= {1.0, 1.3, 1.0}, pb[]= {0.0, 0.0, 1.0};
	REAL t, h= 0.02, L= 0.5, u, du, y, x[5];
	DIFFEQS ode, ode1;

	plsdev("win3");	
	plinit(); 
	plcol0(7);
	plenv(0.0, 20.0, 0.0, 2.0, 0, 1);
	plcol0(1);
	pllab("Time","Output","Step Responses"); 
	t= 0.0; x[0]= x[1]= y= 0.0;
	ode1.InitTimeDelay(0); // set all time delay buffers with 0
	nd= Round(L/h);
	for(i= 0; i < ndata; i++) {
		plline1(0, t, x[0], &s, 4);          // draws x[0]
//		plline1(1, t, y, &s1, 2);            // draws y
		u= 1.0;
//		y= LSim(ode, u, pb, pa, n, t, h, L); // system with time delay for check
		du= ode1.TimeDelay(u, nd);           // time delay implementation
		Rkqs(du, x, n, t, h, plant);         // R-K 5th-order method
		t+= h;
	}
	plend();
	return;
}

///////////////////////////////////////////////////////////////////
//   User-defined function called by "Rkqs"
void plant(REAL u, REAL x[], REAL t, REAL xdot[])
{
	xdot[0]= x[1];
	xdot[1]= -x[0]-1.3*x[1]+u;
	return;
}