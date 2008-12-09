/////////////////////////////////////////////////////////////////////////
// Program  : cmatrix.cpp
// Coded by : Version 15.3
// Coded on : 12/12/2003

#include <stdio.h>
#include "cmatrix.h"

/////////////////////////////////////////////////////////////////////////
// Constructors and Destructors
CMATRIX::CMATRIX(int v1,int v2):n(v1),m(v2)
{
	num=n*m;
	elem=new COMPLEX[num];
}

CMATRIX::CMATRIX(int v1,int v2, char *a):n(v1),m(v2)
{
	num=n*m;
	elem=new COMPLEX[num];
	istrstream s(a);
	for (int i=0;i<num;i++) s>>elem[i].Re>>elem[i].Im;
}

CMATRIX::CMATRIX(const CMATRIX &mat):n(mat.n),m(mat.m)
{
	num=n*m;
	elem=new COMPLEX[num];
	for (int i=0;i<num;i++) elem[i]=mat.elem[i];
}

CMATRIX::CMATRIX(void)
{
	n=m=dimension_of_space; // By default 4*4 matrix is defined 
	num=n*m;
	elem=new COMPLEX[num];
}

CMATRIX::~CMATRIX(void)
{
	if (elem)
	{
		delete []elem;
		elem=NULL;
	}
}

// =, +=, -=, *=, /= with Matrices
CMATRIX CMATRIX::operator = (const CMATRIX &a)
{
	if ((a.m==m) && (a.n==n))
		for (int i=0;i<num;i++) elem[i]=a.elem[i];
	else ErrorMsg ("Error in 'CMATRIX=CMATRIX':\nmatrices has diffirent dimensions");
		return *this;
}

CMATRIX CMATRIX::operator = (char *a)
{
	istrstream s(a);
	for (int i=0;i<num;i++) s>>elem[i].Re>>elem[i].Im;
	return *this;
}

CMATRIX CMATRIX::operator += (const CMATRIX &a)
{
	if ((a.m==m) && (a.n==n))
		for (int i=0;i<num;i++) elem[i]+=a.elem[i];
	else ErrorMsg ("Error in 'CMATRIX+=CMATRIX':\nmatrices has diffirent dimensions");
	return *this;
}

CMATRIX CMATRIX::operator += (const COMPLEX &a)
{
	if (n==m)
		for (int i=0;i<num;i++) elem[i*m+i]+=a;
	else ErrorMsg ("Error in 'CMATRIX+=COMPLEX':\nmatrix is not square");
	return *this;
}

CMATRIX CMATRIX::operator += (double a)
{
	if (n==m)
		for (int i=0;i<num;i++) elem[i*m+i]+=a;
	else ErrorMsg ("Error in 'CMATRIX+=double':\nmatrix is not square");
	return *this;
}

CMATRIX CMATRIX::operator -= (const CMATRIX &a)
{
	if ((a.m==m) && (a.n==n))
		for (int i=0;i<num;i++) elem[i]-=a.elem[i];
	else ErrorMsg ("Error in 'CMATRIX-=CMATRIX':\nmatrices has diffirent dimensions");
	return *this;
}

CMATRIX CMATRIX::operator -= (const COMPLEX &a)
{
	if (n==m)
		for (int i=0;i<num;i++) elem[i*m+i]-=a;
	else ErrorMsg ("Error in 'CMATRIX-=COMPLEX':\nmatrix is not square");
	return *this;
}

CMATRIX CMATRIX::operator -= (double a)
{
	if (n==m)
		for (int i=0;i<num;i++) elem[i*m+i]-=a;
	else ErrorMsg ("Error in 'CMATRIX-=double':\nmatrix is not square");
	return *this;
}

CMATRIX CMATRIX::operator *= (const CMATRIX &b)
{
	if (m==b.n)
		*this = *this * b;
	else ErrorMsg ("Error in 'CMATRIX*=CMATRIX':\nBad dimensions");
	return *this;
}

CMATRIX CMATRIX::operator *= (const COMPLEX &a)
{
	for (int i=0;i<num;i++) elem[i]*=a;
	return *this;
}

CMATRIX CMATRIX::operator *= (double a)
{
	for (int i=0;i<num;i++) elem[i]*=a;
	return *this;
}

CMATRIX CMATRIX::operator /= (const CMATRIX &a)
{
	if (a.num==1)
		for (int i=0;i<num;i++) elem[i]/=*a.elem;
	else ErrorMsg ("Error in 'CMATRIX/=CMATRIX':\nBad dimantions");
		return *this;
}

CMATRIX CMATRIX::operator /= (const COMPLEX &a)
{
	for (int i=0;i<num;i++) elem[i]/=a;
	return *this;
}

CMATRIX CMATRIX::operator /= (double a)
{
	for (int i=0;i<num;i++) elem[i]/=a;
	return *this;
}

// Operators +=, -=, *=, /= with double and complex
double operator += (double &a, const CMATRIX &b)
{
	if ((b.num==1) && (fabs(b(0).Im)<Precision))
		a+=b(0).Re;
	else ErrorMsg("Error in double+=CMATRIX:\nmatrix is not double number");
	return a;
}

double operator -= (double &a, const CMATRIX &b)
{
	if ((b.num==1) && (fabs(b(0).Im)<Precision))
		a-=b(0).Re;
	else ErrorMsg("Error in double-=CMATRIX:\nmatrix is not double number");
	return a;
}

double operator *= (double &a, const CMATRIX &b)
{
	if ((b.num==1) && (fabs(b(0).Im)<Precision))
		a*=b(0).Re;
	else ErrorMsg("Error in double*=CMATRIX:\nmatrix is not double number");
	return a;
}

double operator /= (double &a, const CMATRIX &b)
{
	if ((b.num==1) && (fabs(b(0).Im)<Precision))
		a/=b(0).Re;
	else ErrorMsg("Error in double/=CMATRIX:\nmatrix is not double number");
		return a;
}

COMPLEX operator += (COMPLEX &a, const CMATRIX &b)
{
	if (b.num==1)
		a+=b(0);
	else ErrorMsg("Error in COMPLEX+=CMATRIX:\nmatrix is not 1x1");
		return a;
}

COMPLEX operator -= (COMPLEX &a, const CMATRIX &b)
{
	if (b.num==1)
		a-=b(0);
	else ErrorMsg("Error in COMPLEX-=CMATRIX:\nmatrix is not 1x1");
		return a;
}

COMPLEX operator *= (COMPLEX &a, const CMATRIX &b)
{
	if (b.num==1)
		a*=b(0);
	else ErrorMsg("Error in COMPLEX*=CMATRIX:\nmatrix is not 1x1");
		return a;
}

COMPLEX operator /= (COMPLEX &a, const CMATRIX &b)
{
	if (b.num==1)
		a/=b(0);
	else ErrorMsg("Error in COMPLEX/=CMATRIX:\nmatrix is not 1x1");
		return a;
}

// Operator '+'
CMATRIX operator + (const CMATRIX &a, const CMATRIX &b)
{
	if ((a.n!=b.n) || (a.m!=b.m))
		ErrorMsg ("Error in 'CMATRIX+CMATRIX':\ndifferent dimensions");
	CMATRIX c(a);
	for (int i=0;i<c.num;i++) c(i)+=b(i);
	return c;
}

CMATRIX operator + (const CMATRIX &a, const COMPLEX &b)
{
	if (a.n!=a.m)
		ErrorMsg ("Error in 'CMATRIX+COMPLEX':\nmatrix is not square");
	CMATRIX c(a);
	for(int i=0;i<c.n;i++) c(i,i)+=b;
	return c;
}

CMATRIX operator + (const COMPLEX &b, const CMATRIX &a)
{
	if (a.n!=a.m)
		ErrorMsg ("Error in 'COMPLEX+CMATRIX':\nmatrix is not square");
	CMATRIX c(a);
	for(int i=0;i<c.n;i++) c(i,i)+=b;
	return c;
}

CMATRIX operator + (const CMATRIX &a, double b)
{
	if (a.n!=a.m)
		ErrorMsg ("Error in 'CMATRIX+double':\nmatrix is not square");
	CMATRIX c(a);
	for(int i=0;i<c.n;i++) c(i,i)+=b;
	return c;
}

CMATRIX operator + (double b, const CMATRIX &a)
{
	if (a.n!=a.m)
		ErrorMsg ("Error in 'double+CMATRIX':\nmatrix is not square");
	CMATRIX c(a);
	for(int i=0;i<c.n;i++) c(i,i)+=b;
	return c;
}

// Operator '-'
CMATRIX CMATRIX::operator - ()
{
	CMATRIX c(n,m);
	for (int i=0; i<num; i++) c(i)=-elem[i];
	return c;
}

CMATRIX CMATRIX::operator - () const
{
	CMATRIX c(n,m);
	for (int i=0; i<num; i++) c(i)=-elem[i];
	return c;
}

CMATRIX operator - (const CMATRIX &a, const CMATRIX &b)
{
	if ((a.n!=b.n) || (a.m!=b.m))
		ErrorMsg ("Error in 'CMATRIX-CMATRIX':\ndifferent dimensions");
	CMATRIX c(a);
	for (int i=0;i<a.num;i++) c(i)-=b(i);
	return c;
}

CMATRIX operator - (const CMATRIX &a, const COMPLEX &b)
{
	if (a.n!=a.m)
		ErrorMsg ("Error in 'CMATRIX-COMPLEX':\nmatrix is not square");
	CMATRIX c(a);
	for(int i=0;i<c.n;i++) c(i,i)-=b;
	return c;
}

CMATRIX operator - (const COMPLEX &b, const CMATRIX &a)
{
	if (a.n!=a.m)
		ErrorMsg ("Error in 'COMPLEX-CMATRIX':\nmatrix is not square");
	CMATRIX c(a);
	c=-c;
	for(int i=0;i<c.n;i++) c(i,i)+=b;
	return c;
}

CMATRIX operator - (const CMATRIX &a, double b)
{
	if (a.n!=a.m)
		ErrorMsg ("Error in 'CMATRIX-double':\nmatrix is not square");
	CMATRIX c(a);
	for(int i=0;i<c.n;i++) c(i,i)-=b;
	return c;
}

CMATRIX operator - (double b, const CMATRIX &a)
{
	if (a.n!=a.m)
		ErrorMsg ("Error in 'double-CMATRIX':\nmatrix is not square");
	CMATRIX c(a);
	c=-c;
	for(int i=0;i<c.n;i++) c(i,i)+=b;
	return c;
}

// Operator '*'
CMATRIX operator * (const CMATRIX &a, const CMATRIX &b)
{
	if (b.num==1) return a*b(0);
	if (a.m!=b.n)
		ErrorMsg ("Error in 'CMATRIX*CMATRIX':\nwrong dimensions");
	CMATRIX c(a.n, b.m);
	COMPLEX t;
	for (int i=0;i<a.n;i++)
		for (int k=0;k<b.m;k++)
		{
			t=0;
			for (int j=0;j<a.m;j++) t+=a(i,j)*b(j,k);
			c(i,k)=t;
		}
	return c;
}

CMATRIX operator * (const CMATRIX &a, const COMPLEX &b)
{
	CMATRIX c(a);
	for (int i=0;i<c.num;i++) c(i)*=b;
	return c;
}

CMATRIX operator * (const COMPLEX &b, const CMATRIX &a)
{
	CMATRIX c(a);
	for (int i=0;i<c.num;i++) c(i)*=b;
	return c;
}

CMATRIX operator * (const CMATRIX &a, double b)
{
	CMATRIX c(a);
	for (int i=0;i<c.num;i++) c(i)*=b;
	return c;
}

CMATRIX operator * (double b, const CMATRIX &a)
{
	CMATRIX c(a);
	for (int i=0;i<c.num;i++) c(i)*=b;
	return c;
}

// Operator / 
CMATRIX operator / (const CMATRIX &b, const CMATRIX &a)
{
	return b*ms_Inv(a);
}

CMATRIX operator / (const CMATRIX &a, const COMPLEX &b)
{
	CMATRIX c(a);
	for (int i=0;i<c.num;i++) c(i)/=b;
	return c;
}

CMATRIX operator / (const COMPLEX &b, const CMATRIX &a)
{
	return b*ms_Inv(a);
}

CMATRIX operator / (const CMATRIX &a, double b)
{
	CMATRIX c(a);
	for (int i=0;i<c.num;i++) c(i)/=b;
	return c;
}

CMATRIX operator / (double b, const CMATRIX &a)
{
	return b*ms_Inv(a);
}

// Operators '<<' and '>>'
ostream& operator << (ostream& stream, const CMATRIX &a)
{
	for (int i=0;i<a.n;i++)
	{
		for (int j=0;j<a.m;j++) stream<<a.elem[i*a.m+j]<<"  ";
		stream<<'\n';
	}
	return stream;
}

istream& operator >> (istream& stream, CMATRIX &a)
{
	for (int i=0;i<a.num;i++) stream>>a.elem[i];
	return stream;
}

// Other Operators
CMATRIX CMATRIX::operator ! ()
{
	CMATRIX c(m,n);
	for (int i=0; i<m; i++)
		for (int j=0; j<n; j++)  c(i,j)=!elem[j*m+i];
	return c;
}

CMATRIX CMATRIX::operator ! () const
{
	CMATRIX c(m,n);
	for (int i=0; i<m; i++)
		for (int j=0; j<n; j++)  c(i,j)=!elem[j*m+i];
	return c;
}

CMATRIX operator ^ (const CMATRIX &a, int n)
{
	if (a.n!=a.m)
		ErrorMsg ("Error in 'CMATRIX ^ n': matrix is not square\n");
	CMATRIX c(a.n,a.n);
	ms_Eye(c);
	if (n==0)  return c;
	if (n>0) for (int i=0;i<n;i++) c*=a;
	else for (int j=0;j>n;j--) c*=a;
	if (n>0) return c;
	else return 1/c;
}

CMATRIX operator ^ (const CMATRIX &a, const CMATRIX &b)
{
	int i,j,k,l;
	int an=a.n, am=a.m, bn=b.n, bm=b.m;
	CMATRIX c(an*bn, am*bm);
	int tmp1=am*b.num, tmp2=am*bm;
	for (i=0;i<an;i++)
		for (j=0;j<bn;j++)
			for (k=0;k<am;k++)
				for (l=0;l<bm;l++)
					c(i*tmp1+j*tmp2+k*bm+l) = a(i,k) * b(j,l);
	return c;
}

COMPLEX& CMATRIX::operator () (int i)
{
        if ((i>=num)||(i<0)) ErrorMsg ("Error in CMATRIX::operator(int)\nBad argument.\n");
        return elem[i];
}

COMPLEX& CMATRIX::operator () (int i,int j)
{
        if ((i>=n)||(j>=m)||(j<0)||(i<0))
                ErrorMsg ("Error in CMATRIX::operator(int,int)\nBad arguments.\n");
        return elem[i*m+j];
}

COMPLEX CMATRIX::operator () (int i) const
{
        if ((i>=num)||(i<0)) ErrorMsg ("Error in CMATRIX::operator(int)\nBad argument.\n");
        return elem[i];
}

COMPLEX CMATRIX::operator () (int i,int j) const
{
        if ((i>=n)||(j>=m)||(j<0)||(i<0))
                ErrorMsg ("Error in CMATRIX::operator(int,int)\nBad arguments.\n");
        return elem[i*m+j];
}

// Functions
#define CSWAP(a,b) {temp=(a);(a)=(b);(b)=temp;}

void CMATRIX::SwitchLines (int s,int d)
{
        if ((s>=n) || (d>=n) || (s<0) || (d<0))
                ErrorMsg ("Error in  CMATRIX::SwitchLines\nBad arguments\n");
        COMPLEX temp;
        if (s!=d)
                for (int i=0;i<m;i++)
                   CSWAP (elem[s*m+i], elem[d*m+i]);
        return;
}

void CMATRIX::SwitchColumns (int s,int d)
{
        if ((s>=m) || (d>=m) || (s<0) || (d<0))
                ErrorMsg ("Error in  CMATRIX::SwitchColumns\nBad arguments\n");
        COMPLEX temp;
        if (s!=d)
                for (int i=0;i<n;i++)
                   CSWAP (elem[i*m+s], elem[i*m+d]);
        return;
}

int CMATRIX::SortMatrix (int l)
// Helper for Det function, and only.
{
	int max=l, i;
	COMPLEX maxval,temp;

	for (i=l+1;i<n;i++)
	if (elem[i*m+l]>maxval)
	{
		max=i;
		maxval=elem[i*m+l];
	}
	if (max==l) return 0;
	for (i=l;i<n;i++)
		CSWAP (elem[l*n+i], elem[max*n+i]);
	return max;
}

///////////////// Implementations of Vector Class /////////////

CVECTOR::CVECTOR (int n)
        : CMATRIX (n,1) {}

CVECTOR::CVECTOR (void)
        : CMATRIX (dimension_of_space, 1) {}

CVECTOR::CVECTOR (int n, char* str)
        : CMATRIX (n, 1, str) {}

CVECTOR::CVECTOR (const CVECTOR& a)
        : CMATRIX (a.n, 1)
{
        for (int i=0;i<num;i++) elem[i]=a.elem[i];
}

CVECTOR::~CVECTOR(void)
{
        if (elem)
        {
                delete []elem;
                elem=NULL;
        }
}

CVECTOR CVECTOR::operator = (const CMATRIX &a)
{
        if ((a.n==num) && (a.m==1))
                for (int i=0;i<num;i++) elem[i]=a(i);
        else ErrorMsg ("Error in 'CVECTOR=CMATRIX':\nMatrix has diffirent dimention");
        return *this;
}

CVECTOR CVECTOR::operator = (const CVECTOR &a)
{
        if (a.n==num)
                for (int i=0;i<num;i++) elem[i]=a.elem[i];
        else ErrorMsg ("Error in 'CVECTOR=CVECTOR':\nVectors has diffirent dimensions");
        return *this;
}

CVECTOR CVECTOR::operator = (char *a)
{
        istrstream s(a);
        for (int i=0;i<num;i++) s>>elem[i].Re>>elem[i].Im;
        return *this;
}

//////////////// Math operations for Vectors //////////////

CVECTOR operator - (const CVECTOR &a)
{
        CVECTOR c(a.num);
        for (int i=0;i<a.num;i++) c(i)=-a(i);
        return c;
}

CVECTOR operator *= (const CVECTOR &a, const CMATRIX &b)
{
        if (b.num!=1)
                ErrorMsg ("Error in 'CVECTOR*=CMATRIX':\nmatrix is not 1x1\n");
        CVECTOR c(a.num);
        COMPLEX t=b(0);
        for (int i=0;i<a.num;i++) c(i)=a(i)*t;
        return c;
}

///////////// operator + ////////////

COMPLEX operator + (const CVECTOR &a, const COMPLEX &b)
{
        if (a.num!=1)
                ErrorMsg ("Error in 'CVECTOR+COMPLEX':\nvector is not 1-dimentional");
        return a(0)+b;
}

COMPLEX operator + (const COMPLEX &b, const CVECTOR &a)
{
        if (a.num!=1)
                ErrorMsg ("Error in 'COMPLEX+CVECTOR':\nvector is not 1-dimentional\n");
        return a(0)+b;
}

COMPLEX operator + (const CVECTOR &a, double b)
{
        if (a.num!=1)
                ErrorMsg ("Error in 'CVECTOR+double':\nvector is not 1-dimentional\n");
        return a(0)+b;
}

COMPLEX operator + (double b, const CVECTOR &a)
{
        if (a.num!=1)
                ErrorMsg ("Error in 'double+CVECTOR':\nvector is not 1-dimentional\n");
        return a(0)+b;
}

CVECTOR operator + (const CVECTOR &a, const CVECTOR &b)
{
        if (a.num!=b.num)
                ErrorMsg ("Error in 'CVECTOR+CVECTOR':\nvectors has different dimensions\n");
        CVECTOR c(a.num);
        for (int i=0;i<c.num;i++) c(i) = a(i) + b(i);
        return c;
}

CVECTOR operator + (const CMATRIX &a, const CVECTOR &b)
{
        if ((a.n!=b.num) || (a.m!=1))
                ErrorMsg ("Error in 'CMATRIX+CVECTOR':\ndifferent dimensions\n");
        CVECTOR c(b.num);
        for (int i=0;i<c.num;i++) c(i) = a(i) + b(i);
        return c;
}

CVECTOR operator + (const CVECTOR &a, const CMATRIX &b)
{
        if ((b.n!=a.num) || (b.m!=1))
                ErrorMsg ("Error in 'CVECTOR+CMATRIX':\ndifferent dimensions\n");
        CVECTOR c(b.num);
        for (int i=0;i<c.num;i++) c(i) = a(i) + b(i);
        return c;
}

///////////// operator - //////////////

COMPLEX operator - (const CVECTOR &a, const COMPLEX &b)
{
        if (a.num!=1)
                ErrorMsg ("Error in 'CVECTOR-COMPLEX':\nvector is not 1-dimentional\n");
        return a(0)-b;
}

COMPLEX operator - (const COMPLEX &b, const CVECTOR &a)
{
        if (a.num!=1)
                ErrorMsg ("Error in 'COMPLEX-CVECTOR':\nvector is not 1-dimentional\n");
        return b-a(0);
}

COMPLEX operator - (const CVECTOR &a, double b)
{
        if (a.num!=1)
                ErrorMsg ("Error in 'CVECTOR-double':\nvector is not 1-dimentional\n");
        return a(0)-b;
}

COMPLEX operator - (double b, const CVECTOR &a)
{
        if (a.num!=1)
                ErrorMsg ("Error in 'double-CVECTOR':\nvector is not 1-dimentional\n");
        return b-a(0);
}

CVECTOR operator - (const CVECTOR &a, const CVECTOR &b)
{
        if (a.num!=b.num)
                ErrorMsg ("Error in 'CVECTOR-CVECTOR':\nvectors has different dimensions\n");
        CVECTOR c(a.num);
        for (int i=0;i<c.num;i++) c(i) = a(i) - b(i);
        return c;
}

CVECTOR operator - (const CMATRIX &a, const CVECTOR &b)
{
        if ((a.n!=b.num) || (a.m!=1))
                ErrorMsg ("Error in 'CMATRIX-CVECTOR':\ndifferent dimensions\n");
        CVECTOR c(b.num);
        for (int i=0;i<c.num;i++) c(i) = a(i) - b(i);
        return c;
}

CVECTOR operator - (const CVECTOR &a, const CMATRIX &b)
{
        if ((b.n!=a.num) || (b.m!=1))
                ErrorMsg ("Error in 'CVECTOR-CMATRIX':\ndifferent dimensions\n");
        CVECTOR c(b.num);
        for (int i=0;i<c.num;i++) c(i) = a(i) - b(i);
        return c;
}

////////////// operator * /////////////

CVECTOR operator *  (const CMATRIX &a, const CVECTOR &b)
{
        if (a.m!=b.num)
                ErrorMsg ("Error in 'CMATRIX*CVECTOR':\nwrong dimensions");
        CVECTOR c(a.n);
        COMPLEX t;
        for (int i=0;i<a.n;i++)
        {
                t=0;
                for (int j=0;j<a.m;j++) t+=a(i,j)*b(j);
                c(i)=t;
        }
        return c;
}

CVECTOR operator * (const CVECTOR &a, const COMPLEX &b)
{
        CVECTOR c(a.num);
        for (int i=0; i<c.num; i++) c(i)=a(i)*b;
        return c;
}

CVECTOR operator * (const CVECTOR &a, double b)
{
        CVECTOR c(a.num);
        for (int i=0; i<c.num; i++) c(i)=a(i)*b;
        return c;
}

CVECTOR operator * (const COMPLEX &b, const CVECTOR &a)
{
        CVECTOR c(a.num);
        for (int i=0; i<c.num; i++) c(i)=a(i)*b;
        return c;
}

CVECTOR operator * (double b, const CVECTOR &a)
{
        CVECTOR c(a.num);
        for (int i=0; i<c.num; i++) c(i)=a(i)*b;
        return c;
}

CVECTOR operator * (const CVECTOR &a, const CVECTOR &b)
{
        if (b.num!=1)
                ErrorMsg ("Error in 'CVECTOR*CVECTOR':\nvector is not 1-dimentional\n");
        CVECTOR c(a.num);
        COMPLEX t=b(0);
        for (int i=0; i<c.num; i++) c(i)=a(i)*t;
        return c;
}

////////////// operator / /////////////

COMPLEX operator / (const COMPLEX &b, const CVECTOR &a)
{
        if (a.num!=1)
                ErrorMsg ("Error in 'COMPLEX/CVECTOR':\nvector is not 1-dimentional\n");
        return b/a(0);
}

COMPLEX operator / (double b, const CVECTOR &a)
{
        if (a.num!=1)
                ErrorMsg ("Error in 'double/CVECTOR':\nvector is not 1-dimentional\n");
        return b/a(0);
}

CVECTOR operator / (const CVECTOR &a, const COMPLEX &b)
{
        CVECTOR c(a.num);
        for (int i=0; i<c.num; i++) c(i)=a(i)/b;
        return c;
}

CVECTOR operator / (const CVECTOR &a, double b)
{
        CVECTOR c(a.num);
        for (int i=0; i<c.num; i++) c(i)=a(i)/b;
        return c;
}

CVECTOR operator / (const CVECTOR &a, const CMATRIX &b)
{
        if (b.num!=1)
                ErrorMsg ("Error in 'CVECTOR/CMATRIX':\nmatrix is not 1-dimentional\n");
        CVECTOR c(a.num);
        COMPLEX t=b(0);
        for (int i=0; i<c.num; i++) c(i)=a(i)/t;
        return c;
}

//////////////// operators == and != ////////////////////////

int operator == (const CMATRIX &a, const CMATRIX &b)
{
        if ((a.n != b.n) || (a.m != b.m))
                ErrorMsg ("Error in operator == for Matrices : different dimantions");
        int flag = 1;
        for (int i=0; flag && (i<a.num); i++)  flag = (a(i)==b(i));
        return flag;
}


int operator != (const CMATRIX &a, const CMATRIX &b)
{
        if ((a.n != b.n) || (a.m != b.m))
                ErrorMsg ("Error in operator == for Matrices : different dimantions");
        int flag = 0;
        for (int i=0; (!flag) && (i<a.num); i++)  flag = (a(i)!=b(i));
        return flag;
}

#undef CSWAP

