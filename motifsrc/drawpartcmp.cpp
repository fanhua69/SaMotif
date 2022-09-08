
#include "samotif.h"
#include "drawpartcmp.h"
#include "CMPFile.h"

/*****************************************************************
*  Function Name: DrawPartCMP
*  Function: Show Dialog to Get Pars For Drawing out Part of CMP.
*
*
*
******************************************************************/
bool DrawPartCMP(char sCMPFileSrc[], 
				 char sCMPFileTar[],
				 int nCMPFrom, 
				 int nCMPTo, 
				 int nTimeFrom, 
				 int nTimeTo)
{	
	CCMPFile fileIn;
	if(!fileIn.OpenCMPFile (sCMPFileSrc))
	{
		char s[200];
		sprintf(s,"Can not open CMP file:%s\n",sCMPFileSrc);
		Warn(s);
		return false;
	}
	
	/////////////////////////////////////////
	//
	return fileIn.DrawOutPartCMP (sCMPFileTar,nCMPFrom,nCMPTo,nTimeFrom,nTimeTo);
}
