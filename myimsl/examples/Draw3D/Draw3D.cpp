/////////////////////////////////////////////////////////////////////////
// Program  : draw3d.cpp
//            Draw a 3-D graph
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 20/10/2003
//
#include "stdafx.h"
#include "plplot.h"
#include "imsl.h"

void main(void)
{
  int i, j, n= 30, m= 20;
	REAL *x, *y, **z;
	REAL xmin, xmax, ymin, ymax, zmin, zmax;

	x= RVector(n);
	y= RVector(m);
	z= RMatrix(n,m);
	xmin= ymin= -3.0; xmax= ymax= 3.0;
	LinSpace(xmin, xmax, n, x);
	LinSpace(ymin, ymax, m, y);
	for(i= 0; i < n; i++) 
 		for(j= 0; j < m; j++) 
			z[i][j]= (1.-x[i])*(1.-x[i])+x[j]*y[j];

	plsdev("win3");	
	plinit();
	pladv(0);
	plvpor(0.0, 1.0, 0.0, 1.0);
	plwind(-1.0, 1.0, -0.8, 1.5);
	plMinMax2dGrid(z, n, m, &zmax, &zmin);  
	plw3d(0.8, 1.0, 1.2, xmin, xmax, ymin, ymax, zmin, zmax, 33.0, 25.0);
	plcol0(1);
	plbox3("bnstu", "x axis", 0.0, 2,"bnstu", "y axis", 0.0, 2,
	     "bcmnstuv", "z axis", 0.0, 2);
//	plbox3("bnstu", "x axis", 0.0, 2,"bnstu", "y axis", 0.0, 2,
//	     "bcdmnstuv", "z axis", 0.0, 2);

	plcol0(2);
	plmesh(x, y, z, n, m, 3);
	plend();
	Free_RVector(x);
	Free_RVector(y);
	Free_RMatrix(z);
	return;
}