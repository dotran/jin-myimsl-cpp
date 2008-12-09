/////////////////////////////////////////////////////////////////////////
// Program  : spline.cpp
//            cubic spline interpolation
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 02/12/2003
//
#include "stdafx.h"
#include <math.h>
#include "plplot.h"
#include "imsl.h"

void main(void)
{
	int i, n=20, s=0;
	REAL xx,yy,yp1,ypn,*x,*y;

	x=RVector(n);
	y=RVector(n);
	LinSpace(0,2.0*PI,n,x);
	for(i=0; i<n; i++) 
		y[i]= sin(x[i]);
	yp1= cos(x[0]);
	ypn= cos(x[n-1]);

	plsdev("win3");	
	plinit();
	plcol0(1);
	plenv(0.0, 2.0*PI, -1.5, 1.5, 0, 0); 
	pllab("x","sin(x)",""); 
	plcol0(11);
	plpoin(n, x, y, 21); 

	for(xx=0.0; xx<=2.0*PI; xx+= 0.1) 
	{
		yy= Spline(x,y,n,yp1,ypn,xx);
		plline1(0, xx, yy, &s, 2); 
	}
	Free_RVector(y);
	Free_RVector(x);
	plend();
	return;
}
