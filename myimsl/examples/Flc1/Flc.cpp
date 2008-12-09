/////////////////////////////////////////////////////////////////////////
// Program  : main_sug.cpp
//            Inference of a Sugeno-type fuzzy system
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 2007/08/17
//
#include "stdafx.h"
#include "fuzzy.h"

void InitPara(FUZZY &fl);
void main(void)
{
	REAL cInp[2], y, *vOut1, *vOut2;
	FUZZY fl(5,5,5); //fl(max_no_input, max_no_fset, max_no_rule)

	printf("Food quality(0~1)= ");
	scanf_s("%lf",&cInp[0]);
	printf("Service quality(0~1)= ", &cInp[0]);
	scanf_s("%lf",&cInp[1]);

	InitPara(fl);
	vOut1= RVector(fl.NumRules);
	vOut2= RVector(fl.NumRules);
	Infer(fl, cInp, vOut1, vOut2);
	y= Defuzz(fl, vOut1, vOut2); 
	printf("Tips= %7.2lf Won\n", y);

	Free_RVector(vOut1);
	Free_RVector(vOut2);
	return;
}

/////////////////////////////////////////////////////////////////////////
// Initialises the parameters of a Sugeno-type fuzzy system
void InitPara(FUZZY &fl)
{
	fl.InfType=     SUGENO; // inference type(SUGENO or MAMDANI)
	fl.NumInputs= 	     2; // number of inputs
	fl.NumInputMFs[0]=   3; // number of fuzzy sets over x0
	fl.NumInputMFs[1]=   3; // number of fuzzy sets over x1
	fl.NumOutputMFs=     3; // number of fuzzy sets over y
	fl.NumRules=         4; // number of rules
	fl.AndMethod=     PRODUCT; // PRODUCT or MIN
	fl.OrMethod=      MAX;     // Fixed
	fl.ImpMethod=     NONE;    // Not used
	fl.AggMethod=     NONE;    // Not used
	fl.DefuzzMethod=  NONE;    // Not used
	fl.InRange[0][0]=   0; 	fl.InRange[0][1]= 1; // Lower and upper ranges of x1
	fl.InRange[1][0]=   0; 	fl.InRange[1][1]= 1; // Lower and upper ranges of x2
	fl.OutRange[0]=     0; 	fl.OutRange[1]= 6000; // Lower and upper ranges of y
	fl.InNumLevel[0]= 101; // number of level
	fl.InNumLevel[1]= 101; // number of level
	fl.OutNumLevel=	 NONE; // number of level

	enum {Bad=0, Aver1, Good1};  // Food
	enum {Low1=0, Good2, Excel}; // Service
	enum {Low2=0, Aver2, Genr};  // Tip
	// antecedent parts of the fuzzy rules
	fl.RuleAntecedent[0][0]= Bad; fl.RuleAntecedent[0][1]= Low1; 
	fl.RuleAntecedent[1][0]= NONE; fl.RuleAntecedent[1][1]= Good2; 
	fl.RuleAntecedent[2][0]= Good1; fl.RuleAntecedent[2][1]= Excel; 
	fl.RuleAntecedent[3][0]= Bad; fl.RuleAntecedent[3][1]= Excel; 
	// consequent parts of the fuzzy rules
	fl.RuleConsequent[0]=Low2;
	fl.RuleConsequent[1]=Aver2;
	fl.RuleConsequent[2]=Genr;
	fl.RuleConsequent[3]=Aver2;

	enum {AND=0, OR};
	// fuzzy rule connectives
	fl.RuleConnection[0][0]= OR; // AND= 0, OR= 1
	fl.RuleConnection[1][0]= OR;
	fl.RuleConnection[2][0]= OR;
	fl.RuleConnection[3][0]= AND;
	
	// fuzzy sets defined over input #1(TRAPMF TRIMF, GBELLMF, SIGMF or GAUSSMF)
	fl.SetInFSet(0, SIGMF,-20.0,0.2,0,0);
	fl.SetInFSet(1, GAUSSMF,0.1,0.5,0,0);
	fl.SetInFSet(2, SIGMF,20.0,0.8,0,0);

	// fuzzy sets defined over input #2
	fl.SetInFSet(3, SIGMF, -20.0,0.2,0,0);
	fl.SetInFSet(4, GAUSSMF, 0.1,0.5,0,0);
	fl.SetInFSet(5, SIGMF, 20.0,0.8,0,0);

	// fuzzy sets defined over output y
	fl.SetOutFSet(0, NONE, 0, 0, 0, 0);
	fl.SetOutFSet(1, NONE, 3000, 0, 0, 0);
	fl.SetOutFSet(2, NONE, 6000, 0, 0, 0);

	// check the bounds of the three variables
	if(fl.NumInputs > fl.maxninput)
		ErrorMsg ("Error in 'InitPara': increase array size for inputs");
	if(fl.NumOutputMFs > fl.maxnfset)
		ErrorMsg ("Error in 'InitPara': increase array size for fuzzy sets");
	for(int j=0; j<fl.NumInputs; j++)
		if(fl.NumInputMFs[j] > fl.maxnfset)
			ErrorMsg ("Error in 'InitPara': increase array size for fuzzy sets");
	if(fl.NumRules > fl.maxnrule)
		ErrorMsg ("Error in 'InitPara': increase array size for rules");
	return;
}

