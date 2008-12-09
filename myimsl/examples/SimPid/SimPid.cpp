/////////////////////////////////////////////////////////////////////////
// Program  : simpid.cpp
//            PID control of a 1st-order continuous-time system 
//            with time delay
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 20/10/2003
//
#include "stdafx.h"
#include "plplot.h"
#include "diffeqs.h"

void main()
{
	int i, n= 1, ndata= 1000, s= 0, s1= 0, s2= 0;
	REAL pb[]= {0.0, 1.0}, pa[]= {1.0, 1.0}, L= 0.0; // plant parameters
	REAL t, h= 0.01, u, y;
	REAL e, ee, ce, z, yr, Kp, Ki, Kd;
	DIFFEQS ode; 

	plsdev("win3");	
	plinit();
	plcol0(7);
	plenv(0.0, 10.0, 0.0, 3.0, 0, 1);
	plcol0(1);
	pllab("t(sec)","y(t) & u(t)","Step response of the PID control system");

	t= 0.0; yr= 1.0; y= 0.0; z= 0.0; ee= yr-y;
	Kp= 2.6; Ki= 3.6; Kd= 0.5; // PID gains
	for(i= 0; i < ndata; i++) 
	{
		e= yr-y;
		z+= 0.5*h*(e+ee);
		ce= (e-ee)/h;
		ee= e;
		u= Kp*e+Ki*z+Kd*ce;           // PID control
		y= LSim(ode, u, pb, pa, n, t, h, L); 
		t+= h;
		plline1(0, t, yr, &s, 8);     // reference input yr(t)
		plline1(1, t, y, &s1, 2);     // output y(t)
		plline1(2, t, u, &s2, 11);    // control input u(t)
	}
	plend();
}