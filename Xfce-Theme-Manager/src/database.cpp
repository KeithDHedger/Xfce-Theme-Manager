/*
 *
 * ©K. D. Hedger. Tue 20 Oct 15:53:24 BST 2015 keithdhedger@gmail.com

 * This file (database.cpp) is part of Xfce-Theme-Manager.

 * Xfce-Theme-Manager is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.

 * Xfce-Theme-Manager is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Xfce-Theme-Manager.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>

#include "globals.h"
#include "thumbnails.h"
#include <stdlib.h>

void writeDBFile(char* filename,char* name,char* gtk,char* frame,char* icon,char* paper,char* cursor,char* thumb,bool ismeta)
{
	FILE*	fd;
	char*	filedata;

	asprintf(&filedata,"[Data]\nName=%s\nThumbnail=%s\n",name,thumb);

	if (ismeta==true)
		{
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
		}
	else
		{
			if (gtk!=NULL)
				asprintf(&filedata,"%sThemeName=%s\n",filedata,gtk);
			if (frame!=NULL)
				asprintf(&filedata,"%sThemeName=%s\n",filedata,frame);
			if (icon!=NULL)
				asprintf(&filedata,"%sThemeName=%s\n",filedata,icon);
			if (cursor!=NULL)
				asprintf(&filedata,"%sThemeName=%s\n",filedata,cursor);
			if (paper!=NULL)
				asprintf(&filedata,"%sThemeName=%s\n",filedata,paper);
		}
	
	fd=fopen(filename,"w");

	fprintf(fd,"%s\n",filedata);
	fclose(fd);
}

void updateEntries(char* dbfolder,char** datafolders,const char* subfolder)
{

	const gchar*	entry=NULL;
	GDir*			folder;
	char*			partname=NULL;
	char			filepath[2048];
	bool			found;
	char*			thumbnail;

	GKeyFile*		keyfile=g_key_file_new();

	folder=g_dir_open(dbfolder,0,NULL);
	if(folder!=NULL)
		{
			chdir(dbfolder);
			entry=g_dir_read_name(folder);
			while(entry!=NULL)
				{
					if(g_str_has_suffix(entry,".db"))
						{
							g_key_file_load_from_file(keyfile,entry,G_KEY_FILE_NONE,NULL);
							partname=g_key_file_get_string(keyfile,"Data","Name",NULL);
							if(partname!=NULL)
								{
									found=false;
									for(int i=0;i<2;i++)
										{
											sprintf((char*)&filepath,"%s/%s/%s",datafolders[i],partname,subfolder);
											if(g_file_test(filepath,G_FILE_TEST_EXISTS))
												found=true;
										}

									if(found==false)
										{
											sprintf((char*)&filepath,"rm \"%s\"",entry);
											system(filepath);
											thumbnail=g_key_file_get_string(keyfile,"Data","Thumbnail",NULL);
											sprintf((char*)&filepath,"rm \"%s\"",thumbnail);
											system(filepath);
											g_free(thumbnail);
										}
									g_free(partname);
								}
						}
					entry=g_dir_read_name(folder);
				}
			g_dir_close(folder);
		}
}

void removeDeleted(void)
{
	char*			dbfile=NULL;
	const gchar*	entry=NULL;
	GDir*			folder;
	char*			displayname=NULL;
	char			filepath[2048];
	bool			found;
	bool			foundfirst;
	char*			thumbnail;

	GKeyFile*		keyfile=g_key_file_new();

//meta
//special case

	folder=g_dir_open(metaFolder,0,NULL);
	if(folder!=NULL)
		{
			entry=g_dir_read_name(folder);
			while(entry!=NULL)
				{
					asprintf(&dbfile,"%s/%s",metaFolder,entry);
					if(g_str_has_suffix(dbfile,".db"))
						{
							g_key_file_load_from_file(keyfile,dbfile,G_KEY_FILE_NONE,NULL);
							found=false;
							foundfirst=false;
							displayname=g_key_file_get_string(keyfile,"Data","GtkTheme",NULL);
							if(displayname!=NULL)
								{
									for(int i=0;i<2;i++)
										{
											sprintf((char*)&filepath,"%s/%s/gtk-2.0",themesArray[i],displayname);
											if(g_file_test(filepath,G_FILE_TEST_EXISTS))
												foundfirst=true;
										}
									g_free(displayname);
								}

							displayname=g_key_file_get_string(keyfile,"Data","Xfwm4Theme",NULL);
							if(displayname!=NULL)
								{
									for(int i=0;i<2;i++)
										{
											sprintf((char*)&filepath,"%s/%s/xfwm4",themesArray[i],displayname);
											if((g_file_test(filepath,G_FILE_TEST_EXISTS)==true) && (foundfirst==true))
												found=true;
										}
									g_free(displayname);
								}

							if(found==false)
								{
									sprintf((char*)&filepath,"rm \"%s\"",dbfile);
									system(filepath);
									thumbnail=g_key_file_get_string(keyfile,"Data","Thumbnail",NULL);
									sprintf((char*)&filepath,"rm \"%s\"",thumbnail);
									g_free(thumbnail);
									system(filepath);
								}
						}
					g_free(dbfile);
					entry=g_dir_read_name(folder);
				}
			g_dir_close(folder);
		}

//frames
	updateEntries(framesFolder,themesArray,"xfwm4");

//controls
	updateEntries(controlsFolder,themesArray,"gtk-2.0");

//icons
	updateEntries(iconsFolder,iconsArray,"");

//cursors
	updateEntries(cursorsFolder,iconsArray,"cursors");

//backdrops
//special case
	folder=g_dir_open(wallpapersFolder,0,NULL);
	if(folder!=NULL)
		{
			chdir(wallpapersFolder);
			entry=g_dir_read_name(folder);
			while(entry!=NULL)
				{
					if(g_str_has_suffix(entry,".db"))
						{
							g_key_file_load_from_file(keyfile,entry,G_KEY_FILE_NONE,NULL);
							displayname=g_key_file_get_string(keyfile,"Data","ThemeName",NULL);
							if(!g_file_test(displayname,G_FILE_TEST_EXISTS))
								{
									sprintf((char*)&filepath,"rm \"%s\"",entry);
									system(filepath);
									thumbnail=g_key_file_get_string(keyfile,"Data","Thumbnail",NULL);
									sprintf((char*)&filepath,"rm \"%s\"",thumbnail);
									system(filepath);
									g_free(thumbnail);
								}
							g_free(displayname);
						}
					entry=g_dir_read_name(folder);
				}
			g_dir_close(folder);
		}
}

gpointer rebuildDB(gpointer data)
{
	char*			buffer=NULL;
	char*			buffer2=NULL;
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
	long			makeornot=(long)data;

	if (makeornot==0)
		{
			if (g_file_test(dbFolder,G_FILE_TEST_IS_DIR))
				{
					snprintf(generalBuffer,GENBUFFERSIZE,"rm -r %s",metaFolder);
					system(generalBuffer);
					snprintf(generalBuffer,GENBUFFERSIZE,"rm -r %s",framesFolder);
					system(generalBuffer);
					snprintf(generalBuffer,GENBUFFERSIZE,"rm -r %s",controlsFolder);
					system(generalBuffer);
					snprintf(generalBuffer,GENBUFFERSIZE,"rm -r %s",iconsFolder);
					system(generalBuffer);
					snprintf(generalBuffer,GENBUFFERSIZE,"rm -r %s",cursorsFolder);
					system(generalBuffer);
					snprintf(generalBuffer,GENBUFFERSIZE,"rm -r %s",wallpapersFolder);
					system(generalBuffer);
				}
		}

	if(makeornot==1)
		{
			removeDeleted();
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
											asprintf(&buffer2,"%s/%s/gtk-2.0",themesArray[i],entry);
											if (g_file_test(buffer,G_FILE_TEST_IS_DIR) && g_file_test(buffer2,G_FILE_TEST_IS_DIR))
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

											writeDBFile(dbfile,displayname,gtkname,framename,iconname,papername,cursorname,thumbfile,true);

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
									freeAndNull(&buffer2);
									freeAndNull(&framefolder);
								}
							entry=g_dir_read_name(folder);
						}
					g_dir_close(folder);
				}
		}

	controlWidth=GTKWIDTH;
	controlHeight=GTKHEIGHT;

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
											writeDBFile(dbfile,(char*)entry,NULL,(char*)entry,NULL,NULL,NULL,thumbfile,false);
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
													writeDBFile(dbfile,(char*)entry,(char*)entry,NULL,NULL,NULL,NULL,thumbfile,false);
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
													if (hidden==NULL || g_ascii_strcasecmp(hidden,"true")!=0)
														{
															displayname=g_key_file_get_string(keyfile,"Icon Theme","Name",NULL);
															asprintf(&thumbfile,"%s/%s.png",iconsFolder,entry);
															makeIcon((char*)entry,thumbfile);
															writeDBFile(dbfile,displayname,NULL,NULL,(char*)entry,NULL,NULL,thumbfile,false);
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
												asprintf(&displayname,"%s",entry);

											asprintf(&thumbfile,"%s/%s.png",cursorsFolder,entry);
											makecursor((char*)entry,thumbfile);
											writeDBFile(dbfile,displayname,NULL,NULL,NULL,NULL,(char*)entry,thumbfile,false);
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
					folder=NULL;
				}
		}

//wallpapers
	g_mkdir_with_parents(wallpapersFolder,493);
	for(int i=0;i<2;i++)
		{
			folder=g_dir_open(papersArray[i],0,NULL);
			if(folder!=NULL)
				{
					entry=g_dir_read_name(folder);
					while(entry!=NULL)
						{
							snprintf(generalBuffer,GENBUFFERSIZE,"%s/%s",papersArray[i],entry);
							if(g_file_test(generalBuffer,G_FILE_TEST_IS_DIR)==false)
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
											writeDBFile(dbfile,displayname,NULL,NULL,NULL,buffer,NULL,thumbfile,false);
											pixbuf=gdk_pixbuf_new_from_file_at_size(buffer,-1,256,NULL);
											gdk_pixbuf_savev(pixbuf,thumbfile,"png",NULL,NULL,NULL);
											g_object_unref(pixbuf);
											pixbuf=NULL;

											freeAndNull(&buffer);
											freeAndNull(&displayname);
											freeAndNull(&dbfile);
											freeAndNull(&thumbfile);
										}
								}
							entry=g_dir_read_name(folder);
						}
					g_dir_close(folder);
				}
		}

	g_key_file_free(metakeyfile);
	g_key_file_free(keyfile);
	if ((makeornot==0) && (noGui==false))
		gtk_main_quit();

	return(NULL);
}




