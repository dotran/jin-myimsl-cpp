/////////////////////////////////////////////////////////////////////////
// Program  : fft.cpp
//            Fourier transform of a real noise-contaminated signal 
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 15/08/2003
//
#include "plplot.h"
#include "cmatrix.h"
#include "imsl.h"
#include "diffeqs.h"

void main(void)
{
  int i, n= 600, nhalf, s= 0, s1= 0, s2= 0, s3=0;
	REAL pb[]= {0, 0, 1}, pa[]= {1, 0.3, 1};
	REAL t, h= 0.05, u, y, fs, amp, freq, *tt, *xreal, *ximag, *zreal, *zimag;
	DIFFEQS plant;
	
	n= NextPow2(n);     // nearest integer to n and power of 2
	tt= RVector(n);
	xreal= RVector(n); 
	ximag= RVector(n); 
	zreal= RVector(n); 
	zimag= RVector(n); 
	fs= 1/h;              // sampling frequency[Hz]
	nhalf= n/2;

	t= 0.0; u= 1.0;
	for(i= 0; i < n; i++) 
	{
		y= LSim(plant, u, pb, pa, 2, t, h);
		t+= h;
		tt[i]= t;
		xreal[i]= y;
		ximag[i]= 0;
		zreal[i]= y+0.5*NormRnd(0.0,0.3); // Gaussian noise
		zimag[i]= 0;
	}

	plsdev("win3");	
	plinit();
	plssub(2,2);

	// draws #1 subgraph
	plcol0(7);
	plenv(0.0, n*h, 0.0, 2.0, 0, 0); 
	pllab("Time","Output","Step Response"); 
	for(i=0; i<n; i++)
		plline1(0, tt[i], xreal[i], &s, 2);

	// draws #2 subgraph
	pladv(1);
	plcol0(7);
	plenv(0.0, fs/2.0, 0.0, 1.0, 0, 0); 
	pllab("Frequency[Hz]","Amplitude","FFT of the original signal"); 

	Fft(xreal, ximag, n);    // FFT

	for(i=0; i<nhalf; i++)
	{
		freq= i*fs/n;
		amp= sqrt(xreal[i]*xreal[i]+ximag[i]*ximag[i]);
		plline1(1, freq, amp, &s1, 1); 
	}

	// draws #3 subgraph
	pladv(2);
	plcol0(7);
	plenv(0.0, n*h, 0.0, 2.0, 0, 0); 
	pllab("Time","Output","Step Response with Noise");
	plcol0(2);
	for(i=0; i<n; i++)
		plline1(2, tt[i], zreal[i], &s2, 2);

	// draws #4 subgraph
	pladv(3);
	plcol0(7);
	plenv(0.0, fs/2.0, 0.0, 1.0, 0, 0); 
	pllab("Frequency[Hz]","Amplitude","FFT of the noisy signal"); 

	Fft(zreal, zimag, n);    // FFT

	for(i=0; i<nhalf; i++)
	{
		freq= i*fs/n;
		amp= sqrt(zreal[i]*zreal[i]+zimag[i]*zimag[i]);
		plline1(3, freq, amp, &s3, 1); 
	}
	
	plend();
	Free_RVector(tt);
	Free_RVector(xreal);
	Free_RVector(ximag);
	Free_RVector(zreal);
	Free_RVector(zimag);
	return;
}
