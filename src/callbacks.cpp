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

//information!
void infoDialog(const char* message,char* filename,GtkMessageType type)
{
	GtkWidget*	dialog=gtk_message_dialog_new((GtkWindow*)window,GTK_DIALOG_DESTROY_WITH_PARENT,type,GTK_BUTTONS_CLOSE,"%s - %s",message,filename);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}

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

void installWallpaper(char* filename)
{
	char*		command;
	int		retval=-1;

	asprintf(&command,"cp \"%s\" \"%s\"",filename,papersArray[0]);
	retval=system(command);

	if(retval==0)
		infoDialog("Installed",filename,GTK_MESSAGE_INFO);
	else
		infoDialog("Can't Install",filename,GTK_MESSAGE_ERROR);

	freeAndNull(&command);
}

void extractAndInstall(char* filename)
{
	char		command[4096];
	gchar*	stdout=NULL;
	gchar*	stderr=NULL;
	int		retval=-1;

	while(true)
	{
	sprintf(command,"tar --wildcards -tf %s */gtkrc",filename);
	g_spawn_command_line_sync((char*)command,&stdout,&stderr,NULL,NULL);
	if (stdout!=NULL)
		{
			stdout[strlen(stdout)-1]=0;
			if(strlen(stdout)>1)
				{
					sprintf(command,"tar -C %s -xf %s",themesArray[0],filename);
					retval=system(command);
					break;
				}
		}

	sprintf(command,"tar --wildcards -tf %s */themerc",filename);
	g_spawn_command_line_sync((char*)command,&stdout,&stderr,NULL,NULL);
	if (stdout!=NULL)
		{
			stdout[strlen(stdout)-1]=0;
			if(strlen(stdout)>1)
				{
					sprintf(command,"tar -C %s -xf %s",themesArray[0],filename);
					retval=system(command);
					break;
				}
		}

	sprintf(command,"tar --wildcards -tf %s */index.theme",filename);
	g_spawn_command_line_sync((char*)command,&stdout,&stderr,NULL,NULL);
	if (stdout!=NULL)
		{
			stdout[strlen(stdout)-1]=0;
			if(strlen(stdout)>1)
				{
					sprintf(command,"tar -C %s -xf %s",iconsArray[0],filename);
					retval=system(command);
					break;
				}
		}
	break;
	}

	if(retval==0)
		infoDialog("Installed",filename,GTK_MESSAGE_INFO);
	else
		infoDialog("Can't Install",filename,GTK_MESSAGE_ERROR);

	freeAndNull(&stdout);
	freeAndNull(&stderr);
}

//dnd install
void dropUri(GtkWidget *widget,GdkDragContext *context,gint x,gint y,GtkSelectionData *selection_data,guint info,guint32 time,gpointer user_data)
{
	gchar**	array=gtk_selection_data_get_uris(selection_data);
	int		cnt=g_strv_length(array);
	char*		filename;
	const char*	ziptype[]={".tgz",".gz",".zip",".tar",".bz2",NULL};
	const char* pictype[]={".jpg",".png",".bmp",".gif",NULL};

//themes
	for(int j=0;j<cnt;j++)
		{
			filename=g_filename_from_uri(array[j],NULL,NULL);
			for(int k=0;k<5;k++)
				{
					if(g_str_has_suffix(filename,ziptype[k]))
						{
							extractAndInstall(filename);
							break;
						}
				}
			freeAndNull(&filename);
		}

//pics
	for(int j=0;j<cnt;j++)
		{
			filename=g_filename_from_uri(array[j],NULL,NULL);
			for(int k=0;k<4;k++)
				{
					if(g_str_has_suffix(filename,pictype[k]))
						{
							installWallpaper(filename);
							break;
						}
				}
			freeAndNull(&filename);
		}

	g_strfreev(array);
}

