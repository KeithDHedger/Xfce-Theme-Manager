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

#define _translate(x) langStr[langID][x]

enum words {THEMES=0,WMBORDERS,CONTROLS,ICONS,CURSORS,WALLPAPERS,REBUILDTHEDB,REBUILDDB,LAUNCHXCE,BACKDROPADJ,BRITE,SATU,RESET,BUTTONLAYOUT,FONTSELECT,WMFONT,APPFONT,CURSORSIZE,RESETTHEME,SAVETHEME,ADVANCED,TITLEPOS,STOPWORD};

//extern const char*			langStr[][22];

//ENGLISH="Themes;Window Borders;Controls;Icons;Cursors;Wallpapers;Re-Build The Database;Rebuild DB;Launch Xfce-Composite-Editor;Backdrop Adjustments;Brightness;Saturation;Reset;Button Layout;Font Selection;WM Font;App Font;Cursor Size;Reset Theme;Save Theme;Advanced;Title Position;END"

//SPANISH="Temas;Bordes De Ventana;Controles;Iconos;Cursores;Fondos De Pantalla;Re-Crear La Base De Datos;Reconstruir DB;Lanzar Xfce-Composite-Editor;Ajustes De Fondo De Escritorio;Brillo;Saturación;Reiniciar;Orden De Los Botones;Selección De Fuentes;Fuente De WM;Fuentes De Aplicación;Tamaño Del Cursor;Restablecer Tema;Guardar Tema;Avanzado;Posición Del Título;END"

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

extern GtkNotebook*	advanced;

extern int			controlHeight;
extern int			controlWidth;
extern GdkPixbuf*		controlsPixbuf;
extern GtkNotebook*	notebook;

extern char			generalBuffer[4096];

extern GdkPixbuf*		missingImage;
extern GdkPixbuf*		blankImage;

extern int			langID;

extern void freeAndNull(char** ptr);
extern int positionToInt(char* pos);

#endif

