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
 * gui.h
 */

#include "globals.h"

#ifndef _GUI_
#define _GUI_

extern const char* langStr[][STOPWORD];
extern const char* titlePosStr[][3];

void addNewButtons(GtkWidget* vbox,const char* subfolder,void* callback);
void buildWallpapers(void);
GtkWidget* buildTitlePos(void);
void buildPages(void);
void buildAdvancedGui(GtkWidget* advancedScrollBox);

#endif
