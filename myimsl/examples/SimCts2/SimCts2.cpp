/////////////////////////////////////////////////////////////////////////
// Program  : simcts.cpp
//            Step response of a 1st-order continuous-time system 
//            with/without time delay, setting initial condition
//            Y(s)/U(s)= 0.5/(s+1) or 0.5exp(-s)/(s+1)
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 20/10/2003
//
#include "stdafx.h"
#include "plplot.h"
#include "diffeqs.h"
void main(void)
{
	int i, n= 1, ndata= 1000, s= 0;
	double pa[]= {1.0, 0.5}, pb[]= {0.0, 0.5}, L= 1;
	double t, h= 0.02, u, y, x[5];
	DIFFEQS ode(1,1000);  // ode(n, nd) where nd > L/h

	plsdev("win3");	
	plinit(); 
	plcol0(7);  
	plenv(0.0, 20.0, 0.0, 2.0, 0, 1); 
	plcol0(1);
	pllab("Time","Output","Step Response");
	t= 0.0; 
	x[0]= 0.1;         // sets the initial value
	InitLSim(ode,x,n,0.2); // sets the initial state x with 0.1 and all delay buffers with 0.2
	y= x[0];
	for(i= 0; i < ndata; i++) 
	{
		plline1(0, t, y, &s, 2); 
		u= 1.0;
//		y= LSim(ode, u, pb, pa, n, t, h); // without time delay
		y= LSim(ode, u, pb, pa, n, t, h, L); // with time delay
		t+= h;
	}

	plend();
	return;
}