/////////////////////////////////////////////////////////////////////////
// Program  : simode.cpp
//            Step response of a 1st-order continuous-time system
//            using the Runge-Kutta method directly
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 20/10/2003
//
#include "stdafx.h"
#include "plplot.h"
#include "diffeqs.h"

void plant(REAL u, REAL x[], REAL t, REAL xdot[]);

void main(void)
{
	int i, n= 1, ndata= 1000, s= 0, s1= 0;
	REAL t, h= 0.02, u, x[5], y;
	REAL pb[]= {0.0, 0.5}, pa[]= {1.0, 0.5};
	DIFFEQS ode, ode1;                      // use ode or ode(nd) or ode(n,nd)

	plsdev("win3");	                        // outputs graphics to the window console
//	plscolbg(255, 255, 255);              // sets the background using white color
	plinit();                               // initialises PLPLOT
	plcol0(7);  
	plenv(0.0, 20.0, 0.0, 2.0, 0, 1);       // sets up standard window and draw box
	plcol0(1);
	pllab("Time","Output","Step Response"); // draws the title and labels
	t= 0.0; x[0]= y= 0.0;
	for(i= 0; i < ndata; i++) {
		plline1(0, t, x[0], &s, 2);           // draws x[0]
//		plline1(1, t, y, &s1, 12);            // draws y
		u= 1.0;
		y= LSim(ode, u, pb, pa, n, t, h);     // system without time delay
		Rkqs(u, x, n, t, h, plant);           // 5th-order Runge-Kutta
		t+= h;
	}
	plend();                                 // ends PLPLOT
	return;
}

///////////////////////////////////////////////////////////////////
//   User-defined function called by "Rkqs"
void plant(REAL u, REAL x[], REAL t, REAL xdot[])
{
	xdot[0]= -0.5*x[0]+0.5*u;
	return;
}
