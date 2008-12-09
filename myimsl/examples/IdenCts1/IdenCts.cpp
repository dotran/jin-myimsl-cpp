/////////////////////////////////////////////////////////////////////////
// Program  : idencts.cpp
//            RCGA-based parameter estimation of a 2nd-order system
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
	int gen, s=0, s1=0, s2=0, s3=0, s4=0;
	REAL etha=1.8, b=5;
	RCGAS rcga(20,3); // popsize=20 and lchrom=3

	plsdev("win3");	
//	plscolbg(255, 255, 255);
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
	plwind(0.0, rcga.maxgen, 0.0, 200.0); // window for objective
	plbox("", 0.0, 0, "cmstv", 0.0, 3); // box and axis for objective
	plcol0(1);
	plmtex("r", 5.0, 0.5, 0.5, "Objective"); // labelling for objective

	for(gen= 1; gen <= rcga.maxgen; gen++)
	{
		plwind(0.0, rcga.maxgen, 0.0, 200.0);
		plline1(0, rcga.gen, rcga.bestobj, &s, 2);
		plwind(0.0, rcga.maxgen, 0.0, 10.0);
		plline1(1, rcga.gen, rcga.bestchrom[0], &s1, 3);
		plline1(2, rcga.gen, rcga.bestchrom[1], &s2, 10);
		plline1(3, rcga.gen, rcga.bestchrom[2], &s3, 14);
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
	rcga.gen=       0;         // set the initial generation to 0
	rcga.maxgen= 1000;         // maximum generation number
	rcga.seed=   1644;         // ramdom seed
	rcga.maxmin=   -1;	       // 1 indicates maximization problem; -1, otherwise
	rcga.pcross=  1.0;         // crossover probability
	rcga.pmutat=  0.2;         // mutation probability
	rcga.wsize=     1;         // scaling window size
	rcga.xlb[0]=  0.0;         // lower bound of b2
	rcga.xub[0]= 10.0;	  	   // upper bound of b2
	rcga.xlb[1]=  0.0;         // lower bound of a1
	rcga.xub[1]= 10.0;	  	   // upper bound of a1
	rcga.xlb[2]=  0.0;         // lower bound of a2
	rcga.xub[2]= 10.0;	       // upper bound of a2
	return;
}

//////////////////////////////////////////////////////////////////
// Evaluates the current population on the system
// The plant TF G(s)= b0/(s^2+a1s+a2) where b0= 1, a1= 0.8, a2= 1
void EvalObj(RCGAS &rcga)
{
	int i, j, n= 2, ndata= 1000;
	REAL pb[]= {0.0, 0.0, 1.0}, pa[]= {1.0, 0.8, 1.0};
	REAL t, h= 0.02, u, ma[5], mb[5], yp, ym;
	REAL see, se;
	DIFFEQS plant, model; 

	for(i= 0; i < rcga.popsize; i++) 
	{
		rcga.obj[i]= 0;
		t= 0.0; see=0.0;
		InitLSim(plant); // sets the plant variables with 0
		InitLSim(model); // sets the adjustable model variables with 0
		for(j= 0; j < ndata; j++)
		{
			u= 1;
			yp= LSim(plant, u, pb, pa, n, t, h); // plant
			mb[0]= 0.0;	mb[1]= 0.0; mb[2]= rcga.chrom[i][0];
			ma[0]= 1.0;	ma[1]= rcga.chrom[i][1]; ma[2]= rcga.chrom[i][2];
			ym= LSim(model, u, mb, ma, n, t, h); // adjustable model
			se= (yp-ym)*(yp-ym); // squared error
			rcga.obj[i]+= 0.5*(se+see);
			see= se;
		}
	}
	return;
}
