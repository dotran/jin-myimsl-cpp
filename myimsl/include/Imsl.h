/////////////////////////////////////////////////////////////////////////
// Program  : imsl.h
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 02/03/2003
//
#ifndef _IMSL_H_
#define _IMSL_H_

#include "realtype.h"

/////////////////////////////////////////////////////////////////////////
// basic random number generators
double ms_Rand(void);                  // uniform random numbers distributed on the interval(0,1)
void ms_SRand(long n);                 // seed reset of the state of the current generator
void ms_SRands(long n);                // seed reset of the state of all the generators
void ms_SetRandState(int n);           // reset of the generator to its n-th state(0-255)
long ms_GetSeed(void);                 // gets the seed of the current generator

int ms_Flip();                         // flip 0 or 1
int ms_PickUp(int num);                // uniform random integer numbers with range 0..num-1
long ms_BernRnd(double p);             // Bernoulli random numbers, 0 or 1
double ms_UnifRnd(double a, double b); // uniform random numbers from specified distribution
double ms_NormRnd(double m, double s); // normal(Gaussian) random numbers
long ms_BinoRnd(long n, double p);     // Binomial random numbers
long ms_EquiRnd(long a, long b);       // Equilikely random numbers
long ms_GeoRnd(double p);              // Geometric random numbers
long ms_PasRnd(long n, double p);      // Pascal random numbers
long ms_PoissRnd(double m);            // Poisson random numbers
int ms_Prbs(long &seed);               // Pseudo random number sequence, 0 or 1
double ms_Chi2Rnd(long n);             // Chi square random numbers
double ms_ErlRnd(long n, double b);    // Erlang random numbers
double ms_ExpRnd(double m);            // Exponential random numbers
double ms_LognRnd(double a, double b); // Lognormal random numbers
double ms_StudRnd(long n);             // Student-t random numbers

// vectors and matrices
void ms_VInpt(int v[], long n1, long n2=0);
void ms_VInpt(REAL v[], long n1, long n2=0);
void ms_VOut(int v[], long n1, long n2=0);
void ms_VOut(REAL v[], long n1, long n2=0);
void ms_MInpt(int **a, long n1, long n2, long n3=0, long n4=0);
void ms_MInpt(REAL **a, long n1, long n2, long n3=0, long n4=0);
void ms_MOut(int **a, long n1, long n2, long n3=0, long n4=0);
void ms_MOut(REAL **a, long n1, long n2, long n3=0, long n4=0);

REAL ms_VMax(REAL v[], int n);
REAL ms_VMax(REAL v[], int n, int &iv);
REAL ms_VMin(REAL v[], int n);
REAL ms_VMin(REAL v[], int n, int &iv);
REAL ms_Sum(REAL v[], int n);

REAL ms_Mean(REAL v[], int n);
void ms_CumSum(REAL v[], int n, REAL cumv[]);
void ms_Sort(REAL a[], int n);
void ms_Sort(REAL a[], int n, int pos[]);
REAL ms_Norm1(REAL x[], int n);
REAL ms_Norm1(REAL **a, int n, int m);
REAL ms_Norm2(REAL x[], int n);
REAL ms_Norm2(REAL **a, int n, int m);
REAL ms_Norm8(REAL x[], int n);
REAL ms_Norm8(REAL **a, int n, int m);
void ms_LinSpace(REAL x1, REAL x2, int n, REAL x[]);
void ms_LogSpace(int d1, int d2, int n, REAL x[]);
void ms_LinSol(REAL **a, REAL b[], int n, REAL x[]);

// matrix
REAL ms_Det(REAL **a, int n);
void ms_Inv(REAL **a, int n, REAL **ia);

void ms_Fft(REAL data[], int n);
void ms_Fft(REAL data[], int n, REAL fs);
void ms_Fft(REAL real_data[], REAL imag_data[], int n_pts);
void ms_IFft(REAL data[], int n);
long ms_NextPow2(long n);
void ms_TStats(REAL t[],REAL y[],REAL yr,int n,REAL &mp,REAL &tp,REAL &tr,REAL &ts,REAL &ess, int opts=0);
//opts=0: 2% ts, otherwise: 5% ts
REAL ms_FZero(REAL (*func)(REAL), REAL x1, REAL x2);
REAL ms_FMin(REAL (*func)(REAL x), REAL x0, REAL dx);
void ms_Roots(REAL a[], int n, REAL rootr[], REAL rooti[]);
void ms_Eigen(REAL **a, int m, REAL rootr[], REAL rooti[]);
void ms_PolyFit(REAL x[], REAL y[], int n, REAL a[], int ma, 
		 REAL **covar, void (*func)(REAL x, REAL afunc[], int ma));
REAL ms_Spline(REAL xa[], REAL ya[], int n, REAL yp1, REAL ypn, REAL x);
long ms_Locate(REAL xx[], long n, REAL x);
void ms_Powell(REAL p[], int n, REAL ftol, int *iter, REAL *fret,
	REAL (*func)(REAL []));

// Numerical recipes in C
/*void ludcmp(REAL **a1, int n, int *indx1, REAL *d);
void lubksb(REAL **a1, int n, int *indx1, REAL *b1);
void ludcmp(REAL **a, int n, int *indx, REAL *d);
void lubksb(REAL **a, int n, int *indx, REAL *b);
void four1(REAL data[], int nn, int isign);
void realft(REAL data[], int n, int isign);
*/

#endif // _IMSL_H_
