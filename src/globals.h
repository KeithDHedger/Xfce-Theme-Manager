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
 * Globals.h
 */

#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gtk/gtk.h>

#ifndef _GLOBALS_
#define _GLOBALS_

#define PADWIDTH 72
#define MAXBOXWIDTH 240
#define ICONSIZE 32
#define ICONPAD 8

#define XCONFSETSTYLE "xfconf-query -nRt int -c xfce4-desktop -vp /backdrop/screen0/monitor0/image-style -s "
#define XCONFSETBRIGHT "xfconf-query -nRt int -c xfce4-desktop -vp /backdrop/screen0/monitor0/brightness -s "
#define XCONFSETSATU "xfconf-query -nRt double -c xfce4-desktop -vp /backdrop/screen0/monitor0/saturation -s "

#define XCONFSETFRAME "xfconf-query -nRt string -c xfwm4 -vp /general/theme -s "
#define XCONFSETCONTROLS "xfconf-query -nRt string -c xsettings -vp /Net/ThemeName -s "
#define XCONFSETICONS "xfconf-query -nRt string -c xsettings -vp /Net/IconThemeName -s "
#define XCONFSETCURSOR "xfconf-query -nRt string -c xsettings -vp /Gtk/CursorThemeName -s "
#define XCONFSETPAPER "xfconf-query -nRt string -c xfce4-desktop -vp /backdrop/screen0/monitor0/image-path -s "

#define XCONFSETLAYOUT "xfconf-query -c xfwm4 -vp /general/button_layout -s"
#define XCONFSETTITLEPOS "xfconf-query -c xfwm4 -vp /general/title_alignment -s "

#define XCONFSETWMFONT "xfconf-query -c xfwm4 -vp /general/title_font -s "
#define XCONFSETAPPFONT "xfconf-query -c xsettings -vp /Gtk/FontName -s "

#define GLOBALICONS "/usr/share/icons"
#define GLOBALTHEMES "/usr/share/themes"
#define GLOBALWALLPAPERS "/usr/share/xfce4/backdrops"

#define XCONFGETCONTROLS "xfconf-query -c xsettings -vp /Net/ThemeName"
#define XCONFGETICONS "xfconf-query -c xsettings -vp /Net/IconThemeName"
#define XCONFGETCURSOR "xfconf-query -c xsettings -vp /Gtk/CursorThemeName"
#define XCONFGETFRAME "xfconf-query -c xfwm4 -vp /general/theme"
#define XCONFGETPAPER "xfconf-query -nRt string -c xfce4-desktop -vp /backdrop/screen0/monitor0/image-path"

#define XCONFGETLAYOUT "xfconf-query -c xfwm4 -vp /general/button_layout"
#define XCONFGETTITLEPOS "xfconf-query -c xfwm4 -vp /general/title_alignment"

#define XCONFGETWMFONT "xfconf-query -c xfwm4 -vp /general/title_font"
#define XCONFGETAPPFONT "xfconf-query -c xsettings -vp /Gtk/FontName"

extern int			currentWallStyle;
extern char*		currentIconTheme;
extern char*		currentWmTheme;
extern char*		currentCursorTheme;
extern char*		currentWallPaper;
extern char*		currentGtkTheme;
extern char*		currentButtonLayout;
extern char*		currentTitlePos;
extern char*		currentWMFont;
extern char*		currentAppFont;

//db
extern char*		dbFolder;
extern char*		metaFolder;
extern char*		framesFolder;
extern char*		controlsFolder;
extern char*		iconsFolder;
extern char*		cursorsFolder;
extern char*		wallpapersFolder;

//to bie gone
extern int		button_offset,button_spacing;
extern GdkPixbuf*	gtkPixbuf;
extern int		boxhite;
extern int		gtkwidth;
extern int		gtkheight;

//folders
extern char*		themesArray[2];
extern char*		iconsArray[2];
extern char*		papersArray[2];

extern char*		cursorTheme;
extern char*		iconTheme;

extern GtkWidget*		window;

extern void freeAndNull(char** ptr);


#endif

