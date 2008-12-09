/////////////////////////////////////////////////////////////////////////
// Program  : idendts.cpp
//            RCGA-based parameter estimation of a 1st-order discrete-time
//            system without time delay
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 11/08/2003
//
#include <stdio.h>
#include "plplot.h"
#include "diffeqs.h"
#include "rcgas.h"

void InitPara(RCGAS &rcga);
void EvalObj(RCGAS &rcga);

void main()
{
	int gen, s=0, s1=0, s2=0, s3=0;
	REAL etha=1.8, b=5;
	RCGAS rcga(20,2); // (popsize, lchrom)

	plsdev("win3");	
//	plscolbg(255, 255, 255);
  plinit();
	pladv(0);

	InitPara(rcga);
	InitPop(rcga);
	EvalObj(rcga);
	ScalFit(rcga);

  plvpor(0.15, 0.85, 0.15, 0.85); // viewpoint for both parameters and objective
  plwind(0.0, rcga.maxgen, -2.0, 2.0); // window for parameters
  plcol0(7); 
	plbox("bcnst", 0.0, 0, "bnstv", 0.0, 0); // axis and box for parameters
  plcol0(1); 
  plmtex("t", 2.0, 0.5, 0.5, "RCGA-based parameter estimation"); // labelling for both
	plmtex("b", 3.2, 0.5, 0.5, "Generatin"); // labelling for both
  plmtex("l", 5.0, 0.5, 0.5, "Parameters"); // labelling for parameters
  plcol0(7);
	plwind(0.0, rcga.maxgen, 0.0, 10.0); // window for objective
	plbox("", 0.0, 0, "cmstv", 0.0, 3); // box and axis for objective
  plcol0(1);
  plmtex("r", 5.0, 0.5, 0.5, "Objective"); // labelling for objective

	for(gen= 1; gen <= rcga.maxgen; gen++)
	{
		plwind(0.0, rcga.maxgen, 0.0, 10.0);
		plline1(0, rcga.gen, rcga.bestobj, &s, 2);
		plwind(0.0, rcga.maxgen, -2.0, 2.0);
		plline1(1, rcga.gen, rcga.bestchrom[0], &s1, 3);
		plline1(2, rcga.gen, rcga.bestchrom[1], &s2, 10);
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
	rcga.gen=       0;         // initial generation
	rcga.maxgen=  500;         // maximum generation number
	rcga.seed=   13644;        // ramdom seed
	rcga.maxmin=   -1;		     // 1 indicates maximization problem; -1, otherwise
	rcga.pcross=  1.0;         // crossover probability
	rcga.pmutat=  0.2;         // mutation probability
	rcga.wsize=     1;         // scaling window size
	rcga.xlb[0]= -1.0;         // lower bound of b1
	rcga.xub[0]=  1.0;	  	   // upper bound of b1
	rcga.xlb[1]= -1.0;         // lower bound of a1
	rcga.xub[1]=  1.0;	  	   // upper bound of a1
	return;
}

//////////////////////////////////////////////////////////////////
// Evaluates the current population on the system
void EvalObj(RCGAS &rcga)
{
	int i, j, n= 1, ndata= 700;
	REAL t, h= 0.02, u, ma[5], mb[5], yp, ym, see, se;
	REAL pb[]= {0.0, 0.0196}, pa[]= {1.0, -0.9608};
	DIFFEQS plant, model;

	for(i= 0; i < rcga.popsize; i++) 
	{
		rcga.obj[i]= 0.0;
		t= 0.0; see=0.0;
		InitDSim(plant);             // initialises the plant
		InitDSim(model);             // initialises the adjustable model
		for(j= 0; j < ndata; j++)
		{
			u= 1.0;
			yp= DSim(plant, u, pb, pa, n);         // plant
			mb[0]= 0.0; mb[1]= rcga.chrom[i][0];   // set parameters
			ma[0]= 1.0;	ma[1]= rcga.chrom[i][1];   // set parameters
			ym= DSim(model, u, mb, ma, n);         // adjustable model
			se= (yp-ym)*(yp-ym);                   // squared error
			rcga.obj[i]+= 0.5*(se+see);
			see= se;
		}
	}
	return;
}
