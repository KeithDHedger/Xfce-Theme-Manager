/*
 *
 * ©K. D. Hedger. Tue 20 Oct 15:55:49 BST 2015 keithdhedger@gmail.com

 * This file (thumbnails.cpp) is part of Xfce-Theme-Manager.

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
 * K.D.Hedger 2012 <keithdhedger@gmail.com>
 *
 * thumbnails.cpp
 */

#include <stdlib.h>
#include <string.h>
#include <X11/Xcursor/Xcursor.h>

#include "globals.h"

int			boxhite=90;
int			button_offset,button_spacing;

GdkPixbuf *cursorprev (const char *ptrname,char* themename,int whatSize)
{
	XcursorImage	*image;
	GdkPixbuf		*scaled=NULL,*pixbuf=NULL;
	gsize			bsize;
	guchar		*buffer,*p,tmp;

    /* load the image */

	image=XcursorLibraryLoadImage (ptrname,themename,whatSize);
	if (G_LIKELY(image))
		{
			bsize=image->width*image->height*4;
			buffer=(guchar*)g_malloc(bsize);

        /* copy pixel data to buffer */
			memcpy(buffer,image->pixels,bsize);
        /* swap bits */
			for (p=buffer;p<buffer+bsize;p+=4)
				{
					tmp=p[0];
					p[0]=p[2];
					p[2]=tmp;
				}
        /* create pixbuf */
			pixbuf=gdk_pixbuf_new_from_data(buffer,GDK_COLORSPACE_RGB,TRUE,8,image->width,image->height,4*image->width,(GdkPixbufDestroyNotify) g_free,NULL);

        /* don't leak when creating the pixbuf failed */
			if (G_UNLIKELY(pixbuf==NULL))
				g_free(buffer);

			if (pixbuf!=NULL)
				{
					scaled=gdk_pixbuf_scale_simple(pixbuf,whatSize,whatSize,GDK_INTERP_BILINEAR);
					g_object_unref(G_OBJECT (pixbuf));
				}
				XcursorImageDestroy (image);
		}
	return scaled;
}

void makecursor(char* theme,char* outPath)
{
	GdkPixbuf*	arrow;
	GdkPixbuf*	move;
	GdkPixbuf*	wait;
	GdkPixbuf*	hand;
	cairo_surface_t *surface;
	cairo_t *cr;

	controlsPixbuf=NULL;
	surface=cairo_image_surface_create(CAIRO_FORMAT_ARGB32,CURSORTHEMEWIDTH,CURSORTHEMESIZE);
	cr=cairo_create(surface);

	arrow=cursorprev("left_ptr",theme,CURSORTHEMESIZE);
	move=cursorprev("fleur",theme,CURSORTHEMESIZE);
	wait=cursorprev("watch",theme,CURSORTHEMESIZE);
	hand=cursorprev("hand2",theme,CURSORTHEMESIZE);

	if (arrow==NULL && move==NULL && wait==NULL && hand==NULL)
		return;

	cairo_save (cr);
		if(arrow!=NULL)
			{
				gdk_cairo_set_source_pixbuf(cr,arrow,0,0);
				cairo_paint_with_alpha(cr,100);
				g_object_unref(arrow);
			}
		if(move!=NULL)
			{
				gdk_cairo_set_source_pixbuf(cr,move,CURSORTHEMESIZE,0);
				cairo_paint_with_alpha(cr,100);
				g_object_unref(move);
			}
		if(wait!=NULL)
			{
				gdk_cairo_set_source_pixbuf(cr,wait,CURSORTHEMESIZE*2,0);
				cairo_paint_with_alpha(cr,100);
				g_object_unref(wait);
			}
		if(hand!=NULL)
			{
				gdk_cairo_set_source_pixbuf(cr,hand,CURSORTHEMESIZE*3,0);
				cairo_paint_with_alpha(cr,100);
				g_object_unref(hand);
			}
	cairo_restore (cr);
	cairo_surface_write_to_png(surface,outPath);

	cairo_surface_destroy(surface);
	cairo_destroy(cr);
}

GdkPixmap* draw_window_on_pixbuf(GtkWidget *widget)
{
	GdkVisual	*visual;
	GdkPixmap	*pixmap;
	GtkStyle	*style;
	GdkScreen	*screen=gdk_screen_get_default();
	GdkWindow	*window;
	gint		width,height;

	gtk_widget_ensure_style(widget);

	style=gtk_widget_get_style(widget);

	g_assert(style);
	g_assert(style->font_desc);

	gtk_window_get_size(GTK_WINDOW(widget),&width,&height);

	visual=gtk_widget_get_visual(widget);
	pixmap=gdk_pixmap_new(NULL,width,height,gdk_visual_get_depth(visual));
	gdk_drawable_set_colormap(GDK_DRAWABLE(pixmap),gtk_widget_get_colormap(widget));

	window=gtk_widget_get_window(widget);

	gdk_window_redirect_to_drawable(window,pixmap,0,0,0,0,width,height);
	gdk_window_set_override_redirect(window,TRUE);
	gtk_window_move(GTK_WINDOW(widget),gdk_screen_get_width(screen),gdk_screen_get_height(screen));
	gtk_widget_show(widget);

	gdk_window_process_updates(window,TRUE);
	gtk_widget_hide(widget);

	return pixmap;
}

GdkPixbuf * create_gtk_theme_pixbuf(char* name)
{
	GtkSettings *settings;
	GtkWidget *window,*vbox,*box,*stock_button,*checkbox,*radio;
	GtkRequisition requisition;
	GtkAllocation allocation;
	GdkPixmap *pixmap;
	GdkPixbuf *pixbuf,*retval;
	gint width,height;

	settings=gtk_settings_get_default();
	g_object_set(settings,"gtk-theme-name",(char*)name,"gtk-color-scheme","default",NULL);

	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	
	gtk_window_set_default_size((GtkWindow*)window,controlWidth,controlHeight);

	vbox=gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),vbox);
	box=gtk_hbox_new(FALSE,6);
	gtk_container_set_border_width(GTK_CONTAINER(box),6);
	gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);
	stock_button=gtk_button_new_from_stock(GTK_STOCK_OPEN);
	gtk_box_pack_start(GTK_BOX(box),stock_button,FALSE,FALSE,0);
	checkbox=gtk_check_button_new();
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbox),TRUE);
	gtk_box_pack_start(GTK_BOX(box),checkbox,FALSE,FALSE,0);
	radio=gtk_radio_button_new_from_widget(NULL);
	gtk_box_pack_start(GTK_BOX(box),radio,FALSE,FALSE,0);

	gtk_widget_show_all(vbox);
	gtk_widget_realize(stock_button);
	gtk_widget_realize(gtk_bin_get_child(GTK_BIN(stock_button)));
	gtk_widget_realize(checkbox);
	gtk_widget_realize(radio);
	gtk_widget_map(stock_button);
	gtk_widget_map(gtk_bin_get_child(GTK_BIN(stock_button)));
	gtk_widget_map(checkbox);
	gtk_widget_map(radio);

	gtk_widget_size_request(window,&requisition);
	allocation.x=0;
	allocation.y=0;
	allocation.width=requisition.width;
	allocation.height=requisition.height;
	gtk_widget_size_allocate(window,&allocation);
	gtk_widget_size_request(window,&requisition);

	gtk_window_get_size(GTK_WINDOW(window),&width,&height);

	pixmap=draw_window_on_pixbuf(window);

	pixbuf=gdk_pixbuf_new(GDK_COLORSPACE_RGB,TRUE,8,width,height);
	gdk_pixbuf_get_from_drawable(pixbuf,pixmap,NULL,0,0,0,0,width,height);

	retval=pixbuf;
	gtk_widget_destroy(window);
	g_object_unref(pixmap);

	g_object_set(settings,"gtk-theme-name",currentGtkTheme,"gtk-color-scheme","default",NULL);
	return retval;
}

static const char* image_types[]={"png","svg","gif","jpg","bmp",NULL};

GdkPixbuf* composePixbuf(char* bordername,const char* name,int wantmissing)
{
	char*		pixmapname;
	GdkPixbuf*	basepixbuf=NULL;
	GdkPixbuf*	alpha=NULL;
	int		i=0;
	gint		width,height;
	GdkPixbuf*	returnpixbuf=missingImage;

	if(wantmissing==1)
		returnpixbuf=NULL;
	if(wantmissing==2)
		returnpixbuf=blankImage;

	asprintf(&pixmapname,"%s/xfwm4/%s.xpm",bordername,name);
	basepixbuf=gdk_pixbuf_new_from_file((char*)pixmapname,NULL);

	while ((image_types[i]) && (!alpha))
		{
			asprintf(&pixmapname,"%s/xfwm4/%s.%s",bordername,name,image_types[i]);
        		if (g_file_test(pixmapname,G_FILE_TEST_IS_REGULAR))
        			{
            			alpha=gdk_pixbuf_new_from_file(pixmapname,NULL);
            			break;
            		}
        		++i;
		}
/* We have no suitable image to layer on top of the XPM, stop here... */
	
	if (alpha==NULL)
		{
			if (GDK_IS_PIXBUF(basepixbuf))
 				return (basepixbuf);
 			else
 				return(returnpixbuf);
 		}

/* We have no XPM canvas and found a suitable image, use it... */
	if (basepixbuf==NULL)
 		{
			if (GDK_IS_PIXBUF(alpha))
 				return (alpha);
 			else
				return(returnpixbuf);
 		}

	if(GDK_IS_PIXBUF(alpha) && GDK_IS_PIXBUF(basepixbuf))
		{
			width=MIN(gdk_pixbuf_get_width(basepixbuf),gdk_pixbuf_get_width (alpha));
			height=MIN(gdk_pixbuf_get_height(basepixbuf),gdk_pixbuf_get_height (alpha));
			gdk_pixbuf_composite(alpha,basepixbuf,0,0,width,height,0,0,1.0,1.0,GDK_INTERP_NEAREST,0xFF);
			g_object_unref (alpha);
			return basepixbuf;
		}
	else
		return(returnpixbuf);
}

GdkPixbuf* checkPixBuf(GdkPixbuf* pixbuf)
{
	if (GDK_IS_PIXBUF(pixbuf))
 		return (pixbuf);
 	else
 		return(NULL);
}

void makeborder(char* folder,char* outframe)
{
	GdkPixbuf*	topleft=NULL;
	GdkPixbuf*	toprite=NULL;
	GdkPixbuf*	title1=NULL;
	GdkPixbuf*	title2=NULL;
	GdkPixbuf*	title3=NULL;
	GdkPixbuf*	title4=NULL;
	GdkPixbuf*	title5=NULL;
	GdkPixbuf*	riteside=NULL;
	GdkPixbuf*	leftside=NULL;
	GdkPixbuf*	bottomleft=NULL;
	GdkPixbuf*	bottomrite=NULL;
	GdkPixbuf*	bottom=NULL;
	GdkPixbuf*	close=NULL;
	GdkPixbuf*	max=NULL;
	GdkPixbuf*	min=NULL;
	GdkPixbuf*	menu=NULL;
	GdkPixbuf*	arrow=NULL;

	GtkIconTheme*	theme;
	
	int		lsegwid,rsegwid,boxwid,hiteoffset=0;
	int		closewid=0,maxwid=0,minwid=0,menuwid=0;
	int		closehite=0,maxhite=0,minhite=0,menuhite=0;
	int		topleftwid=0,toplefthite=0,topritewid=0,topritehite=0;
	int		bottomleftwid=0,bottomlefthite=0,bottomritewid=0,bottomritehite=0;
	int		leftsidewid=0,ritesidewid=0;
	int		bottomhite=0;
	int		title1hite=0;
	int		title2wid=0,title2hite=0;
	int		title3hite=0;
	int		title4wid=0,title4hite=0;
	int		title5wid=0;

	int		padwid=PADWIDTH;

	cairo_surface_t *surface;
	cairo_t *cr;

	topleft=composePixbuf(folder,"top-left-active",0);
	toprite=composePixbuf(folder,"top-right-active",0);
	title1=composePixbuf(folder,"title-1-active",0);
	title2=composePixbuf(folder,"title-2-active",1);
	title3=composePixbuf(folder,"title-3-active",0);
	title4=composePixbuf(folder,"title-4-active",1);
	title5=composePixbuf(folder,"title-5-active",0);
	riteside=composePixbuf(folder,"right-active",1);
	leftside=composePixbuf(folder,"left-active",1);
	bottomleft=composePixbuf(folder,"bottom-left-active",0);
	bottomrite=composePixbuf(folder,"bottom-right-active",0);
	bottom=composePixbuf(folder,"bottom-active",0);
	close=composePixbuf(folder,"close-active",1);
	max=composePixbuf(folder,"maximize-active",1);
	min=composePixbuf(folder,"hide-active",1);
	menu=composePixbuf(folder,"menu-active",1);

	if (title1!=NULL)
		{
			title1hite=gdk_pixbuf_get_height((const GdkPixbuf *)title1);
		}

	if (title2!=NULL)
		{
			title2wid=gdk_pixbuf_get_width((const GdkPixbuf *)title2);
			title2hite=gdk_pixbuf_get_height((const GdkPixbuf *)title2);
		}

	if (title3!=NULL)
		{
			title3hite=gdk_pixbuf_get_height((const GdkPixbuf *)title3);
		}
	if (title4!=NULL)
		{
			title4wid=gdk_pixbuf_get_width((const GdkPixbuf *)title4);
			title4hite=gdk_pixbuf_get_height((const GdkPixbuf *)title4);
		}
	if (title5!=NULL)
		{
			title5wid=gdk_pixbuf_get_width((const GdkPixbuf *)title5);
		}

	topleftwid=gdk_pixbuf_get_width((const GdkPixbuf *)topleft);
	toplefthite=gdk_pixbuf_get_height((const GdkPixbuf *)topleft);
	
	topritewid=gdk_pixbuf_get_width((const GdkPixbuf *)toprite);
	topritehite=gdk_pixbuf_get_height((const GdkPixbuf *)toprite);

	bottomleftwid=gdk_pixbuf_get_width((const GdkPixbuf *)bottomleft);
	bottomlefthite=gdk_pixbuf_get_height((const GdkPixbuf *)bottomleft);
	
	bottomritewid=gdk_pixbuf_get_width((const GdkPixbuf *)bottomrite);
	bottomritehite=gdk_pixbuf_get_height((const GdkPixbuf *)bottomrite);

	leftsidewid=gdk_pixbuf_get_width((const GdkPixbuf *)leftside);
	ritesidewid=gdk_pixbuf_get_width((const GdkPixbuf *)riteside);

	bottomhite=gdk_pixbuf_get_height((const GdkPixbuf *)bottom);

	if (title2wid<0)
		title2=0;
	if (title4wid<0)
		title4=0;
	if (title5wid<0)
		title5=0;

	if(close!=NULL)
		{
			closewid=gdk_pixbuf_get_width((const GdkPixbuf *)close);
			closehite=gdk_pixbuf_get_height((const GdkPixbuf *)close);
		}
	if(max!=NULL)
		{
			maxwid=gdk_pixbuf_get_width((const GdkPixbuf *)max);
			maxhite=gdk_pixbuf_get_height((const GdkPixbuf *)max);
		}
	if(min!=NULL)
		{
			minwid=gdk_pixbuf_get_width((const GdkPixbuf *)min);
			minhite=gdk_pixbuf_get_height((const GdkPixbuf *)min);
		}
	if(menu!=NULL)
		{
			menuwid=gdk_pixbuf_get_width((const GdkPixbuf *)menu);
			menuhite=gdk_pixbuf_get_height((const GdkPixbuf *)menu);
		}

	lsegwid=menuwid+button_spacing;
	rsegwid=closewid+maxwid+minwid+(button_spacing*3);

	padwid=MAXBOXWIDTH-(topleftwid+lsegwid+title2wid+title4wid+rsegwid+topritewid);
	boxwid=MAXBOXWIDTH;

	if (boxhite-bottomhite-title3hite<ICONPAD+ICONPAD+ICONSIZE+title3hite+bottomhite)
		boxhite=title3hite+ICONPAD+ICONPAD+ICONSIZE+bottomhite;

	if (boxhite-bottomritehite-topritehite<=0)
		boxhite=bottomritehite+topritehite+10;

	if (boxhite-bottomlefthite-toplefthite<=0)
		boxhite=bottomritehite+topritehite+10;
	
	surface=cairo_image_surface_create(CAIRO_FORMAT_ARGB32,boxwid,boxhite);
	cr=cairo_create(surface);

//do theme
	if (controlsPixbuf!=NULL)
		{
			cairo_save (cr);
				cairo_rectangle(cr,leftsidewid,title3hite,MAXBOXWIDTH-ritesidewid-leftsidewid,boxhite-bottomhite-title3hite);
				cairo_clip(cr);
				gdk_cairo_set_source_pixbuf(cr,controlsPixbuf,leftsidewid,title3hite);
				cairo_paint_with_alpha(cr,100);

				arrow=cursorprev("left_ptr",cursorTheme,ICONSIZE);
				if(arrow!=NULL)
					{
						gdk_cairo_set_source_pixbuf(cr,arrow,boxwid-ritesidewid-ICONSIZE-ICONPAD,title3hite+ICONPAD);
						cairo_paint_with_alpha(cr,100);
						g_object_unref(arrow);
						
						theme=gtk_icon_theme_new();
						gtk_icon_theme_set_custom_theme(theme,iconTheme);
						arrow=gtk_icon_theme_load_icon(theme,"user-home",ICONSIZE,GTK_ICON_LOOKUP_FORCE_SIZE,NULL);
						if (arrow!=NULL)
							{
								gdk_cairo_set_source_pixbuf(cr,arrow,boxwid-ritesidewid-(ICONSIZE*2)-(ICONPAD*2),title3hite+ICONPAD);
								cairo_paint_with_alpha(cr,100);
								g_object_unref(arrow);
							}
						if(theme!=NULL)
							g_object_unref(theme);
					}
			cairo_restore (cr);
		}
	else
		{
			cairo_save (cr);
				cairo_set_source_rgb(cr,1,1,1);
				cairo_rectangle(cr,leftsidewid,title3hite,MAXBOXWIDTH-ritesidewid-leftsidewid,boxhite-bottomhite-title3hite);
				cairo_fill(cr);
			cairo_restore (cr);
		}

//topleft
	cairo_save (cr);
		gdk_cairo_set_source_pixbuf(cr,topleft,0,0);
		cairo_paint_with_alpha(cr,100);
	cairo_restore (cr);

//title1
	if (title1!=NULL)
		{
			cairo_save (cr);
				gdk_cairo_set_source_pixbuf(cr,title1,0,0);
				cairo_pattern_set_extend(cairo_get_source(cr),CAIRO_EXTEND_REPEAT);
				cairo_rectangle(cr,topleftwid,0,lsegwid,title1hite);
 				cairo_clip(cr);
				cairo_paint_with_alpha(cr,100);
			cairo_restore (cr);
		}

//title2
	if (title2!=NULL)
		{
			cairo_save (cr);
				gdk_cairo_set_source_pixbuf(cr,title2,topleftwid+lsegwid,0);
				cairo_pattern_set_extend(cairo_get_source(cr),CAIRO_EXTEND_REPEAT);
				cairo_rectangle(cr,topleftwid+lsegwid,0,title2wid,title2hite);
 				cairo_clip(cr);
				cairo_paint_with_alpha(cr,100);
			cairo_restore (cr);
		}

//title3
	if (title3!=NULL)
		{
			cairo_save (cr);
				gdk_cairo_set_source_pixbuf(cr,title3,0,0);
				cairo_pattern_set_extend(cairo_get_source(cr),CAIRO_EXTEND_REPEAT);
				cairo_rectangle(cr,topleftwid+lsegwid+title2wid,0,padwid,title3hite);
 				cairo_clip(cr);
				cairo_paint_with_alpha(cr,100);
			cairo_restore (cr);
		}

//title4
	if (title4!=NULL)
		{
			cairo_save (cr);
				gdk_cairo_set_source_pixbuf(cr,title4,topleftwid+lsegwid+title2wid+padwid,0);
				cairo_pattern_set_extend(cairo_get_source(cr),CAIRO_EXTEND_REPEAT);
				cairo_rectangle(cr,topleftwid+lsegwid+title2wid+padwid,0,title4wid,title4hite);
 				cairo_clip(cr);
				cairo_paint_with_alpha(cr,100);
			cairo_restore (cr);
		}

//title5
	if (title5!=NULL)
		{
			cairo_save (cr);
				gdk_cairo_set_source_pixbuf(cr,title5,topleftwid+lsegwid+title2wid+padwid+title5wid,0);
				cairo_pattern_set_extend(cairo_get_source(cr),CAIRO_EXTEND_REPEAT);
				cairo_rectangle(cr,topleftwid+lsegwid+title2wid+padwid+title4wid,0,rsegwid,title3hite);
 				cairo_clip(cr);
				cairo_paint_with_alpha(cr,100);
			cairo_restore (cr);
		}

//toprite
	cairo_save (cr);
		gdk_cairo_set_source_pixbuf(cr,toprite,boxwid-topritewid,0);
		cairo_paint_with_alpha(cr,100);
	cairo_restore (cr);

//leftside
	if (leftside!=NULL)
		{
	cairo_save (cr);
		gdk_cairo_set_source_pixbuf(cr,gdk_pixbuf_scale_simple(leftside,leftsidewid,boxhite-bottomlefthite-toplefthite,GDK_INTERP_BILINEAR),0,toplefthite);
		cairo_paint_with_alpha(cr,100);
	cairo_restore (cr);
		}

//riteside
	if (riteside!=NULL)
		{
	cairo_save (cr);
		gdk_cairo_set_source_pixbuf(cr,gdk_pixbuf_scale_simple(riteside,ritesidewid,boxhite-bottomritehite-topritehite,GDK_INTERP_BILINEAR),boxwid-ritesidewid,topritehite);
		cairo_paint_with_alpha(cr,100);
	cairo_restore (cr);
		}

//bottomleft
	cairo_save (cr);
		gdk_cairo_set_source_pixbuf(cr,bottomleft,0,boxhite-bottomlefthite);
		cairo_paint_with_alpha(cr,100);
	cairo_restore (cr);

//bottomrite
	cairo_save (cr);
		gdk_cairo_set_source_pixbuf(cr,bottomrite,boxwid-bottomritewid,boxhite-bottomritehite);
		cairo_paint_with_alpha(cr,100);
	cairo_restore (cr);

//bottom
	cairo_save (cr);
		gdk_cairo_set_source_pixbuf(cr,bottom,bottomleftwid,boxhite-bottomhite);
		cairo_pattern_set_extend(cairo_get_source(cr),CAIRO_EXTEND_REPEAT);
		cairo_rectangle(cr,bottomleftwid,boxhite-bottomhite,boxwid-bottomritewid-bottomleftwid,bottomhite);
 		cairo_clip(cr);
		cairo_paint_with_alpha(cr,100);
	cairo_restore (cr);

//buttons
//menu
hiteoffset=0;
	cairo_save (cr);
		if(menu!=NULL)
			{
				hiteoffset=(title3hite-menuhite)/2;
				gdk_cairo_set_source_pixbuf(cr,menu,button_offset+leftsidewid,hiteoffset);
				cairo_paint_with_alpha(cr,100);
			}
//close
		if(close!=NULL)
			{
				hiteoffset=(title3hite-closehite)/2;
				gdk_cairo_set_source_pixbuf(cr,close,boxwid-button_offset-ritesidewid-closewid,hiteoffset);
				cairo_paint_with_alpha(cr,100);
			}
//max
		if(max!=NULL)
			{
				hiteoffset=(title3hite-maxhite)/2;
				gdk_cairo_set_source_pixbuf(cr,max,boxwid-button_offset-ritesidewid-closewid-maxwid-button_spacing,hiteoffset);
				cairo_paint_with_alpha(cr,100);
			}
//min
		if(min!=NULL)
			{
				hiteoffset=(title3hite-minhite)/2;
				gdk_cairo_set_source_pixbuf(cr,min,boxwid-button_offset-ritesidewid-closewid-maxwid-minwid-button_spacing-button_spacing,hiteoffset);
				cairo_paint_with_alpha(cr,100);
			}
	cairo_restore (cr);

	cairo_surface_write_to_png(surface,outframe);

	if (topleft!=NULL && topleft!=missingImage)
		g_object_unref(topleft);
	if (toprite!=NULL && toprite!=missingImage)
		g_object_unref(toprite);
	if (title1!=NULL && title1!=missingImage)
		g_object_unref(title1);
	if (title2!=NULL && title2!=missingImage)
		g_object_unref(title2);
	if (title3!=NULL && title3!=missingImage)
		g_object_unref(title3);
	if (title4!=NULL && title4!=missingImage)
		g_object_unref(title4);
	if (title5!=NULL && title5!=missingImage)
		g_object_unref(title5);
	if (riteside!=NULL && riteside!=missingImage)
		g_object_unref(riteside);
	if (leftside!=NULL && leftside!=missingImage)
		g_object_unref(leftside);
	if (bottomleft!=NULL && bottomleft!=missingImage)
		g_object_unref(bottomleft);
	if (bottomrite!=NULL && bottomrite!=missingImage)
		g_object_unref(bottomrite);
	if (bottom!=NULL && bottom!=missingImage)
		g_object_unref(bottom);
	if (close!=NULL && close!=missingImage)
		g_object_unref(close);
	if (max!=NULL && max!=missingImage)
		g_object_unref(max);
	if (min!=NULL && min!=missingImage)
		g_object_unref(min);
	if (menu!=NULL && menu!=missingImage)
		g_object_unref(menu);

	cairo_surface_destroy(surface);
	cairo_destroy(cr);
}

void getspace(char* folder)
{
	char*	filename;
	FILE*	fp=NULL;
	char*	offsetstr;
	char*	spacestr;

	asprintf(&filename,"%s/xfwm4/themerc",folder);
	fp=fopen(filename,"r");

	button_offset=0;
	button_spacing=0;

	if (fp==NULL)
		{
			printf("No themerc file... %s\n",filename);
			return;
		}

	while (fgets(generalBuffer,64,fp)!=NULL)
		{
			offsetstr=NULL;
			spacestr=NULL;
			offsetstr=strstr((char*)&generalBuffer,"button_offset=");
			spacestr=strstr((char*)&generalBuffer,"button_spacing=");
			
			if (offsetstr!=NULL)
					button_offset=atoi((char*)&generalBuffer[14]);

			if (spacestr!=NULL)
					button_spacing=atoi((char*)&generalBuffer[15]);
		}

	freeAndNull(&filename);

	if (fp!=NULL)
		fclose(fp);
}

void makeIcon(char* themename,char* outPath)
{
	GdkPixbuf*	home;
	GdkPixbuf*	folder;
	GdkPixbuf*	computer;
	GdkPixbuf*	drive;
	cairo_surface_t	*surface;
	cairo_t		*cr;
	GtkIconTheme*	theme=NULL;

	controlsPixbuf=NULL;
	surface=cairo_image_surface_create(CAIRO_FORMAT_ARGB32,256,ICONTHEMESIZE);
	cr=cairo_create(surface);

	theme=gtk_icon_theme_new();
	gtk_icon_theme_set_custom_theme(theme,themename);

	home=gtk_icon_theme_load_icon(theme,"user-home",ICONTHEMESIZE,GTK_ICON_LOOKUP_FORCE_SIZE,NULL);
	folder=gtk_icon_theme_load_icon(theme,"folder",ICONTHEMESIZE,GTK_ICON_LOOKUP_FORCE_SIZE,NULL);
	computer=gtk_icon_theme_load_icon(theme,"user-desktop",ICONTHEMESIZE,GTK_ICON_LOOKUP_FORCE_SIZE,NULL);
	drive=gtk_icon_theme_load_icon(theme,"drive-harddisk",ICONTHEMESIZE,GTK_ICON_LOOKUP_FORCE_SIZE,NULL);

	if(home!=NULL)
		{
			gdk_cairo_set_source_pixbuf(cr,home,0,0);
			cairo_paint_with_alpha(cr,100);
			g_object_unref(home);
		}
	if(folder!=NULL)
		{
			gdk_cairo_set_source_pixbuf(cr,folder,ICONTHEMESIZE,0);
			cairo_paint_with_alpha(cr,100);
			g_object_unref(folder);
		}
	if(computer!=NULL)
		{
			gdk_cairo_set_source_pixbuf(cr,computer,ICONTHEMESIZE*2,0);
			cairo_paint_with_alpha(cr,100);
			g_object_unref(computer);
		}
	if(drive!=NULL)
		{
			gdk_cairo_set_source_pixbuf(cr,drive,ICONTHEMESIZE*3,0);
			cairo_paint_with_alpha(cr,100);
			g_object_unref(drive);
		}

	cairo_surface_write_to_png(surface,outPath);

	cairo_surface_destroy(surface);
	cairo_destroy(cr);
}

