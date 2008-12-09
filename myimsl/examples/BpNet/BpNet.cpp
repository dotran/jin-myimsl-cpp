#include <stdio.h>
#include "plplot.h"
#include "imsl.h"
#include "bpnet.h"

void InitializeNet(BPNET &Net);
void main()
{
	int i, ndata=100, s=0, s1=0;
//  BOOL Stop, FALSE=0, TRUE=1;
  REAL SumError, **x, **y, **nout;
  BPNET Net(3,1,8,1); // 3-layered NN

	x= RMatrix(ndata,Net.InputLayer.Units);
	y= RMatrix(ndata,Net.OutputLayer.Units);
	nout= RMatrix(ndata,Net.OutputLayer.Units);
	plsdev("win3");	
	plinit();
	plssub(2,2);

	// draws #1 subgraph
	plcol0(7);
	plenv(-1.0, 1.0, 0.0, 2.0, 0, 0); 
	pllab("x","f(x)","Training data"); 

	LinSpace(-1.0, 1.0, ndata, &(x[0][0]));
	for(i=0; i<ndata; i++) {
		y[i][0]= x[i][0]*x[i][0];
	}	
//	for(i=0; i<ndata; i++) {
//		x[i][0]= UnifRnd(-1.0,1.0);
//		y[i][0]= x[i][0]*x[i][0];
//	}
	plcol0(2);
	plpoin(ndata, &(x[0][0]), &(y[0][0]), 21);  // draws symbols

	// draws #2 subgraph
	pladv(1);
	plcol0(7);
	plenv(0.0, 200.0, 0.0, 5.0, 0, 0); 
	pllab("No of Epoch","Sum error","Learning Process"); 
	
  InitializeNet(Net);
  Net.RandomWeights();
  for(i=0; i<200; i++)
	{
		Net.TrainNet(x, y, ndata, 10);
		Net.SaveWeights();
    SumError= Net.EvaluateNet(x, nout, y, ndata);
		plline1(0, (i+1), SumError, &s, 2); 	
    if(SumError < 0.01) break;
	}

	// draws #3 subgraph
	pladv(2);
	plcol0(7);
	plenv(-1.0, 1.0, 0.0, 2.0, 0, 0); 
	pllab("x","f(x)","Training data"); 
	LinSpace(-1.0, 1.0, ndata, &(x[0][0]));
	for(i=0; i<ndata; i++) {
		y[i][0]= x[i][0]*x[i][0];
	}	
	plcol0(2);
	plline(ndata, &(x[0][0]), &(y[0][0]));

	// draws #4 subgraph
	pladv(3);
	plcol0(7);
	plenv(-1.0, 1.0, 0.0, 2.0, 0, 0); 
	pllab("x","f(x)","Training data"); 

	Net.RestoreWeights();
	SumError= Net.EvaluateNet(x,nout,y,ndata);
	for(i=0; i<ndata; i++) 
		plline1(1, x[i][0], nout[i][0], &s1, 2); 
	plend();
	Free_RMatrix(x);
	Free_RMatrix(y);
	Free_RMatrix(nout);
  return;
}
//		printf("%f %f\n",Net.Error,SumError);

//////////////////////////////////////////////////////////////////////////////////
// 
void InitializeNet(BPNET &Net)
{
  Net.Alpha= 0.9;
  Net.Eta= 0.15;
  Net.Gain= 1;
	Net.Seed= 91;
}

