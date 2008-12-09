/////////////////////////////////////////////////////////////////////////
// Program  : diffeqs.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 02/03/2003
//
#include <math.h>
#include "diffeqs.h"

///////////////////// implementation file of DIFFEQS class /////////////////////
// Constructors and Destructors
DIFFEQS::DIFFEQS(int n, int nd):maxn(n),maxnbuf(nd)
{
	int i;

	dy= new REAL[maxn];
	du= new REAL[maxn];
	x= new REAL[maxn];
	TimeDelayBuf= new REAL[maxnbuf+1];
	for(i=0; i<maxn; i++) 
	{
		dy[i]= 0;
		du[i]= 0;
		x[i]= 0;
	}
	idx= maxnbuf;
	for(i=0; i<maxnbuf; i++) 
		TimeDelayBuf[i]= 0;
}

DIFFEQS::~DIFFEQS(void)
{
	delete []dy;
	delete []du;
	delete []x;
	delete []TimeDelayBuf;
}

/////////////////////////////////////////////////////////////////////////
// Time delay implementation for discrete-time models
REAL DIFFEQS::TimeDelay(REAL u, int nd)
{
	int m;
	if(nd < 0)
		ErrorMsg("Error in 'TimeDelay': use nd >= 0");
	if(nd > maxnbuf)
		ErrorMsg("Error in 'TimeDelay': increase instance array buffer for time delay");

	if(idx<0)
		idx= maxnbuf;
	TimeDelayBuf[idx]= u;
	m= (idx+nd)%(maxnbuf+1);
	idx--;
	return TimeDelayBuf[m];
}

/////////////////////////////////////////////////////////////////////////
// Initialize the time delay buffer
void DIFFEQS::InitTimeDelay(REAL initvalue)
{
	for(int i=0; i<maxnbuf; i++)
		TimeDelayBuf[i]= initvalue;
	return;
}

/////////////////////////////////////////////////////////////////////////
// Sets the delayed signals and time delay buffers to the given values
void InitDSim(DIFFEQS &de, REAL du[], int m, REAL dy[], int n, REAL initvalue)
{	
	if(m > de.maxn || n > de.maxn)
		ErrorMsg("Error in 'InitDSim': check m or n");
	for(int i=0; i<m; i++) de.du[i]= du[i];
	for(i=0; i<n; i++) de.dy[i]= dy[i];
	for(i=0; i<de.maxnbuf; i++) de.TimeDelayBuf[i]= initvalue;
	return;
}

/////////////////////////////////////////////////////////////////////////
//  Implements a discrete-time model without/with time delay
REAL DSim(DIFFEQS &de, REAL u, REAL pb[], int m, REAL pa[], int n, int nd)
{
	int i;
	REAL y;
	
	if(n<1||m<1)
		ErrorMsg("Error in 'DSim': check n or m");
	if(n > de.maxn)
		ErrorMsg("Error in 'DSim': check n or increase instance array size");
	if(m > de.maxn)
		ErrorMsg("Error in 'DSim': check m or increase instance array size");
	if(pa[0]==0)
		ErrorMsg("Error in 'DSim': check pa[0]");
	if(nd > 0)
		u= de.TimeDelay(u, nd);

	for(i=m; i>0; i--)
		de.du[i]= de.du[i-1];
	de.du[0]= u;

	y= 0;
	for(i=0; i<m+1; i++)
		y+= pb[i]*de.du[i];

	for(i=1; i<n+1; i++)
		y-= pa[i]*de.dy[i];
	y/= pa[0];
	for(i=n; i>1; i--)
		de.dy[i]= de.dy[i-1];
	de.dy[1]= y;

	return y;
}
/////////////////////////////////////////////////////////////////////////
// Initialises the state variables and buffers of delayed signals to the given values
void InitLSim(DIFFEQS &de, REAL x[], int n, REAL initvalue)
{	
	int i;

	if(n > de.maxn)
		ErrorMsg("Error in 'InitLSim': check n");
	for(i=0; i<n; i++) de.x[i]= x[i];
	for(i=0; i<de.maxnbuf; i++) de.TimeDelayBuf[i]= initvalue;
	return;
}

/////////////////////////////////////////////////////////////////////////
//  Simulation of a system with time delay
REAL LSim(DIFFEQS &de, REAL u, REAL pb[], REAL pa[], int n, REAL t, REAL h, REAL L)
{
	int i, na, nd;
	REAL y= 0, temp;
	void ms_Derivs(REAL u, REAL x[], REAL pa[], int n, REAL t, REAL xdot[]);

	if(n < 1)
		ErrorMsg("Error in 'LSim': check n");
	na= n+1;
	if(pa[0]==0 || h==0)
		ErrorMsg("Error in 'LSim': check pa[0] or h");
	else
	{
		temp= pa[0];
		for(i=0; i<na; i++) 
		{
			pa[i]/= temp;
			pb[i]/= temp;
		}
	}
	if(L > 0)
	{
		nd= Round(L/h);
		u= de.TimeDelay(u,nd);
	}
	Rkqs(u, de.x, pa, n, t, h, ms_Derivs);
	y= pb[0]*u;
	for(i=0; i<n; i++)
		y+= (pb[na-1-i]-pa[na-1-i]*pb[0])*de.x[i];
	return y;
}

///////////////////////////////////////////////////////////////////
//   Function called by Rkqs in LSim
void ms_Derivs(REAL u, REAL x[], REAL pa[], int n, REAL t, REAL xdot[])
{
	int i;

	for(i=0; i<n-1; i++)
		xdot[i]= x[i+1];
	xdot[n-1]= u;
	for(i=0; i<n; i++)
		xdot[n-1]-= pa[n-i]*x[i];
	return;
}

/////////////////////////////////////////////////////////////////////////
//  Fifth-order Runge-Kutta formula with stepsize control which calls
//  the user-defined function "derivs"
#define SAFETY     0.9
#define PSHRNK   -0.25
#define PGROW     -0.2
#define ERRCON 1.89e-4
#define EPS     1.0e-5

void Rkqs(REAL u, REAL x[], int n, REAL t, REAL h,
		void (*derivs)(REAL u, REAL x[], int n, REAL t, REAL ak[]))
{
	int i;
	static REAL a2=0.2,a3=0.3,a4=0.6,a5=1.0,a6=0.875,b21=0.2,b31=3.0/40.0,
	 b32=9.0/40.0,b41=0.3,b42= -0.9,b43=1.2,b51= -11.0/54.0,b52=2.5,
	 b53=-70.0/27.0, b54=35.0/27.0,b61=1631.0/55296.0, b62=175.0/512.0,
	 b63=575.0/13824.0, b64=44275.0/110592.0, b65=253.0/4096.0,c1=37.0/378.0,
	 c3=250.0/621.0,c4=125.0/594.0,c6=512.0/1771.0,dc1=37.0/378.0-2825.0/27648.0,
	 dc3=250.0/621.0-18575.0/48384.0, dc4= 125.0/594.0-13525.0/55296.0,
	 dc5= -277.00/14336.0, dc6=512.0/1771.0-0.25;
	REAL errmax,htemp,hh,hnext,tnew;
	REAL *ak1, *ak2, *ak3, *ak4, *ak5, *ak6, *xerr, *xtemp;
	
	ak1= new REAL[n];
	ak2= new REAL[n];
	ak3= new REAL[n];
	ak4= new REAL[n];
	ak5= new REAL[n];
	ak6= new REAL[n];
	xerr= new REAL[n];
	xtemp= new REAL[n];
	hh= h;
	tnew= t+h;
	for(;;) {
		for(;;) {
			(*derivs)(u,x,n,t,ak1);
			for(i=0;i<n;i++)
				xtemp[i]= x[i]+b21*hh*ak1[i];
			(*derivs)(u,xtemp,n,t+a2*hh,ak2);
			for(i=0;i<n;i++)
				xtemp[i]= x[i]+hh*(b31*ak1[i]+b32*ak2[i]);
			(*derivs)(u,xtemp,n,t+a3*hh,ak3);
			for(i=0;i<n;i++)
				xtemp[i]= x[i]+hh*(b41*ak1[i]+b42*ak2[i]+b43*ak3[i]);
			(*derivs)(u,xtemp,n,t+a4*hh,ak4);
			for(i=0;i<n;i++)
				xtemp[i]= x[i]+hh*(b51*ak1[i]+b52*ak2[i]+b53*ak3[i]+b54*ak4[i]);
			(*derivs)(u,xtemp,n,t+a5*hh,ak5);
			for(i=0;i<n;i++)
				xtemp[i]= x[i]+hh*(b61*ak1[i]+b62*ak2[i]+b63*ak3[i]+b64*ak4[i]+b65*ak5[i]);
			(*derivs)(u,xtemp,n,t+a6*hh,ak6);
			for(i=0;i<n;i++)
				xtemp[i]= x[i]+hh*(c1*ak1[i]+c3*ak3[i]+c4*ak4[i]+c6*ak6[i]);
			for(i=0;i<n;i++)
				xerr[i]= hh*(dc1*ak1[i]+dc3*ak3[i]+dc4*ak4[i]+dc5*ak5[i]+dc6*ak6[i]);
			errmax= 0.0;
			for(i=0;i<n;i++) errmax=MAX(errmax,fabs(xerr[i]));
			errmax/= EPS;
			if(errmax <= 1.0) break;
			htemp= SAFETY*hh*pow(errmax,PSHRNK);
			hh= (hh >= 0.0) ? MAX(htemp,0.1*hh) : MIN(htemp,0.1*hh);
			if(t+hh == t) ErrorMsg("Error in 'RKQS':\nstepsize underflow");
		}
		for(i=0; i<n; i++) x[i]= xtemp[i];
		t+= hh;
		if(t >= tnew) break;
		if(errmax > ERRCON)
			hnext= SAFETY*hh*pow(errmax,PGROW);
		else
			hnext= 5.0*hh;
		hh= MIN(tnew-t,hnext);
	}
	delete []ak1;
	delete []ak2;
	delete []ak3;
	delete []ak4;
	delete []ak5;
	delete []ak6;
	delete []xerr;
	delete []xtemp;
	return;
}

/////////////////////////////////////////////////////////////////////////
//  Fifth-order Runge-Kutta formula with stepsize control which calls
//  the user-defined function "derivs"
void Rkqs(REAL u, REAL x[], REAL pa[], int n, REAL t, REAL h,
		void (*derivs)(REAL u, REAL x[], REAL pa[], int n, REAL t, REAL ak[]))
{
	int i;
	static REAL a2=0.2,a3=0.3,a4=0.6,a5=1.0,a6=0.875,b21=0.2,b31=3.0/40.0,
	 b32=9.0/40.0,b41=0.3,b42= -0.9,b43=1.2,b51= -11.0/54.0,b52=2.5,
	 b53=-70.0/27.0, b54=35.0/27.0,b61=1631.0/55296.0, b62=175.0/512.0,
	 b63=575.0/13824.0, b64=44275.0/110592.0, b65=253.0/4096.0,c1=37.0/378.0,
	 c3=250.0/621.0,c4=125.0/594.0,c6=512.0/1771.0,dc1=37.0/378.0-2825.0/27648.0,
	 dc3=250.0/621.0-18575.0/48384.0, dc4= 125.0/594.0-13525.0/55296.0,
	 dc5= -277.00/14336.0, dc6=512.0/1771.0-0.25;
	REAL errmax,htemp,hh,hnext,tnew;
	REAL *ak1, *ak2, *ak3, *ak4, *ak5, *ak6, *xerr, *xtemp;

	ak1= new REAL[n];
	ak2= new REAL[n];
	ak3= new REAL[n];
	ak4= new REAL[n];
	ak5= new REAL[n];
	ak6= new REAL[n];
	xerr= new REAL[n];
	xtemp= new REAL[n];
	hh= h;
	tnew= t+h;
	for(;;) {
		for(;;) {
			(*derivs)(u,x,pa,n,t,ak1);
			for(i=0;i<n;i++)
				xtemp[i]= x[i]+b21*hh*ak1[i];
			(*derivs)(u,xtemp,pa,n,t+a2*hh,ak2);
			for(i=0;i<n;i++)
				xtemp[i]= x[i]+hh*(b31*ak1[i]+b32*ak2[i]);
			(*derivs)(u,xtemp,pa,n,t+a3*hh,ak3);
			for(i=0;i<n;i++)
				xtemp[i]= x[i]+hh*(b41*ak1[i]+b42*ak2[i]+b43*ak3[i]);
			(*derivs)(u,xtemp,pa,n,t+a4*hh,ak4);
			for(i=0;i<n;i++)
				xtemp[i]= x[i]+hh*(b51*ak1[i]+b52*ak2[i]+b53*ak3[i]+b54*ak4[i]);
			(*derivs)(u,xtemp,pa,n,t+a5*hh,ak5);
			for(i=0;i<n;i++)
				xtemp[i]= x[i]+hh*(b61*ak1[i]+b62*ak2[i]+b63*ak3[i]+b64*ak4[i]+b65*ak5[i]);
			(*derivs)(u,xtemp,pa,n,t+a6*hh,ak6);
			for(i=0;i<n;i++)
				xtemp[i]= x[i]+hh*(c1*ak1[i]+c3*ak3[i]+c4*ak4[i]+c6*ak6[i]);
			for(i=0;i<n;i++)
				xerr[i]= hh*(dc1*ak1[i]+dc3*ak3[i]+dc4*ak4[i]+dc5*ak5[i]+dc6*ak6[i]);
			errmax= 0.0;
			for(i=0;i<n;i++) errmax=MAX(errmax,fabs(xerr[i]));
			errmax/= EPS;
			if(errmax <= 1.0) break;
			htemp= SAFETY*hh*pow(errmax,PSHRNK);
			hh= (hh >= 0.0) ? MAX(htemp,0.1*hh) : MIN(htemp,0.1*hh);
			if(t+hh == t) ErrorMsg("Error in 'RKQS':\nstepsize underflow");
		}
		for(i=0; i<n; i++) x[i]= xtemp[i];
		t+= hh;
		if(t >= tnew) break;
		if(errmax > ERRCON)
			hnext= SAFETY*hh*pow(errmax,PGROW);
		else
			hnext= 5.0*hh;
		hh= MIN(tnew-t,hnext);
	}
	delete []ak1;
	delete []ak2;
	delete []ak3;
	delete []ak4;
	delete []ak5;
	delete []ak6;
	delete []xerr;
	delete []xtemp;
	return;
}

#undef SAFETY
#undef PSHRNK
#undef PGROW
#undef ERRCON
#undef EPS

