
#ifndef CMPDRAWPART_TAG
#define CMPDRAWPART_TAG

#include "dlgmotif.h"

class CDlgDrawPartCMP: public CDlgMotif
{
public:
	CDlgDrawPartCMP();
	~CDlgDrawPartCMP();

	virtual bool Create(Widget parent,char sDlgTitle[]);

public:
	char m_sCMPSrcFileName[500];
	char m_sCMPTarFileName[500];
	long m_nCMPFrom;
	long m_nCMPTo;
	long m_nTimeFrom;    /* ms */
	long m_nTimeTo;		 /* ms */

protected:
	
	static char *CMP_Draw_Labels[];
	static char *CMP_Draw_EditNames[];

	int m_nWidgetEdit[6];

	int m_nbuttonCMPSrcFile;
	int m_nbuttonCMPTarFile;


	char m_FileSavingPar[200];

	bool SetInitValue();
	bool SaveValue();




public:
	virtual int OnOK(void);
};

#endif







