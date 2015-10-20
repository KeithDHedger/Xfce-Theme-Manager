/*
 *
 * ©K. D. Hedger. Tue 20 Oct 15:56:26 BST 2015 keithhedger@keithhedger.darktech.org

 * This file (gui.h) is part of Xfce-Theme-Manager.

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
 * K.D.Hedger 2012 <keithhedger@keithhedger.darktech.org>
 *
 * gui.h
 */

#include "globals.h"

#ifndef _GUI_
#define _GUI_

extern const char* langStr[][STOPWORD];

void addNewButtons(GtkWidget* vbox,const char* subfolder,void* callback);
void buildWallpapers(void);
GtkWidget* buildTitlePos(void);
void buildPages(void);
void buildAdvancedGui(GtkWidget* advancedScrollBox);
void freeIter(int whatBox);
void addNewIcons(const char* subfolder,GtkIconView* tempIconView,int whatBox);
void scrollToCurrent(int whatBox);

#endif
