
#include "samotif.h"

Widget GetTopShell (Widget w);

#ifndef dlgMotif_Tag
#define dlgMotif_Tag

class CDlgMotif
{
public:
	int m_nWidgetShell;
	int m_nWidgetDlg;
	int m_nWidgetParent;
	int m_nFormControl;
	int m_nFormAction;

	int m_nModalResult;


public:
	CDlgMotif();

	virtual bool Create(Widget parent,char sDlgTitle[]);
	virtual int DoModal();
	virtual int Show();

	virtual int OnOK();
	virtual int OnCancel();

	Widget GetControlForm();
	Widget GetActionForm();
	Widget GetDlg();
	Widget GetParent();

	static void CancelButtonPushed(Widget widget, XtPointer client_data, XtPointer call_data);
	static void OKButtonPushed (Widget widget, XtPointer client_data, XtPointer call_data);

};

#endif
