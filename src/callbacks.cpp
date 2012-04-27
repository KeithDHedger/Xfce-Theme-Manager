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

void wallStyleChanged(GtkWidget* widget,gpointer data)
{
	char*	command;

	wallStyle=gtk_combo_box_get_active((GtkComboBox*)widget);
	asprintf(&command,"%s%i",XCONFSETSTYLE,wallStyle);
	system(command);
}

//do meta theme
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

//frame
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

//controls
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

//icons
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

//cursors
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

void launchCompEd(GtkWidget* window,gpointer data)
{
	system("xfce4-composite-editor");
}

void resetBright(GtkWidget* widget,gpointer data)
{
	char*		command;

	gtk_range_set_value((GtkRange*)data,0);
	asprintf(&command,"%s 0",XCONFSETBRIGHT);
	system(command);
	freeAndNull(&command);

}

void setBright(GtkWidget* widget,gpointer data)
{
	char*		command;
	gdouble	val=gtk_range_get_value((GtkRange*)widget);

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


void setFont(GtkWidget* widget,gpointer data)
{
	char*		command;

	if((long)data==0)
		asprintf(&command,"%s \"%s\"",XCONFSETWMFONT,gtk_font_button_get_font_name((GtkFontButton*)widget));
	else
		asprintf(&command,"%s \"%s\"",XCONFSETAPPFONT,gtk_font_button_get_font_name((GtkFontButton*)widget));

	system(command);
	freeAndNull(&command);
}

void resetFont(GtkWidget* widget,gpointer data)
{
	char*		command;

	if((long)data==0)
		{
			asprintf(&command,"%s \"%s\"",XCONFSETWMFONT,currentWMFont);
			gtk_font_button_set_font_name((GtkFontButton*)wmFontButton,currentWMFont);
		}
	else
		{
			asprintf(&command,"%s \"%s\"",XCONFSETAPPFONT,currentAppFont);
			gtk_font_button_set_font_name((GtkFontButton*)appFontButton,currentAppFont);
		}

	system(command);
	freeAndNull(&command);
}






