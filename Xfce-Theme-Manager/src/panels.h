/******************************************************
*
*     ©keithhedger Mon 17 Jun 12:11:12 BST 2013
*     kdhedger68713@gmail.com
*
*     panels.h
* 
******************************************************/

#include "globals.h"

#ifndef _PANELS_
#define _PANELS_

void selectPanel(GtkComboBox *widget, gpointer user_data);
void populatePanels(void);
void selectPanel(GtkComboBox *widget, gpointer user_data);
gboolean panelSizeCallback(GtkWidget *widget,GdkEvent *event,gpointer user_data);
void selectPanelStyle(GtkWidget* widget,gpointer data);
void commnonPanelCallback(GtkWidget* widget,gpointer data);
void setPanelColour(GtkColorButton *widget, gpointer user_data);
void setPanels(void);

#endif
