/////////////////////////////////////////////////////////////////////////
// Program  : sort.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include "cmatrix.h"

/////////////////////////////////////////////////////////////////////////
// Sorting of a REAL vector in increasing order
void ms_Sort(REAL a[], int n)
{
	void hpsort(REAL ra[], int n);
	hpsort(a-1,n);
}

/////////////////////////////////////////////////////////////////////////
// Sorting of a REAL vector in increasing order
void ms_Sort(RVECTOR &b)
{
	int i, j, inc=1, n=b.num;
	REAL v;

	do
	{
		inc *= 3;
		inc++;
	} while (inc <= n);
	do
	{
		inc /= 3;
		for (i=inc; i<n; i++)
		{
			v=b(i);
			j=i;
			while (b(j-inc) > v)  // '>' is modified
			{
				b(j)=b(j-inc);
				j -= inc;
				if (j < inc) break;
			}
			b(j)=v;
		}
	} while (inc > 1);
}

/////////////////////////////////////////////////////////////////////////
// Sorting of a COMPLEX vector in increasing order
void ms_Sort(CVECTOR &b)
{
	int i, j, inc=1, n=b.num;
	COMPLEX v;

	do
	{
		inc *= 3;
		inc++;
	} while (inc <= n);
	do
	{
		inc /= 3;
		for (i=inc; i<n; i++)
		{
			v=b(i);
			j=i;
			while (b(j-inc).Re > v.Re)  // '>' is modified 
			{
				b(j)=b(j-inc);
				j -= inc;
				if (j < inc) break;
			}
			b(j)=v;
		}
	} while (inc > 1);
}

/////////////////////////////////////////////////////////////////////////
// Sorting of a vector in increasing order
void ms_Sort(REAL a[], int n, int pos[])
{
	void indexx(REAL arr[], int n, int indx[]);

	indexx(a-1,n,pos-1);
	for(int j=0;j<n;j++) pos[j]=pos[j]-1;
}

/////////////////////////////////////////////////////////////////////////
// Sorting of a vector in increasing order
void ms_Sort(const RVECTOR &a, int pos[])
{
	void indexx(REAL arr[], int n, int indx[]);
	int n= a.num;
	double *b= RVector(n);

	Vector2Array(a,b);
	indexx(b-1,n,pos-1);
	for(int j=0;j<n;j++) pos[j]-= 1;
}

/////////////////////////////////////////////////////////////////////////
// Sorting of a vector in increasing order
void hpsort(REAL ra[], int n)
{
	int i,ir,j,l;
	REAL rra;

	if (n < 2) return;
	l=(n >> 1)+1;
	ir=n;
	for (;;) 
	{
		if (l > 1) 
		{
			rra=ra[--l];
		} 
		else 
		{
			rra=ra[ir];
			ra[ir]=ra[1];
			if (--ir == 1) 
			{
				ra[1]=rra;
				break;
			}
		}
		i=l;
		j=l+l;
		while (j <= ir) 
		{
			if (j < ir && ra[j] < ra[j+1]) j++;
			if (rra < ra[j]) 
			{
				ra[i]=ra[j];
				i=j;
				j <<= 1;
			} 
			else 
				j=ir+1;
		}
		ra[i]=rra;
	}
	return;
}
/////////////////////////////////////////////////////////////////////////
// Sorting of a vector in increasing order
#define M 7
#define NSTACK 50
void indexx(REAL arr[], int n, int indx[])
{
	int i,indxt,ir=n,j,k,l=1;
	int jstack=0,*istack;
	REAL a;

	istack= IVector(1,NSTACK);
	for (j=1;j<=n;j++) indx[j]=j;
	for (;;) {
		if (ir-l < M) {
			for (j=l+1;j<=ir;j++) {
				indxt=indx[j];
				a=arr[indxt];
				for (i=j-1;i>=1;i--) {
					if (arr[indx[i]] <= a) break;
					indx[i+1]=indx[i];
				}
				indx[i+1]=indxt;
			}
			if (jstack == 0) break;
			ir=istack[jstack--];
			l=istack[jstack--];
		} else {
			k=(l+ir) >> 1;
			ISWAP(indx[k],indx[l+1]);
			if (arr[indx[l+1]] > arr[indx[ir]]) {
				ISWAP(indx[l+1],indx[ir])
			}
			if (arr[indx[l]] > arr[indx[ir]]) {
				ISWAP(indx[l],indx[ir])
			}
			if (arr[indx[l+1]] > arr[indx[l]]) {
				ISWAP(indx[l+1],indx[l])
			}
			i=l+1;
			j=ir;
			indxt=indx[l];
			a=arr[indxt];
			for (;;) {
				do i++; while (arr[indx[i]] < a);
				do j--; while (arr[indx[j]] > a);
				if (j < i) break;
				ISWAP(indx[i],indx[j])
			}
			indx[l]=indx[j];
			indx[j]=indxt;
			jstack += 2;
			if (jstack > NSTACK) ErrorMsg("NSTACK too small in indexx.");
			if (ir-i+1 >= j-l) {
				istack[jstack]=ir;
				istack[jstack-1]=i;
				ir=j-1;
			} else {
				istack[jstack]=j-1;
				istack[jstack-1]=l;
				l=i;
			}
		}
	}
	Free_IVector(istack,1,NSTACK);
	return;
}
#undef M
#undef NSTACK
