

#include "dlgprogress.h"
#include "stdio.h"
#include "stdlib.h"

CDlgProgress::CDlgProgress()
{
	m_dLow=0;
	m_dHigh=100;
	
	m_nPosLow=0;
	m_nPosHigh=50;
	m_nPosCurrent=0;
	m_dCooe=0.0;

}
CDlgProgress::~CDlgProgress()
{
}
bool CDlgProgress::Create(double dLow, double dHigh)
{
	m_dLow=dLow;
	m_dHigh=dHigh;
	m_dCooe=(m_nPosHigh-m_nPosLow)/(m_dHigh-m_dLow);
	return true;
}

bool CDlgProgress::Show(char sStatus[])
{
	printf("%s\n",sStatus);
	char s[310];
	memset(s,61,m_nPosHigh);  // 61: "="
	memset(&s[m_nPosHigh+1],0,1);
	printf("%s\n",s);
	return true;
}
	
void CDlgProgress::SetPos(double dPos)
{
	if(dPos<m_dLow||dPos>m_dHigh)return;
	int nPos=(dPos-m_dLow)*m_dCooe;
	if(nPos<=m_nPosCurrent)return;
	int i;
	
	int nStarQty=nPos-m_nPosCurrent;
	if(nStarQty<1)return;

	for(i=0;i<nStarQty;i++)
	{
		printf("*");
	}
	fflush(stdout);
	m_nPosCurrent=nPos;
}	

void CDlgProgress::Over()
{
	int i;
	for(i=0;i<(m_nPosHigh-m_nPosCurrent);i++)
	{
		printf("*");
	}
	m_nPosCurrent=m_nPosHigh;
	printf("\nOver!\n\n");
}	

void CDlgProgress::Reset()
{
	printf("\n");
	m_nPosCurrent=m_nPosLow;	
}