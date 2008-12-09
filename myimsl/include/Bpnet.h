/////////////////////////////////////////////////////////////////////////
// Program  : bpnet.h
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 02/03/2003
//
#ifndef _BPNET_H_
#define _BPNET_H_

//#define MIN_REAL      -HUGE_VAL
//#define MAX_REAL      +HUGE_VAL
#define BIAS          1

class BPNET
{
protected:

public:
	BPNET(int nl, int u1, int u2);
	BPNET(int nl, int u1, int u2, int u3);
	BPNET(int nl, int u1, int u2, int u3, int u4);
	~BPNET(void);	
	typedef struct              // a layer of a network
	{                     
    int        Units;         // number of units in this layer
    REAL*      Output;        // output of ith unit 
    REAL*      Error;         // error term of ith unit
    REAL**     Weight;        // connection weights to ith unit
    REAL**     WeightSave;    // saved weights for stopped training
    REAL**     dWeight;       // last weight deltas for momentum
	} LAYER;

  LAYER*       Layer;         // layers of this net
  LAYER        InputLayer;    // input layer
  LAYER        OutputLayer;   // output layer
  REAL         Alpha;         // momentum factor
  REAL         Eta;           // learning rate
  REAL         Gain;          // gain of sigmoid function
  REAL         Error;         // total net error
	int          Seed;          // seed
	int          NUM_LAYERS;    // number of layers

	void AdjustWeights();
	void BackpropagateNet();
	void ComputeOutputError(REAL* Target);
	void GetOutput(REAL* Output);
	void PropagateNet();
	void RandomWeights();
	void RestoreWeights();
	void SaveWeights();
	void SetInput(REAL* Input);
	void SimulateNet(REAL* Input, REAL* Output, REAL* Target);
	void TrainNet(REAL** Input, REAL** Target, int ndata, int Epochs);
	REAL EvaluateNet(REAL** Input, REAL** Output, REAL** Target, int ndata);
};

#endif // _BPNET_H_
