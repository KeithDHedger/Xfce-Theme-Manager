/*
 *
 * K.D.Hedger 2012 <kdhedger68713@gmail.com>
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
void wallStyleChanged(GtkWidget* widget,gpointer data);
void previewSizeChanged(GtkWidget* widget,gpointer data);
void themeIconCallback(GtkIconView *view,gpointer doWhat);

gboolean mouseMove(GtkWidget *widget,GdkEvent* event,gpointer user_data);
gboolean clickIt(GtkWidget *widget,GdkEvent* event,gpointer data);

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

void doResize(GtkWindow *window,gpointer user_data);

//do config stuff
void doSetConfigs(void);
void changeView(GtkWidget* widget,gpointer data);
void changeViewWhat(GtkWidget* widget,gpointer data);

#endif
