/////////////////////////////////////////////////////////////////////////
// Program  : draw3d.cpp
//            Draw a 3-D helix graph
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 20/06/2009
//
#include "stdafx.h"
#include <math.h>
#include "plplot.h"
#include "diffeqs.h"
#include "imsl.h"
void fun(double u,double x[],double t,double ak[]);

void main(void)
{
	int i, n= 15000;
	double *xx, *yy, *zz, u= 0,h= 0.005, t= 0, x[3]={10,-10,-10};

	xx= RVector(n);
	yy= RVector(n);
	zz= RVector(n);
	plsdev("win3");	
	plinit();
	pladv(0);
	plvpor(0.0, 1.0, 0.0, 1.0);
	plwind(-1, 1, -1, 1.5);
	plw3d(0.9, 0.9, 1.5, -20.0, 30.0, -20.0, 40.0, -20.0, 70.0, 43.0, 45.0);
	plcol0(1);
	plbox3("bnstu", "x axis", 0.0, 2,"bnstu", "y axis", 0.0, 2,
	     "bcmnstuv", "z axis", 0.0, 2);

	for(i= 0; i < n; i++)
	{
		xx[i]= x[0];
		yy[i]= x[1];
		zz[i]= x[2];
		Rk4(u,x,3,t,h,fun);
		t+= h;
	}

	plcol0(2);
	plline3(n, xx, yy, zz);
	plend();
	Free_RVector(xx);
	Free_RVector(yy);
	Free_RVector(zz);
	return;
}

/////////////////////////////////////////////////////////////////////////
//  Lorenz equation
void fun(double u,double x[],double t,double ak[])
{
	double s= 10, r= 28, b= 8/3;

	ak[0]= -s*x[0]+s*x[1];
	ak[1]= r*x[0]-x[1]-x[0]*x[2];
	ak[2]= x[0]*x[1]-b*x[2];
}