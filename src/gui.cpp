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

	return(box);
}

void freeNames(gpointer data)
{
	freeAndNull((char**)&data);
}

gint sortFunc(gconstpointer a,gconstpointer b)
{
	return(strcasecmp((const char*)a,(const char*)b));
}

void addNewButtons(GtkWidget* vbox,const char* subfolder,void* callback)
{
	char*		foldername;
	char*		filename;
	const gchar*	entry;
	GDir*		folder;
	GKeyFile*	keyfile=g_key_file_new();
	char*		name;
	char*		thumb;
	GtkWidget*	button;
	GtkWidget*	box;

	GSList *	entrylist=NULL;
	char*		entryname;

	asprintf(&foldername,"%s/.config/XfceThemeManager/%s",homeFolder,subfolder);
	folder=g_dir_open(foldername,0,NULL);
	if(folder!=NULL)
		{
			entry=g_dir_read_name(folder);
			while(entry!=NULL)
				{
				if(strstr(entry,".db"))
					{
						asprintf(&entryname,"%s",entry);
						entrylist=g_slist_prepend(entrylist,(void*)entryname);
					}
					entry=g_dir_read_name(folder);
				}
			g_dir_close(folder);
		}

	if(entrylist!=NULL)
		{
			entrylist=g_slist_sort(entrylist,sortFunc);

			for (int j=0;j<(int)g_slist_length(entrylist);j++)
				{
					asprintf(&filename,"%s/.config/XfceThemeManager/%s/%s",homeFolder,subfolder,(char*)g_slist_nth_data(entrylist,j));
					if(g_key_file_load_from_file(keyfile,filename,G_KEY_FILE_NONE,NULL))
						{
							name=g_key_file_get_string(keyfile,"Data","Name",NULL);
							thumb=g_key_file_get_string(keyfile,"Data","Thumbnail",NULL);
							button=gtk_button_new();
							box=imageBox(thumb,name);
							gtk_widget_set_name(button,filename);
							gtk_button_set_relief((GtkButton*)button,GTK_RELIEF_NONE);
							gtk_container_add (GTK_CONTAINER (button),box);
							g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(callback),NULL);
							gtk_box_pack_start((GtkBox*)vbox,button,false,true,4);
							g_free(name);
							g_free(thumb);
						}
			 	}
			g_slist_free_full(entrylist,freeNames);
		}
	g_key_file_free(keyfile);
}

//titlepos
GtkWidget* buildTitlePos(void)
{
	GtkWidget*	advancedHbox=gtk_hbox_new(false,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new("Title Position"), false,false,4);
	titlePos=(GtkComboBoxText*)gtk_combo_box_text_new();
	gtk_combo_box_text_append_text(titlePos,"Left");
	gtk_combo_box_text_append_text(titlePos,"Centre");
	gtk_combo_box_text_append_text(titlePos,"Right");
	gtk_combo_box_set_active((GtkComboBox*)titlePos,positionToInt(currentTitlePos));
	g_signal_connect_after(G_OBJECT(titlePos),"changed",G_CALLBACK(setTitlePos),NULL);
	gtk_box_pack_start(GTK_BOX(advancedHbox),(GtkWidget*)titlePos,true,true,8);
	return(advancedHbox);
}

void buildPages(void)
{
	GtkWidget*	vbox;
	GtkWidget*	wallscroll;

	themesVBox=gtk_vbox_new(FALSE, 0);
	addNewButtons(themesVBox,"custom",(void*)doMeta);
	addNewButtons(themesVBox,"meta",(void*)doMeta);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)themesScrollBox,themesVBox);

	framesVBox=gtk_vbox_new(FALSE, 0);
	addNewButtons(framesVBox,"frames",(void*)doFrame);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)framesScrollBox,framesVBox);

	controlsVBox=gtk_vbox_new(FALSE, 0);
	addNewButtons(controlsVBox,"controls",(void*)doControls);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)controlsScrollBox,controlsVBox);

	iconsVBox=gtk_vbox_new(FALSE, 0);
	addNewButtons(iconsVBox,"icons",(void*)doIcons);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)iconsScrollBox,iconsVBox);

	cursorsVBox=gtk_vbox_new(FALSE, 0);
	addNewButtons(cursorsVBox,"cursors",(void*)doCursors);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)cursorsScrollBox,cursorsVBox);

	wallscroll=gtk_scrolled_window_new(NULL,NULL);
	wallpapersVBox=gtk_vbox_new(FALSE, 0);
	
	vbox=gtk_vbox_new(FALSE, 0);
	addNewButtons(vbox,"wallpapers",(void*)doWallpapers);

	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)wallscroll,vbox);
	gtk_box_pack_start((GtkBox*)wallpapersVBox,(GtkWidget*)wallscroll,true,true,4);
	gtk_container_add (GTK_CONTAINER(wallpapersMainBox),wallpapersVBox);
}

void buildAdvancedGui(GtkWidget* advancedScrollBox)
{
	GtkWidget*	advancedVbox;
	GtkWidget*	advancedHbox;
	GtkWidget*	advancedRange;
	GtkWidget*	button;

	advancedVbox=gtk_vbox_new(FALSE, 0);

//database
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_label_new("Re-Build The Database"),false,false,2);
	advancedHbox=gtk_hbox_new(true,4);
	button=gtk_button_new_with_label("Rebuild DB");
	gtk_box_pack_start(GTK_BOX(advancedHbox),button, false,false,4);
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(rerunAndBuild),NULL);
	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox, false,false,4);
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);

//comp ed
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_label_new("Launch Xfce-Composite-Editor"),false,false,2);
	advancedHbox=gtk_hbox_new(true,4);
	button=gtk_button_new_with_label("Xfce-Composite-Editor");
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(launchCompEd),NULL);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button, false,false,4);
	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox,false,false,8);
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);

//back drop aadj
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_label_new("Backdrop Adjustments"),false,false,2);
	advancedHbox=gtk_hbox_new(false,0);

//bright
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new("Brightness"), false,false,4);
	advancedRange=gtk_hscale_new_with_range(-128,127,1);
	gtk_scale_set_value_pos((GtkScale*)advancedRange,GTK_POS_LEFT);
	gtk_range_set_value((GtkRange*)advancedRange,currentBright);
	briteRange=advancedRange;

	g_signal_connect(G_OBJECT(advancedRange), "button-release-event", G_CALLBACK(setBright),NULL);
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
	gtk_range_set_value((GtkRange*)advancedRange,currentSatu);
	g_signal_connect(G_OBJECT(advancedRange), "button-release-event", G_CALLBACK(setSatu),NULL);
	satuRange=advancedRange;

	gtk_box_pack_start(GTK_BOX(advancedHbox),advancedRange, true,true,0);
	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox, false,false,2);

	button=gtk_button_new_with_label("Reset");
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetSatu),(gpointer)advancedRange);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button, false,false,8);

	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);

//buton layout
	advancedHbox=gtk_hbox_new(false,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new("Button Layout"), false,false,4);

	layoutEntry=gtk_entry_new();
	gtk_entry_set_text((GtkEntry*)layoutEntry,currentButtonLayout);
	g_signal_connect_after(G_OBJECT(layoutEntry),"key-release-event",G_CALLBACK(changeLayout),NULL);
	gtk_box_pack_start(GTK_BOX(advancedHbox),layoutEntry, true,true,2);

	button=gtk_button_new_with_label("Reset");
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetLayout),(gpointer)layoutEntry);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button, false,false,8);

	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox, false,false,2);
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);

//buildTitlePos
	gtk_box_pack_start(GTK_BOX(advancedVbox),buildTitlePos(), false,false,0);
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);

//fonts
//wmfont
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_label_new("Font Selection"), false,false,4);
	advancedHbox=gtk_hbox_new(false,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new("WM Font "), false,false,4);

	wmFontButton=gtk_font_button_new_with_font(currentWMFont);
	g_signal_connect_after(G_OBJECT(wmFontButton),"font-set",G_CALLBACK(setFont),(void*)0);
	gtk_font_button_set_use_font((GtkFontButton*)wmFontButton,true);
	gtk_box_pack_start(GTK_BOX(advancedHbox),wmFontButton, true,true,1);

	button=gtk_button_new_with_label("Reset");
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetFont),(void*)0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button, false,false,1);

	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox, false,false,4);

//appfont
	advancedHbox=gtk_hbox_new(false,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new("App Font"), false,false,4);

	appFontButton=gtk_font_button_new_with_font(currentAppFont);
	gtk_font_button_set_use_font((GtkFontButton*)appFontButton,true);
	g_signal_connect_after(G_OBJECT(appFontButton),"font-set",G_CALLBACK(setFont),(void*)1);
	gtk_box_pack_start(GTK_BOX(advancedHbox),appFontButton, true,true,1);

	button=gtk_button_new_with_label("Reset");
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetFont),(void*)1);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button, false,false,1);

	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox, false,false,4);

	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)advancedScrollBox,advancedVbox);

//cursor size
	advancedHbox=gtk_hbox_new(false,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new("Cursor Size"), false,false,4);
	cursorSize=gtk_hscale_new_with_range(16,48,1);
	gtk_scale_set_value_pos((GtkScale*)cursorSize,GTK_POS_LEFT);
	gtk_range_set_value((GtkRange*)cursorSize,currentCursSize);
	g_signal_connect(G_OBJECT(cursorSize), "value-changed",G_CALLBACK(setCursSize),NULL);
	gtk_box_pack_start(GTK_BOX(advancedHbox),cursorSize, true,true,0);

	button=gtk_button_new_with_label("Reset");
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetCursSize),NULL);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button, false,false,8);
	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox, false,false,2);
}


#if 0
	advancedRange=gtk_hscale_new_with_range(-128,127,1);
	gtk_scale_set_value_pos((GtkScale*)advancedRange,GTK_POS_LEFT);
	gtk_range_set_value((GtkRange*)advancedRange,currentBright);
	briteRange=advancedRange;

	g_signal_connect(G_OBJECT(advancedRange), "button-release-event", G_CALLBACK(setBright),NULL);
	gtk_box_pack_start(GTK_BOX(advancedHbox),advancedRange, true,true,0);
	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox, false,false,2);

	button=gtk_button_new_with_label("Reset");
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetBright),(gpointer)advancedRange);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button, false,false,8);

#endif







