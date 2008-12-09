/////////////////////////////////////////////////////////////////////////
// Program  : simcts.cpp
//            Step response of a 1st-order continuous-time system 
//            with/without time delay
//            Y(s)/U(s)= 0.5/(s+0.5) or 0.5exp(-2s)/(s+0.5)
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 20/10/2003
//
#include "stdafx.h"
#include "plplot.h"
#include "diffeqs.h"

void main(void)
{
	int i, n= 1, ndata= 1000, s= 0;
	REAL pb[]= {0.0, 0.5}, pa[]= {1.0, 0.5}, L= 2.0;
	REAL t, h= 0.02, u, y;
	DIFFEQS ode(3,2000);            // ode(n) or ode(n, nbuf)

	plsdev("win3");	                // outputs graphics to the window console
	plinit();                         // initialises PLPLOT
	plcol0(7);  
	plenv(0.0, 20.0, 0.0, 2.0, 0, 1); // sets up standard window and draw box
	plcol0(1);
	pllab("Time","Output","Step Response"); // draws the title and labels

	t= 0.0; y= 0.0;
	for(i= 0; i < ndata; i++) {
		plline1(0, t, y, &s, 2);              // draws output
		u= 1.0;
//		y= LSim(ode, u, pb, pa, n, t, h);    // without time delay
		y= LSim(ode, u, pb, pa, n, t, h, L);   // with time delay
		t+= h;
	}
	 plend(); // ends PLPLOT
	}