/////////////////////////////////////////////////////////////////////////
// Program  : draw2d.cpp
//            Draw a 2-D histogram
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 20/10/2003
//
#include "stdafx.h"
#include "plplot.h"
#include "imsl.h"

void main(void)
{
	int i, n= 50000;
	REAL *data;

	data= RVector(n);
	plsdev("win3");	
	plinit();
	plssub(1,2);

// #1 subplot
	SRand(100);                   // resets the random number generator
	for(i=0; i<n; i++)
		data[i]= UnifRnd(-1.0,1.0); // uniform random number generator (a,b)

	plcol0(2);
	plhist(n, data, -1.0, 1.0, 101, 0);
	plcol0(3);
	pllab("#frValue", "#frFrequency","#frUniform distribution");

// #2 subplot
	pladv(1);
	for(i=0; i<n; i++)
		data[i]= NormRnd(0.0, 0.05); // Gaussian random number generator (ave, dev)

	plcol0(2);
	plhist(n, data, -3.0, 3.0, 101, 0);
	plcol0(3);
	pllab("Value", "Frequency","Normal distribution");

	plend();
	Free_RVector(data);
	return;
}
