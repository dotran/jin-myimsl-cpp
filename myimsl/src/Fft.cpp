/////////////////////////////////////////////////////////////////////////
// Program  : fft.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include <math.h>
#include "cmatrix.h"

/////////////////////////////////////////////////////////////////////////
// Fourier transform
void ms_Fft(REAL data[], int n)
{
	int nu, isign= 1;
	REAL p;
	void realft(REAL data[], int n, int isign);

	p= (REAL)frexp((double)n, &nu);
	if(p != 0.5) ErrorMsg("Data error in 'Fft': use n, a power of 2");

	realft(data-1, n, isign); // pointer must be data-1
	return;
}

/////////////////////////////////////////////////////////////////////////
// Fourier transform
CVECTOR ms_Fft(const RVECTOR &data, REAL fs)
{
	int nu, n= data.num, isign= 1;
	REAL p, *rdata;
	void realft(REAL data[], int n, int isign);

	p= (REAL)frexp((double)n, &nu);
	if(p != 0.5) ErrorMsg("Data error in 'Fft': use n, a power of 2");
	rdata= RVector(n);
	CVECTOR cdata(n/2);
	Vector2Array(data,rdata);

	realft(rdata-1, n, isign); // pointer must be data-1

	if(fs <= 0) 
		Array2Vector(rdata,cdata);
	else
	{
		for(int i=0; i<n/2; i++)
		{
			cdata(i).Re= sqrt(rdata[2*i]*rdata[2*i]+rdata[2*i+1]*rdata[2*i+1])/fs;
			cdata(i).Im= i*fs/n;
		}
	}
	Free_RVector(rdata);
	return cdata;
}

/////////////////////////////////////////////////////////////////////////
// Fourier transform
void ms_Fft(REAL data[], int n, REAL fs)
{
	int i, nhalf, nu, isign= 1;
	REAL p, *amp;
	void realft(REAL data[], int n, int isign);

	p= (REAL)frexp((double)n, &nu);
	if(p != 0.5) ErrorMsg("Error in 'Fft': use n, power of 2");
	if(fs <= 0.0) ErrorMsg("Error in 'Fft': use a positive fs");

	realft(data-1, n, isign); // pointer must be data-1
	nhalf= n/2;
	amp= ms_RVector(nhalf);
	for(i=0; i<nhalf; i++)
	{
		amp[i]= sqrt(data[2*i]*data[2*i]+data[2*i+1]*data[2*i+1])/fs;
		data[i]= i*fs/n;
	}
	for(i=0; i<nhalf; i++)
		data[nhalf+i]= amp[i];
	ms_Free_RVector(amp);
	return;
}

/////////////////////////////////////////////////////////////////////////
// Inverse Fourier transform
void ms_IFft(REAL data[], int n)
{
	int nu, isign= -1;
	REAL p;
	void realft(REAL data[], int n, int isign);

	p= (REAL)frexp((double)n, &nu);
	if(p != 0.5) ErrorMsg("Data error in 'Fft': use n, a power of 2");

	realft(data-1, n, isign);
	for(int i=0; i<n; i++)
		data[i]= 2.0*data[i]/n;
	return;
}

void four1(REAL data[], int nn, int isign)
{
	int n,mmax,m,j,istep,i;
	double wtemp,wr,wpr,wpi,wi,theta;
	REAL tempr,tempi;

	n= nn << 1;
	j= 1;
	for(i=1;i<n;i+=2) 
	{
		if (j > i) 
		{
			SWAP(data[j],data[i]);
			SWAP(data[j+1],data[i+1]);
		}
		m=n >> 1;
		while (m >= 2 && j > m)
		{
			j -= m;
			m >>= 1;
		}
		j += m;
	}
	mmax= 2;
	while(n > mmax) 
	{
		istep= mmax << 1;
		theta= isign*(6.28318530717959/mmax); 
		wtemp= sin(0.5*theta);
		wpr= -2.0*wtemp*wtemp;
		wpi= sin(theta);
		wr= 1.0;
		wi= 0.0;
		for(m=1;m<mmax;m+=2) 
		{
			for(i=m;i<=n;i+=istep) 
			{
				j= i+mmax;
				tempr= wr*data[j]-wi*data[j+1];
				tempi= wr*data[j+1]+wi*data[j];
				data[j]= data[i]-tempr;
				data[j+1]= data[i+1]-tempi;
				data[i] += tempr;
				data[i+1] += tempi;
			}
			wr= (wtemp=wr)*wpr-wi*wpi+wr;
			wi= wi*wpr+wtemp*wpi+wi;
		}
		mmax= istep;
	}
}

/////////////////////////////////////////////////////////////////////////
// (C) Copr. 1986-92 Numerical Recipes Software
void realft(REAL data[], int n, int isign)
{
	int i,i1,i2,i3,i4,np3;
	REAL c1=0.5,c2,h1r,h1i,h2r,h2i;
	double wr,wi,wpr,wpi,wtemp,theta;
	void four1(REAL data[], int nn, int isign);

	theta= 3.141592653589793/(double)(n>>1);
	if(isign == 1) 
	{
		c2= -0.5;
		four1(data,n>>1,1);
	} 
	else 
	{
		c2= 0.5;
		theta= -theta;
	}
	wtemp= sin(0.5*theta);
	wpr= -2.0*wtemp*wtemp;
	wpi= sin(theta);
	wr= 1.0+wpr;
	wi= wpi;
	np3= n+3;
	for(i=2;i<=(n>>2);i++) 
	{
		i4= 1+(i3=np3-(i2=1+(i1=i+i-1)));
		h1r= c1*(data[i1]+data[i3]);
		h1i= c1*(data[i2]-data[i4]);
		h2r= -c2*(data[i2]+data[i4]);
		h2i= c2*(data[i1]-data[i3]);
		data[i1]= h1r+wr*h2r-wi*h2i;
		data[i2]= h1i+wr*h2i+wi*h2r;
		data[i3]= h1r-wr*h2r+wi*h2i;
		data[i4]= -h1i+wr*h2i+wi*h2r;
		wr= (wtemp=wr)*wpr-wi*wpi+wr;
		wi= wi*wpr+wtemp*wpi+wi;
	}
	if (isign == 1) 
	{
		data[1]= (h1r=data[1])+data[2];
		data[2]= h1r-data[2];
	} 
	else 
	{
		data[1]= c1*((h1r=data[1])+data[2]);
		data[2]= c1*(h1r-data[2]);
		four1(data,n>>1,-1);
	}
}
/////////////////////////////////////////////////////////////////////////
// open Software
void ms_Fft(REAL real_data[], REAL imag_data[], int n_pts)
{
	int n2, j, l, i, ib, k, k1, k2, sgn, nu, inv= 0;
	REAL tr, ti, arg, nu1, p;	/* intermediate values in calcs. */
	REAL c, s;	       /* cosine & sine components of Fourier trans. */
	int bit_swap(int i, int nu);

	p= (REAL)frexp((double)n_pts, &nu);
	if(p != 0.5) ErrorMsg("Data error in 'fft': n is not a power of 2");

	nu= nu-1;
	n2= n_pts / 2;
	nu1= nu - 1.0;
	k= 0;

	// sign change for inverse transform 
	sgn= inv ? -1 : 1;		

	// Calculate the componets of the Fourier series of the function
	for(l= 0; l != nu; l++ )
  {
    do
    {
      for(i= 0; i != n2; i++ )
      {
        j= (int)(k/(pow( 2.0, nu1)));
        ib= bit_swap( j, nu );
        arg= 2.0 * PI * ib / n_pts;
        c= cos( arg );
        s= sgn * sin( arg );
        k1= k;
        k2= k1 + n2;

        tr= real_data[k2] * c + imag_data[k2] * s;
        ti= imag_data[k2] * c - real_data[k2] * s;
        real_data[k2]= real_data[k1] - tr;
        imag_data[k2]= imag_data[k1] - ti;
        real_data[k1]= real_data[k1] + tr;
        imag_data[k1]= imag_data[k1] + ti;                      
        k++;
      }
      k +=  n2;
    } while(k < n_pts - 1);
    k= 0;
    nu1 -= 1.0;
    n2 /= 2;
  }
	for(k= 0; k != n_pts; k++ )
	{
    ib= bit_swap( k, nu );
    if(ib > k)
    {
			SWAP(real_data[k], real_data[ib] );
      SWAP(imag_data[k], imag_data[ib] );
    }
	}

// If calculating the inverse transform, must divide the data by the number of
// data points.
	if(inv)
    for(k= 0; k < n_pts; k++)
    {
			real_data[k] /= n_pts;
      imag_data[k] /= n_pts;
    } 
}

/////////////////////////////////////////////////////////////////////////
// Bit swaping routine in which the bit pattern of the integer i is reordered.
int bit_swap(int i, int nu)
{
	int j, ib, i2;

	ib= 0;
  for(j= 0; j < nu; j++ )
  {
    i2= i / 2;
    ib= ib * 2 + (i - 2 * i2);
    i= i2;
  }
  return ib;
}

