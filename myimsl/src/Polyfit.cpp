/////////////////////////////////////////////////////////////////////////
// Program  : polyfit.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include <math.h>
#include "realtype.h"

/////////////////////////////////////////////////////////////////////////
// returns the polynomial coefficients 
void ms_PolyFit(REAL x[], REAL y[], int n, REAL a[], int ma, 
		 REAL **covar, void (*func)(REAL x, REAL afunc[], int ma))
{
	int i,*ia;
	REAL *sig, **cov, chisq;
	void lfit(REAL x[], REAL y[], REAL sig[], int ndat, REAL a[], int ia[],
		int ma, REAL **covar, REAL *chisq, void (*func)(REAL, REAL [], int));

	ia= IVector(n);
	sig= RVector(n);
	cov= RMatrix(1,ma,1,ma);
	cov= ConvertMatrix(&covar[0][0],1,ma,1,ma);
	for(i=0;i<n;i++) sig[i]=1;
	for(i=0;i<ma;i++) ia[i]=1;

	lfit(x-1,y-1,sig-1,n,a-1,ia-1,ma,cov,&chisq,func);

	Free_ConvertMatrix(cov,1,ma,1,ma);
	Free_RVector(sig);
	Free_IVector(ia);
}

/////////////////////////////////////////////////////////////////////////
// (C) Copr. 1986-92 Numerical Recipes Software 31a
void lfit(REAL x[], REAL y[], REAL sig[], int ndat, REAL a[], int ia[],
	int ma, REAL **covar, REAL *chisq, void (*func)(REAL, REAL [], int))
{
	void covsrt(REAL **covar, int ma, int ia[], int mfit);
	void gaussj(REAL **a, int n, REAL **b, int m);
	int i,j,k,l,m,mfit=0;
	REAL ym,wt,sum,sig2i,**beta,*afunc;

	beta=RMatrix(1,ma,1,1);
	afunc=RVector(1,ma);
	for(j=1;j<=ma;j++)
		if(ia[j]) mfit++;
	if(mfit == 0) ErrorMsg("lfit: no parameters to be fitted");
	for(j=1;j<=mfit;j++) 
	{
		for(k=1;k<=mfit;k++) covar[j][k]=0.0;
		beta[j][1]=0.0;
	}
	for(i=1;i<=ndat;i++) 
	{
		(*func)(x[i],afunc+1,ma);//+1
		ym=y[i];
		if(mfit < ma) 
		{
			for(j=1;j<=ma;j++)
				if(!ia[j]) ym -= a[j]*afunc[j];
		}
		sig2i=1.0/SQR(sig[i]);
		for(j=0,l=1;l<=ma;l++) 
		{
			if(ia[l]) {
				wt=afunc[l]*sig2i;
				for(j++,k=0,m=1;m<=l;m++)
					if(ia[m]) covar[j][++k] += wt*afunc[m];
				beta[j][1] += ym*wt;
			}
		}
	}
	for(j=2;j<=mfit;j++)
		for(k=1;k<j;k++)
			covar[k][j]=covar[j][k];

	gaussj(covar,mfit,beta,1);
	for(j=0,l=1;l<=ma;l++)
		if(ia[l]) a[l]=beta[++j][1];
	*chisq=0.0;
	for(i=1;i<=ndat;i++) 
	{
		(*func)(x[i],afunc+1,ma);//+1
		for(sum=0.0,j=1;j<=ma;j++) sum += a[j]*afunc[j];
		*chisq+= SQR((y[i]-sum)/sig[i]);
	}
	covsrt(covar,ma,ia,mfit);
	Free_RVector(afunc,1,ma);
	Free_RMatrix(beta,1,ma,1,1);
}

/////////////////////////////////////////////////////////////////////////
//
void gaussj(REAL **a, int n, REAL **b, int m)
{
	int *indxc,*indxr,*ipiv;
	int i,icol,irow,j,k,l,ll;
	REAL big,dum,pivinv;

	indxc=IVector(1,n);
	indxr=IVector(1,n);
	ipiv=IVector(1,n);
	for(j=1;j<=n;j++) ipiv[j]=0;
	for(i=1;i<=n;i++) 
	{
		big=0.0;
		for(j=1;j<=n;j++)
			if(ipiv[j] != 1)
				for(k=1;k<=n;k++) 
				{
					if(ipiv[k] == 0) 
					{
						if(fabs(a[j][k]) >= big) 
						{
							big=fabs(a[j][k]);
							irow=j;
							icol=k;
						}
					} 
					else if(ipiv[k] > 1) ErrorMsg("gaussj: Singular Matrix-1");
				}
		++(ipiv[icol]);
		if(irow != icol) 
		{
			for(l=1;l<=n;l++) SWAP(a[irow][l],a[icol][l])
			for(l=1;l<=m;l++) SWAP(b[irow][l],b[icol][l])
		}
		indxr[i]=irow;
		indxc[i]=icol;
		if(a[icol][icol] == 0.0) ErrorMsg("gaussj: Singular Matrix-2");
		pivinv=1.0/a[icol][icol];
		a[icol][icol]=1.0;
		for(l=1;l<=n;l++) a[icol][l] *= pivinv;
		for(l=1;l<=m;l++) b[icol][l] *= pivinv;
		for(ll=1;ll<=n;ll++)
			if(ll != icol) {
				dum=a[ll][icol];
				a[ll][icol]=0.0;
				for(l=1;l<=n;l++) a[ll][l] -= a[icol][l]*dum;
				for(l=1;l<=m;l++) b[ll][l] -= b[icol][l]*dum;
			}
	}
	for(l=n;l>=1;l--) 
	{
		if(indxr[l] != indxc[l])
			for(k=1;k<=n;k++)
				SWAP(a[k][indxr[l]],a[k][indxc[l]]);
	}
	Free_IVector(ipiv,1,n);
	Free_IVector(indxr,1,n);
	Free_IVector(indxc,1,n);
}

/////////////////////////////////////////////////////////////////////////
//
void covsrt(REAL **covar, int ma, int ia[], int mfit)
{
	int i,j,k;

	for(i=mfit+1;i<=ma;i++)
		for(j=1;j<=i;j++) covar[i][j]=covar[j][i]=0.0;
	k=mfit;
	for(j=ma;j>=1;j--) 
	{
		if(ia[j]) 
		{
			for(i=1;i<=ma;i++) SWAP(covar[i][k],covar[i][j])
			for(i=1;i<=ma;i++) SWAP(covar[k][i],covar[j][i])
			k--;
		}
	}
}
