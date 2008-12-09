/////////////////////////////////////////////////////////////////////////
// Program  : minor.cpp
// Coded by : Version 15.3
// Coded on : 12/12/2003

#include <stdio.h>
#include "complex.h"

/////////////////////// +=,-=,*=,/=

REAL operator += (REAL &a, const COMPLEX &b)
{
	if (fabs(b.Im) < Precision) a+=b.Re;
	else
		ErrorMsg ("Error in REAL+=COMPLEX: COMPLEX is not REAL number");
	return a;
}

REAL operator -= (REAL &a, const COMPLEX &b)
{
	if (fabs(b.Im) < Precision) a-=b.Re;
	else
		ErrorMsg ("Error in REAL -=COMPLEX: COMPLEX is not REAL number");
	return a;
}

REAL operator *= (REAL &a, const COMPLEX &b)
{
	if (fabs(b.Im) < Precision) a*=b.Re;
	else
		ErrorMsg ("Error in REAL *=COMPLEX: COMPLEX is not REAL number");
	return a;
}

REAL operator /= (REAL &a, const COMPLEX &b)
{
	if (fabs(b.Im) < Precision) a/=b.Re;
	else
		ErrorMsg ("Error in REAL /=COMPLEX: COMPLEX is not REAL number");
	return a;
}

COMPLEX COMPLEX::operator *= (const COMPLEX &a)
{
	REAL t1=Re*a.Re, t2=Im*a.Im;
	Im = (Re+Im) * (a.Re+a.Im) - t1 - t2;
	Re = t1 - t2;
	return *this;
}

COMPLEX COMPLEX::operator /= (const COMPLEX &a)
{
	REAL t1, t2, temp;
	if (fabs(a.Re) >= fabs(a.Im))
	{
		t1   = a.Im / a.Re;
		t2   = a.Re + a.Im * t1;
		temp = (Re + Im * t1) / t2;
		Im   = (Im - Re * t1) / t2;
		Re   = temp;
	}
	else
	{
		t1   = a.Re / a.Im;
		t2   = a.Re * t1 + a.Im;
		temp = (Re * t1 + Im) / t2;
		Im   = (Im * t1 - Re) / t2;
		Re   = temp;
	}
	return *this;
}

/////////////////////////// *,/

COMPLEX operator * (const COMPLEX &a, const COMPLEX &b)
{
	REAL t1 = a.Re * b.Re;
	REAL t2 = a.Im * b.Im;
	return COMPLEX (t1 - t2, (a.Re+a.Im) * (b.Re+b.Im) - t1 - t2);
}

COMPLEX operator / (const COMPLEX &a, const COMPLEX &b)
{
	REAL t1, t2;
	if (fabs(b.Re) >= fabs(b.Im))
	{
		t1= b.Im / b.Re;
		t2= b.Re + b.Im * t1;
		return COMPLEX ((a.Re + a.Im * t1) / t2, (a.Im - a.Re * t1) / t2);
	}
	else
	{
		t1= b.Re / b.Im;
		t2= b.Re * t1 + b.Im;
		return COMPLEX ((a.Re * t1 + a.Im) / t2, (a.Im * t1 - a.Re) / t2);
	}
}

//////////////////////// <<,>>

ostream& operator << (ostream &stream, const COMPLEX &a)
{
	stream<<"   "<<a.Re<<"  "<<a.Im<<"  ";
	return stream;
}

istream& operator >> (istream &stream, COMPLEX &a)
{
	stream>>a.Re>>a.Im;
	return stream;
}

///////////////////////// Functions

REAL abs (const COMPLEX &a)
{
	if (a.Im == 0) return fabs(a.Re);
	if (a.Re == 0) return fabs(a.Im);
	return sqrt(SQR(a.Re)+SQR(a.Im));
}

REAL Arg (const COMPLEX &a)
{
	return atan2(a.Im,a.Re);
}

REAL phase (const COMPLEX &a)
{
	return atan2(a.Im,a.Re);
}

COMPLEX pow  (const COMPLEX &a, int n)
{ 
	return a^n; 
}

COMPLEX pow  (const COMPLEX &a, REAL n)           
{ 
	return a^n; 
}

COMPLEX pow  (const COMPLEX &a, const COMPLEX &b)   
{ 
	return a^b; 
}

COMPLEX sqrt (const COMPLEX &a, int flag)
{
	if ((a.Re>=0) && (fabs(a.Im) < Precision))
      return flag ? -sqrt(a.Re) : sqrt(a.Re);
	REAL R = fabs(a.Re), I = fabs(a.Im);
	REAL w = (R >= I) ?
           sqrt (R/2 * (  1 + sqrt (1 + SQR(a.Im/a.Re)))):
           sqrt (I/2 * (R/I + sqrt (1 + SQR(a.Re/a.Im))));
   COMPLEX c;
   if (a.Re >= 0)
   {
       c.Re = w;
       c.Im = a.Im / (2*w);
   }
   else
   {
       c.Re = I / (2*w);
       c.Im = (a.Im >= 0) ? w : -w;
   }
	return ((flag && (c.Re<0))  ||  (!flag && (c.Re>=0))) ? c : -c;
}

COMPLEX operator ^ (const COMPLEX &a, int n)
{
	COMPLEX c(1,0);
	if (n==0) return 1;
	if (n>0)
   {
      for (int i=0;i<n;i++) c*=a;
      return c;
   }
	else
   {
      for (int j=0;j>n;j--) c*=a;
      return 1/c;
   }
}

COMPLEX operator ^ (const COMPLEX &a, REAL n)
{
	return exp(n*log(a));
}

COMPLEX operator ^ (const COMPLEX &a, const COMPLEX &b)
{
	return exp(b*log(a));
}

COMPLEX root (const COMPLEX &z, int n, int k)
{
	REAL c=exp(log(abs(z))/n);
	REAL t=(Arg(z)+2*PI*k)/n;
	return COMPLEX (c*cos(t), c*sin(t));
}

COMPLEX exp (const COMPLEX &a)
{
	REAL t=exp(a.Re);
	return COMPLEX (t*cos(a.Im), t*sin(a.Im));
}

COMPLEX log (const COMPLEX &a)
{
	if (a==0)
		ErrorMsg("Error in function log(COMPLEX): argument is 0");
	return COMPLEX (log(abs(a)), Arg(a));
}

COMPLEX sin (const COMPLEX &a)
{
	return COMPLEX (sin(a.Re)*cosh(a.Im), cos(a.Re)*sinh(a.Im));
}

COMPLEX cos (const COMPLEX &a)
{
	return COMPLEX (cos(a.Re)*cosh(a.Im), -sin(a.Re)*sinh(a.Im));
}

COMPLEX tan (const COMPLEX &a)
{
	return sin(a)/cos(a);
}

COMPLEX cot (const COMPLEX &a)
{
	return cos(a)/sin(a);
}

COMPLEX sec (const COMPLEX &a)
{
	return 1/cos(a);
}

COMPLEX csc (const COMPLEX &a)
{
	return 1/sin(a);
}

COMPLEX sinh (const COMPLEX &a)
{
	return COMPLEX (sinh(a.Re)*cos(a.Im), cosh(a.Re)*sin(a.Im));
}

COMPLEX cosh (const COMPLEX &a)
{
	return COMPLEX (cosh(a.Re)*cos(a.Im), sinh(a.Re)*sin(a.Im));
}

COMPLEX tanh (const COMPLEX &a)
{
	return sinh(a)/cosh(a);
}

COMPLEX coth (const COMPLEX &a)
{
	return cosh(a)/sinh(a);
}

COMPLEX sech (const COMPLEX &a)
{
	return 1/cosh(a);
}

COMPLEX csch (const COMPLEX &a)
{
	return 1/sinh(a);
}
//////////////////////// Inverce trigonometric functions

COMPLEX asin (const COMPLEX &a, int flag)
{
	return -ImUnit * log(ImUnit*a + sqrt(1-sqr(a), flag));
}

COMPLEX acos (const COMPLEX &a, int flag)
{
	return -ImUnit * log(a + ImUnit*sqrt(1-sqr(a), flag));
}

COMPLEX atan (const COMPLEX &a)
{
	return ImUnit/2 * log((ImUnit+a)/(ImUnit-a));
}

COMPLEX acot (const COMPLEX &a)
{
	return ImUnit/2 * log((a-ImUnit)/(a+ImUnit));
}

COMPLEX asec (const COMPLEX &a, int flag)
{
	return acos(1/a, flag);
}

COMPLEX acsc (const COMPLEX &a, int flag)
{
	return asin(1/a, flag);
}

COMPLEX asinh (const COMPLEX &a, int flag)
{
	return log(a + sqrt(sqr(a)+1, flag));
}

COMPLEX acosh (const COMPLEX &a, int flag)
{
	return log(a + sqrt(sqr(a)-1, flag));
}

COMPLEX atanh (const COMPLEX &a)
{
	return log((1+a)/(1-a)) / 2;
}

COMPLEX acoth (const COMPLEX &a)
{
	return log((a+1)/(a-1)) / 2;
}

COMPLEX asech (const COMPLEX &a, int flag)
{
	return acosh(1/a, flag);
}

COMPLEX acsch (const COMPLEX &a, int flag)
{
	return asinh(1/a, flag);
}

COMPLEX Polar (REAL a, REAL b)
{
	return COMPLEX (a*cos(b), a*sin(b));
}

void COMPLEX::SetPolar (REAL a, REAL b)
{
	Re=a*cos(b);
	Im=a*sin(b);
}

void COMPLEX::SetAbs (REAL a)
{
	REAL b=Arg(*this);
	Re=a*cos(b);
	Im=a*sin(b);
}

void COMPLEX::SetArg (REAL b)
{
	REAL a=abs(*this);
	Re=a*cos(b);
	Im=a*sin(b);
}

void Solve2 (COMPLEX* z, const COMPLEX &b, const COMPLEX &c)
   // finding z of equation:  z^2 + b*z + c = 0
{
  COMPLEX t = sqrt(sqr(b)-4*c);
  COMPLEX q = ((!b * t).Re >= 0) ? (-(b + t) / 2) : (-(b - t) / 2);
  z[0] = q;
  z[1] = c/q;
}

COMPLEX Solve2 (const COMPLEX &b, const COMPLEX &c, int RootNumber)
{
	if ((RootNumber < 0) || (RootNumber > 1))
		ErrorMsg ("Error in Solve2: wrong root number");
	COMPLEX t = sqrt(sqr(b)-4*c);
	COMPLEX q = ((!b * t).Re >= 0) ? (-(b + t) / 2) : (-(b - t) / 2);
	return RootNumber ? c/q : q;
}

void Solve3 (COMPLEX* z, const COMPLEX &a2, const COMPLEX &a1, const COMPLEX &a0)
   // finding z of equation:  z^3 + a2*z^2 + a1*z + a0 = 0
{
  COMPLEX q, r, t, a, b, zero(0,0);
  q = (sqr(a2) - 3*a1) / 9;
  r = (2*(a2^3) - 9*a2*a1 + 27*a0) / 54;
  t = sqrt((r^2) - (q^3));
        a = ((!r * t) >=0.0) ? -((r+t)^(1.0/3)) : -((r-t)^(1.0/3));
  b = ((a == zero) ? zero : (q/a));
  z[0] = -(a+b)/2 - a2/3 + ImUnit*sqrt(3)*(a-b)/2;
  z[1] = -(a+b)/2 - a2/3 - ImUnit*sqrt(3)*(a-b)/2;
  z[2] = a + b - a2/3;
}

COMPLEX Solve3 (const COMPLEX &a2, const COMPLEX &a1, const COMPLEX &a0, int RootNumber)
{
	if ((RootNumber < 0) || (RootNumber > 2))
		ErrorMsg ("Error in Solve3: wrong root number");
	COMPLEX z[3];
	Solve3 (z,a2,a1,a0);
	return z[RootNumber];
}

void Solve4 (COMPLEX* z, const COMPLEX &a3, const COMPLEX &a2, const COMPLEX &a1, const COMPLEX &a0)
   // finding z of equation:  z^4 + a3*z^3 + a2*z^2 + a1*z + a0 = 0
{
  COMPLEX  t1, t2, t;
  t = Solve3 (-a2, (a1*a3 - 4*a0), -((a1^2) + a0*(a3^2) - 4*a0*a2));
  t1 = sqrt((a3^2)/4 - a2 + t);
  t2 = sqrt((t^2)/4 - a0);
  Solve2 (      z, (a3/2 - t1), (t/2 + t2));
  Solve2 (&(z[2]), (a3/2 + t1), (t/2 - t2));
}

COMPLEX Solve4 (const COMPLEX &a3, const COMPLEX &a2, const COMPLEX &a1, const COMPLEX &a0, int RootNumber)
{
	if ((RootNumber < 0) || (RootNumber > 3))
		ErrorMsg ("Error in Solve4: wrong root number");
	COMPLEX z[4];
	Solve4 (z,a3,a2,a1,a0);
	return z[RootNumber];
}

COMPLEX Gamma(COMPLEX z)
{
  COMPLEX sum(0.0,0.0);
  COMPLEX term;
  if ((z==int(z.Re))&&(int(z.Re)<=0))
          ErrorMsg("Error in Gamma(COMPLEX): negative argument");
  int k=1;
  do
	{
		term=z/k-log(1.0+z/k);
		sum+=term;
		k+=1;
	} while ((abs(term)/abs(sum))>Precision);
  return exp(sum-log(z)-euler_constant*z);
}

COMPLEX Beta(COMPLEX x,COMPLEX y)
{
  return Gamma(x)*Gamma(y)/Gamma(x+y);
}

COMPLEX BesselJ(COMPLEX z, int n)
{
  /*Solutions to equation : (z^2)*d^2w/dz^2+z*dw/dz+(z^2-n^2)w=0 */

  if (n<0) return (1-4*int(n/2)+2*n)*BesselJ(z,-n);
  //if n is negative , return (-1)^n * BesselJ(z,-n)
  if (abs(z)<25.0) 
	{ //Small argument using series expansion
		COMPLEX sum(0.0,0.0);
		COMPLEX term;
		int k=0;
		do
		{
			term=((-sqr(z)/4.0)^(k))/(Gamma(k+1)*Gamma(n+k+1));
			sum+=term;
			k+=1;
		}	while (((abs(term)/abs(sum)) >Precision)||(k<5));
		return sum*((z/2)^n);  
	}
  else
	{            //Big argument using integration
		COMPLEX sum(0.0,0.0);
		REAL dx=PI*sqrt(Precision);
		REAL x1=0.0;
		COMPLEX y2;
		COMPLEX y1=cos(z*sin(x1)-n*x1);
		REAL x2=dx;
		do
		{
			y2=cos(z*sin(x2)-n*x2);
			sum+=dx*(y1+y2)/2.0;
			y1=y2;
			x1+=dx;
			x2+=dx;       
		} while (x1<PI);
	return sum/PI; };
}

COMPLEX BesselJ(COMPLEX z, COMPLEX n)
{
  /*Solutions to equation : (z^2)*d^2w/dz^2+z*dw/dz+(z^2-n^2)w=0 */
  if (abs(z)>25.0)
		WarningMsg("Warning in BesselJ: argument may be too big for this method");
	COMPLEX sum(0.0,0.0);
	COMPLEX term;
	int k=0;
	do
	{
		term=((-sqr(z)/4.0)^(k))/(Gamma(k+1)*Gamma(n+k+1));
		sum+=term;
		k+=1;
	} while (((abs(term)/abs(sum)) >Precision)||(k<5));
	return sum*((z/2)^n);
}

COMPLEX BesselY (COMPLEX z, int n)
{
  if (z==0)
      ErrorMsg("Error: BesselY(zero) is infinity");
  if (n<0) 
		return (1-4*int(n/2)+2*n)*BesselY(z,-n);
  //if n is negative , return (-1)^n * BesselY(z,-n)

  if (abs(z)<25.0) 
	{ //Small argument using series expansion
		COMPLEX sum1(0.0,0.0),sum2(0.0,0.0), sum3,term;
		int k;
		for (k=0;k<n;k++) sum1+=(Gamma(n-k)/Gamma(k+1))*((sqr(z)/4.0)^k);
		sum1*=((2.0/z)^n);
		k=0;
		do
		{
			term=((-sqr(z)/4.0)^(k))/(Gamma(k+1)*Gamma(n+k+1))*
          (GarmonicSeries(k+n)+GarmonicSeries(k));
			sum2+=term;
			k+=1;
		} while (((abs(term)/abs(sum2)) >Precision)||(k<5));
		sum2*=((z/2)^n);
		sum3=(2.0*(euler_constant+log(z/2))*BesselJ(z,n)-sum1-sum2)/PI;
		return sum3; 
	}
  else 
	{            //Big argument using integration
		WarningMsg("Warning: BesselY argument is too big for this method");
		COMPLEX sum(0.0,0.0);
		REAL dx=PI*sqrt(Precision);
		REAL x1=0.0;
		COMPLEX y2;
		COMPLEX y1=sin(z*sin(x1)-n*x1);
		REAL x2=dx;
         do
                {
        y2=sin(z*sin(x2)-n*x2);
        sum+=dx*(y1+y2)/2.0;
        y1=y2;
        x1+=dx;
        x2+=dx;       }
         while (x1<PI);
         //second summ
         COMPLEX sum1(0.0,0.0);
         // integral goes till following number
         dx=log(n+3)*log(1.0/Precision)*sqrt(Precision)/50.0;
         x1=0.0;
         y1=(exp(n*x1)+exp(-n*x1)*cos(n*PI))*exp(-z*sinh(x1));
         x2=dx;
         do
                {
        y2=(exp(n*x2)+exp(-n*x2)*cos(n*PI))*exp(-z*sinh(x2));
        sum1+=dx*(y1+y2)/2.0;
        y1=y2;
        x1+=dx;
        x2+=dx;       }
         while (x1<log(n+3)*log(1.0/Precision)/50.0);
         return (sum-sum1)/PI; };
}

REAL Besselj(REAL x,int n)
{
  /*Spherical bessel funcion  of a first kind
         z^2*w''+2zw'+(z^2-n(n+1))w=0  */
  if (sqrt(x*x)<Precision) {
         if (n==0) return 1.0;
         else return 0.0;
  };
  if (n<0) return (1-4*int(n/2)+2*n)*Bessely(x,-n-1);
  //if n is negative , return (-1)^n * Bessely(z,-n-1)
  if(n==0) return sin(x)/x;
  if(n==1) return sin(x)/(x*x)-cos(x)/x;
  if (x>n/7.0) {
  /*there is a good convergence of
  Bessely(x,n+1)=(2.0*n-1.0)*Bessely(x,n-1)/x-Bessely(x,n-2) */
  REAL y,y1,y2;
  y1=sin(x)/(x*x)-cos(x)/x;
  y2=sin(x)/x;
  for(int k=2;k<n+1;k++) {
         y=(2.0*k-1.0)*y1/x-y2;
         y2=y1;
         y1=y;
  };
  return y;     }
  else {
  /*other method for this bad part */
  COMPLEX mm((n+0.5),0);
  COMPLEX z(x,0.0);
  return sqrt(PI/(2.0*x))*BesselJ(z,mm).Re;
  };
}

/////////////////////////////////////////////////////////////////////////
// outputs a COMPLEX number
void ms_COut(const COMPLEX &v)
{	
	if(v.Im >=0)
		printf("%f+j%f\n",v.Re,v.Im);
	else
		printf("%f-j%f\n",v.Re,-v.Im);
	return;
}