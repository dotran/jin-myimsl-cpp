/////////////////////////////////////////////////////////////////////////
// Program  : tstats.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

#include <math.h>
#include "rmatrix.h"

/////////////////////////////////////////////////////////////////////////
// TStats computes performance from the output response of a system and
// returns overshoot(Mp), peak time(tp), rise time(tr), steady-state error(ess)
// and settling time(ts) (opts=0: 2% ts, otherwise: 5% ts)
void ms_TStats(REAL t[],REAL y[],REAL yr,int n,REAL &mp,REAL &tp,REAL &tr,REAL &ts,REAL &ess, int opts)
{
	int i, i10= 0, i90= 0, iess= 0, pass= 0;
	REAL ymax, t0, t1, y0, y1, t10, t90, per;
	REAL ms_VMax(REAL v[], int n, int &iv);

	ymax= ms_VMax(y, n, i);
	mp= (ymax >= yr) ? 100.0*(ymax-yr)/yr : 0.0;
	tp= (ymax >= yr) ? t[i] : 0.0;
	ess= fabs(yr-y[n-1]);
	per= (opts == 0) ? 0.02:0.05;
	for(i=0; i<n; i++)
	{
		if(pass == 0)
			if(y[i] <= 0.1*yr) 
				i10= i;
			else
				pass= 1;
		else if(pass == 1)
			if(y[i] <= 0.9*yr) 
				i90= i;
			else
				pass= 2;
		if(fabs(yr-y[i]) > per) // 2% or 5% ts
			iess= i;
	}

	if(pass == 2)
	{
		t0= t[i90]; y0= y[i90];
		t1= t[i90+1]; y1= y[i90+1];
		t90= t1-(t1-t0)*(y1-0.9*yr)/(y1-y0);

		t0= t[i10]; y0= y[i10];
		t1= t[i10+1]; y1= y[i10+1];
		t10= t1-(t1-t0)*(y1-0.1*yr)/(y1-y0);
		tr= t90-t10;
	}
	else
		tr= t[n-1];
	if(iess == n-1)
		ts= t[n-1];
	else
	{
		t0= t[iess]; 
		t1= t[iess+1];
		ts= (t0+t1)/2.0;
	}
	return;
}

/////////////////////////////////////////////////////////////////////////
// TStats computes performance from the output response of a system and
// returns overshoot(Mp), peak time(tp), rise time(tr), steady-state error(ess)
// and settling time(ts) (opts=0: 2% ts, otherwise: 5% ts)
void ms_TStats(const RVECTOR &t,const RVECTOR &y,REAL yr,REAL &mp,REAL &tp,REAL &tr,REAL &ts,REAL &ess, int opts)
{
	int i, i10= 0, i90= 0, iess= 0, pass= 0, n=t.num;
	REAL ymax, t0, t1, y0, y1, t10, t90, per;
	REAL ms_VMax(const RVECTOR &v, int &iv);

	if(t.num!=y.num)
		ErrorMsg("Error in 'TStats': Check the sizes of t and y");
	ymax= ms_VMax(y, i);
	mp= (ymax >= yr) ? 100.0*(ymax-yr)/yr : 0.0;
	tp= (ymax >= yr) ? t(i) : 0.0;
	ess= fabs(yr-y(n-1));
	per= (opts == 0) ? 0.02:0.05;
	for(i=0; i<n; i++)
	{
		if(pass == 0)
			if(y(i) <= 0.1*yr) 
				i10= i;
			else
				pass= 1;
		else if(pass == 1)
			if(y(i) <= 0.9*yr) 
				i90= i;
			else
				pass= 2;
		if(fabs(yr-y(i)) > per) // 2% or 5% ts
			iess= i;
	}

	if(pass == 2)
	{
		t0= t(i90); y0= y(i90);
		t1= t(i90+1); y1= y(i90+1);
		t90= t1-(t1-t0)*(y1-0.9*yr)/(y1-y0);

		t0= t(i10); y0= y(i10);
		t1= t(i10+1); y1= y(i10+1);
		t10= t1-(t1-t0)*(y1-0.1*yr)/(y1-y0);
		tr= t90-t10;
	}
	else
		tr= t(n-1);
	if(iess == n-1)
		ts= t(n-1);
	else
	{
		t0= t(iess); 
		t1= t(iess+1);
		ts= (t0+t1)/2.0;
	}
	return;
}
