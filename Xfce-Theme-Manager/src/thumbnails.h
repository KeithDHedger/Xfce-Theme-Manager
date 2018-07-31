/*
 *
 * ©K. D. Hedger. Tue 20 Oct 15:56:38 BST 2015 keithdhedger@gmail.com

 * This file (thumbnails.h) is part of Xfce-Theme-Manager.

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
 * K.D.Hedger 2012 <keithdhedger@gmail.com>
 *
 * thumbnails.h
 */
#include <gdk-pixbuf/gdk-pixbuf.h>

#ifndef _THUMBS_
#define _THUMBS_

extern void makecursor(char* theme,char* outPath);
extern GdkPixbuf * create_gtk_theme_pixbuf(char* name);
extern void makeborder(char* folder,char* outframe);
extern void getspace(char* folder);
extern void makeIcon(char* themename,char* outPath);

#endif
