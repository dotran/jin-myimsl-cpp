/////////////////////////////////////////////////////////////////////////
// Program  : inv.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include "cmatrix.h"
#include "imsl.h"

/////////////////////////////////////////////////////////////////////////
// Inverse of a REAL matrix
void ms_Inv(REAL **a0, int n, REAL **ia)
{
	int i, j, *indx;
	REAL **a, *b, d;
	void lubksb(REAL** a, int n, int *indx, REAL *d);
	void ludcmp(REAL** a, int n, int *indx, REAL *b);

	a= ms_RMatrix(1,n,1,n);
	b= ms_RVector(1,n);
	indx= ms_IVector(1,n);
	for(i=0; i<n; i++)
		for(j=0; j<n; j++) 
			a[i+1][j+1]= a0[i][j];
	ludcmp(a, n, indx, &d);
	for(i=0;i<n;i++) 
	{
		for(j=0;j<n;j++) 
			b[j+1]= 0;
		b[i+1]= 1;
		lubksb(a, n, indx, b);
		for(j=0;j<n;j++) 
			ia[j][i]=b[j+1];
	}
	ms_Free_RMatrix(a,1,n,1,n);
	ms_Free_RVector(b,1,n);
	ms_Free_IVector(indx,1,n);
	return;
}

/////////////////////////////////////////////////////////////////////////
// Inverse of a REAL matrix
RMATRIX ms_Inv(const RMATRIX &a0)
{
	int i, j, *indx, n=a0.n, m=a0.m;
	REAL **a, *b, d;
	RMATRIX ia(n,m);
	void lubksb(REAL** a, int n, int *indx, REAL *d);
	void ludcmp(REAL** a, int n, int *indx, REAL *b);

	if (n!=m)
		ErrorMsg ("Error in 'Inv(RMATRIX)': matrix is not square\n");
	a= ms_RMatrix(1,n,1,n);
	b= ms_RVector(1,n);
	indx= ms_IVector(1,n);
	for(i=0; i<n; i++)
		for(j=0; j<n; j++) 
			a[i+1][j+1]= a0(i,j);
	ludcmp(a, n, indx, &d);
	for(i=0;i<n;i++) 
	{
		for(j=0;j<n;j++) 
			b[j+1]= (i==j) ? 1:0;
		lubksb(a, n, indx, b);
		for(j=0;j<n;j++) 
			ia(j,i)=b[j+1];
	}
	ms_Free_RMatrix(a,1,n,1,n);
	ms_Free_RVector(b,1,n);
	ms_Free_IVector(indx,1,n);
	return ia;
}

/////////////////////////////////////////////////////////////////////////
// Inverse of a COMPLEX matrix
#define CSWAP(a,b) {temp=(a);(a)=(b);(b)=temp;}
CMATRIX ms_Inv(const CMATRIX& f)
{
  if (f.n!=f.m) 
		ErrorMsg ("Error in 'Inv(CMATRIX)': matrix is not square\n");
  if (f.num==1)
  {
    CMATRIX r(1,1);
		r(0) = 1/f(0);
    return r;
  }
  CMATRIX g(f);
  int n=f.n;
  int *indxc, *indxr, *ipiv;
  int i, icol, irow, j, k, l, ll;
  COMPLEX temp, pivinv, dum, big;

  indxc = new int[n];
  indxr = new int[n];
  ipiv  = new int[n];
  for (j=0; j<n; j++) ipiv[j]=0;

  for (i=0; i<n; i++)
  {
    Zero(big);
    for (j=0; j<n; j++)
      if (ipiv[j] != 1)
        for (k=0; k<n; k++)
        {
          if (ipiv[k] == 0)
          {
            if (g(j,k) >= big)
            {
              big = g(j,k);
              irow=j;
              icol=k;
            }
                  }
          else if (ipiv[k] > 1)
                  ErrorMsg("Error in 'Inv': Singular Matrix-1");
        }
    ++(ipiv[icol]);
    if (irow != icol)
      for (l=0; l<n; l++) CSWAP(g(irow,l), g(icol,l))
    indxr[i]=irow;
    indxc[i]=icol;
    if (g(icol,icol) == 0)
      ErrorMsg("Error in 'Inv': Singular Matrix-2");
    pivinv = 1.0/g(icol, icol);
    g(icol, icol) = 1;
    for (l=0; l<n; l++) g(icol, l) *= pivinv;
    for (ll=0; ll<n; ll++)
      if (ll != icol)
      {
        dum=g(ll, icol);
        g(ll,icol) = 0;
        for (l=0; l<n; l++) g(ll,l) -= g(icol,l)*dum;
      }
  }
  for (l=n-1; l>=0; l--)
  {
    if (indxr[l] != indxc[l])
      for (k=0; k<n; k++) CSWAP(g(k,indxr[l]), g(k,indxc[l]));
  }

  delete indxc;
  delete indxr;
  delete ipiv;
  return g;
}
#undef CSWAP
