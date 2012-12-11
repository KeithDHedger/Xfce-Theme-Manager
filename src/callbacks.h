/*
 *
 * K.D.Hedger 2012 <kdheger@yahoo.co.uk>
 *
 * callbacks.cpp
 */

#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <sys/stat.h>

#include "globals.h"

#ifndef _CALLBACKS_
#define _CALLBACKS_

void customTheme(GtkWidget* window,gpointer data);

void rerunAndBuild(GtkWidget* window,gpointer data);
void rerunAndUpdate(bool rebuild,bool resetmeta);

void setTitlePos(GtkComboBoxText* widget,gpointer data);
void dropUri(GtkWidget *widget,GdkDragContext *context,gint x,gint y,GtkSelectionData *selection_data,guint info,guint32 time,gpointer user_data);
void doWallpapers(GtkWidget* widget,gpointer data);
void wallStyleChanged(GtkWidget* widget,gpointer data);
//void doMeta(char* metadata);
void themeIconCallback(GtkIconView *view,gpointer user_data);
void doFrame(GtkWidget* widget,gpointer data);
void doControls(GtkWidget* widget,gpointer data);
void doIcons(GtkWidget* widget,gpointer data);
void doCursors(GtkWidget* widget,gpointer data);
void launchCompEd(GtkWidget* window,gpointer data);

void resetBright(GtkWidget* widget,gpointer data);
gboolean setBright(GtkWidget *widget, GdkEvent *event, gpointer user_data);
void resetSatu(GtkWidget* widget,gpointer data);
gboolean setSatu(GtkWidget *widget, GdkEvent *event, gpointer user_data);

void resetLayout(GtkWidget* widget,gpointer data);
void changeLayout(GtkWidget* widget,gpointer data);
void setFont(GtkWidget* widget,gpointer data);
void resetFont(GtkWidget* widget,gpointer data);

void setCursSize(GtkWidget* widget,gpointer data);
void resetCursSize(GtkWidget* widget,gpointer data);

//do config stuff
void doSetConfigs(void);
void changeView(GtkWidget* widget,gpointer data);
void changeViewWhat(GtkWidget* widget,gpointer data);

#endif
