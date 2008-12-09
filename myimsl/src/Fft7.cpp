/////////////////////////////////////////////////////////////////////////
// Program  : fft.cpp
//            Fourier transform of a real signal
//
#include <math.h>
#include "imsl.h"

/////////////////////////////////////////////////////////////////////////
//  Perform a 2D FFT inplace given a 2D array x[nr][nc]+jy[nr][nc]
//  The direction dir, 1 for forward, -1 for reverse
//  Return if there are memory problems or the dimensions are not powers of 2
//
void _FFT2(REAL **x,REAL **y,int nr,int nc,int dir)
{
   int i,j,m;
   REAL *real,*imag,p;

   /* Transform the columns */
   real= new REAL [nc];
   imag= new REAL [nc];
   if (!real || !imag)
		ErrorMsg ("Error in 'FFT2': Allocation failure");
	p= frexp((REAL)nc, &m); 
	if(p != 0.5) 
		ErrorMsg ("Error in 'FFT2': Dimensions are not powers of 2");
	else
		m--;

   for (j=0;j<nr;j++) 
   {
      for (i=0;i<nc;i++) 
	  {
         real[i]= x[j][i];
         imag[i]= y[j][i];
      }
      _FFT(real,imag,nc,dir);
      for (i=0;i<nc;i++) 
	  {
         x[j][i]= real[i];
         y[j][i]= imag[i];
      }
   }
   delete []real;
   delete []imag;

   /* Transform the rows */
   real= new REAL [nr];
   imag= new REAL [nr];
   if (!real || !imag)
		ErrorMsg ("Error in 'FFT2': Allocation failure");
	p= frexp((REAL)nr, &m);
	if(p != 0.5) 
		ErrorMsg ("Error in 'FFT2': Dimensions are not powers of 2");
	else
		m--;
   for (i=0;i<nc;i++) 
   {
      for (j=0;j<nr;j++) 
	  {
         real[j]= x[j][i];
         imag[j]= y[j][i];
      }
      _FFT(real,imag,nr,dir);
      for (j=0;j<nr;j++) 
	  {
         x[j][i]= real[j];
         y[j][i]= imag[j];
      }
   }
   delete []real;
   delete []imag;

   return;
}

/////////////////////////////////////////////////////////////////////////
// Perform a 1D FFT inplace given a array x[]+jy[]
void _FFT(REAL *x,REAL *y,int nn,int dir)
{
	int m;
   long i,i1,j,k,i2,l,l1,l2;
   REAL c1,c2,tx,ty,t1,t2,u1,u2,z,p;

   /* Calculate the number of points */
	p= frexp((REAL)nn, &m);
	m--;

   /* Do the bit reversal */
   i2 = nn >> 1;
   j = 0;
   for (i=0;i<nn-1;i++) {
      if (i < j) {
         tx = x[i];
         ty = y[i];
         x[i] = x[j];
         y[i] = y[j];
         x[j] = tx;
         y[j] = ty;
      }
      k = i2;
      while (k <= j) {
         j -= k;
         k >>= 1;
      }
      j += k;
   }

   /* Compute the FFT */
   c1 = -1.0;
   c2 = 0.0;
   l2 = 1;
   for (l=0;l<m;l++) {
      l1 = l2;
      l2 <<= 1;
      u1 = 1.0;
      u2 = 0.0;
      for (j=0;j<l1;j++) {
         for (i=j;i<nn;i+=l2) {
            i1 = i + l1;
            t1 = u1 * x[i1] - u2 * y[i1];
            t2 = u1 * y[i1] + u2 * x[i1];
            x[i1] = x[i] - t1;
            y[i1] = y[i] - t2;
            x[i] += t1;
            y[i] += t2;
         }
         z =  u1 * c1 - u2 * c2;
         u2 = u1 * c2 + u2 * c1;
         u1 = z;
      }
      c2 = sqrt((1.0 - c1) / 2.0);
      if (dir == 1)
         c2 = -c2;
      c1 = sqrt((1.0 + c1) / 2.0);
   }

   /* Scaling for forward transform */
   if (dir == 1) {
      for (i=0;i<nn;i++) {
         x[i] /= (REAL)nn;
         y[i] /= (REAL)nn;
      }
   }

   return;
}

/////////////////////////////////////////////////////////////////////////
//
void _FFT(REAL *x,REAL *y,int nn)
{
	int m, dir=1;
   long i,i1,j,k,i2,l,l1,l2;
   REAL c1,c2,tx,ty,t1,t2,u1,u2,z,p;

   /* Calculate the number of points */
	p= frexp((REAL)nn, &m);
	m--;

   /* Do the bit reversal */
   i2 = nn >> 1;
   j = 0;
   for (i=0;i<nn-1;i++) {
      if (i < j) {
         tx = x[i];
         ty = y[i];
         x[i] = x[j];
         y[i] = y[j];
         x[j] = tx;
         y[j] = ty;
      }
      k = i2;
      while (k <= j) {
         j -= k;
         k >>= 1;
      }
      j += k;
   }

   /* Compute the FFT */
   c1 = -1.0;
   c2 = 0.0;
   l2 = 1;
   for (l=0;l<m;l++) {
      l1 = l2;
      l2 <<= 1;
      u1 = 1.0;
      u2 = 0.0;
      for (j=0;j<l1;j++) {
         for (i=j;i<nn;i+=l2) {
            i1 = i + l1;
            t1 = u1 * x[i1] - u2 * y[i1];
            t2 = u1 * y[i1] + u2 * x[i1];
            x[i1] = x[i] - t1;
            y[i1] = y[i] - t2;
            x[i] += t1;
            y[i] += t2;
         }
         z =  u1 * c1 - u2 * c2;
         u2 = u1 * c2 + u2 * c1;
         u1 = z;
      }
      c2 = sqrt((1.0 - c1) / 2.0);
      if (dir == 1)
         c2 = -c2;
      c1 = sqrt((1.0 + c1) / 2.0);
   }

   /* Scaling for forward transform */
   if (dir == 1) {
      for (i=0;i<nn;i++) {
         x[i] /= (REAL)nn;
         y[i] /= (REAL)nn;
      }
   }

   return;
}

