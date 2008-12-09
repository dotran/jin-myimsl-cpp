/////////////////////////////////////////////////////////////////////////
// Program  : array2matrix.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include "cmatrix.h"

/////////////////////////////////////////////////////////////////////////
// Converts a REAL array to a REAL vector
void Array2Vector(REAL a[], RVECTOR &b)
{
	for(int i=0; i<b.num; i++) 
		b(i)= *a++;
}

/////////////////////////////////////////////////////////////////////////
// Converts a REAL array to a COMPLEX vector
void Array2Vector(REAL a[], CVECTOR &b)
{
	for(int i=0; i<b.num; i++)
	{
    b(i).Re= *a++;
    b(i).Im= *a++;
  }
}

/////////////////////////////////////////////////////////////////////////
// Converts a REAL array to a REAL matrix
void Array2Matrix(REAL **a, RMATRIX &b)
{
	for(int i=0; i<b.n; i++) 
		for(int j=0; j<b.m; j++)
			b(i,j)= a[i][j];
}

/////////////////////////////////////////////////////////////////////////
// Converts a REAL vector to a REAL array
void Vector2Array(const RVECTOR &a, REAL b[])
{
	for(int i=0; i<a.num; i++) *b++= a(i);
}

/////////////////////////////////////////////////////////////////////////
// Converts a COMPLEX vector to a REAL array
void Vector2Array(const CVECTOR &a, REAL b[])
{
	for(int i=0; i<a.num; i++)
	{
    *b++= a(i).Re;
    *b++= a(i).Im;
  }
}

/////////////////////////////////////////////////////////////////////////
// Converts a REAL matrix to a REAL array
void Matrix2Array(const RMATRIX &a, REAL **b)
{
	for(int i=0; i<a.n; i++) 
		for(int j=0; j<a.m; j++)
			b[i][j]= a(i,j);
}
