/*
 *
 * K.D.Hedger 2012 <kdhedger68713@gmail.com>
 *
 * Globals.cpp
 */
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <xfconf/xfconf.h>

#include "globals.h"

//current stuff
int					currentWallStyle;
char*				currentIconTheme=NULL;
char*				currentWMTheme=NULL;
char*				currentCursorTheme=NULL;
char*				currentWallPaper=NULL;
char*				currentGtkTheme=NULL;
char*				currentButtonLayout;
char*				currentTitlePos;
char*				currentWMFont;
char*				currentAppFont;
int					currentBright;
double				currentSatu;
int					currentCursSize;
char*				currentMetaTheme=NULL;

char*				homeThemesHash;

char*				originalGtkTheme=NULL;
char*				originalIconTheme=NULL;
char*				originalWMTheme=NULL;
char*				originalCursorTheme=NULL;
char*				originalWallpaper=NULL;
char*				originalMetaTheme=NULL;

boxStruct			previewBox[6]={{NULL,NULL,NULL,0,NULL,NULL}};

//db
char*				dbFolder;
char*				metaFolder;
char*				framesFolder;
char*				controlsFolder;
char*				iconsFolder;
char*				cursorsFolder;
char*				wallpapersFolder;
char*				customFolder;

//folders
char*				themesArray[2];
char*				iconsArray[2];
char*				papersArray[2];
char*				homeFolder;

char*				cursorTheme;
char*				iconTheme;

//widgets etc
GtkWidget*			appFontButton;
GtkWidget*			wmFontButton;
GtkWidget*			window;
GtkComboBoxText*	styleComboBox;
GtkComboBoxText*	previewComboBox;
GdkWindow*			gdkWindow;
GdkCursor*			watchCursor;

int 				wallStyle;
GtkWidget*			layoutEntry;
GtkComboBoxText*	titlePos;
GtkWidget*			briteRange;
GtkWidget*			satuRange;
GtkWidget*			cursorSize;

GtkWidget*			wallpapersMainBox=NULL;

//advanced
GtkNotebook*		advanced;
GtkWidget*			systemCheck;
GtkWidget*			metaCheck;
GtkWidget*			borderCheck;
GtkWidget*			gtkCheck;
GtkWidget*			iconsCheck;
GtkWidget*			cursorsCheck;
GtkWidget*			paperCheck;
GtkWidget*			onlyCustomCheck;

//panels
GtkWidget*			panelSelect;
GtkWidget*			panelStyleWidget;
GtkWidget*			panelSizeWidget;

GtkWidget*			panelImageBox;
GtkWidget*			panelColourBox;
GtkWidget*			panelAlphaBox;

GtkWidget*			panelAlphaWidget;
GtkWidget*			panelColourWidget;
GtkWidget*			panelImagePathWidget;

int					numOfPanels=-1;
panelData*			panels[10];
panelData*			revertPanels[10];
int					currentPanel=1;

int					controlHeight=64;
int					controlWidth=256;
GdkPixbuf*			controlsPixbuf;

GtkNotebook*		notebook;

char				generalBuffer[4096];

GdkPixbuf*			missingImage;
GdkPixbuf*			blankImage;
int					langID;

//config stuff
int					showGlobal=1;
int					showMeta=1;
int					showGtk=1;
int					showDecs=1;
int					showIcons=1;
int					showCursors=1;
int					showBackdrop=1;
int					showOnlyCustom=0;
int					winWid=420;
int					winHite=470;
int					gotXCE=0;
int					previewSize=128;

bool				noGui=false;
bool				updateDb=false;
bool				rebuildDb=false;

char*				cliTheme=NULL;
char*				cliControls=NULL;
char*				cliBorder=NULL;
char*				cliIcons=NULL;
char*				cliCursors=NULL;
char*				cliWallpaper=NULL;
char*				listParts=NULL;
char*				cliFileName=NULL;

const char*			folders[]={"meta","frames","controls","icons","cursors","wallpapers"};

const char*			langStr[][STOPWORD]={
{"Themes","Window Borders","Controls","Icons","Cursors","Wallpapers","Re-Build The Database","Rebuild DB","Launch Xfce-Composite-Editor","Backdrop Adjustments","Brightness","Saturation","Reset","Button Layout","Font Selection","WM Font","App Font","Cursor Size","Reset Theme","Save Theme","Advanced","Title Position","Enter Name for Theme...","Left","Centre","Right","Auto","Centered","Tiled","Stretched","Scaled","Zoomed","Custom","View Options","Show System Themes","Show Only Custom Themes","Delete Custom Theme","Integrated theme manager","An intergrated theme manager for Xfce 4.10","Huge Previews","Large Previews","Medium Previews","Small Previews","Panels","Panel Size:","None","Solid Colour","Image","Style:\t","File:\t\t","Alpha:\t","Colour:\t"},

{"Temas","Bordes De Ventana","Controles","Iconos","Cursores","Fondos De Pantalla","Re-Crear La Base De Datos","Reconstruir DB","Lanzar Xfce-Composite-Editor","Ajustes De Fondo De Escritorio","Brillo","Saturación","Reiniciar","Orden De Los Botones","Selección De Fuentes","Fuente De WM","Fuentes De Aplicación","Tamaño Del Cursor","Restablecer Tema","Guardar Tema","Avanzado","Posición Del Título","Ingrese el nombre del Tema...","Izquierda","Centro","Derecho","Auto","Centrado","Mosaico","Estirado","Escalado","Zoomed","Costumbre","Ver Opciones","Mostrar Temas del Sistema","Mostrar Sólo Temas Personalizados","Borrar Tema Personalizado","Un gestor integrado de temas","Un gestor de temas integrada para Xfce 4.10","Vista previa enorme","Vista previa grande","Vista previa mediana","Vista previa pequeña","Paneles","Tamaño del panel:","Ninguno","Color sólido","Imagen","Estilo:\t","Archivo:\t\t","Alfa:\t","Color:\t"},

{"Oberfläche","Fenster","Schaltflächen","Symbole","Mauszeiger","Hintergründe","Datenbank neu anlegen","DB erneuern","Xfce-Composite-Editor starten","Hintergrund-Anpassung","Helligkeit","Sättigung","Zurücksetzen","Anordnung der Schaltflächen","Schrift","Fensterschrift","Anwendungsschrift","Größe des Mauszeigers","Oberfläche Zurücksetzen","Speichern Oberfläche","Erweitert","Position des Fenstertitels","Name für Oberfläche eingeben...","Links","Mitte","Rechts","Automatisch","Zentriert","Gekachelt","Gestreckt","Skaliert","Vergrößert","Benutzerdefiniert","Anzeige-Optionen","System-Oberflächen Anzeigen","Nur benutzerdefinierte Oberflächen anzeigen","Benutzerdefinierte Oberfläche löschen","Eine integrierte Oberflächen-Verwaltung","Eine integrierte Oberflächen-Verwaltung für Xfce 4.10","Riesige Vorschaubilder","Große Vorschaubilder","Mittlere Vorschaubilder","Kleine Vorschaubilder","Panel","Panel-Größe:","Keine","Einfarbig","Bild","Stil:\t","Datei:\t\t","Alpha:\t","Farbe:\t"},

{"Style","Obramowania okien","Kontrolki","Ikony","Kursory","Tapety","Przebudowanie bazy danych","Przebudowanie bazy danych","Uruchom Xfce-Composite-Editor","Ustawienia tła","Jasność","Nasycenie","Reset","Położenie przycisków","Wybór czcionki","Czcionka menedżera okien","Czcionka aplikacji","Wielkość kursora","Resetowanie stylu","Zapisz styl","Zaawansowane","Pozycja tytułu okna","Wprowadź nazwę stylu","Lewo","Centrum","Prawo","Automatycznie","Wyśrodkowanie","Sąsiadująco","Rozciągnięcie","Przeskalowanie","Powiększenie","Własne","Opcje widoku","Pokaż style systemowe","Pokaż tylko własne style","Usuń własny styl","Zintegrowany menedżer stylów","Zintegrowany menedżer stylów dla Xfce 4.10","Ogromne","Duże","Średnie","Małe","Panele","Wielkość Panelu","Żaden","Stały Kolor","Obraz","Styl:\t\t","Plik:\t\t","Alfa:\t","Kolor:\t"}
};

const wchar_t*		helpStr[][HELPSTOP]=
{
{L"Xfce-Theme-Manager, Version",L"Usage: xfce-theme-manager [option.1] ... [option.N]",L"OPTION			Usage",L"-v, --version		Print version info and quit",L"-u, --update-db		Update the database",L"-r, --build-db		Re-build the database",L"-n, --nogui		Don't run the GUI",L"-t, --theme=ARG		Set the meta-theme to ARG",L"-c, --controls=ARG	Set the controls theme to ARG",L"-w, --wmborder=ARG	Set the window border to ARG",L"-i, --icons=ARG		Set the icon theme to ARG",L"-p, --cursors=ARG	Set the cursor theme to ARG",L"-b, --backdrop=ARG	Set wallpaper to ARG",L"-l, --list=ARG		List DB entry's, where ARG = any of \"*Ctwcib\"",L"Where 'C' prints custom themes, 't' prints themes,",L"'w' prints window borders, 'c' prints controls,",L"'i' prints icons and 'b' prints backdrops.",L"If the first/only character is a '*' then all entry's are printed.",L"-?, --help		This help",L"Options tcwipblvh? all imply -n"},

{L"Xfce-Theme-Manager, Versión",L"Uso: xfce-theme-manager [opción.1] ... [opción.N]",L"OPCION			USO",L"-v, --version		Imprime información de la versión y sale",L"-u, --update-db		Actualiza la base de datos",L"-r, --build-db		Reconstruye la base de datos",L"-n, --nogui		No ejecuta la GUI",L"-t, --theme=ARG		Ajusta el metatema a ARG",L"-c, --controls=ARG	Ajusta el tema de controles a ARG",L"-w, --wmborder=ARG	Ajusta el tema de ventana a ARG",L"-i, --icons=ARG		Ajusta el tema de iconos a ARG",L"-p, --cursors=ARG	Ajusta el tema de cursor a ARG",L"-b, --backdrop=ARG	Ajusta el fondo de escritorio a ARG",L"-l, --list=ARG		Lista de las entradas de la base de datos, donde ARG = cualquiera de \"*Ctwcib\"",L"Donde 'C' imprime temas personalizados, 't' imprime temas,",L"'w' imprime bordes de pantalla, 'c' imprime controles,",L"'i' imprime iconos, y 'b' imprime fondos.",L"Si el primer/único caracter es un '*', entonces todas las entradas son impresas.",L"-?, --help		Imprime ayuda",L"Opciones tcwipblvh? todas implican -n"},

{L"Xfce-Theme-Manager, Version",L"Benutzung: xfce-theme-manager [Option.1] ... [Option.N]",L"OPTION			BENUTZUNG",L"-v, --version		Zeigt nur Versionsinformationen",L"-u, --update-db		Aktualisiert die Datenbank",L"-r, --build-db		Erstellt die Datenbank neu",L"-n, --nogui		Starte ohne grafische Benutzeroberfläche (GUI)",L"-t, --theme=ARG		Aktiviert die Meta-Oberfläche ARG",L"-c, --controls=ARG	Aktiviert das Steuerelement-Thema ARG",L"-w, --wmborder=ARG	Aktiviert das Fensterrahmen-Thema ARG",L"-i, --icons=ARG		 Aktiviert das Symbolthema ARG",L"-p, --cursors=ARG	Aktiviert das Mauszeigerthema ARG",L"-b, --backdrop=ARG	Wählt ARG als Hintergrundbild",L"-l, --list=ARG		Zeigt die Einträge der Datenbank. ARG muss irgendein Zeichen aus \"*Ctwcib\" sein",L"'C' zeigt benutzerdefinierte Oberflächen, 't' zeigt Oberflächen,",L"'w' zeigt Fensterrahmen, 'c' zeigt Steuerelemente,",L"'i' zeigt  Symbole  und  'b' zeigt Hintergrundbilder.",L"Ist das erste Zeichen '*', werden alle Einträge gezeigt.",L"-?, --help		Zeigt die Hilfe",L"Die Optionen tcwipblvh? implizieren alle -n"},

{L"Xfce-Theme-Manager, wersja",L"Użytkowanie: xfce-theme-manager [option.1] ... [option.N]",L"OPTION			USAGE",L"-v, --version		Drukuje informacje i wychodzi.",L"-u, --update-db		Aktualizuje bazę danych.",L"-r, --build-db		Przebudowuje bazę danych.",L"-n, --nogui		Aplikacja nie uruchamia interfejsu graficznego.",L"-t, --theme=ARG		Ustaw meta-styl na ARG.",L"-c, --controls=ARG	Ustaw style kontrolek na ARG",L"-w, --wmborder=ARG	Ustaw styl obramowania okien na ARG.",L"-i, --icons=ARG		Ustaw style ikon na ARG.",L"-p, --cursors=ARG	Ustaw styl kursora na ARG.",L"-b, --backdrop=ARG	Ustaw tapetę na ARG.",L"-l, --list=ARG		Pokaż wpisy w bazie danych, gdzie ARG = dowolny znak z \"*Ctwcib\".",L"Gdzie 'C' pokazuje własne style, 't' pokazuje style,",L"'w' pokazuje obramowania okien, 'c' pokazuje style kontrolek,",L"'i' pokazuje style ikon, a 'b' pokazuje tapety.",L"Jeżeli wpiszemy '*' to zostaną wyświetlone wszystkie wpisy.",L"-?, --help		Pokazuje pomoc.",L"Opcje tcwipblvh? wszystko oznacza -n."}
};

void freeAndNull(char** ptr)
{
	if (*ptr!=NULL)
		{
			free(*ptr);
			*ptr=NULL;
		}
}

void freeAndSet(char** ptr,char* data)
{
	if(*ptr!=NULL)
		free(*ptr);
	*ptr=strdup(data);
}

int positionToInt(char* pos)
{
	if (pos!=NULL)
		{
			if(g_ascii_strcasecmp(pos,"left")==0)
				return(0);

			if(g_ascii_strcasecmp(pos,"center")==0)
				return(1);

			if(g_ascii_strcasecmp(pos,"right")==0)
				return(2);
		}
	else
		{
			asprintf(&currentTitlePos,"%s","center");
			setValue(XFWM,TITLEALIGNPROP,STRING,(void*)currentTitlePos);
		}
	return(1);
}

char* getThemeNameFromDB(char* filepath)
{
	GKeyFile*	keyfile=g_key_file_new();
	char*		dataset=NULL;

	if(g_key_file_load_from_file(keyfile,filepath,G_KEY_FILE_NONE,NULL))
		{
			dataset=g_key_file_get_string(keyfile,"Data","ThemeName",NULL);
		}

	if(keyfile!=NULL)
		g_key_file_free(keyfile);

	return(dataset);
}

void getValue(const char* channel,const char* property,dataType type,void* ptr)
{
	char*	data=NULL;
	int		intdata;
	double	floatdata;
	int		array[4]={-1,-1,-1,-1};

	XfconfChannel*	channelptr=xfconf_channel_get(channel);

	switch(type)
		{
			case INT:
				intdata=xfconf_channel_get_int(channelptr,property,-1);
				if(intdata!=-1)
					*(int*)ptr=intdata;
				break;

			case STRING:
				data=xfconf_channel_get_string(channelptr,property,"DEADBEEF");
				asprintf((char**)ptr,"%s",data);
				g_free(data);
				break;

			case FLOAT:
				floatdata=xfconf_channel_get_double(channelptr,property,-1);
				if(floatdata!=-1)
					*(double*)ptr=floatdata;
				break;
			case COLOURARRAY:
				xfconf_channel_get_array(channelptr,property,G_TYPE_UINT,&array[0],G_TYPE_UINT,&array[1],G_TYPE_UINT,&array[2],G_TYPE_UINT,&array[3],G_TYPE_INVALID);
				*((int*)ptr)=array[0];
				*((int*)ptr+1)=array[1];
				*((int*)ptr+2)=array[2];
				*((int*)ptr+3)=array[3];
				break;
		}
}

void setValue(const char* channel,const char* property,dataType type,void* data)
{
	XfconfChannel*	channelptr=xfconf_channel_get(channel);

	switch(type)
		{
			case INT:
				xfconf_channel_set_int(channelptr,property,(int)(long)data);
				break;

			case STRING:
				xfconf_channel_set_string(channelptr,property,(char*)data);
				break;

			case FLOAT:
				xfconf_channel_set_double(channelptr,property,*(gdouble*)data);
				break;

			case COLOURARRAY:
				break;
		}
}

int sizeDrop(bool toDrop,int data)
{
	if (toDrop==TRUE)
		{
			switch(data)
				{
					case PREHUGE:
						return(0);
						break;

					case 	PRELARGE:
						return(1);
						break;

					case PREMEDIUM:
						return(2);
						break;

					case PRESMALL:
						return(3);
						break;
				}
		}
	else
		{
			switch(data)
				{
					case 0:
						return(PREHUGE);
						break;

					case 1:
						return(PRELARGE);
						break;

					case 2:
						return(PREMEDIUM);
						break;

					case 3:
						return(PRESMALL);
						break;
				}
		}
	return(-1);
}


