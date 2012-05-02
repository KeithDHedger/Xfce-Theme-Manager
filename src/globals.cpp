/*
 *
 * K.D.Hedger 2012 <kdheger@yahoo.co.uk>
 *
 * Globals.cpp
 */
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>

//current stuff
int			currentWallStyle;
char*			currentIconTheme;
char*			currentWmTheme;
char*			currentCursorTheme;
char*			currentWallPaper;
char*			currentGtkTheme;
char*			currentButtonLayout;
char*			currentTitlePos;
char*			currentWMFont;
char*			currentAppFont;
int			currentBright;
double		currentSatu;

//db
char*			dbFolder;
char*			metaFolder;
char*			framesFolder;
char*			controlsFolder;
char*			iconsFolder;
char*			cursorsFolder;
char*			wallpapersFolder;
char*			customFolder;

//folders
char*			themesArray[2];
char*			iconsArray[2];
char*			papersArray[2];

char*			cursorTheme;
char*			iconTheme;

//widgets etc
GtkWidget*		appFontButton;
GtkWidget*		wmFontButton;
GtkWidget*		window;
GtkComboBoxText*	styleComboBox;
int 			wallStyle;
GtkWidget*		layoutEntry;
GtkComboBoxText*	titlePos;
GtkWidget*		briteRange;
GtkWidget*		satuRange;


GtkWidget*		themesScrollBox;
GtkWidget*		framesScrollBox;
GtkWidget*		controlsScrollBox;
GtkWidget*		iconsScrollBox;
GtkWidget*		cursorsScrollBox;
GtkWidget*		wallpapersMainBox;

GtkWidget*		themesVBox;
GtkWidget*		framesVBox;
GtkWidget*		controlsVBox;
GtkWidget*		iconsVBox;
GtkWidget*		cursorsVBox;
GtkWidget*		wallpapersVBox;

GtkNotebook*	advanced;

int			controlHeight=50;
int			controlWidth=200;
GdkPixbuf*		controlsPixbuf;

GtkNotebook*	notebook;

char			generalBuffer[4096];

void freeAndNull(char** ptr)
{
	if (*ptr!=NULL)
		{
			free(*ptr);
			*ptr=NULL;
		}
}

int positionToInt(char* pos)
{
	if(strcasecmp(pos,"left")==0)
		return(0);

	if(strcasecmp(pos,"center")==0)
		return(1);

	if(strcasecmp(pos,"right")==0)
		return(2);

	return(1);
}


