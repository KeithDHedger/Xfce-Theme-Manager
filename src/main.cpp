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

#include "globals.h"
#include "database.h"
#include "thumbnails.h"
#include "gui.h"
#include "callbacks.h"

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

GtkWidget*		progressWindow;
GtkWidget*		progressBar;
GtkWidget*		resetButton;
GtkWidget*		customButton;

// RESET THEME
void resetTheme(GtkWidget* widget,gpointer data)
{
	GtkSettings *settings=gtk_settings_get_default();;
	char*		satval;

	sprintf(generalBuffer,"%s\"%s\"",XCONFSETCONTROLS,currentGtkTheme);
	system(generalBuffer);
	sprintf(generalBuffer,"%s\"%s\"",XCONFSETFRAME,currentWmTheme);
	system(generalBuffer);
	sprintf(generalBuffer,"%s\"%s\"",XCONFSETICONS,currentIconTheme);
	system(generalBuffer);
	sprintf(generalBuffer,"%s\"%s\"",XCONFSETCURSOR,currentCursorTheme);
	system(generalBuffer);
	sprintf(generalBuffer,"%s\"%s\"",XCONFSETPAPER,currentWallPaper);
	system(generalBuffer);
	sprintf(generalBuffer,"%s%i",XCONFSETSTYLE,currentWallStyle);
	system(generalBuffer);
	sprintf(generalBuffer,"%s\"%s\"",XCONFSETLAYOUT,currentButtonLayout);
	system(generalBuffer);
	sprintf(generalBuffer,"%s\"%s\"",XCONFSETTITLEPOS,currentTitlePos);
	system(generalBuffer);
	sprintf(generalBuffer,"%s\"%s\"",XCONFSETWMFONT,currentWMFont);
	system(generalBuffer);
	sprintf(generalBuffer,"%s\"%s\"",XCONFSETAPPFONT,currentAppFont);
	system(generalBuffer);
	sprintf(generalBuffer,"%s%i",XCONFSETBRIGHT,currentBright);
	system(generalBuffer);
	satval=doubleToStr(currentSatu);
	sprintf(generalBuffer,"%s\"%s\"",XCONFSETSATU,satval);
	system(generalBuffer);
	sprintf(generalBuffer,"%s%i",XCONFSETCURSORSIZE,currentCursSize);
	system(generalBuffer);
	sprintf(generalBuffer,"%s\"%s\"",XMTSETMETATHEME,currentMetaTheme);
	system(generalBuffer);

	setValue(XCONFGETCONTROLS,STRING,&lastGtkTheme);
	setValue(XCONFGETICONS,STRING,&lastIconTheme);
	setValue(XCONFGETFRAME,STRING,&lastWmTheme);
	setValue(XCONFGETPAPER,STRING,&lastWallPaper);
	setValue(XCONFGETCURSOR,STRING,&lastCursorTheme);
	setValue(XCONFGETCURSOR,STRING,&lastMetaTheme);

	gtk_combo_box_set_active((GtkComboBox*)styleComboBox,currentWallStyle);
	gtk_entry_set_text((GtkEntry*)layoutEntry,currentButtonLayout);
	gtk_combo_box_set_active((GtkComboBox*)titlePos,positionToInt(currentTitlePos));
	gtk_font_button_set_font_name((GtkFontButton*)wmFontButton,currentWMFont);
	gtk_font_button_set_font_name((GtkFontButton*)appFontButton,currentAppFont);
	gtk_range_set_value((GtkRange*)briteRange,currentBright);
	gtk_range_set_value((GtkRange*)satuRange,currentSatu);
	gtk_range_set_value((GtkRange*)cursorSize,currentCursSize);

	g_object_set(settings,"gtk-theme-name",currentGtkTheme,"gtk-color-scheme","default",NULL);
	freeAndNull(&satval);
	rerunAndUpdate(false,true);
}

void shutdown(GtkWidget* widget,gpointer data)
{
	gtk_window_get_size((GtkWindow*)window,&winWid,&winHite);
	sprintf(generalBuffer,"%s%i",XMTSETWINWID,winWid);
	system(generalBuffer);
	sprintf(generalBuffer,"%s%i",XMTSETWINHITE,winHite);
	system(generalBuffer);
	gtk_main_quit();
}

void showAdvanced(GtkWidget* widget,gpointer data)
{
	gboolean	state=gtk_toggle_button_get_active((GtkToggleButton*)widget);

	gtk_widget_set_sensitive((GtkWidget*)previewComboBox,!state);
	gtk_widget_set_sensitive((GtkWidget*)resetButton,!state);
	gtk_widget_set_sensitive((GtkWidget*)customButton,!state);

	if (state==true)
		{
			gtk_notebook_set_current_page(advanced,1);
		}
	else
		{
			gtk_notebook_set_current_page(advanced,0);
		}
}

void init(void)
{
	gchar	*stdout=NULL;
	gchar	*stderr=NULL;
	gint   retval=0;

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
	
//gtk
	setValue(XCONFGETCONTROLS,STRING,&currentGtkTheme);
	setValue(XCONFGETCONTROLS,STRING,&lastGtkTheme);

//icons
	setValue(XCONFGETICONS,STRING,&currentIconTheme);
	setValue(XCONFGETICONS,STRING,&lastIconTheme);

//window manager
	setValue(XCONFGETTITLEPOS,STRING,&currentTitlePos);
	setValue(XCONFGETLAYOUT,STRING,&currentButtonLayout);
	setValue(XCONFGETFRAME,STRING,&currentWmTheme);
	setValue(XCONFGETFRAME,STRING,&lastWmTheme);

//font
	setValue(XCONFGETWMFONT,STRING,&currentWMFont);
	setValue(XCONFGETAPPFONT,STRING,&currentAppFont);

//backdrop
	setValue(XCONFGETBRIGHT,INT,&currentBright);
	setValue(XCONFGETSATU,FLOAT,&currentSatu);
	setValue(XCONFGETPAPER,STRING,&currentWallPaper);
	setValue(XCONFGETSTYLE,INT,&currentWallStyle);
	setValue(XCONFGETPAPER,STRING,&lastWallPaper);

//mouse
	setValue(XCONFGETCURSORSIZE,INT,&currentCursSize);
	setValue(XCONFGETCURSOR,STRING,&currentCursorTheme);
	setValue(XCONFGETCURSOR,STRING,&lastCursorTheme);

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
		}
//init my configs

	setValue(XMTGETSHOWSYSTEM,INT,&showGlobal);
	setValue(XMTGETSHOWMETA,INT,&showMeta);
	setValue(XMTGETSHOWGTK,INT,&showGtk);
	setValue(XMTGETSHOWWMB,INT,&showDecs);
	setValue(XMTGETSHOWCURSORS,INT,&showCursors);
	setValue(XMTGETSHOWICONS,INT,&showIcons);
	setValue(XMTGETSHOWPAPER,INT,&showBackdrop);
	setValue(XMTGETSHOWCUSTOM,INT,&showOnlyCustom);

	setValue(XMTGETMETATHEME,STRING,&currentMetaTheme);
	setValue(XMTGETMETATHEME,STRING,&lastMetaTheme);

	setValue(XMTGETWINWID,INT,&winWid);
	setValue(XMTGETWINHITE,INT,&winHite);

	setValue(XMTGETPRESIZE,INT,&previewSize);

	g_spawn_command_line_sync("which xfce4-composite-editor",&stdout,&stderr,&retval,NULL);
	if (retval==0)
		gotXCE=1;

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
	vbox=gtk_vbox_new(FALSE, 0);
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

int main(int argc,char **argv)
{
	GtkWidget*		vbox;
	GtkWidget*		buttonHbox;
	GtkWidget*		label;
	GtkWidget*		button;
	GtkWidget*		advancedScrollBox;
	gboolean		dbexists;
                                       
	if (argc==2 && g_ascii_strcasecmp(argv[1],"-v")==0)
		{
			printf("Xfce-Theme-Manager Version %s \nCopyright K.D.Hedger 2012, kdhedger@yahoo.co.uk\n",VERSION);
			return 0;
		}

#if GLIB_MINOR_VERSION < PREFERVERSION
	g_thread_init(NULL);
#endif
	gdk_threads_init();
	gtk_init(&argc, &argv);

	init();

	sprintf(generalBuffer,"%s/.config/XfceThemeManager",homeFolder);
	dbexists=g_file_test(generalBuffer,G_FILE_TEST_IS_DIR);

	if ((argc==2 && g_ascii_strcasecmp(argv[1],"-m")==0) || (dbexists==false))
		{
			makeProgressBar();

			gdk_threads_enter();
				g_timeout_add (100, updateBarTimer, NULL);

#if GLIB_MINOR_VERSION < PREFERVERSION
				g_thread_create(rebuildDB,(void*)0,false,NULL);
#else
				g_thread_new("redo",rebuildDB,NULL);
#endif

				gtk_main();
			gdk_threads_leave();
			gtk_widget_destroy(progressWindow);
		}

	if (argc==2 && g_ascii_strcasecmp(argv[1],"-u")==0)
			rebuildDB((void*)1);

#ifdef GOT_LIBXFCEUI
	window=xfce_titled_dialog_new();
	xfce_titled_dialog_set_subtitle((XfceTitledDialog*)window,_translate(SUBTITLE));
	vbox=gtk_dialog_get_content_area((GtkDialog *)window);
#else
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	vbox=gtk_vbox_new(FALSE, 0);
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

	wallpapersMainBox=gtk_vbox_new(false, 0);
	styleComboBox=(GtkComboBoxText*)gtk_combo_box_text_new();
	gtk_combo_box_text_append_text(styleComboBox,_translate(AUTO));
	gtk_combo_box_text_append_text(styleComboBox,_translate(CENTRED));
	gtk_combo_box_text_append_text(styleComboBox,_translate(TILED));
	gtk_combo_box_text_append_text(styleComboBox,_translate(STRETCH));
	gtk_combo_box_text_append_text(styleComboBox,_translate(SCALE));
	gtk_combo_box_text_append_text(styleComboBox,_translate(ZOOM));
	gtk_combo_box_set_active((GtkComboBox*)styleComboBox,currentWallStyle);
	g_signal_connect_after(G_OBJECT(styleComboBox),"changed",G_CALLBACK(wallStyleChanged),NULL);
	gtk_box_pack_start((GtkBox*)wallpapersMainBox,(GtkWidget*)styleComboBox,false,false,4);

	buildPages();

//notebook
	notebook=(GtkNotebook*)gtk_notebook_new();
	advanced=(GtkNotebook*)gtk_notebook_new();
 	gtk_notebook_set_show_tabs(advanced,false);
 
//pages
	label=gtk_label_new(_translate(THEMES));
//	gtk_notebook_append_page(notebook,previewBoxes[THEMES][VBOX],label);
	gtk_notebook_append_page(notebook,(GtkWidget*)previewBox[THEMES].vBox,label);
#if 0
	label=gtk_label_new(_translate(WMBORDERS));
	gtk_notebook_append_page(notebook,previewBoxes[WMBORDERS][VBOX],label);

	label=gtk_label_new(_translate(CONTROLS));
	gtk_notebook_append_page(notebook,previewBoxes[CONTROLS][VBOX],label);

	label=gtk_label_new(_translate(ICONS));
	gtk_notebook_append_page(notebook,previewBoxes[ICONS][VBOX],label);

	label=gtk_label_new(_translate(CURSORS));
	gtk_notebook_append_page(notebook,previewBoxes[CURSORS][VBOX],label);

	label=gtk_label_new(_translate(WALLPAPERS));
	gtk_notebook_append_page(notebook,previewBoxes[WALLPAPERS][VBOX],label);
#endif
	gtk_notebook_append_page(advanced,(GtkWidget*)notebook,NULL);

//do advanced gui
	advancedScrollBox=gtk_scrolled_window_new(NULL,NULL);
	buildAdvancedGui(advancedScrollBox);
	gtk_notebook_append_page(advanced,advancedScrollBox,NULL);

//add notebook to window
	gtk_container_add(GTK_CONTAINER(vbox),(GtkWidget*)advanced);

	gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(),false,false,4);
	gtk_box_pack_start(GTK_BOX(vbox),(GtkWidget*)previewComboBox,false,false,8);

//do buttons
	buttonHbox=gtk_hbox_new(true,0);

	resetButton=gtk_button_new_with_label(_translate(RESETTHEME));
	gtk_box_pack_start(GTK_BOX(buttonHbox),resetButton, false,false,0);
	g_signal_connect_after(G_OBJECT(resetButton),"clicked",G_CALLBACK(resetTheme),NULL);

	customButton=gtk_button_new_with_label(_translate(CUSTOMTHEME));
	gtk_box_pack_start(GTK_BOX(buttonHbox),customButton, false,false,0);
	g_signal_connect_after(G_OBJECT(customButton),"clicked",G_CALLBACK(customTheme),NULL);

	button=gtk_toggle_button_new_with_label(_translate(ADVANCED));
	gtk_box_pack_start(GTK_BOX(buttonHbox),button, false,false,0);
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(showAdvanced),NULL);

	gtk_box_pack_start(GTK_BOX(vbox),buttonHbox, false,false, 8);

	buttonHbox=gtk_hbox_new(true,0);
	button=gtk_button_new_from_stock(GTK_STOCK_QUIT);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(shutdown),NULL);

	gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(),false,false,0);

	gtk_box_pack_start(GTK_BOX(buttonHbox),button, false,false,8);
	gtk_box_pack_start(GTK_BOX(vbox),buttonHbox, false,false,8);

//do dnd
	gtk_drag_dest_set(vbox,GTK_DEST_DEFAULT_ALL,NULL,0,GDK_ACTION_COPY);
	gtk_drag_dest_add_uri_targets(vbox);
	g_signal_connect (G_OBJECT(vbox),"drag_data_received",G_CALLBACK(dropUri), NULL);

	doSetConfigs();

	g_signal_connect_after(G_OBJECT(window),"check-resize",G_CALLBACK(doResize),NULL);

	gtk_widget_show_all(window);
	gtk_main();
}


