/////////////////////////////////////////////////////////////////////////
// Program  : diffeqs.h
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 02/03/2003
//
#ifndef _DIFFEQS_H_
#define _DIFFEQS_H_

#include "realtype.h"

#ifndef max_no_order    // maximum default order of the model
#define max_no_order    10
#endif
#ifndef max_no_delay    // maximum default size of time delay buffer
#define max_no_delay    1000
#endif

/////////////////////////////////////////////////////////////////////////
// class DIFFEQS
class DIFFEQS
{
protected:

public:
	int maxn, maxnbuf, idx;
	REAL *dy, *du, *x, *TimeDelayBuf;
	REAL TimeDelay(REAL u, int nd);
	void InitTimeDelay(REAL initvalue);
	
	friend void InitDSim(DIFFEQS &de, REAL du[], int m, REAL dy[], int n, REAL initvalue=0);
	friend REAL DSim(DIFFEQS &de, REAL u, REAL pb[], int m, REAL pa[], int n, int nd=0);
	friend void InitLSim(DIFFEQS &de, REAL x[], int n, REAL initvalue=0);
	friend REAL LSim(DIFFEQS &de, REAL u, REAL pb[], REAL pa[], int n, REAL t, REAL h, REAL L=0);
	DIFFEQS(int n=max_no_order, int nd=max_no_delay);
	~DIFFEQS();
};

	void Rkqs(REAL u, REAL x[], int n, REAL t, REAL h,
		void (*derivs)(REAL u, REAL x[], int n, REAL t, REAL ak[]));
	void Rkqs(REAL u, REAL x[], REAL pa[], int n, REAL t, REAL h,
		void (*derivs)(REAL u, REAL x[], REAL pa[], int n, REAL t, REAL ak[]));

#endif // _DIFFEQS_H_
