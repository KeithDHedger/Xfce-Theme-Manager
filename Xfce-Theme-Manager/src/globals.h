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

#define GLOBALICONS "/usr/share/icons"
#define GLOBALTHEMES "/usr/share/themes"
#define GLOBALWALLPAPERS "/usr/share/xfce4/backdrops"

//new props defines
#define XSETTINGS "xsettings"
#define XFWM "xfwm4"
#define XFCEDESKTOP "xfce4-desktop"
#define XTHEMER "xfcethemer"
#define XFCEPANELS "xfce4-panel"

#define CONTROLTHEMEPROP "/Net/ThemeName"
#define ICONTHEMEPROP "/Net/IconThemeName"
#define WMBORDERSPROP "/general/theme"
#define CURSORSPROP "/Gtk/CursorThemeName"
#define PAPERSPROP "/backdrop/screen0/monitor0/image-path"
#define METATHEMEPROP "/MetaTheme"
#define BUTTONLAYOUTPROP "/general/button_layout"
#define TITLEALIGNPROP "/general/title_alignment"
#define WMFONTPROP "/general/title_font"
#define APPFONTPROP "/Gtk/FontName"
#define BACKDROPSTYLEPROP "/backdrop/screen0/monitor0/image-style"
#define BACKDROPBRIGHTPROP "/backdrop/screen0/monitor0/brightness"
#define BACKDROPSATUPROP "/backdrop/screen0/monitor0/saturation"
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

enum {ENGLISH=0,SPANISH,GERMAN,POLISH};

enum dataType {INT,STRING,FLOAT,COLOURARRAY};
enum {PIXBUF_COLUMN,TEXT_COLUMN,FILE_NAME};
enum words {THEMES=0,WMBORDERS,CONTROLS,ICONS,CURSORS,WALLPAPERS,REBUILDTHEDB,REBUILDDB,LAUNCHXCE,BACKDROPADJ,BRITE,SATU,RESET,BUTTONLAYOUT,FONTSELECT,WMFONT,APPFONT,CURSORSIZE,RESETTHEME,CUSTOMTHEME,ADVANCED,TITLEPOS,ENTERNAME,LEFT,CENTRE,RIGHT,AUTO,CENTRED,TILED,STRETCH,SCALE,ZOOM,CUSTOM,VIEW,GLOBAL,CUSTOMMETA,REMOVETHEME,SUBTITLE,ABOUTBOX,HUGEP,LARGEP,MEDIUMP,SMALLP,PANELS,PANELSIZE,PANELNONE,PANELSYS,PANELIMAGE,PANELSTYLE,PANELFILE,PANELALPHA,PANELCOLOUR,STOPWORD};

enum helpwords
{HELP1,HELP2,HELP3,HELP4,HELP5,HELP6,HELP7,HELP8,HELP9,HELP10,HELP11,HELP12,HELP13,HELP14,HELP15,HELP16,HELP17,HELP18,HELP19,HELP20,HELPSTOP};

enum preSize {PREHUGE=256,PRELARGE=128,PREMEDIUM=64,PRESMALL=48};
enum {SCROLLBOX,VBOX,ICONVIEW};

extern const char*		folders[];
extern const char*		langStr[][STOPWORD];
extern const wchar_t*	helpStr[][HELPSTOP];
	
extern int				currentWallStyle;
extern char*			currentIconTheme;
extern char*			currentWMTheme;
extern char*			currentCursorTheme;
extern char*			currentWallPaper;
extern char*			currentGtkTheme;

extern char*			currentButtonLayout;
extern char*			currentTitlePos;
extern char*			currentWMFont;
extern char*			currentAppFont;
extern int				currentBright;
extern double			currentSatu;
extern int				currentCursSize;
extern char*			currentMetaTheme;

extern char*			originalGtkTheme;
extern char*			originalIconTheme;
extern char*			originalWMTheme;
extern char*			originalCursorTheme;
extern char*			originalWallpaper;
extern char*			originalMetaTheme;

extern char*			homeThemesHash;

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

extern int 				wallStyle;
extern GtkWidget*		layoutEntry;
extern GtkComboBoxText*	titlePos;
extern GtkWidget*		briteRange;
extern GtkWidget*		satuRange;
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

extern bool				noGui;
extern bool				updateDb;
extern bool				rebuildDb;

extern char*			cliTheme;
extern char*			cliControls;
extern char*			cliBorder;
extern char*			cliIcons;
extern char*			cliCursors;
extern char*			cliWallpaper;
extern char*			listParts;
extern char*			cliFileName;

extern void freeAndNull(char** ptr);
extern int positionToInt(char* pos);

int sizeDrop(bool toDrop,int data);
void getValue(const char* channel,const char* property,dataType type,void* ptr);
void setValue(const char* channel,const char* property,dataType type,void* ptr);
void freeAndSet(char** ptr,char* data);
char* getThemeNameFromDB(char* filepath);

#endif

