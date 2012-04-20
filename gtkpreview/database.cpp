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

void rebuildDB(void)
{
	char*		buffer;
	char*		indexfile;
	char*		dbfile;
	char*		thumbfile;
	char*		framefolder;

	const gchar*	entry;
	GDir*		folder;
	GKeyFile*	keyfile=g_key_file_new();
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
					thumbfile=NULL;
					dbfile=NULL;
					buffer=NULL;
					framefolder=NULL;

					makedb=false;
					asprintf(&dbfile,"%s/%s.db",metaFolder,entry);
					asprintf(&indexname,"%s/%s/index.theme",localThemes,entry);
					g_key_file_load_from_file(metakeyfile,indexname,G_KEY_FILE_NONE,NULL);

					if (g_file_test(indexname,G_FILE_TEST_EXISTS))
						{
						asprintf(&buffer,"%s/%s/xfwm4",localThemes,entry);
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
							asprintf(&thumbfile,"%s/%s.png",metaFolder,entry);

							writeDBFile(dbfile,displayname,gtkname,framename,iconname,papername,cursorname,thumbfile);

							gtkwidth=400;
							gtkheight=200;
							asprintf(&framefolder,"%s/%s",localThemes,entry);
							gtkPixbuf=create_gtk_theme_pixbuf(gtkname);
							if(gtkPixbuf!=NULL)
								{
									getspace(framefolder);
									asprintf(&iconTheme,"%s",iconname);
									asprintf(&cursorTheme,"%s",cursorname);
									makeborder(framefolder,thumbfile);
									g_object_unref(gtkPixbuf);
									gtkPixbuf=NULL;
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
							asprintf(&thumbfile,"%s/%s.png",framesFolder,entry);

							writeDBFile(dbfile,(char*)entry,NULL,(char*)entry,NULL,NULL,NULL,thumbfile);

							asprintf(&framefolder,"%s/%s",localThemes,entry);
							getspace(framefolder);
							makeborder(framefolder,thumbfile);
						}
					entry=g_dir_read_name(folder);

					freeAndNull(&buffer);
					freeAndNull(&framefolder);
					freeAndNull(&dbfile);
					freeAndNull(&thumbfile);
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
							asprintf(&thumbfile,"%s/%s.png",controlsFolder,entry);
							pixbuf=create_gtk_theme_pixbuf((char*)entry);
							if(pixbuf!=NULL)
								{
									gdk_pixbuf_savev(pixbuf,thumbfile,"png",NULL,NULL,NULL);
									g_object_unref(pixbuf);
									writeDBFile(dbfile,(char*)entry,(char*)entry,NULL,NULL,NULL,NULL,thumbfile);
								}
						}
					entry=g_dir_read_name(folder);

					freeAndNull(&buffer);
					freeAndNull(&dbfile);
					freeAndNull(&thumbfile);
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
									displayname=g_key_file_get_string(keyfile,"Icon Theme","Name",NULL);
									asprintf(&thumbfile,"%s/%s.png",iconsFolder,entry);
									makeIcon((char*)entry,thumbfile);
									writeDBFile(dbfile,displayname,NULL,NULL,(char*)entry,NULL,NULL,thumbfile);
								}
						}
					entry=g_dir_read_name(folder);

					freeAndNull(&buffer);
					freeAndNull(&displayname);
					freeAndNull(&indexfile);
					freeAndNull(&dbfile);
					freeAndNull(&thumbfile);
				}
			g_dir_close(folder);
		}
//cursors
//gtkprev [cursors] cursortheme /out/path/to/png
//makecursor(argv[2],argv[3]);
//writeDBFile(dbfile,displayname,gtkname,framename,iconname,papername,cursorname,thumbfile);
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
									displayname=g_key_file_get_string(keyfile,"Icon Theme","Name",NULL);
									asprintf(&thumbfile,"%s/%s.png",cursorsFolder,entry);
									makecursor((char*)entry,thumbfile);
									writeDBFile(dbfile,displayname,NULL,NULL,NULL,NULL,(char*)entry,thumbfile);
								}
						}

					freeAndNull(&buffer);
					freeAndNull(&displayname);
					freeAndNull(&indexfile);
					freeAndNull(&dbfile);
					freeAndNull(&thumbfile);

					entry=g_dir_read_name(folder);
				}
			g_dir_close(folder);
		}

	g_mkdir_with_parents(wallpapersFolder,493);
	if(folder=g_dir_open(localPapers,0,NULL))
		{
			entry=g_dir_read_name(folder);
			while(entry!=NULL)
				{
					asprintf(&dbfile,"%s/%s.db",wallpapersFolder,entry);
					asprintf(&thumbfile,"%s/%s.png",wallpapersFolder,entry);
					asprintf(&displayname,"%s",entry);
					for(int i=strlen(displayname);i>0;i--)
						{
							if(displayname[i]=='.')
								{
									displayname[i]=0;
									break;
								}
						}
					asprintf(&buffer,"%s/%s",localPapers,entry);
					writeDBFile(dbfile,displayname,NULL,NULL,NULL,buffer,NULL,thumbfile);
					pixbuf=gdk_pixbuf_new_from_file_at_size(buffer,-1,64,NULL);
					gdk_pixbuf_savev(pixbuf,thumbfile,"png",NULL,NULL,NULL);
					g_object_unref(pixbuf);

					freeAndNull(&buffer);
					freeAndNull(&displayname);
					freeAndNull(&dbfile);
					freeAndNull(&thumbfile);

					entry=g_dir_read_name(folder);
				}
			g_dir_close(folder);
		}
}




