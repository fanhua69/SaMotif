

#ifndef FH_dlgcalc_tag
#define FH_dlgcalc_tag

#include "dlgmotif.h"

class CDlgCalc:public CDlgMotif
{
public:
	CDlgCalc();
	~CDlgCalc();

	bool Create(Widget parent,char *sTitle);

	int m_nStaticRange;
	int m_nMaxLoopQuantity;
	int m_nLoopToSaveStatic;
	
	char m_sFileCMP[500];
	char m_sFileSvSys[500];
	char m_sFileInitStatic[500];
	char m_sFileStatic[500];
	char m_sFilePower[500];


protected:
	static char * m_sLabel[];
	int m_nWidgetEdit[10];

	char m_sFileLastSave[300];
	bool SetIniValue();
	bool SaveIniValue();


public:
	virtual int OnOK(void);
};

#endif

