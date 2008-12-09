/////////////////////////////////////////////////////////////////////////
// Program  : draw2d.cpp
//            Draw a 2-D contour
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 20/10/2003
//
#include "stdafx.h"
#include "plplot.h"
#include "imsl.h"
#define NX   50		// Data points in x
#define NY   50		// Datat points in y 
REAL xmin= -2.0, xmax= 4.0, ymin= -2.0, ymax= 2.0;
void mypltr(REAL x, REAL y, REAL *tx, REAL *ty, void *pltr_data);

void main()
{
	int i, j, nlevel= 10;
	REAL **z, x[NX], y[NY];
	REAL clevel[]= {0.05, .2, .4, .6, .8, 1., 1.5, 3, 5, 9};

	z= RMatrix(NX, NY);
	LinSpace(xmin, xmax, NX, x);
	LinSpace(ymin, ymax, NY, y);
	for(i= 0; i < NX; i++) 
		for(j= 0; j < NY; j++) 
	    z[i][j]= (x[i]-1)*(x[i]-1)+x[i]*y[j];

	plsdev("win3");	
	plinit();
	pladv(0);
	plvpor(0.15, 0.85, 0.15, 0.85);
	plwind(xmin, xmax, ymin, ymax);
	plcol0(7);
	plbox("bcnst", 0.0, 0, "bcnst", 0.0, 0);
	pl_setcontlabelparam(0.006, 0.3, 0.1, 1);
	plcol0(2);
	plcont(z, NX, NY, 1, NX, 1, NY, clevel, nlevel, mypltr, NULL);
	plcol0(1);
	pllab("x", "y", "(x-1)*(x-1)+x*y");
    
	plend();
	Free_RMatrix(z);
	return;
}

///////////////////////////////////////////////////////////////////
// function called by "plcont"
void mypltr(REAL x, REAL y, REAL *tx, REAL *ty, void *pltr_data)
{
	*tx= (xmax-xmin)*x/(NX-1)+xmin;
	*ty= (ymax-ymin)*y/(NY-1)+ymin;
}
