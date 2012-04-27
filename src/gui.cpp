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

void buildPages(void)
{
	GtkWidget*	vbox;

	themesScrollBox=gtk_scrolled_window_new(NULL,NULL);
	vbox=gtk_vbox_new(FALSE, 0);
	addNewButtons(vbox,"meta",(void*)doMeta);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)themesScrollBox,vbox);
	
	framesScrollBox=gtk_scrolled_window_new(NULL,NULL);
	vbox=gtk_vbox_new(FALSE, 0);
	addNewButtons(vbox,"frames",(void*)doFrame);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)framesScrollBox,vbox);
	
	controlsScrollBox=gtk_scrolled_window_new(NULL,NULL);
	vbox=gtk_vbox_new(FALSE, 0);
	addNewButtons(vbox,"controls",(void*)doControls);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)controlsScrollBox,vbox);

	iconsScrollBox=gtk_scrolled_window_new(NULL,NULL);
	vbox=gtk_vbox_new(FALSE, 0);
	addNewButtons(vbox,"icons",(void*)doIcons);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)iconsScrollBox,vbox);

	cursorsScrollBox=gtk_scrolled_window_new(NULL,NULL);
	vbox=gtk_vbox_new(FALSE, 0);
	addNewButtons(vbox,"cursors",(void*)doCursors);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)cursorsScrollBox,vbox);

	wallpapersScrollBox=gtk_vbox_new(FALSE, 0);
	gtk_container_add (GTK_CONTAINER (wallpapersScrollBox),buildWallpapers(wallpapersScrollBox));

}

	
void buildAdvancedGtui(GtkWidget* advancedScrollBox)
{
	GtkWidget*	advancedVbox;
	GtkWidget*	advancedHbox;
	GtkWidget*	advancedRange;
	GtkWidget*	advancedEntry;
	GtkWidget*	button;

	advancedVbox=gtk_vbox_new(FALSE, 0);

//comp ed
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_label_new("Launch Xfce-Composite-Editor"),false,false,2);
	button=gtk_button_new_with_label("Xfce-Composite-Editor");
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(launchCompEd),NULL);
	gtk_box_pack_start(GTK_BOX(advancedVbox),button,false,false,8);
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);

//	gtk_notebook_append_page(advanced,advancedScrollBox,NULL);

//back drop aadj
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_label_new("Backdrop Adjustments"),false,false,2);
	advancedHbox=gtk_hbox_new(false,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new("Brightness"), false,false,4);

//bright
	advancedRange=gtk_hscale_new_with_range(-128,127,1);
	gtk_scale_set_value_pos((GtkScale*)advancedRange,GTK_POS_LEFT);
	gtk_range_set_value((GtkRange*)advancedRange,0);
	g_signal_connect_after(G_OBJECT(advancedRange),"value-changed",G_CALLBACK(setBright),NULL);
	gtk_range_set_update_policy((GtkRange*)advancedRange,GTK_UPDATE_DISCONTINUOUS);
	gtk_box_pack_start(GTK_BOX(advancedHbox),advancedRange, true,true,0);
	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox, false,false,2);

	button=gtk_button_new_with_label("Reset");
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetBright),(gpointer)advancedRange);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button, false,false,8);

//satu
	advancedHbox=gtk_hbox_new(false,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new("Saturation"), false,false,4);

	advancedRange=gtk_hscale_new_with_range(-10.0,10,0.1);
	gtk_scale_set_value_pos((GtkScale*)advancedRange,GTK_POS_LEFT);
	gtk_range_set_value((GtkRange*)advancedRange,1.0);
	g_signal_connect_after(G_OBJECT(advancedRange),"value-changed",G_CALLBACK(setSatu),NULL);
	gtk_range_set_update_policy((GtkRange*)advancedRange,GTK_UPDATE_DISCONTINUOUS);
	gtk_box_pack_start(GTK_BOX(advancedHbox),advancedRange, true,true,0);
	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox, false,false,2);

	button=gtk_button_new_with_label("Reset");
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetSatu),(gpointer)advancedRange);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button, false,false,8);

	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);

//buton layout
	advancedHbox=gtk_hbox_new(false,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new("Button Layout"), false,false,4);

	advancedEntry=gtk_entry_new();
	gtk_entry_set_text((GtkEntry*)advancedEntry,currentButtonLayout);
	g_signal_connect_after(G_OBJECT(advancedEntry),"key-release-event",G_CALLBACK(changeLayout),NULL);
	gtk_box_pack_start(GTK_BOX(advancedHbox),advancedEntry, true,true,2);

	button=gtk_button_new_with_label("Reset");
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetLayout),(gpointer)advancedEntry);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button, false,false,8);

	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox, false,false,2);
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);

//buildTitlePos
	gtk_box_pack_start(GTK_BOX(advancedVbox),buildTitlePos(), false,false,2);
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);

//fonts
//wmfont
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_label_new("Font Selection"), false,false,4);
	advancedHbox=gtk_hbox_new(false,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new("WM Font "), false,false,1);

	wmFontButton=gtk_font_button_new_with_font(currentWMFont);
	g_signal_connect_after(G_OBJECT(wmFontButton),"font-set",G_CALLBACK(setFont),(void*)0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),wmFontButton, true,true,1);

	button=gtk_button_new_with_label("Reset");
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetFont),(void*)0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button, false,false,1);

	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox, false,false,4);

//appfont
	advancedHbox=gtk_hbox_new(false,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new("App Font"), false,false,1);

	appFontButton=gtk_font_button_new_with_font(currentAppFont);
	g_signal_connect_after(G_OBJECT(appFontButton),"font-set",G_CALLBACK(setFont),(void*)1);
	gtk_box_pack_start(GTK_BOX(advancedHbox),appFontButton, true,true,1);

	button=gtk_button_new_with_label("Reset");
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetFont),(void*)1);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button, false,false,1);

	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox, false,false,4);

	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)advancedScrollBox,advancedVbox);

}










