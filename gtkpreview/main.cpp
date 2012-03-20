/*
 * Original author David D Lowe <daviddlowe.flimm@gmail.com>
 *
 *
 *
 * Seriously mucked about by:
 *
 * K.D.Hedger 2011 <kdheger@yahoo.co.uk>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gtk/gtk.h>

#define GTK_THUMBNAIL_SIZE 96

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

	gtk_window_get_size(GTK_WINDOW(widget), &width, &height);

	visual=gtk_widget_get_visual(widget);
	pixmap=gdk_pixmap_new(NULL, width, height, visual->depth);
	gdk_drawable_set_colormap(GDK_DRAWABLE(pixmap), gtk_widget_get_colormap(widget));

	window=gtk_widget_get_window(widget);

	gdk_window_redirect_to_drawable(window, pixmap, 0, 0, 0, 0, width, height);
	gdk_window_set_override_redirect(window, TRUE);
	gtk_window_move(GTK_WINDOW(widget), gdk_screen_get_width(screen), gdk_screen_get_height(screen));
	gtk_widget_show(widget);

	gdk_window_process_updates(window, TRUE);
	gtk_widget_hide(widget);

	return pixmap;
}

GdkPixbuf * create_gtk_theme_pixbuf(char* name)
{
	GtkSettings *settings;
	GtkWidget *window, *vbox, *box, *stock_button, *checkbox, *radio;
	GtkRequisition requisition;
	GtkAllocation allocation;
	GdkPixmap *pixmap;
	GdkPixbuf *pixbuf, *retval;
	gint width, height;

	settings=gtk_settings_get_default();
	g_object_set(settings, "gtk-theme-name",(char*)name,"gtk-color-scheme", "default",NULL);

	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	
	gtk_window_set_default_size((GtkWindow*)window, 200,50);

	vbox=gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	box=gtk_hbox_new(FALSE, 6);
	gtk_container_set_border_width(GTK_CONTAINER(box), 6);
	gtk_box_pack_start(GTK_BOX(vbox), box, FALSE, FALSE, 0);
	stock_button=gtk_button_new_from_stock(GTK_STOCK_OPEN);
	gtk_box_pack_start(GTK_BOX(box), stock_button, FALSE, FALSE, 0);
	checkbox=gtk_check_button_new();
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbox), TRUE);
	gtk_box_pack_start(GTK_BOX(box), checkbox, FALSE, FALSE, 0);
	radio=gtk_radio_button_new_from_widget(NULL);
	gtk_box_pack_start(GTK_BOX(box), radio, FALSE, FALSE, 0);

	gtk_widget_show_all(vbox);
	gtk_widget_realize(stock_button);
	gtk_widget_realize(gtk_bin_get_child(GTK_BIN(stock_button)));
	gtk_widget_realize(checkbox);
	gtk_widget_realize(radio);
	gtk_widget_map(stock_button);
	gtk_widget_map(gtk_bin_get_child(GTK_BIN(stock_button)));
	gtk_widget_map(checkbox);
	gtk_widget_map(radio);

	gtk_widget_size_request(window, &requisition);
	allocation.x=0;
	allocation.y=0;
	allocation.width=requisition.width;
	allocation.height=requisition.height;
	gtk_widget_size_allocate(window, &allocation);
	gtk_widget_size_request(window, &requisition);

	gtk_window_get_size(GTK_WINDOW(window), &width, &height);

	pixmap=draw_window_on_pixbuf(window);

	pixbuf=gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, width, height);
	gdk_pixbuf_get_from_drawable(pixbuf, pixmap, NULL, 0, 0, 0, 0, width, height);

	retval=gdk_pixbuf_scale_simple(pixbuf,GTK_THUMBNAIL_SIZE,(int) GTK_THUMBNAIL_SIZE *(((double) height) /((double) width)),GDK_INTERP_BILINEAR);
//	retval=gdk_pixbuf_scale_simple(pixbuf,256,96,GDK_INTERP_BILINEAR);
retval=pixbuf;
//	g_object_unref(pixbuf);
	gtk_widget_destroy(window);
	g_object_unref(pixmap);

	return retval;
}

void makepicX(void)
{
	GdkPixmap*	basepixmap;
	GdkPixbuf*	basepixbuf;
	GdkPixbuf*	pic1;
	
	
	//basepixmap=gdk_pixmap_new(NULL,240,240,32);
		
	//gdk_pixbuf_get_from_drawable(basepixbuf, basepixmap, NULL, 0, 0, 0, 0, 240, 240);
	basepixbuf=gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, 400, 400);
	pic1=gdk_pixbuf_new_from_file("pat.png",NULL);
	
//	gdk_pixbuf_copy_area(pic1,0,0,gdk_pixbuf_get_width(pic1),gdk_pixbuf_get_height(pic1),basepixbuf,100,10);

	//gdk_pixbuf_scale(pic1,basepixbuf,20,20,128,128,20,20,2.0,1.0,GDK_INTERP_NEAREST);	
	gdk_pixbuf_copy_area(gdk_pixbuf_scale_simple(pic1,50,50,GDK_INTERP_BILINEAR),0,0,50,50,basepixbuf,20,20);
	gdk_pixbuf_savev(basepixbuf,"./out.png","png",NULL,NULL,NULL);
}

GdkPixmap*	basepixmap;

void makeborder(void)
{
	GdkPixbuf*	topleft;
	GdkPixbuf*	toprite;
	GdkPixbuf*	title1;
	GdkPixbuf*	title2;
	GdkPixbuf*	title3;
	GdkPixbuf*	title4;
	GdkPixbuf*	title5;
	GdkPixbuf*	riteside;
	GdkPixbuf*	leftside;
	GdkPixbuf*	bottomleft;
	GdkPixbuf*	bottomrite;
	GdkPixbuf*	bottom;
	GdkPixbuf*	close;
	GdkPixbuf*	max;
	GdkPixbuf*	min;
	GdkPixbuf*	menu;
}

int main(int argc,char **argv)
{

	gtk_init(&argc, &argv);

	basepixbuf=gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, 400, 400);
	makeborder();

//makepic();
	return(0);

	GdkPixbuf *pixbuf=NULL;

	gtk_init(&argc, &argv);
	pixbuf=create_gtk_theme_pixbuf(argv[1]);
	gdk_pixbuf_savev(pixbuf,argv[2],"png",NULL,NULL,NULL);
	g_object_unref(pixbuf);


	return(0);
}
