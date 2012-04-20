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

bool whoops=false;

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

	if(g_key_file_load_from_file(keyfile,gtk_widget_get_name(widget),G_KEY_FILE_NONE,NULL))
		{
			controlset=g_key_file_get_string(keyfile,"Data","GtkTheme",NULL);

			if(controlset!=NULL)
				{
					asprintf(&command,"%s\"%s\"",XCONFSETCONTROLS,controlset);
					system(command);
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

void shutdown(GtkWidget* window,gpointer data)
{
	gtk_main_quit();
}

void init(void)
{
	gchar	*stdout;

	asprintf(&localIcons,"%s/.icons",getenv("HOME"));
	asprintf(&localThemes,"%s/.themes",getenv("HOME"));
	asprintf(&localPapers,"%s/.local/share/xfce4/backdrops",getenv("HOME"));

	asprintf(&metaFolder,"%s/.config/XfceThemeManager/meta",getenv("HOME"));

	asprintf(&framesFolder,"%s/.config/XfceThemeManager/frames",getenv("HOME"));
	asprintf(&controlsFolder,"%s/.config/XfceThemeManager/controls",getenv("HOME"));
	asprintf(&iconsFolder,"%s/.config/XfceThemeManager/icons",getenv("HOME"));
	asprintf(&cursorsFolder,"%s/.config/XfceThemeManager/cursors",getenv("HOME"));
	asprintf(&wallpapersFolder,"%s/.config/XfceThemeManager/wallpapers",getenv("HOME"));

	g_spawn_command_line_sync("xfconf-query -c xfce4-desktop -vp /backdrop/screen0/monitor0/image-style",&stdout,NULL,NULL,NULL);
	stdout[strlen(stdout)-1]=0;
	wallStyle=atol(stdout);
	g_free(stdout);

	g_spawn_command_line_sync(XCONFGETCONTROLS,&currentGtkTheme,NULL,NULL,NULL);
	currentGtkTheme[strlen(currentGtkTheme)-1]=0;
}

int main(int argc,char **argv)
{
	GtkWidget*	window;
	GtkWidget*	vbox;
	GtkNotebook*	notebook;

	GtkWidget*	label;

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
	GtkComboBoxText* combo;
//general
	GtkWidget*	vgbox;

	gtk_init(&argc, &argv);

	init();

	GtkSettings *hold;
	hold=gtk_settings_get_default();

	if (argc==2 && strcasecmp(argv[1],"-m")==0)
		rebuildDB();

	g_object_set(hold,"gtk-theme-name",currentGtkTheme,"gtk-color-scheme","default",NULL);

	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size((GtkWindow*)window,400,470);
	g_signal_connect_after(G_OBJECT(window),"destroy",G_CALLBACK(shutdown),NULL);

//main window vbox
	vbox=gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window),(GtkWidget*)vbox);

//themes vbox
	themesScrollBox=gtk_scrolled_window_new(NULL,NULL);
	themesVbox=gtk_vbox_new(FALSE, 0);
//	addButtons(themesVbox,"meta",(void*)doMeta,true);
	addNewButtons(themesVbox,"meta",(void*)doMeta);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)themesScrollBox,themesVbox);

//frames vbox
	framesScrollBox=gtk_scrolled_window_new(NULL,NULL);
	framesVbox=gtk_vbox_new(FALSE, 0);
//	addButtons(framesVbox,"wmf",(void*)doFrame,true);
	addNewButtons(framesVbox,"frames",(void*)doFrame);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)framesScrollBox,framesVbox);

//controls vbox
	controlsScrollBox=gtk_scrolled_window_new(NULL,NULL);
	controlsVbox=gtk_vbox_new(FALSE, 0);
//	addButtons(controlsVbox,"conts",(void*)doControls,true);
	addNewButtons(controlsVbox,"controls",(void*)doControls);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)controlsScrollBox,controlsVbox);

//icons vbox
	iconsScrollBox=gtk_scrolled_window_new(NULL,NULL);
	iconsVbox=gtk_vbox_new(FALSE, 0);
	//addButtons(iconsVbox,"icons",(void*)doIcons,true);
	addNewButtons(iconsVbox,"icons",(void*)doIcons);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)iconsScrollBox,iconsVbox);

//cursors
	cursorsScrollBox=gtk_scrolled_window_new(NULL,NULL);
	cursorsVbox=gtk_vbox_new(FALSE, 0);
//	addButtons(cursorsVbox,"cursors",(void*)doCursors,true);
	addNewButtons(cursorsVbox,"cursors",(void*)doCursors);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)cursorsScrollBox,cursorsVbox);

//wallpapers
	wallpapersScrollBox=gtk_vbox_new(FALSE, 0);

	vgbox=gtk_scrolled_window_new(NULL,NULL);
	wallpapersVbox=gtk_vbox_new(FALSE, 0);
	addNewButtons(wallpapersVbox,"wallpapers",(void*)doWallpapers);

	combo=(GtkComboBoxText*)gtk_combo_box_text_new();
	gtk_combo_box_text_append_text(combo,"Auto");
	gtk_combo_box_text_append_text(combo,"Centered");
	gtk_combo_box_text_append_text(combo,"Tiled");
	gtk_combo_box_text_append_text(combo,"Stretched");
	gtk_combo_box_text_append_text(combo,"Scaled");
	gtk_combo_box_text_append_text(combo,"Zoomed");
	gtk_combo_box_set_active((GtkComboBox*)combo,wallStyle);
	g_signal_connect_after(G_OBJECT(combo),"changed",G_CALLBACK(wallStyleChanged),NULL);

	gtk_box_pack_start((GtkBox*)wallpapersScrollBox,(GtkWidget*)combo,false,true,4);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)vgbox,wallpapersVbox);
	gtk_container_add (GTK_CONTAINER (wallpapersScrollBox), vgbox);

//main notebook
	notebook=(GtkNotebook*)gtk_notebook_new();

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


//add notebook to window
	gtk_container_add(GTK_CONTAINER(vbox),(GtkWidget*)notebook);
	
	gtk_widget_show_all(window);
	gtk_main();

}

//gtkprev [border] /path/to/border /out/path/to/png
//gtkprev [controls] gtkthemename /out/path/to/png
//gtkprev [theme] gtkthemename /path/to/border /out/path/to/png
//gtkprev [cursors] cursortheme /out/path/to/png
//gtkprev [icons] icontheme /out/path/to/png
//gtkprev [custom] gtkthemename cursortheme icontheme /path/to/border /out/path/to/png
//gtkprev [fontpicker] "fontname"


