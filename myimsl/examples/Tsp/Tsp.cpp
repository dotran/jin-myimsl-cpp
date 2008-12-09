/////////////////////////////////////////////////////////////////////////
// Program  : tsp.cpp
//            TSP using a SCGA 
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 15/11/2003
//
#include <stdafx.h>
#include <math.h>
#include "plplot.h"
#include "scgas.h"
#include "imsl.h"

void InitPara(SCGAS &scga);
void EvalObj(SCGAS &scga, REAL x[], REAL y[]);

void main(void)
{
	int i, gen, s=0, s1=0;
	int popsize= 40;         // population size
	int lchrom= 40;          // length of chromosome
	REAL *x, *y;
	char text[50];
	SCGAS scga(popsize,lchrom); 

	InitPara(scga);
	x= RVector(lchrom);
	y= RVector(lchrom);
	for(i=0;i<lchrom;i++) 
	{
		x[i]= UnifRnd(0.0,15.0);
		y[i]= UnifRnd(0.0,15.0);
	}
	plsdev("win3");	
	plinit();
	plssub(2,2);

// #1 subplot
	plcol0(7);
	plenv(0.0, scga.maxgen, 50.0, 800.0, 0, 0);
	plcol0(1);
	sprintf(text, " %5d cities TSP", lchrom);
	pllab("Generation","Objective",text); 

	InitPop(scga);
	EvalObj(scga, x, y);
	ScalFit(scga);

	for(gen= 1; gen <= scga.maxgen; gen++)
	{
		plline1(0, scga.gen, scga.bestobj, &s, 2);
		scga.gen= gen;
		RemSel(scga);
		PMXover(scga);
		SwapMut(scga); // swap mutation
		Invers(scga);  // inversion
		EvalObj(scga, x, y);
		Elitism(scga);
		ScalFit(scga);
	}

// #2 subplot
	pladv(1);
	plcol0(7);
	plenv(0.0, 20.0, 0.0, 20.0, 0, 0);
	plcol0(1);
	pllab("x","y","Optimal path"); 
	plcol0(2);
	for(i= 0; i < lchrom; i++) 
		plpoin(1, &x[i], &y[i], 22); // draws symbols
	for(i= 0; i < lchrom; i++) 
		plline1(1, x[scga.bestchrom[i]], y[scga.bestchrom[i]], &s1, 1); // draws lines
	plline1(1, x[scga.bestchrom[0]], y[scga.bestchrom[0]], &s1, 1); 

	// draws #3 subgraph
	pladv(3);
	plvpor(0.4, 1.0, 0.4, 0.9);
	plwind(0.0, 1.0, 0.0, 1.0);
	plcol0(3);
	sprintf(text, "Min Obj= %7.2f", scga.bestobj);
	plmtex("t", -9.0, 0.01, 0.3, text);

	// output the results
	printf("obj= %f\n",scga.bestobj);
	printf("optimal= ");
	plend();
	Free_RVector(x);
	Free_RVector(y);
	return;
}

//////////////////////////////////////////////////////////////////
// Initialises the scga parameters
void InitPara(SCGAS &scga)
{
	scga.gen=       0;          // initial generation
	scga.seed=   171;          // ramdom seed
	scga.maxgen= 5000;          // maximum generation number
	scga.maxmin=   -1;		      // 1 indicates maximization problem; -1, otherwise
	scga.pcross=  1.0;          // crossover probability
	scga.pmutat= 0.05;          // mutation probability
	scga.wsize=     1;          // scaling window size
	return;
}

//////////////////////////////////////////////////////////////////
// Evaluates the distance from chromosomes
#define Dist(a,b,c,d) sqrt(((b)-(a))*((b)-(a))+((d)-(c))*((d)-(c)))
void EvalObj(SCGAS &scga, REAL x[], REAL y[])
{
	int i, j, i1, i2;

	for(i= 0; i < scga.popsize; i++) 
	{
		i1= scga.chrom[i][scga.lchrom-1];
		i2= scga.chrom[i][0];
		scga.obj[i]= Dist(x[i1],x[i2],y[i1],y[i2]);
		for(j= 0; j < scga.lchrom-1; j++) 
		{
			i1= scga.chrom[i][j];
			i2= scga.chrom[i][j+1];
			scga.obj[i]+= Dist(x[i1],x[i2],y[i1],y[i2]);
		}
	}
	return;
}
