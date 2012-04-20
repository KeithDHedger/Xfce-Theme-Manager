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
 * thumbnails.cpp
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

GdkPixbuf *cursorprev (const char *ptrname,char* themename)
{
	XcursorImage	*image;
	GdkPixbuf	*scaled=NULL, *pixbuf=NULL;
	gsize		bsize;
	guchar		*buffer, *p, tmp;

    /* load the image */

	image=XcursorLibraryLoadImage (ptrname,themename,32);

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
					scaled=gdk_pixbuf_scale_simple(pixbuf,32,32,GDK_INTERP_BILINEAR);
					g_object_unref (G_OBJECT (pixbuf));
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

	gtkPixbuf=NULL;
	surface=cairo_image_surface_create(CAIRO_FORMAT_ARGB32,128,32);
	cr=cairo_create(surface);

	arrow=cursorprev("left_ptr",theme);
	move=cursorprev("fleur",theme);
	wait=cursorprev("watch",theme);
	hand=cursorprev("hand2",theme);

	if (arrow==NULL || move==NULL || wait==NULL || hand==NULL)
		exit(1);
	cairo_save (cr);
		gdk_cairo_set_source_pixbuf(cr,arrow,0,0);
		cairo_paint_with_alpha(cr,100);
		gdk_cairo_set_source_pixbuf(cr,move,32,0);
		cairo_paint_with_alpha(cr,100);
		gdk_cairo_set_source_pixbuf(cr,wait,64,0);
		cairo_paint_with_alpha(cr,100);
		gdk_cairo_set_source_pixbuf(cr,hand,96,0);
		cairo_paint_with_alpha(cr,100);
	cairo_restore (cr);

	cairo_surface_write_to_png(surface,outPath);

	g_object_unref(arrow);
	g_object_unref(move);
	g_object_unref(wait);
	g_object_unref(hand);

	cairo_surface_destroy(surface);
	cairo_destroy(cr);
}

