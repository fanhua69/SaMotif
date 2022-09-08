

/* file_sel.c -- file selection dialog displays a list of all the writable
** files in the directory described by the XmNmask of the dialog. 
** This program demonstrates how to use the XmNfileSearchProc for 
** file selection dialog widgets.
*/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/FileSB.h>
#include <Xm/DialogS.h>
#include <Xm/PushBG.h>
#include <Xm/PushB.h>
#include <X11/Xos.h>
#include <sys/stat.h> 
#include <Xm/TextF.h>

#include "samotif.h"
#include "filedialog.h"

extern XtAppContext app;

bool CFileDialog::m_bForReading=false;

CFileDialog::CFileDialog()
{
}

CFileDialog::~CFileDialog()
{
}


/* routine to determine if a file is accessible, a directory,
** or writable. 
** Return -1 on all errors .
** Return 0 if it's a directory .
** Return 1 if it's readable or writable
*/
int CFileDialog::is_writable (char *file)
{
	struct stat s_buf;
	
	/* The has is a new file: */
	if (stat (file, &s_buf) == -1)
	{
		printf("new file\n");
		return 1;
	}

	/* a directory */
	else if ((s_buf.st_mode & S_IFMT) == S_IFDIR)
	{
		printf("dir\n");
		return 0; 
	}
	
	/* not a normal file */
	else if (!(s_buf.st_mode & S_IFREG) )		
	{
		printf("error\n");
		return -1;
	}

	else
	{
		printf("Warnig: existing file: %s \n" , file);
	}
		
	
	/* legitimate file */
	if(access (file,02) == 0)
		return 1;
	else
		return -1;


}

int CFileDialog::is_readable(char *file)
{
	struct stat s_buf;
	
	/* if file can't be accessed (via stat()) return. */	
	if (stat (file, &s_buf) == -1)
		return -1;

	/* a directory */
	else if ((s_buf.st_mode & S_IFMT) == S_IFDIR)
		return 0; 
	
	/* not a normal file or it is not writable */
	else if (!(s_buf.st_mode & S_IFREG) )		
		return -1;
		
	
	/* legitimate file */
	if(access (file,04) == 0){
		printf("readable file\n");
		return 1;
	}
	else
		return -1;

}


/*
 OpenFile() -- create a FileSelectionDialog
*/
char * CFileDialog::OpenFile(Widget parent, bool bOpenForReading )
{
	Widget       dialog;
	extern void  exit(int);
	Arg          args[5];
	int          n = 0;

	if(parent==(Widget)0)return false;

	m_bForReading=bOpenForReading ;	
	
	dialog = XmCreateFileSelectionDialog (parent, "Files", args, 0);
	XtSetSensitive (XtNameToWidget (dialog, "Help"), False);
	
	/* if user presses OK button, call new_file_cb() */
	XtAddCallback (dialog, XmNokCallback, OKPushed, (void*)this);
	
	/* if user presses Cancel button, exit program */
	XtAddCallback (dialog, XmNcancelCallback, Cancel_Pushed, (void*)this);
	XtManageChild (dialog);

	// Loop till the user selected a file:
	m_bButtonPushed=NULL;
	while (m_bButtonPushed==NULL)
	{
		XtAppProcessEvent (app, XtIMAll);  
	}

	XtUnmanageChild (dialog);   
	
	/* make sure the dialog goes away before returning. Sync with server     
	** and update the display.     
	*/  	
	
	XSync (XtDisplay (dialog), 0);   
	XmUpdateDisplay (parent);    

	if(m_bButtonPushed==IDCANCEL)
	{
		return NULL;
	}
	else
	{
		return m_sFile;
	}

}

/* a new file was selected -- check to see if it's readable and not
** a directory. If it's not readable, report an error. If it's a
** directory, scan it just as though the user had typed it in the mask
** Text field and selected "Search".
*/
void CFileDialog::OKPushed (Widget widget, XtPointer client_data, XtPointer call_data)
{
	int nMode;
	char *file;

	CFileDialog * pDlg=(CFileDialog * )client_data;


	XmFileSelectionBoxCallbackStruct *cbs = (XmFileSelectionBoxCallbackStruct *) call_data;
	
	/* get the string typed in the text field in char * format */
	XmStringGetLtoR(cbs->value,XmSTRING_DEFAULT_CHARSET,&file);
	if(!file)
	{
		return;
	}
	/*if (!(file = (char *) XmStringUnparse (cbs->value, XmFONTLIST_DEFAULT_TAG, 
					       XmCHARSET_TEXT, XmCHARSET_TEXT, NULL, 0, XmOUTPUT_ALL)))
		return;*/
		
	if (*file != '/') {
		/* if it's not a directory, determine the full pathname 
		** of the selection by concatenating it to the "dir" part
		*/
		
		char *dir, *newfile; 

		XmStringGetLtoR(cbs->value,XmSTRING_DEFAULT_CHARSET,&dir);
		
		if (dir)
		{
			newfile = XtMalloc (strlen (dir) + 1 + strlen (file) + 1);
			
			sprintf (newfile, "%s/%s", dir, file);

			XtFree (file);
			XtFree (dir);

			file = newfile;
		}
	}


	if(m_bForReading)
	{
		printf("for reading\n");
		nMode=CFileDialog::is_readable(file);
	}
	else
	{
		printf("for writing\n");
		nMode=CFileDialog::is_writable(file);
	}

	
	switch (nMode) 
	{
		case 1:
		{
			strcpy(pDlg->m_sFile,file);
			pDlg->m_bButtonPushed=IDOK;
			break;

		}

		/* a directory was selected, scan it */			
		case 0: 
		{			
			XmString str = XmStringCreateLocalized (file);
			
			XmFileSelectionDoSearch (widget, str);
			XmStringFree (str);
			break;
		}
		
		/* a system error on this file */
		case -1:
		{
			perror (file);
		}
	}
	
	XtFree (file);	
}


void CFileDialog::Cancel_Pushed(Widget    widget, 
                XtPointer client_data,
				XtPointer call_data)
{
	CFileDialog * pDlg=(CFileDialog * )client_data;
	pDlg->m_bButtonPushed=IDCANCEL;
}


void CFileDialog::GetAndSetFileName(Widget widget, XtPointer client_data, XtPointer call_data)
{
	CFileOpenPar *pSet=(CFileOpenPar *)client_data;

	CFileDialog dlg;
	char *file= dlg.OpenFile (GetTopShell(widget),pSet->m_bForReading);

	if(!file)
	{
		printf("Null File Opened!\n");
	}
	else
	{
		XmTextFieldSetString(pSet->m_widgetEdit, file);
	}
}
