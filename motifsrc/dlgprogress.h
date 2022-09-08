

#ifndef SA_DLG_PROGRESS_TAG
#define SA_DLG_PROGRESS_TAG


#include "samotif.h"

class CDlgProgress
{
public:
	CDlgProgress();
	~CDlgProgress();


	bool Create(double dLow, double dHigh);
	bool Show(char sStatus[]);
	
	void SetPos(double dPos);
	void Over();
	
protected:
	double m_dLow;
	double m_dHigh;
	
	int m_nPosLow;
	int m_nPosHigh;
	int m_nPosCurrent;

	double m_dCooe;
	
public:
	void Reset(void);
};

#endif
