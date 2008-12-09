/////////////////////////////////////////////////////////////////////////
// Program  : freqres.cpp
//            Draw the amplitude and phase diagrams of a system
//            G(jw)= 1/(a1+jw)(a2+jw)
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 17/05/2003
//
#include <math.h>
#include "plplot.h"
#include "complex.h"

void main(void)
{
	int i, s=0, s1=0;
  REAL a1= 1.0, a2= 2.0, freq, freql, ampl, pha;
	COMPLEX z1,z2,z;

 	plsdev("win3");	
  plinit();
//  plfont(3);
  pladv(0);

  plvpor(0.15, 0.85, 0.15, 0.85);
  plwind(-2.0, 3.0, -80.0, 10.0);    // window for amplitude
  plcol0(7);
	plbox("bclnst", 0.0, 0, "bnstv", 0.0, 0);
  plcol0(1);
  plmtex("t", 2.0, 0.5, 0.5, "G(s)= 1/(a1+s)(a2+s)");
  plcol0(1);
  plmtex("b", 3.2, 0.5, 0.5, "Frequency");
  plmtex("l", 5.0, 0.5, 0.5, "Amplitude(dB)");

	plcol0(7);
	plwind(-2.0, 3.0, -180.0, 0.0);    // window for phase
	plbox("", 0.0, 0, "cmstv", 60.0, 3);
	plcol0(1);
	plmtex("r", 5.0, 0.5, 0.5, "Phase shift(degrees)");

  for(i= 0; i <= 100; i++) 
	{
		freql= -2.0 + i / 20.0;  
		freq= pow(10.0, freql); 
		z1.Set(a1, freq);
		z2.Set(a2, freq);
		z= 1/(z1*z2);
		ampl= 20.0*log10(abs(z));
		pha= 180.0/PI*phase(z);
		plwind(-2.0, 3.0, -80.0, 10.0);  // window for amplitude
		plline1(0, freql, ampl, &s, 2);
		plwind(-2.0, 3.0, -180.0, 0.0);  // window for phase
		plline1(1, freql, pha, &s1, 3);
	}		
  
	plend();
	return;
}
