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
 * gui.cpp
 */

#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <sys/stat.h>

#include "globals.h"
#include "callbacks.h"

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

//wallpapers
GtkWidget* buildWallpapers(GtkWidget* wallpapersScrollBox)
{
	GtkWidget*	wallpapersVbox;
	GtkWidget*	paperVbox;

	paperVbox=gtk_scrolled_window_new(NULL,NULL);
	wallpapersVbox=gtk_vbox_new(FALSE, 0);
	addNewButtons(wallpapersVbox,"wallpapers",(void*)doWallpapers);

	styleComboBox=(GtkComboBoxText*)gtk_combo_box_text_new();
	gtk_combo_box_text_append_text(styleComboBox,"Auto");
	gtk_combo_box_text_append_text(styleComboBox,"Centered");
	gtk_combo_box_text_append_text(styleComboBox,"Tiled");
	gtk_combo_box_text_append_text(styleComboBox,"Stretched");
	gtk_combo_box_text_append_text(styleComboBox,"Scaled");
	gtk_combo_box_text_append_text(styleComboBox,"Zoomed");
	gtk_combo_box_set_active((GtkComboBox*)styleComboBox,currentWallStyle);
	g_signal_connect_after(G_OBJECT(styleComboBox),"changed",G_CALLBACK(wallStyleChanged),NULL);

	gtk_box_pack_start((GtkBox*)wallpapersScrollBox,(GtkWidget*)styleComboBox,false,true,4);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)paperVbox,wallpapersVbox);
	return(paperVbox);
}

//titlepos
GtkWidget* buildTitlePos(void)
{
	GtkWidget*	advancedHbox;
	GtkWidget*	firstRadio;
	GtkWidget*	button;

	advancedHbox=gtk_hbox_new(true,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new("Title Position"), false,false,2);
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

	return(advancedHbox);
}


