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

bool			whoops=false;
GtkWidget*		progressWindow;
GtkWidget*		progressBar;
int 			wallStyle;
GtkComboBoxText*	comboBox;
GtkNotebook*	advanced;

void respond(GtkFontSelectionDialog* dialog,gint response,gpointer data)
{
	gchar* font;

	switch(response)
		{
			case (GTK_RESPONSE_APPLY):
			case (GTK_RESPONSE_OK):
				font=gtk_font_selection_dialog_get_font_name(dialog);
				printf("%s\n",font);
				g_free(font);
				break;
			default:
				whoops=true;
		}

	gtk_main_quit();
}

void pickfont(char* currentname)
{
	GtkWidget*	dialog;
	
	dialog=gtk_font_selection_dialog_new("Please Pick A Font");
	gtk_font_selection_dialog_set_font_name(GTK_FONT_SELECTION_DIALOG(dialog),currentname);
	gtk_font_selection_dialog_set_preview_text(GTK_FONT_SELECTION_DIALOG(dialog),"The Quick Brown Fox Jumped Over The Lazy Dog");
	g_signal_connect_after(G_OBJECT(dialog),"response",G_CALLBACK(respond), NULL);

	gtk_widget_show_all(dialog);
	gtk_main();

	gtk_widget_destroy(GTK_WIDGET(dialog));

	if(whoops==true)
		printf("%s\n",currentname);

	return;
}

//*******************************************************************
//
//	FRAMES
//
void doFrame(GtkWidget* widget,gpointer data)
{


	GKeyFile*	keyfile=g_key_file_new();
	char*		command;
	char*		frameset;

	if(g_key_file_load_from_file(keyfile,gtk_widget_get_name(widget),G_KEY_FILE_NONE,NULL))
		{
			frameset=g_key_file_get_string(keyfile,"Data","Xfwm4Theme",NULL);

			if(frameset!=NULL)
				{
					asprintf(&command,"%s\"%s\"",XCONFSETFRAME,frameset);
					system(command);
					free(command);
					free(frameset);
				}
		}
	g_key_file_free(keyfile);
}
//

//*******************************************************************
//
//	CONTROLS
//
void doControls(GtkWidget* widget,gpointer data)
{
	GKeyFile*	keyfile=g_key_file_new();
	char*		command;
	char*		controlset;
	GtkSettings *settings=gtk_settings_get_default();;

	if(g_key_file_load_from_file(keyfile,gtk_widget_get_name(widget),G_KEY_FILE_NONE,NULL))
		{
			controlset=g_key_file_get_string(keyfile,"Data","GtkTheme",NULL);

			if(controlset!=NULL)
				{
					asprintf(&command,"%s\"%s\"",XCONFSETCONTROLS,controlset);
					system(command);
					g_object_set(settings,"gtk-theme-name",controlset,"gtk-color-scheme","default",NULL);
					free(command);
					free(controlset);
				}
		}
	g_key_file_free(keyfile);
}
//
//*******************************************************************


//*******************************************************************
//
//	META
//
void doMeta(GtkWidget* widget,gpointer data)
{
	GKeyFile*	keyfile=g_key_file_new();
	char*		command;
	char*		cursorset;
	char*		gtkset;
	char*		frameset;
	char*		iconset;
	char*		paperset;

	GtkSettings *settings=gtk_settings_get_default();;

	if(g_key_file_load_from_file(keyfile,gtk_widget_get_name(widget),G_KEY_FILE_NONE,NULL))
		{
			gtkset=g_key_file_get_string(keyfile,"Data","GtkTheme",NULL);
			frameset=g_key_file_get_string(keyfile,"Data","Xfwm4Theme",NULL);
			iconset=g_key_file_get_string(keyfile,"Data","IconTheme",NULL);	
			cursorset=g_key_file_get_string(keyfile,"Data","CursorTheme",NULL);	
			paperset=g_key_file_get_string(keyfile,"Data","BackgroundImage",NULL);	
		
			if(gtkset!=NULL)
				{
					asprintf(&command,"%s\"%s\"",XCONFSETCONTROLS,gtkset);
					system(command);
					g_object_set(settings,"gtk-theme-name",gtkset,"gtk-color-scheme","default",NULL);
					free(command);
					free(gtkset);
				}
			if(frameset!=NULL)
				{
					asprintf(&command,"%s\"%s\"",XCONFSETFRAME,frameset);
					system(command);
					free(command);
					free(frameset);
				}
			if(iconset!=NULL)
				{
					asprintf(&command,"%s\"%s\"",XCONFSETICONS,iconset);
					system(command);
					free(command);
					free(iconset);
				}
			if(cursorset!=NULL)
				{
					asprintf(&command,"%s\"%s\"",XCONFSETCURSOR,cursorset);
					system(command);
					free(command);
					free(cursorset);
				}
			if(paperset!=NULL)
				{
					asprintf(&command,"%s\"%s\"",XCONFSETPAPER,paperset);
					system(command);
					free(command);
					free(paperset);
			}
		}
	system("xfdesktop --reload");
	g_key_file_free(keyfile);
}
//
//*******************************************************************

//*******************************************************************
//
//	ICONS
//

void doIcons(GtkWidget* widget,gpointer data)
{
	GKeyFile*	keyfile=g_key_file_new();
	char*		command;
	char*		iconset;

	if(g_key_file_load_from_file(keyfile,gtk_widget_get_name(widget),G_KEY_FILE_NONE,NULL))
		{
			iconset=g_key_file_get_string(keyfile,"Data","IconTheme",NULL);

			if(iconset!=NULL)
				{
					asprintf(&command,"%s\"%s\"",XCONFSETICONS,iconset);
					system(command);
					free(command);
					free(iconset);
				}
		}
	system("xfdesktop --reload");
	g_key_file_free(keyfile);
}
//
//*******************************************************************

//*******************************************************************
//
//	CURSORS
//
void doCursors(GtkWidget* widget,gpointer data)
{
	GKeyFile*	keyfile=g_key_file_new();
	char*		command;
	char*		cursorset;

	if(g_key_file_load_from_file(keyfile,gtk_widget_get_name(widget),G_KEY_FILE_NONE,NULL))
		{
			cursorset=g_key_file_get_string(keyfile,"Data","CursorTheme",NULL);

			if(cursorset!=NULL)
				{
					asprintf(&command,"%s\"%s\"",XCONFSETCURSOR,cursorset);
					system(command);
					free(command);
					free(cursorset);
				}
		}
	g_key_file_free(keyfile);
}
//
//*******************************************************************

//*******************************************************************
//
//	WALPAPERS
//

void setWallStyle()
{
	char*	command;

	asprintf(&command,"%s%i",XCONFSETSTYLE,wallStyle);
	system(command);
}

void wallStyleChanged(GtkWidget* widget,gpointer data)
{
	wallStyle=gtk_combo_box_get_active((GtkComboBox*)widget);
	setWallStyle();
}

void doWallpapers(GtkWidget* widget,gpointer data)
{
	GKeyFile*	keyfile=g_key_file_new();
	char*		command;
	char*		paperset;

	if(g_key_file_load_from_file(keyfile,gtk_widget_get_name(widget),G_KEY_FILE_NONE,NULL))
		{
			paperset=g_key_file_get_string(keyfile,"Data","BackgroundImage",NULL);

			if(paperset!=NULL)
				{
					asprintf(&command,"%s\"%s\"",XCONFSETPAPER,paperset);
					system(command);
					free(command);
					free(paperset);
				}
		}
	g_key_file_free(keyfile);
}
//
//*******************************************************************

//*******************************************************************
//
// RESET THEME
void resetTheme(GtkWidget* widget,gpointer data)
{
	char		command[256];
	GtkSettings *settings=gtk_settings_get_default();;

	sprintf(command,"%s\"%s\"",XCONFSETCONTROLS,currentGtkTheme);
	system(command);
	sprintf(command,"%s\"%s\"",XCONFSETFRAME,currentWmTheme);
	system(command);
	sprintf(command,"%s\"%s\"",XCONFSETICONS,currentIconTheme);
	system(command);
	sprintf(command,"%s\"%s\"",XCONFSETCURSOR,currentCursorTheme);
	system(command);
	sprintf(command,"%s\"%s\"",XCONFSETPAPER,currentWallPaper);
	system(command);
	sprintf(command,"%s%i",XCONFSETSTYLE,currentWallStyle);
	system(command);

	g_object_set(settings,"gtk-theme-name",currentGtkTheme,"gtk-color-scheme","default",NULL);
	gtk_combo_box_set_active((GtkComboBox*)comboBox,currentWallStyle);
}

GtkWidget *imageBox(char* filename,char* text)
{
	GtkWidget*	box;
	GtkWidget*	label;
	GtkWidget*	image;

    /* Create box for image and label */
	box=gtk_vbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER (box), 2);

	image=gtk_image_new_from_file(filename);
	label=gtk_label_new(text);

    /* Pack the image and label into the box */
	gtk_box_pack_start(GTK_BOX (box),image,FALSE,FALSE,3);
	gtk_box_pack_start(GTK_BOX (box),label,FALSE,FALSE,3);

	return box;
}

void addNewButtons(GtkWidget* vbox,const char* subfolder,void* callback)
{
	char*		foldername;
	char*		filename;
	const gchar*	entry;
	GDir*		folder;
	GKeyFile*	keyfile=g_key_file_new();
	char*		name;
	char*		set;
	char*		thumb;
	GtkWidget*	button;
	GtkWidget*	box;

	asprintf(&foldername,"%s/.config/XfceThemeManager/%s",getenv("HOME"),subfolder);
	folder=g_dir_open(foldername,0,NULL);
	if(folder!=NULL)
		{
			entry=g_dir_read_name(folder);
			while(entry!=NULL)
				{
					if(strstr(entry,".db"))
						{
							asprintf(&filename,"%s/.config/XfceThemeManager/%s/%s",getenv("HOME"),subfolder,entry);
							if(g_key_file_load_from_file(keyfile,filename,G_KEY_FILE_NONE,NULL))
								{
									name=g_key_file_get_string(keyfile,"Data","Name",NULL);
									set=g_key_file_get_string(keyfile,"Data","XconfName",NULL);
									thumb=g_key_file_get_string(keyfile,"Data","Thumbnail",NULL);
									button=gtk_button_new();
									box=imageBox(thumb,name);
									gtk_widget_set_name(button,filename);
									gtk_button_set_relief((GtkButton*)button,GTK_RELIEF_NONE);
									gtk_container_add (GTK_CONTAINER (button),box);
									g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(callback),NULL);
									gtk_box_pack_start((GtkBox*)vbox,button,false,true,4);
									g_free(name);
									g_free(set);
									g_free(thumb);
								}
						}
					entry=g_dir_read_name(folder);
				}
		}
}

void launchCompEd(GtkWidget* window,gpointer data)
{
	system("xfce4-composite-editor");
}


void shutdown(GtkWidget* window,gpointer data)
{
	gtk_main_quit();
}

void rerunAndBuild(GtkWidget* window,gpointer data)
{
	char*	datax[]={(char*)"xfce-theme-manager",(char*)"-m",NULL};

	gtk_main_quit();
	execvp("xfce-theme-manager",datax);
}

void showAdvanced(GtkWidget* widget,gpointer data)
{
	gboolean	state=gtk_toggle_button_get_active((GtkToggleButton*)widget);

	if (state==true)
		gtk_notebook_set_current_page(advanced,1);
	else
		gtk_notebook_set_current_page(advanced,0);
}

void resetBright(GtkWidget* widget,gpointer data)
{
	char*		command;

	gtk_range_set_value((GtkRange*)data,0);
	asprintf(&command,"%s 0",XCONFSETBRIGHT);
	system(command);
	freeAndNull(&command);

}
//#include <vgamouse.h> 

void setBright(GtkWidget* widget,gpointer data)
{
	char*		command;
	gdouble	val=gtk_range_get_value((GtkRange*)widget);

//	int state;
//	state=mouse_getbutton();
//	printf("XXXXXXXXXXXXXXXX\n");

	asprintf(&command,"%s\"%i\"",XCONFSETBRIGHT,(int)val);
	system(command);
	freeAndNull(&command);
	
}

void resetSatu(GtkWidget* widget,gpointer data)
{
	char*		command;

	gtk_range_set_value((GtkRange*)data,1.0);
	asprintf(&command,"%s 1.0",XCONFSETSATU);
	system(command);
	freeAndNull(&command);
}

void setSatu(GtkWidget* widget,gpointer data)
{
	char*		command;
	gdouble	val=gtk_range_get_value((GtkRange*)widget);
	
	asprintf(&command,"%s\"%f\"",XCONFSETSATU,val);
	system(command);
	freeAndNull(&command);
}

void resetLayout(GtkWidget* widget,gpointer data)
{
	char*		command;

	gtk_entry_set_text((GtkEntry*)data,currentButtonLayout);
	asprintf(&command,"%s \"%s\"",XCONFSETLAYOUT,currentButtonLayout);
	system(command);
	freeAndNull(&command);
}

void changeLayout(GtkWidget* widget,gpointer data)
{
	char*		command;

	asprintf(&command,"%s \"%s\"",XCONFSETLAYOUT,gtk_entry_get_text((GtkEntry*)widget));
	system(command);
	freeAndNull(&command);
}

void setTitlePos(GtkWidget* widget,gpointer data)
{
	char*		command;

	gboolean	state=gtk_toggle_button_get_active((GtkToggleButton*)widget);

	if (state==true)
		{
			asprintf(&command,"%s %s",XCONFSETTITLEPOS,(char*)data);
			system(command);
			freeAndNull(&command);
		}
}

void init(void)
{
	gchar	*stdout;

	asprintf(&themesArray[0],"%s/.themes",getenv("HOME"));
	asprintf(&themesArray[1],"%s",GLOBALTHEMES);
	
	asprintf(&iconsArray[0],"%s/.icons",getenv("HOME"));
	asprintf(&iconsArray[1],"%s",GLOBALICONS);

	asprintf(&papersArray[0],"%s/.local/share/xfce4/backdrops",getenv("HOME"));
	asprintf(&papersArray[1],"%s",GLOBALWALLPAPERS);


	asprintf(&dbFolder,"%s/.config/XfceThemeManager",getenv("HOME"));
	asprintf(&metaFolder,"%s/.config/XfceThemeManager/meta",getenv("HOME"));
	asprintf(&framesFolder,"%s/.config/XfceThemeManager/frames",getenv("HOME"));
	asprintf(&controlsFolder,"%s/.config/XfceThemeManager/controls",getenv("HOME"));
	asprintf(&iconsFolder,"%s/.config/XfceThemeManager/icons",getenv("HOME"));
	asprintf(&cursorsFolder,"%s/.config/XfceThemeManager/cursors",getenv("HOME"));
	asprintf(&wallpapersFolder,"%s/.config/XfceThemeManager/wallpapers",getenv("HOME"));

	g_spawn_command_line_sync("xfconf-query -c xfce4-desktop -vp /backdrop/screen0/monitor0/image-style",&stdout,NULL,NULL,NULL);
	stdout[strlen(stdout)-1]=0;
	currentWallStyle=atol(stdout);
	g_free(stdout);

	g_spawn_command_line_sync(XCONFGETCONTROLS,&currentGtkTheme,NULL,NULL,NULL);
	currentGtkTheme[strlen(currentGtkTheme)-1]=0;
	
	g_spawn_command_line_sync(XCONFGETICONS,&currentIconTheme,NULL,NULL,NULL);
	currentIconTheme[strlen(currentIconTheme)-1]=0;

	g_spawn_command_line_sync(XCONFGETCURSOR,&currentCursorTheme,NULL,NULL,NULL);
	currentCursorTheme[strlen(currentCursorTheme)-1]=0;

	g_spawn_command_line_sync(XCONFGETFRAME,&currentWmTheme,NULL,NULL,NULL);
	currentWmTheme[strlen(currentWmTheme)-1]=0;

	g_spawn_command_line_sync(XCONFGETPAPER,&currentWallPaper,NULL,NULL,NULL);
	currentWallPaper[strlen(currentWallPaper)-1]=0;

	g_spawn_command_line_sync(XCONFGETLAYOUT,&currentButtonLayout,NULL,NULL,NULL);
	currentButtonLayout[strlen(currentButtonLayout)-1]=0;

	g_spawn_command_line_sync(XCONFGETTITLEPOS,&currentTitlePos,NULL,NULL,NULL);
	currentTitlePos[strlen(currentTitlePos)-1]=0;

}

void makeProgressBar(void)
{
	GtkWidget*		vbox;

	progressWindow=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size((GtkWindow*)progressWindow,400,40);
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
	GtkWidget*		window;
	GtkWidget*		vbox;
	GtkNotebook*	notebook;
	GtkWidget*		buttonHbox;
	GtkWidget*		label;
	GtkWidget*		button;

//themes tab
	GtkWidget*	themesVbox;
	GtkWidget*	themesScrollBox;

//frames tab
	GtkWidget*	framesScrollBox;
	GtkWidget*	framesVbox;

//controls tab
	GtkWidget*	controlsVbox;
	GtkWidget*	controlsScrollBox;
//icons tab
	GtkWidget*	iconsVbox;
	GtkWidget*	iconsScrollBox;
//cursors tab
	GtkWidget*	cursorsVbox;
	GtkWidget*	cursorsScrollBox;
//wallpapers tab
	GtkWidget*	wallpapersVbox;
	GtkWidget*	wallpapersScrollBox;
	GtkWidget*	paperVbox;

//advanced
	GtkWidget*	advancedVbox;
	GtkWidget*	advancedScrollBox;
	GtkWidget*	advancedHbox;
	GtkWidget*	advancedRange;
	GtkWidget*	advancedEntry;
//	GSList*	advancedGroup;
	GtkWidget*	firstRadio;

	g_thread_init(NULL);
	gdk_threads_init();
	gtk_init(&argc, &argv);

	init();

	if (argc==2 && strcasecmp(argv[1],"-m")==0)
		{
		makeProgressBar();

		gdk_threads_enter();
			g_timeout_add (100, updateBarTimer, NULL);
			g_thread_create(rebuildDB,NULL,false,NULL);
			gtk_main();
		gdk_threads_leave();
		gtk_widget_destroy(progressWindow);
		}

	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size((GtkWindow*)window,400,470);
	g_signal_connect_after(G_OBJECT(window),"destroy",G_CALLBACK(shutdown),NULL);

//main window vbox
	vbox=gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window),(GtkWidget*)vbox);

//themes vbox
	themesScrollBox=gtk_scrolled_window_new(NULL,NULL);
	themesVbox=gtk_vbox_new(FALSE, 0);
	addNewButtons(themesVbox,"meta",(void*)doMeta);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)themesScrollBox,themesVbox);

//frames vbox
	framesScrollBox=gtk_scrolled_window_new(NULL,NULL);
	framesVbox=gtk_vbox_new(FALSE, 0);
	addNewButtons(framesVbox,"frames",(void*)doFrame);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)framesScrollBox,framesVbox);

//controls vbox
	controlsScrollBox=gtk_scrolled_window_new(NULL,NULL);
	controlsVbox=gtk_vbox_new(FALSE, 0);
	addNewButtons(controlsVbox,"controls",(void*)doControls);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)controlsScrollBox,controlsVbox);

//icons vbox
	iconsScrollBox=gtk_scrolled_window_new(NULL,NULL);
	iconsVbox=gtk_vbox_new(FALSE, 0);
	addNewButtons(iconsVbox,"icons",(void*)doIcons);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)iconsScrollBox,iconsVbox);

//cursors
	cursorsScrollBox=gtk_scrolled_window_new(NULL,NULL);
	cursorsVbox=gtk_vbox_new(FALSE, 0);
	addNewButtons(cursorsVbox,"cursors",(void*)doCursors);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)cursorsScrollBox,cursorsVbox);

//wallpapers
	wallpapersScrollBox=gtk_vbox_new(FALSE, 0);

	paperVbox=gtk_scrolled_window_new(NULL,NULL);
	wallpapersVbox=gtk_vbox_new(FALSE, 0);
	addNewButtons(wallpapersVbox,"wallpapers",(void*)doWallpapers);

	comboBox=(GtkComboBoxText*)gtk_combo_box_text_new();
	gtk_combo_box_text_append_text(comboBox,"Auto");
	gtk_combo_box_text_append_text(comboBox,"Centered");
	gtk_combo_box_text_append_text(comboBox,"Tiled");
	gtk_combo_box_text_append_text(comboBox,"Stretched");
	gtk_combo_box_text_append_text(comboBox,"Scaled");
	gtk_combo_box_text_append_text(comboBox,"Zoomed");
	gtk_combo_box_set_active((GtkComboBox*)comboBox,currentWallStyle);
	g_signal_connect_after(G_OBJECT(comboBox),"changed",G_CALLBACK(wallStyleChanged),NULL);

	gtk_box_pack_start((GtkBox*)wallpapersScrollBox,(GtkWidget*)comboBox,false,true,4);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)paperVbox,wallpapersVbox);
	gtk_container_add (GTK_CONTAINER (wallpapersScrollBox), paperVbox);


//notebook
	notebook=(GtkNotebook*)gtk_notebook_new();
	advanced=(GtkNotebook*)gtk_notebook_new();
 	gtk_notebook_set_show_tabs(advanced,false);
 
//pages
	label=gtk_label_new("Themes");
	gtk_notebook_append_page(notebook,themesScrollBox,label);

	label=gtk_label_new("Window Borders");
	gtk_notebook_append_page(notebook,framesScrollBox,label);

	label=gtk_label_new("Controls");
	gtk_notebook_append_page(notebook,controlsScrollBox,label);

	label=gtk_label_new("Icons");
	gtk_notebook_append_page(notebook,iconsScrollBox,label);

	label=gtk_label_new("Cursors");
	gtk_notebook_append_page(notebook,cursorsScrollBox,label);

	label=gtk_label_new("Wallpapers");
	gtk_notebook_append_page(notebook,wallpapersScrollBox,label);

	gtk_notebook_append_page(advanced,(GtkWidget*)notebook,NULL);

//do advanced gui
	advancedScrollBox=gtk_scrolled_window_new(NULL,NULL);
	advancedVbox=gtk_vbox_new(FALSE, 0);

//comp ed
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_label_new("Launch Xfce-Composite-Editor"),false,false,2);
	button=gtk_button_new_with_label("Xfce-Composite-Editor");
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(launchCompEd),NULL);
	gtk_box_pack_start(GTK_BOX(advancedVbox),button,false,false,8);
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);

	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)advancedScrollBox,advancedVbox);
	gtk_notebook_append_page(advanced,advancedScrollBox,NULL);

//back drop aadj
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_label_new("Backdrop Adjustments"),false,false,2);
	advancedHbox=gtk_hbox_new(false,0);
	button=gtk_button_new_with_label("Reset");
	gtk_box_pack_start(GTK_BOX(advancedHbox),button, false,false,8);
	advancedRange=gtk_hscale_new_with_range(-128,127,1);
	gtk_scale_set_value_pos((GtkScale*)advancedRange,GTK_POS_LEFT);
	gtk_range_set_value((GtkRange*)advancedRange,0);
	g_signal_connect_after(G_OBJECT(advancedRange),"value-changed",G_CALLBACK(setBright),NULL);


//	g_signal_connect_after(G_OBJECT(advancedRange),"button-release-event",G_CALLBACK(setBright),NULL);

	gtk_range_set_update_policy((GtkRange*)advancedRange,GTK_UPDATE_DISCONTINUOUS);

	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetBright),(gpointer)advancedRange);
	gtk_box_pack_start(GTK_BOX(advancedHbox),advancedRange, true,true,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new("Brightness"), false,false,4);
	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox, false,false,2);

	advancedHbox=gtk_hbox_new(false,0);
	button=gtk_button_new_with_label("Reset");
	gtk_box_pack_start(GTK_BOX(advancedHbox),button, false,false,8);
	advancedRange=gtk_hscale_new_with_range(-10.0,10,0.1);
	gtk_scale_set_value_pos((GtkScale*)advancedRange,GTK_POS_LEFT);
	gtk_range_set_value((GtkRange*)advancedRange,1.0);
	g_signal_connect_after(G_OBJECT(advancedRange),"value-changed",G_CALLBACK(setSatu),NULL);

	gtk_range_set_update_policy((GtkRange*)advancedRange,GTK_UPDATE_DISCONTINUOUS);

	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetSatu),(gpointer)advancedRange);
	gtk_box_pack_start(GTK_BOX(advancedHbox),advancedRange, true,true,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new("Saturation"), false,false,4);
	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox, false,false,2);

	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);

//buton layot
	advancedHbox=gtk_hbox_new(false,0);
	button=gtk_button_new_with_label("Reset");
	gtk_box_pack_start(GTK_BOX(advancedHbox),button, false,false,8);
	advancedEntry=gtk_entry_new();
	gtk_entry_set_text((GtkEntry*)advancedEntry,currentButtonLayout);
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetLayout),(gpointer)advancedEntry);

	g_signal_connect_after(G_OBJECT(advancedEntry),"key-release-event",G_CALLBACK(changeLayout),NULL);

	gtk_box_pack_start(GTK_BOX(advancedHbox),advancedEntry, false,false,2);
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new("Button Layout"), false,false,4);

	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox, false,false,2);
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);

//titlepos
	advancedHbox=gtk_hbox_new(false,0);
	firstRadio=gtk_radio_button_new_with_label (NULL, "Left");
	g_signal_connect_after(G_OBJECT(firstRadio),"toggled",G_CALLBACK(setTitlePos),(void*)"left");
	if(strcasecmp(currentTitlePos,"left")==0)
		gtk_toggle_button_set_active((GtkToggleButton*)firstRadio,true);
	gtk_box_pack_start(GTK_BOX(advancedHbox),firstRadio,false,false,0);

	button=gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON (firstRadio),"Centre");
	g_signal_connect_after(G_OBJECT(button),"toggled",G_CALLBACK(setTitlePos),(void*)"center");
	if(strcasecmp(currentTitlePos,"center")==0)
		gtk_toggle_button_set_active((GtkToggleButton*)button,true);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button,false,false,0);

	button=gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON (firstRadio),"Right");
	g_signal_connect_after(G_OBJECT(button),"toggled",G_CALLBACK(setTitlePos),(void*)"right");
	if(strcasecmp(currentTitlePos,"right")==0)
		gtk_toggle_button_set_active((GtkToggleButton*)button,true);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button,false,false,0);

	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox, false,false,2);
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);

//add notebook to window
	gtk_container_add(GTK_CONTAINER(vbox),(GtkWidget*)advanced);

	gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(),false,false,4);

//do buttons
	buttonHbox=gtk_hbox_new(true,0);

	button=gtk_button_new_with_label("Reset Theme");
	gtk_box_pack_start(GTK_BOX(buttonHbox),button, false,false,0);
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetTheme),NULL);

	button=gtk_button_new_with_label("Rebuild DB");
	gtk_box_pack_start(GTK_BOX(buttonHbox),button, false,false,0);
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(rerunAndBuild),NULL);

	button=gtk_toggle_button_new_with_label("Advanced");
	gtk_box_pack_start(GTK_BOX(buttonHbox),button, false,false,0);
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(showAdvanced),NULL);

	gtk_box_pack_start(GTK_BOX(vbox),buttonHbox, false,false, 8);

	buttonHbox=gtk_hbox_new(true,0);
	button=gtk_button_new_from_stock(GTK_STOCK_QUIT);
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(shutdown),NULL);

	gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(),false,false,0);

	gtk_box_pack_start(GTK_BOX(buttonHbox),button, false,false,8);
	gtk_box_pack_start(GTK_BOX(vbox),buttonHbox, false,false,8);

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


