

#include "samotif.h"
#include "dlgdrawpartcmp.h"
#include "filedialog.h"
#include "FHGlobal.h"

char * CDlgDrawPartCMP::CMP_Draw_Labels[] = {
	                   "CMP Source File:", 
                       "CMP Target File:", 
					   "       CMP From:", 
					   "       CMP   To:",
					   "  Time From(ms):",
					   "  Time   To(ms):"};

char * CDlgDrawPartCMP::CMP_Draw_EditNames[] = {
	                    "CMP_Src_File", 
                       "CMP_Tar_File", 
					   "CMP_From", 
					   "CMP_To",
					   "Time_From",
					   "Time_To"};

#include <Xm/TextF.h>

CFileOpenPar DlgDrawPartCMPFileOpenPar[2];			

CDlgDrawPartCMP::CDlgDrawPartCMP()
{
	
}

CDlgDrawPartCMP::~CDlgDrawPartCMP()
{
}

bool CDlgDrawPartCMP::Create(Widget parent,char sDlgTitle[])
{	
	Widget    pane, form, label,widget,thispane;
	Arg       args[10];
	int       i;
	int nFractionBase=8;
	bool bForReading;



	strcpy(m_FileSavingPar,"dlgdrawpartcmp.txt");

	if(!CDlgMotif::Create(parent,sDlgTitle))return false;

	
	pane=GetControlForm (); 
	if(pane==(Widget)0)return false;


	XtSetArg (args[0], XmNsashWidth, 1);
	XtSetArg (args[1], XmNsashHeight, 1);	
	XtSetArg (args[2], XmNfractionBase,nFractionBase );
	thispane= XmCreatePanedWindow(pane, "form2", args, 3);


	long nn=XtNumber(CMP_Draw_Labels);
	printf("XtNumber:%ld",nn);



	for(i=0;i<XtNumber(CMP_Draw_Labels);i++)
	{

		XtSetArg (args[0], XmNfractionBase, nFractionBase);
		form=XmCreateForm(thispane,"form",args,1);

		
		label = XmCreateLabelGadget (form,CMP_Draw_Labels[i],NULL, 0); 
			
		XtVaSetValues (form, XmNtopAttachment, XmATTACH_FORM, 
					   XmNbottomAttachment, XmATTACH_FORM,        
					   XmNleftAttachment, XmATTACH_POSITION,        
					   XmNleftPosition, 1, 
					   XmNrightAttachment, XmATTACH_POSITION, 
					   XmNrightPosition, 3, 
					   XmNshowAsDefault, False,
					   XmNdefaultButtonShadowThickness, 1,
					   NULL);
		XtManageChild (label);
		
		
		widget=XmCreateTextField (form, CMP_Draw_EditNames[i], NULL, 0);
		XtVaSetValues (widget , XmNtopAttachment, XmATTACH_FORM, 
					   XmNbottomAttachment, XmATTACH_FORM,        
					   XmNleftAttachment, XmATTACH_POSITION,        
					   XmNleftPosition, 3, 
					   XmNrightAttachment, XmATTACH_POSITION, 
					   XmNrightPosition, 6, 
					   XmNshowAsDefault, False,
					   XmNdefaultButtonShadowThickness, 1,
					   NULL);
		XtManageChild (widget);
		m_nWidgetEdit[i]=(int)widget;
		
		
		
		if(i==0)
		{
			widget = XmCreatePushButtonGadget (form, "...", NULL, 0);
			XtVaSetValues (widget, XmNtopAttachment, XmATTACH_FORM, 
						   XmNbottomAttachment, XmATTACH_FORM,        
						   XmNleftAttachment, XmATTACH_POSITION,        
						   XmNleftPosition, 6, 
						   XmNrightAttachment, XmATTACH_POSITION, 
						   XmNrightPosition, 7, 
						   XmNshowAsDefault, False,
						   XmNdefaultButtonShadowThickness, 1,
						   NULL);
			XtManageChild (widget);
			
			DlgDrawPartCMPFileOpenPar[0].m_bForReading =true;
			DlgDrawPartCMPFileOpenPar[0].m_widgetEdit =(Widget)m_nWidgetEdit[0];
			XtAddCallback (widget, XmNactivateCallback, CFileDialog::GetAndSetFileName, (void*)(&DlgDrawPartCMPFileOpenPar[0]));
		} 
		   
		else if(i==1)
		{
			widget = XmCreatePushButtonGadget (form, "...", NULL, 0);
			XtVaSetValues (widget , XmNtopAttachment, XmATTACH_FORM, 
						   XmNbottomAttachment, XmATTACH_FORM,        
						   XmNleftAttachment, XmATTACH_POSITION,        
						   XmNleftPosition, 6, 
						   XmNrightAttachment, XmATTACH_POSITION, 
						   XmNrightPosition, 7, 
						   XmNshowAsDefault, False,
						   XmNdefaultButtonShadowThickness, 1,
						   NULL);
			XtManageChild (widget );

			DlgDrawPartCMPFileOpenPar[1].m_bForReading =false;
			DlgDrawPartCMPFileOpenPar[1].m_widgetEdit =(Widget)m_nWidgetEdit[1];			
			XtAddCallback (widget, XmNactivateCallback, CFileDialog::GetAndSetFileName, (void*)(&DlgDrawPartCMPFileOpenPar[1]));	
		} 			
		 
		else
		{
			label = XmCreateLabelGadget (form,CMP_Draw_Labels[i],NULL, 0); 
				
			XtVaSetValues (form, XmNtopAttachment, XmATTACH_FORM, 
						   XmNbottomAttachment, XmATTACH_FORM,        
						   XmNleftAttachment, XmATTACH_POSITION,        
						   XmNleftPosition, 6, 
						   XmNrightAttachment, XmATTACH_POSITION, 
						   XmNrightPosition, 7, 
						   XmNshowAsDefault, False,
						   XmNdefaultButtonShadowThickness, 1,
						   NULL);
			XtManageChild (label);

		}
		
		
		XtManageChild (form);
	}

	SetInitValue();

	XtManageChild (thispane);	
	
	return true;
}

int CDlgDrawPartCMP::OnOK(void)
{
	strcpy(m_sCMPSrcFileName ,XmTextFieldGetString((Widget)m_nWidgetEdit[0]));
	strcpy(m_sCMPTarFileName ,XmTextFieldGetString((Widget)m_nWidgetEdit[1]));
	sscanf(XmTextFieldGetString((Widget)m_nWidgetEdit[2]),"%d",&m_nCMPFrom);
	sscanf(XmTextFieldGetString((Widget)m_nWidgetEdit[3]),"%d",&m_nCMPTo);
	sscanf(XmTextFieldGetString((Widget)m_nWidgetEdit[4]),"%d",&m_nTimeFrom);
	sscanf(XmTextFieldGetString((Widget)m_nWidgetEdit[5]),"%d",&m_nTimeTo);

	SaveValue();
	return IDOK;
}

bool CDlgDrawPartCMP::SetInitValue()
{
	if(m_nWidgetEdit[0]==0)
	{
		return false;
	}

	FILE *fp=fopen(m_FileSavingPar,"rt");
	if(fp)
	{
		GetLineData(fp,m_sCMPSrcFileName );
		GetLineData(fp,m_sCMPTarFileName);
		GetLineData(fp,m_nCMPFrom );		
		GetLineData(fp,m_nCMPTo );
		GetLineData(fp,m_nTimeFrom);
		GetLineData(fp,m_nTimeTo );
		fclose(fp);
	}
	else
	{
		strcpy(m_sCMPSrcFileName,"sample.cmp");
		strcpy(m_sCMPTarFileName,"part.cmp");
		m_nCMPFrom =10 ;		
		m_nCMPTo   =15 ; 
		m_nTimeFrom=2000;
		m_nTimeTo=4000;
	}

	////////////////////////////////
	// Set the value of the widget:
	
	XmTextFieldSetString((Widget)m_nWidgetEdit[0], m_sCMPSrcFileName);
	XmTextFieldSetString((Widget)m_nWidgetEdit[1], m_sCMPTarFileName);
	
	char s[300];
	sprintf(s,"%ld",m_nCMPFrom);
	XmTextFieldSetString((Widget)m_nWidgetEdit[2], s);
	sprintf(s,"%ld",m_nCMPTo);
	XmTextFieldSetString((Widget)m_nWidgetEdit[3], s);
	sprintf(s,"%ld",m_nTimeFrom);
	XmTextFieldSetString((Widget)m_nWidgetEdit[4], s);
	sprintf(s,"%ld",m_nTimeTo);
	XmTextFieldSetString((Widget)m_nWidgetEdit[5], s);

	return true;
}


bool CDlgDrawPartCMP::SaveValue()
{
	FILE *fp=fopen(m_FileSavingPar,"wt");
	if(!fp)
	{
		printf("No Calculation Initiate file.\n");
		return false;
	}

	fprintf(fp,"%s\n",m_sCMPSrcFileName );
	fprintf(fp,"%s\n",m_sCMPTarFileName);
	fprintf(fp,"%ld\n",m_nCMPFrom );
	fprintf(fp,"%ld\n", m_nCMPTo );
	fprintf(fp,"%ld\n", m_nTimeFrom);
	fprintf(fp,"%ld\n", m_nTimeTo );
	fclose(fp);
	
	return true;
}
