
#include "dlgmakesvsys.h"
#include "makesvsys.h"
#include "cmpannealdoc.h"
#include "FHString.h"


bool MakeSvSys(char sCMPFile[], char sSvSysFile[])
{
	CCMPAnnealDoc doc;
	if(!doc.OpenCMPFile (sCMPFile,"cdp"))
	{
		CFHString s="Error:when opening the CMP file:";
		s+=sCMPFile;
		Warn(s.GetPointer ());
		return false;
	}

	return doc.MakeSurveySystem (sSvSysFile);
}
