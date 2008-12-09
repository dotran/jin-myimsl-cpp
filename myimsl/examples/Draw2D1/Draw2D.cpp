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
	int i, n= 100, s=0, s1= 0, s2= 0;
	long l=123;
	REAL *x, *y1, *y2;

	x= RVector(n);
	y1= RVector(n);
	y2= RVector(n);
	LinSpace(-3.0*PI, 3.0*PI, n, x); // sets an equally spaced vector

	plsdev("win3");	
	plinit();
	plssub(2,2);

// #1 subplot
	plcol0(1);
	plenv(-3.0*PI, 3.0*PI, -1.5, 1.5, 0, 0); // sets up standard window and draw box
	pllab("x","y(x)","");                    // draws the title and labels
	for(i= 0; i < n; i++) 
	{
		plline1(0, x[i], cos(x[i]), &s, 2);    // draws line segments
		plline1(1, x[i], sin(x[i]), &s1, 3);   // draws line segments
	}

// #2 subplot
	for(i= 0; i < n; i++) 
	{
		y1[i]= exp(-0.1*fabs(x[i]))*cos(x[i]);
		y2[i]= exp(-0.1*fabs(x[i]))*sin(x[i]);
	}
	pladv(1);
	plcol0(1);
	plenv(-3.0*PI, 3.0*PI, -1.5, 1.5, 0, 0); // sets up standard window and draw box
	pllab("x","y1(x) & y2(x)","");           // draws the title and labels
	plcol0(2);
	plline(n, x, y1);                        // draws line segments
	plcol0(4);
	plline(n, x, y2);                        // draws line segments

// #3 subplot
	pladv(2);
	plcol0(1);
	plenv(-3.0*PI, 3.0*PI, -1.5, 1.5, 0, 0); // sets up standard window and draw box
	pllab("y1(x)","y2(x)","");               // draws the title and labels
	plcol0(2);
	plline(n, y1, y2);                       // draws line segments


	plend();
	Free_RVector(x);
	Free_RVector(y1);
	Free_RVector(y2);
	return;
}
