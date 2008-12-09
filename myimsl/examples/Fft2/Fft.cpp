/////////////////////////////////////////////////////////////////////////
// Program  : fft.cpp
//            Fourier transform of a real 2D signal
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 15/08/2003
//
#include <math.h>
#include "plplot.h"
#include "imsl.h"

void main(void)
{
	int i, j,nr=128,nc=128, nrhalf, nchalf, s=0, s1=0, s2=0;
	REAL xfs, yfs, xs, ys, **zreal, **zimag, *x, *y;
	
	nr= NextPow2(nr);       // if nr and nc are not power of 2, they are changed nearest integer to nr or nc
	nc= NextPow2(nc);			
	x= RVector(nc);
	y= RVector(nr);
	zreal= RMatrix(nr,nc);
	zimag= RMatrix(nr,nc);
	xs= 0.05;					// sampling time
	ys= 0.05;					// sampling time
	xfs= 1/xs;              // sampling frequency
	yfs= 1/ys;              // sampling frequency
	for(i=0; i<nr; i++)
	{

		y[i]= ys*i;
		for(j=0; j<nc; j++)
		{
			x[j]= xs*j;
			zreal[i][j]=cos(2*3.1415*2.1*x[j])+cos(2*3.1415*5.7*y[i]);
			zimag[i][j]=0;
		}
	}
	nchalf= nc/2;
	nrhalf= nr/2;

	// draws #1 subgraph
	plsdev("win3");	
	plinit();
	plssub(2,1);
	pladv(0);
	plvpor(0.0, 1.0, 0.0, 1.0);
	plwind(-1.0, 1.0, -2, 3);
//	plMinMax2dGrid(zreal, nr, nc, &zmax, &zmin);  
	plw3d(0.8, 1.0, 1.2, 0, 15, 0, 15, -2, 2, 20.0, 25.0);
	plcol0(1);
	plbox3("bnstu", "x axis", 0.0, 2,"bnstu", "y axis", 0.0, 2,
	     "bcdmnstuv", "z axis", 0.0, 2);
	plcol0(2);
	plmesh(x, y, zreal, nc, nr, 3);

	// FFT returning with complex results
	Fft2(zreal, zimag, nr, nc,1); 

	// draws #2 subgraph
	for(i=0; i<nrhalf; i++)
	{
		y[i]= i*ys/nr;
		for(j=0; j<nchalf; j++)
		{
			x[j]= j*xs/nc;
			zreal[i][j]=sqrt(zreal[i][j]*zreal[i][j]+zimag[i][j]*zimag[i][j]);
		}
	}
	pladv(2);
	plvpor(0.0, 1.0, 0.0, 1.0);
	plwind(-1.0, 1.0, -2, 3.0);
//	plMinMax2dGrid(z, n, m, &zmax, &zmin);  
	plw3d(0.8, 1.0, 1.2, 0, 10,0, 10, 0, 1, 20.0, 25.0);
	plcol0(1);
	plbox3("bnstu", "x axis", 0.0, 2,"bnstu", "y axis", 0.0, 2,
	     "bcdmnstuv", "z axis", 0.0, 2);

	plcol0(2);
	plmesh(x, y, zreal, nchalf, nrhalf, 3);

	plend();
	return;
}

