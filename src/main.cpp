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
 * K.D.Hedger 2012 <kdheger@yahoo.co.uk>
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
}

void shutdown(GtkWidget* window,gpointer data)
{
	gtk_main_quit();
}

void showAdvanced(GtkWidget* widget,gpointer data)
{
	gboolean	state=gtk_toggle_button_get_active((GtkToggleButton*)widget);

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



	g_spawn_command_line_sync(XCONFGETSTYLE,&stdout,&stderr,&retval,NULL);

	if (retval==0)
		{
			stdout[strlen(stdout)-1]=0;
			currentWallStyle=atol(stdout);
		}

	freeAndNull(&stdout);
	freeAndNull(&stderr);

	g_spawn_command_line_sync(XCONFGETCONTROLS,&currentGtkTheme,&stderr,&retval,NULL);
	if (retval==0)
		currentGtkTheme[strlen(currentGtkTheme)-1]=0;
	freeAndNull(&stderr);
	
	g_spawn_command_line_sync(XCONFGETICONS,&currentIconTheme,&stderr,&retval,NULL);
	if (retval==0)
		currentIconTheme[strlen(currentIconTheme)-1]=0;
	freeAndNull(&stderr);

	g_spawn_command_line_sync(XCONFGETCURSOR,&currentCursorTheme,&stderr,&retval,NULL);
	if (retval==0)
		currentCursorTheme[strlen(currentCursorTheme)-1]=0;
	freeAndNull(&stderr);

	g_spawn_command_line_sync(XCONFGETFRAME,&currentWmTheme,&stderr,&retval,NULL);
	if (retval==0)
		currentWmTheme[strlen(currentWmTheme)-1]=0;

	g_spawn_command_line_sync(XCONFGETPAPER,&currentWallPaper,&stderr,&retval,NULL);
	if (retval==0)
			currentWallPaper[strlen(currentWallPaper)-1]=0;
	freeAndNull(&stderr);

	g_spawn_command_line_sync(XCONFGETLAYOUT,&currentButtonLayout,&stderr,&retval,NULL);
	if (retval==0)
		currentButtonLayout[strlen(currentButtonLayout)-1]=0;
	freeAndNull(&stderr);

	g_spawn_command_line_sync(XCONFGETTITLEPOS,&currentTitlePos,&stderr,&retval,NULL);
	if (retval==0)
		currentTitlePos[strlen(currentTitlePos)-1]=0;
	freeAndNull(&stderr);

	g_spawn_command_line_sync(XCONFGETWMFONT,&currentWMFont,&stderr,&retval,NULL);
	if (retval==0)
		currentWMFont[strlen(currentWMFont)-1]=0;
	freeAndNull(&stderr);

	g_spawn_command_line_sync(XCONFGETAPPFONT,&currentAppFont,&stderr,&retval,NULL);
	if (retval==0)
		currentAppFont[strlen(currentAppFont)-1]=0;
	freeAndNull(&stderr);

	g_spawn_command_line_sync(XCONFGETBRIGHT,&stdout,&stderr,&retval,NULL);
	if (retval==0)
		{
			stdout[strlen(stdout)-1]=0;
			currentBright=atoi(stdout);
		}
	freeAndNull(&stdout);
	freeAndNull(&stderr);

	g_spawn_command_line_sync(XCONFGETSATU,&stdout,&stderr,&retval,NULL);
	if (retval==0)
		{
			stdout[strlen(stdout)-1]=0;
			currentSatu=atof(stdout);
		}
	freeAndNull(&stdout);
	freeAndNull(&stderr);

	g_spawn_command_line_sync(XCONFGETCURSORSIZE,&stdout,&stderr,&retval,NULL);
	if (retval==0)
		{
			stdout[strlen(stdout)-1]=0;
			currentCursSize=atoi(stdout);
		}
	freeAndNull(&stdout);
	freeAndNull(&stderr);
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

	if (argc==2 && strcasecmp(argv[1],"-v")==0)
		{
			printf("Xfce-Theme-Manager Version %s \nCopyright K.D.Hedger 2012, kdhedger@yahoo.co.uk\n",VERSION);
			return 0;
		}

	g_thread_init(NULL);
	gdk_threads_init();
	gtk_init(&argc, &argv);

	init();


	if (argc==2 && strcasecmp(argv[1],"-m")==0)
		{
			makeProgressBar();

			gdk_threads_enter();
				g_timeout_add (100, updateBarTimer, NULL);
				g_thread_create(rebuildDB,(void*)0,false,NULL);
				gtk_main();
			gdk_threads_leave();
			gtk_widget_destroy(progressWindow);
		}

	if (argc==2 && strcasecmp(argv[1],"-u")==0)
			rebuildDB((void*)1);

	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size((GtkWindow*)window,400,470);
	g_signal_connect_after(G_OBJECT(window),"destroy",G_CALLBACK(shutdown),NULL);

//main window vbox
	vbox=gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window),(GtkWidget*)vbox);

	themesScrollBox=gtk_scrolled_window_new(NULL,NULL);
	framesScrollBox=gtk_scrolled_window_new(NULL,NULL);
	controlsScrollBox=gtk_scrolled_window_new(NULL,NULL);
	iconsScrollBox=gtk_scrolled_window_new(NULL,NULL);
	cursorsScrollBox=gtk_scrolled_window_new(NULL,NULL);
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
	gtk_notebook_append_page(notebook,themesScrollBox,label);

	label=gtk_label_new(_translate(WMBORDERS));
	gtk_notebook_append_page(notebook,framesScrollBox,label);

	label=gtk_label_new(_translate(CONTROLS));
	gtk_notebook_append_page(notebook,controlsScrollBox,label);

	label=gtk_label_new(_translate(ICONS));
	gtk_notebook_append_page(notebook,iconsScrollBox,label);

	label=gtk_label_new(_translate(CURSORS));
	gtk_notebook_append_page(notebook,cursorsScrollBox,label);

	label=gtk_label_new(_translate(WALLPAPERS));
	gtk_notebook_append_page(notebook,wallpapersMainBox,label);

	gtk_notebook_append_page(advanced,(GtkWidget*)notebook,NULL);

//do advanced gui
	advancedScrollBox=gtk_scrolled_window_new(NULL,NULL);
	buildAdvancedGui(advancedScrollBox);
	gtk_notebook_append_page(advanced,advancedScrollBox,NULL);

//add notebook to window
	gtk_container_add(GTK_CONTAINER(vbox),(GtkWidget*)advanced);

	gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(),false,false,4);

//do buttons
	buttonHbox=gtk_hbox_new(true,0);

	button=gtk_button_new_with_label(_translate(RESETTHEME));
	gtk_box_pack_start(GTK_BOX(buttonHbox),button, false,false,0);
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetTheme),NULL);

	button=gtk_button_new_with_label(_translate(CUSTOMTHEME));
	gtk_box_pack_start(GTK_BOX(buttonHbox),button, false,false,0);
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(customTheme),NULL);

	button=gtk_toggle_button_new_with_label(_translate(ADVANCED));
	gtk_box_pack_start(GTK_BOX(buttonHbox),button, false,false,0);
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(showAdvanced),NULL);

	gtk_box_pack_start(GTK_BOX(vbox),buttonHbox, false,false, 8);

	buttonHbox=gtk_hbox_new(true,0);
	button=gtk_button_new_from_stock(GTK_STOCK_QUIT);
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(shutdown),NULL);

	gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(),false,false,0);

	gtk_box_pack_start(GTK_BOX(buttonHbox),button, false,false,8);
	gtk_box_pack_start(GTK_BOX(vbox),buttonHbox, false,false,8);

//do dnd
	gtk_drag_dest_set(vbox,GTK_DEST_DEFAULT_ALL,NULL,0,GDK_ACTION_COPY);
	gtk_drag_dest_add_uri_targets(vbox);
	g_signal_connect (G_OBJECT(vbox),"drag_data_received",G_CALLBACK(dropUri), NULL);

	gtk_widget_show_all(window);
	gtk_main();
}
//
//gtkprev [border] /path/to/border /out/path/to/png
//gtkprev [controls] gtkthemename /out/path/to/png
//gtkprev [theme] gtkthemename /path/to/border /out/path/to/png
//gtkprev [cursors] cursortheme /out/path/to/png
//gtkprev [icons] icontheme /out/path/to/png
//gtkprev [custom] gtkthemename cursortheme icontheme /path/to/border /out/path/to/png
//gtkprev [fontpicker] "fontname"


