/*
 * Original author of parts of gtkpreview David D Lowe <daviddlowe.flimm@gmail.com>
 * Parts of cursor preveiw Copyright(c)2008 Nick Schermer <nick@xfce.org> & Jannis Pohlmann <jannis@xfce.org>
 * from xfce4-settings-4.6.5/dialogs/mouse-settings
 *
 * Parts of xwm4 4.10pre
 *
 * oroborus -(c)2001 Ken Lynch
 * xfwm4    -(c)2002-2011 Olivier Fourdan
 *
 * Seriously mucked about by:
 *
 * K.D.Hedger 2012 <kdhedger68713@gmail.com>
 *
 * gui.cpp
 */
 
 /* 
 * Parts of this code taken from the fspot application
 * Specifically the f_pixbuf_from_cairo_surface subroutine
 *
 * Copyright(C)2001, 2002, 2003 The Free Software Foundation, Inc.
 * Copyright(C)2003 Ettore Perazzoli
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or(at your option)any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * Author: Paolo Bacchilega <paolo.bacch@tin.it>
 *
 * Adapted by Ettore Perazzoli <ettore@perazzoli.org>
 */

/* Some bits are based upon the GIMP source code, the original copyright
 * note follows:
 *
 * The GIMP -- an image manipulation program
 * Copyright(C)1995 Spencer Kimball and Peter Mattis
*/
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <sys/stat.h>

#include "globals.h"
#include "callbacks.h"

int			size=128;
bool			addView=true;
GtkWidget*		icon_view;
GtkListStore*	store;


bool isCurrent(char* themename,const char* catagory,char* name)
{
	bool	retval=false;

	if(themename!=NULL)
		{
			if((g_ascii_strcasecmp(lastGtkTheme,themename)==0)&&(g_ascii_strcasecmp("controls",catagory)==0))
				retval=true;

			if((g_ascii_strcasecmp(lastCursorTheme,themename)==0)&&(g_ascii_strcasecmp("cursors",catagory)==0))
				retval=true;

			if((g_ascii_strcasecmp(lastWmTheme,themename)==0)&&(g_ascii_strcasecmp("frames",catagory)==0))
				retval=true;

			if((g_ascii_strcasecmp(lastIconTheme,themename)==0)&&(g_ascii_strcasecmp("icons",catagory)==0))
				retval=true;

			if((g_ascii_strcasecmp(lastWallPaper,themename)==0)&&(g_ascii_strcasecmp("wallpapers",catagory)==0))
				retval=true;
		}
	else
		{
			if(lastMetaTheme!=NULL)
				{
					if((g_ascii_strcasecmp(lastMetaTheme,name)==0)&&((g_ascii_strcasecmp("meta",catagory)==0)||(g_ascii_strcasecmp("custom",catagory)==0)))
					retval=true;
				}
		}

	return(retval);
}

GtkWidget *imageBox(char* filename,char* text,const char* catagory,char* themename)
{
	GtkWidget*	box;
	GtkWidget*	hbox;
	GtkWidget*	label;
	GtkWidget*	image;
	GtkWidget*	stockimage=gtk_image_new_from_stock(GTK_STOCK_YES,GTK_ICON_SIZE_SMALL_TOOLBAR);;
	GtkWidget*	stockimage2=gtk_image_new_from_pixbuf(blankImage);
	GtkWidget*	stockimage3=gtk_image_new_from_pixbuf(blankImage);

	gtk_widget_set_size_request(stockimage,24,24);
	gtk_widget_set_size_request(stockimage2,24,24);
	gtk_widget_set_size_request(stockimage3,24,24);

  /* Create box for image and label */
	box=gtk_vbox_new(FALSE, 0);
	hbox=gtk_hbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(box),0);

	image=gtk_image_new_from_file(filename);
	label=gtk_label_new(text);

	gtk_box_pack_start(GTK_BOX(box),image,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(box),label,TRUE,TRUE,0);
	if(isCurrent(themename,catagory,text)==true)
		{
			gtk_box_pack_end(GTK_BOX(hbox),stockimage,FALSE,FALSE,0);
			gtk_box_pack_start(GTK_BOX(hbox),stockimage2,FALSE,FALSE,0);
		}
	else
		{
			gtk_box_pack_end(GTK_BOX(hbox),stockimage2,FALSE,FALSE,0);
			gtk_box_pack_start(GTK_BOX(hbox),stockimage3,FALSE,FALSE,0);
		}

	gtk_box_pack_start(GTK_BOX(hbox),box,TRUE,TRUE,0);

	return(hbox);
}

void freeNames(gpointer data)
{
	freeAndNull((char**)&data);
}

gint sortFunc(gconstpointer a,gconstpointer b)
{
	return(g_ascii_strcasecmp((const char*)a,(const char*)b));
}



GdkPixbuf *f_pixbuf_from_cairo_surface(cairo_surface_t *source)
{
	gint width=cairo_image_surface_get_width(source);
	gint height=cairo_image_surface_get_height(source);
	GdkPixbuf *pixbuf=gdk_pixbuf_new(GDK_COLORSPACE_RGB,TRUE,8,width,height);

	guchar *gdk_pixels=gdk_pixbuf_get_pixels(pixbuf);
	int gdk_rowstride=gdk_pixbuf_get_rowstride(pixbuf);
	int n_channels=gdk_pixbuf_get_n_channels(pixbuf);

	cairo_surface_t *surface;
	cairo_t *ctx;

	//int j;

	surface=cairo_image_surface_create_for_data(gdk_pixels,CAIRO_FORMAT_ARGB32,width, height, gdk_rowstride);
	ctx=cairo_create(surface);
	cairo_set_source_surface(ctx, source, 0, 0);

	cairo_mask_surface(ctx, source, 0, 0);
//else
//	  cairo_paint(ctx);

	for(int j=height; j; j--)
		{
			guchar *p=gdk_pixels;
			guchar *end=p + 4 * width;
			guchar tmp;

			while(p < end)
				{
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
					tmp=p[0];
					p[0]=p[2];
					p[2]=tmp;
#else	  
					tmp=p[0];
					p[0]=p[3];
					p[3]=p[2];
					p[2]=p[1];
					p[1]=tmp;
#endif
					p += 4;
				}

			gdk_pixels += gdk_rowstride;
		}

	cairo_destroy(ctx);
	cairo_surface_destroy(surface);

	return pixbuf;
}

void addIconEntry(GtkListStore *store,const char* iconPng,const char* iconName,char* dbPath,char* subfolder,char* themename)
{
	GtkTreeIter	iter;
	GdkPixbuf*	pixbuf;
	GdkPixbuf*	star;

GtkWidget * starwidget;
int pixWid,pixHite,starWid,starHite;

	gtk_list_store_append(store,&iter);
	pixbuf=gdk_pixbuf_new_from_file_at_size(iconPng,previewSize,-1,NULL);

if(isCurrent(themename,subfolder,(char*)iconName)==true)
	{
		pixWid=gdk_pixbuf_get_width(pixbuf);
		pixHite=gdk_pixbuf_get_height(pixbuf);
		printf("XXXCURRENT=%s %s %s\n",themename,subfolder,iconName);
//		star=gdk_pixbuf_new_from_file("star.png", NULL);
//star=gtk_widget_render_icon(NULL,GTK_STOCK_ABOUT,(GtkIconSize)-1,0);
starwidget=gtk_image_new_from_stock(GTK_STOCK_ABOUT,(GtkIconSize)GTK_ICON_SIZE_LARGE_TOOLBAR);
//star=gtk_image_get_pixbuf((GtkImage *)starwidget);
star=gtk_widget_render_icon(starwidget,GTK_STOCK_ABOUT,(GtkIconSize)GTK_ICON_SIZE_LARGE_TOOLBAR,"");
//GError *error=NULL;
//GtkIconTheme*     icon_theme=gtk_icon_theme_get_default();
//star=gtk_icon_theme_load_icon(theme,"emblem-favorite.png",16,GTK_ICON_LOOKUP_NO_SVG,NULL);

//star=gtk_icon_theme_load_icon(icon_theme,
///                                 "emblem-special", /* icon name */
   //                              16, /* size */
     //                           (GtkIconLookupFlags)0,  /* flags */
       //                          &error);
                              
		gdk_pixbuf_add_alpha(pixbuf,FALSE,0,0,0);
		gdk_pixbuf_add_alpha(star,FALSE,0,0,0);
// gdk_pixbuf_copy_area               (star,0,0,32,32,pixbuf,10,10);
		starWid=gdk_pixbuf_get_width(star);
		starHite=gdk_pixbuf_get_height(star);

	cairo_surface_t *surface;
	cairo_t *cr;

surface=cairo_image_surface_create(CAIRO_FORMAT_ARGB32,200,200);
cr=cairo_create(surface);
cairo_set_source_surface(cr,surface, 0, 0);
cairo_save(cr);
gdk_cairo_set_source_pixbuf(cr,pixbuf,0,0);
cairo_paint_with_alpha(cr,100);
cairo_restore(cr);
cairo_save(cr);

cairo_rectangle(cr,10,10,100,100);
//cairo_clip(cr);

//cairo_paint_with_alpha(cr,100);
cairo_set_line_width(cr,10.0);
cairo_stroke(cr);
	if(strcmp(subfolder,"frames")==0)
		{
			//cairo_surface_write_to_png(surface,"/tmp/xx.png");
			//cairo_t *tmp=gdk_cairo_create((GdkDrawable *)pixbuf);
	//cairo_surface_t * drawable_surface=cairo_get_target(tmp);
			//GtkWidget *     da=gtk_drawing_area_new();
			//GdkWindow *        window= gtk_widget_get_window(da);
			//gdk_drawable_set_colormap((GdkDrawable *)surface,gdk_drawable_get_colormap((GdkDrawable *)pixbuf));
			//cairo_surface_t * drawable_surface=cairo_get_target(surface);
//			GdkColormap *       cmap=gdk_colormap_get_system            ();
//			pixbuf=gdk_pixbuf_get_from_drawable(NULL,(GdkDrawable *)drawable_surface,
//                                                       NULL,
  //                                                     0,
    //                                                   0,
      //                                                 0,
        //                                               0,
          //                                             100,
            //                                           100);
			//pixbuf=gdk_pixbuf_new_from_file("/tmp/xx.png",NULL);
			pixbuf=f_pixbuf_from_cairo_surface(surface);
			printf("AAAAAAAAAA\n");
		}
cairo_restore(cr);
	cairo_surface_destroy(surface);
	cairo_destroy(cr);

	//	gdk_pixbuf_composite(star,pixbuf,pixWid-starWid,pixHite-starHite,starWid,starHite,pixWid-starWid,pixHite-starHite,1.0,1.0,GDK_INTERP_NEAREST,0xFF);
	}

//gdk_draw_rectangle((GdkDrawable *)pixbuf,
//                                           GdkGC *gc,
  //                                         gboolean filled,
    //                                       gint x,
      //                                     gint y,
        //                                   gint width,
          //                                 gint height);


	//pixbuf=gdk_pixbuf_new_from_file_at_scale(iconPng,size,-1,FALSE,NULL);
	gtk_list_store_set(store,&iter,PIXBUF_COLUMN,pixbuf,TEXT_COLUMN,iconName,FILE_NAME,dbPath,-1);
	g_object_unref(pixbuf);
}

void addNewIcons(GtkWidget* vbox,const char* subfolder)
{
	char*			foldername;
	char*			filename;
	const gchar*	entry;
	GDir*			folder;
	GKeyFile*		keyfile=g_key_file_new();
	char*			name;
	char*			thumb;
	char*			themename;

	GSList *		entrylist=NULL;
	char*			entryname;
	bool			flag=false;
	int 			itemSize=previewSize+previewSize/2;

	if(addView==true)
		{

			icon_view=gtk_icon_view_new();
			store=gtk_list_store_new(3, GDK_TYPE_PIXBUF, G_TYPE_STRING, G_TYPE_STRING);

//			if(size<=64)
//				itemSize=size+(size/2);
//			else
//				itemSize=-1;

			gtk_icon_view_set_item_width((GtkIconView *)icon_view,itemSize);
			gtk_icon_view_set_item_padding((GtkIconView *)icon_view,0);
			gtk_icon_view_set_column_spacing((GtkIconView *)icon_view,0);
			gtk_icon_view_set_spacing((GtkIconView *)icon_view,0);


			gtk_icon_view_set_pixbuf_column(GTK_ICON_VIEW(icon_view), PIXBUF_COLUMN);
			gtk_icon_view_set_text_column(GTK_ICON_VIEW(icon_view), TEXT_COLUMN);

			gtk_icon_view_set_model(GTK_ICON_VIEW(icon_view), GTK_TREE_MODEL(store));

			gtk_container_add((GtkContainer*)vbox,(GtkWidget*)icon_view);
		}

	asprintf(&foldername,"%s/.config/XfceThemeManager/%s",homeFolder,subfolder);
	folder=g_dir_open(foldername,0,NULL);
	if(folder!=NULL)
		{
			entry=g_dir_read_name(folder);
			while(entry!=NULL)
				{
				flag=false;
				if(strstr(entry,".db"))
					{
						if(showGlobal==1)
							{
								if(showOnlyCustom==0)
									{
										if((strcmp(subfolder,"meta")==0 && showMeta==1)|| entry[0]=='0' )
											flag=true;
									}
								if((strcmp(subfolder,"controls")==0 && showGtk==1)||(strcmp(subfolder,"controls")==0 && entry[0]=='0'))
									flag=true;
								if((strcmp(subfolder,"cursors")==0 && showCursors==1)||(strcmp(subfolder,"cursors")==0 && entry[0]=='0'))
									flag=true;
								if((strcmp(subfolder,"frames")==0 && showDecs==1)||(strcmp(subfolder,"frames")==0 && entry[0]=='0'))
									flag=true;
								if((strcmp(subfolder,"icons")==0 && showIcons==1)||(strcmp(subfolder,"icons")==0 && entry[0]=='0'))
									flag=true;
								if((strcmp(subfolder,"wallpapers")==0 && showBackdrop==1)||(strcmp(subfolder,"wallpapers")==0 && entry[0]=='0'))
									flag=true;
								if(strcmp(subfolder,"custom")==0)
									flag=true;
							}
						else
							{
								if(entry[0]=='0')
									flag=true;
								if((strcmp(subfolder,"meta")==0 && showOnlyCustom==1))
									flag=false;
								if(strcmp(subfolder,"custom")==0)
									flag=true;
							}

						if(flag==true)
							{
								asprintf(&entryname,"%s",entry);
								entrylist=g_slist_prepend(entrylist,(void*)entryname);
							}
					}
					entry=g_dir_read_name(folder);
				}
			g_dir_close(folder);
		}

	if(entrylist!=NULL)
		{
			entrylist=g_slist_sort(entrylist,sortFunc);

			for(int j=0;j<(int)g_slist_length(entrylist);j++)
				{
					asprintf(&filename,"%s/.config/XfceThemeManager/%s/%s",homeFolder,subfolder,(char*)g_slist_nth_data(entrylist,j));
					if(g_key_file_load_from_file(keyfile,filename,G_KEY_FILE_NONE,NULL))
						{
							name=g_key_file_get_string(keyfile,"Data","Name",NULL);
							thumb=g_key_file_get_string(keyfile,"Data","Thumbnail",NULL);
							themename=g_key_file_get_string(keyfile,"Data","ThemeName",NULL);
							addIconEntry(store,thumb,name,filename,(char*)subfolder,(char*)themename);
							freeAndNull(&name);
							freeAndNull(&thumb);
							freeAndNull(&filename);
							freeAndNull(&themename);
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
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new(_translate(TITLEPOS)), false,false,4);
	titlePos=(GtkComboBoxText*)gtk_combo_box_text_new();
	gtk_combo_box_text_append_text(titlePos, _translate(LEFT));
	gtk_combo_box_text_append_text(titlePos,_translate(CENTRE));
	gtk_combo_box_text_append_text(titlePos,_translate(RIGHT));
	gtk_combo_box_set_active((GtkComboBox*)titlePos,positionToInt(currentTitlePos));
	g_signal_connect_after(G_OBJECT(titlePos),"changed",G_CALLBACK(setTitlePos),NULL);
	gtk_box_pack_start(GTK_BOX(advancedHbox),(GtkWidget*)titlePos,true,true,8);
	return(advancedHbox);
}

void buildPages(void)
{
	themesScrollBox=gtk_scrolled_window_new(NULL,NULL);
	addView=true;
	if(themesVBox==NULL)
		themesVBox=gtk_vbox_new(FALSE, 0);
	addNewIcons(themesScrollBox,"custom");

	addView=false;
	addNewIcons(themesScrollBox,"meta");

	g_signal_connect(G_OBJECT(icon_view),"motion-notify-event",G_CALLBACK(mouseMove),NULL);
	g_signal_connect(G_OBJECT(icon_view),"button-press-event",G_CALLBACK(clickIt),(void*)THEMES);

	addView=true;

	gtk_box_pack_start((GtkBox*)themesVBox,themesScrollBox,TRUE,TRUE,0);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(themesScrollBox),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

	framesScrollBox=gtk_scrolled_window_new(NULL,NULL);
	if(framesVBox==NULL)
		framesVBox=gtk_vbox_new(FALSE, 0);
	addNewIcons(framesScrollBox,"frames");
	gtk_box_pack_start((GtkBox*)framesVBox,framesScrollBox,TRUE,TRUE,0);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(framesScrollBox),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

	g_signal_connect(G_OBJECT(icon_view),"motion-notify-event",G_CALLBACK(mouseMove),NULL);
	g_signal_connect(G_OBJECT(icon_view),"button-press-event",G_CALLBACK(clickIt),(void*)WMBORDERS);

	controlsScrollBox=gtk_scrolled_window_new(NULL,NULL);
	if(controlsVBox==NULL)
		controlsVBox=gtk_vbox_new(FALSE, 0);
	addNewIcons(controlsScrollBox,"controls");
	gtk_box_pack_start((GtkBox*)controlsVBox,controlsScrollBox,TRUE,TRUE,0);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(controlsScrollBox),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

	g_signal_connect(G_OBJECT(icon_view),"motion-notify-event",G_CALLBACK(mouseMove),NULL);
	g_signal_connect(G_OBJECT(icon_view),"button-press-event",G_CALLBACK(clickIt),(void*)CONTROLS);

	iconsScrollBox=gtk_scrolled_window_new(NULL,NULL);
	if(iconsVBox==NULL)
		iconsVBox=gtk_vbox_new(FALSE, 0);
	addNewIcons(iconsScrollBox,"icons");
	gtk_box_pack_start((GtkBox*)iconsVBox,iconsScrollBox, TRUE, TRUE, 0);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(iconsScrollBox),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

	g_signal_connect(G_OBJECT(icon_view),"motion-notify-event",G_CALLBACK(mouseMove),NULL);
	g_signal_connect(G_OBJECT(icon_view),"button-press-event",G_CALLBACK(clickIt),(void*)ICONS);

	cursorsScrollBox=gtk_scrolled_window_new(NULL,NULL);
	if(cursorsVBox==NULL)
		cursorsVBox=gtk_vbox_new(FALSE, 0);
	addNewIcons(cursorsScrollBox,"cursors");
	gtk_box_pack_start((GtkBox*)cursorsVBox,cursorsScrollBox, TRUE, TRUE, 0);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(cursorsScrollBox),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

	g_signal_connect(G_OBJECT(icon_view),"motion-notify-event",G_CALLBACK(mouseMove),NULL);
	g_signal_connect(G_OBJECT(icon_view),"button-press-event",G_CALLBACK(clickIt),(void*)CURSORS);

	wallpapersScrollBox=gtk_scrolled_window_new(NULL,NULL);
	if(wallpapersVBox==NULL)
		{
			wallpapersVBox=gtk_vbox_new(FALSE, 0);
			gtk_box_pack_start((GtkBox*)wallpapersVBox,wallpapersMainBox,FALSE,FALSE,0);
		}
	addNewIcons(wallpapersScrollBox,"wallpapers");

	gtk_box_pack_start((GtkBox*)wallpapersVBox,wallpapersScrollBox, TRUE, TRUE, 0);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(wallpapersScrollBox),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

	g_signal_connect(G_OBJECT(icon_view),"motion-notify-event",G_CALLBACK(mouseMove),NULL);
	g_signal_connect(G_OBJECT(icon_view),"button-press-event",G_CALLBACK(clickIt),(void*)WALLPAPERS);
	
}

void doAbout(GtkWidget* widget,gpointer data)
{
	const char*	authors[]={"K.D.Hedger <"MYEMAIL">",NULL};
	const char	copyright[] ="Copyright \xc2\xa9 2012 K.D.Hedger";
	const char*	aboutboxstring=_translate(ABOUTBOX);
	const char*	translators="Spanish translation:\nPablo Morales Romero <pg.morales.romero@gmail.com>.\n\nGerman translation:\nMartin F. Schumann. <mfs@mfs.name>";

	gtk_show_about_dialog(NULL,"authors", authors,"translator-credits",translators,"comments", aboutboxstring,"copyright", copyright,"version", VERSION,"website", "http://keithhedger.hostingsiteforfree.com/index.html","program-name", "Xfce-Theme-Manager","logo-icon-name", "xfce-theme-manager", NULL); 
}

void buildAdvancedGui(GtkWidget* advancedScrollBox)
{
	GtkWidget*	advancedVbox;
	GtkWidget*	advancedHbox;
	GtkWidget*	advancedRange;
	GtkWidget*	button;

	advancedVbox=gtk_vbox_new(FALSE, 0);
//about
	button=gtk_button_new_from_stock(GTK_STOCK_ABOUT);
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(doAbout),NULL);
	advancedHbox=gtk_hbox_new(true,4);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button, false,false,4);
	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox, false,false,4);
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);

//database
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_label_new(_translate(REBUILDTHEDB)),false,false,2);
	advancedHbox=gtk_hbox_new(true,4);
	button=gtk_button_new_with_label(_translate(REBUILDDB));
	gtk_box_pack_start(GTK_BOX(advancedHbox),button, false,false,4);
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(rerunAndBuild),NULL);
	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox, false,false,4);
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);

//comp ed
	if(gotXCE==1)
		{
			gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_label_new(_translate(LAUNCHXCE)),false,false,2);
			advancedHbox=gtk_hbox_new(true,4);
			button=gtk_button_new_with_label("Xfce-Composite-Editor");
			g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(launchCompEd),NULL);
			gtk_box_pack_start(GTK_BOX(advancedHbox),button, false,false,4);
			gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox,false,false,8);
			gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);
		}
//back drop aadj
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_label_new(_translate(BACKDROPADJ)),false,false,2);
	advancedHbox=gtk_hbox_new(false,0);

//bright
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new(_translate(BRITE)), false,false,4);
	advancedRange=gtk_hscale_new_with_range(-128,127,1);
	gtk_scale_set_value_pos((GtkScale*)advancedRange,GTK_POS_LEFT);
	gtk_range_set_value((GtkRange*)advancedRange,currentBright);
	briteRange=advancedRange;

	g_signal_connect(G_OBJECT(advancedRange), "button-release-event", G_CALLBACK(setBright),NULL);
	gtk_box_pack_start(GTK_BOX(advancedHbox),advancedRange, true,true,0);
	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox, false,false,2);

	button=gtk_button_new_with_label(_translate(RESET));
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetBright),(gpointer)advancedRange);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button, false,false,8);

//satu
	advancedHbox=gtk_hbox_new(false,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new(_translate(SATU)), false,false,4);

	advancedRange=gtk_hscale_new_with_range(-10,10,0.1);
	gtk_scale_set_value_pos((GtkScale*)advancedRange,GTK_POS_LEFT);
	gtk_range_set_value((GtkRange*)advancedRange,currentSatu);
	g_signal_connect(G_OBJECT(advancedRange), "button-release-event", G_CALLBACK(setSatu),NULL);
	satuRange=advancedRange;

	gtk_box_pack_start(GTK_BOX(advancedHbox),advancedRange, true,true,0);
	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox, false,false,2);

	button=gtk_button_new_with_label(_translate(RESET));
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetSatu),(gpointer)advancedRange);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button, false,false,8);

	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);

//buton layout
	advancedHbox=gtk_hbox_new(false,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new(_translate(BUTTONLAYOUT)), false,false,4);

	layoutEntry=gtk_entry_new();
	gtk_entry_set_text((GtkEntry*)layoutEntry,currentButtonLayout);
	g_signal_connect_after(G_OBJECT(layoutEntry),"key-release-event",G_CALLBACK(changeLayout),NULL);
	gtk_box_pack_start(GTK_BOX(advancedHbox),layoutEntry, true,true,2);

	button=gtk_button_new_with_label(_translate(RESET));
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetLayout),(gpointer)layoutEntry);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button, false,false,8);

	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox, false,false,2);
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);

//buildTitlePos
	gtk_box_pack_start(GTK_BOX(advancedVbox),buildTitlePos(), false,false,0);
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);

//fonts
//wmfont
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_label_new(_translate(FONTSELECT)), false,false,4);
	advancedHbox=gtk_hbox_new(false,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new(_translate(WMFONT)), false,false,4);

	wmFontButton=gtk_font_button_new_with_font(currentWMFont);
	g_signal_connect_after(G_OBJECT(wmFontButton),"font-set",G_CALLBACK(setFont),(void*)0);
	gtk_font_button_set_use_font((GtkFontButton*)wmFontButton,true);
	gtk_box_pack_start(GTK_BOX(advancedHbox),wmFontButton, true,true,1);

	button=gtk_button_new_with_label(_translate(RESET));
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetFont),(void*)0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button, false,false,1);

	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox, false,false,4);

//appfont
	advancedHbox=gtk_hbox_new(false,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new(_translate(APPFONT)), false,false,4);

	appFontButton=gtk_font_button_new_with_font(currentAppFont);
	gtk_font_button_set_use_font((GtkFontButton*)appFontButton,true);
	g_signal_connect_after(G_OBJECT(appFontButton),"font-set",G_CALLBACK(setFont),(void*)1);
	gtk_box_pack_start(GTK_BOX(advancedHbox),appFontButton, true,true,1);

	button=gtk_button_new_with_label(_translate(RESET));
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetFont),(void*)1);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button, false,false,1);

	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox, false,false,4);

	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)advancedScrollBox,advancedVbox);

//cursor size
	advancedHbox=gtk_hbox_new(false,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new(_translate(CURSORSIZE)), false,false,4);
	cursorSize=gtk_hscale_new_with_range(16,48,1);
	gtk_scale_set_value_pos((GtkScale*)cursorSize,GTK_POS_LEFT);
	gtk_range_set_value((GtkRange*)cursorSize,currentCursSize);
	g_signal_connect(G_OBJECT(cursorSize), "value-changed",G_CALLBACK(setCursSize),NULL);
	gtk_box_pack_start(GTK_BOX(advancedHbox),cursorSize, true,true,0);

	button=gtk_button_new_with_label(_translate(RESET));
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetCursSize),NULL);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button, false,false,8);
	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox, false,false,2);

//database stuff
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_label_new(_translate(VIEW)),false,false,2);
	advancedHbox=gtk_hbox_new(true,0);


	systemCheck=gtk_check_button_new_with_label(_translate(GLOBAL));
	gtk_toggle_button_set_active((GtkToggleButton*)systemCheck,showGlobal);
	g_signal_connect_after(G_OBJECT(systemCheck),"toggled",G_CALLBACK(changeView),NULL);
	gtk_box_pack_start(GTK_BOX(advancedHbox),systemCheck, true,true,0);

	onlyCustomCheck=gtk_check_button_new_with_label(_translate(CUSTOMMETA));
	gtk_toggle_button_set_active((GtkToggleButton*)onlyCustomCheck,showOnlyCustom);
	g_signal_connect_after(G_OBJECT(onlyCustomCheck),"toggled",G_CALLBACK(changeViewWhat),(gpointer)CUSTOMMETA);
	gtk_box_pack_start(GTK_BOX(advancedHbox),onlyCustomCheck, true,true,0);

	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox,false,false,2);

	metaCheck=gtk_check_button_new_with_label(_translate(THEMES));
	gtk_toggle_button_set_active((GtkToggleButton*)metaCheck,showMeta);
	g_signal_connect_after(G_OBJECT(metaCheck),"toggled",G_CALLBACK(changeViewWhat),(gpointer)THEMES);

	borderCheck=gtk_check_button_new_with_label(_translate(WMBORDERS));
	gtk_toggle_button_set_active((GtkToggleButton*)borderCheck,showDecs);
	g_signal_connect_after(G_OBJECT(borderCheck),"toggled",G_CALLBACK(changeViewWhat),(gpointer)WMBORDERS);

	gtkCheck=gtk_check_button_new_with_label(_translate(CONTROLS));
	gtk_toggle_button_set_active((GtkToggleButton*)gtkCheck,showGtk);
	g_signal_connect_after(G_OBJECT(gtkCheck),"toggled",G_CALLBACK(changeViewWhat),(gpointer)CONTROLS);

	iconsCheck=gtk_check_button_new_with_label(_translate(ICONS));
	gtk_toggle_button_set_active((GtkToggleButton*)iconsCheck,showIcons);
	g_signal_connect_after(G_OBJECT(iconsCheck),"toggled",G_CALLBACK(changeViewWhat),(gpointer)ICONS);

	cursorsCheck=gtk_check_button_new_with_label(_translate(CURSORS));
	gtk_toggle_button_set_active((GtkToggleButton*)cursorsCheck,showCursors);
	g_signal_connect_after(G_OBJECT(cursorsCheck),"toggled",G_CALLBACK(changeViewWhat),(gpointer)CURSORS);

	paperCheck=gtk_check_button_new_with_label(_translate(WALLPAPERS));
	gtk_toggle_button_set_active((GtkToggleButton*)paperCheck,showBackdrop);
	g_signal_connect_after(G_OBJECT(paperCheck),"toggled",G_CALLBACK(changeViewWhat),(gpointer)WALLPAPERS);

	advancedHbox=gtk_hbox_new(true,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),metaCheck, true,true,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),borderCheck, true,true,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtkCheck, true,true,0);
	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox,false,false,2);

	advancedHbox=gtk_hbox_new(true,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),iconsCheck, true,true,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),cursorsCheck, true,true,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),paperCheck, true,true,0);
	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox,false,false,2);
}

