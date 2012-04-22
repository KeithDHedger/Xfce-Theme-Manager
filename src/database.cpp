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

#if 0
gboolean pulsebar(gpointer data)
{
GdkEvent* event;

event=gdk_event_new(GDK_EXPOSE);
	gdk_event_put(event);

	gtk_progress_bar_pulse((GtkProgressBar*)pbox);
	return(true);
}

gpointer updateBarTimerZZZZ(gpointer data)
{
	//GtkSettings *hold;
//	hold=gtk_settings_get_default();
	//g_object_set(hold,"gtk-theme-name",currentGtkTheme,"gtk-color-scheme","default",NULL);

gint func_ref = g_timeout_add (100, pulsebar, NULL);
printf("AAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
//gtk_main();

//
GdkEvent* event;

event=gdk_event_new(GDK_EXPOSE);

//while(true)
{
	printf("XXXXXXXXXXXXXXXXX\n");
	gtk_progress_bar_pulse((GtkProgressBar*)pbox);
	gtk_widget_queue_draw(pbox);
	//g_main_context_iteration(NULL,false);
	//gtk_main_iteration_do               (true);
	//gtk_main_do_event(event);
event=gdk_event_new(GDK_EXPOSE);
	gdk_event_put(event);
	//gtk_main_do_event(event);
	//gtk_main_iteration();
	g_main_context_iteration(NULL,false);
}
//	return(true);
}
	GtkWidget*		windowp;


gpointer makeProgresswin(gpointer data)
{
	GtkWidget*		vbox;


	windowp=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size((GtkWindow*)windowp,400,40);
	vbox=gtk_vbox_new(FALSE, 0);
	pbox=gtk_progress_bar_new();
	gtk_progress_bar_pulse((GtkProgressBar*)pbox);

	gtk_progress_bar_set_orientation((GtkProgressBar*)pbox,GTK_PROGRESS_LEFT_TO_RIGHT);

	gtk_box_pack_start(GTK_BOX(vbox),pbox,false,false,8);
	gtk_container_add(GTK_CONTAINER(windowp),vbox);
//	gint func_ref = g_timeout_add (100, updateBarTimer, NULL);


//	GMainLoop *   ml=g_main_loop_new(NULL,false);
	gtk_widget_show_all(windowp);
//	gint func_ref = g_timeout_add (100, updateBarTimer, NULL);
//	  g_main_loop_run                     (ml);
	
	
//	while(true)
//		{
//		gtk_progress_bar_pulse((GtkProgressBar*)pbox);
//		gtk_widget_queue_draw(pbox);
  //  		g_main_context_iteration(NULL,false);
    //		}
	//gtk_widget_show(window);
	//g_idle_add(lengthy_func_done, NULL);
//	gtk_main;
}

#if 0
gpointer makeProgress(gpointer data)
{
	GtkWidget*		window;
	GtkWidget*		vbox;


	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size((GtkWindow*)window,400,40);
	vbox=gtk_vbox_new(FALSE, 0);
	pbox=gtk_progress_bar_new();
	gtk_progress_bar_pulse((GtkProgressBar*)pbox);

	gtk_progress_bar_set_orientation((GtkProgressBar*)pbox,GTK_PROGRESS_LEFT_TO_RIGHT);

	gtk_box_pack_start(GTK_BOX(vbox),pbox,false,false,8);
	gtk_container_add(GTK_CONTAINER(window),vbox);
//	gint func_ref = g_timeout_add (100, updateBarTimer, NULL);


	GMainLoop *   ml=g_main_loop_new(NULL,false);
	gtk_widget_show_all(window);
	gint func_ref = g_timeout_add (100, updateBarTimer, NULL);
	  g_main_loop_run                     (ml);
	
	
//	while(true)
//		{
//		gtk_progress_bar_pulse((GtkProgressBar*)pbox);
//		gtk_widget_queue_draw(pbox);
  //  		g_main_context_iteration(NULL,false);
    //		}
	//gtk_widget_show(window);
	//g_idle_add(lengthy_func_done, NULL);
//	gtk_main;
}
#endif
#endif
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
	char*		buffer;
	char*		indexfile;
	char*		dbfile;
	char*		thumbfile;
	char*		framefolder;

	const gchar*	entry;
	GDir*		folder;
	GKeyFile*	keyfile=g_key_file_new();

	GdkPixbuf*	pixbuf;

	char*		gtkname;
	char*		framename;
	char*		iconname;
	char*		papername;
	char*		indexname;
	char*		displayname;
	char*		cursorname;

	GKeyFile*	metakeyfile=g_key_file_new();

	bool		makedb;
	char*		hidden;



#if 1
	g_mkdir_with_parents(metaFolder,493);
	for(int i=0;i<2;i++)
		{
			folder=g_dir_open(themesArray[i],0,NULL);
			if(folder!=NULL)
				{
					entry=g_dir_read_name(folder);
					while(entry!=NULL)
						{
							makedb=false;
							asprintf(&dbfile,"%s/%s.db",metaFolder,entry);
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
									asprintf(&dbfile,"%s/%s.db",metaFolder,entry);
									asprintf(&thumbfile,"%s/%s.png",metaFolder,entry);

									writeDBFile(dbfile,displayname,gtkname,framename,iconname,papername,cursorname,thumbfile);

									gtkwidth=400;
									gtkheight=200;
									asprintf(&framefolder,"%s/%s",themesArray[i],entry);
									gdk_threads_enter();
									gtkPixbuf=create_gtk_theme_pixbuf(gtkname);
									gdk_threads_leave();
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
					g_dir_close(folder);
				}
		}

#endif

	gtkwidth=200;
	gtkheight=50;


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
							asprintf(&buffer,"%s/%s/xfwm4",themesArray[i],entry);
							if (g_file_test(buffer,G_FILE_TEST_IS_DIR))
								{
									asprintf(&dbfile,"%s/%s.db",framesFolder,entry);
									asprintf(&thumbfile,"%s/%s.png",framesFolder,entry);

									writeDBFile(dbfile,(char*)entry,NULL,(char*)entry,NULL,NULL,NULL,thumbfile);

									asprintf(&framefolder,"%s/%s",themesArray[i],entry);
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
		}

#if 1
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
							asprintf(&buffer,"%s/%s/gtk-2.0",themesArray[i],entry);
							if (g_file_test(buffer,G_FILE_TEST_IS_DIR))
								{
									asprintf(&dbfile,"%s/%s.db",controlsFolder,entry);
									asprintf(&thumbfile,"%s/%s.png",controlsFolder,entry);
									gdk_threads_enter();
									pixbuf=create_gtk_theme_pixbuf((char*)entry);
									gdk_threads_leave();
									
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
		}
#endif

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
							asprintf(&buffer,"%s/%s/cursors",iconsArray[i],entry);
							if (!g_file_test(buffer,G_FILE_TEST_IS_DIR))
								{
									asprintf(&indexfile,"%s/%s/index.theme",iconsArray[i],entry);
									asprintf(&dbfile,"%s/%s.db",iconsFolder,entry);
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
//writeDBFile(dbfile,displayname,gtkname,framename,iconname,papername,cursorname,thumbfile);
	g_mkdir_with_parents(cursorsFolder,493);
	for(int i=0;i<2;i++)
		{
			folder=g_dir_open(iconsArray[i],0,NULL);
			if(folder!=NULL)
				{
					entry=g_dir_read_name(folder);
					while(entry!=NULL)
						{
							asprintf(&buffer,"%s/%s/cursors",iconsArray[i],entry);
							if (g_file_test(buffer,G_FILE_TEST_IS_DIR))
								{
									asprintf(&indexfile,"%s/%s/index.theme",iconsArray[i],entry);
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
							asprintf(&dbfile,"%s/%s.db",wallpapersFolder,entry);
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

							freeAndNull(&buffer);
							freeAndNull(&displayname);
							freeAndNull(&dbfile);
							freeAndNull(&thumbfile);

							entry=g_dir_read_name(folder);
						}
					g_dir_close(folder);
				}
		}

gtk_main_quit();

return(NULL);

	return NULL;
}




