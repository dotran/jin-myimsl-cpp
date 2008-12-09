/////////////////////////////////////////////////////////////////////////
// Program  : scgas.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 02/03/2003
//
#include <stdlib.h>
#include <math.h>
#include "imsl.h"
#include "scgas.h"

///////////////////// implementation file of SCGAS class /////////////////////
// Constructors and Destructors

SCGAS::SCGAS(int n,int m):popsize(n), lchrom(m)
{
	gen= 0;
	maxgen= 100;
	seed= 1;
	maxmin= -1;
	wsize= 1;
	nworst= 0;
	chrom= ms_IMatrix(popsize,lchrom);
	obj= ms_RVector(popsize);
	fit= ms_RVector(popsize);
	bestchrom= ms_IVector(lchrom);
	bestobj= bestfit= avgobj= 0.0;
	pcross= 0.9;
	pmutat= 0.05;
	gam= 0.0;
	for(int i=0; i<7; i++) wbuf[i]= 0.0;
}

SCGAS::~SCGAS(void)
{
	ms_Free_IMatrix(chrom);
	ms_Free_IVector(bestchrom);
	ms_Free_RVector(obj);
	ms_Free_RVector(fit);
}


//////////////////////////////////////////////////////////////////
// Creates a random initial population
void InitPop(SCGAS &scga)
{
	int i, j, *idxchrom,npick;

	idxchrom= ms_IVector(scga.lchrom);
	ms_SRands(scga.seed);    // resets the state seed of all the generators
	ms_SetRandState(0); // resets the generator to 0
	for(i= 0; i < scga.popsize; i++)
	{
		scga.obj[i]= 0;
		scga.fit[i]= 0;
		for(j= 0; j < scga.lchrom; j++)
			idxchrom[j]= j;
		for(j= 0; j < scga.lchrom; j++)
		{
			npick= PickUp(scga.lchrom-j);
			scga.chrom[i][j]= idxchrom[npick];
			idxchrom[npick]= idxchrom[scga.lchrom-1-j];
		}
	}
	ms_Free_IVector(idxchrom);
	return;
}
//printf("%3d %3d\n", lchrom-j, npick); //


//////////////////////////////////////////////////////////////////
// Evaluates scaled fitness
void ScalFit(SCGAS &scga)
{
	int i, j, m, nmin, nmax, nbest;
	REAL objmin, objmax;
	
	if(scga.wsize<1 || scga.wsize>7)
		ErrorMsg("Bad arguments in 'ScalFit': use 1<= wsize <=7");
	objmin= ms_VMin(scga.obj, scga.popsize, nmin);
	objmax= ms_VMax(scga.obj, scga.popsize, nmax);
	nbest= (scga.maxmin == 1) ? nmax:nmin;
	scga.nworst= (scga.maxmin == 1) ? nmin:nmax;
	scga.bestobj= scga.obj[nbest];
	for(j= 0; j < scga.lchrom; j++)
		scga.bestchrom[j]= scga.chrom[nbest][j];
	scga.avgobj= ms_Sum(scga.obj, scga.popsize)/scga.popsize;

	if(scga.gen <= 0)
		scga.gam= (scga.maxmin == 1) ? objmin:-objmax;
	for(i=0; i<scga.popsize; i++)
	{
		scga.fit[i]= (scga.maxmin == 1) ? scga.obj[i]-scga.gam: -scga.obj[i]-scga.gam;
		if(scga.fit[i] < 0) scga.fit[i]=0;
	}
	scga.bestfit= scga.fit[nbest];
	if(scga.gen < scga.wsize)
	{
		m= scga.gen+1;
		scga.wbuf[scga.gen]= (scga.maxmin == 1) ? objmin:-objmax;
	}
	else
	{
		m= scga.wsize;
		for(j=0; j<scga.wsize-1; j++)
			scga.wbuf[j]=scga.wbuf[j+1];
		scga.wbuf[scga.wsize-1]= (scga.maxmin == 1) ? objmin:-objmax;
	}
	scga.gam= ms_VMin(scga.wbuf, m);
	return;
}
//for(i= 0; i < m; i++) printf("%f ",wbuf[i]); printf("\n");
//printf("%d %d %d %d\n", maxmin, nmin, nmax, nbest); //
//printf("%f\n", bestchrom(j));

//////////////////////////////////////////////////////////////////
// Maps raw fitness into linearly scaled fitness
// sfact: 1.2 - 2
void LinScal(SCGAS &scga, REAL sfact)
{
	int i;
	REAL fitmin, fitmax, fitavg, delta, a, b;

	if(sfact<1.2 || sfact>2)
		ErrorMsg("Bad arguments in 'LinScal': use 1.2 <= sfact <=2");
	fitmin= ms_VMin(scga.fit, scga.popsize);
	fitmax= ms_VMax(scga.fit, scga.popsize);
	fitavg= ms_Mean(scga.fit, scga.popsize);
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
	for(i= 0; i < scga.popsize; i++) 
		scga.fit[i]= a*scga.fit[i]+b;
}

//////////////////////////////////////////////////////////////////
//  Roulette-wheel selection operator
void RwSel(SCGAS &scga)
{
	int i, *idxchrom;
	REAL fitsum, fitmin, z, *psel;

	fitmin= ms_VMin(scga.fit, scga.popsize);
	if(fitmin < 0) 
		ErrorMsg ("Error in 'RwSel': Negative fitness");
	ms_SetRandState(10); // resets the generator to 10
	idxchrom= ms_IVector(scga.popsize);
	psel= ms_RVector(scga.popsize);
	fitsum= ms_Sum(scga.fit, scga.popsize);
	if(fitsum != 0) 
	{
		for(i= 0; i < scga.popsize; i++) 
			psel[i]= scga.fit[i]/fitsum;
		ms_CumSum(psel, scga.popsize, psel);
		for(i= 0; i < scga.popsize; i++) 
		{
			z= ms_Rand();
			idxchrom[i]= ms_Locate(psel,scga.popsize,z)+1;
		}
	}
	else
		for(i= 0; i < scga.popsize; i++) 
			idxchrom[i]= i;
	Select(scga, idxchrom);
	ms_Free_IVector(idxchrom);
	ms_Free_RVector(psel);
	return;
}
//for(i= 0; i < scga.popsize; i++) printf("%f ",psel[i]); printf("\n");
//for(i=0;i<scga.popsize;i++) printf("%d ",idxchrom[i]);printf("\n");//del
//printf("z=%f %d\n",z,k);

//////////////////////////////////////////////////////////////////
// Remainder stochastic sample with repla]cement operator
void RemSel(SCGAS &scga)
{
	int i, nsel, nassign, *idxchrom;
	REAL fitmin, fitsum, z, expect, *psel;

	fitmin= ms_VMin(scga.fit, scga.popsize);
	if(fitmin < 0) 
		ErrorMsg ("Error in 'RemSel': Negative fitness");
	ms_SetRandState(11); // resets the generator to 11
	idxchrom= ms_IVector(scga.popsize);
	psel= ms_RVector(scga.popsize);
	fitsum= ms_Sum(scga.fit, scga.popsize);
	if(fitsum != 0) 
	{
		nsel= 0;
		for(i= 0; i < scga.popsize; i++) 
		{
			expect= scga.fit[i]*scga.popsize/fitsum;
			nassign= int(expect);
			psel[i]= expect-nassign;
			while(nassign > 0)
			{
				idxchrom[nsel]= i;
				nsel++;
				nassign--;
			}
		}
		if(nsel < scga.popsize) 
		{
			for(i= 0; i < scga.popsize; i++)
				psel[i]/= (REAL)(scga.popsize-nsel);
			ms_CumSum(psel, scga.popsize, psel);
			for(i= nsel; i < scga.popsize; i++) 
			{
				z= ms_Rand();
				idxchrom[i]= ms_Locate(psel,scga.popsize,z)+1;
			}
		}
	}
	else
		for(i= 0; i < scga.popsize; i++) 
			idxchrom[i]= i;
	Select(scga, idxchrom);
	ms_Free_RVector(psel);
	ms_Free_IVector(idxchrom);
	return;
}
//for(i=0;i<scga.popsize;i++) printf("%d ",idxchrom[i]);printf("\n");//del
//for(i=0; i<scga.popsize; i++) printf("%f ",psel[i]); printf("\n");
//printf("%f\n",expect);//

//////////////////////////////////////////////////////////////////
//  Stochastic universal sampling
void UniSel(SCGAS &scga)
{
	int i, *idxchrom;
	REAL *pexp, fitmin, fitsum, z;

	fitmin= ms_VMin(scga.fit, scga.popsize);
	if(fitmin < 0) 
		ErrorMsg ("Error in 'UniSel': Negative fitness");
	ms_SetRandState(12); // resets the generator to 12
	idxchrom= ms_IVector(scga.popsize);
	pexp= ms_RVector(scga.popsize);
	fitsum= ms_Sum(scga.fit, scga.popsize);
	if(fitsum != 0) 
	{
		for(i= 0; i < scga.popsize; i++) 
			pexp[i]= scga.popsize*scga.fit[i]/fitsum; // expected value
		ms_CumSum(pexp, scga.popsize, pexp);
		z= ms_Rand();
		for(i= 0; i < scga.popsize; i++)
		{
			idxchrom[i]= ms_Locate(pexp,scga.popsize,z)+1;
			z+= 1.0;
		}
	}
	else
		for(i= 0; i < scga.popsize; i++) 
			idxchrom[i]= i;
	Select(scga, idxchrom);
	ms_Free_RVector(pexp);
	ms_Free_IVector(idxchrom);
	return;
}
//for(i= 0; i <scga.popsize; i++) printf("%d ",idxchrom[i]); printf("\n");
//for(i= 0; i <scga.popsize; i++) printf("%f\n",pexp[i]); printf("\n");
//printf("z=%f %d\n",z,k);


//////////////////////////////////////////////////////////////////
// Tournament selection operator
void TouSel(SCGAS &scga, int tsize)
{
	int i, j, k, m, *idxchrom;
	REAL fitmin, fitsum, bfit;

	if(tsize<2 || tsize>scga.popsize)
		ErrorMsg("Bad arguments in 'TouSel': Tsize < 2 or > scga.popsize");
	fitmin= ms_VMin(scga.fit, scga.popsize);
	if(fitmin < 0) 
		ErrorMsg ("Error in 'TouSel': Negative fitness");
	ms_SetRandState(13); // resets the generator to 13
	idxchrom= ms_IVector(scga.popsize);
	fitsum= ms_Sum(scga.fit, scga.popsize);
	if(fitsum != 0)
	{
		for(i= 0; i < scga.popsize; i++)
		{
			k= PickUp(scga.popsize);
			bfit= scga.fit[k];
			for(j= 1; j < tsize; j++)
			{
				m= PickUp(scga.popsize);
				if(scga.fit[m] > bfit)
				{
					bfit= scga.fit[m];
					k= m;
				}
			}
			idxchrom[i]= k;
		}
	}
	else
		for(i= 0; i < scga.popsize; i++)
			idxchrom[i]= i;
	Select(scga, idxchrom);
	ms_Free_IVector(idxchrom);
	return;
}
//for(i= 0; i<scga.popsize; i++) printf("%d ",idxchrom[i]); printf("\n");
//printf("%d %d\n ", k, m);

//////////////////////////////////////////////////////////////////
// Rank-based selection operator
void RankSel(SCGAS &scga, REAL rfact)
{
	int i, jrev, *idxchrom, *idx;
	REAL fitmin, fitsum, z, *pexp;

	if(rfact<1.1 || rfact > 2) 
		ErrorMsg("Bad arguments in 'RankSel': use 1.1<= rfact <=2");
	fitmin= ms_VMin(scga.fit, scga.popsize);
	if(fitmin < 0) 
		ErrorMsg ("Error in 'RankSel': Negative fitness");
	ms_SetRandState(14); // resets the generator to 14
	idx= ms_IVector(scga.popsize);
	idxchrom= ms_IVector(scga.popsize);
	pexp= ms_RVector(scga.popsize);
	fitsum= ms_Sum(scga.fit, scga.popsize);
	if(fitsum != 0)
	{
		ms_Sort(scga.fit, scga.popsize, idx); // idx used as temporary storage
		for(i= 0; i < scga.popsize; i++)
		{
			jrev= scga.popsize-i;           // scga.popsize ... 1
			pexp[idx[i]]= rfact-2.0*(rfact-1.0)*(jrev-1.0)/(scga.popsize-1.0);
		}
		ms_CumSum(pexp, scga.popsize, pexp);
		z= ms_Rand();
		for(i= 0; i < scga.popsize; i++)
		{
			idxchrom[i]= ms_Locate(pexp,scga.popsize,z)+1;
			z+= 1.0;
		}
	}
	else
		for(i= 0; i < scga.popsize; i++)
			idxchrom[i]= i;
	Select(scga, idxchrom);
	ms_Free_IVector(idxchrom);
	ms_Free_IVector(idx);
	ms_Free_RVector(pexp);
	return;
}
//for(i=0;i<scga.popsize;i++) printf("%d ",idxchrom[i]);printf("\n");
//for(i= 0; i < scga.popsize; i++) printf("%f ",pexp[i]); printf("\n");
//printf("z=%f %d\n", z, k);
//for(i= 0; i < scga.popsize; i++) printf("%d ",idx[i]);


///////////////////////////////////////////////////////////////////
// Partially mapped crossover operator
void PMXover(SCGAS &scga)
{
	int i,j, k, gene, halfpop, mate1, mate2, xpoint1, xpoint2;

	if(scga.pcross<0 || scga.pcross>1) 
		ErrorMsg("Bad arguments in 'PMXover': use 0< pcross <1");
	ms_SetRandState(20); // resets the generator to 20
	halfpop= scga.popsize >> 1;
	for(i= 0; i < halfpop; i++) 
	{
		if(ms_BernRnd(scga.pcross)) 
		{
			mate1= 2*i;
			mate2= 2*i+1;
			xpoint1= PickUp(scga.lchrom-1)+1;
			xpoint2= PickUp(scga.lchrom-1)+1;
			while(xpoint1 == xpoint2)
				xpoint2= PickUp(scga.lchrom-1)+1;
			if(xpoint2 < xpoint1)
				ISWAP(xpoint1, xpoint2);
			for(j= 0; j < scga.lchrom; j++) 
			{
				if(j < xpoint1 || j >= xpoint2) 
				{
					// generates a part of  child 1
					gene= scga.chrom[mate1][j];
					k= xpoint1;
					while(k < xpoint2) 
					{
						if(gene == scga.chrom[mate2][k]) 
						{
							gene= scga.chrom[mate1][k];
							scga.chrom[mate1][j]= gene;
							k= xpoint1;
						}
						else
							k++;
					}
					// generates a part of child 2
					gene= scga.chrom[mate2][j];
					k= xpoint1;
					while(k < xpoint2) 
					{
						if(gene == scga.chrom[mate1][k]) 
						{
							gene= scga.chrom[mate2][k];
							scga.chrom[mate2][j]= gene;
							k= xpoint1;
						}
						else
							k++;
					}
				}
			}
			// exchanges the substrings(mapping sections)
			for(j= xpoint1; j < xpoint2; j++)
				ISWAP(scga.chrom[mate1][j],scga.chrom[mate2][j]);
		}
	}
	return;
}
//printf("%d %d %d\n", mate1, mate2, xpoint);
//printf("%d %d  %d %d\n", mate1, mate2, xpoint1, xpoint2);
//printf("i=%d mate1=%d mate2=%d ",i,mate1, mate2);

///////////////////////////////////////////////////////////////////
// Order crossover operator
void OXover(SCGAS &scga)
{
	int i,j, k, n, selgene, halfpop, mate1, mate2, xpoint1, xpoint2;
	int *chrom1, *chrom2;

	if(scga.pcross<0 || scga.pcross>1) 
		ErrorMsg("Bad arguments in 'OXover': use 0< pcross <1");
	ms_SetRandState(21); // resets the generator to 21
	chrom1= ms_IVector(scga.lchrom);
	chrom2= ms_IVector(scga.lchrom);
	halfpop= scga.popsize >> 1;
	for(i= 0; i < halfpop; i++) 
	{
		if(ms_BernRnd(scga.pcross)) 
		{
			mate1= 2*i;
			mate2= 2*i+1;
			xpoint1= PickUp(scga.lchrom-1)+1;
			xpoint2= PickUp(scga.lchrom-1)+1;
			while(xpoint1 == xpoint2)
				xpoint2= PickUp(scga.lchrom-1)+1;
			if(xpoint2 < xpoint1)
				ISWAP(xpoint1, xpoint2);
			// generates genes for child 1
			n=0;
			for(j= xpoint2; j < scga.lchrom; j++) 
			{
				selgene=1;
				chrom1[n]= scga.chrom[mate2][j];
				for(k= xpoint1; k < xpoint2; k++)
					if(chrom1[n] == scga.chrom[mate1][k]) 
					{
						selgene= 0;
						break;
					}
					if(selgene==1) n++;
			}
			for(j= 0; j < xpoint2; j++) 
			{
				selgene=1;
				chrom1[n]= scga.chrom[mate2][j];
				for(k= xpoint1; k < xpoint2; k++)
					if(chrom1[n] == scga.chrom[mate1][k]) 
					{
						selgene= 0;
						break;
					}
					if(selgene==1) n++;
			}

			// generates genes for child 2
			n=0;
			for(j= xpoint2; j < scga.lchrom; j++) 
			{
				selgene=1;
				chrom2[n]= scga.chrom[mate1][j];
				for(k= xpoint1; k < xpoint2; k++)
					if(chrom2[n] == scga.chrom[mate2][k])
					{
						selgene= 0;
						break;
					}
					if(selgene) n++;
			}
			for(j= 0; j < xpoint2; j++) 
			{
				selgene=1;
				chrom2[n]= scga.chrom[mate1][j];
				for(k= xpoint1; k < xpoint2; k++)
					if(chrom2[n] == scga.chrom[mate2][k]) 
					{
						selgene= 0;
						break;
					}
					if(selgene) n++;
			}

			n=0;
			for(j= xpoint2; j < scga.lchrom; j++) 
			{
				scga.chrom[mate1][j]= chrom1[n];
				scga.chrom[mate2][j]= chrom2[n];
				n++;
			}
			for(j= 0; j < xpoint1; j++) 
			{
				scga.chrom[mate1][j]= chrom1[n];
				scga.chrom[mate2][j]= chrom2[n];
				n++;
			}
		}
	}
	ms_Free_IVector(chrom1);
	ms_Free_IVector(chrom2);
	return;
}
//printf("i=%d cpt= %d %d\n",i,xpoint1, xpoint2);
//for(j= 0; j < n; j++) printf("%f \n",chrom1[i]); //
//printf("a=%d %d \n",n,chrom1[n]); //
//for(j= 0; j < n; j++) printf("%d \n",chrom2[j]); //

///////////////////////////////////////////////////////////////////
// Cycle crossover operator
void CXover(SCGAS &scga)
{
	int i,j, gene, firstgene, halfpop, mate1, mate2, *cycle;

	if(scga.pcross<0 || scga.pcross>1) 
		ErrorMsg("Bad arguments in 'CXover': use 0< pcross <1");
	ms_SetRandState(22); // resets the generator to 22
	cycle= ms_IVector(scga.lchrom);
	halfpop= scga.popsize >> 1;
	for(i= 0; i < halfpop; i++) 
	{
		if(ms_BernRnd(scga.pcross)) 
		{
			mate1= 2*i;
			mate2= 2*i+1;
			// finds cycle 
			for(j= 0; j < scga.lchrom; j++)
				cycle[j]= 1;
			firstgene= scga.chrom[mate1][0];
			gene= scga.chrom[mate2][0];
			cycle[0]= 0;

			while(gene != firstgene)
				for(j= 0; j < scga.lchrom; j++)
					if(gene == scga.chrom[mate1][j]) 
					{
						gene= scga.chrom[mate2][j];
						cycle[j]= 0;
						break;
					}
			// exchanges genes not in the cycle 
			for(j= 0; j < scga.lchrom; j++)
				if(cycle[j]) ISWAP(scga.chrom[mate1][j], scga.chrom[mate2][j]);
		}
	}
	ms_Free_IVector(cycle);
	return;
}

//////////////////////////////////////////////////////////////////
// Insertion mutation operator
void InsMut(SCGAS &scga)
{
	int i, j, k, gene, ipoint;

	if(scga.pmutat<0 || scga.pmutat>1)
		ErrorMsg("Bad arguments in 'InsMut': use 0< pmutat <1");
	ms_SetRandState(30); // resets the generator to 30
	for(i= 0; i < scga.popsize; i++) 
	{
		for(j= 0; j < scga.lchrom; j++) 
		{
			if(ms_BernRnd(scga.pmutat)) 
			{
				gene= scga.chrom[i][j];
				ipoint= PickUp(scga.lchrom);
				while(ipoint == j)
					ipoint= PickUp(scga.lchrom);
				if(ipoint > j) 
				{
					for(k= j; k < ipoint; k++)
						scga.chrom[i][k]= scga.chrom[i][k+1];
					scga.chrom[i][ipoint]= gene;
				}
				else 
				{
					for(k= ipoint; k < j; k++)
						scga.chrom[i][j+ipoint-k]= scga.chrom[i][j+ipoint-k-1];
					scga.chrom[i][ipoint]= gene;
				}
			}
		}
	}
	return;
}
//printf("i=%d j=%d ipoint=%d\n",i, j,ipoint);

//////////////////////////////////////////////////////////////////
// Swap mutation operator
void SwapMut(SCGAS &scga)
{
	int i, j, ipoint;

	if(scga.pmutat<0 || scga.pmutat>1)
		ErrorMsg("Bad arguments in 'SwapMut': use 0< pmutat <1");
	ms_SetRandState(31); // resets the generator to 31
	for(i= 0; i < scga.popsize; i++) 
	{
		for(j= 0; j < scga.lchrom; j++) 
		{
			if(ms_BernRnd(scga.pmutat)) 
			{
				ipoint= PickUp(scga.lchrom);
				while(ipoint == j)
					ipoint= PickUp(scga.lchrom);
				ISWAP(scga.chrom[i][j], scga.chrom[i][ipoint]);
			}
		}
	}
}
//printf("%d i=%d j=%d ipoint=%d \n",gen, i, j, ipoint);


//////////////////////////////////////////////////////////////////
// Inversion operator
void Invers(SCGAS &scga)
{
	int i, j, n, xpoint1, xpoint2;

	if(scga.pmutat<0 || scga.pmutat>1)
		ErrorMsg("Bad arguments in 'Invers': use 0< pmutat <1");
	ms_SetRandState(32); // resets the generator to 32
	for(i= 0; i < scga.popsize; i++) 
	{
		if(ms_BernRnd(scga.pmutat)) 
		{
			xpoint1= PickUp(scga.lchrom);
			xpoint2= PickUp(scga.lchrom);
			while(xpoint1 == xpoint2)
				xpoint2= PickUp(scga.lchrom);
			if(xpoint2 < xpoint1)
				ISWAP(xpoint1, xpoint2);
			n= (int)((xpoint2-xpoint1+1)/2);
			for(j= 0; j < n; j++)
				ISWAP(scga.chrom[i][xpoint1+j], scga.chrom[i][xpoint2-j]);
		}
	}
}
//printf("***i=%d cpt=%d %d n=%d\n",i, xpoint1, xpoint2,n);
//printf("i=%d j=%d\n",i,j);
//printf("i=%d j=%d %f\n",i, j, range);


//////////////////////////////////////////////////////////////////
// Elitism operator(If the elite is destroyed, it replaces 
// the worst one in the new population 
void Elitism(SCGAS &scga)
{
	int j, nmin, nmax;
	REAL objmin, objmax;

	if(scga.gen < 1) return;
	objmin= ms_VMin(scga.obj, scga.popsize, nmin);
	objmax= ms_VMax(scga.obj, scga.popsize, nmax);
	if(scga.maxmin == 1) 
	{
		if(objmax < scga.bestobj) 
		{
			scga.obj[nmin]= scga.bestobj;
			for(j= 0; j < scga.lchrom; j++)
				scga.chrom[nmin][j]= scga.bestchrom[j];
		}
	}
	else 
	{
		if(objmin > scga.bestobj) 
		{
			scga.obj[nmax]= scga.bestobj;
			for(j= 0; j < scga.lchrom; j++)
				scga.chrom[nmax][j]= scga.bestchrom[j];
		}
	}
	return;
}
//printf("%d %d %f %f\n",nmin, nmax, objmin, objmax);
//printf("%f %f\n",objmin,bestobj);

//////////////////////////////////////////////////////////////////
// Selets a population using the remainder method 
void Select(SCGAS &scga, int *idxchrom)
{
	int i, j, n, nsel, npick;
	int **newchrom;

	newchrom= ms_IMatrix(scga.popsize, scga.lchrom);
	n= scga.popsize;
	ms_SetRandState(1); // resets the generator to 1
	for(i= 0; i < scga.popsize; i++)
	{
		npick= PickUp(n);
		nsel= idxchrom[npick];
		for(j= 0; j < scga.lchrom; j++)
			newchrom[i][j]= scga.chrom[nsel][j];
		idxchrom[npick]=idxchrom[n-1];
		n--;
	}
	for(i= 0; i < scga.popsize; i++)
		for(j= 0; j < scga.lchrom; j++)
			scga.chrom[i][j]= newchrom[i][j];
	ms_Free_IMatrix(newchrom);
	return;
}
//printf("%d %d %d\n",n, npick, nsel);
