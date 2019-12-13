/*
 *
 * ©K. D. Hedger. Tue 20 Oct 15:53:55 BST 2015 keithdhedger@gmail.com

 * This file (globals.cpp) is part of Xfce-Theme-Manager.

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


#include <stdlib.h>
#include <string.h>
#include <xfconf/xfconf.h>

#include "globals.h"

//current stuff
char*				currentIconTheme=NULL;
char*				currentWMTheme=NULL;
char*				currentCursorTheme=NULL;
char*				currentGtkTheme=NULL;
char*				currentButtonLayout;
char*				currentTitlePos;
char*				currentWMFont;
char*				currentAppFont;
int					currentCursSize;
char*				currentMetaTheme=NULL;

char*				homeThemesHash;
bool				initing=true;

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
GtkWidget*			screenNumber;

//walpaper style
int					numberOfMonitors;
int					currentMonitor;
monitorStruct*		monitorData[10];
monitorStruct*		revertMonitorData[10];

GtkWidget*			layoutEntry;
GtkComboBoxText*	titlePos;
GtkWidget*			briteRange;
GtkWidget*			satuRange;
GtkWidget*			spanMonitorsWidget;
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
int					spanMonitors=0;

bool				noGui=false;
bool				updateDb=false;
bool				rebuildDb=false;

const char*			folders[]={"meta","frames","controls","icons","cursors","wallpapers"};

const char*			langStr[][STOPWORD]={
{"Themes","Window Borders","Controls","Icons","Cursors","Wallpapers","Re-Build The Database","Rebuild DB","Launch Xfce-Composite-Editor","Backdrop Adjustments","Brightness","Saturation","Reset","Button Layout","Font Selection","WM Font","App Font","Cursor Size","Reset Theme","Save Theme","Advanced","Title Position","Enter Name for Theme...","Left","Centre","Right","Auto","Centered","Tiled","Stretched","Scaled","Zoomed","Custom","View Options","Show System Themes","Show Only Custom Themes","Delete Custom Theme","Integrated theme manager","An intergrated theme manager for Xfce 4.10","Huge Previews","Large Previews","Medium Previews","Small Previews","Panels","Panel Size:","None","Solid Colour","Image","Style:\t","File:\t\t","Alpha:\t","Colour:\t","Get Xfce4-Composite-Editor","Monitor","None","Span Monitors"},

{"Temas","Bordes De Ventana","Controles","Iconos","Cursores","Fondos De Pantalla","Re-Crear La Base De Datos","Reconstruir DB","Lanzar Xfce-Composite-Editor","Ajustes De Fondo De Escritorio","Brillo","Saturación","Reiniciar","Orden De Los Botones","Selección De Fuentes","Fuente De WM","Fuentes De Aplicación","Tamaño Del Cursor","Restablecer Tema","Guardar Tema","Avanzado","Posición Del Título","Ingrese el nombre del Tema...","Izquierda","Centro","Derecho","Auto","Centrado","Mosaico","Estirado","Escalado","Zoomed","Costumbre","Ver Opciones","Mostrar Temas del Sistema","Mostrar Sólo Temas Personalizados","Borrar Tema Personalizado","Un gestor integrado de temas","Un gestor de temas integrada para Xfce 4.10","Vista previa enorme","Vista previa grande","Vista previa mediana","Vista previa pequeña","Paneles","Tamaño del panel:","Ninguno","Color sólido","Imagen","Estilo:\t","Archivo:\t\t","Alfa:\t","Color:\t","Consíguelo Xfce4-Composite-Editor","Monitor","None","Span Monitors"},

{"Oberfläche","Fensterrahmen","Schaltflächen","Symbole","Mauszeiger","Hintergründe","Datenbank neu anlegen","DB erneuern","Xfce-Composite-Editor starten","Hintergrund-Anpassung","Helligkeit","Sättigung","Zurücksetzen","Anordnung der Schaltflächen","Schrift","Fensterschrift","Anwendungsschrift","Größe des Mauszeigers","Oberfläche zurücksetzen","Oberfläche speichern","Erweitert","Position des Fenstertitels","Name für Oberfläche eingeben...","Links","Mitte","Rechts","Automatisch","Zentriert","Gekachelt","Gestreckt","Skaliert","Vergrößert","Benutzerdefiniert","Anzeige-Optionen","System-Oberflächen Anzeigen","Nur benutzerdefinierte Oberflächen anzeigen","Benutzerdefinierte Oberfläche löschen","Eine integrierte Oberflächen-Verwaltung","Eine integrierte Oberflächen-Verwaltung für Xfce 4.10","Riesige Vorschaubilder","Große Vorschaubilder","Mittlere Vorschaubilder","Kleine Vorschaubilder","Panele","Panel-Größe:","Keine","Einfarbig","Bild","Stil:\t","Datei:\t\t","Alpha:\t","Farbe:\t","Herunterladen Xfce4-Composite-Editor","Bildschirm","None","Span Monitors"},

{"Style","Obramowania okien","Kontrolki","Ikony","Kursory","Tapety","Przebudowanie bazy danych","Przebudowanie bazy danych","Uruchom Xfce-Composite-Editor","Ustawienia tła","Jasność","Nasycenie","Reset","Położenie przycisków","Wybór czcionki","Czcionka menedżera okien","Czcionka aplikacji","Wielkość kursora","Resetowanie stylu","Zapisz styl","Zaawansowane","Pozycja tytułu okna","Wprowadź nazwę stylu","Lewo","Centrum","Prawo","Automatycznie","Wyśrodkowanie","Sąsiadująco","Rozciągnięcie","Przeskalowanie","Powiększenie","Własne","Opcje widoku","Pokaż style systemowe","Pokaż tylko własne style","Usuń własny styl","Zintegrowany menedżer stylów","Zintegrowany menedżer stylów dla Xfce 4.10","Ogromne","Duże","Średnie","Małe","Panele","Wielkość Panelu","Żaden","Stały Kolor","Obraz","Styl:\t\t","Plik:\t\t","Alfa:\t","Kolor:\t","Zdobądź Xfce4-Composite-Editor","Monitor","None","Span Monitors"},

{"Thèmes","Bourdures de fenêtres","Contrôles","Icônes","Curseurs","Fonds d'écran","Regénérer la base de données","Regénérer la BDD","Lancer Xfce-Composite-Editor","Ajustements de l'arrière plan","Luminosité","Saturation","Réinitialiser","Agencement des boutons","Sélection de la police","Gestionnaire de fenêtres","Applications","Taille du curseur","Réinitialiser le thème","Sauvegarder le thème","Avancés","Position du titre","Entrez le nom du thème...","Gauche","Centre","Droite","Auto","Centré","Mosaïque","Étiré","Adapté","Zoomé","Personnalisé","Options d'affichage","Afficher les thèmes système","N'afficher que les thèmes personnalisés","Supprimer le thème personnalisé","Gestionnaire de thèmes intégré","Un gestionnaire de thème intégrée pour Xfce 4.10","Très grands aperçus","Grands aperçus","Aperçus moyen","Petits aperçus","Tableau de bord","Dimension :","Aucun","Couleur pleine","Image","Style :\t","Ficher :\t\t","Opacité :\t","Couleur :\t","Procurez-vous Xfce4-Composite-Editor","Moniteur","None","Span Monitors"},

{"","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","None","Span Monitors"}

};

const wchar_t*		helpStr[][HELPSTOP]=
{
{L"Xfce-Theme-Manager, Version",L"Usage: xfce-theme-manager [option.1] ... [option.N]",L"OPTION\t\t\tUsage",L"-v, --version\t\tPrint version info and quit",L"-u, --update-db\t\tUpdate the database",L"-r, --build-db\t\tRe-build the database",L"-n, --nogui\t\tDon't run the GUI",L"-t, --theme=ARG\t\tSet the meta-theme to ARG",L"-c, --controls=ARG\tSet the controls theme to ARG",L"-w, --wmborder=ARG\tSet the window border to ARG",L"-i, --icons=ARG\t\tSet the icon theme to ARG",L"-p, --cursors=ARG\tSet the cursor theme to ARG",L"-b, --backdrop=ARG\tSet wallpaper to ARG",L"-l, --list=ARG\t\tList DB entry's, where ARG = any of \"*Ctwcib\"",L"Where 'C' prints custom themes, 't' prints themes,",L"'w' prints window borders, 'c' prints controls,",L"'i' prints icons and 'b' prints backdrops.",L"If the first/only character is a '*' then all entry's are printed.",L"-?, --help\t\tThis help",L"Options tcwipblvh? all imply -n",L"-m, --monitor=ARG\tSet which monitor to change the wallpaper on ( default is 0 )",L"-a, --panel=ARG\t\tSet which panel to change ( default is 1 )",L"-z, --panel-size=ARG\tSet panel size to ARG",L"-y, --panel-style=ARG\tSet panel style to ARG",L"-g, --panel-image=ARG\tSet path to panel image to ARG",L"-d, --panel-alpha=ARG\tSet panel alpha to ARG",L"-o, --panel-colour=ARG\tSet panel colour to ARG in hex format ie ff00ff",L"-e, --paper-style=ARG\tSet wallpaper style to ARG"},

{L"Xfce-Theme-Manager, Versión",L"Uso: xfce-theme-manager [opción.1] ... [opción.N]",L"OPCION\t\t\tUSO",L"-v, --version\t\tImprime información de la versión y sale",L"-u, --update-db\t\tActualiza la base de datos",L"-r, --build-db\t\tReconstruye la base de datos",L"-n, --nogui\t\tNo ejecuta la GUI",L"-t, --theme=ARG\t\tAjusta el metatema a ARG",L"-c, --controls=ARG\tAjusta el tema de controles a ARG",L"-w, --wmborder=ARG\tAjusta el tema de ventana a ARG",L"-i, --icons=ARG\t\tAjusta el tema de iconos a ARG",L"-p, --cursors=ARG\tAjusta el tema de cursor a ARG",L"-b, --backdrop=ARG\tAjusta el fondo de escritorio a ARG",L"-l, --list=ARG\t\tLista de las entradas de la base de datos, donde ARG = cualquiera de \"*Ctwcib\"",L"Donde 'C' imprime temas personalizados, 't' imprime temas,",L"'w' imprime bordes de pantalla, 'c' imprime controles,",L"'i' imprime iconos, y 'b' imprime fondos.",L"Si el primer/único caracter es un '*', entonces todas las entradas son impresas.",L"-?, --help\t\tImprime ayuda",L"Opciones tcwipblvh? todas implican -n",L"-m, --monitor=ARG\tDefine en cuál monitor cambiar el fondo de pantalla ( por defecto es 0 )",L"-a, --panel=ARG\t\tDefine cuál panel cambiar ( por defecto es 1 )",L"-z, --panel-size=ARG\tAjusta el tamaño del panel a ARG",L"-y, --panel-style=ARG\tAjusta el estilo del panel a ARG",L"-g, --panel-image=ARG\tAjusta la ruta de imagen del panel a ARG",L"-d, --panel-alpha=ARG\tAjusta el alfa del panel a ARG",L"-o, --panel-colour=ARG\tDefine el color del panel a ARG en formato hex, p.ej. ff00ff",L"-e, --paper-style=ARG\tDefine el estilo del fondo de pantalla a ARG"},

{L"Xfce-Theme-Manager, Version",L"Benutzung: xfce-theme-manager [Option.1] ... [Option.N]",L"OPTION\t\t\tBENUTZUNG",L"-v, --version\t\tZeigt nur Versionsinformationen",L"-u, --update-db\t\tAktualisiert die Datenbank",L"-r, --build-db\t\tErstellt die Datenbank neu",L"-n, --nogui\t\tStartet ohne grafische Benutzeroberfläche (GUI)",L"-t, --theme=ARG\t\tAktiviert die Meta-Oberfläche ARG",L"-c, --controls=ARG\tAktiviert das Steuerelement-Thema ARG",L"-w, --wmborder=ARG\tAktiviert das Fensterrahmen-Thema ARG",L"-i, --icons=ARG\t\tAktiviert das Symbolthema ARG",L"-p, --cursors=ARG\tAktiviert das Mauszeigerthema ARG",L"-b, --backdrop=ARG\tWählt ARG als Hintergrundbild",L"-l, --list=ARG\t\tZeigt die Einträge der Datenbank. ARG muss irgendein Zeichen aus \"*Ctwcib\" sein",L"'C' zeigt benutzerdefinierte Oberflächen, 't' zeigt Oberflächen,",L"'w' zeigt Fensterrahmen, 'c' zeigt Steuerelemente,",L"'i' zeigt  Symbole  und  'b' zeigt Hintergrundbilder.",L"Ist das erste Zeichen '*', werden alle Einträge gezeigt.",L"-?, --help\t\tZeigt die Hilfe",L"Die Optionen tcwipblvh? implizieren alle -n",L"-m, --monitor=ARG\tLegt fest, auf welchem Monitor das Hintergrundbild geändert werden soll ( Standard ist 0 )",L"-a, --panel=ARG\t\tLegt fest, welches Panel geändert wird ( Standard ist 1 )",L"-z, --panel-size=ARG\tSetzt Panel-Größe auf ARG",L"-y, --panel-style=ARG\tSetzt Panel-Stil auf ARG",L"-g, --panel-image=ARG\tSetzt den Pfad zum Panel-Hintergrundbild auf ARG",L"-d, --panel-alpha=ARG\tSetzt Alpha-Wert des Panels auf ARG",L"-o, --panel-colour=ARG\tSetzt Farbe des Panels auf ARG. ARG muss im Hexadezimalformat angegeben werden (z. B. ff00ff)",L"-e, --paper-style=ARG\tSetzt Stil des Hintergrundbilds auf ARG"},

{L"Xfce-Theme-Manager, wersja",L"Uzytkowanie: xfce-theme-manager [option.1] ... [option.N]",L"OPTION\t\t\tUSAGE",L"-v, --version\t\tDrukuje informacje i wychodzi.",L"-u, --update-db\t\tAktualizuje baze danych.",L"-r, --build-db\t\tPrzebudowuje baze danych.",L"-n, --nogui\t\tAplikacja nie uruchamia interfejsu graficznego.",L"-t, --theme=ARG\t\tUstaw meta-styl na ARG.",L"-c, --controls=ARG\tUstaw style kontrolek na ARG",L"-w, --wmborder=ARG\tUstaw styl obramowania okien na ARG.",L"-i, --icons=ARG\t\tUstaw style ikon na ARG.",L"-p, --cursors=ARG\tUstaw styl kursora na ARG.",L"-b, --backdrop=ARG\tUstaw tapete na ARG.",L"-l, --list=ARG\t\tPokaz wpisy w bazie danych, gdzie ARG = dowolny znak z \"*Ctwcib\".",L"Gdzie 'C' pokazuje wlasne style, 't' pokazuje style,",L"'w' pokazuje obramowania okien, 'c' pokazuje style kontrolek,",L"'i' pokazuje style ikon, a 'b' pokazuje tapety.",L"Jeżeli wpiszemy '*' to zostaną nam wyswietlone wszystkie wpisy.",L"-?, --help\t\tPokazuje pomoc.",L"Wszystkie opcje tcwipblvh? oznaczamy -n",L"-m, --monitor=ARG\tUstawia, na którym monitorze ma być zmieniana tapeta ( domyślnie jest 0 )",L"-a, --panel=ARG\t\tUstawia, który panel ma się zmieniać ( domyślnie jest 1 )",L"-z, --panel-size=ARG\tUstawia wielkość panelu na ARG",L"-y, --panel-style=ARG\tUstawia styl panelu na ARG",L"-g, --panel-image=ARG\tUstawia ścieżkę do obrazka panelu na ARG",L"-d, --panel-alpha=ARG\tUstawia kanał alfa panelu na ARG",L"-o, --panel-colour=ARG\tUstawia kolor panelu na ARG w formacie hex, np. ff00ff",L"-e, --paper-style=ARG\tUstawia styl tapety na ARG"},

{L"Xfce-Theme-Manager, Version",L"Utilisation : xfce-theme-manager [option.1] ... [option.N]",L"OPTION\t\t\tUtilisation",L"-v, --version\t\tAfficher les informations de version et quitter",L"-u, --update-db\t\tMettre à jour la base de données",L"-r, --build-db\t\tRegénérer la base de données",L"-n, --nogui\t\tNe pas lancer l'interface graphique",L"-t, --theme=ARG\t\tDéfinir le méta-thème à ARG",L"-c, --controls=ARG\tDéfinir le thème des contrôles à ARG",L"-w, --wmborder=ARG\tDéfinir le thème de bordure de fenêtres à ARG",L"-i, --icons=ARG\t\tDéfinir le thème d'icônes à ARG",L"-p, --cursors=ARG\tDéfinir le thème de curseur à ARG",L"-b, --backdrop=ARG\tDéfinir le fond d'écran à ARG",L"-l, --list=ARG\t\tLister les entrées de la BDD, où ARG peut être \"*Ctwcib\"",L"Où 'C' affiche les thèmes personnalisés, 't' affiche les thèmes,",L"'w' affiche les thèmes de bordure de fenêtres, 'c' affiche les thèmes des contrôles,",L"'i' affiche les thèmes d'icônes et 'b' affiche les fonds d'écran.",L"Si le premier/seul caractère est un '*' toutes les entrées sont affichées.",L"-?, --help\t\tCette aide",L"Les options tcwipblvh? équivalent toutes à -n",L"-m, --monitor=ARG\tDéfinir sur quel moniteur changer le fond d'écran ( 0 par défaut )",L"-a, --panel=ARG\t\tDéfinir quel tableau de bord modifier ( 1 par défaut )",L"-z, --panel-size=ARG\tDéfinir la taille de tableau de bord à ARG",L"-y, --panel-style=ARG\tDéfinir le style du tableau de bord à ARG",L"-g, --panel-image=ARG\tDéfinir le chemin vers l'image du tableau de bord à ARG",L"-d, --panel-alpha=ARG\tDéfinir l'opacité du tableau de bord à ARG",L"-o, --panel-colour=ARG\tDéfinir la couleur du tableau de bord à ARG en hexadécimal, soit ff00ff",L"-e, --paper-style=ARG\tDéfinir le style du fond d'écran à ARG"},


{L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"-",L"",L"",L"",L"",L""}


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
	int		booldata;

	XfconfChannel*	channelptr=xfconf_channel_get(channel);

	switch(type)
		{
			case INT:
				intdata=xfconf_channel_get_int(channelptr,property,-1);
				if(intdata!=-1)
					*(int*)ptr=intdata;
				break;

			case BOOLEAN:
				booldata=(int)xfconf_channel_get_bool(channelptr,property,-1);
				if(booldata!=-1)
					*(int*)ptr=booldata;
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

			case BOOLEAN:
				xfconf_channel_set_bool(channelptr,property,(bool)data);
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

char* slice(char* srcstring,int tmpstartchar,int tmpendchar)
{
	char*	dest;
	int		strsize;
	int		startchar=tmpstartchar;
	int		endchar=tmpendchar;

	if(tmpstartchar<0)
		startchar=0;

	if((tmpendchar<0) || (tmpendchar>(int)strlen(srcstring)))
		endchar=strlen(srcstring)-1;

	strsize=endchar-startchar+1;

	dest=(char*)malloc(strsize+1);
	strncpy(dest,(char*)&srcstring[startchar],strsize);
	dest[strsize]=0;

	return(dest);
}

char* sliceBetween(char* srcstring,char* startstr,char* endstr)
{
	int		startchar;
	int		endchar;
	char*	ptr;
	char*	dest=NULL;

	ptr=strstr(srcstring,startstr);
	if(ptr==NULL)
		return(NULL);
	startchar=(int)(long)ptr+strlen(startstr)-(long)srcstring;

	ptr=strstr((char*)&srcstring[startchar],endstr);
	if(ptr==NULL)
		return(NULL);
	endchar=(int)(long)ptr-(long)srcstring-1;

	dest=slice(srcstring,startchar,endchar);
	return(dest);
}


