/////////////////////////////////////////////////////////////////////////
// Program  : anneal.h
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003
//
#ifndef _ANNEAL_H_
#define _ANNEAL_H_

#include "realtype.h"

#ifndef max_len_chrom
#define max_len_chrom   20
#endif

class ANNEAL
{
protected:
	int maxlchrom;               // maximum length of chrom

public:
	ANNEAL(int n=max_len_chrom); // constructor
	~ANNEAL();                   // destructor
	int maxgen;                  // maximum generation number
	int lchrom;                  // length ofchromosome
	int nsucc;                   // nsucc
	int seed;                    // ramdom seed
	int *path;                   // travel path
	REAL tfactr;                 // factor
	REAL obj;                    // objective function value of the individual
	REAL temp;                   // temperature
	void Anneal(REAL x[], REAL y[], int lchrom);
};

#endif // _ANNEAL_H_
