/*
 *
 * ©K. D. Hedger. Tue 20 Oct 15:52:50 BST 2015 kdhedger68713@gmail.com

 * This file (callbacks.h) is part of Xfce-Theme-Manager.

 * Xfce-Theme-Manager is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.

 * Xfce-Theme-Manager is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Xfce-Theme-Manager.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "globals.h"

#ifndef _CALLBACKS_
#define _CALLBACKS_

void doMeta(char* metaFilename);

void customTheme(GtkWidget* window,gpointer data);

void rerunAndBuild(GtkWidget* window,gpointer data);
void rerunAndUpdate(bool rebuild,bool resetmeta);

void setTitlePos(GtkComboBoxText* widget,gpointer data);
void dropUri(GtkWidget *widget,GdkDragContext *context,gint x,gint y,GtkSelectionData *selection_data,guint info,guint32 time,gpointer user_data);
void wallStyleChanged(GtkWidget* widget,gpointer data);
void previewSizeChanged(GtkWidget* widget,gpointer data);
void themeIconCallback(GtkIconView *view,gpointer doWhat);
void setPiece(char* filePath,const char* doCommand,bool update);

gboolean itemact (GtkWidget *widget,GdkEvent  *event,gpointer   user_data);
gboolean mouseMove(GtkWidget *widget,GdkEvent* event,gpointer user_data);
gboolean clickIt(GtkWidget *widget,GdkEvent* event,gpointer data);

void launchCompEd(GtkWidget* window,gpointer data);

void resetBright(GtkWidget* widget,gpointer data);
gboolean setBright(GtkWidget *widget,GdkEvent *event,gpointer user_data);
void resetSatu(GtkWidget* widget,gpointer data);
gboolean setSatu(GtkWidget *widget,GdkEvent *event,gpointer user_data);

void resetLayout(GtkWidget* widget,gpointer data);
void changeLayout(GtkWidget* widget,gpointer data);
void setFont(GtkWidget* widget,gpointer data);
void resetFont(GtkWidget* widget,gpointer data);

void setCursSize(GtkWidget* widget,gpointer data);
void resetCursSize(GtkWidget* widget,gpointer data);

void doResize(GtkWindow *window,gpointer user_data);
gboolean doChangePage(GtkNotebook *notebook,gpointer arg1,guint arg2,gpointer user_data);

//do config stuff
void doSetConfigs(void);
void changeView(GtkWidget* widget,gpointer data);
void changeViewWhat(GtkWidget* widget,gpointer data);
int checkFolders(void);

void monitorChanged(GtkWidget* widget,gpointer data);
void setMonitorData(void);
void setSpanMonitors(GtkWidget* widget,gpointer data);

#endif
