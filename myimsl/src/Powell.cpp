/////////////////////////////////////////////////////////////////////////
// Program  : powell.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include <math.h>
#include "realtype.h"

#define ITMAX 200
void ms_Powell(REAL p[], int n, REAL ftol, int *iter, REAL *fret,
	REAL (*func)(REAL []))
{
	void linmin(REAL p[], REAL xi[], int n, REAL *fret,	REAL (*func)(REAL []));
	int i,ibig,j;
	REAL del,fp,fptt,t,*pt,*ptt,*xit,**xi;

	xi=RMatrix(1,n,1,n);
	pt= RVector(1,n);
	ptt=RVector(1,n);
	xit=RVector(1,n);
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			xi[i][j]=(i == j ? 1.0 : 0.0);

	*fret=(*func)(p); //
	for (j=1;j<=n;j++) pt[j]=p[j-1];//
	for (*iter=1;;++(*iter)) {
		fp=(*fret);
		ibig=0;
		del=0.0;
		for (i=1;i<=n;i++) {
			for (j=1;j<=n;j++) xit[j]=xi[j][i];
			fptt=(*fret);
			linmin(p-1,xit,n,fret,func); //
			if (fabs(fptt-(*fret)) > del) {
				del=fabs(fptt-(*fret));
				ibig=i;
			}
		}
		if (2.0*fabs(fp-(*fret)) <= ftol*(fabs(fp)+fabs(*fret))) {
			Free_RVector(xit,1,n);
			Free_RVector(ptt,1,n);
			Free_RVector(pt,1,n);
			Free_RMatrix(xi,1,n,1,n);
			return;
		}
		if (*iter == ITMAX) ErrorMsg("powell exceeding maximum iterations.");
		for (j=1;j<=n;j++) {
			ptt[j]=2.0*p[j-1]-pt[j]; //
			xit[j]=p[j-1]-pt[j]; //
			pt[j]=p[j-1]; //
		}
		fptt=(*func)(ptt+1); //
		if (fptt < fp) {
			t=2.0*(fp-2.0*(*fret)+fptt)*SQR(fp-(*fret)-del)-del*SQR(fp-fptt);
			if (t < 0.0) {
				linmin(p-1,xit,n,fret,func); //
				for (j=1;j<=n;j++) {
					xi[j][ibig]=xi[j][n];
					xi[j][n]=xit[j];
				}
			}
		}
	}
}
#undef ITMAX

/////////////////////////////////////////////////////////////////////////
// 
#define TOL 2.0e-4
int ncom;
REAL *pcom,*xicom,(*nrfunc)(REAL []);
void linmin(REAL p[], REAL xi[], int n, REAL *fret, REAL (*func)(REAL []))
{
	REAL brent(REAL ax, REAL bx, REAL cx,	REAL (*f)(REAL), REAL tol, REAL *xmin);
	void mnbrak(REAL *ax, REAL *bx, REAL *cx, REAL *fa, REAL *fb,
		REAL *fc, REAL (*func)(REAL));
	REAL f1dim(REAL x);
	int j;
	REAL xx,xmin,fx,fb,fa,bx,ax;

	ncom=n;
	pcom=RVector(1,n);
	xicom=RVector(1,n);
	nrfunc=func;
	for (j=1;j<=n;j++) {
		pcom[j]=p[j];
		xicom[j]=xi[j];
	}
	ax=0.0;
	xx=1.0;
	mnbrak(&ax,&xx,&bx,&fa,&fx,&fb,f1dim);
	*fret=brent(ax,xx,bx,f1dim,TOL,&xmin);
	for (j=1;j<=n;j++) {
		xi[j] *= xmin;
		p[j] += xi[j];
	}
	Free_RVector(xicom,1,n);
	Free_RVector(pcom,1,n);
}
#undef TOL


/////////////////////////////////////////////////////////////////////////
// 
#define ITMAX 100
#define CGOLD 0.3819660
#define ZEPS 1.0e-10
#define SHFT(a,b,c,d) (a)=(b);(b)=(c);(c)=(d);
REAL brent(REAL ax, REAL bx, REAL cx, REAL (*f)(REAL), REAL tol,
	REAL *xmin)
{
	int iter;
	REAL a,b,d,etemp,fu,fv,fw,fx,p,q,r,tol1,tol2,u,v,w,x,xm;
	REAL e=0.0;

	a=(ax < cx ? ax : cx);
	b=(ax > cx ? ax : cx);
	x=w=v=bx;
	fw=fv=fx=(*f)(x);
	for (iter=1;iter<=ITMAX;iter++) {
		xm=0.5*(a+b);
		tol2=2.0*(tol1=tol*fabs(x)+ZEPS);
		if (fabs(x-xm) <= (tol2-0.5*(b-a))) {
			*xmin=x;
			return fx;
		}
		if (fabs(e) > tol1) {
			r=(x-w)*(fx-fv);
			q=(x-v)*(fx-fw);
			p=(x-v)*q-(x-w)*r;
			q=2.0*(q-r);
			if (q > 0.0) p = -p;
			q=fabs(q);
			etemp=e;
			e=d;
			if (fabs(p) >= fabs(0.5*q*etemp) || p <= q*(a-x) || p >= q*(b-x))
				d=CGOLD*(e=(x >= xm ? a-x : b-x));
			else {
				d=p/q;
				u=x+d;
				if (u-a < tol2 || b-u < tol2)
					d=SIGN(tol1,xm-x);
			}
		} else {
			d=CGOLD*(e=(x >= xm ? a-x : b-x));
		}
		u=(fabs(d) >= tol1 ? x+d : x+SIGN(tol1,d));
		fu=(*f)(u);
		if (fu <= fx) {
			if (u >= x) a=x; else b=x;
			SHFT(v,w,x,u)
			SHFT(fv,fw,fx,fu)
		} else {
			if (u < x) a=u; else b=u;
			if (fu <= fw || w == x) {
				v=w;
				w=u;
				fv=fw;
				fw=fu;
			} else if (fu <= fv || v == x || v == w) {
				v=u;
				fv=fu;
			}
		}
	}
	ErrorMsg("Too many iterations in brent");
	*xmin=x;
	return fx;
}
#undef ITMAX
#undef CGOLD
#undef ZEPS
#undef SHFT

/////////////////////////////////////////////////////////////////////////
// 
#define GOLD 1.618034
#define GLIMIT 100.0
#define TINY 1.0e-20
#define SHFT(a,b,c,d) (a)=(b);(b)=(c);(c)=(d);
void mnbrak(REAL *ax, REAL *bx, REAL *cx, REAL *fa, REAL *fb, REAL *fc,
	REAL (*func)(REAL))
{
	REAL ulim,u,r,q,fu,dum;

	*fa=(*func)(*ax); //
	*fb=(*func)(*bx);//
	if (*fb > *fa) {
		SHFT(dum,*ax,*bx,dum)
		SHFT(dum,*fb,*fa,dum)
	}
	*cx=(*bx)+GOLD*(*bx-*ax);
	*fc=(*func)(*cx);
	while (*fb > *fc) {
		r=(*bx-*ax)*(*fb-*fc);
		q=(*bx-*cx)*(*fb-*fa);
		u=(*bx)-((*bx-*cx)*q-(*bx-*ax)*r)/
			(2.0*SIGN(MAX(fabs(q-r),TINY),q-r));
		ulim=(*bx)+GLIMIT*(*cx-*bx);
		if ((*bx-u)*(u-*cx) > 0.0) {
			fu=(*func)(u); //
			if (fu < *fc) {
				*ax=(*bx);
				*bx=u;
				*fa=(*fb);
				*fb=fu;
				return;
			} else if (fu > *fb) {
				*cx=u;
				*fc=fu;
				return;
			}
			u=(*cx)+GOLD*(*cx-*bx);
			fu=(*func)(u);
		} else if ((*cx-u)*(u-ulim) > 0.0) {
			fu=(*func)(u);
			if (fu < *fc) {
				SHFT(*bx,*cx,u,*cx+GOLD*(*cx-*bx))
				SHFT(*fb,*fc,fu,(*func)(u))
			}
		} else if ((u-ulim)*(ulim-*cx) >= 0.0) {
			u=ulim;
			fu=(*func)(u);
		} else {
			u=(*cx)+GOLD*(*cx-*bx);
			fu=(*func)(u);
		}
		SHFT(*ax,*bx,*cx,u)
		SHFT(*fa,*fb,*fc,fu)
	}
}
#undef GOLD
#undef GLIMIT
#undef TINY
#undef SHFT

/////////////////////////////////////////////////////////////////////////
// 
extern int ncom;
extern REAL *pcom,*xicom,(*nrfunc)(REAL []);
REAL f1dim(REAL x)
{
	int j;
	REAL f,*xt;

	xt=RVector(1,ncom);
	for (j=1;j<=ncom;j++) xt[j]=pcom[j]+x*xicom[j];
	f=(*nrfunc)(xt+1); //
	Free_RVector(xt,1,ncom);
	return f;
}
