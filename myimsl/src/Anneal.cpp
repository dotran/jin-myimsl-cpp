/////////////////////////////////////////////////////////////////////////
// Program  : anneal.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003
//
#include <math.h>
#include "imsl.h"
#include "anneal.h"

///////////////////// implementation file of ANNEAL class /////////////////////
// Constructors and Destructors
ANNEAL::ANNEAL(int n):maxlchrom(n)
{
	lchrom= maxlchrom;
	tfactr= 0.9;
	seed= 1;
	path= IVector(maxlchrom);
}

ANNEAL::~ANNEAL()
{
	Free_IVector(path);
}

/////////////////////////////////////////////////////////////////////////
//
void ANNEAL::Anneal(REAL x[], REAL y[], int lchrom)
{
	void anneal1(REAL x[], REAL y[], int lchrom, int path[], REAL &obj,
						 REAL &temp, int &nsucc, REAL &tfactr);
	
	if(lchrom > maxlchrom)
		ErrorMsg("Error in 'Anneal': check lchrom or increase instance array size");
	anneal1(x-1,y-1,lchrom,path-1,obj,temp,nsucc,tfactr);
	return;
}

#define Dist(a,b,c,d) sqrt(((b)-(a))*((b)-(a))+((d)-(c))*((d)-(c)))
/////////////////////////////////////////////////////////////////////////
//
void anneal1(REAL x[], REAL y[], int lchrom, int iorder[], REAL &obj,
						 REAL &temp, int &nsucc, REAL &tfactr)
{
	REAL revcst(REAL x[], REAL y[], int iorder[], int lchrom, int n[]);
	REAL trncst(REAL x[], REAL y[], int iorder[], int lchrom, int n[]);
	int metrop(REAL de, REAL t);
	void reverse(int iorder[], int lchrom, int n[]);
	void trnspt(int iorder[], int lchrom, int n[]);
	int ans,nover,nlimit,k,nn;

	static int n[7];
	REAL de;

	nover= 100*lchrom;
	nlimit= 10*lchrom;
	nsucc= 0;
	for(k=1;k<=nover;k++) 
	{
		do 
		{
			n[1]=1+PickUp(lchrom);
			n[2]=1+PickUp(lchrom-1);
			if(n[2] >= n[1]) ++n[2];
			nn=1+((n[1]-n[2]+lchrom-1) % lchrom);
		} while(nn<3);
		if(Flip() == 0) 
		{
			n[3]=n[2]+PickUp(abs(nn-2))+1;
			n[3]=1+((n[3]-1) % lchrom);
			de=trncst(x,y,iorder,lchrom,n);
			ans=metrop(de,temp);
			if(ans) 
			{
				++nsucc;
				obj+= de;
				trnspt(iorder,lchrom,n);
			}
		} 
		else 
		{
			de=revcst(x,y,iorder,lchrom,n);
			ans=metrop(de,temp);
			if(ans) 
			{
				++nsucc;
				obj+= de;
				reverse(iorder,lchrom,n);
			}
		}
		if(nsucc >= nlimit) break;
	}
	temp*= tfactr;
}

/////////////////////////////////////////////////////////////
//
REAL revcst(REAL x[], REAL y[], int iorder[], int lchrom, int n[])
{
	REAL xx[5],yy[5],de;
	int j,ii;

	n[3]=1 + ((n[1]+lchrom-2) % lchrom);
	n[4]=1 + (n[2] % lchrom);
	for(j=1;j<=4;j++) 
	{
		ii=iorder[n[j]];
		xx[j]=x[ii];
		yy[j]=y[ii];
	}
	de = -Dist(xx[1],xx[3],yy[1],yy[3]);
	de -= Dist(xx[2],xx[4],yy[2],yy[4]);
	de += Dist(xx[1],xx[4],yy[1],yy[4]);
	de += Dist(xx[2],xx[3],yy[2],yy[3]);
	return de;
}

/////////////////////////////////////////////////////////////
//
void reverse(int iorder[], int lchrom, int n[])
{
	int nn,j,k,l,itmp;

	nn=(1+((n[2]-n[1]+lchrom) % lchrom))/2;
	for (j=1;j<=nn;j++)
	{
		k=1 + ((n[1]+j-2) % lchrom);
		l=1 + ((n[2]-j+lchrom) % lchrom);
		itmp=iorder[k];
		iorder[k]=iorder[l];
		iorder[l]=itmp;
	}
}

/////////////////////////////////////////////////////////////
//
REAL trncst(REAL x[], REAL y[], int iorder[], int lchrom, int n[])
{
	REAL xx[7],yy[7],de;
	int j,ii;

	n[4]=1 + (n[3] % lchrom);
	n[5]=1 + ((n[1]+lchrom-2) % lchrom);
	n[6]=1 + (n[2] % lchrom);
	for(j=1;j<=6;j++) 
	{
		ii=iorder[n[j]];
		xx[j]=x[ii];
		yy[j]=y[ii];
	}
	de = -Dist(xx[2],xx[6],yy[2],yy[6]);
	de -= Dist(xx[1],xx[5],yy[1],yy[5]);
	de -= Dist(xx[3],xx[4],yy[3],yy[4]);
	de += Dist(xx[1],xx[3],yy[1],yy[3]);
	de += Dist(xx[2],xx[4],yy[2],yy[4]);
	de += Dist(xx[5],xx[6],yy[5],yy[6]);
	return de;
}

/////////////////////////////////////////////////////////////
//
void trnspt(int iorder[], int lchrom, int n[])
{
	int m1,m2,m3,nn,j,jj,*jorder;

	jorder= IVector(1,lchrom);
	m1=1 + ((n[2]-n[1]+lchrom) % lchrom);
	m2=1 + ((n[5]-n[4]+lchrom) % lchrom);
	m3=1 + ((n[3]-n[6]+lchrom) % lchrom);
	nn=1;
	for(j=1;j<=m1;j++) 
	{
		jj=1 + ((j+n[1]-2) % lchrom);
		jorder[nn++]=iorder[jj];
	}
	if(m2>0) {
		for(j=1;j<=m2;j++) 
		{
			jj=1+((j+n[4]-2) % lchrom);
			jorder[nn++]=iorder[jj];
		}
	}
	if(m3>0) 
	{
		for(j=1;j<=m3;j++) 
		{
			jj=1 + ((j+n[6]-2) % lchrom);
			jorder[nn++]=iorder[jj];
		}
	}
	for (j=1;j<=lchrom;j++)
		iorder[j]=jorder[j];
	Free_IVector(jorder,1,lchrom);
}

/////////////////////////////////////////////////////////////
//
int metrop(REAL de, REAL t)
{
	return de < 0.0 || Rand() < exp(-de/t);
}
#undef Dist
