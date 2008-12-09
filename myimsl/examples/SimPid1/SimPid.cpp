/////////////////////////////////////////////////////////////////////////
// Program  : simpid.cpp
//            PID control of a 2nd-order continuous-time system 
//            with time delay
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 20/10/2003
//
#include "imsl.h"
#include "plplot.h"
#include "diffeqs.h"
void main()
{
	int i, n= 2, ndata= 2000, s= 0, s1= 0, s2= 0, op=1;
	REAL pb[]= {0.0, 0.0, 1.0}, pa[]= {1.0, 0.7, 1.0}, L= 0.5;
	REAL t, h= 0.005, u, y;
	REAL e,e1, ce, z, yr, Kp, Ki, Kd;
	REAL mp, tp, tr, ts, ess, *tt, *yy;
	DIFFEQS ode(3,600); //ode(n,nd)

	tt=RVector(ndata);
	yy=RVector(ndata);
	plsdev("win3");	
    plinit();
	plcol0(7);
	plenv(0.0, 10.0, -1.0, 3.0, 0, 1);
    plcol0(1);
	pllab("t(sec)","y(t) & u(t)","Step response of the PID control system");

	t= 0.0; yr= 1.0; y= 0.0; z= 0.0; e1= yr-y; u=0;
	Kp= 1.44; Ki= 0.72; Kd= 1.55; // PID gains
	for(i= 0; i < ndata; i++) 
	{
		e= yr-y;
		z+= 0.5*h*(e+e1);
		ce= (e-e1)/h;
		e1= e;
		u= Kp*e+Ki*z+Kd*ce;           // PID control
		y= LSim(ode, u, pb, pa, n, t, h, L); 
		t+= h;
		tt[i]= t; 
		yy[i]= y;
		plline1(0, t, yr, &s, 8);     // reference input yr(t)
		plline1(1, t, y, &s1, 2);     // output y(t)
		plline1(2, t, u, &s2, 11);    // control input u(t)
	}
	TStats(tt, yy, yr, ndata, mp, tp, tr, ts, ess); // system performance with default 2% ts
	TStats(tt, yy, yr, ndata, mp, tp, tr, ts, ess, op); // system performance(op=1: 5% ts)
	printf("System performance\n");
	printf("mp=%6.2f tp=%6.2f tr=%6.2f ts=%6.2f ess=%6.2f\n",mp, tp, tr, ts, ess);
	plend();
	Free_RVector(tt);
	Free_RVector(yy);
}
