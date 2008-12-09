/////////////////////////////////////////////////////////////////////////
// Program  : ployfit.cpp
//            polynomial fitting(y= a0+a1*x+a2*x^2 with parameters a0=1.4, a1=1, a2= 0.6)
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 22/12/2003
//
#include "stdafx.h"
#include <math.h>
#include "plplot.h"
#include "imsl.h"
void func(REAL x, REAL y[],int m);

void main(void)
{
	int i, j, n=100, m=3;
	REAL *a,*x,*y,**covar,p[9];

	x=RVector(n);
	y=RVector(n);
	a=RVector(m);
	covar= RMatrix(m,m);
	SRand(299);    // set the random number generator with seed= 299
	LinSpace(0.0, 10.0, n, x);
	for(i=0;i<n;i++)
		y[i]=1.4+x[i]+0.6*x[i]*x[i]+2*UnifRnd(-1,1); // generate data with random noises(-2~2)

	plsdev("win3");	
	plinit();
	plcol0(1);
	plenv(0.0, 10.0, -10.0, 90.0, 0, 0); 
	pllab("x","y(x)",""); 
	plcol0(11);
	plpoin(n, x, y, 21); 

	PolyFit(x,y,n,a,m,covar,func); // output a[0..m-1], n: data number

	for(i=0;i<n;i++)
		y[i]= a[0]+a[1]*x[i]+a[2]*x[i]*x[i]; // generate polynomial with estimated coefficients
	plcol0(2);
	plline(n, x, y); 

	printf("\n%11s %15s\n","parameter","deviation");
	for(i=0;i<m;i++)
		printf("a[%1d]= %8.6f    %8.6f\n",i,a[i],sqrt(covar[i][i]));
	printf("\n");
	printf("covariance matrix\n");
	MOut(covar,m,m);

	Free_RVector(y);
	Free_RVector(x);
	Free_RVector(a);
	Free_RMatrix(covar);
	plend();
	return;
}

void func(REAL x, REAL y[], int m)
{
	for(int i=0; i<m; i++)
		y[i]= pow(x, i);
}
