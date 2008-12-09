/////////////////////////////////////////////////////////////////////////
// Program  : minfun1.cpp
//            Finds a local minimum of f(x) using ** method
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 20/11/2003
//
#include "stdafx.h"
#include <math.h>
#include "plplot.h"
#include "imsl.h"

REAL fun(REAL x);
void main(void)
{
	int n= 50, s= 0, s1= 0;
	REAL x1= -1, x2= 2, x, dx= 0.1, y, y1;

	plsdev("win3");	
	plinit();
	plcol0(1);
	plenv(x1, x2, -2.0, 1.0, 0, 0);
	pllab("x","f(x)",""); 

	for(x= x1; x < x2; x+= 0.05) 
		plline1(0, x, fun(x), &s, 2);

	x= FMin(fun, x1, dx);   // function minimisation
	y1= fun(x);
	for(y= -2.0; y <= y1; y+= 0.08) 
	{
		pllsty(3);            // dashed line
		plline1(1, x, y, &s1, 3);
	}

	printf("x= %f, f(x)= %f\n", x, y1);
	plend();
	return;
}

/////////////////////////////////////////////////////////////////////////
// f(x)= x*x-2+exp(-x)
REAL fun(REAL x)
{
	return(x*x-2.0+exp(-x));
}
