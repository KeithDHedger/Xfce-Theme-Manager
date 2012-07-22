/*
 *
 * K.D.Hedger 2012 <kdheger@yahoo.co.uk>
 *
 * Globals.h
 */

#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gtk/gtk.h>

#ifndef _GLOBALS_
#define _GLOBALS_

#define VERSION "0.1.12"

#define PADWIDTH 72
#define MAXBOXWIDTH 240
#define ICONSIZE 32
#define ICONPAD 8

#define DELETETHEME 100

#define XCONFSETSTYLE "xfconf-query -nRt int -c xfce4-desktop -vp /backdrop/screen0/monitor0/image-style -s "
#define XCONFSETBRIGHT "xfconf-query -nRt int -c xfce4-desktop -vp /backdrop/screen0/monitor0/brightness -s "
#define XCONFSETSATU "xfconf-query -nRt double -c xfce4-desktop -vp /backdrop/screen0/monitor0/saturation -s "

#define XCONFSETFRAME "xfconf-query -nRt string -c xfwm4 -vp /general/theme -s "
#define XCONFSETCONTROLS "xfconf-query -nRt string -c xsettings -vp /Net/ThemeName -s "
#define XCONFSETICONS "xfconf-query -nRt string -c xsettings -vp /Net/IconThemeName -s "
#define XCONFSETCURSOR "xfconf-query -nRt string -c xsettings -vp /Gtk/CursorThemeName -s "
#define XCONFSETPAPER "xfconf-query -nRt string -c xfce4-desktop -vp /backdrop/screen0/monitor0/image-path -s "

#define XCONFSETLAYOUT "xfconf-query -c xfwm4 -vp /general/button_layout -s "
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

#define XCONFGETSTYLE "xfconf-query -nRt int -c xfce4-desktop -vp /backdrop/screen0/monitor0/image-style"
#define XCONFGETBRIGHT "xfconf-query -nRt int -c xfce4-desktop -vp /backdrop/screen0/monitor0/brightness"
#define XCONFGETSATU "xfconf-query -nRt double -c xfce4-desktop -vp /backdrop/screen0/monitor0/saturation"

#define XCONFGETCURSORSIZE "xfconf-query -nRt int -c xsettings -vp /Gtk/CursorThemeSize"
#define XCONFSETCURSORSIZE "xfconf-query -nRt int -c xsettings -vp /Gtk/CursorThemeSize -s "

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

#define _translate(x) langStr[langID][x]

#define ENGLISH 0
#define SPANISH 1
#define GERMAN 2

enum words {THEMES=0,WMBORDERS,CONTROLS,ICONS,CURSORS,WALLPAPERS,REBUILDTHEDB,REBUILDDB,LAUNCHXCE,BACKDROPADJ,BRITE,SATU,RESET,BUTTONLAYOUT,FONTSELECT,WMFONT,APPFONT,CURSORSIZE,RESETTHEME,CUSTOMTHEME,ADVANCED,TITLEPOS,ENTERNAME,LEFT,CENTRE,RIGHT,AUTO,CENTRED,TILED,STRETCH,SCALE,ZOOM,CUSTOM,VIEW,GLOBAL,CUSTOMMETA,STOPWORD};

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
extern int 			wallStyle;
extern GtkWidget*		layoutEntry;
extern GtkComboBoxText*	titlePos;
extern GtkWidget*		briteRange;
extern GtkWidget*		satuRange;
extern GtkWidget*		cursorSize;

extern GtkWidget*		themesScrollBox;
extern GtkWidget*		framesScrollBox;
extern GtkWidget*		controlsScrollBox;
extern GtkWidget*		iconsScrollBox;
extern GtkWidget*		cursorsScrollBox;
extern GtkWidget*		wallpapersMainBox;

extern GtkWidget*		themesVBox;
extern GtkWidget*		framesVBox;
extern GtkWidget*		controlsVBox;
extern GtkWidget*		iconsVBox;
extern GtkWidget*		cursorsVBox;
extern GtkWidget*		wallpapersVBox;

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

extern void freeAndNull(char** ptr);
extern int positionToInt(char* pos);
extern char* doubleToStr(double num);

#endif

