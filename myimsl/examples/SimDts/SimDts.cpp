/////////////////////////////////////////////////////////////////////////
// Program  : simdts.cpp
//            Step response of a 1st-order discrete-time system
//            Y(s)/U(s)= 1/(s+2) => y(k)-0.9608y(k-1)= 0.0196u(k-1) 
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 20/10/2003
//
#include "stdafx.h"
#include "plplot.h"
#include "diffeqs.h"

void main(void)
{
	int i, n= 1, ndata= 300, s= 0;
	REAL t, h= 0.02, u, y;
	REAL NZ[]= {0,0.0196}, DZ[]= {1, -0.9608};
	DIFFEQS dte;

	plsdev("win3");	
	plinit(); 
	plcol0(7);  
	plenv(0.0, 6.0, 0.0, 1.0, 0, 1); 
	plcol0(1);
	pllab("Time","Output","Step Responses"); 
	t= 0.0; y= 0.0; 

	for(i= 0; i < ndata; i++) {
		u= 1.0;
		plline1(0, t, y, &s1, 3); // draws discrete-time signals
		y= DSim(dte, u, NZ, n, DZ, n);
		t+= h;
	}
	plend();
	return;
}
