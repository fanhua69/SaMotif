

#ifndef SAMotif_Head_Tag

#define SAMotif_Head_Tag


#include <stdio.h>
#include <ctype.h>
#include <Xm/DialogS.h>
#include <Xm/MainW.h>
#include <Xm/RowColumn.h>
#include <Xm/Form.h>
#include <Xm/Text.h>
#include <Xm/PushBG.h>
#include <Xm/LabelG.h>
#include <Xm/PanedW.h>




#ifndef bool
	#define bool int 
	#define true -1
	#define false 0
	#define IDOK 1
	#define IDCANCEL -1
	#define NULL 0
#endif


Widget GetTopShell (Widget w);


bool DrawPartCMP(char *sCMPSrcFile,
				 char *sCMPFileTar,
				 int nCMPFrom,
				 int nCMPTo,
				 int nTimeFrom,
				 int nTimeTo);

bool CreateSvSys();
bool Calculation();
void DestroyShell (Widget,XtPointer,XtPointer );
void GetCMPSrcFileName(Widget widget, XtPointer client_data, XtPointer call_data);
void GetCMPTarFileName(Widget widget, XtPointer client_data, XtPointer call_data);

void Warn(char s[]);

struct  AreaItem
{
	char     *label;
	void    (*callback)(Widget w, XtPointer client_data, XtPointer call_data);
	XtPointer data;
};

#endif
