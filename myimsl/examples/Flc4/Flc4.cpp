/////////////////////////////////////////////////////////////////////////
// Program  : main_sug.cpp
//            fuzzy control of the Lorenz model
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 2007/08/17
//
#include "stdafx.h"
#include <math.h>
#include "plplot.h"
#include "fuzzy.h"
#include "diffeqs.h"

void model(double u,double x[],double t,double ak[]);
void main(void)
{
	int i, n= 15000;
	double *xx, *yy, *zz, u= 0,h= 0.005, t= 0, x[3]={10,-10,-10};
	double alpha1, alpha2, u1, u2, K1[]={295.7, 137.2, 8.1}, K2[]={444.1, 204.8, -12.7};

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
		alpha1= Trapmf(x[0], -30, -30, -20, 30);
		alpha2= Trapmf(x[0], -20, 30, 40, 40);
		u1= -(K1[0]*x[0]+K1[1]*x[1]+K1[2]*x[2]);
		u2= -(K2[0]*x[0]+K2[1]*x[1]+K2[2]*x[2]);
		u= (u1*alpha1+u2*alpha2)/(alpha1+alpha2);
		if(i < 1000)
			u=0;
		Rk4(u,x,3,t,h,model);
		xx[i]= x[0];
		yy[i]= x[1];
		zz[i]= x[2];
		t+= h;
	}
	plcol0(4);
	plpoin3(1, xx, yy, zz, 23); 
	plcol0(2);
	plline3(n, xx, yy, zz);
	plcol0(8);
	plpoin3(1, &xx[n-1], &yy[n-1], &zz[n-1], 29); 
	plend();
	Free_RVector(xx);
	Free_RVector(yy);
	Free_RVector(zz);
	return;
}

/////////////////////////////////////////////////////////////////////////
//  Lorenz equation
void model(double u,double x[],double t,double ak[])
{
	double s= 10, r= 28, b= 8/3;

	ak[0]= -s*x[0]+s*x[1]+u;
	ak[1]= r*x[0]-x[1]-x[0]*x[2];
	ak[2]= x[0]*x[1]-b*x[2];
}