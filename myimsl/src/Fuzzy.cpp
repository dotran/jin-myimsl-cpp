/////////////////////////////////////////////////////////////////////////
// Program  : fuzzy.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 2007/08/17
//
#include <math.h>
#include "imsl.h"
#include "fuzzy.h"

///////////////////// Implementation of CLASS FUZZY /////////////////////
// Constructors
FUZZY::FUZZY(int ni, int ns, int nr):maxninput(ni),maxnfset(ns),maxnrule(nr)
{
	NumInputMFs= IVector(maxninput);               // allocation for the numbers of input MFs
	InNumLevel= IVector(maxninput);                // allocation for the level numbers of input MFs
	InMFTypes= IVector(maxninput*maxnfset);        // allocation for the types of input MFs
	OutMFTypes= IVector(maxnfset);                 // allocation for the types of output MFs
	RuleConsequent= IVector(maxnrule);             // allocation for rule consequent
	RuleAntecedent= IMatrix(maxnrule, maxninput);  // allocation for rule antecedent
	RuleConnection= IMatrix(maxnrule, maxninput);  // allocation for rule connection
	OutRange= RVector(2);                          // allocation for the output ranges
	InRange= RMatrix(maxninput,2);                 // allocation for the input ranges
	InMFParams= RMatrix(maxninput*maxnfset,4);	   // allocation for the parameters of input MFs
	OutMFParams= RMatrix(maxnfset,4);              // allocation for the parameters of output MFs
}

/////////////////////////////////////////////////////////////////////////
// Destructors
FUZZY::~FUZZY()
{
	Free_IVector(NumInputMFs);
	Free_IVector(InNumLevel);
	Free_IVector(InMFTypes);
	Free_IVector(OutMFTypes);
	Free_IVector(RuleConsequent);
	Free_IMatrix(RuleAntecedent);
	Free_IMatrix(RuleConnection);
	Free_RVector(OutRange);
	Free_RMatrix(InRange);
	Free_RMatrix(InMFParams);
	Free_RMatrix(OutMFParams);
}

/////////////////////////////////////////////////////////////////////////
//  Mamdani-type inference 
void FUZZY::MamInfer(REAL cInp[], REAL vOut[])
{
	int i, j, n, idx;
	REAL alpha, alpha1;
	REAL *fset= new REAL [OutNumLevel], *fset1= new REAL [OutNumLevel];
	enum {AND=0, OR};

	for(j= 0; j < OutNumLevel; j++)
		vOut[j]= 0.0;
	for(j= 0; j < NumRules; j++) 
	{
		n= RuleAntecedent[j][0];
		idx= 0;

		if(n<0)
			alpha= 0;
		else
			alpha= MemGrade(InMFTypes[n], cInp[0], InMFParams[n]);
		for(i= 1; i < NumInputs; i++) 
		{
			idx+= NumInputMFs[i-1];
			n= RuleAntecedent[j][i];
			if(n<0)
				alpha1= 0;
			else
				alpha1= MemGrade(InMFTypes[n+idx], cInp[i], InMFParams[n+idx]);

			switch(RuleConnection[j][i-1])
			{
				case AND: 
					alpha= RuleConn(AndMethod, alpha, alpha1);
					break;
				case OR:
					alpha= MAX2(alpha, alpha1);
					break;
				default:
					ErrorMsg("Error in 'MamInfer': Rule connection fault");
					break;
			}			
		}

		n= RuleConsequent[j];
		MemFunc(OutMFTypes[n], OutMFParams[n], OutRange, OutNumLevel, fset);
		FuzzImp(ImpMethod, alpha, fset, fset1);
		FuzzAgg(AggMethod, fset1, vOut, vOut);
	}
	delete []fset;
	delete []fset1;
}

/////////////////////////////////////////////////////////////////////////
//  Sugeno-type inference 
void FUZZY::SugInfer(REAL cInp[], REAL vOut[])
{
	int i, j, k, n, idx;
	REAL alpha, alpha1, fx;
	enum {AND=0, OR};


	for(j= 0; j < 2; j++)
		vOut[j]= 0.0;
	for(j= 0; j < NumRules; j++) 
	{
		n= RuleAntecedent[j][0];
		idx= 0;

		if(n<0)
			alpha= 0;
		else
			alpha= MemGrade(InMFTypes[n], cInp[0], InMFParams[n]);
		for(i= 1; i < NumInputs; i++) 
		{
			idx+= NumInputMFs[i-1];
			n= RuleAntecedent[j][i];
			if(n<0)
				alpha1= 0;
			else
				alpha1= MemGrade(InMFTypes[n+idx], cInp[i], InMFParams[n+idx]);

			switch(RuleConnection[j][i-1])
			{
				case AND: 
					alpha= RuleConn(AndMethod, alpha, alpha1);
					break;
				case OR:
					alpha= MAX2(alpha, alpha1);
					break;
				default:
					ErrorMsg("Error in 'SugInfer': Rule connection fault");
					break;
			}			
		}

		n= RuleConsequent[j];
		vOut[0]+= alpha;
		fx= OutMFParams[n][0];
		for(k= 1; k < NumInputs; k++) 
			fx+= OutMFParams[n][k+1]*cInp[k];
		vOut[1]+= alpha*fx;
	}
}

/////////////////////////////////////////////////////////////////////////
// Implements the rule connective
REAL FUZZY::RuleConn(int method, REAL alpha1, REAL alpha2)
{
	REAL alpha;

	switch(method)
	{
		case MIN: 
			alpha= MIN2(alpha1, alpha2); 
			break;
		case PRODUCT:
			alpha= alpha1*alpha2;
			break;
		default:
			ErrorMsg("Error in 'RuleConn': Use MIN or PRODUCT");
			break;
	}
	return alpha;
}

/////////////////////////////////////////////////////////////////////////
// Implements the fuzzy implication
void FUZZY::FuzzImp(int method, REAL alpha, REAL fInp[], REAL fOut[])
{
	int i;

	switch(method)
	{
		case MIN: 
			for(i= 0; i < OutNumLevel; i++) 
				fOut[i]= MIN2(alpha, fInp[i]);
			break;
		case PRODUCT:
			for(i= 0; i < OutNumLevel; i++) 
				fOut[i]= alpha*fInp[i];
			break;
		default:
			ErrorMsg("Error in 'FuzzImp': Use MIN or PRODUCT");
			break;
	}
}

/////////////////////////////////////////////////////////////////////////
// Aggregates the inferred result
void FUZZY::FuzzAgg(int method, REAL fInp1[], REAL fInp2[], REAL fOut[])
{
	int i;

	switch(method)
	{
		case MAX: 
			for(i= 0; i < OutNumLevel; i++) 
				fOut[i]= MAX2(fInp1[i], fInp2[i]); 
			break;
		case SUM:
			for(i= 0; i < OutNumLevel; i++) 
				fOut[i]= fInp1[i]+fInp2[i];
			break;
		default:
			ErrorMsg("Error in 'FuzzAgg': Use MAX or SUM");
			break;
	}
}

/////////////////////////////////////////////////////////////////////////
// Calculates the membership grade of a fuzzy set
REAL FUZZY::MemGrade(int mftype, REAL x, REAL p[])
{
	REAL y;
	REAL Trapmf(REAL x, REAL p1, REAL p2, REAL p3, REAL p4);
	REAL Trimf(REAL x, REAL p1, REAL p2, REAL p3);
	REAL Sigmf(REAL x, REAL a, REAL c);
	REAL Gbellmf(REAL x, REAL a, REAL b, REAL c);
	REAL Gaussmf(REAL x, REAL sig, REAL c);

	switch (mftype)
	{
		case TRAPMF: 
			y= Trapmf(x, p[0], p[1], p[2], p[3]);
			break;
		case TRIMF:
			y= Trimf(x, p[0], p[1], p[2]);
			break;
		case GBELLMF:
			y= Gbellmf(x, p[0], p[1], p[2]);
			break;
		case SIGMF:
			y= Sigmf(x, p[0], p[1]);
			break;
		case GAUSSMF:
			y= Gaussmf(x, p[0], p[1]);
			break;
		default:
			ErrorMsg("Error in 'MemGrade': use one of the reserved MFs");
			break;
	}
	return y; 
}

/////////////////////////////////////////////////////////////////////////
// Gets the membership function of a fuzzy set
void FUZZY::MemFunc(int mftype, REAL p[], REAL Range[], int nlevel, REAL fOut[])
{
	REAL Trapmf(REAL x, REAL p1, REAL p2, REAL p3, REAL p4);
	REAL Trimf(REAL x, REAL p1, REAL p2, REAL p3);
	REAL Sigmf(REAL x, REAL a, REAL c);
	REAL Gbellmf(REAL x, REAL a, REAL b, REAL c);
	REAL Gaussmf(REAL x, REAL sig, REAL c);
	REAL x, h;

	if(nlevel <= 1)	ErrorMsg("Error in 'MemFunc': level Number must be greater than 1");
	h= (Range[1]-Range[0])/(nlevel-1);
	x= Range[0];
	for(int i=0; i<nlevel; i++)
	{
		switch (mftype)
		{
			case TRAPMF: 
				fOut[i]= Trapmf(x, p[0], p[1], p[2], p[3]);
				break;
			case TRIMF:
				fOut[i]= Trimf(x, p[0], p[1], p[2]);
				break;
			case GBELLMF:
				fOut[i]= Gbellmf(x, p[0], p[1], p[2]);
				break;
			case SIGMF:
				fOut[i]= Sigmf(x, p[0], p[1]);
				break;
			case GAUSSMF:
				fOut[i]= Gaussmf(x, p[0], p[1]);
				break;
			default:
				ErrorMsg("Error in 'MemFunc': use one of the reserved MFs");
				break;
		}
		x+= h;
	}
	return; 
}


/////////////////////////////////////////////////////////////////////////
// checks the ranges of the crisp inputs 
void CheckInput(FUZZY &fl, REAL cInp[])
{
	for(int i=0; i<fl.NumInputs; i++)
		if(cInp[i] < fl.InRange[i][0])
			cInp[i]= fl.InRange[i][0];
		else if (cInp[i] > fl.InRange[i][1])
			cInp[i]= fl.InRange[i][1];
}

//////////////////////////////////////////////////////////////////////////
// Infer and defuzzify the fuzzy system using a given method
REAL InferDefuzz(FUZZY &fl, REAL cInp[])
{
	REAL CogDefuzz(REAL x[], REAL ifs[], int n);
	REAL MomDefuzz(REAL x[], REAL ifs[], int n);
	REAL SomDefuzz(REAL x[], REAL ifs[], int n);
	REAL LomDefuzz(REAL x[], REAL ifs[], int n);
	REAL cOut, *x, *fInp;

	fInp= RVector(fl.OutNumLevel);
	switch(fl.InfType)
	{
		case MAMDANI: 
			fl.MamInfer(cInp, fInp);
			x= RVector(fl.OutNumLevel);
			ms_LinSpace(fl.OutRange[0], fl.OutRange[1], fl.OutNumLevel, x);
			switch(fl.DefuzzMethod)
			{
				case COG: 
					cOut= CogDefuzz(x, fInp, fl.OutNumLevel);
					break;
				case MOM:
					cOut= MomDefuzz(x, fInp, fl.OutNumLevel);
					break;
				case SOM:
					cOut= SomDefuzz(x, fInp, fl.OutNumLevel);
					break;
				case LOM:
					cOut= LomDefuzz(x, fInp, fl.OutNumLevel);
					break;
				default:
					ErrorMsg("Error in 'Defuzz': use COG, MOM, SOM or LOM");
					break;
			}
			Free_RVector(x);
			break;
		case SUGENO: 
			fl.SugInfer(cInp, fInp);
			cOut= fInp[1]/fInp[0];
			break;
		default:
			ErrorMsg("Error in 'Infer': Use MAMDANI or SUGENO");
	}
	Free_RVector(fInp);
	return cOut;
}

/////////////////////////////////////////////////////////////////////////
// Defuzzify a fuzzy set using the center of gravity method(COG)
REAL CogDefuzz(REAL x[], REAL ifs[], int n)
{
	int i;
	REAL nval, dval;

	nval= 0.0;
	dval= 0.0;
	for(i= 0; i < n; i++)
		if(ifs[i] > 0.0)
		{
			nval+= ifs[i]*x[i];
			dval+= ifs[i];
		}
	return((dval > 0.0) ? nval/dval : 0.0);
}

/////////////////////////////////////////////////////////////////////////
// Defuzzify a fuzzy set using the smallest of maximum method(SOM)
REAL SomDefuzz(REAL x[], REAL ifs[], int n)
{
	int i, j1, j2;
	REAL maxval;

	maxval= ms_VMax(ifs, n, j1);
	for(i= j1; i < n; i++)
		if(ifs[i] == maxval)
			j2= i;
	if(x[j1] > 0 && x[j2] > 0)
		return x[j1];
	else if(x[j1] < 0 && x[j2] < 0)
		return x[j2];
	else 
		return 0;
}

/////////////////////////////////////////////////////////////////////////
// Defuzzify a fuzzy set using the largest of maximum method(LOM)
REAL LomDefuzz(REAL x[], REAL ifs[], int n)
{
	int i, j1, j2;
	REAL maxval;

	maxval= ms_VMax(ifs, n, j1);
	for(i= j1; i < n; i++)
		if(ifs[i] == maxval)
			j2= i;
	if(fabs(x[j1]) > fabs(x[j2])) 
		return x[j1];
	else
		return x[j2];
}

/////////////////////////////////////////////////////////////////////////
//  Defuzzify membership function using the mean of maximum method(MOM)
REAL MomDefuzz(REAL x[], REAL ifs[], int n)
{
	int i, j1, j2;
	REAL maxval;

	maxval= ms_VMax(ifs, n, j1);
	for(i= j1; i < n; i++)
		if(ifs[i] == maxval)
			j2= i;
	return (x[j2]+x[j1])/2.0;
}

/////////////////////////////////////////////////////////////////////////
// Trapezoidal-type membership function 
REAL Trapmf(REAL x, REAL a, REAL b, REAL c, REAL d)
{
	REAL xx,p1,p2,p3,p4;

	xx= REAL(x);p1= REAL(a);p2= REAL(b);p3= REAL(c);p4= REAL(d);
	if(p1>p2|| p1>p3 || p1>p4 || p2>p3 || p2>p4 || p3>p4)
		ErrorMsg("Error in 'Trapmf': illegal parameter condition");
	if(xx<p1 || xx>p4) return 0;
	if(p1==p2 && p2==p3 && p3==p4)
		return 1;
	else if(p1==p2 && p2==p3)
		return (p4-xx)/(p4-p3);
	else if(p2==p3 && p3==p4)
		return (xx-p1)/(p2-p1);	
	else if(p1==p2 && p3==p4)
		return 1;	
	else if(p1==p2 && xx>=p2 && xx<p3)
		return 1;
	else if(p1==p2 && xx>=p3 && xx<=p4)
		return (p4-xx)/(p4-p3);
	else if(p3==p4 && xx>=p1 && xx<p2)
		return (xx-p1)/(p2-p1);
	else if(p3==p4 && xx>=p2 && xx<=p3)
		return 1;
	else if(xx>=p1 && x<p2)
		return (xx-p1)/(p2-p1);	
	else if(xx>=p2 && xx<=p3)
		return 1;
	else
		return (p4-xx)/(p4-p3);
}

/////////////////////////////////////////////////////////////////////////
// Triangular-type membership function    
REAL Trimf(REAL x, REAL a, REAL b, REAL c)
{
	REAL xx,p1,p2,p3;

	xx= REAL(x);p1= REAL(a);p2= REAL(b);p3= REAL(c);
	if(p1>p2|| p1>p3 || p2>p3)
		ErrorMsg("Error in 'Trimf': illegal parameter condition");
	if(xx<p1 || xx>p3) return 0;
	if(p1==p2 && p2==p3)
		return 1;
	else if(p1==p2)
		return (p3-xx)/(p3-p2);
	else if(p2==p3)
		return (xx-p1)/(p2-p1);	
	else if(xx>=p1 && xx<=p2)
		return (xx-p1)/(p2-p1);
	else 
		return (p3-xx)/(p3-p2);
}

/////////////////////////////////////////////////////////////////////////
// Sigmoid curve membership function
REAL Sigmf(REAL x, REAL a, REAL c)
{
	return 1.0/(1.0+exp(-a*(x-c)));
}


/////////////////////////////////////////////////////////////////////////
// Generalized bell curve membership function
REAL Gbellmf(REAL x, REAL a, REAL b, REAL c)
{
	if(a==0)
		ErrorMsg("Error in 'Gbellmf': illegal parameter condition");
	return 1.0/(1.0+pow(fabs((x-c)/a),2.0*b));
}

/////////////////////////////////////////////////////////////////////////
// Gaussian curve membership function
REAL Gaussmf(REAL x, REAL sig, REAL c)
{
	if(sig==0)
		ErrorMsg("Error in 'Gaussmf': illegal parameter condition");
	return exp(-(x-c)*(x-c)/(2*sig*sig));
}

/////////////////////////////////////////////////////////////////////////
// sets fuzzy sets
void FUZZY::SetInFSet(int no, int mftype, REAL p1, REAL p2, REAL p3, REAL p4)
{
	InMFTypes[no]= mftype;
	InMFParams[no][0]= p1;
	InMFParams[no][1]= p2;
	InMFParams[no][2]= p3;
	InMFParams[no][3]= p4;
	return;
}

/////////////////////////////////////////////////////////////////////////
// sets fuzzy sets
void FUZZY::SetOutFSet(int no, int mftype, REAL p1, REAL p2, REAL p3, REAL p4)
{
	OutMFTypes[no]= mftype;
	OutMFParams[no][0]= p1;
	OutMFParams[no][1]= p2;
	OutMFParams[no][2]= p3;
	OutMFParams[no][3]= p4;
	return;
}