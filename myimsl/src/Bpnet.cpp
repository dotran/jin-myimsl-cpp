#include <stdlib.h>
#include <math.h>
#include "realtype.h"
#include "bpnet.h"

BPNET::BPNET(int nl, int u1, int u2):	NUM_LAYERS(nl)
{
	int l, i, Units[5];

	Units[0]= u1;
	Units[1]= u2;

  Layer= (LAYER*) calloc(NUM_LAYERS, sizeof(LAYER));
  for(l=0; l<NUM_LAYERS; l++)
	{      
    Layer[l].Units= Units[l];
    Layer[l].Output= (REAL*)  calloc(Units[l]+1, sizeof(REAL));
    Layer[l].Error= (REAL*)  calloc(Units[l]+1, sizeof(REAL));
    Layer[l].Weight= (REAL**) calloc(Units[l]+1, sizeof(REAL*));
    Layer[l].WeightSave= (REAL**) calloc(Units[l]+1, sizeof(REAL*));
    Layer[l].dWeight= (REAL**) calloc(Units[l]+1, sizeof(REAL*));
    Layer[l].Output[0]= BIAS;
      
    if(l != 0) 
		{
      for(i=1; i<=Units[l]; i++) 
			{
        Layer[l].Weight[i]= (REAL*) calloc(Units[l-1]+1, sizeof(REAL));
        Layer[l].WeightSave[i]= (REAL*) calloc(Units[l-1]+1, sizeof(REAL));
        Layer[l].dWeight[i]= (REAL*) calloc(Units[l-1]+1, sizeof(REAL));
      }
    }
  }
  InputLayer= Layer[0];
  OutputLayer= Layer[NUM_LAYERS-1];
  Alpha= 0.9;
  Eta= 0.25;
  Gain= 1;
  Seed= 1;
}

BPNET::BPNET(int nl, int u1, int u2, int u3):	NUM_LAYERS(nl)
{
	int l, i, Units[5];

	Units[0]= u1;
	Units[1]= u2;
	Units[2]= u3;

  Layer= (LAYER*) calloc(NUM_LAYERS, sizeof(LAYER));
  for(l=0; l<NUM_LAYERS; l++)
	{      
    Layer[l].Units= Units[l];
    Layer[l].Output= (REAL*)  calloc(Units[l]+1, sizeof(REAL));
    Layer[l].Error= (REAL*)  calloc(Units[l]+1, sizeof(REAL));
    Layer[l].Weight= (REAL**) calloc(Units[l]+1, sizeof(REAL*));
    Layer[l].WeightSave= (REAL**) calloc(Units[l]+1, sizeof(REAL*));
    Layer[l].dWeight= (REAL**) calloc(Units[l]+1, sizeof(REAL*));
    Layer[l].Output[0]= BIAS;
      
    if(l != 0) 
		{
      for(i=1; i<=Units[l]; i++) 
			{
        Layer[l].Weight[i]= (REAL*) calloc(Units[l-1]+1, sizeof(REAL));
        Layer[l].WeightSave[i]= (REAL*) calloc(Units[l-1]+1, sizeof(REAL));
        Layer[l].dWeight[i]= (REAL*) calloc(Units[l-1]+1, sizeof(REAL));
      }
    }
  }
  InputLayer= Layer[0];
  OutputLayer= Layer[NUM_LAYERS-1];
  Alpha= 0.9;
  Eta= 0.25;
  Gain= 1;
  Seed= 1;
}

BPNET::BPNET(int nl, int u1, int u2, int u3, int u4):	NUM_LAYERS(nl)
{
	int l, i, Units[5];

	Units[0]= u1;
	Units[1]= u2;
	Units[2]= u3;
	Units[3]= u4;

  Layer= (LAYER*) calloc(NUM_LAYERS, sizeof(LAYER));
  for(l=0; l<NUM_LAYERS; l++)
	{      
    Layer[l].Units= Units[l];
    Layer[l].Output= (REAL*)  calloc(Units[l]+1, sizeof(REAL));
    Layer[l].Error= (REAL*)  calloc(Units[l]+1, sizeof(REAL));
    Layer[l].Weight= (REAL**) calloc(Units[l]+1, sizeof(REAL*));
    Layer[l].WeightSave= (REAL**) calloc(Units[l]+1, sizeof(REAL*));
    Layer[l].dWeight= (REAL**) calloc(Units[l]+1, sizeof(REAL*));
    Layer[l].Output[0]= BIAS;
      
    if(l != 0) 
		{
      for(i=1; i<=Units[l]; i++) 
			{
        Layer[l].Weight[i]= (REAL*) calloc(Units[l-1]+1, sizeof(REAL));
        Layer[l].WeightSave[i]= (REAL*) calloc(Units[l-1]+1, sizeof(REAL));
        Layer[l].dWeight[i]= (REAL*) calloc(Units[l-1]+1, sizeof(REAL));
      }
    }
  }
  InputLayer= Layer[0];
  OutputLayer= Layer[NUM_LAYERS-1];
  Alpha= 0.9;
  Eta= 0.25;
  Gain= 1;
  Seed= 1;
}

BPNET::~BPNET(void)
{
  for(int l=0; l<NUM_LAYERS; l++) 
	{
    free(Layer[l].Output);
    free(Layer[l].Error);
    free(Layer[l].Weight);
    free(Layer[l].WeightSave);
    free(Layer[l].dWeight);
	}
  free(Layer);
}

//////////////////////////////////////////////////////////////////////////////////
// 
void BPNET::RandomWeights()
{
  int l,i,j;
   
  srand(Seed);
  for(l=1; l<NUM_LAYERS; l++) 
	{
    for(i=1; i<=Layer[l].Units; i++) 
		{
      for(j=0; j<=Layer[l-1].Units; j++)
        Layer[l].Weight[i][j]= UnifRnd(-0.5, 0.5);
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////
// S I M U L A T I N G   T H E   N E T
// 
void BPNET::TrainNet(REAL** Input, REAL** Target, int ndata, int Epochs)
{
  int  i, j;
  REAL Output[200]; //change

  for(i=0; i<Epochs; i++) 
	{
		for(j=0; j<ndata; j++) 
		{
			SimulateNet(Input[j], Output, Target[j]);
	    BackpropagateNet();
		  AdjustWeights();
	  }
  }
}

//////////////////////////////////////////////////////////////////////////////////
// 
void BPNET::SimulateNet(REAL* Input, REAL* Output, REAL* Target)
{
  SetInput(Input);
  PropagateNet();
  GetOutput(Output);
  ComputeOutputError(Target);
}

//////////////////////////////////////////////////////////////////////////////////
// 
void BPNET::SetInput(REAL* Input)
{   
  for(int i=1; i<=InputLayer.Units; i++) 
    InputLayer.Output[i]= Input[i-1];
}

//////////////////////////////////////////////////////////////////////////////////
// P R O P A G A T I N G   S I G N A L S
//
void BPNET::PropagateNet()
{
  int l,i,j;
  REAL Sum;

  for(l=0; l<NUM_LAYERS-1; l++) {
		for(i=1; i<=Layer[l+1].Units; i++) 
		{
			Sum= 0;
			for(j=0; j<=Layer[l].Units; j++) 
			{
				Sum += Layer[l+1].Weight[i][j] * Layer[l].Output[j];
			}
			Layer[l+1].Output[i] = 1 / (1 + exp(-Gain * Sum));
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////
// 
void BPNET::GetOutput(REAL* Output)
{
  for(int i=1; i<=OutputLayer.Units; i++)
    Output[i-1]= OutputLayer.Output[i];
}

//////////////////////////////////////////////////////////////////////////////////
//
void BPNET::ComputeOutputError(REAL* Target)
{
  int i;
  REAL Out, Err;
   
  Error= 0;
  for(i=1; i<=OutputLayer.Units; i++) 
	{
    Out= OutputLayer.Output[i];
    Err= Target[i-1]-Out;
    OutputLayer.Error[i]= Gain * Out * (1-Out) * Err;
    Error+= 0.5*Err*Err;
  }
}

//////////////////////////////////////////////////////////////////////////////////
// B A C K P R O P A G A T I N G   E R R O R S
//
void BPNET::BackpropagateNet()
{
  int l,i,j;
  REAL Out, Err;
   
  for(l=NUM_LAYERS-1; l>1; l--) 
	{
	  for(i=1; i<=Layer[l-1].Units; i++) 
		{
		  Out= Layer[l-1].Output[i];
			Err= 0;
			for(j=1; j<=Layer[l].Units; j++) 
			{
	      Err+= Layer[l].Weight[j][i] * Layer[l].Error[j];
		  }
			Layer[l-1].Error[i]= Gain * Out * (1-Out) * Err;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////
//
void BPNET::AdjustWeights()
{
  int l,i,j;
  REAL Out, Err, dWeight;
   
  for(l=1; l<NUM_LAYERS; l++) 
	{
    for(i=1; i<=Layer[l].Units; i++) 
		{
      for(j=0; j<=Layer[l-1].Units; j++) 
			{
        Out= Layer[l-1].Output[j];
        Err= Layer[l].Error[i];
        dWeight= Layer[l].dWeight[i][j];
        Layer[l].Weight[i][j]+= Eta * Err * Out + Alpha * dWeight;
        Layer[l].dWeight[i][j]= Eta * Err * Out;
      }
    }
  }
}
/////////////////////////////////////////////////////////////////////////////////
// S U P P O R T   F O R   S T O P P E D   T R A I N I N G
// 
void BPNET::SaveWeights()
{
  int l,i,j;

  for(l=1; l<NUM_LAYERS; l++) 
	{
    for(i=1; i<=Layer[l].Units; i++) 
		{
      for(j=0; j<=Layer[l-1].Units; j++) 
			{
        Layer[l].WeightSave[i][j]= Layer[l].Weight[i][j];
      }
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////
// 
void BPNET::RestoreWeights()
{
  int l,i,j;

  for(l=1; l<NUM_LAYERS; l++) 
	{
    for(i=1; i<=Layer[l].Units; i++) 
		{
      for(j=0; j<=Layer[l-1].Units; j++) 
			{
        Layer[l].Weight[i][j]= Layer[l].WeightSave[i][j];
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////
// 
REAL BPNET::EvaluateNet(REAL** Input, REAL** Output, REAL** Target, int ndata)
{
  int i,j;
  REAL SumError= 0, NetOut[20];

  for(i=0; i<ndata; i++) 
	{
    SimulateNet(Input[i], NetOut, Target[i]);
		for(j=0; j<OutputLayer.Units; j++) //
			Output[i][j]= NetOut[j];         // change
    SumError+= Error;
  }
	return SumError;
}

