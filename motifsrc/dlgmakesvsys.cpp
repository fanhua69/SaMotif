

#include "dlgmakesvsys.h"
#include "dlgmotif.h"
#include <Xm/TextF.h>
#include "filedialog.h"
#include "FHGlobal.h"


char * CDlgMakeSvSys::m_sLabel[] = {
	                   "             CMP Source File:", 
                       "Target Survey System File:" };


CDlgMakeSvSys::CDlgMakeSvSys()
{
}

CDlgMakeSvSys::~CDlgMakeSvSys()
{
}

CFileOpenPar DlgMkSvSysFileOpenPar[2];

bool CDlgMakeSvSys::Create(Widget parent, char sTitle[])
{
	Widget pane,form,label,widget,thispane;
	Arg args[10];
	int i;
	int nFractionBase=10;

	strcpy(m_FileSavingPar,"dlgmakesvsys.txt");

	if(!CDlgMotif::Create(parent, sTitle))return false;
	form=this->GetControlForm();
	if(form==Widget(0))return false;

	/////////////////////////////////////////////////////////////////////////
	//
	XtSetArg (args[0], XmNsashWidth, 1);
	XtSetArg (args[1], XmNsashHeight, 1);	
	XtSetArg (args[2], XmNfractionBase,nFractionBase );
	thispane= XmCreatePanedWindow(form, "form2", args, 3);

	for(i=0;i<XtNumber(m_sLabel);i++)
	{
		XtSetArg (args[0], XmNfractionBase, nFractionBase);
		form=XmCreateForm(thispane,"form",args,1);

		
		label = XmCreateLabelGadget (form,m_sLabel[i],NULL, 0); 
			
		XtVaSetValues (form, XmNtopAttachment, XmATTACH_FORM, 
					   XmNbottomAttachment, XmATTACH_FORM,        
					   XmNleftAttachment, XmATTACH_POSITION,        
					   XmNleftPosition, 1, 
					   XmNrightAttachment, XmATTACH_POSITION, 
					   XmNrightPosition, 5, 
					   XmNshowAsDefault, False,
					   XmNdefaultButtonShadowThickness, 1,
					   NULL);
		XtManageChild (label);
		
		
		widget=XmCreateTextField (form, "edit", NULL, 0);
		XtVaSetValues (widget , XmNtopAttachment, XmATTACH_FORM, 
					   XmNbottomAttachment, XmATTACH_FORM,        
					   XmNleftAttachment, XmATTACH_POSITION,        
					   XmNleftPosition, 5, 
					   XmNrightAttachment, XmATTACH_POSITION, 
					   XmNrightPosition, 8, 
					   XmNshowAsDefault, False,
					   XmNdefaultButtonShadowThickness, 1,
					   NULL);
		XtManageChild (widget);
		m_nWidgetEdit[i]=(int)widget;
		
		
		widget = XmCreatePushButtonGadget (form, "...", NULL, 0);
		XtVaSetValues (widget, XmNtopAttachment, XmATTACH_FORM, 
						XmNbottomAttachment, XmATTACH_FORM,        
						XmNleftAttachment, XmATTACH_POSITION,        
						XmNleftPosition, 8, 
						XmNrightAttachment, XmATTACH_POSITION, 
						XmNrightPosition, 9, 
						XmNshowAsDefault, False,
						XmNdefaultButtonShadowThickness, 1,
						NULL);
		XtManageChild (widget);
		
		DlgMkSvSysFileOpenPar[i].m_widgetEdit =(Widget)m_nWidgetEdit[i];

		if(i==0)
		{
			DlgMkSvSysFileOpenPar[i].m_bForReading =true;
		}
		else
		{
			DlgMkSvSysFileOpenPar[i].m_bForReading =false;
		}

		XtAddCallback (widget, XmNactivateCallback, CFileDialog::GetAndSetFileName, XtPointer(&DlgMkSvSysFileOpenPar[i]));

		XtManageChild (form);
	}

	SetInitValue();

	XtManageChild (thispane);
}




int CDlgMakeSvSys::OnOK(void)
{
	strcpy(m_sCMPFile,XmTextFieldGetString((Widget)m_nWidgetEdit[0]));
	strcpy(m_sSvSysFile,XmTextFieldGetString((Widget)m_nWidgetEdit[1]));
	
	SaveValue();
	return IDOK;
}


bool CDlgMakeSvSys::SetInitValue()
{
	if(m_nWidgetEdit[0]==0)
	{
		return false;
	}

	FILE *fp=fopen(m_FileSavingPar,"rt");
	if(fp)
	{
		GetLineData(fp,m_sCMPFile );
		GetLineData(fp,m_sSvSysFile);
		fclose(fp);
	}
	else
	{
		strcpy(m_sCMPFile,"sample.cmp");
		strcpy(m_sSvSysFile,"sample.sys");
	}

	////////////////////////////////
	// Set the value of the widget:	
	XmTextFieldSetString((Widget)m_nWidgetEdit[0], m_sCMPFile);
	XmTextFieldSetString((Widget)m_nWidgetEdit[1], m_sSvSysFile);
	
	return true;
}


bool CDlgMakeSvSys::SaveValue()
{
	FILE *fp=fopen(m_FileSavingPar,"wt");
	if(!fp)
	{
		printf("No Calculation Initiate file.\n");
		return false;
	}

	fprintf(fp,"%s\n",m_sCMPFile );
	fprintf(fp,"%s\n",m_sSvSysFile);
	fclose(fp);
	
	return true;
}
