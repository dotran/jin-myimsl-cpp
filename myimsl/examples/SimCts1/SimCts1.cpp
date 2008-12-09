/////////////////////////////////////////////////////////////////////////
// Program  : simcts.cpp
//            Step response of a 2nd-order continuous-time system 
//            with/without time delay
//            Y(s)/U(s)= 1/(s^2+0.7s+1) or exp(-0.5s)/(s^2+0.7s+1)
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 20/10/2003
//
#include "stdafx.h"
#include "plplot.h"
#include "diffeqs.h"

void main(void)
{
	int i, n= 2, ndata= 1000, s= 0;
	REAL pb[]= {0.0, 0.0, 1.0}, pa[]= {1.0, 0.7, 1.0}, L= 0.5;
	REAL t, h= 0.02, u, y;
	DIFFEQS ode;                    // use ode or ode(nd) or ode(n,nd)

	plsdev("win3");	                // outputs graphics to the window console
//	plscolbg(255, 255, 255);        // sets the background white
	plinit();                         // initialises PLPLOT
	plcol0(7);  
	plenv(0.0, 20.0, 0.0, 2.0, 0, 1); // sets up standard window and draw box
	plcol0(1);
	pllab("Time","Output","Step Response"); // draws the title and labels
	t= 0.0; y= 0.0;

	for(i= 0; i < ndata; i++) {
		plline1(0, t, y,&s, 2);               // draws a line with a given point
		u= 1.0;
//		y= LSim(ode, u, pb, pa, n, t, h);  // system without time delay
		y= LSim(ode, u, pb, pa, n, t, h, L);   // system with time delay
		t+= h;
	}
	 plend(); // ends PLPLOT
}