


#include "samotif.h"
#include "dlgmotif.h"

extern XtAppContext app;

CDlgMotif::CDlgMotif()
{
	m_nWidgetShell=654321;
	m_nWidgetDlg=0;
	m_nWidgetParent= 0;
	m_nFormControl = 0;
	m_nFormAction  = 0;

	m_nModalResult=NULL;
}

bool CDlgMotif::Create(Widget parent,char sDlgTitle[])
{
	Widget    pane, form, widget,board;
	Arg       args[10];
	int i;
	Dimension h;
	int nFractionBase=8;

	if(parent==(Widget)0)return false;

	// create bulletinboard and the pane 
	i = 0;
	XtSetArg (args[i], XmNdeleteResponse, XmDESTROY); i++;	
	widget= XmCreateDialogShell (GetTopShell(parent), sDlgTitle, args, i);
	board= XmCreateBulletinBoard (widget, "board", args, i);
	m_nWidgetParent=(int)parent;
	m_nWidgetShell=(int)widget;
	m_nWidgetDlg =(int)board;

	/* Create a PanedWindow to manage the stuff in this dialog. */
	XtSetArg (args[0], XmNsashWidth, 1);
	XtSetArg (args[1], XmNsashHeight, 1);	
	pane = XmCreatePanedWindow (board, "pane", args, 2);

	// Create Two forms for Drawing and action:
	XtSetArg (args[0], XmNfractionBase, nFractionBase);
	
	m_nFormControl = (int)XmCreateForm (pane, "ControlForm", args, 1);
	XtManageChild ((Widget)m_nFormControl);

	m_nFormAction  = (int)XmCreateForm (pane, "ActionForm" , args, 1);
	XtManageChild ((Widget)m_nFormAction);


	/* Create OK and Cancel button */
	widget = XmCreatePushButtonGadget ((Widget)m_nFormAction, "OK", NULL, 0);
			
	XtVaSetValues (widget, XmNtopAttachment, XmATTACH_FORM, 
			       XmNbottomAttachment, XmATTACH_FORM,        
			       XmNleftAttachment, XmATTACH_POSITION,        
			       XmNleftPosition, 3, 
			       XmNrightAttachment, XmATTACH_POSITION, 
			       XmNrightPosition, 4, 
			       XmNshowAsDefault, True,
			       XmNdefaultButtonShadowThickness, 1,
			       NULL);
	XtManageChild (widget);
	XtAddCallback (widget, XmNactivateCallback, CDlgMotif::OKButtonPushed,(void*)this);
	
	widget = XmCreatePushButtonGadget ((Widget)m_nFormAction  , "Cancel", NULL, 0);
	XtVaSetValues (widget, XmNsensitive, True, 
			       XmNtopAttachment, XmATTACH_FORM,
			       XmNbottomAttachment, XmATTACH_FORM,
			       XmNleftAttachment, XmATTACH_POSITION,
			       XmNleftPosition, 5,
			       XmNrightAttachment, XmATTACH_POSITION,
			       XmNrightPosition, 6,
			       XmNshowAsDefault, False,
			       XmNdefaultButtonShadowThickness, 1, 
			       NULL);
	XtManageChild (widget);
	XtAddCallback (widget, XmNactivateCallback, CDlgMotif::CancelButtonPushed, this);

	/* Fix the action area pane to its current height -- never let it resize */
	XtVaGetValues (widget, XmNheight, &h, NULL);
	XtVaSetValues ((Widget)m_nFormAction, XmNpaneMaximum, h, XmNpaneMinimum, h, NULL);

	XtManageChild ((Widget)m_nFormAction);
	XtManageChild (pane);

	return true;
}

Widget CDlgMotif::GetControlForm()
{
	return (Widget)m_nFormControl;
}

Widget CDlgMotif::GetActionForm()
{
	return (Widget)m_nFormAction;
}

Widget CDlgMotif::GetParent()
{
	return (Widget)m_nWidgetParent;
}

Widget CDlgMotif::GetDlg()
{
	return (Widget)m_nWidgetDlg;
}

int CDlgMotif::DoModal()
{
	if(m_nWidgetDlg==0)return 0;

	Widget dialog=(Widget)m_nWidgetDlg;
	Widget parent=(Widget)m_nWidgetParent;

	XtVaSetValues (dialog, XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL, NULL);
	XtManageChild (dialog);

	while (m_nModalResult == 0)        
	{
		XtAppProcessEvent (app, XtIMAll);  
	}

	XtUnmanageChild (dialog);   
	
	/* make sure the dialog goes away before returning. Sync with server     
	** and update the display.     
	*/    
	
	XSync (XtDisplay (dialog), 0);   
	XmUpdateDisplay (parent);    

	return m_nModalResult;

}

int CDlgMotif::OnOK()
{
	return IDOK;
}

int CDlgMotif::OnCancel()
{
	return IDCANCEL;
}

int CDlgMotif::Show()
{
	if(m_nWidgetDlg==0)return 0;

	XtVaSetValues ((Widget)m_nWidgetDlg, XmNdialogStyle, XmDIALOG_MODELESS, NULL);
	XtManageChild ((Widget)m_nWidgetDlg);
}

void CDlgMotif::CancelButtonPushed(Widget widget, XtPointer client_data, XtPointer call_data)
{
	CDlgMotif *pDlg=(CDlgMotif *)client_data;
	pDlg->m_nModalResult =IDCANCEL;
	pDlg->OnCancel ();
}


void CDlgMotif::OKButtonPushed (Widget widget, XtPointer client_data, XtPointer call_data)
{
	CDlgMotif *pDlg=(CDlgMotif *)client_data;
	pDlg->m_nModalResult =IDOK;
	pDlg->OnOK ();
}


