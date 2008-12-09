/////////////////////////////////////////////////////////////////////////
// Program  : rsgas.h
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 02/03/2003
//
#ifndef _RCGAS_H_
#define _RCGAS_H_

#include "realtype.h"

class RCGAS
{
protected:
	REAL wbuf[7];             // buffer for the scaling window scheme

public:
	RCGAS(int n,int m);       // constructor(n: popsize, n: lchrom)
	~RCGAS();                 // destructor
	int popsize;              // population size
	int lchrom;               // length of the chromosome per individual
	int gen;                  // generation
	int maxgen;               // maximum generation number
	int seed;                 // ramdom seed
	int maxmin;		            // 1 indicates maximization problem; -1, otherwise
	int wsize;                // scaling window size
	int nworst;               // the worst chromosome number
	REAL **chrom;             // chromosome for the individual
	REAL *obj;                // objective function value of the individual
	REAL *fit;                // scaled fitness of the individual
	REAL *bestchrom;          // chromosome for the best individual
	REAL *xlb;                // lower bound of the gene
	REAL *xub;                // upper bound of the gene
	REAL bestobj;             // objective function value of the best individual
	REAL bestfit;             // scaled fitness of the best individual
	REAL avgobj;              // average objective function value of the population
	REAL pcross;              // crossover probability
	REAL pmutat;              // mutation probability
	REAL gam;                 // coefficient for window scaling
	friend void ScalFit(RCGAS &rcga);       // fitness evaluation based on scaling window scheme
};
	void InitPop(RCGAS &rcga);              // random population initialisation
	void LinScal(RCGAS &rcga, REAL sfact);  // maps raw fitness into linearly scaled fitness
	void RwSel(RCGAS &rcga);                // Roulette-wheel selection
	void RemSel(RCGAS &rcga);               // remainder stochastic sample with repla]cement
	void UniSel(RCGAS &rcga);               // stochastic universal sampling
	void TouSel(RCGAS &rcga, int tsize);    // tournament selection
	void RankSel(RCGAS &rcga, REAL rfact);  // rank-based selection
	void GradSel(RCGAS &rcga, REAL etha);   // gradient-like selection for only RCGAs use
	void OpXover(RCGAS &rcga);              // one-point crossover
	void TpXover(RCGAS &rcga);              // two-point crossover 
	void MsXover(RCGAS &rcga);              // modified simple crossover
	void FlXover(RCGAS &rcga);              // flat crossover
	void ArXover(RCGAS &rcga);              // arithmetic crossover
	void UniMut(RCGAS &rcga);               // uniform mutation
	void DynMut(RCGAS &rcga, REAL b);       // dynamic mutation
	void CrpMut(RCGAS &rcga, REAL cfact);   // real-number creep mutation
	void Elitism(RCGAS &rcga);              // elitism
	void Select(RCGAS &rcga, int *idxchrom);// population shuffle
	void OutputPop(RCGAS &rcga, int op);    // use for program test

#endif // _RCGAS_H_
