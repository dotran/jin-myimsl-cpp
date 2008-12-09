/////////////////////////////////////////////////////////////////////////
// Program  : main_sug.cpp
//            Inference of a Sugeno-type fuzzy model
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 2007/08/17
//
#include "stdafx.h"
#include <math.h>
#include "plplot.h"
#include "fuzzy.h"
#include "diffeqs.h"

void model1(double u,double x[],double t,double ak[]);
void model2(double u,double x[],double t,double ak[]);
void main(void)
{
	int i, loop= 1500, s=0, s1=0, s2=0;
	double u= 0,h= 0.02, t= 0, xf=0, xf1[3], xf2[3], x1[3], x2[3];
	double alpha1, alpha2;

	plsdev("win3");	
	plinit();
	plenv(0, 30.0, -1, 3, 0, 0); // sets up standard window and draw box
	pllab("t", "Responses","Fuzzy modeling");

	x1[0]= xf;
	x2[0]= xf;

	for(i= 0; i < loop; i++)
	{
		u= sin(t)+ 0.5*sin(5*t)+ 0.2*sin(11*t);
		if(i > loop/2)
			u+= 1.5;
	
		xf1[0]= xf;
		xf2[0]= xf;
		alpha1= Sigmf(xf, -5, 1);
		alpha2= Sigmf(xf, 5, 1);
		Rk4(u,xf1,1,t,h,model1);
		Rk4(u,xf2,1,t,h,model2);
		xf= (xf1[0]*alpha1+xf2[0]*alpha2)/(alpha1+alpha2);

		Rk4(u,x1,1,t,h,model1);
		Rk4(u,x2,1,t,h,model2);

		t+= h;
		plline1(0, t, xf, &s, 2);         // fuzzy model(yellow)
		plline1(1, t, x1[0], &s1, 4);    // model1(cayon)
		plline1(2, t, x2[0], &s2, 8);    // model2(red)
	}
	plend();
	return;
}


/////////////////////////////////////////////////////////////////////////
//  Model 1
void model1(double u,double x[],double t,double ak[])
{
	double k1= 1, tau1= 1;

	ak[0]= (-x[0]+k1*u)/tau1;
}

/////////////////////////////////////////////////////////////////////////
//  Model 2
void model2(double u,double x[],double t,double ak[])
{
	double k2= 0.8, tau2= 0.5;

	ak[0]= (-x[0]+k2*u)/tau2;
}
