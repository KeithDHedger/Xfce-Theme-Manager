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
#include <string.h>

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

//GdkPixmap*	basepixmap;
GdkPixbuf*	basepixbuf;
int		button_offset,button_spacing;

//"$1"/xfwm4/top-left-active.*
GdkPixbuf * loadfile(char* bordername,const char* name)
{
	char	pixmapname[2048];
	GdkPixbuf* tmpbuf;

	sprintf((char*)pixmapname,"%s/xfwm4/%s.xpm",bordername,name);
	tmpbuf=gdk_pixbuf_new_from_file((char*)pixmapname,NULL);
	if (tmpbuf==NULL)
		{
			sprintf((char*)pixmapname,"%s/xfwm4/%s.png",bordername,name);
			tmpbuf=gdk_pixbuf_new_from_file((char*)pixmapname,NULL);
		}
	
//	printf("%s\n",pixmapname);
//if (tmpbuf==NULL)
//	printf("no pixbuf\n");
//else
//	printf("got a pix buf\n");
	
	return(tmpbuf);
}
#define boxhite 80

void makeborder(char* folder)
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
	
	int		lsegwid,rsegwid,boxwid,hiteoffset;

	topleft=loadfile(folder,"top-left-active");
	toprite=loadfile(folder,"top-right-active");
	title1=loadfile(folder,"title-1-active");
	title2=loadfile(folder,"title-2-active");
	title3=loadfile(folder,"title-3-active");
	title4=loadfile(folder,"title-4-active");
	title5=loadfile(folder,"title-5-active");
	riteside=loadfile(folder,"right-active");
	leftside=loadfile(folder,"left-active");
	bottomleft=loadfile(folder,"bottom-left-active");
	bottomrite=loadfile(folder,"bottom-right-active");
	bottom=loadfile(folder,"bottom-active");
	close=loadfile(folder,"close-active");
	max=loadfile(folder,"maximize-active");
	min=loadfile(folder,"hide-active");
	menu=loadfile(folder,"menu-active");

	int closewid,maxwid,minwid,menuwid;
	int closehite,maxhite,minhite,menuhite;
	int topleftwid,toplefthite,topritewid,topritehite;
	int bottomleftwid,bottomlefthite,bottomritewid,bottomritehite;
	int leftsidewid,leftsidehite,ritesidewid,ritesidehite;
	int bottomwid,bottomhite;

	int title1wid,title1hite;
	int title2wid,title2hite;
	int title3wid,title3hite;
	int title4wid,title4hite;
	int title5wid,title5hite;
	
	gdouble	sw;
	gdouble	sh;

	if (title1!=NULL)
		{
			title1wid=gdk_pixbuf_get_width((const GdkPixbuf *)title1);
			title1hite=gdk_pixbuf_get_height((const GdkPixbuf *)title1);
		}
	else
		{
			title1wid=0;
			title1hite=0;
		}
	if (title2!=NULL)
		{
			title2wid=gdk_pixbuf_get_width((const GdkPixbuf *)title2);
			title2hite=gdk_pixbuf_get_height((const GdkPixbuf *)title2);
		}
	else
		{
			title2wid=0;
			title2hite=0;
		}
	if (title3!=NULL)
		{
			title3wid=gdk_pixbuf_get_width((const GdkPixbuf *)title3);
			title3hite=gdk_pixbuf_get_height((const GdkPixbuf *)title3);
		}
	else
		{
			title3wid=0;
			title3hite=0;
		}
	if (title4!=NULL)
		{
		title4wid=gdk_pixbuf_get_width((const GdkPixbuf *)title4);
		title4hite=gdk_pixbuf_get_height((const GdkPixbuf *)title4);
		}
	else
		{
			title4wid=0;
			title4hite=0;
		}
	if (title5!=NULL)
		{
			title5wid=gdk_pixbuf_get_width((const GdkPixbuf *)title5);
			title5hite=gdk_pixbuf_get_height((const GdkPixbuf *)title5);
		}
	else
		{
			title5wid=0;
			title5hite=0;
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
	leftsidehite=gdk_pixbuf_get_height((const GdkPixbuf *)leftside);
	
	ritesidewid=gdk_pixbuf_get_width((const GdkPixbuf *)riteside);
	ritesidehite=gdk_pixbuf_get_height((const GdkPixbuf *)riteside);
	
	bottomwid=gdk_pixbuf_get_width((const GdkPixbuf *)bottom);
	bottomhite=gdk_pixbuf_get_height((const GdkPixbuf *)bottom);
	
	closewid=gdk_pixbuf_get_width((const GdkPixbuf *)close);
	maxwid=gdk_pixbuf_get_width((const GdkPixbuf *)max);
	minwid=gdk_pixbuf_get_width((const GdkPixbuf *)min);
	menuwid=gdk_pixbuf_get_width((const GdkPixbuf *)menu);
	
	closehite=gdk_pixbuf_get_height((const GdkPixbuf *)close);
	maxhite=gdk_pixbuf_get_height((const GdkPixbuf *)max);
	minhite=gdk_pixbuf_get_height((const GdkPixbuf *)min);
	menuhite=gdk_pixbuf_get_height((const GdkPixbuf *)menu);
	
	lsegwid=menuwid+button_spacing;
	rsegwid=closewid+maxwid+minwid+(button_spacing*3);
	boxwid=topleftwid+lsegwid+title2wid+64+title4wid+rsegwid+topritewid;

	basepixbuf=gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE,8, boxwid, boxhite);
//	basepixbuf=gdk_pixbuf_new_from_file("pat.png",NULL);

	cairo_surface_t *surface;
	cairo_t *cr;

	surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, boxwid, boxhite);
	cr = cairo_create (surface);

//topleft
	cairo_save (cr);

	gdk_cairo_set_source_pixbuf(cr,topleft,0,0);
	cairo_paint_with_alpha(cr,100);
	
	cairo_restore (cr);

//	gdk_pixbuf_copy_area(topleft,0,0,topleftwid,toplefthite,basepixbuf,0,0);

//gdk_pixbuf_scale_simple(title1,leftsegwid,title3hite,GDK_INTERP_BILINEAR);
//com2_1="image  SrcOver ${topleft[1]},0 $lsegwid,${title3[2]} \"$(echo ${title1[0]})\""
//title1
	if (title1!=NULL)
		{
			cairo_save (cr);
				gdk_cairo_set_source_pixbuf(cr,gdk_pixbuf_scale_simple(title1,lsegwid,title3hite,GDK_INTERP_BILINEAR),topleftwid,0);
				cairo_paint_with_alpha(cr,100);
			cairo_restore (cr);

		//gdk_pixbuf_copy_area(gdk_pixbuf_scale_simple(title1,lsegwid,title3hite,GDK_INTERP_BILINEAR),0,0,lsegwid,title3hite,basepixbuf,topleftwid,0);
		}
//title2
	if (title2!=NULL)
		{
			cairo_save (cr);
				gdk_cairo_set_source_pixbuf(cr,title2,topleftwid+lsegwid,0);
				cairo_paint_with_alpha(cr,100);
			cairo_restore (cr);
		}
//		gdk_pixbuf_copy_area(title2,0,0,title2wid,title2hite,basepixbuf,topleftwid+lsegwid,0);
//com2_2="image  SrcOver $((topleft[1]+lsegwid)),0 0,0 \"$(echo ${title2[0]})\""

//title3
//com2_3="image  SrcOver $((topleft[1]+lsegwid+title2[1])),0 64,${title3[2]} \"$(echo ${title3[0]})\""
	if (title3!=NULL)
		{
			cairo_save (cr);
				gdk_cairo_set_source_pixbuf(cr,gdk_pixbuf_scale_simple(title3,64,title3hite,GDK_INTERP_BILINEAR),topleftwid+lsegwid+title2wid,0);
				cairo_paint_with_alpha(cr,100);
			cairo_restore (cr);
		}
		//gdk_pixbuf_copy_area(gdk_pixbuf_scale_simple(title3,64,title3hite,GDK_INTERP_BILINEAR),0,0,64,title3hite,basepixbuf,topleftwid+lsegwid+title2wid,0);

//title4
//com2_4="image  SrcOver $((topleft[1]+lsegwid+title2[1]+64)),0 0,0 \"$(echo ${title4[0]})\""
	if (title4!=NULL)
		{
			cairo_save (cr);
				gdk_cairo_set_source_pixbuf(cr,title2,topleftwid+lsegwid+title2wid+64,0);
				cairo_paint_with_alpha(cr,100);
			cairo_restore (cr);
		}
		//gdk_pixbuf_copy_area(title4,0,0,title4wid,title4hite,basepixbuf,topleftwid+lsegwid+title2wid+64,0);
//
//title5
//com2_5="image  SrcOver $((topleft[1]+lsegwid+title2[1]+64+title4[1])),0 $rsegwid,${title3[2]} \"$(echo ${title5[0]})\""

	if (title5!=NULL)
		{
			cairo_save (cr);
					gdk_cairo_set_source_pixbuf(cr,gdk_pixbuf_scale_simple(title5,rsegwid,title3hite,GDK_INTERP_BILINEAR),topleftwid+lsegwid+title2wid+64+title4wid,0);
			cairo_paint_with_alpha(cr,100);
			cairo_restore (cr);
		}
		//gdk_pixbuf_copy_area(gdk_pixbuf_scale_simple(title5,rsegwid,title3hite,GDK_INTERP_BILINEAR),0,0,rsegwid,title3hite,basepixbuf,topleftwid+lsegwid+title2wid+64+title4wid,0);

//toprite
//com3="image  SrcOver $((topleft[1]+lsegwid+title2[1]+64+title4[1]+rsegwid)),0 0,0 \"$(echo ${toprite[0]})\""
	cairo_save (cr);
		gdk_cairo_set_source_pixbuf(cr,toprite,boxwid-topritewid,0);
		cairo_paint_with_alpha(cr,100);
	cairo_restore (cr);

//	gdk_pixbuf_copy_area(toprite,0,0,topritewid,topritehite,basepixbuf,topleftwid+lsegwid+title2wid+64+title4wid+rsegwid,0);

//leftside
//com4="image  SrcOver 0,${topleft[2]} ${leftside[1]},$((boxhite-bottomleft[2]-topleft[2])) \"$(echo ${leftside[0]})\""
	//gdk_pixbuf_copy_area(gdk_pixbuf_scale_simple(leftside,leftsidewid,boxhite-bottomlefthite-toplefthite,GDK_INTERP_BILINEAR),0,0,leftsidewid,boxhite-bottomlefthite-toplefthite,basepixbuf,0,toplefthite);
	
	cairo_save (cr);
		gdk_cairo_set_source_pixbuf(cr,gdk_pixbuf_scale_simple(leftside,leftsidewid,boxhite-bottomlefthite-toplefthite,GDK_INTERP_BILINEAR),0,toplefthite);
		cairo_paint_with_alpha(cr,100);
	cairo_restore (cr);


//ritesie
//com5="image  SrcOver $((boxwid-riteside[1])),${toprite[2]} ${riteside[1]},$((boxhite-bottomrite[2]-toprite[2])) \"$(echo ${riteside[0]})\""
	cairo_save (cr);
		gdk_cairo_set_source_pixbuf(cr,gdk_pixbuf_scale_simple(riteside,ritesidewid,boxhite-bottomritehite-topritehite,GDK_INTERP_BILINEAR),boxwid-ritesidewid,topritehite);
		cairo_paint_with_alpha(cr,100);
	cairo_restore (cr);



	//gdk_pixbuf_copy_area(gdk_pixbuf_scale_simple(riteside,ritesidewid,boxhite-bottomritehite-topritehite,GDK_INTERP_BILINEAR),0,0,ritesidewid,boxhite-bottomritehite-topritehite,basepixbuf,boxwid-ritesidewid,topritehite);

//bottomleft
//com6="image  SrcOver 0,$((boxhite-bottomleft[2])) 0,0 \"$(echo ${bottomleft[0]})\""
	cairo_save (cr);
		gdk_cairo_set_source_pixbuf(cr,bottomleft,0,boxhite-bottomlefthite);
		cairo_paint_with_alpha(cr,100);
	cairo_restore (cr);


//	gdk_pixbuf_copy_area(bottomleft,0,0,bottomleftwid,bottomlefthite,basepixbuf,0,boxhite-bottomlefthite);

//bottomrite
//com7="image  SrcOver $((boxwid-bottomrite[1])),$((boxhite-bottomrite[2])) 0,0 \"$(echo ${bottomrite[0]})\""
//	gdk_pixbuf_copy_area(bottomrite,0,0,bottomritewid,bottomritehite,basepixbuf,boxwid-bottomritewid,boxhite-bottomritehite);
	cairo_save (cr);
		gdk_cairo_set_source_pixbuf(cr,bottomrite,boxwid-bottomritewid,boxhite-bottomlefthite);
		cairo_paint_with_alpha(cr,100);
	cairo_restore (cr);

//bottom
//com8="image  SrcOver ${bottomleft[1]},$((boxhite-bottom[2])) $((boxwid-bottomleft[1]-bottomrite[1])),${bottom[2]} \"$(echo ${bottom[0]})\""

	cairo_save (cr);
		gdk_cairo_set_source_pixbuf(cr,gdk_pixbuf_scale_simple(bottom,boxwid-bottomritewid-bottomleftwid,bottomhite,GDK_INTERP_BILINEAR),bottomleftwid,boxhite-bottomhite);
		cairo_paint_with_alpha(cr,100);
	cairo_restore (cr);


//	gdk_pixbuf_copy_area(gdk_pixbuf_scale_simple(bottom,boxwid-bottomritewid-bottomleftwid,bottomhite,GDK_INTERP_BILINEAR),0,0,boxwid-bottomritewid-bottomleftwid,bottomhite,basepixbuf,bottomleftwid,boxhite-bottomhite);


//menu
//menubut="image  SrcOver $((button_offset+leftside[1])),$hiteoffset 0,0 \"$(echo ${menu[0]})\""
	hiteoffset=(title3hite-menuhite)/2;
	cairo_save (cr);
		gdk_cairo_set_source_pixbuf(cr,menu,button_offset+leftsidewid,hiteoffset);
		cairo_paint_with_alpha(cr,100);

//close
		hiteoffset=(title3hite-closehite)/2;
		gdk_cairo_set_source_pixbuf(cr,close,boxwid-button_offset-ritesidewid-closewid,hiteoffset);
		cairo_paint_with_alpha(cr,100);
//max
		gdk_cairo_set_source_pixbuf(cr,max,boxwid-button_offset-ritesidewid-closewid-maxwid-button_spacing,hiteoffset);
		cairo_paint_with_alpha(cr,100);

//min
		gdk_cairo_set_source_pixbuf(cr,min,boxwid-button_offset-ritesidewid-closewid-maxwid-minwid-button_spacing-button_spacing,hiteoffset);
		cairo_paint_with_alpha(cr,100);
	cairo_restore (cr);

//	gdk_pixbuf_copy_area(menu,0,0,menuwid,menuhite,basepixbuf,button_offset+leftsidewid,hiteoffset);


//closebut="image  SrcOver $((boxwid-button_offset-riteside[1]-close[1])),$hiteoffset 0,0 \"$(echo ${close[0]})\""
//	hiteoffset=(title3hite-closehite)/2;
//	gdk_pixbuf_copy_area(close,0,0,closewid,closehite,basepixbuf,boxwid-button_offset-ritesidewid-closewid,hiteoffset);


//maxbut="image  SrcOver $((boxwid-button_offset-riteside[1]-close[1]-max[1]-button_spacing)),$hiteoffset 0,0 \"$(echo ${max[0]})\""
//	gdk_pixbuf_copy_area(max,0,0,maxwid,maxhite,basepixbuf,boxwid-button_offset-ritesidewid-closewid-maxwid-button_spacing,hiteoffset);


//printf ("%i %i %i %i\n",bottomleftwid,bottomlefthite,boxhite-bottomlefthite,0);

//	gdk_pixbuf_savev(basepixbuf,"./out.png","png",NULL,NULL,NULL);



cairo_surface_write_to_png(surface,"outcairo.png");
}

void getspace(char* folder)
{
	char	filename[2048];
	FILE*	fp;
	char*	strstart=NULL;

	sprintf((char*)filename,"%s/xfwm4/themerc",folder);
	fp=fopen(filename,"r");
	//fgets(filename,80,fp);
	while ( fgets(filename, 80, fp) != NULL)
	{
	strstart=NULL;
	strstart=strstr(filename,"button_offset");
	if (strstart!=NULL)
	{
	printf("%s\n%i\n",filename,button_offset);
		button_offset=atoi((char*)&filename[14]);
	printf("xx %s\n%i\n",filename,button_offset);
	}
	}
	fclose(fp);
}

int main(int argc,char **argv)
{

	gtk_init(&argc, &argv);
getspace(argv[3]);
return(0);
	//basepixbuf=gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, 400, 400);
	button_offset=atoi(argv[1]);
	button_spacing=atoi(argv[2]);
	makeborder(argv[3]);

//makepic();
	return(0);

	GdkPixbuf *pixbuf=NULL;

	gtk_init(&argc, &argv);
	pixbuf=create_gtk_theme_pixbuf(argv[1]);
	gdk_pixbuf_savev(pixbuf,argv[2],"png",NULL,NULL,NULL);
	g_object_unref(pixbuf);


	return(0);
}
