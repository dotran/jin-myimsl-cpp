/////////////////////////////////////////////////////////////////////////
// Program  : rngs.cpp
// Coded by : Steve Park & Dave Geyer
// Coded on : 09-22-98
/* The library supplies 256 streams of random numbers; use 
 * SelectStream(s) to switch between streams indexed s = 0,1,...,255.
 *
 * The streams must be initialized.  The recommended way to do this is by
 * using the function PlantSeeds(x) with the value of x used to initialize 
 * the default stream and all other streams initialized automatically with
 * values dependent on the value of x.  The following convention is used 
 * to initialize the default stream:
 *    if x > 0 then x is the state
 *    if x <= 0 then the state is obtained from the system clock
 *
 * The generator used in this library is a so-called 'Lehmer random number
 * generator' which returns a pseudo-random number uniformly distributed
 * 0.0 and 1.0.  The period is (m - 1) where m = 2,147,483,647 and the
 * smallest and largest possible values are (1 / m) and 1 - (1 / m)
 * respectively.  For more details see:
 */

#include <stdio.h>
#include <time.h>
#include <math.h>
#include "realtype.h"
#include "imsl.h"

#define MODULUS    2147483647 // DON'T CHANGE THIS VALUE              
#define MULTIPLIER 48271      // DON'T CHANGE THIS VALUE              
#define CHECK      399268537  // DON'T CHANGE THIS VALUE              
#define STREAMS    256        // # of streams, DON'T CHANGE THIS VALUE
#define A256       22925      // jump multiplier, DON'T CHANGE THIS VALUE
#define DEFAULT    123456789  // initial seed, use 0 < DEFAULT < MODULUS
      
static long seed[STREAMS]= {DEFAULT};  // current state of each stream 
static int  stream       = 0;          // stream index, 0 is the default
static int  initialized  = 0;          // test for stream initialization

static unsigned long iseed= DEFAULT;   // seed of function Flip

/////////////////////////////////////////////////////////////////////////
// Returns a pseudo-random number uniformly distributed between 0 and 1 
double ms_Rand(void)
{
  const long Q= MODULUS / MULTIPLIER;
  const long R= MODULUS % MULTIPLIER;
  long t;

  t= MULTIPLIER * (seed[stream] % Q) - R * (seed[stream] / Q);
  if(t > 0) 
    seed[stream]= t;
  else 
    seed[stream]= t + MODULUS;
  return ((double) seed[stream] / MODULUS);
}


/////////////////////////////////////////////////////////////////////////
// sets the state of all the random number generator streams by "planting" 
// a sequence of states (seeds), one per stream, with all states dictated 
// by the state of the default stream. The sequence of planted states is 
// separated one from the next by 8,367,782 calls to Rand()
void ms_SRands(long x)
{
  const long Q= MODULUS / A256;
  const long R= MODULUS % A256;
  int j;
  int s;

  initialized= 1;
  s= stream;                       // remember the current stream 
  ms_SetRandState(0);              // change to stream 0          
  ms_SRand(x);                     // set seed[0]              
  stream= s;                       // reset the current stream 
  for(j= 1; j < STREAMS; j++) 
	{
    x= A256*(seed[j-1]%Q) - R*(seed[j-1]/Q);
    if(x > 0)
		{
      seed[j]= x;
    	iseed= x;
		}
		else
		{
			seed[j]= x + MODULUS;
			iseed= x + MODULUS;
		}
	}
}

/////////////////////////////////////////////////////////////////////////
// sets the state of the current random number generator stream
// if x > 0 then x is the state (unless too large)
// if x <= 0 then the state is obtained from the system clock
void ms_SRand(long x)
{
  char ok= 0;

  if(x > 0)
    x= x % MODULUS;        // correct if x is too large
  if(x <= 0)                                 
    x= ((unsigned long) time((time_t *) NULL)) % MODULUS;              
  seed[stream]= x;
	iseed= x;
}

/////////////////////////////////////////////////////////////////////////
// sets the current random number generator stream that stream from which
// the next random number will come.
void ms_SetRandState(int index)
{
  stream= ((unsigned int) index) % STREAMS;
  if((initialized == 0) && (stream != 0))   // protect against       
    ms_SRands(DEFAULT);                     // un-initialized streams 
}


/////////////////////////////////////////////////////////////////////////
// gets the state of the current random number generator stream.                                                   
long GetSeed(void)
{
  return seed[stream];
}
#undef MODULUS              
#undef MULTIPLIER              
#undef CHECK              
#undef STREAMS
#undef A256 
#undef DEFAULT


/* generating random variates from six discrete distributions
 *
 *      Generator         Range (x)     Mean         Variance
 *
 *      BernRnd(p)         x = 0,1       p            p*(1-p)
 *      BinoRnd(n, p)      x = 0,...,n   n*p          n*p*(1-p)
 *      EquiRnd(a, b)      x = a,...,b   (a+b)/2      ((b-a+1)*(b-a+1)-1)/12
 *      GeoRnd(p)          x = 0,...     p/(1-p)      p/((1-p)*(1-p))
 *      PasRnd(n, p)       x = 0,...     n*p/(1-p)    n*p/((1-p)*(1-p))
 *      PoissRnd(m)        x = 0,...     m            m
 * 
 * and seven continuous distributions
 *
 *      UnifRnd(a, b)      a < x < b     (a + b)/2    (b - a)*(b - a)/12 
 *      ExpoRnd(m)         x > 0         m            m*m
 *      ErlRnd(n, b)       x > 0         n*b          n*b*b
 *      NormRnd(m, s)      all x         m            s*s
 *      Chi2Rnd(n)         x > 0         n            2*n 
 *      StudRnd(n)         all x         0  (n > 1)   n/(n - 2)   (n > 2)
 *      LognRnd(a, b)      x > 0         exp(a + 0.5*b*b)  (exp(b*b) - 1) * exp(2*a + b*b)
 */


/////////////////////////////////////////////////////////////////////////
// Returns 1 with probability p or 0 with probability 1-p. 
// NOTE: use 0 <= p <= 1                                  
long ms_BernRnd(double p)
{
	if(p<0.0 || p>1.0) ErrorMsg("Error in 'BernRnd': use 0<= p <=1");
  return ((ms_Rand() < (1.0 - p)) ? 0 : 1);
}

/////////////////////////////////////////////////////////////////////////
// Returns a binomial distributed integer between 0 and n inclusive. 
// NOTE: use n >= 0 and 0.0 <= p <= 1.0
long ms_BinoRnd(long n, double p)
{ 
  long i, x= 0;

	if(n<0 || p<0.0 || p>1.0) ErrorMsg("Error in 'BinoRnd': use n>=0 and 0<p<1");
  for (i= 0; i < n; i++)
    x+= ms_BernRnd(p);
  return (x);
}

/////////////////////////////////////////////////////////////////////////
// Returns an equilikely distributed integer between a and b inclusive. 
// NOTE: use a < b
long ms_EquiRnd(long a, long b)
{
	if(a>=b) ErrorMsg("Error in 'EquiRnd': use a < b");
  return (a + (long)((b - a + 1) * ms_Rand()));
}

/////////////////////////////////////////////////////////////////////////
// Returns a geometric distributed non-negative integer.
// NOTE: use 0.0 < p < 1.0
long ms_GeoRnd(double p)
{
	if(p<=0.0 || p>=1.0) ErrorMsg("Error in 'GeoRnd': use 0< p <1");
  return ((long)(log(1.0 - ms_Rand()) / log(p)));
}

/////////////////////////////////////////////////////////////////////////
// Returns a Pascal distributed non-negative integer. 
// NOTE: use n > 0 and 0.0 < p < 1.0
long ms_PasRnd(long n, double p)
{ 
  long i, x = 0;

	if(n<=0 || p<=0.0 || p>=1.0) ErrorMsg("Error in 'PasRnd': use n>0 and 0<p<1");
  for(i = 0; i < n; i++)
    x += ms_GeoRnd(p);
  return (x);
}

/////////////////////////////////////////////////////////////////////////
// Returns a Poisson distributed non-negative integer. 
// NOTE: use m > 0
long ms_PoissRnd(double m)
{ 
  double t= 0.0;
  long x= 0;

	if(m<0.0) ErrorMsg("Error in 'PoissRnd': use m >= 0");
	else if(m==0.0) return x;
  while(t < m) {
    t += ms_ExpRnd(1.0);
    x++;
  }
  return (x - 1);
}

/////////////////////////////////////////////////////////////////////////
// Returns a uniformly distributed real number between a and b. 
// NOTE: use a < b
double ms_UnifRnd(double a, double b)
{ 
	if(a>=b) ErrorMsg("Error in 'UnifRnd': use a < b");
  return (a + (b - a) * ms_Rand());
}

/////////////////////////////////////////////////////////////////////////
// Returns an exponentially distributed positive real number. 
// NOTE: use m > 0.0
double ms_ExpRnd(double m)
{
	if(m<=0.0) ErrorMsg("Error in 'ExpRnd': use m > 0");
  return (-m * log(1.0 - ms_Rand()));
}

/////////////////////////////////////////////////////////////////////////
// Returns an Erlang distributed positive real number.
// NOTE: use n > 0 and b > 0.0
double ms_ErlRnd(long n, double b)
{ 
  long   i;
  double x = 0.0;

	if(n<=0 || b<=0.0) ErrorMsg("Error in 'ErlRnd': use n > 0 and b > 0");
  for (i = 0; i < n; i++) 
    x += ms_ExpRnd(b);
  return (x);
}

/////////////////////////////////////////////////////////////////////////
// Returns a normal (Gaussian) distributed real number.
// NOTE: use s >= 0.0
double ms_NormRnd(double m, double s)
{ 
  const double p0 = 0.322232431088;     const double q0 = 0.099348462606;
  const double p1 = 1.0;                const double q1 = 0.588581570495;
  const double p2 = 0.342242088547;     const double q2 = 0.531103462366;
  const double p3 = 0.204231210245e-1;  const double q3 = 0.103537752850;
  const double p4 = 0.453642210148e-4;  const double q4 = 0.385607006340e-2;
  double u, t, p, q, z;

	if(s<0.0) ErrorMsg("Error in 'NormRnd': use s >= 0");
  u= ms_Rand();
  if(u < 0.5)
    t= sqrt(-2.0 * log(u));
  else
    t= sqrt(-2.0 * log(1.0 - u));
  p= p0 + t * (p1 + t * (p2 + t * (p3 + t * p4)));
  q= q0 + t * (q1 + t * (q2 + t * (q3 + t * q4)));
  if(u < 0.5)
    z= (p / q) - t;
  else
    z= t - (p / q);
  return (m + s * z);
}

/////////////////////////////////////////////////////////////////////////
// Returns a lognormal distributed positive real number. 
// NOTE: use b > 0.0
double ms_LognRnd(double a, double b)
{
	if(b<=0.0) ErrorMsg("Error in 'LognRnd': use b > 0");
  return (exp(a + b * ms_NormRnd(0.0, 1.0)));
}

/////////////////////////////////////////////////////////////////////////
// Returns a chi-square distributed positive real number. 
// NOTE: use n > 0
double ms_Chi2Rnd(long n)
{ 
  long i;
  double z, x= 0.0;

	if(n<=0.0) ErrorMsg("Error in 'Chi2Rnd': use n > 0");
  for(i= 0; i < n; i++) {
    z= ms_NormRnd(0.0, 1.0);
    x+= z*z;
  }
  return (x);
}

/////////////////////////////////////////////////////////////////////////
// Returns a student-t distributed real number.
// NOTE: use n > 0
double ms_StudRnd(long n)
{
	if(n<=0.0) ErrorMsg("Error in 'StudRnd': use n > 0");
  return (ms_NormRnd(0.0, 1.0) / sqrt(ms_Chi2Rnd(n)/n));
}

/////////////////////////////////////////////////////////////////////////
// generates a random integer number with range 0..num-1
int ms_PickUp(int num)
{
	int m;

	m= (int)ms_UnifRnd(0.0, (double)num);
	if(m==num) 
		return m-1;
	else
		return m;
}

/////////////////////////////////////////////////////////////////////////
// Returns an integer, 0 or 1 
// NOTE: use SRand or SRands to reset Flip
#define IB1 1
#define IB2 2
#define IB5 16
#define IB18 131072

int ms_Flip()
{
	unsigned long newbit;

	newbit= (iseed & IB18) >> 17
		^ (iseed & IB5) >> 4
		^ (iseed & IB2) >> 1
		^ (iseed & IB1);
	iseed=(iseed << 1) | newbit;
	return (int) newbit;
}
#undef IB1
#undef IB2
#undef IB5
#undef IB18
