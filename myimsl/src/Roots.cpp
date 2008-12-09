/////////////////////////////////////////////////////////////////////////
// Program  : roots.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include "cmatrix.h"

/////////////////////////////////////////////////////////////////////////
// Finds the roots of a REAL coefficient polynomials
void ms_Roots(REAL a[], int n, REAL rtr[], REAL rti[])
{
	int j,k;
	REAL **hess,xr,xi;
	void balanc(REAL **a, int n);
	void hqr(REAL **a, int n, REAL wr[], REAL wi[]);

	if(a[0]==0||n<1) 
		ErrorMsg("Error in 'Roots': check args or n");
	else if(n==1) 
	{
		rtr[0]= -a[1]/a[0];
		rti[0]= 0;
		return;
	}
	hess=RMatrix(1,n,1,n);
	for(k=1;k<=n;k++)
	{
		hess[1][k]= -a[k]/a[0];
		for(j=2;j<=n;j++) hess[j][k]=0.0;
		if(k != n) hess[k+1][k]=1.0;
	}

	balanc(hess,n);
	hqr(hess,n,rtr-1,rti-1);

	for(j=1;j<n;j++) 
	{
		xr=rtr[j];
		xi=rti[j];
		for(k=j-1;k>=0;k--) 
		{
			if(rtr[k] <= xr) break;
			rtr[k+1]=rtr[k];
			rti[k+1]=rti[k];
		}
		rtr[k+1]=xr;
		rti[k+1]=xi;
	}
	Free_RMatrix(hess,1,n,1,n);
	return;
}

/////////////////////////////////////////////////////////////////////////
// Finds the roots of a REAL coefficient polynomials
CVECTOR ms_Roots(const RVECTOR &a)
{
	int j,k,n=a.num-1; //n= para number-1
	REAL **hess,*rtr,*rti;
	CVECTOR rt(n);
	void balanc(REAL **a, int n);
	void hqr(REAL **a, int n, REAL wr[], REAL wi[]);

	if(a(0)==0||n<1) 
		ErrorMsg("Error in 'Roots': check args or n");
	else if(n==1) 
	{
		rt(0)= -a(1)/a(0);
		return rt;
	}
	hess= RMatrix(1,n,1,n);
	rtr= RVector(1,n);
	rti= RVector(1,n);
	for(k=1;k<=n;k++) 
	{
		hess[1][k]= -a(k)/a(0);
		for(j=2;j<=n;j++) hess[j][k]=0.0;
		if(k != n) hess[k+1][k]=1.0;
	}

	balanc(hess,n);
	hqr(hess,n,rtr,rti);

	for(k=1;k<=n;k++)
		rt(k-1).Set(rtr[k],rti[k]);
	Sort(rt);

	Free_RMatrix(hess,1,n,1,n);
	Free_RVector(rtr,1,n);
	Free_RVector(rti,1,n);
	return rt;
}

