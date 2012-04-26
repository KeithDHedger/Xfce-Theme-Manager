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
 * callbacks.cpp
 */

#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <sys/stat.h>

#include "globals.h"

//set title position
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

void extractAndInstall(char* filename)
{
	char*		command;
	gchar*	stdout=NULL;
	gchar*	stderr=NULL;
	
	asprintf(&command,"tar --wildcards -tf %s */gtkrc",filename);
	g_spawn_command_line_sync(command,&stdout,&stderr,NULL,NULL);
	if (stdout!=NULL)
		{
			stdout[strlen(stdout)-1]=0;
			if(strlen(stdout)>1)
				printf("Its a gtk\n");
		}

	freeAndNull(&stdout);
	freeAndNull(&stderr);
	freeAndNull(&command);

}

//dnd install
void dropUri(GtkWidget *widget,GdkDragContext *context,gint x,gint y,GtkSelectionData *selection_data,guint info,guint32 time,gpointer user_data)
{
	gchar**	array=gtk_selection_data_get_uris(selection_data);
	int		cnt=g_strv_length(array);
	char*		filename;

	for(int j=0;j<cnt;j++)
		{
			filename=g_filename_from_uri(array[j],NULL,NULL);
			if(g_str_has_suffix(filename,".tgz")||g_str_has_suffix(filename,".gz")||g_str_has_suffix(filename,".zip"))
				{
					//printf("file %i = %s\n",j,filename);
					extractAndInstall(filename);
				}
			freeAndNull(&filename);
		}

	g_strfreev(array);
}

