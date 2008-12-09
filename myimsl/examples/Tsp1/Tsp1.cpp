/////////////////////////////////////////////////////////////////////////
// Program  : tsp.cpp
//            TSP using simulated annealing
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 15/11/2003
//
#include <stdafx.h>
#include <math.h>
#include "plplot.h"
#include "imsl.h"
#include "anneal.h"

void InitANL(ANNEAL &anl);
REAL ObjFun(REAL x[], REAL y[], int path[], int lchrom);

void main(void)
{
	int i,j,s=0,s1=0;
	REAL *x,*y;
	ANNEAL anl(50); // maximum number of cities

	InitANL(anl);   // initialize annealing process

	x= RVector(anl.lchrom);
	y= RVector(anl.lchrom);
	for(i=0;i<anl.lchrom;i++) 
	{
		anl.path[i]= i+1;        // initial order must start with 1
		x[i]= UnifRnd(0.0,15.0); // x position
		y[i]= UnifRnd(0.0,15.0); // y position
	}

	plsdev("win3");	
	plinit();
	plssub(2,2);

// #1 subplot
	plcol0(7);
	plenv(0.0, anl.maxgen, 80.0, 90.0, 0, 0);
	plcol0(1);
	pllab("Iteration","Objective","40 cities TSP"); 

	anl.obj= ObjFun(x,y,anl.path,anl.lchrom);
	for(i=1;i<=anl.maxgen;i++) 
	{
		anl.Anneal(x,y,anl.lchrom);
		plline1(0, i, anl.obj, &s, 2);
	}

// #2 subplot
	pladv(1);
	plcol0(7);
	plenv(0.0, 20.0, 0.0, 20.0, 0, 0);
	plcol0(1);
	pllab("x","y","Optimal route"); 

	for(i= 0; i < anl.lchrom; i++)
	{
		plcol0(2);
		plpoin(1, &x[i], &y[i], 22); 
		j= anl.path[i]-1;   
		plline1(1, x[j], y[j], &s1, 1);
	}
	j= anl.path[0]-1;
	plline1(1, x[j], y[j], &s1, 1); 

	printf("obj= %f\n",anl.obj);
	printf("Optimal route= \n");
	for(i= 0; i < anl.lchrom; i++)
		printf("%3d %7.3f %7.3f\n",anl.path[i], x[i], y[i]);
	plend();	
	Free_RVector(x);
	Free_RVector(y);
	return;
}

void InitANL(ANNEAL &anl)
{
	anl.lchrom=  40;     // number of cities
	anl.maxgen= 200;     // maximum iteration
	anl.seed= 10976;     // random seed
	anl.temp=   0.5;     // initial temperature
	anl.tfactr= 0.9;     // factor
	SRand(anl.seed);     // resets Rand()
}

#define Dist(a,b,c,d) sqrt(((b)-(a))*((b)-(a))+((d)-(c))*((d)-(c)))
REAL ObjFun(REAL x[], REAL y[], int path[], int lchrom)
{
	int i,i1,i2;
	REAL obj;
	
	i1= path[lchrom-1];
	i2= path[0];
	obj= Dist(x[i1],x[i2],y[i1],y[i2]);
	for(i=0;i<lchrom-1;i++) 
	{
		i1= path[i];
		i2= path[i+1];
		obj+= Dist(x[i1],x[i2],y[i1],y[i2]);
	}
	return obj;
}