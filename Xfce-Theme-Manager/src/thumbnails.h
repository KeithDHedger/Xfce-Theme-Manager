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
 * K.D.Hedger 2012 <kdhedger68713@gmail.com>
 *
 * thumbnails.h
 */

#ifndef _THUMBS_
#define _THUMBS_

extern void makecursor(char* theme,char* outPath);
extern GdkPixbuf * create_gtk_theme_pixbuf(char* name);
extern void makeborder(char* folder,char* outframe);
extern void getspace(char* folder);
extern void makeIcon(char* themename,char* outPath);

#endif
