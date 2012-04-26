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


