/*
 *
 * ©K. D. Hedger. Tue 20 Oct 15:54:03 BST 2015 keithdhedger@gmail.com

 * This file (globals.h) is part of Xfce-Theme-Manager.

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


#include <gtk/gtk.h>

#ifndef _GLOBALS_
#define _GLOBALS_

#define PADWIDTH 72
#define MAXBOXWIDTH 256
#define ICONSIZE 32
#define ICONTHEMESIZE 64
#define GTKWIDTH 256
#define GTKHEIGHT 64

#define CURSORTHEMESIZE 64
#define CURSORTHEMEWIDTH CURSORTHEMESIZE*4

#define ICONPAD 8
#define PREFERVERSION 34
#define GAP 8
#define HALFGAP GAP/2
#define BORDER 0

#define DELETETHEME 100

#define GLOBALICONS "/usr/share/icons"
#define GLOBALTHEMES "/usr/share/themes"
#define GLOBALWALLPAPERS "/usr/share/backgrounds/xfce"

//new props defines
#define XSETTINGS "xsettings"
#define XFWM "xfwm4"
#define XFCEDESKTOP "xfce4-desktop"
#define XTHEMER "xfcethemer"
#define XFCEPANELS "xfce4-panel"
#define MONITORPROP "/backdrop/screen0/monitor"
#define SCREENPROP "/backdrop/screen0/xinerama-stretch"
#define CONTROLTHEMEPROP "/Net/ThemeName"
#define ICONTHEMEPROP "/Net/IconThemeName"
#define WMBORDERSPROP "/general/theme"
#define CURSORSPROP "/Gtk/CursorThemeName"

#define METATHEMEPROP "/MetaTheme"
#define BUTTONLAYOUTPROP "/general/button_layout"
#define TITLEALIGNPROP "/general/title_alignment"
#define WMFONTPROP "/general/title_font"
#define APPFONTPROP "/Gtk/FontName"

#define CURSORSIZEPROP "/Gtk/CursorThemeSize"

//my configs
#define SHOWSYSTEMPROP "/ShowGlobal"
#define SHOWMETAPROP "/ShowMeta"
#define SHOWGTKPROP "/ShowGtk"
#define SHOWWMBORDERPROP "/ShowDecs"
#define SHOWICONSPROP "/ShowIcons"
#define SHOWCURSORSPROP "/ShowCursors"
#define SHOWBACKDROPSPROP "/ShowBackdrop"
#define SHOWCUSTOMPROP "/ShowOnlyCustom"
#define WINWIDPROP "/WindowWidth"
#define WINHITEPROP "/WindowHeight"
#define PREVSIZEPROP "/PreveiwSize"
#define HASHPROP "/ThemesHash"

#define _translate(x) langStr[langID][x]
#define _translateHelp(x) helpStr[langID][x]

enum {ENGLISH=0,SPANISH,GERMAN,POLISH,FRENCH,PORTUGUESE,NONE};

enum dataType {INT,BOOLEAN,STRING,FLOAT,COLOURARRAY};
enum {PIXBUF_COLUMN,TEXT_COLUMN,FILE_NAME};
enum words {THEMES=0,WMBORDERS,CONTROLS,ICONS,CURSORS,WALLPAPERS,REBUILDTHEDB,REBUILDDB,LAUNCHXCE,BACKDROPADJ,BRITE,SATU,RESET,BUTTONLAYOUT,FONTSELECT,WMFONT,APPFONT,CURSORSIZE,RESETTHEME,CUSTOMTHEME,ADVANCED,TITLEPOS,ENTERNAME,LEFT,CENTRE,RIGHT,AUTO,CENTRED,TILED,STRETCH,SCALE,ZOOM,CUSTOM,VIEW,GLOBAL,CUSTOMMETA,REMOVETHEME,SUBTITLE,ABOUTBOX,HUGEP,LARGEP,MEDIUMP,SMALLP,PANELS,PANELSIZE,PANELNONE,PANELSYS,PANELIMAGE,PANELSTYLE,PANELFILE,PANELALPHA,PANELCOLOUR,GOTOSITE,MONITOR,NOSTYLE,SPANMONITORS,STOPWORD};

enum helpwords
{HELP1,HELP2,HELP3,HELP4,HELP5,HELP6,HELP7,HELP8,HELP9,HELP10,HELP11,HELP12,HELP13,HELP14,HELP15,HELP16,HELP17,HELP18,HELP19,HELP20,HELP21,HELP22,HELP23,HELP24,HELP25,HELP26,HELP27,HELP28,HELPSTOP};

enum preSize {PREHUGE=256,PRELARGE=128,PREMEDIUM=64,PRESMALL=48};
enum {SCROLLBOX,VBOX,ICONVIEW};

extern const char*		folders[];
extern const char*		langStr[][STOPWORD];
extern const wchar_t*	helpStr[][HELPSTOP];
	
extern char*			currentIconTheme;
extern char*			currentWMTheme;
extern char*			currentCursorTheme;
extern char*			currentGtkTheme;

extern char*			currentButtonLayout;
extern char*			currentTitlePos;
extern char*			currentWMFont;
extern char*			currentAppFont;
extern int				currentCursSize;
extern char*			currentMetaTheme;

extern char*			originalGtkTheme;
extern char*			originalIconTheme;
extern char*			originalWMTheme;
extern char*			originalCursorTheme;
extern char*			originalWallpaper;
extern char*			originalMetaTheme;

extern char*			homeThemesHash;
extern bool				initing;

struct boxStruct
{
	GtkScrolledWindow*	scrollBox;
	GtkVBox*			vBox;
	GtkIconView*		iconView;
	int					itemCnt;
	GtkTreeIter*		partIter;
	GtkListStore *		store;
};

extern boxStruct		previewBox[6];

//db
extern char*			dbFolder;
extern char*			metaFolder;
extern char*			framesFolder;
extern char*			controlsFolder;
extern char*			iconsFolder;
extern char*			cursorsFolder;
extern char*			wallpapersFolder;
extern char*			customFolder;

//folders
extern char*			themesArray[2];
extern char*			iconsArray[2];
extern char*			papersArray[2];
extern char*			homeFolder;

extern char*			cursorTheme;
extern char*			iconTheme;

//widgets
extern GtkWidget*		appFontButton;
extern GtkWidget*		wmFontButton;
extern GtkWidget*		window;
extern GtkComboBoxText*	styleComboBox;
extern GtkComboBoxText*	previewComboBox;
extern GdkWindow*		gdkWindow;
extern GdkCursor*		watchCursor;
extern GtkWidget*		screenNumber;

//monitor stuff
struct monitorStruct
{
	char*	imagePath;
	int		brightness;
	double	satu;
	int		style;
	char*	name;
};

extern int				numberOfMonitors;
extern int				currentMonitor;
extern monitorStruct*	monitorData[10];
extern monitorStruct*	revertMonitorData[10];

extern GtkWidget*		layoutEntry;
extern GtkComboBoxText*	titlePos;
extern GtkWidget*		briteRange;
extern GtkWidget*		satuRange;
extern GtkWidget*		spanMonitorsWidget;
extern GtkWidget*		cursorSize;

extern GtkWidget*		wallpapersMainBox;

//advanced
extern GtkNotebook*		advanced;
extern GtkWidget*		systemCheck;
extern GtkWidget*		metaCheck;
extern GtkWidget*		borderCheck;
extern GtkWidget*		gtkCheck;
extern GtkWidget*		iconsCheck;
extern GtkWidget*		cursorsCheck;
extern GtkWidget*		paperCheck;
extern GtkWidget*		onlyCustomCheck;

//panels
struct panelData
{
	char*				imagePath;
	int					style;
	int					size;
	int					red;
	int					green;
	int					blue;
	int					alpha;
	int					panelNumber;
};

//panels
extern GtkWidget*		panelSelect;
extern GtkWidget*		panelStyleWidget;
extern GtkWidget*		panelSizeWidget;
extern panelData*		panels[10];
extern panelData*		revertPanels[10];
extern int				numOfPanels;

extern int				currentPanel;
extern GtkWidget*		panelImagePathWidget;
extern GtkWidget*		panelAlphaWidget;
extern GtkWidget*		panelColourWidget;

extern GtkWidget*		panelImageBox;
extern GtkWidget*		panelColourBox;
extern GtkWidget*		panelAlphaBox;

extern int				controlHeight;
extern int				controlWidth;
extern GdkPixbuf*		controlsPixbuf;
extern GtkNotebook*		notebook;

extern char				generalBuffer[4096];

extern GdkPixbuf*		missingImage;
extern GdkPixbuf*		blankImage;

extern int				langID;

//config stuff
extern int				showGlobal;
extern int				showMeta;
extern int				showGtk;
extern int				showDecs;
extern int				showIcons;
extern int				showCursors;
extern int				showBackdrop;
extern int				showOnlyCustom;
extern int				winWid;
extern int				winHite;
extern int				previewSize;
extern int				gotXCE;
extern int				spanMonitors;

extern bool				noGui;
extern bool				updateDb;
extern bool				rebuildDb;

void freeAndNull(char** ptr);
int positionToInt(char* pos);
int sizeDrop(bool toDrop,int data);
void getValue(const char* channel,const char* property,dataType type,void* ptr);
void setValue(const char* channel,const char* property,dataType type,void* ptr);
void freeAndSet(char** ptr,char* data);
char* getThemeNameFromDB(char* filepath);
char* sliceBetween(char* srcstring,char* startstr,char* endstr);
char* slice(char* srcstring,int tmpstartchar,int tmpendchar);

#endif

