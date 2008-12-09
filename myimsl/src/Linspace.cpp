/////////////////////////////////////////////////////////////////////////
// Program  : linspace.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include <math.h>
#include "rmatrix.h"

/////////////////////////////////////////////////////////////////////////
// generates n equally spaced points between x1 and x2.
void ms_LinSpace(REAL x1, REAL x2, int n, REAL x[])
{
	REAL step;

	if(n < 2)
		ErrorMsg("Error in 'LinSpace': use n >= 2");
	step= (x2-x1)/REAL(n-1);
	x[0]= x1;
	for(int i=1; i<n-1; i++)
		x[i]= x[i-1]+step;
	x[n-1]= x2;
	return;
}

/////////////////////////////////////////////////////////////////////////
// generates n equally spaced points between x1 and x2.
RVECTOR ms_LinSpace(REAL x1, REAL x2, int n)
{
	REAL step;
	RVECTOR x(n);

	if(n < 2)
		ErrorMsg("Error in 'LinSpace': use n >= 2");
	step= (x2-x1)/REAL(n-1);
	x(0)= x1;
	for(int i=1; i<n-1; i++)
		x(i)= x(i-1)+step;
	x(n-1)= x2;
	return x;
}

/////////////////////////////////////////////////////////////////////////
// generates n logarithmically equally spaced points between 
// decades 10^d1 and 10^d2
void ms_LogSpace(int d1, int d2, int n, REAL x[])
{
	int i;
	REAL step;

	if(n < 2)
		ErrorMsg("Error in 'LinSpace': use n >= 2");
	step= (REAL)(d2-d1)/(REAL)(n-1);
	x[0]= d1;
	x[n-1]= d2;
	for(i=1; i<n-1; i++)
		x[i]= x[i-1]+step;
	for(i=0; i<n; i++)
		x[i]= pow(10,x[i]);
	return;
}

/////////////////////////////////////////////////////////////////////////
// generates n logarithmically equally spaced points between 
// decades 10^d1 and 10^d2
RVECTOR ms_LogSpace(int d1, int d2, int n)
{
	int i;
	REAL step;
	RVECTOR x(n);

	if(n < 2)
		ErrorMsg("Error in 'LinSpace': use n >= 2");
	step= (REAL)(d2-d1)/(REAL)(n-1);
	x(0)= d1;
	for(i=1; i<n-1; i++)
		x(i)= x(i-1)+step;
	x(n-1)= d2;
	for(i=0; i<n; i++)
		x(i)= pow(10,x(i));
	return x;
}
