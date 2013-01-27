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
 * Copyright(C)2001,2002,2003 The Free Software Foundation,Inc.
 * Copyright(C)2003 Ettore Perazzoli
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License,or(at your option)any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not,write to the
 * Free Software Foundation,Inc.,59 Temple Place - Suite 330,
 * Boston,MA 02111-1307,USA.
 *
 * Author: Paolo Bacchilega <paolo.bacch@tin.it>
 *
 * Adapted by Ettore Perazzoli <ettore@perazzoli.org>
 */

/* Some bits are based upon the GIMP source code,the original copyright
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

bool			addView=true;
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
	box=gtk_vbox_new(FALSE,0);
	hbox=gtk_hbox_new(FALSE,0);
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

	gdk_pixbuf_fill(pixbuf,0);
	guchar *gdk_pixels=gdk_pixbuf_get_pixels(pixbuf);
	int gdk_rowstride=gdk_pixbuf_get_rowstride(pixbuf);

	cairo_surface_t *surface;
	cairo_t *ctx;

	surface=cairo_image_surface_create_for_data(gdk_pixels,CAIRO_FORMAT_ARGB32,width,height,gdk_rowstride);
	ctx=cairo_create(surface);
	cairo_set_source_surface(ctx,source,0,0);

	cairo_mask_surface (ctx,source,0,0);

	for(int j=height;j;j--)
		{
			guchar *p=gdk_pixels;
			guchar *end=p + 4 * width;
			guchar tmp;

			while(p<end)
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

GtkTreePath* holdPathTemp=NULL;

void addIconEntry(GtkListStore *store,const char* iconPng,const char* iconName,char* dbPath,char* subfolder,char* themename)
{
	GtkTreeIter	iter;
	GdkPixbuf*	pixbuf;
	int pixWid,pixHite;
	cairo_surface_t *surface;
	cairo_t *cr;

	gtk_list_store_append(store,&iter);
	pixbuf=gdk_pixbuf_new_from_file_at_size(iconPng,previewSize,-1,NULL);

	if(isCurrent(themename,subfolder,(char*)iconName)==true)
		{
			pixbuf=gdk_pixbuf_new_from_file_at_size(iconPng,previewSize-GAP,-1,NULL);
			pixWid=gdk_pixbuf_get_width(pixbuf);
			pixHite=gdk_pixbuf_get_height(pixbuf);

			surface=cairo_image_surface_create(CAIRO_FORMAT_ARGB32,pixWid+GAP,pixHite+GAP);
			cr=cairo_create(surface);

			cairo_save(cr);
				cairo_set_source_rgb(cr,1,1,1);
				cairo_rectangle(cr,0,0,pixWid+GAP,pixHite+GAP);
				cairo_fill (cr);
			cairo_restore(cr);

			cairo_save(cr);
				gdk_cairo_set_source_pixbuf(cr,pixbuf,HALFGAP,HALFGAP);
				cairo_paint_with_alpha(cr,100);
			cairo_restore(cr);

			cairo_save(cr);
				cairo_rectangle(cr,0,0,pixWid+GAP,pixHite+GAP);
				cairo_set_line_width(cr,HALFGAP);
				cairo_stroke(cr);
			cairo_restore(cr);

			g_object_unref(pixbuf);
			pixbuf=f_pixbuf_from_cairo_surface(surface);

			cairo_surface_destroy(surface);
			cairo_destroy(cr);
			//printf("XXX\n");
			//holdPathTemp=gtk_tree_model_get_path(GTK_TREE_MODEL(store),&iter);
			//printf("ZZZ\n");
		}

	gtk_list_store_set(store,&iter,PIXBUF_COLUMN,pixbuf,TEXT_COLUMN,iconName,FILE_NAME,dbPath,-1);
	g_object_unref(pixbuf);

}

void addNewIcons(GtkHBox* hbox,const char* subfolder,GtkIconView* tempIconView,int whatBox)
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
			store=gtk_list_store_new(3,GDK_TYPE_PIXBUF,G_TYPE_STRING,G_TYPE_STRING);

			gtk_icon_view_set_item_width((GtkIconView *)tempIconView,itemSize);
			gtk_icon_view_set_item_padding((GtkIconView *)tempIconView,0);
			gtk_icon_view_set_column_spacing((GtkIconView *)tempIconView,0);
			gtk_icon_view_set_spacing((GtkIconView *)tempIconView,0);


			gtk_icon_view_set_pixbuf_column(GTK_ICON_VIEW(tempIconView),PIXBUF_COLUMN);
			gtk_icon_view_set_text_column(GTK_ICON_VIEW(tempIconView),TEXT_COLUMN);

			gtk_icon_view_set_model(GTK_ICON_VIEW(tempIconView),GTK_TREE_MODEL(store));
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
							//previewBox[whatBox].adj=holdPathTemp;
							previewBox[whatBox].itemCnt++;
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
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new(_translate(TITLEPOS)),false,false,4);
	titlePos=(GtkComboBoxText*)gtk_combo_box_text_new();
	gtk_combo_box_text_append_text(titlePos,_translate(LEFT));
	gtk_combo_box_text_append_text(titlePos,_translate(CENTRE));
	gtk_combo_box_text_append_text(titlePos,_translate(RIGHT));
	gtk_combo_box_set_active((GtkComboBox*)titlePos,positionToInt(currentTitlePos));
	g_signal_connect_after(G_OBJECT(titlePos),"changed",G_CALLBACK(setTitlePos),NULL);
	gtk_box_pack_start(GTK_BOX(advancedHbox),(GtkWidget*)titlePos,true,true,8);
	return(advancedHbox);
}

void buildPages(void)
{
	if(previewBox[THEMES].vBox==NULL)
		previewBox[THEMES].vBox=(GtkVBox*)gtk_vbox_new(FALSE,0);

	previewBox[THEMES].hBox=(GtkHBox*)gtk_hbox_new(FALSE,0);
	previewBox[THEMES].scrollBox=(GtkScrolledWindow*)gtk_scrolled_window_new(NULL,NULL);
	previewBox[THEMES].itemCnt=0;
	gtk_scrolled_window_set_policy(previewBox[THEMES].scrollBox,GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);

	addView=true;
	previewBox[THEMES].iconView=(GtkIconView*)gtk_icon_view_new();
	addNewIcons(previewBox[THEMES].hBox,"custom",previewBox[THEMES].iconView,THEMES);
	addView=false;
	addNewIcons(previewBox[THEMES].hBox,"meta",previewBox[THEMES].iconView,THEMES);
	addView=true;

	gtk_container_add((GtkContainer*)previewBox[THEMES].hBox,(GtkWidget*)previewBox[THEMES].iconView);
	gtk_scrolled_window_add_with_viewport(previewBox[THEMES].scrollBox,(GtkWidget*)previewBox[THEMES].hBox);
	gtk_box_pack_start((GtkBox*)previewBox[THEMES].vBox,(GtkWidget*)previewBox[THEMES].scrollBox,TRUE,TRUE,0);

	g_signal_connect(G_OBJECT(previewBox[THEMES].iconView),"motion-notify-event",G_CALLBACK(mouseMove),NULL);
	g_signal_connect(G_OBJECT(previewBox[THEMES].iconView),"button-press-event",G_CALLBACK(clickIt),(void*)THEMES);

	for (int j=1;j<WALLPAPERS;j++)
		{
			if(previewBox[j].vBox==NULL)
				previewBox[j].vBox=(GtkVBox*)gtk_vbox_new(FALSE,0);

			previewBox[j].hBox=(GtkHBox*)gtk_hbox_new(FALSE,0);
			previewBox[j].scrollBox=(GtkScrolledWindow*)gtk_scrolled_window_new(NULL,NULL);
			previewBox[j].itemCnt=0;
			gtk_scrolled_window_set_policy(previewBox[j].scrollBox,GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);

			previewBox[j].iconView=(GtkIconView*)gtk_icon_view_new();
			addNewIcons(previewBox[j].hBox,folders[j],previewBox[j].iconView,j);

			gtk_container_add((GtkContainer*)previewBox[j].hBox,(GtkWidget*)previewBox[j].iconView);
			gtk_scrolled_window_add_with_viewport(previewBox[j].scrollBox,(GtkWidget*)previewBox[j].hBox);
			gtk_box_pack_start((GtkBox*)previewBox[j].vBox,(GtkWidget*)previewBox[j].scrollBox,TRUE,TRUE,0);
			
			g_signal_connect(G_OBJECT(previewBox[j].iconView),"motion-notify-event",G_CALLBACK(mouseMove),NULL);
			g_signal_connect(G_OBJECT(previewBox[j].iconView),"button-press-event",G_CALLBACK(clickIt),(void*)(long)j);
		}
	
	if(previewBox[WALLPAPERS].vBox==NULL)
		{
			previewBox[WALLPAPERS].vBox=(GtkVBox*)gtk_vbox_new(FALSE,0);
			gtk_box_pack_start((GtkBox*)previewBox[WALLPAPERS].vBox,(GtkWidget*)wallpapersMainBox,FALSE,FALSE,0);
		}

	previewBox[WALLPAPERS].hBox=(GtkHBox*)gtk_hbox_new(FALSE,0);
	previewBox[WALLPAPERS].scrollBox=(GtkScrolledWindow*)gtk_scrolled_window_new(NULL,NULL);
	previewBox[WALLPAPERS].itemCnt=0;
	gtk_scrolled_window_set_policy(previewBox[WALLPAPERS].scrollBox,GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);

	previewBox[WALLPAPERS].iconView=(GtkIconView*)gtk_icon_view_new();
	addNewIcons(previewBox[WALLPAPERS].hBox,folders[WALLPAPERS],previewBox[WALLPAPERS].iconView,WALLPAPERS);

	gtk_container_add((GtkContainer*)previewBox[WALLPAPERS].hBox,(GtkWidget*)previewBox[WALLPAPERS].iconView);
	gtk_scrolled_window_add_with_viewport(previewBox[WALLPAPERS].scrollBox,(GtkWidget*)previewBox[WALLPAPERS].hBox);


	gtk_box_pack_start((GtkBox*)previewBox[WALLPAPERS].vBox,(GtkWidget*)previewBox[WALLPAPERS].scrollBox,TRUE,TRUE,0);

	g_signal_connect(G_OBJECT(previewBox[WALLPAPERS].iconView),"motion-notify-event",G_CALLBACK(mouseMove),NULL);
	g_signal_connect(G_OBJECT(previewBox[WALLPAPERS].iconView),"button-press-event",G_CALLBACK(clickIt),(void*)(long)WALLPAPERS);

}

void doAboutXX(GtkWidget* widget,gpointer data)
{
	const char*	authors[]={"K.D.Hedger <"MYEMAIL">",NULL};
	const char	copyright[] ="Copyright \xc2\xa9 2012 K.D.Hedger";
	const char*	aboutboxstring=_translate(ABOUTBOX);
	const char*	translators="Spanish translation:\nPablo Morales Romero <pg.morales.romero@gmail.com>.\n\nGerman translation:\nMartin F. Schumann. <mfs@mfs.name>";

	gtk_show_about_dialog(NULL,"authors",authors,"translator-credits",translators,"comments",aboutboxstring,"copyright",copyright,"version",VERSION,"website","http://keithhedger.hostingsiteforfree.com/index.html","program-name","Xfce-Theme-Manager","logo-icon-name","xfce-theme-manager",NULL); 
}

void buildAdvancedGui(GtkWidget* advancedScrollBox)
{
	GtkWidget*	advancedVbox;
	GtkWidget*	advancedHbox;
	GtkWidget*	advancedRange;
	GtkWidget*	button;

	advancedVbox=gtk_vbox_new(FALSE,0);
//about
/*
	button=gtk_button_new_from_stock(GTK_STOCK_ABOUT);
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(doAbout),NULL);
	advancedHbox=gtk_hbox_new(true,4);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button,false,false,4);
	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox,false,false,4);
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);
*/
//database
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_label_new(_translate(REBUILDTHEDB)),false,false,2);
	advancedHbox=gtk_hbox_new(true,4);
	button=gtk_button_new_with_label(_translate(REBUILDDB));
	gtk_box_pack_start(GTK_BOX(advancedHbox),button,false,false,4);
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(rerunAndBuild),NULL);
	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox,false,false,4);
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);

//comp ed
	if(gotXCE==1)
		{
			gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_label_new(_translate(LAUNCHXCE)),false,false,2);
			advancedHbox=gtk_hbox_new(true,4);
			button=gtk_button_new_with_label("Xfce-Composite-Editor");
			g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(launchCompEd),NULL);
			gtk_box_pack_start(GTK_BOX(advancedHbox),button,false,false,4);
			gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox,false,false,8);
			gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);
		}
//back drop aadj
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_label_new(_translate(BACKDROPADJ)),false,false,2);
	advancedHbox=gtk_hbox_new(false,0);

//bright
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new(_translate(BRITE)),false,false,4);
	advancedRange=gtk_hscale_new_with_range(-128,127,1);
	gtk_scale_set_value_pos((GtkScale*)advancedRange,GTK_POS_LEFT);
	gtk_range_set_value((GtkRange*)advancedRange,currentBright);
	briteRange=advancedRange;

	g_signal_connect(G_OBJECT(advancedRange),"button-release-event",G_CALLBACK(setBright),NULL);
	gtk_box_pack_start(GTK_BOX(advancedHbox),advancedRange,true,true,0);
	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox,false,false,2);

	button=gtk_button_new_with_label(_translate(RESET));
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetBright),(gpointer)advancedRange);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button,false,false,8);

//satu
	advancedHbox=gtk_hbox_new(false,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new(_translate(SATU)),false,false,4);

	advancedRange=gtk_hscale_new_with_range(-10,10,0.1);
	gtk_scale_set_value_pos((GtkScale*)advancedRange,GTK_POS_LEFT);
	gtk_range_set_value((GtkRange*)advancedRange,currentSatu);
	g_signal_connect(G_OBJECT(advancedRange),"button-release-event",G_CALLBACK(setSatu),NULL);
	satuRange=advancedRange;

	gtk_box_pack_start(GTK_BOX(advancedHbox),advancedRange,true,true,0);
	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox,false,false,2);

	button=gtk_button_new_with_label(_translate(RESET));
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetSatu),(gpointer)advancedRange);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button,false,false,8);

	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);

//buton layout
	advancedHbox=gtk_hbox_new(false,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new(_translate(BUTTONLAYOUT)),false,false,4);

	layoutEntry=gtk_entry_new();
	gtk_entry_set_text((GtkEntry*)layoutEntry,currentButtonLayout);
	g_signal_connect_after(G_OBJECT(layoutEntry),"key-release-event",G_CALLBACK(changeLayout),NULL);
	gtk_box_pack_start(GTK_BOX(advancedHbox),layoutEntry,true,true,2);

	button=gtk_button_new_with_label(_translate(RESET));
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetLayout),(gpointer)layoutEntry);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button,false,false,8);

	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox,false,false,2);
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);

//buildTitlePos
	gtk_box_pack_start(GTK_BOX(advancedVbox),buildTitlePos(),false,false,0);
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);

//fonts
//wmfont
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_label_new(_translate(FONTSELECT)),false,false,4);
	advancedHbox=gtk_hbox_new(false,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new(_translate(WMFONT)),false,false,4);

	wmFontButton=gtk_font_button_new_with_font(currentWMFont);
	g_signal_connect_after(G_OBJECT(wmFontButton),"font-set",G_CALLBACK(setFont),(void*)0);
	gtk_font_button_set_use_font((GtkFontButton*)wmFontButton,true);
	gtk_box_pack_start(GTK_BOX(advancedHbox),wmFontButton,true,true,1);

	button=gtk_button_new_with_label(_translate(RESET));
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetFont),(void*)0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button,false,false,1);

	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox,false,false,4);

//appfont
	advancedHbox=gtk_hbox_new(false,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new(_translate(APPFONT)),false,false,4);

	appFontButton=gtk_font_button_new_with_font(currentAppFont);
	gtk_font_button_set_use_font((GtkFontButton*)appFontButton,true);
	g_signal_connect_after(G_OBJECT(appFontButton),"font-set",G_CALLBACK(setFont),(void*)1);
	gtk_box_pack_start(GTK_BOX(advancedHbox),appFontButton,true,true,1);

	button=gtk_button_new_with_label(_translate(RESET));
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetFont),(void*)1);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button,false,false,1);

	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox,false,false,4);

	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)advancedScrollBox,advancedVbox);

//cursor size
	advancedHbox=gtk_hbox_new(false,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtk_label_new(_translate(CURSORSIZE)),false,false,4);
	cursorSize=gtk_hscale_new_with_range(16,48,1);
	gtk_scale_set_value_pos((GtkScale*)cursorSize,GTK_POS_LEFT);
	gtk_range_set_value((GtkRange*)cursorSize,currentCursSize);
	g_signal_connect(G_OBJECT(cursorSize),"value-changed",G_CALLBACK(setCursSize),NULL);
	gtk_box_pack_start(GTK_BOX(advancedHbox),cursorSize,true,true,0);

	button=gtk_button_new_with_label(_translate(RESET));
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(resetCursSize),NULL);
	gtk_box_pack_start(GTK_BOX(advancedHbox),button,false,false,8);
	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox,false,false,2);

//database stuff
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_hseparator_new(),false,false,4);
	gtk_box_pack_start(GTK_BOX(advancedVbox),gtk_label_new(_translate(VIEW)),false,false,2);
	advancedHbox=gtk_hbox_new(true,0);


	systemCheck=gtk_check_button_new_with_label(_translate(GLOBAL));
	gtk_toggle_button_set_active((GtkToggleButton*)systemCheck,showGlobal);
	g_signal_connect_after(G_OBJECT(systemCheck),"toggled",G_CALLBACK(changeView),NULL);
	gtk_box_pack_start(GTK_BOX(advancedHbox),systemCheck,true,true,0);

	onlyCustomCheck=gtk_check_button_new_with_label(_translate(CUSTOMMETA));
	gtk_toggle_button_set_active((GtkToggleButton*)onlyCustomCheck,showOnlyCustom);
	g_signal_connect_after(G_OBJECT(onlyCustomCheck),"toggled",G_CALLBACK(changeViewWhat),(gpointer)CUSTOMMETA);
	gtk_box_pack_start(GTK_BOX(advancedHbox),onlyCustomCheck,true,true,0);

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
	gtk_box_pack_start(GTK_BOX(advancedHbox),metaCheck,true,true,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),borderCheck,true,true,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),gtkCheck,true,true,0);
	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox,false,false,2);

	advancedHbox=gtk_hbox_new(true,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),iconsCheck,true,true,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),cursorsCheck,true,true,0);
	gtk_box_pack_start(GTK_BOX(advancedHbox),paperCheck,true,true,0);
	gtk_box_pack_start(GTK_BOX(advancedVbox),advancedHbox,false,false,2);
}

