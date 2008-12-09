/////////////////////////////////////////////////////////////////////////
// Program  : realtype.h
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 02/03/2003
//
#ifndef _REALTYPE_H_
#define _REALTYPE_H_

//#define TDFL 1        // define TDFL if you want REAL= float
#ifdef TDFL
typedef float    REAL;
#else
typedef double   REAL;
#endif
typedef int      BOOL;

/////////////////////////////////////////////////////////////////////////
// Inline functions
#ifndef PI
#define PI 3.141592653589793238462643
#endif

#ifndef Precision
#define Precision 1e-8
#endif

#ifndef euler_constant
#define euler_constant 0.577215664901532860606512
#endif

#ifndef IMAX
static int _imaxarg1,_imaxarg2;
#define IMAX(a,b) (_imaxarg1=(a),_imaxarg2=(b),(_imaxarg1) > (_imaxarg2) ?\
        (_imaxarg1) : (_imaxarg2))
#endif

#ifndef IMIN
static int _iminarg1,_iminarg2;
#define IMIN(a,b) (_iminarg1=(a),_iminarg2=(b),(_iminarg1) < (_iminarg2) ?\
        (_iminarg1) : (_iminarg2))
#endif

#ifndef MAX
static REAL _maxarg1,_maxarg2;
#define MAX(a,b) (_maxarg1=(a),_maxarg2=(b),(_maxarg1) > (_maxarg2) ?\
        (_maxarg1) : (_maxarg2))
#endif

#ifndef MIN
static REAL _minarg1,_minarg2;
#define MIN(a,b) (_minarg1=(a),_minarg2=(b),(_minarg1) < (_minarg2) ?\
        (_minarg1) : (_minarg2))
#endif

#ifndef IABS
static int _iabsarg;
#define IABS(a) ((_iabsarg=(a)) >= 0.0 ? (_iabsarg) : -(_iabsarg))
#endif

#ifndef ABS
static REAL _absarg;
#define ABS(a) ((_absarg=(a)) >= 0.0 ? (_absarg) : -(_absarg))
#endif

#ifndef SQR
static REAL _sqrarg;
#define SQR(a) ((_sqrarg=(a)) == 0.0 ? 0.0 : _sqrarg*_sqrarg)
#endif

#ifndef ISIGN
#define ISIGN(a,b) ((b) >= 0 ? IABS(a) : -IABS(a))
#endif

#ifndef SIGN
#define SIGN(a,b) ((b) >= 0.0 ? ABS(a) : -ABS(a))
#endif

#ifndef ISWAP
#define ISWAP(a,b) {int iswaparg=(a);(a)=(b);(b)=iswaparg;}
#endif

#ifndef SWAP
#define SWAP(a,b) {REAL swaparg=(a);(a)=(b);(b)=swaparg;}
#endif

#ifndef Round
#define Round(a)  (int)((a)<0.0 ? ((a)-0.5) : ((a)+0.5))
#endif

/////////////////////////////////////////////////////////////////////////
// Function name redefinition related to matrix and vector allocation/free
#define IVector ms_IVector
#define RVector ms_RVector
#define IMatrix ms_IMatrix
#define RMatrix ms_RMatrix
#define Free_IVector ms_Free_IVector
#define Free_RVector ms_Free_RVector
#define Free_IMatrix ms_Free_IMatrix
#define Free_RMatrix ms_Free_RMatrix
#define SubMatrix ms_SubMatrix
#define ConvertMatrix ms_ConvertMatrix
#define Free_ConvertMatrix ms_Free_ConvertMatrix
#define Free_SubMatrix ms_Free_SubMatrix

/////////////////////////////////////////////////////////////////////////
// Function name redefinition related to matrix and vector allocation/free
#define CumSum ms_CumSum
#define COut ms_COut
#define Det ms_Det
#define Eigen ms_Eigen
#define Eye ms_Eye
#define Fft ms_Fft 
#define FMin ms_FMin
#define FZero ms_FZero
#define Hermit ms_Hermit
#define IFft ms_IFft 
#define Inv ms_Inv
#define LinSol ms_LinSol
#define LinSpace ms_LinSpace
#define LogSpace ms_LogSpace
#define Locate ms_Locate
#define Mean ms_Mean
#define Minor ms_Minor
#define MInpt ms_MInpt 
#define MOut ms_MOut 
#define NextPow2 ms_NextPow2
#define Norm1 ms_Norm1
#define Norm2 ms_Norm2
#define Norm8 ms_Norm8
#define Norm ms_Norm2
#define Ones ms_Ones
#define Poly ms_Poly
#define PolyFit ms_PolyFit
#define Powell ms_Powell
#define Roots ms_Roots
#define Sort ms_Sort
#define Spline ms_Spline
#define Sum ms_Sum
#define Trace ms_Trace
#define Trans ms_Trans
#define TStats ms_TStats
#define VInpt ms_VInpt
#define VMax ms_VMax
#define VMin ms_VMin
#define VOut ms_VOut
#define Zeros ms_Zeros
#define Filter ms_Filter
#define Conv ms_Conv

/////////////////////////////////////////////////////////////////////////
// Function name redefinition related to random number generators
#define BernRnd ms_BernRnd
#define BinoRnd ms_BinoRnd
#define Chi2Rnd ms_Chi2Rnd
#define EquiRnd ms_EquiRnd
#define ErlRnd ms_ErlRnd
#define ExpRnd ms_ExpRnd
#define Flip ms_Flip
#define GeoRnd ms_GeoRnd
#define GetSeed ms_GetSeed
#define LognRnd ms_LognRnd
#define NormRnd ms_NormRnd
#define PasRnd ms_PasRnd
#define PickUp ms_PickUp
#define PoissRnd ms_PoissRnd
#define Prbs ms_Prbs
#define Rand ms_Rand
#define SetRandState ms_SetRandState
#define SRand ms_SRand
#define SRands ms_SRands
#define StudRnd ms_StudRnd
#define UnifRnd ms_UnifRnd

/////////////////////////////////////////////////////////////////////////
// Error message functions
void ErrorMsg(char *msg);        
void WarningMsg(char *msg);

/////////////////////////////////////////////////////////////////////////
// Allocation and free functions of vectors and matrices
int* ms_IVector(long n);                  // allocates an integer vector
int* ms_IVector(long nl, long nh);
REAL* ms_RVector(long n);                 // allocates a real vector
REAL* ms_RVector(long nl, long nh);
int** ms_IMatrix(long nr, long nl);       // allocates an integer matrix
int** ms_IMatrix(long nrl, long nrh, long ncl, long nch);
REAL** ms_RMatrix(long nr, long nl);      // allocates a real matrix
REAL** ms_RMatrix(long nrl, long nrh, long ncl, long nch);
void ms_Free_IVector(int* v);             // frees the allocated integer vector
void ms_Free_IVector(int* v, long nl, long nh);
void ms_Free_RVector(REAL* v);            // frees the allocated real vector
void ms_Free_RVector(REAL* v, long nl, long nh);
void ms_Free_IMatrix(int** mat);          // frees the allocated integer matrix
void ms_Free_IMatrix(int** mat, long nrl, long nrh, long ncl, long nch);
void ms_Free_RMatrix(REAL** mat);         // frees the allocated real matrix
void ms_Free_RMatrix(REAL** mat, long nrl, long nrh, long ncl, long nch);
REAL** ms_SubMatrix(REAL** a, long oldrl, long oldrh, long oldcl, long oldch,
	long newrl, long newcl);
REAL** ms_ConvertMatrix(REAL* a, long nrl, long nrh, long ncl, long nch);
void ms_Free_SubMatrix(REAL** a, long nrl, long nrh, long ncl, long nch);
void ms_Free_ConvertMatrix(REAL** a, long nrl, long nrh, long ncl, long nch);

/////////////////////////////////////////////////////
// Additional double functions
double cot(double);
double sec(double);
double csc(double);
double coth(double);
double sech(double);
double csch(double);
double Gamma(int);
double Gamma(double);
double Beta(int,int);
double GarmonicSeries(int);
double BesselJ(double,int);
double Bessely(double,int);

#endif // _REALTYPE_H_