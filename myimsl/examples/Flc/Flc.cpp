/////////////////////////////////////////////////////////////////////////
// Program  : flc.cpp
//            Inference of a Mamdani-type fuzzy system
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 2007/08/17
//
#include "stdafx.h"
#include "fuzzy.h"
#include "realtype.h"

void InitPara(FUZZY &fl);
void main(void)
{
	REAL cInp[2], y, *vOut1, *vOut2;
	FUZZY fl(5,5,5); //fl(max_input_no,max_fset_no,max_rule_no)

	printf("Food quality(0-1)= ");
	scanf_s("%lf",&cInp[0]);
	printf("Service quality(0-1)= ", &cInp[0]);
	scanf_s("%lf",&cInp[1]);

	InitPara(fl);
	vOut1= RVector(fl.OutNumLevel);
	vOut2= RVector(fl.OutNumLevel);

	CheckInput(fl, cInp);
	Infer(fl, cInp, vOut1, vOut2);
	y= Defuzz(fl, vOut1, vOut2);
	printf("Tips= %7.2lf Won\n", y);
	Free_RVector(vOut1);
	Free_RVector(vOut2);
	return;
}

/////////////////////////////////////////////////////////////////////////
// Initialises the parameters of a fuzzy system
void InitPara(FUZZY &fl)
{
	fl.InfType=    MAMDANI; // inference type
	fl.NumInputs= 	     2; // number of input
	fl.NumInputMFs[0]=   3; // number of fuzzy sets over x0
	fl.NumInputMFs[1]=   3; // number of fuzzy sets over x1
	fl.NumOutputMFs=     3; // number of fuzzy sets over y
	fl.NumRules=         4; // number of rules
	fl.AndMethod=      MIN;
	fl.OrMethod=       MAX;
	fl.ImpMethod=      MIN;
	fl.AggMethod=      MAX;
	fl.DefuzzMethod=   COG; // COG, MOM, SOM, LOM
	fl.InRange[0][0]=    0; 	fl.InRange[0][1]= 1;  // Lower and upper ranges of x1
	fl.InRange[1][0]=    0; 	fl.InRange[1][1]= 1;  // Lower and upper ranges of x2
	fl.OutRange[0]=      0; 	fl.OutRange[1]= 6000; // Lower and upper ranges of y
	fl.InNumLevel[0]=  101; // number of level
	fl.InNumLevel[1]=  101; // number of level
	fl.OutNumLevel=	   101; // number of level

	enum {NB=0, ZO, PB};
	// antecedent parts of the fuzzy rules
	fl.RuleAntecedent[0][0]= NB; fl.RuleAntecedent[0][1]= NB; 
	fl.RuleAntecedent[1][0]= -1; fl.RuleAntecedent[1][1]= ZO; 
	fl.RuleAntecedent[2][0]= PB; fl.RuleAntecedent[2][1]= PB; 
	fl.RuleAntecedent[3][0]= NB; fl.RuleAntecedent[3][1]= PB; 
	// consequent parts of the fuzzy rules
	fl.RuleConsequent[0]=NB;
	fl.RuleConsequent[1]=ZO;
	fl.RuleConsequent[2]=PB;
	fl.RuleConsequent[3]=ZO;

	enum {AND=0, OR};
	// fuzzy rule connectives
	fl.RuleConnection[0][0]= OR; // AND= 0, OR= 1
	fl.RuleConnection[1][0]= OR;
	fl.RuleConnection[2][0]= OR;
	fl.RuleConnection[3][0]= AND;
	
	// fuzzy sets defined over input #1
	fl.SetInFSet(0, SIGMF,-20.0,0.2,0,0);
	fl.SetInFSet(1, GAUSSMF,0.1,0.5,0,0);
	fl.SetInFSet(2, SIGMF,20.0,0.8,0,0);

	// fuzzy sets defined over input #2
	fl.SetInFSet(3, SIGMF, -20.0,0.2,0,0);
	fl.SetInFSet(4, GAUSSMF, 0.1,0.5,0,0);
	fl.SetInFSet(5, SIGMF, 20.0,0.8,0,0);

	// fuzzy sets defined over y
	fl.SetOutFSet(0, SIGMF, -0.008, 500, 0, 0);
	fl.SetOutFSet(1, GAUSSMF, 600, 3000, 0, 0);
	fl.SetOutFSet(2, SIGMF, 0.008, 5500, 0, 0);

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