


#include "samotif.h"
#include "dlgmotif.h"


class CDlgMakeSvSys: public CDlgMotif
{

public:
	CDlgMakeSvSys();
	~CDlgMakeSvSys();

	bool Create(Widget parent, char sTitle[]);

	char m_sCMPFile[300];
	char m_sSvSysFile[300];
	int OnOK(void);

protected:
	static char * m_sLabel[];
	int m_nWidgetEdit[10];
	
	char m_FileSavingPar[200];

	bool SaveValue();
	bool SetInitValue();


};
