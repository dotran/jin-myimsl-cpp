/////////////////////////////////////////////////////////////////////////
// Program  : draw3d.cpp
//            Draw a 3-D graph
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 20/10/2003
//
#include "stdafx.h"
#include <math.h>
#include "plplot.h"
#include "imsl.h"
void cmap1_init();

void main(void)
{
	int i, j, n=30, m=30;
	REAL *x, *y, **z, xx, yy;
	REAL xmin, xmax, ymin, ymax, zmin, zmax;

	x= RVector(n);
	y= RVector(m);
	z= RMatrix(n,m);
	xmin= ymin= -3.0; xmax= ymax= 3.0;
	LinSpace(xmin, xmax, n, x);
	LinSpace(ymin, ymax, m, y);
	for(i= 0; i < n; i++)
	{
		xx= x[i];
 		for(j= 0; j < m; j++) 
		{
			yy= y[j];
			z[i][j]= 3*(1-xx)*(1-xx)*exp(-(xx*xx)-(yy+1)*(yy+1)) -
	             10*(xx/5-pow(xx,3)-pow(yy,5))*exp(-xx*xx-yy*yy)-
	             exp(-(xx+1)*(xx+1)-(yy*yy))/3;
		}
	}
 	plsdev("win3");	
	plinit();
	cmap1_init();
	pladv(0);
	plvpor(0.0, 1.0, 0.0, 1.0);
	plwind(-1.0, 1.0, -1.0, 1.4);
	plMinMax2dGrid(z, n, m, &zmax, &zmin);  
	plw3d(0.8, 1.0, 1.2, xmin, xmax, ymin, ymax, zmin, zmax, 33.0, 25.0);
	plcol0(1);
	plbox3("bnstu", "x axis", 0.0, 2,"bnstu", "y axis", 0.0, 2,
	     "bcmnstuv", "z axis", 0.0, 2);

	plmesh(x, y, z, n, m, 3 | MAG_COLOR);
//	plsurf3d(x, y, z, n, m, MAG_COLOR | FACETED, NULL, 0);

	plend();
	Free_RVector(x);
	Free_RVector(y);
	Free_RMatrix(z);
	return;
}

void cmap1_init()
{
  double i[2], h[2], l[2], s[2];

  i[0]= 0.0; i[1]= 1.0;  // left and right boundaries
  h[0]= 240; h[1]= 0;    // blue -> green -> yellow -> red
  l[0]= 0.6; l[1]= 0.6;
  s[0]= 0.8; s[1]= 0.8;
  plscmap1n(256);
  c_plscmap1l(0, 2, i, h, l, s, NULL);
}
