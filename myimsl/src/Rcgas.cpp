/////////////////////////////////////////////////////////////////////////
// Program  : rcgas.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 02/03/2003
//
#include <stdio.h>  //temp
#include <stdlib.h>
#include <math.h>
#include "imsl.h"
#include "rcgas.h"

///////////////////// implementation file of RCGAS class /////////////////////
// Constructors and Destructors
RCGAS::RCGAS(int n, int m):popsize(n), lchrom(m)
{
	gen= 0;
	maxgen= 100;
	seed= 123;
	maxmin= -1;
	nworst= 0;
	wsize= 1;
	chrom= ms_RMatrix(popsize,lchrom);
	obj= ms_RVector(popsize);
	fit= ms_RVector(popsize);
	bestchrom= ms_RVector(lchrom);
	xlb= ms_RVector(lchrom);
	xub= ms_RVector(lchrom);
	bestobj= bestfit= avgobj= 0.0;
	pcross= 1.0;
	pmutat= 0.05;
	gam= 0.0;
	for(int i=0; i<7; i++) wbuf[i]= 0.0;
}

RCGAS::~RCGAS(void)
{
	ms_Free_RMatrix(chrom);
	ms_Free_RVector(obj);
	ms_Free_RVector(fit);
	ms_Free_RVector(bestchrom);
	ms_Free_RVector(xlb);
	ms_Free_RVector(xub);
}


//////////////////////////////////////////////////////////////////
// Creates a random initial population
void InitPop(RCGAS &rcga)
{
	int i, j;

	ms_SRands(rcga.seed);    // sets the state of all the generators to seed
	ms_SetRandState(0); // resets the generator to 0
	for(i= 0; i < rcga.popsize; i++) 
	{
		rcga.obj[i]= 0;
		rcga.fit[i]= 0;
		for(j= 0; j < rcga.lchrom; j++)
			rcga.chrom[i][j]= ms_UnifRnd(rcga.xlb[j], rcga.xub[j]);
	}
	return;
}

//////////////////////////////////////////////////////////////////
// Evaluates fitness based on the scaling window scheme
void ScalFit(RCGAS &rcga)
{
	int i, j, m, nmin, nmax, nbest;
	REAL objmin, objmax;

	if(rcga.wsize<1 || rcga.wsize>7)
		ErrorMsg("Bad arguments in 'ScalFit': use 1<= wsize <=7");
	objmin= ms_VMin(rcga.obj, rcga.popsize, nmin);
	objmax= ms_VMax(rcga.obj, rcga.popsize, nmax);
	nbest= (rcga.maxmin == 1) ? nmax:nmin;
	rcga.nworst= (rcga.maxmin == 1) ? nmin:nmax;
	rcga.bestobj= rcga.obj[nbest];
	for(j= 0; j < rcga.lchrom; j++)
		rcga.bestchrom[j]= rcga.chrom[nbest][j];
	rcga.avgobj= ms_Mean(rcga.obj, rcga.popsize);

	if(rcga.gen <= 0)
		rcga.gam= (rcga.maxmin == 1) ? objmin:-objmax;
	for(i=0; i<rcga.popsize; i++)
	{
		rcga.fit[i]= (rcga.maxmin == 1) ? rcga.obj[i]-rcga.gam: -rcga.obj[i]-rcga.gam;
		if(rcga.fit[i] < 0) rcga.fit[i]=0;
	}
	rcga.bestfit= rcga.fit[nbest];
	if(rcga.gen < rcga.wsize)
	{
		m= rcga.gen+1;
		rcga.wbuf[rcga.gen]= (rcga.maxmin == 1) ? objmin:-objmax;
	}
	else
	{
		m= rcga.wsize;
		for(j=0; j<rcga.wsize-1; j++)
			rcga.wbuf[j]=rcga.wbuf[j+1];
		rcga.wbuf[rcga.wsize-1]= (rcga.maxmin == 1) ? objmin:-objmax;
	}
	rcga.gam= ms_VMin(rcga.wbuf, m);
	return;
}
//for(i= 0; i < m; i++) printf("%f ",wbuf[i]); printf("\n");
//printf("%d %d %d %d\n", maxmin, nmin, nmax, nbest); //
//printf("%d\n", nbest); //
//printf("%f\n", bestchrom(j));

//////////////////////////////////////////////////////////////////
// Maps raw fitness into linearly scaled fitness
// sfact: 1.2 - 2
void LinScal(RCGAS &rcga, REAL sfact)
{
	int i;
	REAL fitmin, fitmax, fitavg, delta, a, b;

	if(sfact<1.2 || sfact>2)
		ErrorMsg("Bad arguments in 'LinScal': use 1.2 <= sfact <=2");
	fitmin= ms_VMin(rcga.fit, rcga.popsize);
	fitmax= ms_VMax(rcga.fit, rcga.popsize);
	fitavg= ms_Mean(rcga.fit, rcga.popsize);
	if(fitmax-fitmin < 0.001)
		return;
	if(fitmin >= (sfact*fitavg-fitmax)/(sfact-1))
	{
		delta= fitmax-fitavg;
		if(delta < 0.001)	delta= 0.001;
		a= (sfact-1)*fitavg/delta;
		b= fitavg*(fitmax-sfact*fitavg)/delta;
	}
	else
	{
		delta= fitavg-fitmin;
		if(delta < 0.001)	delta= 0.001;
		a= fitavg/delta;
		b= -fitmin*fitavg/delta;
	}
	for(i= 0; i < rcga.popsize; i++) 
	{
		rcga.fit[i]= a*rcga.fit[i]+b;
		if(rcga.fit[i] < 0) rcga.fit[i]=0;
	}
}

//////////////////////////////////////////////////////////////////
//  Roulette-wheel selection operator
void RwSel(RCGAS &rcga)
{
	int i, *idxchrom;
	REAL fitsum, fitmin, z, *psel;

	fitmin= ms_VMin(rcga.fit, rcga.popsize);
	if(fitmin < 0) 
		ErrorMsg ("Error in 'RwSel': Negative fitness");
	ms_SetRandState(10); // resets the generator to 10
	idxchrom= ms_IVector(rcga.popsize);
	psel= ms_RVector(rcga.popsize);
	fitsum= ms_Sum(rcga.fit, rcga.popsize);
	if(fitsum != 0) 
	{
		for(i= 0; i < rcga.popsize; i++) 
			psel[i]= rcga.fit[i]/fitsum;
		ms_CumSum(psel, rcga.popsize, psel);
		for(i= 0; i < rcga.popsize; i++) 
		{
			z= ms_Rand();
			idxchrom[i]= ms_Locate(psel,rcga.popsize,z)+1;
		}\
	}
	else
		for(i= 0; i < rcga.popsize; i++) 
			idxchrom[i]= i;
	Select(rcga, idxchrom);
	ms_Free_IVector(idxchrom);
	ms_Free_RVector(psel);
	return;
}
//for(i= 0; i < popsize; i++) printf("%f ",psel[i]); printf("\n");
//for(i=0;i<popsize;i++) printf("%d ",idxchrom[i]);printf("\n");//del
//printf("z=%f %d\n",z,k);

//////////////////////////////////////////////////////////////////
// Remainder stochastic sample with repla]cement operator
void RemSel(RCGAS &rcga)
{
	int i, nsel, nassign, *idxchrom;
	REAL fitmin, fitsum, z, expect, *psel;

	fitmin= ms_VMin(rcga.fit, rcga.popsize);
	if(fitmin < 0) 
		ErrorMsg ("Error in 'RemSel': Negative fitness");
	ms_SetRandState(11); // resets the generator to 11
	idxchrom= ms_IVector(rcga.popsize);
	psel= ms_RVector(rcga.popsize);
	fitsum= ms_Sum(rcga.fit, rcga.popsize);
	if(fitsum != 0) 
	{
		nsel= 0;
		for(i= 0; i < rcga.popsize; i++) 
		{
			expect= rcga.fit[i]*rcga.popsize/fitsum;
			nassign= int(expect);
			psel[i]= expect-nassign;
			while(nassign > 0)
			{
				idxchrom[nsel]= i;
				nsel++;
				nassign--;
			}
		}
		if(nsel < rcga.popsize) 
		{
			for(i= 0; i < rcga.popsize; i++)
				psel[i]/= (REAL)(rcga.popsize-nsel);
			ms_CumSum(psel, rcga.popsize, psel);
			for(i= nsel; i < rcga.popsize; i++) 
			{
				z= ms_Rand();
				idxchrom[i]= ms_Locate(psel,rcga.popsize,z)+1;
			}
		}
	}
	else
		for(i= 0; i < rcga.popsize; i++) 
			idxchrom[i]= i;
	Select(rcga, idxchrom);
	ms_Free_RVector(psel);
	ms_Free_IVector(idxchrom);
	return;
}
//for(i=0;i<rcga.popsize;i++) printf("%d ",idxchrom[i]);printf("\n");//del
//for(i=0; i<rcga.popsize; i++) printf("%f ",psel[i]); printf("\n");
//printf("%f\n",expect);//

//////////////////////////////////////////////////////////////////
//  Stochastic universal sampling
void UniSel(RCGAS &rcga)
{
	int i, *idxchrom;
	REAL *pexp, fitmin, fitsum, z;

	fitmin= ms_VMin(rcga.fit, rcga.popsize);
	if(fitmin < 0) 
		ErrorMsg ("Error in 'UniSel': Negative fitness");
	ms_SetRandState(12); // resets the generator to 12
	idxchrom= ms_IVector(rcga.popsize);
	pexp= ms_RVector(rcga.popsize);
	fitsum= ms_Sum(rcga.fit, rcga.popsize);
	if(fitsum != 0) 
	{
		for(i= 0; i < rcga.popsize; i++) 
			pexp[i]= rcga.popsize*rcga.fit[i]/fitsum; // expected value
		ms_CumSum(pexp, rcga.popsize, pexp);
		z= ms_Rand();
		for(i= 0; i < rcga.popsize; i++)
		{
			idxchrom[i]= ms_Locate(pexp,rcga.popsize,z)+1;
			z+= 1.0;
		}
	}
	else
		for(i= 0; i < rcga.popsize; i++) 
			idxchrom[i]= i;
	Select(rcga, idxchrom);
	ms_Free_RVector(pexp);
	ms_Free_IVector(idxchrom);
	return;
}
//for(i= 0; i <rcga.popsize; i++) printf("%d ",idxchrom[i]); printf("\n");
//for(i= 0; i <rcga.popsize; i++) printf("%f\n",pexp[i]); printf("\n");
//printf("z=%f %d\n",z,k);


//////////////////////////////////////////////////////////////////
// Tournament selection operator
void TouSel(RCGAS &rcga, int tsize)
{
	int i, j, k, m, *idxchrom;
	REAL fitmin, fitsum, bfit;

	if(tsize<2 || tsize>rcga.popsize)
		ErrorMsg("Bad arguments in 'TouSel': Tsize < 2 or > rcga.popsize");
	fitmin= ms_VMin(rcga.fit, rcga.popsize);
	if(fitmin < 0) 
		ErrorMsg ("Error in 'TouSel': Negative fitness");
	ms_SetRandState(13); // resets the generator to 13
	idxchrom= ms_IVector(rcga.popsize);
	fitsum= ms_Sum(rcga.fit, rcga.popsize);
	if(fitsum != 0)
	{
		for(i= 0; i < rcga.popsize; i++)
		{
			k= PickUp(rcga.popsize);
			bfit= rcga.fit[k];
			for(j= 1; j < tsize; j++)
			{
				m= PickUp(rcga.popsize);
				if(rcga.fit[m] > bfit)
				{
					bfit= rcga.fit[m];
					k= m;
				}
			}
			idxchrom[i]= k;
		}
	}
	else
		for(i= 0; i < rcga.popsize; i++)
			idxchrom[i]= i;
	Select(rcga, idxchrom);
	ms_Free_IVector(idxchrom);
	return;
}
//for(i= 0; i<rcga.popsize; i++) printf("%d ",idxchrom[i]); printf("\n");
//printf("%d %d\n ", k, m);

//////////////////////////////////////////////////////////////////
// Rank-based selection operator
void RankSel(RCGAS &rcga, REAL rfact)
{
	int i, jrev, *idxchrom, *idx;
	REAL fitmin, fitsum, z, *pexp;

	if(rfact<1.1 || rfact > 2) 
		ErrorMsg("Bad arguments in 'RankSel': use 1.1<= rfact <=2");
	fitmin= ms_VMin(rcga.fit, rcga.popsize);
	if(fitmin < 0) 
		ErrorMsg ("Error in 'RankSel': Negative fitness");
	ms_SetRandState(14); // resets the generator to 14
	idx= ms_IVector(rcga.popsize);
	idxchrom= ms_IVector(rcga.popsize);
	pexp= ms_RVector(rcga.popsize);
	fitsum= ms_Sum(rcga.fit, rcga.popsize);
	if(fitsum != 0)
	{
		ms_Sort(rcga.fit, rcga.popsize, idx); // idx used as temporary storage
		for(i= 0; i < rcga.popsize; i++)
		{
			jrev= rcga.popsize-i;           // rcga.popsize ... 1
			pexp[idx[i]]= rfact-2.0*(rfact-1.0)*(jrev-1.0)/(rcga.popsize-1.0);
		}
		ms_CumSum(pexp, rcga.popsize, pexp);
		z= ms_Rand();
		for(i= 0; i < rcga.popsize; i++)
		{
			idxchrom[i]= ms_Locate(pexp,rcga.popsize,z)+1;
			z+= 1.0;
		}
	}
	else
		for(i= 0; i < rcga.popsize; i++)
			idxchrom[i]= i;
	Select(rcga, idxchrom);
	ms_Free_IVector(idxchrom);
	ms_Free_IVector(idx);
	ms_Free_RVector(pexp);
	return;
}
//for(i=0;i<rcga.popsize;i++) printf("%d ",idxchrom[i]);printf("\n");
//for(i= 0; i < rcga.popsize; i++) printf("%f ",pexp[i]); printf("\n");
//printf("z=%f %d\n", z, k);
//for(i= 0; i < rcga.popsize; i++) printf("%d ",idx[i]);

//////////////////////////////////////////////////////////////////
// Gradient-like selection operator for only RCGAs use
void GradSel(RCGAS &rcga, REAL etha)
{
	int i, j, pass, *idxchrom;
	REAL etha8, normfit, *xnew;

	if(etha<0.5 || etha>2)
		ErrorMsg("Bad arguments in 'GradSel': use 0.5< etha < 2");

	idxchrom= ms_IVector(rcga.popsize);
	if(rcga.bestfit != 0)
	{
		xnew= ms_RVector(rcga.popsize);
		for(i= 0; i < rcga.popsize; i++) 
		{
			etha8= etha;
			normfit= 1-rcga.fit[i]/rcga.bestfit;

			do
			{
				pass= 1;
				for(j= 0; j < rcga.lchrom; j++) 
				{
					xnew[j]= rcga.chrom[i][j]+etha8*normfit*(rcga.bestchrom[j]-rcga.chrom[i][j]);
					if(xnew[j] < rcga.xlb[j] || xnew[j] > rcga.xub[j]) 
					{
						pass= 0;
						etha8*= 0.8;
						break;
					}
				}
			} while(!pass);
			for(j= 0; j < rcga.lchrom; j++)
				rcga.chrom[i][j]= xnew[j];
		}
		ms_Free_RVector(xnew);
	}
	else
	{
		for(i= 0; i < rcga.popsize; i++)
			idxchrom[i]= i;
		Select(rcga, idxchrom);
	}
	ms_Free_IVector(idxchrom);	
	return;
}
//printf("%d %f %f %f\n", j, xnew[j], xlb(j), xub(j));

///////////////////////////////////////////////////////////////////
// One-point crossover operator
void OpXover(RCGAS &rcga)
{
	int i, j, halfsize, mate1, mate2, xpoint;

	if(rcga.pcross<0 || rcga.pcross>1) 
		ErrorMsg("Bad arguments in 'OpXover': use 0< pcross <1");
	ms_SetRandState(20); // resets the generator to 20
	halfsize= rcga.popsize >> 1;
	for(i= 0; i < halfsize; i++)
		if(ms_BernRnd(rcga.pcross)) 
		{
			mate1= 2*i;
			mate2= 2*i+1;
			xpoint= PickUp(rcga.lchrom-1)+1;
			for(j= xpoint; j < rcga.lchrom; j++)
				SWAP(rcga.chrom[mate1][j], rcga.chrom[mate2][j]);
		}
	return;
}
//printf("%d %d %d\n", mate1, mate2, xpoint);

//////////////////////////////////////////////////////////////////
// Two-point crossover operator 
void TpXover(RCGAS &rcga)
{
	int i, j, halfsize, mate1, mate2, xpoint1, xpoint2;

	if(rcga.pcross<0 || rcga.pcross>1)
		ErrorMsg("Bad arguments in 'TpXover': use 0< pcross <1");
	ms_SetRandState(21); // resets the generator to 21
	halfsize= rcga.popsize >> 1;
	for(i= 0; i < halfsize; i++)
		if(ms_BernRnd(rcga.pcross)) 
		{
			mate1= 2*i;
			mate2= 2*i+1;
			xpoint1= PickUp(rcga.lchrom-1)+1;
			xpoint2= PickUp(rcga.lchrom-1)+1;
			while(xpoint1 == xpoint2)
				xpoint2= PickUp(rcga.lchrom-1)+1;
			if(xpoint2 < xpoint1)
				ISWAP(xpoint1, xpoint2);
			for(j= xpoint1; j < xpoint2; j++)
				SWAP(rcga.chrom[mate1][j], rcga.chrom[mate2][j]);
		}
	return;
}
//printf("%d %d  %d %d\n", mate1, mate2, xpoint1, xpoint2);

//////////////////////////////////////////////////////////////////
// Modified simple crossover operator
void MsXover(RCGAS &rcga)
{
	int i, j, halfsize, mate1, mate2, xpoint;
	REAL lam, chrom1, chrom2;

	if(rcga.pcross<0 || rcga.pcross>1)
		ErrorMsg("Bad arguments in 'MsXover': use 0< pcross <1");
	ms_SetRandState(22); // resets the generator to 22
	halfsize= rcga.popsize >> 1;
	for(i= 0; i < halfsize; i++)
		if(ms_BernRnd(rcga.pcross)) 
		{
			mate1= 2*i;
			mate2= 2*i+1;
			xpoint= PickUp(rcga.lchrom-1)+1;
			chrom1= rcga.chrom[mate1][xpoint];
			chrom2= rcga.chrom[mate2][xpoint];
			lam= ms_Rand();
			rcga.chrom[mate1][xpoint]= lam*chrom2+(1.0-lam)*chrom1;
			rcga.chrom[mate2][xpoint]= lam*chrom1+(1.0-lam)*chrom2;
			for(j= xpoint+1; j < rcga.lchrom; j++)
				SWAP(rcga.chrom[mate1][j], rcga.chrom[mate2][j]);
		}
	return;
}
//printf("%d %d %d %f",mate1, mate2, xpoint, lam); printf("\n");

//////////////////////////////////////////////////////////////////
// Flat crossover operator
void FlXover(RCGAS &rcga)
{
	int i, j, mate1, mate2;
	REAL chrom1, chrom2, **tchrom;

	if(rcga.pcross<0 || rcga.pcross>1)
		ErrorMsg("Bad arguments in 'FlXover': use 0< pcross <1");
	ms_SetRandState(23); // resets the generator to 23
	tchrom= ms_RMatrix(rcga.popsize, rcga.lchrom);
	for(i= 0; i < rcga.popsize; i++)
		for(j= 0; j < rcga.lchrom; j++)
			tchrom[i][j]= rcga.chrom[i][j];
	for(i= 0; i < rcga.popsize; i++)
		if(ms_BernRnd(rcga.pcross)) 
		{
			mate1= PickUp(rcga.popsize);
			mate2= PickUp(rcga.popsize);
			while(mate1 == mate2)
				mate2= PickUp(rcga.popsize);
			for(j= 0; j < rcga.lchrom; j++) 
			{
				chrom1= tchrom[mate1][j];
				chrom2= tchrom[mate2][j];
				if(chrom1 > chrom2) SWAP(chrom1, chrom2);
				rcga.chrom[i][j]= ms_UnifRnd(chrom1, chrom2);
			}
		}
	ms_Free_RMatrix(tchrom);
	return;
}
//printf("mate1=%d mate2=%d %d\n",mate1, mate2,i);

//////////////////////////////////////////////////////////////////
// Arithmetic crossover operator
void ArXover(RCGAS &rcga)
{
	int i, j, halfsize, mate1, mate2;
	REAL lam, chrom1, chrom2;

	if(rcga.pcross<0 || rcga.pcross>1)
		ErrorMsg("Bad arguments in 'ArXover': use 0< pcross <1");
	ms_SetRandState(24); // resets the generator to 24
	halfsize= rcga.popsize >> 1;
	for(i= 0; i < halfsize; i++)
		if(ms_BernRnd(rcga.pcross)) 
		{
			mate1= 2*i;
			mate2= 2*i+1;
			for(j= 0; j < rcga.lchrom;j++)
			{
				lam= ms_Rand();
				chrom1= rcga.chrom[mate1][j];
				chrom2= rcga.chrom[mate2][j];
				rcga.chrom[mate1][j]= lam*chrom2+(1.0-lam)*chrom1;
				rcga.chrom[mate2][j]= lam*chrom1+(1.0-lam)*chrom2;
			}
		}
}

//////////////////////////////////////////////////////////////////
// Uniform mutation operator
void UniMut(RCGAS &rcga)
{
	int i, j;

	if(rcga.pmutat<0 || rcga.pmutat>1)
		ErrorMsg("Bad arguments in 'UniMut': use 0< pmutat <1");
	ms_SetRandState(30); // resets the generator to 30
	for(i= 0; i < rcga.popsize; i++)
		for(j= 0; j < rcga.lchrom; j++)
			if(ms_BernRnd(rcga.pmutat))
				rcga.chrom[i][j]= ms_UnifRnd(rcga.xlb[j], rcga.xub[j]);
	return;
}
//printf("i=%d j=%d\n",i,j); 

//////////////////////////////////////////////////////////////////
// Dynamic mutation operator
void DynMut(RCGAS &rcga, REAL b)
{
	int i, j;
	REAL temp;

	if(rcga.pmutat<0 || rcga.pmutat>1)
		ErrorMsg("Bad arguments in 'DynMut': use 0< pmutat <1");
	ms_SetRandState(31); // resets the generator to 31
	for(i= 0; i < rcga.popsize; i++)
		for(j= 0; j < rcga.lchrom; j++)
			if(ms_BernRnd(rcga.pmutat)) 
			{
				temp= ms_Rand()*pow(1-REAL(rcga.gen)/REAL(rcga.maxgen), b);
				if(ms_BernRnd(0.5))
					rcga.chrom[i][j]+= (rcga.xub[j]-rcga.chrom[i][j])*temp;
				else
					rcga.chrom[i][j]-= (rcga.chrom[i][j]-rcga.xlb[j])*temp;
			}
	return;
}
//printf("i=%d j=%d %f\n",i,j,temp);

//////////////////////////////////////////////////////////////////
// Real-number creep mutation operator
void CrpMut(RCGAS &rcga, REAL cfact)
{
	int i, j;
	REAL range1, range2, delta;

	if(rcga.pmutat<0 || rcga.pmutat>1)
		ErrorMsg("Bad arguments in 'CrpMut': use 0< pmutat <1");
	if(cfact<0.1 || cfact>1)
		ErrorMsg("Bad arguments in 'CrpMut': use 0.1<= cfact <=1");
	ms_SetRandState(32); // resets the generator to 32
	for(i= 0; i < rcga.popsize; i++)
		for(j= 0; j < rcga.lchrom; j++)
			if(ms_BernRnd(rcga.pmutat)) 
			{
				range1= fabs(rcga.xub[j]-rcga.chrom[i][j]);
				range2= fabs(rcga.xlb[j]-rcga.chrom[i][j]);
				delta= (range1<range2) ? range1*cfact: range2*cfact;
				if(ms_BernRnd(0.5))
					rcga.chrom[i][j]+= delta;
				else
					rcga.chrom[i][j]-= delta;
			}
	return;
}
//printf("i=%d j=%d\n",i,j);
//printf("i=%d j=%d %f\n",i, j, range);

//////////////////////////////////////////////////////////////////
// Elitism operator(If the elite is destroyed, it replaces 
// the worst in the new population)
void Elitism(RCGAS &rcga)
{
	int j, nmin, nmax;
	REAL objmin, objmax;

	if(rcga.gen < 1) return;
	objmin= ms_VMin(rcga.obj, rcga.popsize, nmin);
	objmax= ms_VMax(rcga.obj, rcga.popsize, nmax);
	if(rcga.maxmin == 1) 
	{
		if(objmax < rcga.bestobj) 
		{
			rcga.obj[nmin]=  rcga.bestobj;
			for(j= 0; j < rcga.lchrom; j++)
				rcga.chrom[nmin][j]= rcga.bestchrom[j];
		}
	}
	else 
	{
		if(objmin > rcga.bestobj) 
		{
			rcga.obj[nmax]= rcga.bestobj;
			for(j= 0; j < rcga.lchrom; j++)
				rcga.chrom[nmax][j]= rcga.bestchrom[j];
		}
	}
	return;
}
//printf("%d %d %f %f\n",nmin, nmax, objmin, objmax);
//printf("%f %f\n",objmin,bestobj);

//////////////////////////////////////////////////////////////////
// Randomly shuffles a population
void Select(RCGAS &rcga, int *idxchrom)
{
	int i, j, n, nsel, npick;
	REAL **newchrom;

	newchrom= ms_RMatrix(rcga.popsize, rcga.lchrom);
	n= rcga.popsize;
	ms_SetRandState(1); // resets the generator to 1
	for(i= 0; i < rcga.popsize; i++)
	{
		npick= PickUp(n);
		nsel= idxchrom[npick];
		for(j= 0; j < rcga.lchrom; j++)
			newchrom[i][j]= rcga.chrom[nsel][j];
			idxchrom[npick]=idxchrom[n-1];
			n--;
	}
	for(i= 0; i < rcga.popsize; i++)
		for(j= 0; j < rcga.lchrom; j++)
			rcga.chrom[i][j]= newchrom[i][j];
	ms_Free_RMatrix(newchrom);
	return;
}

//////////////////////////////////////////////////////////////////
//  Outputs the population and its statistics
void OutputPop(RCGAS &rcga, int op)
{
	int i, j;

	printf("gen=%3d\n", rcga.gen);
	for(i= 0; i < rcga.popsize; i++) {
		printf("%2d) ", i);
		for(j= 0; j < rcga.lchrom; j++)
			printf("%10.3f", rcga.chrom[i][j]);
		if(op == 1 || op == 2) {
			printf("%10.3f %10.3f ", rcga.obj[i], rcga.fit[i]);
		}
		printf("\n");
	}
	printf("\n");
	if(op == 2) {
		printf("fb(x)=%10.3f  ", rcga.bestobj);
		printf("xb= ");
		for(j= 0; j < rcga.lchrom; j++)
			printf("%10.3f",rcga.bestchrom[j]);
		printf("\n");
		printf("fa(x)=%10.3f  gam=%10.3f\n", rcga.avgobj, rcga.gam);
	}
}
