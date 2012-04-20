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
 * database.cpp
 */

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gtk/gtk.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <X11/Xcursor/Xcursor.h>
#include <glib/gstdio.h>
#include <fcntl.h>

#include "globals.h"

extern GdkPixbuf * create_gtk_theme_pixbuf(char* name);
extern void getspace(char* folder);
extern void makeborder(char* folder,char* outframe);
extern void makecursor(char* theme,char* outPath);
extern void makeIcon(char* themename,char* outPath);

void rebuildDB(void)
{
	char*		buffer;
	char*		buffer2;
	char*		indexfile;
	char*		dbfile;

	const gchar*	entry;
	GDir*		folder;
	int		entrylen;
	GKeyFile*	keyfile=g_key_file_new();
	char*		name;
	char*		set;
	char*		thumb;
	FILE*		fd;

	GdkPixbuf*	pixbuf;

	char*		gtkname;
	char*		framename;
	char*		iconname;
	char*		papername;
	char*		indexname;
	char*		displayname;
	char*		cursorname;

	GKeyFile*	metakeyfile=g_key_file_new();
	gchar*		temp=NULL;

	bool		makedb;
//build themes
//gtkprev [theme] gtkthemename /path/to/border /out/path/to/png
	g_mkdir_with_parents(metaFolder,493);

	if(folder=g_dir_open(localThemes,0,NULL))
		{
			entry=g_dir_read_name(folder);
			while(entry!=NULL)
				{
					gtkname=NULL;
					framename=NULL;
					iconname=NULL;
					papername=NULL;
					indexname=NULL;
					displayname=NULL;
					cursorname=NULL;
					makedb=false;

					asprintf(&dbfile,"%s/%s.db",metaFolder,entry);
					asprintf(&indexname,"%s/%s/index.theme",localThemes,entry);
					g_key_file_load_from_file(metakeyfile,indexname,G_KEY_FILE_NONE,NULL);

					if (g_file_test(indexname,G_FILE_TEST_EXISTS))
						{
						asprintf(&buffer,"%s/%s/xfwm4",localThemes,entry);
						if (g_file_test(buffer,G_FILE_TEST_IS_DIR))
							{
								temp=NULL;
								temp=g_key_file_get_string(metakeyfile,"Desktop Entry","Name",NULL);
								if(temp==NULL)
									temp=g_key_file_get_string(metakeyfile,"X-GNOME-Metatheme","Name",NULL);
								if (temp==NULL)
									asprintf(&displayname,"%s",entry);
								else
									{
										asprintf(&displayname,"%s",temp);
										g_free(temp);
										temp=NULL;
									}
								temp=g_key_file_get_string(metakeyfile,"X-GNOME-Metatheme","GtkTheme",NULL);
								if (temp!=NULL)
									{
										asprintf(&gtkname,"%s",temp);
										g_free(temp);
										temp=NULL;
									}
								temp=g_key_file_get_string(metakeyfile,"X-GNOME-Metatheme","IconTheme",NULL);
								if (temp!=NULL)
									{
										asprintf(&iconname,"%s",temp);
										g_free(temp);
										temp=NULL;
									}
								temp=g_key_file_get_string(metakeyfile,"X-GNOME-Metatheme","CursorTheme",NULL);
								if (temp!=NULL)
									{
										asprintf(&cursorname,"%s",temp);
										g_free(temp);
										temp=NULL;
									}
								temp=g_key_file_get_string(metakeyfile,"X-GNOME-Metatheme","BackgroundImage",NULL);
								if (temp!=NULL)
									{
										asprintf(&papername,"%s",temp);
										g_free(temp);
										temp=NULL;
									}
								makedb=true;
							}
						}
					else
						{
							indexname[0]=0;
							asprintf(&buffer,"%s/%s/xfwm4",localThemes,entry);
							if (g_file_test(buffer,G_FILE_TEST_IS_DIR))
								{
									asprintf(&buffer,"%s/%s/gtk-2.0",localThemes,entry);
									if (g_file_test(buffer,G_FILE_TEST_IS_DIR))
										{
											asprintf(&displayname,"%s",entry);
											asprintf(&gtkname,"%s",entry);
											makedb=true;
										}
								}
						}


					if(makedb==true)
						{
							asprintf(&framename,"%s",entry);
							asprintf(&dbfile,"%s/%s.db",metaFolder,entry);
							fd=fopen(dbfile,"w");
							asprintf(&buffer,"%s/%s.png",metaFolder,entry);
							fprintf(fd,"[Data]\nName=%s\nThumbnail=%s\nGtkTheme=%s\nXfwm4Theme=%s\nIconTheme=%s\nCursorTheme=%s\nBackgroundImage=%s\n"
							,displayname,buffer,gtkname,framename,iconname,cursorname,papername);
							fclose(fd);
							gtkwidth=400;
							gtkheight=200;
							asprintf(&buffer2,"%s/%s",localThemes,entry);
							gtkPixbuf=create_gtk_theme_pixbuf(gtkname);
							if(gtkPixbuf!=NULL)
								{
									getspace(buffer);
									printf("%s\n%s\n",buffer,buffer2);
									asprintf(&iconTheme,"%s",iconname);
									asprintf(&cursorTheme,"%s",cursorname);
									makeborder(buffer2,buffer);
									g_object_unref(gtkPixbuf);
									gtkPixbuf=NULL;
								}

						}
					entry=g_dir_read_name(folder);
				}
		}
	
	g_dir_close(folder);

	gtkwidth=200;
	gtkheight=50;

//build frames
//gtkprev [border] /path/to/border /out/path/to/png
//makeborder(argv[2],argv[3]);
	g_mkdir_with_parents(framesFolder,493);
	if(folder=g_dir_open(localThemes,0,NULL))
		{
			entry=g_dir_read_name(folder);
			while(entry!=NULL)
				{
					asprintf(&buffer,"%s/%s/xfwm4",localThemes,entry);
					if (g_file_test(buffer,G_FILE_TEST_IS_DIR))
						{
							asprintf(&dbfile,"%s/%s.db",framesFolder,entry);
							fd=fopen(dbfile,"w");
							asprintf(&buffer,"%s/%s.png",framesFolder,entry);
							fprintf(fd,"[Data]\nName=%s\nThumbnail=%s\nXconfName=%s",entry,buffer,entry);
							fclose(fd);
							asprintf(&buffer2,"%s/%s",localThemes,entry);
							makeborder(buffer2,buffer);
						}
					entry=g_dir_read_name(folder);
				}
			g_dir_close(folder);
		}

//build controls
//gtkprev [controls] gtkthemename /out/path/to/png
	g_mkdir_with_parents(controlsFolder,493);
	if(folder=g_dir_open(localThemes,0,NULL))
		{
			entry=g_dir_read_name(folder);
			while(entry!=NULL)
				{
					asprintf(&buffer,"%s/%s/gtk-2.0",localThemes,entry);
					if (g_file_test(buffer,G_FILE_TEST_IS_DIR))
						{
							asprintf(&dbfile,"%s/%s.db",controlsFolder,entry);

							fd=fopen(dbfile,"w");
							asprintf(&buffer,"%s/%s.png",controlsFolder,entry);
							pixbuf=create_gtk_theme_pixbuf((char*)entry);
							if(pixbuf!=NULL)
								{
									gdk_pixbuf_savev(pixbuf,buffer,"png",NULL,NULL,NULL);
									g_object_unref(pixbuf);
								}
							fprintf(fd,"[Data]\nName=%s\nThumbnail=%s\nXconfName=%s",entry,buffer,entry);
							fclose(fd);
						}
					entry=g_dir_read_name(folder);
				}
			g_dir_close(folder);
		}

//buid icons
	g_mkdir_with_parents(iconsFolder,493);
	if(folder=g_dir_open(localIcons,0,NULL))
		{
			entry=g_dir_read_name(folder);
			while(entry!=NULL)
				{
					asprintf(&buffer,"%s/%s/cursors",localIcons,entry);
					if (!g_file_test(buffer,G_FILE_TEST_IS_DIR))
						{
							asprintf(&indexfile,"%s/%s/index.theme",localIcons,entry);
							asprintf(&dbfile,"%s/%s.db",iconsFolder,entry);
							if(g_key_file_load_from_file(keyfile,indexfile,G_KEY_FILE_NONE,NULL))
								{
									name=g_key_file_get_string(keyfile,"Icon Theme","Name",NULL);
									fd=fopen(dbfile,"w");
									asprintf(&buffer,"%s/%s.png",iconsFolder,entry);
									makeIcon((char*)entry,(char*)buffer);
									fprintf(fd,"[Data]\nName=%s\nThumbnail=%s\nXconfName=%s",name,buffer,entry);
									fclose(fd);
									g_free(name);
								}
						}
					entry=g_dir_read_name(folder);
				}
			g_dir_close(folder);
		}
//cursors
//gtkprev [cursors] cursortheme /out/path/to/png
//makecursor(argv[2],argv[3]);
	g_mkdir_with_parents(cursorsFolder,493);
	if(folder=g_dir_open(localIcons,0,NULL))
		{
			entry=g_dir_read_name(folder);
			while(entry!=NULL)
				{
					asprintf(&buffer,"%s/%s/cursors",localIcons,entry);
					if (g_file_test(buffer,G_FILE_TEST_IS_DIR))
						{
							asprintf(&indexfile,"%s/%s/index.theme",localIcons,entry);
							asprintf(&dbfile,"%s/%s.db",cursorsFolder,entry);
							if(g_key_file_load_from_file(keyfile,indexfile,G_KEY_FILE_NONE,NULL))
								{
									name=g_key_file_get_string(keyfile,"Icon Theme","Name",NULL);
									fd=fopen(dbfile,"w");
									asprintf(&buffer,"%s/%s.png",cursorsFolder,entry);
									makecursor((char*)entry,(char*)buffer);
									fprintf(fd,"[Data]\nName=%s\nThumbnail=%s\nXconfName=%s",name,buffer,entry);
									fclose(fd);
									g_free(name);
								}
						}
					entry=g_dir_read_name(folder);
				}
			g_dir_close(folder);
		}

}

