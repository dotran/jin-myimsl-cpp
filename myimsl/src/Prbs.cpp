/////////////////////////////////////////////////////////////////////////
// Program  : prbs.cpp
// Coded by : Prof. Gang-Gyoo Jin, Korea Maritime University 
// Coded on : 12/12/2003

/////////////////////////////////////////////////////////////////////////
// generate an integer random bit
#define IB1 1
#define IB2 2
#define IB5 16
#define IB18 131072
#define MASK (IB1+IB2+IB5)
int ms_Prbs(long &seed)
{
	if(seed & IB18) 
	{
		seed=((seed ^ MASK) << 1) | IB1;
		return 1;
	} 
	else 
	{
		seed <<= 1;
		return 0;
	}
}
#undef MASK
#undef IB18
#undef IB5
#undef IB2
#undef IB1