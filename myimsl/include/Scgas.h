/////////////////////////////////////////////////////////////////////////
// Program  : scgas.h
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 02/03/2003
//
#ifndef _SCGAS_H_
#define _SCGAS_H_

#include "realtype.h"

class SCGAS
{
protected:
	REAL wbuf[7];             // buffer for scaling window

public:
	//SCGAS();                // constructor
	SCGAS(int n, int m);      // constructor(n: maxpopsize, n: maxlchrom)
	~SCGAS();                 // destructor
	int popsize;              // population size
	int lchrom;               // length of the chromosome per individual
	int gen;                  // generation
	int maxgen;               // maximum generation number
	int seed;                 // ramdom seed
	int maxmin;		            // 1 indicates maximization problem; -1, otherwise
	int wsize;                // scaling window size
	int nworst;               // the worst chromosome number
	int **chrom;              // chromosome for the individual
	int *bestchrom;           // chromosome for the best individual
	REAL *obj;                // objective function value of the individual
	REAL *fit;                // scaled fitness of the individual
	REAL bestobj;             // objective function value of the best individual
	REAL bestfit;             // scaled fitness of the best individual
	REAL avgobj;              // average objective function value of the population
	REAL pcross;              // crossover probability
	REAL pmutat;              // mutation probability
	REAL gam;                 // coefficient for window scaling

	friend void ScalFit(SCGAS &scga);              // fitness evaluation based on scaling window scheme
};
	void InitPop(SCGAS &scga);              // random population initialisation
	void LinScal(SCGAS &scga, REAL sfact);  // maps raw fitness into linearly scaled fitness
	void RwSel(SCGAS &scga);                // Roulette-wheel selection
	void RemSel(SCGAS &scga);               // remainder stochastic sample with repla]cement
	void UniSel(SCGAS &scga);               // stochastic universal sampling
	void TouSel(SCGAS &scga, int tsize);    // tournament selection
	void RankSel(SCGAS &scga, REAL rfact);  // rank-based selection
	void PMXover(SCGAS &scga);              // partially mapped crossover
	void CXover(SCGAS &scga);               // cycle crossover
	void OXover(SCGAS &scga);               // order crossover
	void InsMut(SCGAS &scga);               // insertion mutation
	void SwapMut(SCGAS &scga);              // swap mutation
	void Invers(SCGAS &scga);               // inversion
	void Elitism(SCGAS &scga);              // elitism
	void Select(SCGAS &scga, int *idxchrom);// population shuffle

#endif // _SCGAS_H_
