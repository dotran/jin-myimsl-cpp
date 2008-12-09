/////////////////////////////////////////////////////////////////////////
// Program  : main_sug.cpp
//            Inference of a Sugeno-type fuzzy system
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 2007/08/17
//
#include "stdafx.h"
#include "fuzzy.h"
#include "imsl.h"

void InitPara(FUZZY &fl);
void main(void)
{
	REAL cInp[2], y, *vOut1, *vOut2;
	FUZZY fl(10,10,10); //fl(max_no_input, max_no_fset, max_no_rule)

	printf("Input 1(-1~1)= ");
	scanf_s("%lf",&cInp[0]);
	printf("Input 2(-1~1)= ", &cInp[0]);
	scanf_s("%lf",&cInp[1]);

	InitPara(fl);
	vOut1= RVector(fl.NumRules);
	vOut2= RVector(fl.NumRules);
	Infer(fl, cInp, vOut1, vOut2);
	y= Defuzz(fl, vOut1, vOut2); 
	printf("Output= %lf\n", y);

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
	fl.NumOutputMFs=     6; // number of fuzzy sets over y
	fl.NumRules=         6; // number of rules
	fl.AndMethod=     PRODUCT; // PRODUCT or MIN
	fl.OrMethod=      MAX;     // Fixed
	fl.ImpMethod=     NONE;    // Not used
	fl.AggMethod=     NONE;    // Not used
	fl.DefuzzMethod=  NONE;    // Not used
	fl.InRange[0][0]=  -1; 	fl.InRange[0][1]= 1; // Lower and upper ranges of x1
	fl.InRange[1][0]=  -1; 	fl.InRange[1][1]= 1; // Lower and upper ranges of x2
	fl.OutRange[0]=   -10; 	fl.OutRange[1]=  10; // Lower and upper ranges of y
	fl.InNumLevel[0]= 101; // number of level
	fl.InNumLevel[1]= 101; // number of level
//	fl.OutNumLevel=	 NONE; // number of level

	enum {N1=0, Z1, P1};  // x1
	enum {N2=0, Z2, P2}; // x2
	enum {f1=0, f2, f3, f4, f5, f6};  // y
	// antecedent parts of the fuzzy rules
	fl.RuleAntecedent[0][0]= N1; fl.RuleAntecedent[0][1]= P2; 
	fl.RuleAntecedent[1][0]= Z1; fl.RuleAntecedent[1][1]= Z2; 
	fl.RuleAntecedent[2][0]= P1; fl.RuleAntecedent[2][1]= Z2; 
	fl.RuleAntecedent[3][0]= P1; fl.RuleAntecedent[3][1]= N2; 
	fl.RuleAntecedent[4][0]= N1; fl.RuleAntecedent[4][1]= N2; 
	fl.RuleAntecedent[5][0]= P1; fl.RuleAntecedent[5][1]= P2; 
	// consequent parts of the fuzzy rules
	fl.RuleConsequent[0]= f1;
	fl.RuleConsequent[1]= f2;
	fl.RuleConsequent[2]= f3;
	fl.RuleConsequent[3]= f4;
	fl.RuleConsequent[4]= f5;
	fl.RuleConsequent[5]= f6;

	enum {AND=0, OR};
	// fuzzy rule connectives
	fl.RuleConnection[0][0]= AND; // AND= 0, OR= 1
	fl.RuleConnection[1][0]= AND;
	fl.RuleConnection[2][0]= AND;
	fl.RuleConnection[3][0]= AND;
	fl.RuleConnection[4][0]= OR;
	fl.RuleConnection[5][0]= AND;
	
	// fuzzy sets defined over input #1(TRAPMF TRIMF, GBELLMF, SIGMF or GAUSSMF)
	fl.SetInFSet(0, TRAPMF,-1,-1,-0.8,0);
	fl.SetInFSet(1, TRIMF,-0.6,0,0.6,0);
	fl.SetInFSet(2, TRAPMF,0,0.8,1,1);

	// fuzzy sets defined over input #2
	fl.SetInFSet(3, TRAPMF,-1,-1,-0.8,0);
	fl.SetInFSet(4, TRIMF,-0.6,0,0.6,0);
	fl.SetInFSet(5, TRAPMF,0,0.8,1,1);

	// fuzzy sets defined over output y
	fl.SetOutFSet(0, NONE, 2, 1, 0, 0);
	fl.SetOutFSet(1, NONE, 0, 0, 0, 0);
	fl.SetOutFSet(2, NONE, 1, 2, 1, 0);
	fl.SetOutFSet(3, NONE, 2, -1, -1, 0);
	fl.SetOutFSet(4, NONE, 1, 0, 0, 0);
	fl.SetOutFSet(5, NONE, 1, 1, 1, 0);

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

