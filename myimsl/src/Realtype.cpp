/////////////////////////////////////////////////////////////////////////
// Program  : realtype.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 02/03/2003
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "realtype.h"
#define NR_END 1

/////////////////////////////////////////////////////////////////////////
// Helper Error Function
void ErrorMsg (char *msg)
{
	printf("%s\n",msg);
  exit(1);
}

void WarningMsg (char *msg)
{
    printf("%s\n",msg);
}
/////////////////////////////////////////////////////////////////////////
// allocates an integer vector with subscript range v[0..n-1]
int* ms_IVector(long n)
{
	int* v= new int[n];
	if(!v) ErrorMsg("Error in 'IVector': Allocation failure");
	return v;
}

/////////////////////////////////////////////////////////////////////////
// allocates an integer vector with subscript range v[nl..nh]
int* ms_IVector(long nl, long nh)
{
	int* v= new int[nh-nl+1+NR_END];
	if(!v) ErrorMsg("Error in 'ivector': Allocation failure");
	return v-nl+NR_END;
}

/////////////////////////////////////////////////////////////////////////
// allocates a REAL vector with subscript range v[0..n-1]
REAL* ms_RVector(long n)
{
	REAL* v= new REAL[n];
	if(!v) ErrorMsg("Error in 'RVector': Allocation failure");
	return v;
}

/////////////////////////////////////////////////////////////////////////
// allocates a REAL vector with subscript range v[nl..nh]
REAL* ms_RVector(long nl, long nh)
{
	REAL* v= new REAL[nh-nl+1+NR_END];
	if(!v) ErrorMsg("Error in 'vector': Allocation failure");
	return v-nl+NR_END;
}

/////////////////////////////////////////////////////////////////////////
// allocates an integer matrix with subscript range mat[0..nr-1][0..nl-1]
int** ms_IMatrix(long nr, long nl)
{
	int** mat= new int* [nr];
	if(!mat) ErrorMsg("Error in 'IMatrix': Allocation failure");
	mat[0]= new int [nr*nl];
	if(!mat[0])	ErrorMsg("Error in 'IMatrix': Allocation failure");
  for(int i=1; i<nr; i++)
		mat[i]= mat[i-1]+nl;
	return mat;
}

/////////////////////////////////////////////////////////////////////////
// allocates a int matrix with subscript range m[nrl..nrh][ncl..nch]
int** ms_IMatrix(long nrl, long nrh, long ncl, long nch)
{
	long i, nrow=nrh-nrl+1, ncol=nch-ncl+1;

	// allocate pointers to rows 
	int** mat= new int* [nrow+NR_END];
	if(!mat) ErrorMsg("Error in 'imatrix': Allocation failure");
	mat+= NR_END;
	mat-= nrl;

	// allocate rows and set pointers to them
	mat[nrl]= new int [nrow*ncol+NR_END];
	if(!mat[nrl])	ErrorMsg("Error in 'imatrix': Allocation failure");
	mat[nrl]+= NR_END;
	mat[nrl]-= ncl;

	for(i=nrl+1; i<=nrh; i++) 
		mat[i]= mat[i-1]+ncol;
	return mat;
}

/////////////////////////////////////////////////////////////////////////
// allocates a REAL matrix with subscript range mat[0..nr-1][0..nl-1] 
REAL** ms_RMatrix(long nr, long nl)
{
	REAL** mat= new REAL* [nr];
	if(!mat) ErrorMsg("Error in 'RMatrix': Allocation failure");
	mat[0]= new REAL [nr*nl];
	if(!mat[0])	ErrorMsg("Error in 'RMatrix': Allocation failure");
  for(int i=1; i<nr; i++)
		mat[i]= mat[i-1]+nl;
	return mat;
}

/////////////////////////////////////////////////////////////////////////
// allocates a REAL matrix with subscript range mat[nrl..nrh][ncl..nch]
REAL** ms_RMatrix(long nrl, long nrh, long ncl, long nch)
{
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;

	// allocate pointers to rows 
	REAL** mat= new REAL* [nrow+NR_END];
	if(!mat) ErrorMsg("Error in 'matrix': Allocation failure");
	mat+= NR_END;
	mat-= nrl;

	/* allocate rows and set pointers to them */
	mat[nrl]= new REAL [nrow*ncol+NR_END];
	if(!mat[nrl])	ErrorMsg("Error in 'matrix': Allocation failure");
	mat[nrl]+= NR_END;
	mat[nrl]-= ncl;

	for(i=nrl+1; i<=nrh; i++) 
		mat[i]= mat[i-1]+ncol;
	return mat;
}

/////////////////////////////////////////////////////////////////////////
// frees an integer vector allocated by IVector
void ms_Free_IVector(int* v)
{
	delete []v;
	v= NULL;
}

/////////////////////////////////////////////////////////////////////////
// frees an integer vector allocated by IVector
void ms_Free_IVector(int* v, long nl, long nh)
{
	delete [](v+nl-NR_END);
}

/////////////////////////////////////////////////////////////////////////
// frees a REAL vector allocated by RVector
void ms_Free_RVector(REAL* v)
{
	delete []v;
	v= NULL;
}

/////////////////////////////////////////////////////////////////////////
// frees a REAL vector allocated by RVector
void ms_Free_RVector(REAL* v, long nl, long nh)
{
	delete [](v+nl-NR_END);
}

/////////////////////////////////////////////////////////////////////////
// frees an integer matrix allocated by IMatrix
void ms_Free_IMatrix(int** mat)
{
	delete []mat[0];
	delete []mat;
}

/////////////////////////////////////////////////////////////////////////
// frees an int matrix allocated by imatrix()
void ms_Free_IMatrix(int** mat, long nrl, long nrh, long ncl, long nch)
{
	delete [](mat[nrl]+ncl-NR_END);
	delete [](mat+nrl-NR_END);
}

/////////////////////////////////////////////////////////////////////////
// frees a REAL matrix allocated by RMatrix()
void ms_Free_RMatrix(REAL** mat)
{
	delete []mat[0];
	delete []mat;
}

/////////////////////////////////////////////////////////////////////////
// frees a REAL matrix allocated by matrix()
void ms_Free_RMatrix(REAL **mat, long nrl, long nrh, long ncl, long nch)
{
	delete [](mat[nrl]+ncl-NR_END);
	delete [](mat+nrl-NR_END);
}


/////////////////////////////////////////////////////////////////////////
// points a submatrix [newrl..][newcl..] to a[oldrl..oldrh][oldcl..oldch]
REAL** ms_SubMatrix(REAL **a, long oldrl, long oldrh, long oldcl, long oldch,
	long newrl, long newcl)
{
	long i,j,nrow=oldrh-oldrl+1,ncol=oldcl-newcl;

	// allocate array of pointers to rows
	REAL** mat= new REAL* [nrow+NR_END];
	if(!mat) ErrorMsg("Error in 'submatrix': Allocation failure");
	mat+= NR_END;
	mat-= newrl;

	// set pointers to rows
	for(i=oldrl,j=newrl; i<=oldrh; i++,j++) 
		mat[j]= a[i]+ncol;
	return mat;
}

/////////////////////////////////////////////////////////////////////////
// allocates a REAL matrix m[nrl..nrh][ncl..nch] that points to the matrix
// declared in the standard C manner as a[nrow][ncol], where nrow=nrh-nrl+1
// and ncol=nch-ncl+1. The routine should be called with the address
// &a[0][0] as the first argument.
REAL** ms_ConvertMatrix(REAL *a, long nrl, long nrh, long ncl, long nch)
{
	long i,j,nrow=nrh-nrl+1,ncol=nch-ncl+1;

	// allocate pointers to rows
	REAL** mat= new REAL* [nrow+NR_END];
	if(!mat) ErrorMsg("Error in 'convert_matrix': Allocation failure");
	mat+= NR_END;
	mat-= nrl;

	// set pointers to rows
	mat[nrl]=a-ncl;
	for(i=1,j=nrl+1;i<nrow;i++,j++) 
		mat[j]= mat[j-1]+ncol;
	return mat;
}

/////////////////////////////////////////////////////////////////////////
// frees a matrix allocated by SubMatrix 
void ms_Free_SubMatrix(REAL **b, long nrl, long nrh, long ncl, long nch)
{
	delete [](b+nrl-NR_END);
}

/////////////////////////////////////////////////////////////////////////
// frees a matrix allocated by ConvertMatrix
void ms_Free_ConvertMatrix(REAL **b, long nrl, long nrh, long ncl, long nch)
{
	delete [](b+nrl-NR_END);
}

#undef NR_END

/////////////////////////////////////////////////////////////////////////
// Trigonometry
/*double cot (double a)
{
   double t=sin(a);
   if (!t) ErrorMsg ("Bad argument in cot(double)");
   return cos(a)/t;
}

double sec (double a)
{
   double t=cos(a);
   if (!t) ErrorMsg ("Bad argument in sec(double)");
   return 1/t;
}

double csc (double a)
{
   double t=sin(a);
   if (!t) ErrorMsg ("Bad argument in csc(double)");
   return 1/t;
}

double coth (double a)
{
   double t=sinh(a);
   if (!t) ErrorMsg ("Bad argument in coth(double)");
   return cosh(a)/t;
}

double sech (double a)
{
        return 1/cosh(a);
}

double csch (double a)
{
   double t=sinh(a);
   if (!t) ErrorMsg ("Bad argument in csch(double)");
   return 1/t;
}
*/
double Gamma(int n)
{
  double result=1.0;
  if (n<0) ErrorMsg("Error in Gamma function: negative argument");
  for (int i=1;i<n;i++) result*=double(i);
  return result;
}

double Gamma(double x)
{
  if (x==int(x)) return Gamma(int(x));
  if ((x<1.0)&&(x>0.0)) {
    /*using series for 1/Gamma(x) 2 vol Principa Press, Bloomington Ind,1933*/
    double c[26];
    c[0]=1.0;
    c[1]= 0.5772156649015329;
    c[2]=-0.6558780715202538;
    c[3]=-0.0420026350340952;
    c[4]= 0.1665386113822915;
    c[5]=-0.0421977345555443;
    c[6]=-0.0096219715278770;
    c[7]= 0.0072189432466630;
    c[8]=-0.0011651675918591;
    c[9]=-0.0002152416741149;
    c[10]= 0.0001280502823882;
    c[11]=-0.0000201348547807;
    c[12]=-0.0000012504934821;
    c[13]= 0.0000011330272320;
    c[14]=-0.0000002056338417;
    c[15]= 0.0000000061160950;
    c[16]= 0.0000000050020075;
    c[17]=-0.0000000011812746;
    c[18]= 0.0000000001043427;
    c[19]= 0.0000000000077823;
    c[20]=-0.0000000000036968;
    c[21]= 0.0000000000005100;
    c[22]=-0.0000000000000206;
    c[23]=-0.0000000000000054;
    c[24]= 0.0000000000000014;
    c[25]= 0.0000000000000001;

    double sum=0;
    double y=x;
    for (int k=0;k<26;k++) {
      sum+=c[k]*y;
      y*=x;
    }
    return 1/sum;
  }

  if (x>=1) {
    double y=x-int(x);
    double product=1.0;
    int k;
    for(k=0;k<int(x);k++) product*=y+k;
    return product*Gamma(y);
  }

  return PI/(Gamma(1-x)*sin(PI*(1-x)));
  /* using Gamma(x)*Gamma(1-x)=PI*csc(PI*x) */
}

double Beta(int x,int y)
{
  return Gamma(x)*Gamma(y)/Gamma(x+y);
}

double GarmonicSeries(int n)
{
  double result=0.0;
  for (int i=1;i<n+1;i++) result+=1.0/i;
  return result;
}

double BesselJ(double z, int n)
{
  /*Solutions to equation : (z^2)*d^2w/dz^2+z*dw/dz+(z^2-n^2)w=0 */

  if (n<0) return (1-4*int(n/2)+2*n)*BesselJ(z,-n);
  //if n is negative , return (-1)^n * BesselJ(z,-n)
  if (sqrt(z*z)<25.0) { //Small argument using series expansion
         double sum=0.0;
         double term;
         int k=0;
         do
                {
        term=pow((-SQR(z)/4.0),double(k))/(Gamma(k+1)*Gamma(n+k+1));
        sum+=term;
        k+=1;}
         while (((sqrt(term*term/(sum*sum))) >Precision)||(k<5));
         return sum*pow((z/2),double(n));  }
  else {            //Big argument using integration
         double sum=0.0;
         double dx=PI*sqrt(Precision);
         double x1=0.0;
         double y2;
         double y1=cos(z*sin(x1)-n*x1);
         double x2=dx;
         do
                {
        y2=cos(z*sin(x2)-n*x2);
        sum+=dx*(y1+y2)/2.0;
        y1=y2;
        x1+=dx;
        x2+=dx;       }
         while (x1<PI);
         return sum/PI; };
}

double Bessely(double x,int n)
{
  /*Spherical bessel funcion  of a second kind
       z^2*w''+2zw'+(z^2-n(n+1))w=0  */
  if (sqrt(x*x)<Precision)
      ErrorMsg("Error: Bessely(zero) infinity");
  if (n<0) return (-1+4*int(n/2)-2*n)*BesselJ(x,-n-1);  //was: Besselj
  //if n is negative , return (-1)^(n+1) * Bessely(z,-n-1)
  if(n==0) return -cos(x)/x;
  if(n==1) return -cos(x)/(x*x)-sin(x)/x;
  //return (2.0*n-1.0)*Bessely(x,n-1)/x-Bessely(x,n-2);
  double y,y1,y2;
  y2=-cos(x)/x;
  y1=-cos(x)/(x*x)-sin(x)/x;
  for(int k=2;k<n+1;k++) {
         y=(2.0*k-1.0)*y1/x-y2;
         y2=y1;
         y1=y;
  };
  return y;
}

