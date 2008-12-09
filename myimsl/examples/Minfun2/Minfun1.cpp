/////////////////////////////////////////////////////////////////////////
// Program  : minfun2.cpp
//            Finds a local minimum of f(x) of n variables
//            using the Powell method
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 10/12/2003
//
#include "stdafx.h"
#include <math.h>
#include "plplot.h"
#include "imsl.h"

REAL func(REAL x[]);

void main(void)
{
	int i, j, iter, n= 2, m= 25;
	REAL *x0, *x1, **f, x[5], p[5], fx, tol= 1.0e-7;
	REAL x0min, x0max, x1min, x1max, fmin, fmax;

	x0= RVector(m);
	x1= RVector(m);
	f= RMatrix(m,m);
	x0min= x1min= -6.0; x0max= x1max= 6.0;
	LinSpace(x0min, x0max, m, x0);
	LinSpace(x1min, x1max, m, x1);
	for(i= 0; i < m; i++)
	{
		x[0]= x0[i];
 		for(j= 0; j < m; j++)
		{
			x[1]= x1[j];
			f[i][j]= func(x);
		}
	}
	plsdev("win3");	
	plinit();
	pladv(0);
	plvpor(0.0, 1.0, 0.0, 1.0);
	plwind(-1.0, 1.0, -0.8, 1.5);
	plMinMax2dGrid(f, m, m, &fmax, &fmin);  
	plw3d(0.8, 1.0, 1.2, x0min-1, x0max+1, x1min-1, x1max+1, fmin-2, fmax+2, 33.0, 25.0);
	plcol0(1);
	plbox3("bnstu", "x0 axis", 0.0, 2,"bnstu", "x1 axis", 0.0, 2,
	     "bcdmnstuv", "f axis", 0.0, 2);

	plcol0(2);
	plmesh(x0, x1, f, m, m, 3);     // draws 3-D

//	p[0]=0; p[1]=10;                // initial values
//	p[0]=-1; p[1]=-1;               // initial values
	p[0]=1; p[1]=-1;                // initial values
	Powell(p,n,tol,&iter,&fx,func); // calls the powell method

	printf("Iterations= %3d\n\n",iter);
	printf("Minimum x= \n");
	VOut(p,n);
	printf("Minimum f(x)= %10.6f\n",fx);

	plend();
	Free_RVector(x0);
	Free_RVector(x1);
	Free_RMatrix(f);
	return;
}

/////////////////////////////////////////////////////////////////////////
// User-defined function
REAL func(REAL x[])
{
	REAL f,x0,x1;

	x0= x[0];
	x1= x[1];
	f= SQR(SQR(x0)+x1-11)+SQR(x0+SQR(x1)-7);
//	f= 100.0*pow(x0*x0-x1,2)+pow(1.0-x0,2);
	return f;
}