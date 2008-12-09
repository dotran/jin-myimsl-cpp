/////////////////////////////////////////////////////////////////////////
// Program  : eigen.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include <math.h>
#include "cmatrix.h"

/////////////////////////////////////////////////////////////////////////
// (C) Copr. 1986-92 Numerical Recipes Software
void ms_Eigen(REAL **a, int m, REAL rtr[], REAL rti[])
{
	int j,k;
	REAL **hess,xr,xi;
	void balanc(REAL **a, int n);
	void elmhes(REAL **a, int n);
	void hqr(REAL **a, int n, REAL wr[], REAL wi[]);

	hess= RMatrix(1,m,1,m);
	hess= ConvertMatrix(&a[0][0],1,m,1,m);
	
	balanc(hess,m);
	elmhes(hess,m);
	hqr(hess,m,rtr-1,rti-1);
	for(j=1;j<m;j++) 
	{
		xr=rtr[j];
		xi=rti[j];
		for(k=j-1;k>=0;k--) 
		{
			if(rtr[k] <= xr) break;
			rtr[k+1]=rtr[k];
			rti[k+1]=rti[k];
		}
		rtr[k+1]=xr;
		rti[k+1]=xi;
	}
	Free_ConvertMatrix(hess,1,m,1,m);
}

/////////////////////////////////////////////////////////////////////////
// Computes the eigenvalues of a REAL matrix 
CVECTOR ms_Eigen(const RMATRIX &a)
{
	int j,k,m=a.n;
	REAL **hess,*rtr,*rti,xr,xi;
	CVECTOR c(m);
	void balanc(REAL **a, int n);
	void elmhes(REAL **a, int n);
	void hqr(REAL **a, int n, REAL wr[], REAL wi[]);

	if(a.n!=a.m)
		ErrorMsg("Error in 'Eigen(RMATRIX)': Matrix is not square");
	hess= RMatrix(1,m,1,m);
	rtr= RVector(m);
	rti= RVector(m);
	for(j=0;j<m;j++)
		for(k=0;k<m;k++)
			hess[j+1][k+1]= a(j,k);
		
	balanc(hess,m);
	elmhes(hess,m);
	hqr(hess,m,rtr-1,rti-1);
	for(j=1;j<m;j++) 
	{
		xr=rtr[j];
		xi=rti[j];
		for(k=j-1;k>=0;k--) 
		{
			if(rtr[k] <= xr) break;
			rtr[k+1]=rtr[k];
			rti[k+1]=rti[k];
		}
		rtr[k+1]=xr;
		rti[k+1]=xi;
	}
	for(j=0;j<m;j++)
		c(j).Set(rtr[j],rti[j]);

	Free_RMatrix(hess,1,m,1,m);
	Free_RVector(rtr);
	Free_RVector(rti);
	return c;
}

/////////////////////////////////////////////////////////////////////////
// Computes the eigenvalues of a COMPLEX matrix 
CVECTOR ms_Eigen(const CMATRIX &f)
{
	int i;
	COMPLEX t, tt;
	CVECTOR v(f.n);
	void HermitEigen(const CMATRIX &f, CVECTOR &v, CMATRIX &m);

	if (f.n!=f.m)
		ErrorMsg("Error in 'Eigen(CMATRIX)': Matrix is not square");
	switch (f.n)
	{
    case 1:
       {
          v(0)=f(0);
          return v;
       }
    case 2:
       {
          COMPLEX z[2];
          Solve2 (z, -Trace(f), Det(f));
          v(0) = z[0];
          v(1) = z[1];
          ms_Sort(v);
          return v;
       }
    case 3:
       {
          t = f(0,0)*f(1,1) + f(1,1)*f(2,2) + f(0,0)*f(2,2)
            - f(0,1)*f(1,0) - f(1,2)*f(2,1) - f(0,2)*f(2,0);
          COMPLEX z[3];
          Solve3 (z, -Trace(f), t, -Det(f));
          for (i=0; i<3; i++)  v(i) = z[i];
          ms_Sort(v);
          return v;
       }

    case 4:
       {
          t = f(0,0)*f(1,1) + f(1,1)*f(2,2) + f(2,2)*f(0,0)
            + f(0,0)*f(3,3) + f(1,1)*f(3,3) + f(2,2)*f(3,3)
            - f(0,1)*f(1,0) - f(1,2)*f(2,1) - f(0,2)*f(2,0)
            - f(0,3)*f(3,0) - f(1,3)*f(3,1) - f(2,3)*f(3,2);
          tt = - (f(1,1)*f(2,2)*f(3,3) + f(0,0)*f(2,2)*f(3,3) +
                f(0,0)*f(1,1)*f(3,3) + f(0,0)*f(1,1)*f(2,2));
          tt += f(3,3) * ( f(0,1)*f(1,0) + f(1,2)*f(2,1) + f(0,2)*f(2,0) );
          tt += f(2,2) * ( f(0,1)*f(1,0) + f(0,3)*f(3,0) + f(1,3)*f(3,1) );
          tt += f(1,1) * ( f(0,2)*f(2,0) + f(2,3)*f(3,2) + f(0,3)*f(3,0) );
          tt += f(0,0) * ( f(2,1)*f(1,2) + f(2,3)*f(3,2) + f(1,3)*f(3,1) );
          tt -= f(0,1)*f(1,2)*f(2,0) + f(0,2)*f(2,1)*f(1,0) +
                f(0,2)*f(2,3)*f(3,0) + f(0,3)*f(3,2)*f(2,0) +
                f(0,1)*f(1,3)*f(3,0) + f(0,3)*f(3,1)*f(1,0) +
                f(1,2)*f(2,3)*f(3,1) + f(1,3)*f(3,2)*f(2,1);
          COMPLEX z[4];
          Solve4 (z, -Trace(f), t, tt, Det(f));
          for (i=0; i<4; i++)  v(i) = z[i];
          ms_Sort(v);
          return v;
       }

    default:
       {
          if (f==(!f))
          {
            CMATRIX m(f.n, f.m);
            HermitEigen(f, v, m);
          }
          else ErrorMsg ("Matrix is not Hermitian");
          return v;
       }
    }
}

/////////////////////////////////////////////////////////////////////////
// Eigenvalues and Vectors.
#define CSWAP(a,b) {temp=(a);(a)=(b);(b)=temp;}
void HermitEigen(const CMATRIX &f, CVECTOR &v, CMATRIX &m)
{
	int n=f.n, n2=2*n, num2=2*f.num, i,j, base, base2;
  double *a = new double [2*num2];
  double *d = new double [n2];
  COMPLEX temp;
	void FindEigen (double a[], int n, double d[]);

  for (i=0; i<n; i++)
   {
      base  = i*n;
      base2 = i*n2;
      for (j=0; j<n; j++)
      {
         a[base2+j       ] =  f(base+j).Re;
         a[base2+j+n     ] = -f(base+j).Im;
         a[base2+j  +num2] =  f(base+j).Im;
         a[base2+j+n+num2] =  f(base+j).Re;
      }
   }
   FindEigen (a,n2,d);
   for (i=0; i<n; i++) v(i) = d[i];
   for (i=0; i<n; i++)
   {
      base2 = i*n2;
      for (j=0; j<n; j++)
        m(i,j).Set(a[num2+base2+j*2], -a[base2+j*2]);
   }

   CVECTOR vv = v;
   ms_Sort(v);
   for (i=0; i<n-1; i++)
      for (j=i; j<n; j++)
         if (v(i)==vv(j))
         {
            m.SwitchColumns(i,j);
            CSWAP (vv(i), vv(j));
            break;
         }

   delete a;
   delete d;
}
#undef CSWAP

void FindEigen (double a[], int n, double d[])
{
	double *e = new double[n];
	double scale,hh,h,g,f,s,r,p,dd,c,b;
	int l,k,j,i,m,iter;
	double modul (double a, double b);

	for (i=n-1; i>=1; i--)
	{
		l=i-1;
		h=scale=0.0;
		if (l > 0)
		{
			for (k=0; k<=l; k++)
				scale += fabs(a[i*n+k]);
			if (scale == 0.0)
				e[i]=a[i*n+l];
			else
			{
				for (k=0; k<=l; k++)
				{
					a[i*n+k] /= scale;
					h += sqr(a[i*n+k]);
				}
				f=a[i*n+l];
				g=(f >= 0.0 ? -sqrt(h) : sqrt(h));
				e[i]=scale*g;
				h -= f*g;
				a[i*n+l]=f-g;
				f=0.0;
				for (j=0; j<=l; j++)
				{
					a[j*n+i]=a[i*n+j]/h;
					g=0.0;
					for (k=0; k<=j; k++)
						g += a[j*n+k]*a[i*n+k];
					for (k=j+1; k<=l; k++)
						g += a[k*n+j]*a[i*n+k];
					e[j]=g/h;
					f += e[j]*a[i*n+j];
				}
				hh=f/(h+h);
				for (j=0; j<=l; j++)
				{
                        f=a[i*n+j];
                        e[j]=g=e[j]-hh*f;
                         for (k=0; k<=j; k++)
                                   a[j*n+k] -= (f*e[k]+g*a[i*n+k]);
                }
              }
      }
      else e[i]=a[i*n+l];
      d[i]=h;
   }
        d[0]=0.0;
        e[0]=0.0;
        for (i=0; i<n; i++)
   {
                l=i-1;
                if (d[i])
      {
                        for (j=0; j<=l; j++)
         {
                                g=0.0;
                                for (k=0; k<=l; k++)
                                        g += a[i*n+k]*a[k*n+j];
                                for (k=0; k<=l; k++)
                                        a[k*n+j] -= g*a[k*n+i];
                        }
                }
                d[i]=a[i*n+i];
                a[i*n+i]=1.0;
                for (j=0; j<=l; j++) a[j*n+i]=a[i*n+j]=0.0;
        }

        for (i=1; i<n; i++) e[i-1]=e[i];
        e[n-1]=0.0;
        for (l=0; l<n; l++)
   {
                iter=0;
                do
      {
                        for (m=l; m<n-1; m++)
         {
                                dd=fabs(d[m])+fabs(d[m+1]);
                                if ((double)(fabs(e[m])+dd) == dd) break;
                        }
                        if (m != l)
         {
                                if (iter++ == 30)
               ErrorMsg ("Too many iterations in eigen5");
                                g=(d[l+1]-d[l])/(2.0*e[l]);
                                r=modul(g,1);
                                g=d[m]-d[l]+e[l]/(g + (g>=0 ? r : -r));
                                s=c=1.0;
                                p=0.0;
                                for (i=m-1; i>=l; i--)
            {
                                        f=s*e[i];
                                        b=c*e[i];
                                        e[i+1]=(r=modul(f,g));
                                        if (r == 0.0)
               {
                                                d[i+1] -= p;
                                                e[m]=0.0;
                                                break;
                                        }
                                        s=f/r;
                                        c=g/r;
                                        g=d[i+1]-p;
                                        r=(d[i]-g)*s+2.0*c*b;
                                        d[i+1]=g+(p=s*r);
                                        g=c*r-b;
                                        for (k=0; k<n; k++)
               {
                                                f=a[k*n+i+1];
                                                a[k*n+i+1]=s*a[k*n+i]+c*f;
                                                a[k*n+i]=c*a[k*n+i]-s*f;
                                        }
                                }
                                if (r == 0.0 && i >= l) continue;
                                d[l] -= p;
                                e[l]=g;
                                e[m]=0.0;
			}
		} while (m != l);
	}
	delete e;
}

double modul (double a, double b)
{
	double absa = fabs(a);
	double absb = fabs(b);
	if (absa > absb)
		return absa*sqrt(1.0+SQR(absb/absa));
	else
		return (absb == 0.0 ? 0.0 : absb*sqrt(1.0+SQR(absa/absb)));
}

/////////////////////////////////////////////////////////////////////////
// 
#define RADIX 2.0
void balanc(REAL **a, int n)
{
	int last,j,i;
	REAL s,r,g,f,c,sqrdx;

	sqrdx=RADIX*RADIX;
	last=0;
	while(last == 0) 
	{
		last=1;
		for(i=1;i<=n;i++) 
		{
			r=c=0.0;
			for(j=1;j<=n;j++)
				if(j != i) 
				{
					c += fabs(a[j][i]);
					r += fabs(a[i][j]);
				}
			if(c && r) 
			{
				g=r/RADIX;
				f=1.0;
				s=c+r;
				while(c<g) 
				{
					f *= RADIX;
					c *= sqrdx;
				}
				g=r*RADIX;
				while (c>g) 
				{
					f /= RADIX;
					c /= sqrdx;
				}
				if((c+r)/f < 0.95*s) 
				{
					last=0;
					g=1.0/f;
					for(j=1;j<=n;j++) a[i][j] *= g;
					for(j=1;j<=n;j++) a[j][i] *= f;
				}
			}
		}
	}
}
#undef RADIX

/////////////////////////////////////////////////////////////////////////
// 
void elmhes(REAL **a, int n)
{
	int m,j,i;
	REAL y,x;

	for (m=2;m<n;m++) {
		x=0.0;
		i=m;
		for (j=m;j<=n;j++) {
			if (fabs(a[j][m-1]) > fabs(x)) {
				x=a[j][m-1];
				i=j;
			}
		}
		if (i != m) {
			for (j=m-1;j<=n;j++) SWAP(a[i][j],a[m][j])
			for (j=1;j<=n;j++) SWAP(a[j][i],a[j][m])
		}
		if (x) {
			for (i=m+1;i<=n;i++) {
				if ((y=a[i][m-1]) != 0.0) {
					y /= x;
					a[i][m-1]=y;
					for (j=m;j<=n;j++)
						a[i][j] -= y*a[m][j];
					for (j=1;j<=n;j++)
						a[j][m] += y*a[j][i];
				}
			}
		}
	}
}
/////////////////////////////////////////////////////////////////////////
// 
void hqr(REAL **a, int n, REAL wr[], REAL wi[])
{
	int nn,m,l,k,j,its,i,mmin;
	REAL z,y,x,w,v,u,t,s,r,q,p,anorm;

	anorm=fabs(a[1][1]);
	for(i=2;i<=n;i++)
		for(j=(i-1);j<=n;j++)
			anorm += fabs(a[i][j]);
	nn=n;
	t=0.0;
	while(nn >= 1) {
		its=0;
		do{
			for(l=nn;l>=2;l--) 
			{
				s=fabs(a[l-1][l-1])+fabs(a[l][l]);
				if(s == 0.0) s=anorm;
				if((REAL)(fabs(a[l][l-1]) + s) == s) break;
			}
			x=a[nn][nn];
			if(l == nn) 
			{
				wr[nn]=x+t;
				wi[nn--]=0.0;
			} 
			else 
			{
				y=a[nn-1][nn-1];
				w=a[nn][nn-1]*a[nn-1][nn];
				if(l == (nn-1)) 
				{
					p=0.5*(y-x);
					q=p*p+w;
					z=sqrt(fabs(q));
					x += t;
					if(q >= 0.0) 
					{
						z=p+SIGN(z,p);
						wr[nn-1]=wr[nn]=x+z;
						if (z) wr[nn]=x-w/z;
						wi[nn-1]=wi[nn]=0.0;
					} 
					else 
					{
						wr[nn-1]=wr[nn]=x+p;
						wi[nn-1]= -(wi[nn]=z);
					}
					nn -= 2;
				} 
				else 
				{
					if(its == 30) ErrorMsg("Too many iterations in hqr");
					if(its == 10 || its == 20) 
					{
						t += x;
						for (i=1;i<=nn;i++) a[i][i] -= x;
						s=fabs(a[nn][nn-1])+fabs(a[nn-1][nn-2]);
						y=x=0.75*s;
						w = -0.4375*s*s;
					}
					++its;
					for(m=(nn-2);m>=l;m--) 
					{
						z=a[m][m];
						r=x-z;
						s=y-z;
						p=(r*s-w)/a[m+1][m]+a[m][m+1];
						q=a[m+1][m+1]-z-r-s;
						r=a[m+2][m+1];
						s=fabs(p)+fabs(q)+fabs(r);
						p /= s;
						q /= s;
						r /= s;
						if (m == l) break;
						u=fabs(a[m][m-1])*(fabs(q)+fabs(r));
						v=fabs(p)*(fabs(a[m-1][m-1])+fabs(z)+fabs(a[m+1][m+1]));
						if ((REAL)(u+v) == v) break;
					}
					for(i=m+2;i<=nn;i++) 
					{
						a[i][i-2]=0.0;
						if (i != (m+2)) a[i][i-3]=0.0;
					}
					for(k=m;k<=nn-1;k++) 
					{
						if (k != m) {
							p=a[k][k-1];
							q=a[k+1][k-1];
							r=0.0;
							if(k != (nn-1)) r=a[k+2][k-1];
							if((x=fabs(p)+fabs(q)+fabs(r)) != 0.0) 
							{
								p/= x;
								q/= x;
								r/= x;
							}
						}
						if ((s=SIGN(sqrt(p*p+q*q+r*r),p)) != 0.0) 
						{
							if (k == m) 
							{
								if (l != m)
								a[k][k-1] = -a[k][k-1];
							} else
								a[k][k-1] = -s*x;
							p += s;
							x=p/s;
							y=q/s;
							z=r/s;
							q /= p;
							r /= p;
							for(j=k;j<=nn;j++) 
							{
								p=a[k][j]+q*a[k+1][j];
								if (k != (nn-1)) {
									p += r*a[k+2][j];
									a[k+2][j] -= p*z;
								}
								a[k+1][j] -= p*y;
								a[k][j] -= p*x;
							}
							mmin = nn<k+3 ? nn : k+3;
							for(i=l;i<=mmin;i++) 
							{
								p=x*a[i][k]+y*a[i][k+1];
								if (k != (nn-1)) {
									p += z*a[i][k+2];
									a[i][k+2] -= p*r;
								}
								a[i][k+1] -= p*q;
								a[i][k] -= p;
							}
						}
					}
				}
			}
		} while (l < nn-1);
	}
}

