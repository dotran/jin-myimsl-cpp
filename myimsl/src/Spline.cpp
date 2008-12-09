/////////////////////////////////////////////////////////////////////////
// Program  : spline.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include "realtype.h"

/////////////////////////////////////////////////////////////////////////
// cubic spline interpolation
REAL ms_Spline(REAL xa[], REAL ya[], int n, REAL yp1, REAL ypn, REAL x)
{
	int klo,khi,k;
	REAL h,b,a,y,*y2a;
	void spline(REAL x[], REAL y[], int n, REAL yp1, REAL ypn, REAL y2[]);

	y2a=RVector(n);
	spline(xa-1,ya-1,n,yp1,ypn,y2a-1);
	klo=0;
	khi=n-1;
	while(khi-klo > 1) 
	{
		k= (khi+klo) >> 1;
		if(xa[k] > x) khi=k;
		else klo=k;
	}
	h= xa[khi]-xa[klo];
	if(h == 0.0) ErrorMsg("Error in 'spline': Bad x input");
	a= (xa[khi]-x)/h;
	b= (x-xa[klo])/h;
	y= a*ya[klo]+b*ya[khi]+((a*a*a-a)*y2a[klo]+(b*b*b-b)*y2a[khi])*(h*h)/6.0;
	Free_RVector(y2a);
	return y;
}

/////////////////////////////////////////////////////////////////////////
// (C) Copr. 1986-92 Numerical Recipes Software 31a
void spline(REAL x[], REAL y[], int n, REAL yp1, REAL ypn, REAL y2[])
{
	int i,k;
	REAL p,qn,sig,un,*u;

	u= RVector(1,n-1);
	if(yp1 > 0.99e30)
		y2[1]=u[1]=0.0;
	else 
	{
		y2[1]= -0.5;
		u[1]= (3.0/(x[2]-x[1]))*((y[2]-y[1])/(x[2]-x[1])-yp1);
	}
	for(i=2;i<=n-1;i++) 
	{
		sig= (x[i]-x[i-1])/(x[i+1]-x[i-1]);
		p= sig*y2[i-1]+2.0;
		y2[i]= (sig-1.0)/p;
		u[i]= (y[i+1]-y[i])/(x[i+1]-x[i]) - (y[i]-y[i-1])/(x[i]-x[i-1]);
		u[i]= (6.0*u[i]/(x[i+1]-x[i-1])-sig*u[i-1])/p;
	}
	if (ypn > 0.99e30)
		qn=un=0.0;
	else 
	{
		qn= 0.5;
		un= (3.0/(x[n]-x[n-1]))*(ypn-(y[n]-y[n-1])/(x[n]-x[n-1]));
	}
	y2[n]= (un-qn*u[n-1])/(qn*y2[n-1]+1.0);
	for(k=n-1;k>=1;k--)
		y2[k]= y2[k]*y2[k+1]+u[k];
	Free_RVector(u,1,n-1);
}
