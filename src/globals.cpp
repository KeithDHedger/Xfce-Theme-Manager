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
 * Globals.cpp
 */
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <stdlib.h>
#include <gtk/gtk.h>

//current stuff
int		currentWallStyle=0;
char*		currentIconTheme;
char*		currentWmTheme;
char*		currentCursorTheme;
char*		currentWallPaper;
char*		currentGtkTheme;
char*		currentButtonLayout;
char*		currentTitlePos;
char*		currentWMFont;
char*		currentAppFont;

//db
char*		dbFolder;
char*		metaFolder;
char*		framesFolder;
char*		controlsFolder;
char*		iconsFolder;
char*		cursorsFolder;
char*		wallpapersFolder;

//to bie gone
int		button_offset,button_spacing;
GdkPixbuf*	gtkPixbuf;
int		boxhite=90;
int		gtkwidth=200;
int		gtkheight=50;

//folders
char*		themesArray[2];
char*		iconsArray[2];
char*		papersArray[2];

char*		cursorTheme;
char*		iconTheme;

void freeAndNull(char** ptr)
{
	if (*ptr!=NULL)
		{
			free(*ptr);
			*ptr=NULL;
		}
}




