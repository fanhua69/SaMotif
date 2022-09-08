/* help_text.c:
** Create a simple main window that contains a sample (dummy) work
** area and a menubar. The menubar contains two items: File and Help.
** The items in the Help pulldown call help_cb(), which pops up a
** home-made dialog that displays predefined help texts. The purpose
** of this program is to demonstrate how one might approach the
** problem displaying a large amount of text in a dialog box.
*/

#include "samotif.h"
#include "dlgdrawpartcmp.h"
#include "stdlib.h"
#include "dlgcalc.h"
#include "calc.h"
#include "FHGlobal.h"
#include "string.h"


bool Calc(int nStaticRange,
		  int nMaxLoopQuantity,
		  int nLoopToSave,
		  int nCMPRate,
		  char sFileCMP[],
		  char sFileSvSys[],
		  char sFileStatic[],
		  char sFilePower[]);


/* The following help text information is a continuous stream of characters
** that will all be placed in a single ScrolledText object. If a specific
** newline is desired, you must do that yourself. See "index_help" below.
*/
String context_help[] = { "This program is to ", 
			  "Calculate static values by CMP data that have been processed ",
			  "by NMO. Pay attention to elliminate liner Noise especially which",
			  " will decrease the quality of the static value.",
			  NULL };
String window_help[] = { "You should firstly select a setion of CMP data ",
			 "with good quality that is from Time T1 to Time T2 and from ",
			 "CMP C1 to C2, and cut it by this program, ",			 
			 "And then create survey system by this program "
			 "according to the CMP data,",
			 "Thirdly calculate by the CMP data and the survey system.",
			 NULL};
String index_help[] = { 
	         "              Author : Fan Yong \n",
             "                       TDP Co. Lt. BeiJing, China \n",
			 "              Email  : fanhua69@sohu.com \n",
			 "              Mobile : 13683012272\n",
			 "\n", 
			NULL};
String *help_texts[] = {context_help, window_help, index_help};


XtAppContext app;


long G_HOSTQTY=6;
long G_HOSTID[6]={0x80826F44,
                  0x80FD02F3,
				  0x80FD0203,
                  0x80FCFBFC,
                  0x80BC4776,
                  0x80BC46DE};


main (int argc, char *argv[])
{
	Widget       rc, main_w, menubar, w, label_g,toplevel;
	void         help_cb(Widget, XtPointer, XtPointer);
	void         Process_Selected(Widget, XtPointer, XtPointer);
	XmString     str1, str2, str3,str4;
	Widget      *cascade_btns;
	int          num_btns;
	Arg          args[2];
	
	XtSetLanguageProc (NULL, NULL, NULL);
	
	toplevel = XtVaOpenApplication (&app, "Static Calculation ", NULL, 0, &argc, argv, NULL, 
					 sessionShellWidgetClass, NULL); 

	/* the main window contains the work area and the menubar */
	main_w = XmCreateMainWindow ((Widget)toplevel, "main_w", NULL, 0);
	
	/* Create a simple MenuBar that contains two cascade buttons */
	str1 = XmStringCreateLocalized ("Process");
	str2 = XmStringCreateLocalized ("Help");
	menubar = XmVaCreateSimpleMenuBar (main_w, "main_w", XmVaCASCADEBUTTON, str1, 'F',
							     XmVaCASCADEBUTTON, str2, 'H',
							     NULL);
	XmStringFree (str1);
	XmStringFree (str2); 
	
	/* create the "File" pulldown menu -- callback is Process_Selected() */
	str1 = XmStringCreateLocalized ("Draw Out Part CMP Data");
	str2 = XmStringCreateLocalized ("Create Survey System");
	str3 = XmStringCreateLocalized ("Calculation");
	str4 = XmStringCreateLocalized ("Quit");

	XmVaCreateSimplePulldownMenu (menubar, "file_menu", 0, Process_Selected, 
					       XmVaPUSHBUTTON, str1, 'D', NULL, NULL, 
					       XmVaPUSHBUTTON, str2, 'S', NULL, NULL,					       
					       XmVaPUSHBUTTON, str3, 'C', NULL, NULL,
						   XmVaSEPARATOR,
						   XmVaPUSHBUTTON, str4, 'Q', NULL, NULL,
					       NULL);
					       
	XmStringFree (str1);
	XmStringFree (str2);
	XmStringFree (str3);
	XmStringFree (str4);

	
	/* create the "Help" menu -- callback is help_cb() */
	str1 = XmStringCreateLocalized ("Introduction of SA");
	str2 = XmStringCreateLocalized ("Process Steps");
	str3 = XmStringCreateLocalized ("Author");
	w = XmVaCreateSimplePulldownMenu (menubar, "help_menu", 1, help_cb,
						   XmVaPUSHBUTTON, str1, 'I', NULL, NULL,
						   XmVaPUSHBUTTON, str2, 'P', NULL, NULL,
						   XmVaPUSHBUTTON, str3, 'A', NULL, NULL,
						   NULL);
	XmStringFree (str1);
	XmStringFree (str2);
	XmStringFree (str3);
	
	/* Identify the Help Menu for the MenuBar */
	XtVaGetValues (menubar, XmNchildren, &cascade_btns, XmNnumChildren, &num_btns, NULL);
	XtVaSetValues (menubar, XmNmenuHelpWidget, cascade_btns[num_btns-1], NULL);
	XtManageChild (menubar);
	
	/* the work area for the main window -- just create dummy stuff */
	rc = XmCreateRowColumn (main_w, "rc", NULL, 0);

	str1 = XmStringCreateLocalized ("\n                                              \n");	
	XtSetArg (args[0], XmNlabelString, str1); 
	label_g = XmCreateLabelGadget (rc, "label", args, 1);
	XtManageChild (label_g);
	XmStringFree (str1);

	str1 = XmStringCreateLocalized ("\n                  \n");	
	XtSetArg (args[0], XmNlabelString, str1); 
	label_g = XmCreateLabelGadget (rc, "label", args, 1);
	XtManageChild (label_g);
	XmStringFree (str1);


	str1 = XmStringCreateLocalized ("\n              Static Correction                \n");	
	XtSetArg (args[0], XmNlabelString, str1); 
	label_g = XmCreateLabelGadget (rc, "label", args, 1);
	XtManageChild (label_g);
	XmStringFree (str1);

	str1 = XmStringCreateLocalized ("\n                  SA Method                     \n");
	XtSetArg (args[0], XmNlabelString, str1); 	
	label_g = XmCreateLabelGadget (rc, "label", args, 1);
	XtManageChild (label_g);
	XmStringFree (str1);

	str1 = XmStringCreateLocalized ("\n                  \n");	
	XtSetArg (args[0], XmNlabelString, str1); 
	label_g = XmCreateLabelGadget (rc, "label", args, 1);
	XtManageChild (label_g);
	XmStringFree (str1);

	str1 = XmStringCreateLocalized ("\n                  \n");	
	XtSetArg (args[0], XmNlabelString, str1); 
	label_g = XmCreateLabelGadget (rc, "label", args, 1);
	XtManageChild (label_g);
	XmStringFree (str1);


	XtManageChild (rc);
	XtManageChild (main_w);
	XtRealizeWidget ((Widget)toplevel);
	XtAppMainLoop (app);
}

/* callback for all the entries in the File pulldown menu. */
#include "dlgmakesvsys.h"
#include "makesvsys.h"


void Process_Selected (Widget w, XtPointer client_data, XtPointer call_data)
{
	int item_no = (int) client_data;

	///////////////////////////////////////////////////////////////
	// Draw out part of CMP File:
	if (item_no==0)
	{
		CDlgDrawPartCMP dlg;
		dlg.Create(w,"Draw Out Part Of CMP");
		if(dlg.DoModal()==IDOK)
		{
			DrawPartCMP(dlg.m_sCMPSrcFileName,
				dlg.m_sCMPTarFileName ,
				dlg.m_nCMPFrom ,
				dlg.m_nCMPTo ,
				dlg.m_nTimeFrom ,
				dlg.m_nTimeTo );
		}
		
	}
	
	///////////////////////////////////////////////////////////////
	// Make Survey System File:
	else if(item_no==1)
	{
		CDlgMakeSvSys dlg;
		dlg.Create(w,"Make Survey System");
		if(dlg.DoModal()==IDOK)
		{
			MakeSvSys(dlg.m_sCMPFile ,dlg.m_sSvSysFile );
		}
	}
	
	///////////////////////////////////////////////////////////////
	// Calculation:
	else if(item_no==2)
	{
		CDlgCalc dlg;
		dlg.Create (w,"Calculation Pars");
		if(dlg.DoModal ()==IDOK)
		{
			Calc(dlg.m_nStaticRange ,
					dlg.m_nMaxLoopQuantity,
					dlg.m_nLoopToSaveStatic,					
					dlg.m_sFileCMP,
					dlg.m_sFileSvSys,
					dlg.m_sFileInitStatic,
					dlg.m_sFileStatic,
					dlg.m_sFilePower);
		}
	}
	
	///////////////////////////////////////////////////////////////
	// Exit
	else if (item_no == 3)
	{
		exit (0);
	}		

}

/* climb widget tree until we get to the top. Return the Shell */
Widget GetTopShell (Widget w)
{
	while (w && !XtIsWMShell (w))
		w = XtParent (w);
	return w;
}

#include "info.xbm" 

/* bitmap data used by our dialog */
/* callback for all the entries in the Help pulldown menu.
** Create a dialog box that contains control and action areas.
*/
void help_cb (Widget w, XtPointer client_data, XtPointer call_data)
{
	Widget    help_dialog, pane, text_w, form, sep, widget,widget2, label;
	void      DestroyShell(Widget, XtPointer, XtPointer);
	Pixmap    pixmap;
	Pixel     fg, bg; 
	Arg       args[10];
	int       n = 0;
	int       i;
	char     *p, buf[BUFSIZ];
	int       item_no = (int) client_data; 
	Dimension h;
	
	/* Set up a DialogShell as a popup window. Set the delete
	** window protocol response to XmDESTROY to make sure that
	** the window goes away appropriately. Otherwise, it's XmUNMAP
	** which means it'd be lost forever, since we're not storing
	** the widget globally or statically to this function. 
	*/

	i = 0;
	XtSetArg (args[i], XmNdeleteResponse, XmDESTROY); i++;	
	help_dialog = XmCreateDialogShell (GetTopShell (w), "Help", args, i);

	/* Create a PanedWindow to manage the stuff in this dialog. */
	XtSetArg (args[0], XmNsashWidth, 1);
	
	/* PanedWindow won't let us set these to 0! */
	XtSetArg (args[1], XmNsashHeight, 10);
	
	/* Make small so user doesn't try to resize */ 
	pane = XmCreatePanedWindow (help_dialog, "pane", args, 2);
	
	/* Create a RowColumn in the form for Label and Text widgets.
	** This is the control area. 
	*/
	
	form = XmCreateForm (pane, "form1", NULL, 0);
	XtVaGetValues (form, /* once created, we can get its colors */
		       XmNforeground, &fg,
		       XmNbackground, &bg,
		       NULL);
		       
	/* create the pixmap of the appropriate depth using the colors 
	** that will be used by the parent (form). 
	*/
	 
	pixmap = XCreatePixmapFromBitmapData (XtDisplay (form),
					      RootWindowOfScreen (XtScreen (form)),
					      (char *) info_bits, info_width, info_height, fg, bg,
					      DefaultDepthOfScreen (XtScreen (form)));
					      
	/* Create a label gadget using this pixmap */
	n = 0;
	XtSetArg (args[n], XmNlabelType, XmPIXMAP); n++;
	XtSetArg (args[n], XmNlabelPixmap, pixmap); n++;
	XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM); n++; 
	XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
	label = XmCreateLabelGadget (form, "label", args, n);
	XtManageChild (label); 
	
	/* prepare the text for display in the ScrolledText object 
	** we are about to create. 
	*/
	
	for (p = buf, i = 0; help_texts[item_no][i]; i++)
	{
		p += strlen (strcpy (p, help_texts[item_no][i]));
		
		if (!isspace (p[-1]))
			/* spaces, tabs and newlines are spaces. */
			
			*p++ = ' '; /* lines are concatenated together, insert a space */
	}
		
	*--p = 0; /* get rid of trailing space... */

	n = 0;
	XtSetArg (args[n], XmNscrollVertical, True); n++; 
	XtSetArg (args[n], XmNscrollHorizontal, False); n++;
	XtSetArg (args[n], XmNeditMode, XmMULTI_LINE_EDIT); n++;
	XtSetArg (args[n], XmNeditable, False); n++;
	XtSetArg (args[n], XmNcursorPositionVisible, False); n++;
	XtSetArg (args[n], XmNwordWrap, True); n++;
	XtSetArg (args[n], XmNvalue, buf); n++;
	XtSetArg (args[n], XmNrows, 5); n++;
	text_w = XmCreateScrolledText (form, "help_text", args, n);
		
	/* Attachment values must be set on the Text widget's PARENT, 
	** the ScrolledWindow. This is the object that is positioned. 
	*/ 
		
	XtVaSetValues (XtParent (text_w), XmNleftAttachment, XmATTACH_WIDGET, XmNleftWidget, label,
					  XmNtopAttachment, XmATTACH_FORM,
					  XmNrightAttachment, XmATTACH_FORM,
					  XmNbottomAttachment, XmATTACH_FORM,
					  NULL);
	XtManageChild (text_w);
	XtManageChild (form);
	
	/* Create another form to act as the action area for the dialog */
	
	XtSetArg (args[0], XmNfractionBase, 10);
	form = XmCreateForm (pane, "form2", args, 1);
	
	/* The OK button is under the pane's separator and is 
	** attached to the left edge of the form. It spreads from
	** position 0 to 1 along the bottom (the form is split into 
	** 5 separate grids via XmNfractionBase upon creation). 
	*/
		
	widget = XmCreatePushButtonGadget (form, "OK", NULL, 0);
		
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
	XtAddCallback (widget, XmNactivateCallback, DestroyShell, help_dialog);
		
	/* This is created with its XmNsensitive resource set to False 
	** because we don't support "more" help. However, this is the 
	** place to attach it to if there were any more. 
	*/
		
	widget = XmCreatePushButtonGadget (form, "Cancel", NULL, 0);
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
	XtAddCallback (widget, XmNactivateCallback, DestroyShell, help_dialog);
		
	/* Fix the action area pane to its current height -- never let it resize */
	XtManageChild (form);
		
	XtVaGetValues (widget, XmNheight, &h, NULL);
	XtVaSetValues (form, XmNpaneMaximum, h, XmNpaneMinimum, h, NULL);
		
	/* This also pops up the dialog, as it is the child of a DialogShell */
		
	XtManageChild (pane);
}


void DestroyShell (Widget widget, XtPointer client_data, XtPointer call_data)
{
	Widget shell = (Widget) client_data;
	
	XtDestroyWidget (shell);
}


void Warn(char s[])
{
	printf("%s\n",s);
	return;
}