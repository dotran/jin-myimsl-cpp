/////////////////////////////////////////////////////////////////////////
// Program  : draw3d.cpp
//            Draw a 3-D graph with sides
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 20/10/2003
//
#include "stdafx.h"
#include "plplot.h"
#include "imsl.h"

void main(void)
{
	int i, j, n=30, m=30;
	REAL *x, *y, **z, zmin, zmax;

	x= RVector(n);
	y= RVector(m);
	z= RMatrix(n,m);
	LinSpace(-3.0, 3.0, n, x);
	LinSpace(-3.0, 3.0, m, y);
	for(i= 0; i < n; i++) 
 		for(j= 0; j < m; j++) 
			 z[i][j]= (1.-x[i])*(1.-x[i]) +y[j]*y[j];

	plsdev("win3");	
	plinit();
	pladv(0);
	plvpor(0.0, 1.0, 0.0, 1.0);
	plwind(-1.0, 1.0, -1.0, 1.5);
	plMinMax2dGrid(z, n, m, &zmax, &zmin);  
	plw3d(0.8, 1.0, 1.2, -3.0, 3.0, -3.0, 3.0, zmin, zmax, 33.0, 25.0);
	plcol0(1);
	plbox3("bnstu", "x axis", 0.0, 2,"bnstu", "y axis", 0.0, 2,
	     "bcmnstuv", "z axis", 0.0, 2);

	plcol0(2);
	plot3d(x, y, z, n, m, 3, 1);
//	plsurf3d(x, y, z, n, m, 0, NULL, 0);
	plend();
	Free_RVector(x);
	Free_RVector(y);
	Free_RMatrix(z);
	return;
}
