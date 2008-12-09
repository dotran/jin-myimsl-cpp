/////////////////////////////////////////////////////////////////////////
// Program  : rmatrix.cpp
// Coded by : Version 15.3
// Coded on : 12/12/2003

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rmatrix.h"

//############## Constructors and Destructors #################//

RMATRIX::RMATRIX(int v1,int v2):n(v1),m(v2)
{
	num=n*m;
	elem=new REAL[num];
}

RMATRIX::RMATRIX(int v1,int v2, char *a):n(v1),m(v2)
{
	num=n*m;
	elem=new REAL[num];
	istrstream s(a);
	for (int i=0;i<num;i++) s>>elem[i];
}

RMATRIX::RMATRIX(const RMATRIX &mat):n(mat.n),m(mat.m)
{
	num=n*m;
	elem=new REAL[num];
	for (int i=0;i<num;i++) elem[i]=mat.elem[i];
}

RMATRIX::RMATRIX(void)
// by default we define 4*4 matrix
{
	n=m=dimension_of_space;
	num=n*m;
	elem=new REAL[num];
}

RMATRIX::~RMATRIX(void)
{
	if (elem)
	{
		delete []elem;
		elem=NULL;
	}
}

///////////////// =, +=, -=, *=, /= with Matrices //////////////////

RMATRIX RMATRIX::operator = (const RMATRIX &a)
{
	if ((a.m==m) && (a.n==n))
		for (int i=0;i<num;i++) elem[i]=a.elem[i];
	else ErrorMsg ("Error in 'RMATRIX=RMATRIX':\nmatrices has diffirent dimensions");
		return *this;
}

RMATRIX RMATRIX::operator = (char *a)
{
	istrstream s(a);
	for (int i=0;i<num;i++) s>>elem[i];
	return *this;
}

RMATRIX RMATRIX::operator += (const RMATRIX &a)
{
	if ((a.m==m) && (a.n==n))
		for (int i=0;i<num;i++) elem[i]+=a.elem[i];
	else ErrorMsg ("Error in 'RMATRIX+=RMATRIX':\nmatrices has diffirent dimensions");
		return *this;
}

RMATRIX RMATRIX::operator += (REAL a)
{
	if (n==m)
		for (int i=0;i<num;i++) elem[i*m+i]+=a;
	else ErrorMsg ("Error in 'RMATRIX+=REAL':\nmatrix is not square");
		return *this;
}

RMATRIX RMATRIX::operator -= (const RMATRIX &a)
{
	if ((a.m==m) && (a.n==n))
		for (int i=0;i<num;i++) elem[i]-=a.elem[i];
	else ErrorMsg ("Error in 'RMATRIX-=RMATRIX':\nmatrices has diffirent dimensions");
		return *this;
}

RMATRIX RMATRIX::operator -= (REAL a)
{
	if (n==m)
		for (int i=0;i<num;i++) elem[i*m+i]-=a;
	else ErrorMsg ("Error in 'RMATRIX-=REAL':\nmatrix is not square");
		return *this;
}

RMATRIX RMATRIX::operator *= (const RMATRIX &b)
{
	if (m==b.n)
		*this=*this*b;
	else ErrorMsg ("Error in 'RMATRIX*=RMATRIX':\nBad dimensions");
		return *this;
}

RMATRIX RMATRIX::operator *= (REAL a)
{
	for (int i=0;i<num;i++) elem[i]*=a;
	return *this;
}

RMATRIX RMATRIX::operator /= (const RMATRIX &a)
{
	if (a.num!=1)
		ErrorMsg ("Error in 'RMATRIX/=RMATRIX': matrix is not 1x1");
	REAL t=*a.elem;
	if (t==0)
		ErrorMsg ("Error in 'RMATRIX/=RMATRIX': matrix is devided by 0");
	for (int i=0;i<num;i++) elem[i]/=t;
	return *this;
}

RMATRIX RMATRIX::operator /= (REAL a)
{
	if (a==0)
		ErrorMsg ("Error in 'RMATRIX/=REAL': matrix is devided by 0");
	for (int i=0;i<num;i++) elem[i]/=a;
	return *this;
}

// ######## Operators +=, -=, *=, /= with REAL and complex ##########//

REAL operator += (REAL &a, const RMATRIX &b)
{
	if (b.num==1)
		a+=b(0);
	else ErrorMsg("Error in REAL+=RMATRIX:\nmatrix is not REAL number");
		return a;
}

REAL operator -= (REAL &a, const RMATRIX &b)
{
	if (b.num==1)
		a-=b(0);
	else ErrorMsg("Error in REAL-=RMATRIX:\nmatrix is not REAL number");
		return a;
}

REAL operator *= (REAL &a, const RMATRIX &b)
{
	if (b.num==1)
		a*=b(0);
	else ErrorMsg("Error in REAL*=RMATRIX:\nmatrix is not REAL number");
		return a;
}

REAL operator /= (REAL &a, const RMATRIX &b)
{
	if (b.num==1)
		a/=b(0);
	else ErrorMsg("Error in REAL/=RMATRIX:\nmatrix is not REAL number");
		return a;
}

// ####################### Operator '+' ######################## //

RMATRIX operator + (const RMATRIX &a, const RMATRIX &b)
{
	if ((a.n!=b.n) || (a.m!=b.m))
		ErrorMsg ("Error in 'RMATRIX+RMATRIX':\ndifferent dimensions");
	RMATRIX c(a);
	for (int i=0;i<c.num;i++) c(i)+=b(i);
	return c;
}

RMATRIX operator + (const RMATRIX &a, REAL b)
{
	if (a.n!=a.m)
		ErrorMsg ("Error in 'RMATRIX+REAL':\nmatrix is not square");
	RMATRIX c(a);
	for (int i=0;i<c.n;i++) c(i,i)+=b;
	return c;
}

RMATRIX operator + (REAL b, const RMATRIX &a)
{
	if (a.n!=a.m)
		ErrorMsg ("Error in 'REAL+RMATRIX':\nmatrix is not square");
	RMATRIX c(a);
	for (int i=0;i<c.n;i++) c(i,i)+=b;
	return c;
}

//######################## Operator '-' #########################

RMATRIX RMATRIX::operator - ()
{
	RMATRIX c(n,m);
	for (int i=0; i<num; i++) c(i)=-elem[i];
	return c;
}

RMATRIX RMATRIX::operator - () const
{
	RMATRIX c(n,m);
	for (int i=0; i<num; i++) c(i)=-elem[i];
	return c;
}

RMATRIX operator - (const RMATRIX &a, const RMATRIX &b)
{
	if ((a.n!=b.n) || (a.m!=b.m))
		ErrorMsg ("Error in 'RMATRIX-RMATRIX':\ndifferent dimensions");
	RMATRIX c(a);
	for (int i=0;i<a.num;i++) c(i)-=b(i);
	return c;
}

RMATRIX operator - (const RMATRIX &a, REAL b)
{
	if (a.n!=a.m)
		ErrorMsg ("Error in 'RMATRIX-REAL':\nmatrix is not square");
	RMATRIX c(a);
	for (int i=0;i<c.n;i++) c(i,i)-=b;
	return c;
}

RMATRIX operator - (REAL b, const RMATRIX &a)
{
	if (a.n!=a.m)
		ErrorMsg ("Error in 'REAL-RMATRIX':\nmatrix is not square");
	RMATRIX c(a);
	c=-c;
	for (int i=0;i<c.n;i++) c(i,i)+=b;
	return c;
}

// ######################## Operator '*' #######################

RMATRIX operator * (const RMATRIX &a, const RMATRIX &b)
{
	if (b.num==1) return a*b(0);
	if (a.m!=b.n)
		ErrorMsg ("Error in 'RMATRIX*RMATRIX':\nwrong dimensions");
	RMATRIX c(a.n, b.m);
	for (int i=0;i<a.n;i++)
		for (int k=0;k<b.m;k++)
		{
			c(i,k)=0;
			for (int j=0;j<a.m;j++) 
				c(i,k)+=a(i,j)*b(j,k);
		}
	return c;
}

RMATRIX operator * (const RMATRIX &a, REAL b)
{
	RMATRIX c(a);
	for (int i=0;i<c.num;i++) c(i)*=b;
	return c;
}

RMATRIX operator * (REAL b, const RMATRIX &a)
{
	RMATRIX c(a);
	for (int i=0;i<c.num;i++) c(i)*=b;
	return c;
}

//################### Operator / ##########################

RMATRIX operator / (const RMATRIX &b, const RMATRIX &a)
{
	RMATRIX ms_Inv(const RMATRIX &a0);

	return b*ms_Inv(a);
}

RMATRIX operator / (const RMATRIX &a, REAL b)
{
	if (b==0)
		ErrorMsg ("Error in 'RMATRIX/REAL': matrix is devided by 0");
	RMATRIX c(a);
	for (int i=0;i<c.num;i++) c(i)/=b;
	return c;
}

RMATRIX operator / (REAL b, const RMATRIX &a)
{
	RMATRIX ms_Inv(const RMATRIX &a0);

	return b*ms_Inv(a);
}

// ################## Operators '<<' and '>>' ###################

ostream& operator << (ostream& stream, const RMATRIX &a)
{
	for (int i=0;i<a.n;i++)
	{
		for (int j=0;j<a.m;j++) stream<<a.elem[i*a.m+j]<<"  ";
		stream<<'\n';
	}
	return stream;
}

istream& operator >> (istream& stream, RMATRIX &a)
{
	for (int i=0;i<a.num;i++) stream>>a.elem[i];
	return stream;
}

// ################# Other Operators ################## //

RMATRIX operator ^ (const RMATRIX &a, int n)
{
	if (a.n!=a.m)
		ErrorMsg ("Error in 'RMATRIX ^ int': matrix not square\n");
	RMATRIX ms_Eye(int n);
	RMATRIX c=ms_Eye(a.n);
	if (n==0)  return c;
	if (n>0) for (int i=0;i<n;i++) c*=a;
	else for (int j=0;j>n;j--) c*=a;
	if (n>0) return c;
	else return 1/c;
}

RMATRIX operator ^ (const RMATRIX &a, const RMATRIX &b)
{
	int i,j,k,l;
	int an=a.n, am=a.m, bn=b.n, bm=b.m;
	RMATRIX c(an*bn, am*bm);
	int tmp1=am*b.num, tmp2=am*bm;
	for (i=0;i<an;i++)
		for (j=0;j<bn;j++)
			for (k=0;k<am;k++)
				for (l=0;l<bm;l++)
					c(i*tmp1+j*tmp2+k*bm+l) = a(i,k) * b(j,l);
	return c;
}

REAL& RMATRIX::operator () (int i)
{
	if ((i>=num)||(i<0)) ErrorMsg ("Error in RMATRIX::operator(int)\nBad argument.\n");
	return elem[i];
}

REAL& RMATRIX::operator () (int i,int j)
{
	if ((i>=n)||(j>=m)||(j<0)||(i<0))
		ErrorMsg ("Error in RMATRIX::operator(int,int)\nBad arguments.\n");
	return elem[i*m+j];
}

REAL RMATRIX::operator () (int i) const
{
	if ((i>=num)||(i<0)) ErrorMsg ("Error in RMATRIX::operator(int)\nBad argument.\n");
	return elem[i];
}

REAL RMATRIX::operator () (int i,int j) const
{
	if ((i>=n)||(j>=m)||(j<0)||(i<0))
		ErrorMsg ("Error in RMATRIX::operator(int,int)\nBad arguments.\n");
	return elem[i*m+j];
}

// ################### Functions #########################

void RMATRIX::SwapRow(int s,int d)
{
	if ((s>=n) || (d>=n) || (s<0) || (d<0))
		ErrorMsg ("Error in  'RMATRIX::SwapRow': Bad arguments\n");
	if (s!=d)
		for (int i=0;i<m;i++)
			SWAP (elem[s*m+i], elem[d*m+i]);
	return;
}

void RMATRIX::SwapCol(int s,int d)
{
	if ((s>=m) || (d>=m) || (s<0) || (d<0))
		ErrorMsg ("Error in 'RMATRIX::SwapCol': Bad arguments\n");
	if (s!=d)
		for (int i=0;i<n;i++)
			SWAP (elem[i*m+s], elem[i*m+d]);
	return;
}

/*int RMATRIX::SortMatrix (int l)
// Helper for Det function, and only.
{
	int max=l, i;
	REAL maxval=0;

	for (i=l+1;i<n;i++)
		if (elem[i*m+l]>maxval)
		{
			max=i;
			maxval=elem[i*m+l];
		}
	if (max==l) return 0;
	for (i=l;i<n;i++)
		SWAP (elem[l*n+i], elem[max*n+i]);
	return max;
}
*/
///////////////// Implementations of Vector Class /////////////

RVECTOR::RVECTOR (int n): RMATRIX (n,1) {}

RVECTOR::RVECTOR (void): RMATRIX (dimension_of_space, 1) {}

RVECTOR::RVECTOR (int n, char* str): RMATRIX (n, 1, str) {}

RVECTOR::RVECTOR (const RVECTOR& a): RMATRIX (a.n, 1)
{
	for (int i=0;i<num;i++) elem[i]=a.elem[i];
}

RVECTOR::~RVECTOR(void)
{
	if (elem)
	{
		delete []elem;
		elem=NULL;
	}
}

RVECTOR RVECTOR::operator = (const RMATRIX &a)
{
	if ((a.n==num) && (a.m==1))
		for (int i=0;i<num;i++) elem[i]=a(i);
	else ErrorMsg ("Error in 'RVECTOR=RMATRIX':\nMatrix has diffirent dimention");
	return *this;
}

RVECTOR RVECTOR::operator = (const RVECTOR &a)
{
	if (a.n==num)
		for (int i=0;i<num;i++) elem[i]=a.elem[i];
	else ErrorMsg ("Error in 'RVECTOR=RVECTOR':\nVectors has diffirent dimensions");
		return *this;
}

RVECTOR RVECTOR::operator = (char *a)
{
	istrstream s(a);
	for (int i=0;i<num;i++) s>>elem[i];
	return *this;
}

//////////////// Math operations for Vectors //////////////

RVECTOR operator - (const RVECTOR &a)
{
	RVECTOR c(a.num);
	for (int i=0;i<a.num;i++) c(i)=-a(i);
	return c;
}

RVECTOR operator *= (const RVECTOR &a, const RMATRIX &b)
{
	if (b.num!=1)
		ErrorMsg ("Error in 'RVECTOR*=RMATRIX':\nmatrix is not 1x1\n");
	RVECTOR c(a.num);
	REAL t=b(0);
	for (int i=0;i<a.num;i++) c(i)=a(i)*t;
	return c;
}

///////////// operator + ////////////

REAL operator + (const RVECTOR &a, REAL b)
{
	if (a.num!=1)
		ErrorMsg ("Error in 'RVECTOR+REAL':\nvector is not 1-dimentional\n");
	return a(0)+b;
}

REAL operator + (REAL b, const RVECTOR &a)
{
	if (a.num!=1)
		ErrorMsg ("Error in 'REAL+RVECTOR':\nvector is not 1-dimentional\n");
	return a(0)+b;
}

RVECTOR operator + (const RVECTOR &a, const RVECTOR &b)
{
	if (a.num!=b.num)
		ErrorMsg ("Error in 'RVECTOR+RVECTOR':\nvectors has different dimensions\n");
	RVECTOR c(a.num);
	for (int i=0;i<c.num;i++) c(i) = a(i) + b(i);
	return c;
}

RVECTOR operator + (const RMATRIX &a, const RVECTOR &b)
{
	if ((a.n!=b.num) || (a.m!=1))
		ErrorMsg ("Error in 'RMATRIX+RVECTOR':\ndifferent dimensions\n");
	RVECTOR c(b.num);
	for (int i=0;i<c.num;i++) c(i) = a(i) + b(i);
	return c;
}

RVECTOR operator + (const RVECTOR &a, const RMATRIX &b)
{
	if ((b.n!=a.num) || (b.m!=1))
		ErrorMsg ("Error in 'RVECTOR+RMATRIX':\ndifferent dimensions\n");
	RVECTOR c(b.num);
	for (int i=0;i<c.num;i++) c(i) = a(i) + b(i);
	return c;
}

///////////// operator - //////////////

REAL operator - (const RVECTOR &a, REAL b)
{
	if (a.num!=1)
		ErrorMsg ("Error in 'RVECTOR-REAL':\nvector is not 1-dimentional\n");
	return a(0)-b;
}

REAL operator - (REAL b, const RVECTOR &a)
{
	if (a.num!=1)
		ErrorMsg ("Error in 'REAL-RVECTOR':\nvector is not 1-dimentional\n");
	return b-a(0);
}

RVECTOR operator - (const RVECTOR &a, const RVECTOR &b)
{
	if (a.num!=b.num)
		ErrorMsg ("Error in 'RVECTOR-RVECTOR':\nvectors has different dimensions\n");
	RVECTOR c(a.num);
	for (int i=0;i<c.num;i++) c(i) = a(i) - b(i);
	return c;
}

RVECTOR operator - (const RMATRIX &a, const RVECTOR &b)
{
	if ((a.n!=b.num) || (a.m!=1))
		ErrorMsg ("Error in 'RMATRIX-RVECTOR':\ndifferent dimensions\n");
	RVECTOR c(b.num);
	for (int i=0;i<c.num;i++) c(i) = a(i) - b(i);
	return c;
}

RVECTOR operator - (const RVECTOR &a, const RMATRIX &b)
{
	if ((b.n!=a.num) || (b.m!=1))
		ErrorMsg ("Error in 'RVECTOR-RMATRIX':\ndifferent dimensions\n");
	RVECTOR c(b.num);
	for (int i=0;i<c.num;i++) c(i) = a(i) - b(i);
	return c;
}

////////////// operator * /////////////

RVECTOR operator *  (const RMATRIX &a, const RVECTOR &b)
{
	if (a.m!=b.num)
		ErrorMsg ("Error in 'RMATRIX*RVECTOR':\nwrong dimensions");
	RVECTOR c(a.n);
	REAL t;
	for (int i=0;i<a.n;i++)
	{
		t=0;
		for (int j=0;j<a.m;j++) t+=a(i,j)*b(j);
		c(i)=t;
	}
	return c;
}

RVECTOR operator * (const RVECTOR &a, REAL b)
{
	RVECTOR c(a.num);
	for (int i=0; i<c.num; i++) c(i)=a(i)*b;
	return c;
}

RVECTOR operator * (REAL b, const RVECTOR &a)
{
	RVECTOR c(a.num);
	for (int i=0; i<c.num; i++) c(i)=a(i)*b;
	return c;
}

RVECTOR operator * (const RVECTOR &a, const RVECTOR &b)
{
	if (b.num!=1)
		ErrorMsg ("Error in 'RVECTOR*RVECTOR':\nvector is not 1-dimentional\n");
	RVECTOR c(a.num);
	REAL t=b(0);
	for (int i=0; i<c.num; i++) c(i)=a(i)*t;
	return c;
}

////////////// operator / /////////////

REAL operator / (REAL b, const RVECTOR &a)
{
	if (a.num!=1)
		ErrorMsg ("Error in 'REAL/RVECTOR':\nvector is not 1-dimentional\n");
	return b/a(0);
}

RVECTOR operator / (const RVECTOR &a, REAL b)
{
	RVECTOR c(a.num);
	for (int i=0; i<c.num; i++) c(i)=a(i)/b;
	return c;
}

RVECTOR operator / (const RVECTOR &a, const RMATRIX &b)
{
	if (b.num!=1)
		ErrorMsg ("Error in 'RVECTOR/RMATRIX':\nmatrix is not 1-dimentional\n");
	RVECTOR c(a.num);
	REAL t=b(0);
	for (int i=0; i<c.num; i++) c(i)=a(i)/t;
	return c;
}

//////////////// operators == and != ////////////////////////

int operator == (const RMATRIX &a, const RMATRIX &b)
{
	if ((a.n != b.n) || (a.m != b.m))
		ErrorMsg ("Error in operator == for Matrices : different dimantions");
	int flag = 1;
	for (int i=0; flag && (i<a.num); i++)  flag = (a(i)==b(i));
	return flag;
}

int operator != (const RMATRIX &a, const RMATRIX &b)
{
	if ((a.n != b.n) || (a.m != b.m))
		ErrorMsg ("Error in operator == for Matrices : different dimantions");
	int flag = 0;
	for (int i=0; (!flag) && (i<a.num); i++)  flag = (a(i)!=b(i));
	return flag;
}

/////////////////////////////////////////////////////////////////////////
/*REAL Abs(const RVECTOR &a)
{
	REAL c=0;
	for (int i=0;i<a.num;i++)
		c += SQR(a(i));
	return sqrt(c);
}
*/