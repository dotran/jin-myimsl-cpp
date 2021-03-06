/////////////////////////////////////////////////////////////////////////
// Program  : tunepid.cpp
//            RCGA-based gain tuning of the PID controller for a 2nd-order 
//            system with time delay
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 15/11/2003
//
#include "stdafx.h"
#include <math.h>
#include "plplot.h"
#include "diffeqs.h"
#include "rcgas.h"

void InitPara(RCGAS &rcga);
void EvalObj(RCGAS &rcga);

void main(void)
{
	int gen, s=0, s1=0, s2=0, s3=0;
	REAL etha=1.8, b=5;
	RCGAS rcga(20,3);

	plsdev("win3");	
	plinit();
	pladv(0);

	InitPara(rcga);
	InitPop(rcga);
	EvalObj(rcga);
	ScalFit(rcga);
	
	plcol0(7);
	plvpor(0.15, 0.85, 0.15, 0.85);
	plwind(0.0, rcga.maxgen, 0.0, 5.0);
	plcol0(7);
	plbox("bcnst", 0.0, 0, "bnstv", 0.0, 0);
	plcol0(1);
	plmtex("t", 2.0, 0.5, 0.5, "RCGA-based PID tuning");
	plmtex("b", 3.2, 0.5, 0.5, "Generation");
	plmtex("l", 5.0, 0.5, 0.5, "Tuned gains");
	plcol0(7);
	plwind(0.0, rcga.maxgen, 0.0, 10.0);
	plbox("", 0.0, 0, "cmstv", 0.0, 0);
	plcol0(1);
	plmtex("r", 5.0, 0.5, 0.5, "Objective");

	for(gen= 1; gen <= rcga.maxgen; gen++)
	{
		plwind(0.0, rcga.maxgen, 0.0, 10.0);
		plline1(0, rcga.gen, rcga.bestobj, &s, 2);
		plwind(0.0, rcga.maxgen, 0.0, 5.0);
		plline1(1, rcga.gen, rcga.bestchrom[0], &s1, 9);
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
	printf("Kp, Ki, Kd= ");
	for(int i=0; i<rcga.lchrom; i++)
		printf("%f ",rcga.bestchrom[i]);
	printf("\n");
	plend();
	return;
}

//////////////////////////////////////////////////////////////////
// Initialises the RCGA parameters
void InitPara(RCGAS &rcga)
{
	rcga.gen=       0;         // initial generation
	rcga.maxgen=  500;         // maximum generation number
	rcga.seed=   5529;         // ramdom seed
	rcga.maxmin=   -1;		     // 1 indicates maximization problem; -1, otherwise
	for(int j=0; j < rcga.lchrom; j++) 
	{
		rcga.xlb[j]= 0.0;        // lower bound of the PID gains
		rcga.xub[j]= 5.0;	  		 // upper bound of the PID gains
	}
	rcga.pcross= 1.0;          // crossover probability
	rcga.pmutat= 0.2;          // mutation probability
	rcga.wsize= 1;             // scaling window size
	return;
}

//////////////////////////////////////////////////////////////////
// Evaluates all chromosomes in the PID control system
void EvalObj(RCGAS &rcga)
{
	int i, j, n= 2, ndata= 750;
	REAL pb[]= {0, 0, 1}, pa[]= {1, 0.7, 1}, L= 0.5;
	REAL t, h= 0.02, yr, u, y;
	REAL e, ee, z, ce, se, see, Kp, Ki, Kd;
	DIFFEQS ode;

	for(i= 0; i < rcga.popsize; i++) 
	{
		t= 0.0; y= 0.0; yr= 1.0; z= 0.0; see= 0.0; ee= yr-y;
		InitLSim(ode);                      // resets time delay buffer
		rcga.obj[i]= 0;
		Kp= rcga.chrom[i][0];
		Ki= rcga.chrom[i][1];
		Kd= rcga.chrom[i][2];
		for(j= 0; j < ndata; j++)
		{
			e= yr-y;
			z+= 0.5*h*(e+ee);
			ce= (e-ee)/h;
			ee= e;
			u= Kp*e+Ki*z+Kd*ce;                 // PID control
			y= LSim(ode, u, pb, pa, n, t, h, L);
			se= fabs(e);
			if(t>L) 
				rcga.obj[i]+= 0.5*h*(se+see);     // objective function value
			see= se;
			if(rcga.obj[i] > 1.0e+10) break;    // in case of unstable parameter combinations
			t+= h;
		}
	}
	return;
}