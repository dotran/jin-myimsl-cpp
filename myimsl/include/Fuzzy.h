/////////////////////////////////////////////////////////////////////////
// Program  : fuzzy.h
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 2007/08/17
//
#ifndef _FUZZY_H_
#define _FUZZY_H_

#include "realtype.h"

//#define TDFL 1        // define TDFL if you want REAL= float
#ifdef TDFL
typedef float    REAL;
#else
typedef double   REAL;
#endif
enum {TRAPMF=0, TRIMF, GBELLMF, SIGMF, GAUSSMF};
enum {MAMDANI=0, SUGENO};
enum {COG=0, MOM, SOM, LOM};
enum {NONE= -1, MIN, MAX, PRODUCT, SUM};
#ifndef MAX2
static REAL _maxarg11,_maxarg12;
#define MAX2(a,b) (_maxarg11=(a),_maxarg12=(b),(_maxarg11) > (_maxarg12) ?\
        (_maxarg11) : (_maxarg12))
#endif

#ifndef MIN2
static REAL _minarg11,_minarg12;
#define MIN2(a,b) (_minarg11=(a),_minarg12=(b),(_minarg11) < (_minarg12) ?\
        (_minarg11) : (_minarg12))
#endif
#ifndef max_no_input  // default input number
#define max_no_input   5
#endif
#ifndef max_no_fset   // default fuzzy set number
#define max_no_fset    7
#endif
#ifndef max_no_rule   // default rule number
#define max_no_rule   20
#endif
#ifndef max_no_level  // default level number
#define max_no_level  11
#endif

class FUZZY
{
protected:

public:

	int maxninput, maxnlevel, maxnrule, maxnfset;
	int InfType, NumInputs, *NumInputMFs, NumOutputMFs, NumRules;
	int AndMethod, OrMethod, ImpMethod, AggMethod, DefuzzMethod;
	int *InNumLevel, OutNumLevel;
	int *InMFTypes, *OutMFTypes;            // definition of input and output MF types
	int **RuleConnection;                    // definition of rule connectives
	int **RuleAntecedent, *RuleConsequent;  // definition of rules
	REAL **InRange, *OutRange;	
	REAL **InMFParams, **OutMFParams;       // definition of input and output MFs
	void MamInfer(REAL cInp[], REAL vOut[]);
	void SugInfer(REAL cInp[], REAL vOut[]);
	REAL RuleConn(int method, REAL alpha1, REAL alpha2);
	void FuzzImp(int method, REAL alpha, REAL fInp[], REAL fOut[]);
	void FuzzAgg(int method, REAL fInp1[], REAL fInp2[], REAL fOut[]);
	REAL MemGrade(int mftype, REAL x, REAL p[]);
	void MemFunc(int mftype, REAL p[], REAL Range[], int nlevel, REAL fOut[]);
	void SetInFSet(int no, int mftype, REAL p1, REAL p2, REAL p3=0, REAL p4=0);
	void SetOutFSet(int no, int mftype, REAL p1, REAL p2, REAL p3=0, REAL p4=0);

	FUZZY(int ni=max_no_input, int ns=max_no_fset, int nr=max_no_rule); // constructor
	~FUZZY();
};

void CheckInput(FUZZY &fl, REAL cInp[]);
REAL InferDefuzz(FUZZY &fl, REAL cInp[]);

#endif // _FUZZY_H_