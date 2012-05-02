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

#include <string.h>

#include "globals.h"
#include "thumbnails.h"
#include <gtk/gtk.h>
#include <stdlib.h>

void writeDBFile(char* filename,char* name,char* gtk,char* frame,char* icon,char* paper,char* cursor,char* thumb)
{

	FILE*	fd;
	char*	filedata;

	asprintf(&filedata,"[Data]\nName=%s\nThumbnail=%s\n",name,thumb);

	if (gtk!=NULL)
		asprintf(&filedata,"%sGtkTheme=%s\n",filedata,gtk);
	if (frame!=NULL)
		asprintf(&filedata,"%sXfwm4Theme=%s\n",filedata,frame);
	if (icon!=NULL)
		asprintf(&filedata,"%sIconTheme=%s\n",filedata,icon);
	if (cursor!=NULL)
		asprintf(&filedata,"%sCursorTheme=%s\n",filedata,cursor);
	if (paper!=NULL)
		asprintf(&filedata,"%sBackgroundImage=%s\n",filedata,paper);

	fd=fopen(filename,"w");

	fprintf(fd,"%s\n",filedata);
	fclose(fd);
}

gpointer rebuildDB(gpointer data)
{
	char*			buffer=NULL;
	char*			indexfile=NULL;
	char*			dbfile=NULL;
	char*			thumbfile=NULL;
	char*			framefolder=NULL;

	const gchar*	entry=NULL;
	GDir*			folder;
	GKeyFile*		keyfile=g_key_file_new();

	GdkPixbuf*		pixbuf;

	char*			gtkname=NULL;
	char*			framename=NULL;
	char*			iconname=NULL;
	char*			papername=NULL;
	char*			indexname=NULL;
	char*			displayname=NULL;
	char*			cursorname=NULL;

	GKeyFile*		metakeyfile=g_key_file_new();

	bool			makedb=false;
	char*			hidden=NULL;
	char			remdir[1024];
	long			makeornot=(long)data;

	if (makeornot==0)
		{
			if (g_file_test(dbFolder,G_FILE_TEST_IS_DIR))
				{
					sprintf(remdir,"rm -r %s",metaFolder);
					system(remdir);
					sprintf(remdir,"rm -r %s",framesFolder);
					system(remdir);
					sprintf(remdir,"rm -r %s",controlsFolder);
					system(remdir);
					sprintf(remdir,"rm -r %s",iconsFolder);
					system(remdir);
					sprintf(remdir,"rm -r %s",cursorsFolder);
					system(remdir);
					sprintf(remdir,"rm -r %s",wallpapersFolder);
					system(remdir);
				}
		}

	g_mkdir_with_parents(metaFolder,493);
	for(int i=0;i<2;i++)
		{
			folder=g_dir_open(themesArray[i],0,NULL);
			if(folder!=NULL)
				{
					entry=g_dir_read_name(folder);
					while(entry!=NULL)
						{
							asprintf(&dbfile,"%s/%i.%s.db",metaFolder,i,entry);
							if(!g_file_test(dbfile,G_FILE_TEST_EXISTS))
								{
									makedb=false;
									asprintf(&indexname,"%s/%s/index.theme",themesArray[i],entry);
									g_key_file_load_from_file(metakeyfile,indexname,G_KEY_FILE_NONE,NULL);

									if (g_file_test(indexname,G_FILE_TEST_EXISTS))
										{
											asprintf(&buffer,"%s/%s/xfwm4",themesArray[i],entry);
											if (g_file_test(buffer,G_FILE_TEST_IS_DIR))
												{
													displayname=g_key_file_get_string(metakeyfile,"Desktop Entry","Name",NULL);
													if(displayname==NULL)
														displayname=g_key_file_get_string(metakeyfile,"X-GNOME-Metatheme","Name",NULL);
													if (displayname==NULL)
														asprintf(&displayname,"%s",entry);

													gtkname=g_key_file_get_string(metakeyfile,"X-GNOME-Metatheme","GtkTheme",NULL);
													iconname=g_key_file_get_string(metakeyfile,"X-GNOME-Metatheme","IconTheme",NULL);
													cursorname=g_key_file_get_string(metakeyfile,"X-GNOME-Metatheme","CursorTheme",NULL);
													papername=g_key_file_get_string(metakeyfile,"X-GNOME-Metatheme","BackgroundImage",NULL);
													makedb=true;
												}
										}
									else
										{
											indexname=NULL;
											asprintf(&buffer,"%s/%s/xfwm4",themesArray[i],entry);
											if (g_file_test(buffer,G_FILE_TEST_IS_DIR))
												{
													asprintf(&buffer,"%s/%s/gtk-2.0",themesArray[i],entry);
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
											asprintf(&thumbfile,"%s/%s.png",metaFolder,entry);

											writeDBFile(dbfile,displayname,gtkname,framename,iconname,papername,cursorname,thumbfile);

											controlWidth=400;
											controlHeight=200;
											asprintf(&framefolder,"%s/%s",themesArray[i],entry);
											if (makeornot==0)
												{
													gdk_threads_enter();
														controlsPixbuf=create_gtk_theme_pixbuf(gtkname);
													gdk_threads_leave();
												}
											else
												controlsPixbuf=create_gtk_theme_pixbuf(gtkname);

											if(controlsPixbuf!=NULL)
												{
													getspace(framefolder);
													asprintf(&iconTheme,"%s",iconname);
													asprintf(&cursorTheme,"%s",cursorname);
													makeborder(framefolder,thumbfile);
													g_object_unref(controlsPixbuf);
													controlsPixbuf=NULL;
												}
										}

									freeAndNull(&dbfile);
									freeAndNull(&displayname);
									freeAndNull(&gtkname);
									freeAndNull(&framename);
									freeAndNull(&iconname);
									freeAndNull(&papername);
									freeAndNull(&cursorname);
									freeAndNull(&thumbfile);
									freeAndNull(&indexname);
									freeAndNull(&buffer);
									freeAndNull(&framefolder);
								}
							entry=g_dir_read_name(folder);
						}
					g_dir_close(folder);
				}
		}

	controlWidth=200;
	controlHeight=50;

//build frames
//gtkprev [border] /path/to/border /out/path/to/png
//makeborder(argv[2],argv[3]);
	g_mkdir_with_parents(framesFolder,493);
	for(int i=0;i<2;i++)
		{
			folder=g_dir_open(themesArray[i],0,NULL);
			if(folder!=NULL)
				{
					entry=g_dir_read_name(folder);
					while(entry!=NULL)
						{
							asprintf(&dbfile,"%s/%i.%s.db",framesFolder,i,entry);
							if(!g_file_test(dbfile,G_FILE_TEST_EXISTS))
								{
									asprintf(&buffer,"%s/%s/xfwm4",themesArray[i],entry);
									if (g_file_test(buffer,G_FILE_TEST_IS_DIR))
										{
											asprintf(&thumbfile,"%s/%s.png",framesFolder,entry);
											writeDBFile(dbfile,(char*)entry,NULL,(char*)entry,NULL,NULL,NULL,thumbfile);
											asprintf(&framefolder,"%s/%s",themesArray[i],entry);
											getspace(framefolder);
											makeborder(framefolder,thumbfile);
										}
									freeAndNull(&buffer);
									freeAndNull(&framefolder);
									freeAndNull(&dbfile);
									freeAndNull(&thumbfile);
								}
							entry=g_dir_read_name(folder);
						}
					g_dir_close(folder);
				}
		}

//build controls
//gtkprev [controls] gtkthemename /out/path/to/png
	g_mkdir_with_parents(controlsFolder,493);
	for(int i=0;i<2;i++)
		{
			folder=g_dir_open(themesArray[i],0,NULL);
			if(folder!=NULL)
				{
					entry=g_dir_read_name(folder);
					while(entry!=NULL)
						{
							asprintf(&dbfile,"%s/%i.%s.db",controlsFolder,i,entry);
							if(!g_file_test(dbfile,G_FILE_TEST_EXISTS))
								{
									asprintf(&buffer,"%s/%s/gtk-2.0",themesArray[i],entry);
									if (g_file_test(buffer,G_FILE_TEST_IS_DIR))
										{
											asprintf(&thumbfile,"%s/%s.png",controlsFolder,entry);
											controlsPixbuf=NULL;
											if (makeornot==0)
												{
													gdk_threads_enter();
														controlsPixbuf=create_gtk_theme_pixbuf((char*)entry);
													gdk_threads_leave();
												}
											else
												controlsPixbuf=create_gtk_theme_pixbuf((char*)entry);

											if(controlsPixbuf!=NULL)
												{
													gdk_pixbuf_savev(controlsPixbuf,thumbfile,"png",NULL,NULL,NULL);
													g_object_unref(controlsPixbuf);
													controlsPixbuf=NULL;
													writeDBFile(dbfile,(char*)entry,(char*)entry,NULL,NULL,NULL,NULL,thumbfile);
												}
										}
									freeAndNull(&buffer);
									freeAndNull(&dbfile);
									freeAndNull(&thumbfile);
								}
							entry=g_dir_read_name(folder);
						}
					g_dir_close(folder);
				}
		}

//buid icons
	g_mkdir_with_parents(iconsFolder,493);
	for(int i=0;i<2;i++)
		{
			folder=g_dir_open(iconsArray[i],0,NULL);
			if(folder!=NULL)
				{
					entry=g_dir_read_name(folder);
					while(entry!=NULL)
						{
							asprintf(&dbfile,"%s/%i.%s.db",iconsFolder,i,entry);
							if(!g_file_test(dbfile,G_FILE_TEST_EXISTS))
								{
									asprintf(&buffer,"%s/%s/cursors",iconsArray[i],entry);
									if (!g_file_test(buffer,G_FILE_TEST_IS_DIR))
										{
											asprintf(&indexfile,"%s/%s/index.theme",iconsArray[i],entry);
											if(g_key_file_load_from_file(keyfile,indexfile,G_KEY_FILE_NONE,NULL))
												{
													hidden=g_key_file_get_string(keyfile,"Icon Theme","Hidden",NULL);
													if (hidden==NULL || strcasecmp(hidden,"true")!=0)
														{
															displayname=g_key_file_get_string(keyfile,"Icon Theme","Name",NULL);
															asprintf(&thumbfile,"%s/%s.png",iconsFolder,entry);
															makeIcon((char*)entry,thumbfile);
															writeDBFile(dbfile,displayname,NULL,NULL,(char*)entry,NULL,NULL,thumbfile);
														}
												}
										}
								}
							entry=g_dir_read_name(folder);

							freeAndNull(&buffer);
							freeAndNull(&displayname);
							freeAndNull(&indexfile);
							freeAndNull(&dbfile);
							freeAndNull(&thumbfile);
							freeAndNull(&hidden);
						}
					g_dir_close(folder);
				}
		}

//cursors
//gtkprev [cursors] cursortheme /out/path/to/png
//makecursor(argv[2],argv[3]);
	g_mkdir_with_parents(cursorsFolder,493);
	for(int i=0;i<2;i++)
		{
			folder=g_dir_open(iconsArray[i],0,NULL);
			if(folder!=NULL)
				{
					entry=g_dir_read_name(folder);
					while(entry!=NULL)
						{
							asprintf(&dbfile,"%s/%i.%s.db",cursorsFolder,i,entry);
							if(!g_file_test(dbfile,G_FILE_TEST_EXISTS))
								{
									asprintf(&buffer,"%s/%s/cursors",iconsArray[i],entry);
									if (g_file_test(buffer,G_FILE_TEST_IS_DIR))
										{
											asprintf(&indexfile,"%s/%s/index.theme",iconsArray[i],entry);
											if(g_key_file_load_from_file(keyfile,indexfile,G_KEY_FILE_NONE,NULL))
												displayname=g_key_file_get_string(keyfile,"Icon Theme","Name",NULL);
											else
												asprintf(&displayname,entry);
											asprintf(&thumbfile,"%s/%s.png",cursorsFolder,entry);
											makecursor((char*)entry,thumbfile);
											writeDBFile(dbfile,displayname,NULL,NULL,NULL,NULL,(char*)entry,thumbfile);
										}

									freeAndNull(&buffer);
									freeAndNull(&displayname);
									freeAndNull(&indexfile);
									freeAndNull(&dbfile);
									freeAndNull(&thumbfile);
								}
							entry=g_dir_read_name(folder);
						}
					g_dir_close(folder);
				}
		}

	g_mkdir_with_parents(wallpapersFolder,493);
	for(int i=0;i<2;i++)
		{
			folder=g_dir_open(papersArray[i],0,NULL);
			if(folder!=NULL)
				{
					entry=g_dir_read_name(folder);
					while(entry!=NULL)
						{
							asprintf(&dbfile,"%s/%i.%s.db",wallpapersFolder,i,entry);
							if(!g_file_test(dbfile,G_FILE_TEST_EXISTS))
								{
									asprintf(&thumbfile,"%s/%s.png",wallpapersFolder,entry);
									asprintf(&displayname,"%s",entry);
									for(int j=strlen(displayname);j>0;j--)
										{
											if(displayname[j]=='.')
												{
													displayname[j]=0;
													break;
												}
										}
									asprintf(&buffer,"%s/%s",papersArray[i],entry);
									writeDBFile(dbfile,displayname,NULL,NULL,NULL,buffer,NULL,thumbfile);
									pixbuf=gdk_pixbuf_new_from_file_at_size(buffer,-1,64,NULL);
									gdk_pixbuf_savev(pixbuf,thumbfile,"png",NULL,NULL,NULL);
									g_object_unref(pixbuf);
									pixbuf=NULL;

									freeAndNull(&buffer);
									freeAndNull(&displayname);
									freeAndNull(&dbfile);
									freeAndNull(&thumbfile);
								}
							entry=g_dir_read_name(folder);
						}
					g_dir_close(folder);
				}
		}

	if (makeornot==0)
		gtk_main_quit();

	return(NULL);
}




