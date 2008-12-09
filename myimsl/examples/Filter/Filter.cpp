/////////////////////////////////////////////////////////////////////////
// Program  : filter.cpp
//            Implementation of a digital IIR/FIR filter
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 10/01/2004
//
#include <math.h>
#include "plplot.h"
#include "imsl.h"
#include "rmatrix.h"
void main(void)
{
  int i, n=3, ndata=100, s=0, s1=0;
	RVECTOR a(n+1),b(n+1),t(ndata),x(ndata),y(ndata);

	b= "0.0495 0.1486  0.1486 0.0495";
	a= "1.0000 -1.1619 0.6959 -0.1378";

	t= LinSpace(0,10,ndata);
	for(i=0; i<ndata; i++)
		x(i)= sin(2*t(i))+0.3*UnifRnd(-1,1);
	y= Filter(b,a,x);

	plsdev("win3");	
	plinit();
	plcol0(1);
	plenv(0, 10.0, -1.5, 1.5, 0, 0); 
	pllab("t","x(t)",""); 
	for(i=0; i<ndata; i++)
	{
		plline1(0, t(i), x(i), &s, 2);
		plline1(1, t(i), y(i), &s1, 3);
	}
  plend();
  return;
}