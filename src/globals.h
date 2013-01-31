/*
 *
 * K.D.Hedger 2012 <kdhedger68713@gmail.com>
 *
 * Globals.h
 */


#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gtk/gtk.h>


#ifndef _GLOBALS_
#define _GLOBALS_

extern GtkTreeModel* treemodel;
extern GtkTreePath* holdPath;
extern GtkAdjustment *    adj;
extern GtkTreeIter savediter;

#define VERSION "0.2.3"
#define MYEMAIL "kdhedger68713@gmail.com"
#define MYWEBSITE "http://keithhedger.hostingsiteforfree.com"

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

#define XCONFSETSTYLE "xfconf-query -nRt int -c xfce4-desktop -p /backdrop/screen0/monitor0/image-style -s "
#define XCONFSETBRIGHT "xfconf-query -nRt int -c xfce4-desktop -p /backdrop/screen0/monitor0/brightness -s "
#define XCONFSETSATU "xfconf-query -nRt double -c xfce4-desktop -p /backdrop/screen0/monitor0/saturation -s "

#define XCONFSETFRAME "xfconf-query -nRt string -c xfwm4 -p /general/theme -s "
#define XCONFSETCONTROLS "xfconf-query -nRt string -c xsettings -p /Net/ThemeName -s "
#define XCONFSETICONS "xfconf-query -nRt string -c xsettings -p /Net/IconThemeName -s "
#define XCONFSETCURSOR "xfconf-query -nRt string -c xsettings -p /Gtk/CursorThemeName -s "
#define XCONFSETPAPER "xfconf-query -nRt string -c xfce4-desktop -p /backdrop/screen0/monitor0/image-path -s "

#define XCONFSETLAYOUT "xfconf-query -c xfwm4 -p /general/button_layout -s "
#define XCONFSETTITLEPOS "xfconf-query -c xfwm4 -p /general/title_alignment -s "

#define XCONFSETWMFONT "xfconf-query -c xfwm4 -p /general/title_font -s "
#define XCONFSETAPPFONT "xfconf-query -c xsettings -p /Gtk/FontName -s "

#define GLOBALICONS "/usr/share/icons"
#define GLOBALTHEMES "/usr/share/themes"
#define GLOBALWALLPAPERS "/usr/share/xfce4/backdrops"

#define XCONFGETCONTROLS "xfconf-query -c xsettings -p /Net/ThemeName"
#define XCONFGETICONS "xfconf-query -c xsettings -p /Net/IconThemeName"
#define XCONFGETCURSOR "xfconf-query -c xsettings -p /Gtk/CursorThemeName"
#define XCONFGETFRAME "xfconf-query -c xfwm4 -p /general/theme"
#define XCONFGETPAPER "xfconf-query -nRt string -c xfce4-desktop -vp /backdrop/screen0/monitor0/image-path"

#define XCONFGETLAYOUT "xfconf-query -c xfwm4 -p /general/button_layout"
#define XCONFGETTITLEPOS "xfconf-query -c xfwm4 -p /general/title_alignment"

#define XCONFGETWMFONT "xfconf-query -c xfwm4 -p /general/title_font"
#define XCONFGETAPPFONT "xfconf-query -c xsettings -p /Gtk/FontName"

#define XCONFGETSTYLE "xfconf-query -nRt int -c xfce4-desktop -p /backdrop/screen0/monitor0/image-style"
#define XCONFGETBRIGHT "xfconf-query -nRt int -c xfce4-desktop -p /backdrop/screen0/monitor0/brightness"
#define XCONFGETSATU "xfconf-query -nRt double -c xfce4-desktop -p /backdrop/screen0/monitor0/saturation"

#define XCONFGETCURSORSIZE "xfconf-query -nRt int -c xsettings -p /Gtk/CursorThemeSize"
#define XCONFSETCURSORSIZE "xfconf-query -nRt int -c xsettings -p /Gtk/CursorThemeSize -s "

#define XMTGETSHOWSYSTEM  "xfconf-query -c xfcethemer -p /ShowGlobal"
#define XMTSETSHOWSYSTEM  "xfconf-query -nt int -c xfcethemer -p /ShowGlobal -s "
#define XMTGETSHOWMETA "xfconf-query -c xfcethemer -p /ShowMeta"
#define XMTSETSHOWMETA  "xfconf-query -nt int -c xfcethemer -p /ShowMeta -s "
#define XMTGETSHOWGTK "xfconf-query -c xfcethemer -p /ShowGtk"
#define XMTSETSHOWGTK  "xfconf-query -nt int -c xfcethemer -p /ShowGtk -s "
#define XMTGETSHOWWMB "xfconf-query -c xfcethemer -p /ShowDecs"
#define XMTSETSHOWWMB  "xfconf-query -nt int -c xfcethemer -p /ShowDecs -s "
#define XMTGETSHOWICONS "xfconf-query -c xfcethemer -p /ShowIcons"
#define XMTSETSHOWICONS  "xfconf-query -nt int -c xfcethemer -p /ShowIcons -s "
#define XMTGETSHOWCURSORS "xfconf-query -c xfcethemer -p /ShowCursors"
#define XMTSETSHOWCURSORS  "xfconf-query -nt int -c xfcethemer -p /ShowCursors -s "
#define XMTGETSHOWPAPER "xfconf-query -c xfcethemer -p /ShowBackdrop"
#define XMTSETSHOWPAPER  "xfconf-query -nt int -c xfcethemer -p /ShowBackdrop -s "
#define XMTGETSHOWCUSTOM "xfconf-query -c xfcethemer -p /ShowOnlyCustom"
#define XMTSETSHOWCUSTOM "xfconf-query -nt int -c xfcethemer -p /ShowOnlyCustom -s "

#define XMTGETWINWID "xfconf-query -c xfcethemer -p /WindowWidth"
#define XMTGETWINHITE "xfconf-query -c xfcethemer -p /WindowHeight"
#define XMTSETWINWID "xfconf-query -nt int -c xfcethemer -p /WindowWidth -s "
#define XMTSETWINHITE "xfconf-query -nt int -c xfcethemer -p /WindowHeight -s "

#define XMTGETMETATHEME "xfconf-query -c xfcethemer -p /MetaTheme"
#define XMTSETMETATHEME "xfconf-query -nt string -c xfcethemer -p /MetaTheme -s "

#define XMTSETPRESIZE "xfconf-query -nt int -c xfcethemer -p /PreveiwSize -s "
#define XMTGETPRESIZE "xfconf-query -c xfcethemer -p /PreveiwSize"

#define _translate(x) langStr[langID][x]

enum {ENGLISH=0,SPANISH,GERMAN};

enum dataType {INT,STRING,FLOAT};
enum {PIXBUF_COLUMN,TEXT_COLUMN,FILE_NAME};
enum words {THEMES=0,WMBORDERS,CONTROLS,ICONS,CURSORS,WALLPAPERS,REBUILDTHEDB,REBUILDDB,LAUNCHXCE,BACKDROPADJ,BRITE,SATU,RESET,BUTTONLAYOUT,FONTSELECT,WMFONT,APPFONT,CURSORSIZE,RESETTHEME,CUSTOMTHEME,ADVANCED,TITLEPOS,ENTERNAME,LEFT,CENTRE,RIGHT,AUTO,CENTRED,TILED,STRETCH,SCALE,ZOOM,CUSTOM,VIEW,GLOBAL,CUSTOMMETA,REMOVETHEME,SUBTITLE,ABOUTBOX,HUGEP,LARGEP,MEDIUMP,SMALLP,STOPWORD};

enum preSize {PREHUGE=256,PRELARGE=128,PREMEDIUM=64,PRESMALL=48};
enum {SCROLLBOX,VBOX,ICONVIEW};

extern const char*	folders[];
extern const char*	langStr[][STOPWORD];
	
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
extern int			currentBright;
extern double		currentSatu;
extern int			currentCursSize;
extern char*		currentMetaTheme;

extern char*		lastGtkTheme;
extern char*		lastIconTheme;
extern char*		lastWmTheme;
extern char*		lastCursorTheme;
extern char*		lastWallPaper;
extern char*		lastMetaTheme;

struct boxStruct
{
	GtkScrolledWindow*	scrollBox;
//	GtkHBox*			hBox;
	GtkVBox*			vBox;
	GtkIconView*		iconView;
	int				itemCnt;
	GtkTreeIter			partIter;
	GtkListStore *		listStore;
};

extern boxStruct previewBox[6];

//db
extern char*		dbFolder;
extern char*		metaFolder;
extern char*		framesFolder;
extern char*		controlsFolder;
extern char*		iconsFolder;
extern char*		cursorsFolder;
extern char*		wallpapersFolder;
extern char*		customFolder;

//folders
extern char*		themesArray[2];
extern char*		iconsArray[2];
extern char*		papersArray[2];
extern char*		homeFolder;

extern char*		cursorTheme;
extern char*		iconTheme;

//widgets
extern GtkWidget*		appFontButton;
extern GtkWidget*		wmFontButton;
extern GtkWidget*		window;
extern GtkComboBoxText*	styleComboBox;
extern GtkComboBoxText*	previewComboBox;

extern int 			wallStyle;
extern GtkWidget*		layoutEntry;
extern GtkComboBoxText*	titlePos;
extern GtkWidget*		briteRange;
extern GtkWidget*		satuRange;
extern GtkWidget*		cursorSize;

extern GtkWidget*		wallpapersMainBox;

//advanced
extern GtkNotebook*	advanced;
extern GtkWidget*		systemCheck;
extern GtkWidget*		metaCheck;
extern GtkWidget*		borderCheck;
extern GtkWidget*		gtkCheck;
extern GtkWidget*		iconsCheck;
extern GtkWidget*		cursorsCheck;
extern GtkWidget*		paperCheck;
extern GtkWidget*		onlyCustomCheck;

extern int			controlHeight;
extern int			controlWidth;
extern GdkPixbuf*		controlsPixbuf;
extern GtkNotebook*	notebook;

extern char			generalBuffer[4096];

extern GdkPixbuf*		missingImage;
extern GdkPixbuf*		blankImage;

extern int			langID;

//config stuff
extern int			showGlobal;
extern int			showMeta;
extern int			showGtk;
extern int			showDecs;
extern int			showIcons;
extern int			showCursors;
extern int			showBackdrop;
extern int			showOnlyCustom;
extern int			winWid;
extern int			winHite;
extern int			previewSize;
extern int			gotXCE;

extern void freeAndNull(char** ptr);
extern int positionToInt(char* pos);
extern char* doubleToStr(double num);
void setValue(const char* command,dataType type,void* ptr);
int sizeDrop(bool toDrop,int data);

#endif

