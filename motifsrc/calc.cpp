

#include "calc.h"
#include "StocConj.h"


bool Calc(int nStaticRange,
		  int nMaxLoopQuantity,
		  int nLoopToSave,
		  char sFileCMP[],
		  char sFileSvSys[],
		  char sFileInitStatic[],
		  char sFileStatic[],
		  char sFilePower[])
{
	
	///////////////////////////////////////////////////
	// This is a color egg for calculation method:
	int n;
	enumPowerMethod method=POWER;
	Warn("Trying to load method.txt...");
	FILE *fp=fopen("method.txt","rt");
	if(fp)
	{		
		fscanf(fp,"%d\n",&n);
		if(n==2)
		{
			method=CORRELATION;
			Warn("file method.txt Found, use correclation method to calculate static.");
		}
		fclose(fp);
	}	
	else
	{
		Warn("file method.txt not found, use power method to calculate static.");
	}

	///////////////////////////////////////////////////
	// Initiate:
	CStocConj sto;
	if(!sto.Initiate(
			nStaticRange,
			nMaxLoopQuantity,
			nLoopToSave,
			sFileCMP,
			sFileSvSys,
			sFileInitStatic,
			sFileStatic,
			sFilePower,
			method))
	{
		Warn("Error: when initiating the parameters for calculation!\n");
		return false;
	}

	return  sto.Calculate ();
}
