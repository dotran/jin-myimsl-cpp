/////////////////////////////////////////////////////////////////////////
// Program  : linsol.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include <math.h>
#include "rmatrix.h"
/////////////////////////////////////////////////////////////////////////
// Solves a linear equation
void ms_LinSol(REAL **a, REAL b[], int n, REAL x[])
{
	int *indx;
	REAL **aa, d;
	void lubksb(REAL** a, int n, int *indx, REAL *d);
	void ludcmp(REAL** a, int n, int *indx, REAL *b);

	aa= ms_RMatrix(1,n,1,n);
	indx= ms_IVector(n);
	for(int i=0; i<n; i++)
	{
		x[i]= b[i];
		for(int j=0; j<n; j++) 
			aa[i+1][j+1]= a[i][j];
	}
	ludcmp(aa, n, indx-1, &d);
	lubksb(aa, n, indx-1, x-1);
	ms_Free_RMatrix(aa,1,n,1,n);
	ms_Free_IVector(indx);
	return;
}

/////////////////////////////////////////////////////////////////////////
// Solves a linear equation
RVECTOR ms_LinSol(const RMATRIX &a, const RVECTOR &b)
{
	int *indx,n=b.num;
	REAL **aa, *x0, d;
	RVECTOR x(n);
	void lubksb(REAL** a, int n, int *indx, REAL *d);
	void ludcmp(REAL** a, int n, int *indx, REAL *b);

	aa= ms_RMatrix(1,n,1,n);
	x0= ms_RVector(n);
	indx= ms_IVector(n);
	for(int i=0; i<n; i++)
	{
		x0[i]= b(i);
		for(int j=0; j<n; j++) 
			aa[i+1][j+1]= a(i,j);
	}
	ludcmp(aa, n, indx-1, &d);
	lubksb(aa, n, indx-1, x0-1);
	Array2Vector(x0,x);
	ms_Free_RMatrix(aa,1,n,1,n);
	ms_Free_RVector(x0);
	ms_Free_IVector(indx);
	return x;
}
/////////////////////////////////////////////////////////////////////////
// (C) Copr. 1986-92 Numerical Recipes Software
void ludcmp(REAL **a, int n, int *indx, REAL *d)
{
	int i,imax,j,k;
	REAL big,dum,sum,temp;
	REAL *vv;

	vv= ms_RVector(1,n);
	*d=1.0;
	for(i=1;i<=n;i++) {
		big=0.0;
		for(j=1;j<=n;j++)
			if((temp=fabs(a[i][j])) > big) big=temp;
		if(big == 0.0) ErrorMsg("Error in 'ludcmp': Matrix is close to singular");
		vv[i]=1.0/big;
	}
	for(j=1;j<=n;j++) {
		for(i=1;i<j;i++) {
			sum=a[i][j];
			for(k=1;k<i;k++) sum -= a[i][k]*a[k][j];
			a[i][j]=sum;
		}
		big=0.0;
		for(i=j;i<=n;i++) {
			sum=a[i][j];
			for (k=1;k<j;k++)
				sum -= a[i][k]*a[k][j];
			a[i][j]=sum;
			if((dum=vv[i]*fabs(sum)) >= big) {
				big=dum;
				imax=i;
			}
		}
		if(j != imax) {
			for(k=1;k<=n;k++) {
				dum=a[imax][k];
				a[imax][k]=a[j][k];
				a[j][k]=dum;
			}
			*d = -(*d);
			vv[imax]=vv[j];
		}
		indx[j]=imax;
		if(a[j][j] == 0.0) ErrorMsg("Error in 'ludcmp': Matrix is close to singular"); 
		if(j != n) {
			dum=1.0/(a[j][j]);
			for(i=j+1;i<=n;i++) a[i][j] *= dum;
		}
	}
	ms_Free_RVector(vv,1,n);
}

/////////////////////////////////////////////////////////////////////////
// (C) Copr. 1986-92 Numerical Recipes Software
void lubksb(REAL **a, int n, int *indx, REAL *b)
{
	int i,ii=0,ip,j;
	REAL sum;

	for(i=1;i<=n;i++) {
		ip=indx[i];
		sum=b[ip];
		b[ip]=b[i];
		if(ii)
			for(j=ii;j<=i-1;j++) sum -= a[i][j]*b[j];
		else if(sum) ii=i;
		b[i]=sum;
	}
	for(i=n;i>=1;i--) {
		sum=b[i];
		for(j=i+1;j<=n;j++) sum -= a[i][j]*b[j];
		b[i]=sum/a[i][i];
	}
}
