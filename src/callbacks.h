/*
 * Original author of parts of gtkpreview David D Lowe <daviddlowe.flimm@gmail.com>
 * Parts of cursor preveiw Copyright (c) 2008 Nick Schermer <nick@xfce.org> & Jannis Pohlmann <jannis@xfce.org>
 * from xfce4-settings-4.6.5/dialogs/mouse-settings
 *
 * Parts of xwm4 4.10pre
 *
 * oroborus - (c) 2001 Ken Lynch
 * xfwm4    - (c) 2002-2011 Olivier Fourdan
 *
 * Seriously mucked about by:
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

void setTitlePos(GtkWidget* widget,gpointer data);
void dropUri(GtkWidget *widget,GdkDragContext *context,gint x,gint y,GtkSelectionData *selection_data,guint info,guint32 time,gpointer user_data);
void doWallpapers(GtkWidget* widget,gpointer data);
void wallStyleChanged(GtkWidget* widget,gpointer data);
void doMeta(GtkWidget* widget,gpointer data);
void doFrame(GtkWidget* widget,gpointer data);
void doControls(GtkWidget* widget,gpointer data);
void doIcons(GtkWidget* widget,gpointer data);
void doCursors(GtkWidget* widget,gpointer data);
void launchCompEd(GtkWidget* window,gpointer data);
void resetBright(GtkWidget* widget,gpointer data);

//void valChanged(GtkWidget* widget,gpointer data);
gboolean setBright(GtkWidget *widget, GdkEvent *event, gpointer user_data);

void resetSatu(GtkWidget* widget,gpointer data);
//void setSatu(GtkWidget* widget,gpointer data);
gboolean setSatu(GtkWidget *widget, GdkEvent *event, gpointer user_data);

void resetLayout(GtkWidget* widget,gpointer data);
void changeLayout(GtkWidget* widget,gpointer data);
void setFont(GtkWidget* widget,gpointer data);
void resetFont(GtkWidget* widget,gpointer data);

#endif
