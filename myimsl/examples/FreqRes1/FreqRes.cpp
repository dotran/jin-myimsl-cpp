/////////////////////////////////////////////////////////////////////////
// Program  : freqres.cpp
//            Draw the amplitude and phase diagrams of a system
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 17/05/2003
//
#include <math.h>
#include "plplot.h"
#include "imsl.h"
#include "complex.h"

void main(void)
{
	int i, n=100;
  REAL a= 1.0, freq, *freql, *ampl, *pha;
	COMPLEX z1,z;

  freql= RVector(n);
	ampl= RVector(n);
	pha= RVector(n);
	LinSpace(-2, 3, n, freql);
  for(i= 0; i < n; i++) {
		freq= pow(10.0, freql[i]);
		z1.Set(a, freq);
 		z= 1/z1;
		ampl[i]= 20.0*log10(abs(z));
		pha[i]= 180.0/PI*phase(z);
	}		

	plsdev("win3");	
  plinit();
  pladv(0);

  plvpor(0.15, 0.85, 0.55, 0.9);
  plwind(-2.0, 3.0, -80.0, 10.0);
  plcol0(7);
	plbox("bcfghlnst", 0.0, 0, "bcghnstv", 0.0, 0);
	plcol0(1);
  plmtex("t", 2.0, 0.5, 0.5, "G(s)= 1/(s+a)");
  plmtex("b", 3.2, 0.5, 0.5, "Freq(rad/sec)");
  plmtex("l", 5.0, 0.5, 0.5, "Amplitude(dB)");
  plcol0(2);
	plline(n, freql, ampl);
  plcol0(3);
  plptex(1.6, -25.0, 1.0, -20.0, 0.5, "-20 dB/decade");

  plvpor(0.15, 0.85, 0.1, 0.45);
	plwind(-2.0, 3.0, -100.0, 10.0);
	plcol0(7);
	plbox("bcfghlnst", 0.0, 0, "bcghnstv", 0.0, 0);
	plcol0(1);
  plmtex("b", 3.2, 0.5, 0.5, "Freq(rad/sec)");
	plmtex("l", 5.0, 0.5, 0.5, "Phase(degrees)");
  plcol0(2);
	plline(n, freql, pha);
  
	plend();
	Free_RVector(freql);
	Free_RVector(ampl);
	Free_RVector(pha);
	return;
}
