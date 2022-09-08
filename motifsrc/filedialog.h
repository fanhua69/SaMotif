
/////////////////////////////
// This is for GetAndSetFileName
#ifndef CFileOpenPar_Tag
#define CFileOpenPar_Tag

class CFileOpenPar
{
public:
	Widget m_widgetEdit;
	bool m_bForReading;

	CFileOpenPar()
	{
		m_widgetEdit=(Widget)0;
		m_bForReading=false;
	};

	CFileOpenPar(Widget widget, bool bForReading)
	{
		m_widgetEdit=widget;
		m_bForReading=bForReading;
	};

	CFileOpenPar(int widget, bool bForReading)
	{
		m_widgetEdit=(Widget)widget;
		m_bForReading=bForReading;
	};

};

#endif

#ifndef FH_FILEDIALOG_TAG_12345
#define FH_FILEDIALOG_TAG_12345

class CFileDialog
{
public:
	CFileDialog();
	~CFileDialog();

	char * OpenFile(Widget parent, bool bOpenForReading);


public:
	static int is_writable (char *file);
	static int is_readable(char *file);

public:
	char m_sFile[300];  // For saving the selected file;
	bool m_bButtonPushed;

public:
	static void GetAndSetFileName(Widget widget, XtPointer client_data, XtPointer call_data);

protected:
	static bool m_bForReading;  // Used only in this class
	static void Cancel_Pushed(Widget, XtPointer, XtPointer);
	static void OKPushed (Widget widget, XtPointer client_data, XtPointer call_data);

};

#endif

