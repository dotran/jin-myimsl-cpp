/////////////////////////////////////////////////////////////////////////
// Program  : idencts.cpp
//            RCGA-based parameter estimation of a 1st-order system with time delay
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 11/08/2003
//
#include "stdafx.h"
#include "plplot.h"
#include "diffeqs.h"
#include "rcgas.h"

void InitPara(RCGAS &rcga);
void EvalObj(RCGAS &rcga);

void main()
{
	int gen, s=0, s1=0, s2=0, s3=0;
	int popsize=10, lchrom=3;
	REAL etha=1.8, b=5;
	RCGAS rcga(popsize,lchrom);

	plsdev("win3");	
	plinit();
	pladv(0);

	InitPara(rcga);
	InitPop(rcga);
	EvalObj(rcga);
	ScalFit(rcga);

	plvpor(0.15, 0.85, 0.15, 0.85); // viewpoint for both parameters and objective
	plwind(0.0, rcga.maxgen, 0.0, 10.0); // window for parameters
	plcol0(7); 
	plbox("bcnst", 0.0, 0, "bnstv", 0.0, 0); // axis and box for parameters
	plcol0(1); 
	plmtex("t", 2.0, 0.5, 0.5, "RCGA-based parameter estimation"); // labelling for both
	plmtex("b", 3.2, 0.5, 0.5, "Generatin"); // labelling for both
	plmtex("l", 5.0, 0.5, 0.5, "Parameters"); // labelling for parameters
	plcol0(7);
	plwind(0.0, rcga.maxgen, 0.0, 100.0); // window for objective
	plbox("", 0.0, 0, "cmstv", 0.0, 3); // box and axis for objective
	plcol0(1);
	plmtex("r", 5.0, 0.5, 0.5, "Objective"); // labelling for objective

	for(gen= 1; gen <= rcga.maxgen; gen++)
	{
		plwind(0.0, rcga.maxgen, 0.0, 100.0);
		plline1(0, rcga.gen, rcga.bestobj, &s, 2);
		plwind(0.0, rcga.maxgen, 0.0, 10.0);
		plline1(1, rcga.gen, rcga.bestchrom[0], &s1, 3);
		plline1(2, rcga.gen, rcga.bestchrom[1], &s2, 10);
		plline1(3, rcga.gen, rcga.bestchrom[2], &s3, 11);
		rcga.gen= gen;
		GradSel(rcga, etha);
		MsXover(rcga);
		DynMut(rcga, b);
		EvalObj(rcga);
		Elitism(rcga);
		ScalFit(rcga);

	}

	printf("obj= %f\n",rcga.bestobj);
	printf("  x= ");
	for(int i=0; i<rcga.lchrom; i++)
		printf("%f ",rcga.bestchrom[i]);	
	printf("\n");

	plend();
}

//		RwSel(rcga);
//		RankSel(rcga, rfact);
//		UniSel(rcga);
//		TouSel(rcga, tsize);
// 		RemSel(rcga);  
// 		ArXover(rcga); 
//		OpXover(rcga);
//		TpXover(rcga);
//		FlXover(rcga);
//		UniMut(rcga);
//		CrpMut(rcga, cfact);

//////////////////////////////////////////////////////////////////
// Initialises the RCGA parameters
void InitPara(RCGAS &rcga)
{
	rcga.gen= 0;
	rcga.maxgen= 1000;         // maximum generation number
	rcga.maxmin=  -1;		       // 1 indicates maximization problem; -1, otherwise
	rcga.seed=   123;
	rcga.wsize=    1;
	rcga.pcross= 1.0;          // crossover probability
	rcga.pmutat= 0.1;          // mutation probability
	rcga.xlb[0]= 0.0;          // lower bound of b1
	rcga.xub[0]= 15.0;	  	   // upper bound of b1
	rcga.xlb[1]= 0.0;          // lower bound of a1
	rcga.xub[1]= 15.0;	  	   // upper bound of a1
	rcga.xlb[2]= 0.0;          // lower bound of L
	rcga.xub[2]= 5.0;	         // upper bound of L
	return;
}

//////////////////////////////////////////////////////////////////
// Evaluates the current population on the system
void EvalObj(RCGAS &rcga)
{
	int i, j, n= 1, ndata= 500;
	REAL pb[]= {0.0, 0.5}, pa[]= {1.0, 0.5}, Lp= 1.5;
	REAL t, h= 0.02, u, ma[5], mb[5], yp, ym, Lm;
	REAL see, se;
	DIFFEQS plant, model(1000); // array instance is declared for the model

	for(i= 0; i < rcga.popsize; i++) 
	{
		rcga.obj[i]= 0;
		t= 0.0; see=0.0;
		InitLSim(plant); // resets the plant
		InitLSim(model); // resets the adjustable model
		for(j= 0; j < ndata; j++)
		{
			u= 1;
			yp= LSim(plant, u, pb, pa, n, t, h, Lp); // plant
			mb[0]= 0.0; mb[1]= rcga.chrom[i][0];
			ma[0]= 1.0; ma[1]= rcga.chrom[i][1];
			Lm= rcga.chrom[i][2];
			ym= LSim(model, u, mb, ma, n, t, h, Lm); // adjustable model
			se= (yp-ym)*(yp-ym); // squared error
			rcga.obj[i]+= 0.5*(se+see);
			see= se;
		}
	}
	return;
}
