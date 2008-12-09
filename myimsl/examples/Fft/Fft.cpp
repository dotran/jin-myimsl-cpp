/////////////////////////////////////////////////////////////////////////
// Program  : fft.cpp
//            Fourier transform of a real signal
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 15/08/2003
//
#include "stdafx.h"
#include <math.h>
#include "plplot.h"
#include "imsl.h"
void main(void)
{
	int i, n, nhalf, s= 0, s1= 0;
	REAL *t, *x, *y, f0, f1, f2, fs, freq, h, ti, tf, amp;
	
	n= NextPow2(250);       // data number, near to 250 and power of 2
	t= RVector(n);
	x= RVector(n); 
	y= RVector(n); 

	ti= 0.0; tf= 1.0;
	LinSpace(ti, tf, n, t); // generates time array 
	h= (tf-ti)/(n-1);       // sampling time[sec]
	fs= 1.0/h;              // sampling frequency[Hz]
	f0= 10; f1= 31; f2= 67; // signal frequencies[Hz]
	for(i=0; i<n; i++) 
		x[i]= cos(2.0*PI*f0*t[i])+0.3*cos(2.0*PI*f1*t[i])+0.2*cos(2.0*PI*f2*t[i]);

	plsdev("win3");	
	plinit();
	plssub(1,2);

	// draws #1 subgraph
	plcol0(7);
	plenv(ti, tf, -1.5, 1.5, 0, 0); 
	pllab("t[sec]","f(t)",""); 
	for(i=0; i<n; i++)
		plline1(0, t[i], x[i], &s, 1); 

	Fft(x,y,n,1);            // Fourier transform

	// draws #2 subgraph
	pladv(1);
	plcol0(7);
	plenv(0.0, fs/2.0, 0.0, 1.0, 0, 0); 
	pllab("Frequency[Hz]","Amplitude",""); 

	nhalf= n >> 1;
	for(i=0; i<nhalf; i++)
	{
		freq= i*fs/n;
		amp= sqrt(x[i]*x[i]+y[i]*y[i]);
		plline1(1, freq, amp, &s1, 1); 
	}
	plend();
	Free_RVector(t);
	Free_RVector(x);
	Free_RVector(y);
	return;
}