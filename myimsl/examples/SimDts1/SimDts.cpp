/////////////////////////////////////////////////////////////////////////
// Program  : simdts.cpp
//            Step response of a 2nd-order discrete-timesystem
//            Y(s)/U(s)= 1/(s^2+s+1) => y(k)-1.94879y(k-1)+0.95123y(k-2)= 
//            0.001229u(k-1)+0.001209u(k-2) 
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 20/10/2003
//
#include "stdafx.h"
#include "plplot.h"
#include "diffeqs.h"

void main(void)
{
	int i, n= 2, ndata= 300, s= 0;
	REAL t, h= 0.05, u, y;
	REAL NZ[]= {0, 0.001229, 0.001209}, DZ[]= {1, -1.94879, 0.95123};
	DIFFEQS dte;

	plsdev("win3");
	plinit(); 
	plcol0(7);  
	plenv(0.0, 15.0, 0.0, 2.0, 0, 1);
	plcol0(1);
	pllab("Time","Output","Step Responses"); 
	t= 0.0; y= 0.0; 

	for(i= 0; i < ndata; i++) {
		u= 1.0;
		plline1(0, t, y, &s, 3); 
		y= DSim(dte, u, NZ, n, DZ, n);
		t+= h;
	}
	plend(); 
	return;
}