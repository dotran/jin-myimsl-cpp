/////////////////////////////////////////////////////////////////////////
// Program  : simdts.cpp
//            Step response of a 2nd-order discrete-time system
//            with time delay
//            Y(s)/U(s)= exp(-0.1s)/(s^2+s+1) => y(k)-1.9488y(k-1)+0.9512y(k-2)= 
//            [0u(k)+0.0012u(k-1)+0.0012u(k-2)]z^-2
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 20/10/2003
//
#include "stdafx.h"
#include "plplot.h"
#include "diffeqs.h"

void main(void)
{
	int i, n= 2, nd, ndata= 300, s= 0;
	REAL t, h= 0.05, u, y, L= 0.1;
	REAL NZ[]= {0, 0.0012, 0.0012}, DZ[]= {1, -1.9488, 0.9512};
	DIFFEQS dte(2,10);  //(n, nd)  where nd > L/h
	
	plsdev("win3");	
	plinit(); 
	plcol0(7);  
	plenv(0.0, 15.0, 0.0, 2.0, 0, 1); 
	plcol0(1);
	pllab("Time","Output","Step Response"); 
	t= 0.0; y= 0.0; 
	nd= Round(L/h);

	for(i= 0; i < ndata; i++) {
		u= 1.0;
		plline1(0, t, y, &s, 3); 
		y= DSim(dte, u, NZ, n, DZ, n, nd);
		t+= h;
	}
	plend(); 
	return;
}	