
#include "samotif.h"
#include <Xm/TextF.h>
#include "dlgcalc.h"
#include "FHGlobal.h"

char * CDlgCalc::m_sLabel[] = {
	                        "                     Static Range:",
							"               Most Loop Quantity:",
							"Per How Many Loops to Save Static:",
							"                         CMP File:",
							"               Survey System File:",
							"File to Initiate Static(Blank OK):",
							"              File to Save Static:",
							"               File to Save Power:"};


#include "filedialog.h"
CFileOpenPar DlgCalcFileOpenPar[9];

CDlgCalc::CDlgCalc()
{
}

CDlgCalc::~CDlgCalc()
{
}

bool CDlgCalc::Create(Widget parent,char *sTitle)
{
	Widget pane,form,label,widget,thispane;
	Arg args[10];
	int i;

	int nFractionBase=10;

	strcpy(m_sFileLastSave,"dlgcalc.txt");

	DlgCalcFileOpenPar[3].m_bForReading=true;
	DlgCalcFileOpenPar[4].m_bForReading=true;
	DlgCalcFileOpenPar[5].m_bForReading=true;
	DlgCalcFileOpenPar[6].m_bForReading=false;
	DlgCalcFileOpenPar[7].m_bForReading=false;

	AreaItem action_items[] = { 
		{ "    ", NULL, NULL },
		{ "    ", NULL, NULL }, 
		{ "    ", NULL, NULL }, 
		{ "...", CFileDialog::GetAndSetFileName, (void*)(&DlgCalcFileOpenPar[3])},
		{ "...", CFileDialog::GetAndSetFileName, (void*)(&DlgCalcFileOpenPar[4])},
		{ "...", CFileDialog::GetAndSetFileName, (void*)(&DlgCalcFileOpenPar[5])},
		{ "...", CFileDialog::GetAndSetFileName, (void*)(&DlgCalcFileOpenPar[6])},
		{ "...", CFileDialog::GetAndSetFileName, (void*)(&DlgCalcFileOpenPar[7])},		
	};

	

	if(!CDlgMotif::Create(parent, sTitle))return false;
	form=this->GetControlForm();
	if(form==Widget(0))return false;

	/////////////////////////////////////////////////////////////////////////
	//
	XtSetArg (args[0], XmNsashWidth, 1);
	XtSetArg (args[1], XmNsashHeight, 1);	
	XtSetArg (args[2], XmNfractionBase,12);
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
					   XmNleftPosition,5, 
					   XmNrightAttachment, XmATTACH_POSITION, 
					   XmNrightPosition,8, 
					   XmNshowAsDefault, False,
					   XmNdefaultButtonShadowThickness, 1,
					   NULL);
		XtManageChild (widget);
		m_nWidgetEdit[i]=(int)widget;
		DlgCalcFileOpenPar[i].m_widgetEdit =widget;
		
		/////////////////////////////////////////////////////////////////////////
		// Create the file open button to set file names:
		if(i>2)
		{			
			widget = XmCreatePushButtonGadget (form, action_items[i].label , NULL, 0);			
			XtVaSetValues (widget, XmNtopAttachment, XmATTACH_FORM, 
							XmNbottomAttachment, XmATTACH_FORM,        
							XmNleftAttachment, XmATTACH_POSITION,        
							XmNleftPosition,8, 
							XmNrightAttachment, XmATTACH_POSITION, 
							XmNrightPosition,9, 
							XmNshowAsDefault, False,
							XmNdefaultButtonShadowThickness, 1,
							NULL);
			XtManageChild (widget);

			XtAddCallback (widget, XmNactivateCallback, action_items[i].callback, &DlgCalcFileOpenPar[i]);
		};
		   
		XtManageChild (form);
	}
	
	SetIniValue();

	XtManageChild (thispane);
}

int CDlgCalc::OnOK(void)
{
	sscanf(XmTextFieldGetString((Widget)m_nWidgetEdit[0]),"%d",&m_nStaticRange);
	sscanf(XmTextFieldGetString((Widget)m_nWidgetEdit[1]),"%d",&m_nMaxLoopQuantity);
	sscanf(XmTextFieldGetString((Widget)m_nWidgetEdit[2]),"%d",&m_nLoopToSaveStatic);
	strcpy(m_sFileCMP ,XmTextFieldGetString((Widget)m_nWidgetEdit[3]));
	strcpy(m_sFileSvSys ,XmTextFieldGetString((Widget)m_nWidgetEdit[4]));
	strcpy(m_sFileInitStatic ,XmTextFieldGetString((Widget)m_nWidgetEdit[5]));
	strcpy(m_sFileStatic ,XmTextFieldGetString((Widget)m_nWidgetEdit[6]));
	strcpy(m_sFilePower ,XmTextFieldGetString((Widget)m_nWidgetEdit[7]));
	
	SaveIniValue();
	
	return IDOK;
}

bool CDlgCalc::SetIniValue()
{
	if(m_nWidgetEdit[0]==0)
	{
		return false;
	}

	FILE *fp=fopen(m_sFileLastSave,"rt");
	if(fp){
		GetLineData(fp,m_nStaticRange );
		GetLineData(fp,m_nMaxLoopQuantity);
		GetLineData(fp,m_nLoopToSaveStatic );
		
		GetLineData(fp,m_sFileCMP );
		GetLineData(fp,m_sFileSvSys);
		GetLineData(fp,m_sFileInitStatic );
		GetLineData(fp,m_sFileStatic);
		GetLineData(fp,m_sFilePower );
		fclose(fp);
	}
	else
	{
		m_nStaticRange=60;
		m_nMaxLoopQuantity=1000;
		m_nLoopToSaveStatic =50;
		strcpy(m_sFileCMP,"sample.cmp");		
		strcpy(m_sFileSvSys,"sample.sys");
		strcpy(m_sFileInitStatic,"blank.t");
		strcpy(m_sFileStatic,"sample.t");
		strcpy(m_sFilePower,"power.txt");
	}

	////////////////////////////////
	// Set the value of the widget:
	char s[300];
	sprintf(s,"%ld",m_nStaticRange);
	XmTextFieldSetString((Widget)m_nWidgetEdit[0], s);
	sprintf(s,"%ld",m_nMaxLoopQuantity);
	XmTextFieldSetString((Widget)m_nWidgetEdit[1], s);
	sprintf(s,"%ld",m_nLoopToSaveStatic);
	XmTextFieldSetString((Widget)m_nWidgetEdit[2], s);

	XmTextFieldSetString((Widget)m_nWidgetEdit[3], m_sFileCMP);
	XmTextFieldSetString((Widget)m_nWidgetEdit[4], m_sFileSvSys);
	XmTextFieldSetString((Widget)m_nWidgetEdit[5], m_sFileInitStatic);
	XmTextFieldSetString((Widget)m_nWidgetEdit[6], m_sFileStatic);
	XmTextFieldSetString((Widget)m_nWidgetEdit[7], m_sFilePower);

	return true;
}


bool CDlgCalc::SaveIniValue()
{
	FILE *fp=fopen(m_sFileLastSave,"wt");
	if(!fp)
	{
		printf("No Calculation Initiate file.\n");
		return false;
	}

	fprintf(fp,"%ld\n",m_nStaticRange );
	fprintf(fp,"%ld\n",m_nMaxLoopQuantity);
	fprintf(fp,"%ld\n",m_nLoopToSaveStatic );
	fprintf(fp,"%s\n", m_sFileCMP );
	fprintf(fp,"%s\n", m_sFileSvSys);
	fprintf(fp,"%s\n", m_sFileInitStatic );
	fprintf(fp,"%s\n", m_sFileStatic);
	fprintf(fp,"%s\n", m_sFilePower );
	fclose(fp);
	
	return true;
}









