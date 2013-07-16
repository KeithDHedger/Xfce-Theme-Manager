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
 * K.D.Hedger 2012 <kdhedger68713@gmail.com>
 *
 */

#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <sys/stat.h>
#include <getopt.h>
#include <locale.h>
#include <wchar.h>
#include <xfconf/xfconf.h>

#include "globals.h"
#include "database.h"
#include "thumbnails.h"
#include "gui.h"
#include "callbacks.h"
#include "panels.h"

#include "config.h"

#ifdef GOT_LIBXFCEUI
#include <libxfce4ui/libxfce4ui.h>
#endif

static const char* error_xpm[]=
	{
		"16 16 2 1",
		" 	c #FF0000",
		".	c #FFFFFF",
		" .............. ",
		". ............ .",
		".. .......... ..",
		"... ........ ...",
		".... ...... ....",
		"..... .... .....",
		"...... .. ......",
		".......  .......",
		".......  .......",
		"...... .. ......",
		"..... .... .....",
		".... ...... ....",
		"... ........ ...",
		".. .......... ..",
		". ............ .",
		" .............. "
	};

static const char * blank_xpm[]=
	{
		"16 16 1 1",
		" 	c None",
		"                ",
		"                ",
		"                ",
		"                ",
		"                ",
		"                ",
		"                ",
		"                ",
		"                ",
		"                ",
		"                ",
		"                ",
		"                ",
		"                ",
		"                ",
		"                "
	};

GtkWidget*	progressWindow;
GtkWidget*	progressBar;
GtkWidget*	resetButton;
GtkWidget*	customButton;

int			cliRetVal=0;
bool		doPrintHelp=false;

// RESET THEME
void resetTheme(GtkWidget* widget,gpointer data)
{
	double	d=1.0;

	gdk_window_set_cursor(gdkWindow,watchCursor); 

	freeAndSet(&currentMetaTheme,originalMetaTheme);
	setValue(XTHEMER,METATHEMEPROP,STRING,originalMetaTheme);

	setValue(XFWM,WMBORDERSPROP,STRING,originalWMTheme);
	freeAndSet(&currentWMTheme,originalWMTheme);

	setValue(XSETTINGS,CONTROLTHEMEPROP,STRING,originalGtkTheme);
	freeAndSet(&currentGtkTheme,originalGtkTheme);

	setValue(XSETTINGS,ICONTHEMEPROP,STRING,originalIconTheme);
	freeAndSet(&currentIconTheme,originalIconTheme);

	setValue(XSETTINGS,CURSORSPROP,STRING,originalCursorTheme);
	freeAndSet(&currentCursorTheme,originalCursorTheme);

	setValue(XFCEDESKTOP,PAPERSPROP,STRING,originalWallpaper);
	freeAndSet(&currentWallPaper,originalWallpaper);

	setValue(XFCEDESKTOP,BACKDROPSTYLEPROP,INT,(void*)(long)wallStyle);
	setValue(XFCEDESKTOP,BACKDROPBRIGHTPROP,INT,(void*)(long)currentBright);
	setValue(XFCEDESKTOP,BACKDROPSATUPROP,FLOAT,(void*)&d);

	setValue(XFWM,BUTTONLAYOUTPROP,STRING,(void*)currentButtonLayout);
	setValue(XFWM,TITLEALIGNPROP,STRING,(void*)currentTitlePos);
	setValue(XFWM,WMFONTPROP,STRING,(void*)currentWMFont);
	setValue(XSETTINGS,APPFONTPROP,STRING,(void*)currentAppFont);

	gtk_combo_box_set_active((GtkComboBox*)styleComboBox,currentWallStyle);
	gtk_entry_set_text((GtkEntry*)layoutEntry,currentButtonLayout);
	gtk_combo_box_set_active((GtkComboBox*)titlePos,positionToInt(currentTitlePos));
	gtk_font_button_set_font_name((GtkFontButton*)wmFontButton,currentWMFont);
	gtk_font_button_set_font_name((GtkFontButton*)appFontButton,currentAppFont);
	gtk_range_set_value((GtkRange*)briteRange,currentBright);
	gtk_range_set_value((GtkRange*)satuRange,currentSatu);
	gtk_range_set_value((GtkRange*)cursorSize,currentCursSize);

	rerunAndUpdate(false,true);

	gdk_window_set_cursor(gdkWindow,NULL);
	resetPanels();
}

void shutdown(GtkWidget* widget,gpointer data)
{
	gtk_window_get_size((GtkWindow*)window,&winWid,&winHite);
	setValue(XTHEMER,WINHITEPROP,INT,(void*)(long)winHite);
	setValue(XTHEMER,WINWIDPROP,INT,(void*)(long)winWid);
	xfconf_shutdown();
	gtk_main_quit();
}

void showAdvanced(GtkWidget* widget,gpointer data)
{
	gboolean	state=gtk_toggle_button_get_active((GtkToggleButton*)widget);

	gtk_widget_set_sensitive((GtkWidget*)previewComboBox,!state);
	gtk_widget_set_sensitive((GtkWidget*)resetButton,!state);
	gtk_widget_set_sensitive((GtkWidget*)customButton,!state);

	if (state==true)
		gtk_notebook_set_current_page(advanced,1);
	else
		gtk_notebook_set_current_page(advanced,0);
}

void init(void)
{
	gchar	*stdout=NULL;
	gchar	*stderr=NULL;
	gint   retval=0;

	setlocale(LC_ALL, "");

	homeFolder=(char*)g_get_home_dir();

	if(strcmp(getenv("HOME"),homeFolder)!=0)
		setenv("HOME",homeFolder,1);

	asprintf(&themesArray[0],"%s/.themes",homeFolder);
	asprintf(&themesArray[1],"%s",GLOBALTHEMES);
	
	asprintf(&iconsArray[0],"%s/.icons",homeFolder);
	asprintf(&iconsArray[1],"%s",GLOBALICONS);

	asprintf(&papersArray[0],"%s/.local/share/xfce4/backdrops",homeFolder);
	asprintf(&papersArray[1],"%s",GLOBALWALLPAPERS);

	asprintf(&dbFolder,"%s/.config/XfceThemeManager",homeFolder);
	asprintf(&metaFolder,"%s/meta",dbFolder);
	asprintf(&framesFolder,"%s/frames",dbFolder);
	asprintf(&controlsFolder,"%s/controls",dbFolder);
	asprintf(&iconsFolder,"%s/icons",dbFolder);
	asprintf(&cursorsFolder,"%s/cursors",dbFolder);
	asprintf(&wallpapersFolder,"%s/wallpapers",dbFolder);
	asprintf(&customFolder,"%s/custom",dbFolder);

	asprintf(&homeThemesHash,"12345");
	
//gtk
	getValue(XSETTINGS,CONTROLTHEMEPROP,STRING,&currentGtkTheme);
	getValue(XSETTINGS,CONTROLTHEMEPROP,STRING,&originalGtkTheme);

//icons
	getValue(XSETTINGS,ICONTHEMEPROP,STRING,&originalIconTheme);
	getValue(XSETTINGS,ICONTHEMEPROP,STRING,&currentIconTheme);

//window manager
	getValue(XFWM,TITLEALIGNPROP,STRING,&currentTitlePos);
	getValue(XFWM,BUTTONLAYOUTPROP,STRING,&currentButtonLayout);
	getValue(XFWM,WMBORDERSPROP,STRING,&originalWMTheme);
	getValue(XFWM,WMBORDERSPROP,STRING,&currentWMTheme);

//font
	getValue(XFWM,WMFONTPROP,STRING,&currentWMFont);
	getValue(XSETTINGS,APPFONTPROP,STRING,&currentAppFont);

//backdrop
	getValue(XFCEDESKTOP,PAPERSPROP,STRING,&currentWallPaper);
	getValue(XFCEDESKTOP,PAPERSPROP,STRING,&originalWallpaper);
	getValue(XFCEDESKTOP,BACKDROPSTYLEPROP,INT,&currentWallStyle);
	getValue(XFCEDESKTOP,BACKDROPBRIGHTPROP,INT,&currentBright);
	getValue(XFCEDESKTOP,BACKDROPSATUPROP,FLOAT,&currentSatu);

//mouse
	getValue(XSETTINGS,CURSORSPROP,STRING,&currentCursorTheme);
	getValue(XSETTINGS,CURSORSPROP,STRING,&originalCursorTheme);
	getValue(XSETTINGS,CURSORSIZEPROP,INT,&currentCursSize);

//metatheme
	getValue(XTHEMER,METATHEMEPROP,STRING,&currentMetaTheme);
	getValue(XTHEMER,METATHEMEPROP,STRING,&originalMetaTheme);

	missingImage=gdk_pixbuf_new_from_xpm_data((const char**)error_xpm);
	blankImage=gdk_pixbuf_new_from_xpm_data((const char**)blank_xpm);

	langID=ENGLISH;

	stdout=getenv("LANG");
	if (stdout!=NULL)
		{
			if(strncmp("es",stdout,2)==0)
				langID=SPANISH;
			if(strncmp("de",stdout,2)==0)
				langID=GERMAN;
			if(strncmp("pl",stdout,2)==0)
				langID=POLISH;
		}

//check hashses
	getValue(XTHEMER,HASHPROP,STRING,&homeThemesHash);

//init my configs
	getValue(XTHEMER,SHOWSYSTEMPROP,INT,&showGlobal);
	getValue(XTHEMER,SHOWMETAPROP,INT,&showMeta);
	getValue(XTHEMER,SHOWGTKPROP,INT,&showGtk);
	getValue(XTHEMER,SHOWWMBORDERPROP,INT,&showDecs);
	getValue(XTHEMER,SHOWICONSPROP,INT,&showIcons);
	getValue(XTHEMER,SHOWCURSORSPROP,INT,&showCursors);
	getValue(XTHEMER,SHOWBACKDROPSPROP,INT,&showBackdrop);
	getValue(XTHEMER,SHOWCUSTOMPROP,INT,&showOnlyCustom);

	getValue(XTHEMER,WINWIDPROP,INT,&winWid);
	getValue(XTHEMER,WINHITEPROP,INT,&winHite);
	getValue(XTHEMER,PREVSIZEPROP,INT,&previewSize);

	g_spawn_command_line_sync("which xfce4-composite-editor",&stdout,&stderr,&retval,NULL);
	if (retval==0)
		gotXCE=1;
			int	itemSize=previewSize+previewSize/2;

	for(int j=THEMES;j<WALLPAPERS;j++)
		{

			previewBox[j].scrollBox=(GtkScrolledWindow*)gtk_scrolled_window_new(NULL,NULL);
			gtk_scrolled_window_set_policy(previewBox[j].scrollBox,GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
			previewBox[j].vBox=(GtkVBox*)gtk_vbox_new(FALSE,0);
			previewBox[j].iconView=(GtkIconView*)gtk_icon_view_new();
			previewBox[j].itemCnt=0;
			previewBox[j].partIter=NULL;
			previewBox[j].store=gtk_list_store_new(3,GDK_TYPE_PIXBUF,G_TYPE_STRING,G_TYPE_STRING);

			gtk_icon_view_set_item_width(previewBox[j].iconView,itemSize);
			gtk_icon_view_set_item_padding(previewBox[j].iconView,0);
			gtk_icon_view_set_column_spacing(previewBox[j].iconView,0);
			gtk_icon_view_set_spacing(previewBox[j].iconView,0);

			gtk_icon_view_set_pixbuf_column(GTK_ICON_VIEW(previewBox[j].iconView),PIXBUF_COLUMN);
			gtk_icon_view_set_text_column(GTK_ICON_VIEW(previewBox[j].iconView),TEXT_COLUMN);

			gtk_icon_view_set_model(GTK_ICON_VIEW(previewBox[j].iconView),GTK_TREE_MODEL(previewBox[j].store));

			gtk_container_add((GtkContainer *)previewBox[j].scrollBox,(GtkWidget*)previewBox[j].iconView);
			gtk_box_pack_start((GtkBox*)previewBox[j].vBox,(GtkWidget*)previewBox[j].scrollBox,TRUE,TRUE,0);
		}

			previewBox[WALLPAPERS].scrollBox=(GtkScrolledWindow*)gtk_scrolled_window_new(NULL,NULL);
			gtk_scrolled_window_set_policy(previewBox[WALLPAPERS].scrollBox,GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
			previewBox[WALLPAPERS].vBox=(GtkVBox*)gtk_vbox_new(FALSE,0);
			previewBox[WALLPAPERS].iconView=(GtkIconView*)gtk_icon_view_new();
			previewBox[WALLPAPERS].itemCnt=0;
			previewBox[WALLPAPERS].partIter=NULL;
			previewBox[WALLPAPERS].store=gtk_list_store_new(3,GDK_TYPE_PIXBUF,G_TYPE_STRING,G_TYPE_STRING);

			gtk_icon_view_set_item_width(previewBox[WALLPAPERS].iconView,itemSize);
			gtk_icon_view_set_item_padding(previewBox[WALLPAPERS].iconView,0);
			gtk_icon_view_set_column_spacing(previewBox[WALLPAPERS].iconView,0);
			gtk_icon_view_set_spacing(previewBox[WALLPAPERS].iconView,0);

			gtk_icon_view_set_pixbuf_column(GTK_ICON_VIEW(previewBox[WALLPAPERS].iconView),PIXBUF_COLUMN);
			gtk_icon_view_set_text_column(GTK_ICON_VIEW(previewBox[WALLPAPERS].iconView),TEXT_COLUMN);

			gtk_icon_view_set_model(GTK_ICON_VIEW(previewBox[WALLPAPERS].iconView),GTK_TREE_MODEL(previewBox[WALLPAPERS].store));

			gtk_container_add((GtkContainer *)previewBox[WALLPAPERS].scrollBox,(GtkWidget*)previewBox[WALLPAPERS].iconView);


	styleComboBox=(GtkComboBoxText*)gtk_combo_box_text_new();
	gtk_combo_box_text_append_text(styleComboBox,_translate(AUTO));
	gtk_combo_box_text_append_text(styleComboBox,_translate(CENTRED));
	gtk_combo_box_text_append_text(styleComboBox,_translate(TILED));
	gtk_combo_box_text_append_text(styleComboBox,_translate(STRETCH));
	gtk_combo_box_text_append_text(styleComboBox,_translate(SCALE));
	gtk_combo_box_text_append_text(styleComboBox,_translate(ZOOM));
	gtk_combo_box_set_active((GtkComboBox*)styleComboBox,currentWallStyle);
	g_signal_connect_after(G_OBJECT(styleComboBox),"changed",G_CALLBACK(wallStyleChanged),NULL);

	gtk_box_pack_start((GtkBox*)previewBox[WALLPAPERS].vBox,(GtkWidget*)styleComboBox,FALSE,FALSE,2);
	gtk_box_pack_start((GtkBox*)previewBox[WALLPAPERS].vBox,gtk_hseparator_new(),FALSE,FALSE,1);
	gtk_box_pack_start((GtkBox*)previewBox[WALLPAPERS].vBox,(GtkWidget*)previewBox[WALLPAPERS].scrollBox,TRUE,TRUE,0);

	freeAndNull(&stdout);
	freeAndNull(&stderr);
}

void makeProgressBar(void)
{
	GtkWidget*		vbox;

	progressWindow=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(progressWindow,400,40);
	gtk_window_set_deletable((GtkWindow*)progressWindow,false);
	gtk_window_set_resizable((GtkWindow*)progressWindow,false);
	gtk_window_set_type_hint((GtkWindow*)progressWindow,GDK_WINDOW_TYPE_HINT_DIALOG);
	gtk_window_set_title((GtkWindow*)progressWindow,"Re-Building Database, Please Wait...");
	vbox=gtk_vbox_new(FALSE,0);
	progressBar=gtk_progress_bar_new();
	gtk_progress_bar_pulse((GtkProgressBar*)progressBar);

	gtk_progress_bar_set_orientation((GtkProgressBar*)progressBar,GTK_PROGRESS_LEFT_TO_RIGHT);

	gtk_box_pack_start(GTK_BOX(vbox),progressBar,false,false,8);
	gtk_container_add(GTK_CONTAINER(progressWindow),vbox);

	gtk_widget_show_all(progressWindow);
}

gboolean updateBarTimer(gpointer data)
{	
	if(GTK_IS_PROGRESS_BAR((GtkProgressBar*)progressBar))
		{
			gtk_progress_bar_pulse((GtkProgressBar*)progressBar);
			return(true);
		}
	else
		return(false);
}
//				cliRetVal|=doCliThemePart(cliControls,controlsFolder,XCONFSETCONTROLS);
int doCliThemePart(char* name,long what)
{

	char*	papername=NULL;

printf("name=%s\n",name);
	switch(what)
		{
			case WMBORDERS:
				setValue(XFWM,WMBORDERSPROP,STRING,name);
				setValue(XTHEMER,METATHEMEPROP,STRING,(void*)"DEADBEEF");
				return(0);
				break;
			case CONTROLS:
				setValue(XSETTINGS,CONTROLTHEMEPROP,STRING,name);
				setValue(XTHEMER,METATHEMEPROP,STRING,(void*)"DEADBEEF");
				return(0);
				break;
			case ICONS:
				setValue(XSETTINGS,ICONTHEMEPROP,STRING,name);
				setValue(XTHEMER,METATHEMEPROP,STRING,(void*)"DEADBEEF");
				return(0);
				break;
			case CURSORS:
				setValue(XSETTINGS,CURSORSPROP,STRING,name);
				setValue(XTHEMER,METATHEMEPROP,STRING,(void*)"DEADBEEF");
				return(0);
				break;
			case WALLPAPERS:
				for(int j=0;j<2;j++)
					{
						sprintf((char*)&generalBuffer,"%s/%i.%s.db",wallpapersFolder,j,name);
						papername=getThemeNameFromDB(generalBuffer);
						if(papername!=NULL)
							{
								setValue(XFCEDESKTOP,PAPERSPROP,STRING,papername);
								setValue(XTHEMER,METATHEMEPROP,STRING,(void*)"DEADBEEF");
								return(0);
							}
					}
				break;
		}
	return(1);
}

int doCliTheme(void)
{
	char* tn=NULL;			

	asprintf(&tn,"%s/%s.db",customFolder,cliTheme);
	if (g_file_test(tn,G_FILE_TEST_EXISTS))
		{
			doMeta(tn);
			freeAndNull(&tn);
			return(0);
		}
	else
		freeAndNull(&tn);

	for (int j=0;j<2;j++)
		{
			asprintf(&tn,"%s/%i.%s.db",metaFolder,j,cliTheme);
			if (g_file_test(tn,G_FILE_TEST_EXISTS))
				{
					doMeta(tn);
					freeAndNull(&tn);
					return(0);
				}
			else
				freeAndNull(&tn);
		}
	return(1);
}

void printName(const char* section,char* folderName)
{
	GDir*			folder=NULL;
	const gchar*	entry=NULL;

	printf("[%s]\n",section);
	folder=g_dir_open(folderName,0,NULL);
	if(folder!=NULL)
		{
			entry=g_dir_read_name(folder);
			while(entry!=NULL)
				{
					if(strstr(entry,".db"))
						{
							sprintf(generalBuffer,"%s\n",&entry[2]);
							generalBuffer[strlen(entry)-5]=0;
							printf("%s\n",generalBuffer);
						}
					entry=g_dir_read_name(folder);
				}
		}
	g_dir_close(folder);
}

void printList(void)
{
	GDir*			folder=NULL;
	const gchar*	entry=NULL;
	char*			what;

	if (listParts[0]=='*')
		what=(char*)"Ctcwipb";
	else
		what=listParts;

	for (unsigned int j=0;j<=strlen(what);j++)
		{
			if (what[j]=='C')
				{
					printf("[Custom Themes]\n");
					folder=g_dir_open(customFolder,0,NULL);
					if(folder!=NULL)
						{
							entry=g_dir_read_name(folder);
							while(entry!=NULL)
								{
									if(strstr(entry,".db"))
										{
											sprintf(generalBuffer,"%s\n",entry);
											generalBuffer[strlen(generalBuffer)-4]=0;
											printf("%s\n",generalBuffer);
										}
									entry=g_dir_read_name(folder);
								}
						}
					g_dir_close(folder);
				}

			if (what[j]=='t')
				printName("Themes",metaFolder);

			if (what[j]=='w')
				printName("Window Borders",framesFolder);

			if (what[j]=='c')
				printName("Controls",controlsFolder);

			if (what[j]=='i')
				printName("Icons",iconsFolder);

			if (what[j]=='p')
				printName("Cursors",cursorsFolder);

			if (what[j]=='b')
				printName("Wallpapers",wallpapersFolder);

		}
}

void doAbout(GtkWidget* widget,gpointer data)
{
	const char*	authors[]={"K.D.Hedger <"MYEMAIL">",NULL};
	const char	copyright[] ="Copyright \xc2\xa9 2012-2013 K.D.Hedger";
	const char*	aboutboxstring=_translate(ABOUTBOX);
	const char*	translators="Spanish translation:\nPablo Morales Romero <pg.morales.romero@gmail.com>.\n\nGerman translation:\nMartin F. Schumann. <mfs@mfs.name>\n\nPolish translation:\nMichał Olber (OSWorld) <redakcja@osworld.pl> ";

	gtk_show_about_dialog(NULL,"authors",authors,"translator-credits",translators,"comments",aboutboxstring,"copyright",copyright,"version",VERSION,"website",MYWEBSITE,"program-name","Xfce-Theme-Manager","logo-icon-name","xfce-theme-manager",NULL); 
}

void printhelp(void)
{
	printf("%ls %s\n",_translateHelp(HELP1),VERSION);
	printf("%ls\n",_translateHelp(HELP2));
	printf("%ls\n",_translateHelp(HELP3));
	printf("%ls\n",_translateHelp(HELP4));
	printf("%ls\n",_translateHelp(HELP5));
	printf("%ls\n",_translateHelp(HELP6));
	printf("%ls\n",_translateHelp(HELP7));
	printf("%ls\n",_translateHelp(HELP8));
	printf("%ls\n",_translateHelp(HELP9));
	printf("%ls\n",_translateHelp(HELP10));
	printf("%ls\n",_translateHelp(HELP11));
	printf("%ls\n",_translateHelp(HELP12));
	printf("%ls\n",_translateHelp(HELP13));
	printf("%ls\n",_translateHelp(HELP14));
	printf("			%ls\n",_translateHelp(HELP15));
	printf("			%ls\n",_translateHelp(HELP16));
	printf("			%ls\n",_translateHelp(HELP17));
	printf("			%ls\n",_translateHelp(HELP18));
	printf("%ls\n",_translateHelp(HELP19));
	printf("\n%ls\n",_translateHelp(HELP20));
}

struct option long_options[]=
	{
		{"version",0,0,'v'},
		{"update-db",0,0,'u'},
		{"rebuild-db",0,0,'r'},
		{"nogui",0,0,'n'},
		{"theme",1,0,'t'},
		{"controls",1,0,'c'},
		{"wmborder",1,0,'w'},
		{"icons",1,0,'i'},
		{"cursors",1,0,'p'},
		{"backdrop",1,0,'b'},
		{"list",1,0,'l'},
		{"save",1,0,'s'},
		{"help",0,0,'?'},
		{0, 0, 0, 0}
	};

int main(int argc,char **argv)
{
	GtkWidget*	vbox;
	GtkWidget*	buttonHbox;
	GtkWidget*	label;
	GtkWidget*	button;
	GtkWidget*	advancedScrollBox;
	gboolean	dbexists;
	int			c;
	int			fd;
	fpos_t		pos;

	while (1)
		{
			int option_index=0;
			c=getopt_long_only(argc,argv,":t:c:w:i:p:b:l:s:urnv?h",long_options,&option_index);

			if (c==-1)
				break;

			switch (c)
				{
					case '?':
					case 'h':
						doPrintHelp=true;
						break;

					case 'n':
						noGui=true;
						break;
			
					case 'r':
						rebuildDb=true;
						break;
			
					case 'u':
						updateDb=true;
						break;

					case 'l':
						listParts=optarg;
						noGui=true;
						break;

					case 'v':
						printf("Xfce-Theme-Manager Version %s \nCopyright K.D.Hedger 2012, %s\n",VERSION,MYEMAIL);
						return 0;
						break;

					case 't':
						noGui=true;
						cliTheme=optarg;
						break;

					case 'c':
						noGui=true;
						cliControls=optarg;
						break;

					case 'w':
						noGui=true;
						cliBorder=optarg;
						break;

					case 'i':
						noGui=true;
						cliIcons=optarg;
						break;

					case 'p':
						noGui=true;
						cliCursors=optarg;
						break;

					case 'b':
						noGui=true;
						cliWallpaper=optarg;
						break;

					case 's':
						cliFileName=optarg;
						noGui=true;
						break;

					default:
						printf ("?? Unknown argument ??\n");
						return 1;
						break;
			}
		}

	fflush(stderr);
	fgetpos(stderr,&pos);
	fd=dup(fileno(stderr));
	freopen("/dev/null","w",stderr);
  
#if GLIB_MINOR_VERSION < PREFERVERSION
	g_thread_init(NULL);
#endif
	gdk_threads_init();
	gtk_init(&argc,&argv);
	xfconf_init(NULL);

	init();

	if(doPrintHelp==true)
		{
			printhelp();
			return 0;
		}

	if(checkFolders()!=0)
		updateDb=true;

	sprintf(generalBuffer,"%s/.config/XfceThemeManager",homeFolder);
	dbexists=g_file_test(generalBuffer,G_FILE_TEST_IS_DIR);

	if ((rebuildDb==true) ||  (dbexists==false))
		{
			if (noGui==false)
				{
					makeProgressBar();
					gdk_threads_enter();
						g_timeout_add (100,updateBarTimer,NULL);

#if GLIB_MINOR_VERSION < PREFERVERSION
						g_thread_create(rebuildDB,(void*)0,false,NULL);
#else
						g_thread_new("redo",rebuildDB,NULL);
#endif

						gtk_main();
					gdk_threads_leave();
					gtk_widget_destroy(progressWindow);
				}
			else
				{
					rebuildDB((void*)0);
					return(0);
				}
		}

	if (updateDb==true)
		{
			rebuildDB((void*)1);
			if (noGui==true)
				return(0);
		}

	if (noGui==false)
		{
#ifdef GOT_LIBXFCEUI
			window=xfce_titled_dialog_new();
			xfce_titled_dialog_set_subtitle((XfceTitledDialog*)window,_translate(SUBTITLE));
			vbox=gtk_dialog_get_content_area((GtkDialog *)window);
#else
			window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
			vbox=gtk_vbox_new(FALSE,0);
			gtk_container_add(GTK_CONTAINER(window),(GtkWidget*)vbox);
#endif

			previewComboBox=(GtkComboBoxText*)gtk_combo_box_text_new();
			gtk_combo_box_text_append_text(previewComboBox,_translate(HUGEP));
			gtk_combo_box_text_append_text(previewComboBox,_translate(LARGEP));
			gtk_combo_box_text_append_text(previewComboBox,_translate(MEDIUMP));
			gtk_combo_box_text_append_text(previewComboBox,_translate(SMALLP));

			gtk_combo_box_set_active((GtkComboBox*)previewComboBox,sizeDrop(true,previewSize));
			g_signal_connect_after(G_OBJECT(previewComboBox),"changed",G_CALLBACK(previewSizeChanged),NULL);

			gtk_window_set_position((GtkWindow*)window,GTK_WIN_POS_CENTER);
			gtk_window_set_default_size((GtkWindow*)window,winWid,winHite);
			gtk_window_set_title((GtkWindow*)window,"Xfce Theme Manager");

			gtk_window_set_icon_name((GtkWindow*)window,"preferences-desktop-theme");
			g_signal_connect(G_OBJECT(window),"delete-event",G_CALLBACK(shutdown),NULL);

//main window vbox
			buildPages();
//notebook
			notebook=(GtkNotebook*)gtk_notebook_new();
			advanced=(GtkNotebook*)gtk_notebook_new();
		 	gtk_notebook_set_show_tabs(advanced,false);
 
//pages
			label=gtk_label_new(_translate(THEMES));
			gtk_notebook_append_page(notebook,(GtkWidget*)previewBox[THEMES].vBox,label);

			label=gtk_label_new(_translate(WMBORDERS));
			gtk_notebook_append_page(notebook,(GtkWidget*)previewBox[WMBORDERS].vBox,label);

			label=gtk_label_new(_translate(CONTROLS));
			gtk_notebook_append_page(notebook,(GtkWidget*)previewBox[CONTROLS].vBox,label);

			label=gtk_label_new(_translate(ICONS));
			gtk_notebook_append_page(notebook,(GtkWidget*)previewBox[ICONS].vBox,label);

			label=gtk_label_new(_translate(CURSORS));
			gtk_notebook_append_page(notebook,(GtkWidget*)previewBox[CURSORS].vBox,label);

			label=gtk_label_new(_translate(WALLPAPERS));
			gtk_notebook_append_page(notebook,(GtkWidget*)previewBox[WALLPAPERS].vBox,label);

			gtk_notebook_append_page(advanced,(GtkWidget*)notebook,NULL);

//do advanced gui
			advancedScrollBox=gtk_scrolled_window_new(NULL,NULL);
			buildAdvancedGui(advancedScrollBox);
			gtk_notebook_append_page(advanced,advancedScrollBox,NULL);

//add notebook to window
			gtk_container_add(GTK_CONTAINER(vbox),(GtkWidget*)advanced);
			gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(),false,false,4);

//do buttons
			buttonHbox=gtk_hbox_new(false,8);

			gtk_box_pack_start(GTK_BOX(buttonHbox),(GtkWidget*)previewComboBox,true,true,4);

			resetButton=gtk_button_new_with_label(_translate(RESETTHEME));
			gtk_box_pack_start(GTK_BOX(buttonHbox),resetButton,false,false,0);
			g_signal_connect_after(G_OBJECT(resetButton),"clicked",G_CALLBACK(resetTheme),NULL);

			customButton=gtk_button_new_with_label(_translate(CUSTOMTHEME));
			gtk_box_pack_start(GTK_BOX(buttonHbox),customButton,false,false,0);
			g_signal_connect_after(G_OBJECT(customButton),"clicked",G_CALLBACK(customTheme),NULL);

			button=gtk_toggle_button_new_with_label(_translate(ADVANCED));
			gtk_box_pack_start(GTK_BOX(buttonHbox),button,false,false,4);
			g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(showAdvanced),NULL);

			gtk_box_pack_start(GTK_BOX(vbox),buttonHbox,false,false,8);
			buttonHbox=gtk_hbox_new(false,0);

			button=gtk_button_new_from_stock(GTK_STOCK_ABOUT);
			g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(doAbout),NULL);
			gtk_box_pack_start(GTK_BOX(buttonHbox),button,false,false,4);

			button=gtk_button_new_from_stock(GTK_STOCK_CLOSE);
			g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(shutdown),NULL);

			gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(),false,false,8);
			gtk_box_pack_start(GTK_BOX(buttonHbox),gtk_hbox_new(false,0),true,true,0);

			gtk_box_pack_start(GTK_BOX(buttonHbox),button,false,false,4);
			gtk_box_pack_start(GTK_BOX(vbox),buttonHbox,false,false,0);

//do dnd
			gtk_drag_dest_set(vbox,GTK_DEST_DEFAULT_ALL,NULL,0,GDK_ACTION_COPY);
			gtk_drag_dest_add_uri_targets(vbox);
			g_signal_connect (G_OBJECT(vbox),"drag_data_received",G_CALLBACK(dropUri),NULL);

			doSetConfigs();

			g_signal_connect_after(G_OBJECT(window),"check-resize",G_CALLBACK(doResize),(void*)0xdeadbeef);

			gtk_widget_show_all(window);
	
			gtk_widget_set_size_request(window,300,400);

			gdkWindow=gtk_widget_get_window(GTK_WIDGET(window));
			watchCursor=gdk_cursor_new(GDK_WATCH);

			g_signal_connect(G_OBJECT(notebook),"switch-page",G_CALLBACK(doChangePage),NULL);


			gtk_main();

			fflush(stderr);
			dup2(fd,fileno(stderr));
			close(fd);
			clearerr(stderr);
			fsetpos(stderr, &pos);
		}
	else
		{
			if (listParts!=NULL)
				{
					printList();
					return(0);
				}
			populatePanels();

			if (cliControls!=NULL)
				cliRetVal|=doCliThemePart(cliControls,CONTROLS);

			if (cliBorder!=NULL)
				cliRetVal|=doCliThemePart(cliBorder,WMBORDERS);

			if (cliIcons!=NULL)
				{
					cliRetVal|=doCliThemePart(cliIcons,ICONS);
					system("xfdesktop --reload");
				}

			if (cliCursors!=NULL)
				cliRetVal|=doCliThemePart(cliCursors,CURSORS);

			if (cliWallpaper!=NULL)
				cliRetVal|=doCliThemePart(cliWallpaper,WALLPAPERS);


			if (cliFileName!=NULL)
				customTheme(NULL,NULL);

			if (cliTheme!=NULL)
				cliRetVal=doCliTheme();

			return(cliRetVal);
		}
}


