/////////////////////////////////////////////////////////////////////////
// Program  : draw2d.cpp
//            Draw a 2-D graph
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 20/10/2003
//
#include "stdafx.h"
#include <math.h>
#include "plplot.h"
#include "imsl.h"

void main(void)
{
	int i, n= 100;
	double *x, *y;

	x= RVector(n);
	y= RVector(n);
	LinSpace(-3.0*PI, 3.0*PI, n, x); // sets an equally spaced vector
	for(i= 0; i < n; i++)
		y[i]= exp(-0.1*fabs(x[i]))*cos(x[i]);
	plsdev("win3");	
	plinit();

	plcol0(1);
	plenv(-3.0*PI, 3.0*PI, -1.5, 1.5, 0, 0); // sets up standard window and draw box
	pllab("x","y(x)",""); // draws the title and labels
	plcol0(2);
	plline(n, x, y);      // draws line segments
	plcol0(11);
	plpoin(n, x, y, 21);  // draws symbols(#21)


	plend();
	Free_RVector(x);
	Free_RVector(y);
	return;
}
