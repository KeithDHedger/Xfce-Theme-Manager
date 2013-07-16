/******************************************************
*
*     ©keithhedger Mon 17 Jun 12:11:12 BST 2013
*     kdhedger68713@gmail.com
*
*     panels.cpp
* 
******************************************************/
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <xfconf/xfconf.h>

#include "globals.h"

bool	panelChanging=false;
int		panelNumbers[10];

void setPanelData(bool fromwidget)
{
	panelData*	panel;
	GdkColor	colour;
	char		buffer[1024];
	XfconfChannel*	channelptr=xfconf_channel_get(XFCEPANELS);
	int alpha=65535;

	if(panelChanging==false)
		{
			panel=panels[currentPanel];
//style
			if(fromwidget==true)
				panel->style=gtk_combo_box_get_active((GtkComboBox*)panelStyleWidget);
			sprintf((char*)&buffer,"/panels/panel-%i/background-style",panel->panelNumber);
			setValue(XFCEPANELS,buffer,INT,(void*)(long)panel->style);

//size
			if(fromwidget==true)
				panel->size=gtk_range_get_value((GtkRange*)panelSizeWidget);
			sprintf((char*)&buffer,"/panels/panel-%i/size",panel->panelNumber);
			setValue(XFCEPANELS,buffer,INT,(void*)(long)panel->size);
//image
			if(fromwidget==true)
				{
					freeAndNull(&panel->imagePath);
					panel->imagePath=gtk_file_chooser_get_filename((GtkFileChooser*)panelImagePathWidget);
				}
			sprintf((char*)&buffer,"/panels/panel-%i/background-image",panel->panelNumber);
			setValue(XFCEPANELS,buffer,STRING,(void*)(long)panel->imagePath);

//alpha
			if(fromwidget==true)
				panel->alpha=gtk_range_get_value((GtkRange*)panelAlphaWidget);
			sprintf((char*)&buffer,"/panels/panel-%i/background-alpha",panel->panelNumber);
			setValue(XFCEPANELS,buffer,INT,(void*)(long)panel->alpha);
//colour
			if(fromwidget==true)
				{
					gtk_color_button_get_color((GtkColorButton*)panelColourWidget,&colour);
					panel->red=colour.red;
					panel->green=colour.green;
					panel->blue=colour.blue;
				}

			sprintf((char*)&buffer,"/panels/panel-%i/background-color",panel->panelNumber);
			xfconf_channel_set_array(channelptr,(const gchar*)&buffer,XFCONF_TYPE_UINT16,&panel->red,XFCONF_TYPE_UINT16,&panel->green,XFCONF_TYPE_UINT16,&panel->blue,XFCONF_TYPE_UINT16,&alpha,G_TYPE_INVALID);
		}
}

gboolean panelSizeCallback(GtkWidget *widget,GdkEvent *event,gpointer user_data)
{
	setPanelData(true);
	return(false);
}

void commnonPanelCallback(GtkWidget* widget,gpointer data)
{
	setPanelData(true);
}

void selectPanelStyle(GtkWidget* widget,gpointer data)
{
	int style;
	style=gtk_combo_box_get_active((GtkComboBox*)widget);

	switch(style)
		{
			case 0:
				gtk_widget_set_sensitive(panelImageBox,false);
				gtk_widget_set_sensitive(panelColourBox,false);
				gtk_widget_set_sensitive(panelAlphaBox,true);
				break;
			case 1:
				gtk_widget_set_sensitive(panelImageBox,false);
				gtk_widget_set_sensitive(panelColourBox,true);
				gtk_widget_set_sensitive(panelAlphaBox,true);
				break;
			case 2:
				gtk_widget_set_sensitive(panelColourBox,false);
				gtk_widget_set_sensitive(panelAlphaBox,false);
				gtk_widget_set_sensitive(panelImageBox,true);
				break;
		}

	setPanelData(true);
}

void selectPanel(GtkComboBox *widget, gpointer user_data)
{
	panelData*	panel;
	GdkColor	colour;

	panelChanging=true;
	currentPanel=gtk_combo_box_get_active((GtkComboBox*)panelSelect);

	panel=panels[currentPanel];

	gtk_combo_box_set_active((GtkComboBox*)panelStyleWidget,panel->style);
	gtk_file_chooser_set_filename((GtkFileChooser*)panelImagePathWidget,panel->imagePath);
	gtk_range_set_value((GtkRange*)panelSizeWidget,panel->size);

	colour.red=panel->red;
	colour.green=panel->green;
	colour.blue=panel->blue;
	gtk_color_button_set_color((GtkColorButton*)panelColourWidget,&colour);

	gtk_range_set_value((GtkRange*)panelAlphaWidget,panel->alpha);

	selectPanelStyle(panelStyleWidget,NULL);
	panelChanging=false;
}

void setPanelColour(GtkColorButton *widget, gpointer user_data)
{
	GdkColor	colour;
	int			panelnum;

	gtk_color_button_get_color((GtkColorButton*)widget,&colour);
	panelnum=gtk_combo_box_get_active((GtkComboBox*)panelSelect);
	panels[panelnum]->red=colour.red;
	panels[panelnum]->green=colour.green;
	panels[panelnum]->blue=colour.blue;
	setPanelData(true);
}

void makeNewPanelData(int num,int panelnum)
{
	panels[num]=(panelData*)malloc(sizeof(panelData));
	panels[num]->style=0;
	panels[num]->size=48;
	panels[num]->imagePath=NULL;
	panels[num]->red=56540;
	panels[num]->green=56026;
	panels[num]->blue=54741;
	panels[num]->alpha=100;
	panels[num]->panelNumber=panelnum;
	panelNumbers[num]=panelnum;
}


//#define PANEL_PROPERTIES_TYPE_VALUE_ARRAY (panel_properties_value_array_get_type ())
gchar *
_xfconf_string_from_gvalue(GValue *val)
{
    g_return_val_if_fail(val && G_VALUE_TYPE(val), NULL);

    switch(G_VALUE_TYPE(val)) {
        case G_TYPE_STRING:
        	printf("string\n");
            return g_value_dup_string(val);
        case G_TYPE_UCHAR:
        	printf("uchar\n");
            return g_strdup_printf("%u", (guint)g_value_get_uchar(val));
        case G_TYPE_CHAR:
#if GLIB_CHECK_VERSION (2, 32, 0)
            return g_strdup_printf("%d", g_value_get_schar(val));
#else
            return g_strdup_printf("%d", (gint)g_value_get_char(val));
#endif
        case G_TYPE_UINT:
          	printf("UINT\n");
          return g_strdup_printf("%u", g_value_get_uint(val));
        case G_TYPE_INT:
         	printf("INT\n");
           return g_strdup_printf("%d", g_value_get_int(val));
        case G_TYPE_UINT64:
            return g_strdup_printf("%" G_GUINT64_FORMAT,
                                   g_value_get_uint64(val));
        case G_TYPE_INT64:
            return g_strdup_printf("%" G_GINT64_FORMAT,
                                   g_value_get_int64(val));
        case G_TYPE_FLOAT:
            return g_strdup_printf("%f", (gdouble)g_value_get_float(val));
        case G_TYPE_DOUBLE:
            return g_strdup_printf("%f", g_value_get_double(val));
        case G_TYPE_BOOLEAN:
            return g_strdup(g_value_get_boolean(val) ? "true" : "false");
        default:
            if(G_VALUE_TYPE(val) == XFCONF_TYPE_UINT16) {
                return g_strdup_printf("%u",
                                       (guint)xfconf_g_value_get_uint16(val));
            } else if(G_VALUE_TYPE(val) == XFCONF_TYPE_INT16) {
                return g_strdup_printf("%d",
                                       (gint)xfconf_g_value_get_int16(val));
            }
            break;
    }

 //   g_warning("Unable to convert GValue to string");
    return NULL;
}
void TpopulatePanels(void)
{
// GPtrArray    *panels;
// guint         i, j, n_panels;
// 	GValue        val = { 0, };
	XfconfChannel*	channel=xfconf_channel_get("xfce4-panel");
 //   	printf("zzzzz\n");
	// if (xfconf_channel_get_property (channelptr, "/panels", &val))
//    {
  //  	printf("XXX\n");
  //  }
  //      if (G_VALUE_HOLDS_UINT (&val))
 //       {
//          n_panels = g_value_get_uint (&val);
//          panels = NULL;
//          printf("AAAAAAAAAA\n");
//        }
//panels = (GPtrArray*)g_value_get_boxed (&val);
 //         n_panels = panels->len;
 //         printf("%i\n",n_panels);
  GValue value = { 0, };

            if(!xfconf_channel_get_property(channel, "/panels", &value))
            {
            printf("SSSSSSS\n");
               // xfconf_query_printerr(_("Property \"%s\" does not exist on channel \"%s\""),
                //                      "/","panels");
                return;
            }
           else
           {
           int len=-1;
           xfconf_channel_get_array            (channel,"/panels", G_TYPE_INT,&len,G_TYPE_INVALID);
                    printf("Value is an array with %i items:::::::::\n", len);
           	GPtrArray *arr;
           	// = (GPtrArray*)g_value_get_boxed(&value);
                guint i;
 arr=xfconf_channel_get_arrayv(channel,"/panels");
                printf("Value is an array with %d items:\n", arr->len);
                for(i = 0; i < arr->len; ++i)
                {
                    GValue *item_value = (GValue *)g_ptr_array_index(arr, i);
                    int* t;
                    t=(int*)g_ptr_array_index(arr, i);
					printf("panel num=%i\n",(int)*t);
					char* s;
					s=(char*)g_ptr_array_index(arr, i);
					printf("panel num=%s\n",s);
                    if(item_value)
                    {
                      gchar *str_val = _xfconf_string_from_gvalue(item_value);
                    	if(str_val!=NULL)
                     	   printf("%s\n", str_val);
                       // g_free(str_val);
                    }
                }
               // g_print("\n\n");
           }
}

void populatePanels(void)
{
	FILE*	fp;
	char	buffer[1024];
	char	command[1024];
	int		cnt=0;
	int		tempint;
	char*	tempstr=NULL;
	int		red,green,blue,alpha;
	int		temparray[4]={0,0,0,0};

	bool	gotthispanel;
	for(int j=0;j<10;j++)
		{
			gotthispanel=false;

			tempint=-1;
			sprintf((char*)&buffer,"/panels/panel-%i/background-style",j);
			getValue(XFCEPANELS,(const char*)buffer,INT,&tempint);
			if(tempint!=-1)
				{
					if(gotthispanel==false)
						{
							gotthispanel=true;
							makeNewPanelData(cnt,j);
						}
					panels[cnt]->style=tempint;
				}

			sprintf((char*)&buffer,"/panels/panel-%i/size",j);
			tempint=-1;
			getValue(XFCEPANELS,(const char*)buffer,INT,&tempint);
			if(tempint!=-1)
				{
					if(gotthispanel==false)
						{
							gotthispanel=true;
							makeNewPanelData(cnt,j);
						}
					panels[cnt]->size=tempint;
				}

			sprintf((char*)&buffer,"/panels/panel-%i/background-image",j);
			getValue(XFCEPANELS,(const char*)buffer,STRING,&tempstr);
			if(strcmp("DEADBEEF",tempstr)!=0)
				{
					if(gotthispanel==false)
						{
							gotthispanel=true;
							makeNewPanelData(cnt,j);
						}

					panels[cnt]->imagePath=strdup(tempstr);
					freeAndNull(&tempstr);
				}


			sprintf((char*)&buffer,"/panels/panel-%i/background-color",j);
			getValue(XFCEPANELS,(const char*)buffer,COLOURARRAY,&temparray);
			if(temparray[0]!=-1)
				{
					if(gotthispanel==false)
						{
							gotthispanel=true;
							makeNewPanelData(cnt,j);
						}
					panels[cnt]->red=temparray[0];
					panels[cnt]->green=temparray[1];
					panels[cnt]->blue=temparray[2];
				}

			sprintf((char*)&buffer,"/panels/panel-%i/background-alpha",j);
			getValue(XFCEPANELS,(const char*)buffer,INT,&tempint);
			if(tempint!=-1)
				{
					if(gotthispanel==false)
						{
							gotthispanel=true;
							makeNewPanelData(cnt,j);
						}
					panels[cnt]->alpha=tempint;
				}

			if(gotthispanel==true)
				{
					revertPanels[cnt]=(panelData*)malloc(sizeof(panelData));
					revertPanels[cnt]->style=panels[cnt]->style;
					revertPanels[cnt]->size=panels[cnt]->size;
					if(panels[cnt]->imagePath!=NULL)
						revertPanels[cnt]->imagePath=strdup(panels[cnt]->imagePath);
					else
						revertPanels[cnt]->imagePath=NULL;
					revertPanels[cnt]->red=panels[cnt]->red;
					revertPanels[cnt]->green=panels[cnt]->green;
					revertPanels[cnt]->blue=panels[cnt]->blue;
					revertPanels[cnt]->alpha=panels[cnt]->alpha;
					revertPanels[cnt]->panelNumber=panelNumbers[cnt];
					cnt++;
				}
		}
	numOfPanels=cnt;
}

void populatePanelsAAAA(void)
{
	FILE*	fp;
	char	buffer[1024];
	char	command[1024];
	int		cnt=0;
	int		tempint;

//TpopulatePanels();

	bool	gotthispanel;
	for(int j=0;j<10;j++)
		{
			gotthispanel=false;
			buffer[0]=0;
			tempint=-1;
			//sprintf((char*)&command,"xfconf-query  array -c xfce4-panel -p /panels/panel-%i/background-style 2>/dev/null",j);
			//fp=popen(command,"r");
			//fgets(buffer,1024,fp);
			//pclose(fp);
			sprintf((char*)&buffer,"/panels/panel-%i/background-style",j);
			getValue(XFCEPANELS,(const char*)buffer,INT,&tempint);
			if(strlen(buffer)>0)
				{
					if(gotthispanel==false)
						{
							gotthispanel=true;
							makeNewPanelData(cnt,j);
						}
					panels[cnt]->style=atoi(buffer);
				}
			buffer[0]=0;
			sprintf((char*)&command,"xfconf-query  array -c xfce4-panel -p /panels/panel-%i/size 2>/dev/null",j);
			fp=popen(command,"r");
			fgets(buffer,1024,fp);
			pclose(fp);
			if(strlen(buffer)>0)
				{
					if(gotthispanel==false)
						{
							gotthispanel=true;
							makeNewPanelData(cnt,j);
						}
					panels[cnt]->size=atoi(buffer);
				}

			buffer[0]=0;
			sprintf((char*)&command,"xfconf-query  array -c xfce4-panel -p /panels/panel-%i/background-image 2>/dev/null",j);
			fp=popen(command,"r");
			fgets(buffer,1024,fp);
			pclose(fp);
			if(strlen(buffer)>0)
				{
					if(gotthispanel==false)
						{
							gotthispanel=true;
							makeNewPanelData(cnt,j);
						}

					buffer[strlen(buffer)-1]=0;
					panels[cnt]->imagePath=strdup(buffer);
				}

			buffer[0]=0;
			sprintf((char*)&command,"xfconf-query  array -c xfce4-panel -p /panels/panel-%i/background-color 2>/dev/null",j);
			fp=popen(command,"r");
			fgets(buffer,1024,fp);
			if(strlen(buffer)>0)
				{
					if(gotthispanel==false)
						{
							gotthispanel=true;
							makeNewPanelData(cnt,j);
						}

					fgets(buffer,1024,fp);

					fgets(buffer,1024,fp);
					panels[cnt]->red=atoi(buffer);
					fgets(buffer,1024,fp);
					panels[cnt]->green=atoi(buffer);
					fgets(buffer,1024,fp);
					panels[cnt]->blue=atoi(buffer);
				}
			pclose(fp);

			buffer[0]=0;
			sprintf((char*)&command,"xfconf-query  array -c xfce4-panel -p /panels/panel-%i/background-alpha 2>/dev/null",j);
			fp=popen(command,"r");
			fgets(buffer,1024,fp);
			pclose(fp);
			if(strlen(buffer)>0)
				{
					if(gotthispanel==false)
						{
							gotthispanel=true;
							makeNewPanelData(cnt,j);
						}
					panels[cnt]->alpha=atoi(buffer);
				}

			if(gotthispanel==true)
				{
					revertPanels[cnt]=(panelData*)malloc(sizeof(panelData));
					revertPanels[cnt]->style=panels[cnt]->style;
					revertPanels[cnt]->size=panels[cnt]->size;
					if(panels[cnt]->imagePath!=NULL)
						revertPanels[cnt]->imagePath=strdup(panels[cnt]->imagePath);
					else
						revertPanels[cnt]->imagePath=NULL;
					revertPanels[cnt]->red=panels[cnt]->red;
					revertPanels[cnt]->green=panels[cnt]->green;
					revertPanels[cnt]->blue=panels[cnt]->blue;
					revertPanels[cnt]->alpha=panels[cnt]->alpha;
					revertPanels[cnt]->panelNumber=panelNumbers[cnt];
					cnt++;
				}
		}
	numOfPanels=cnt;
}


void setPanels(void)
{
	panelChanging=false;
	for(int j=0;j<numOfPanels;j++)
		{
			currentPanel=j;
			setPanelData(false);
		}

	currentPanel=0;
	selectPanel((GtkComboBox*)panelSelect,NULL);
}

void resetPanels(void)
{
	for(int j=0;j<numOfPanels;j++)
		{
			if(panels[j]->imagePath!=NULL)
				g_free(panels[j]->imagePath);
			g_free(panels[j]);
			panels[j]=(panelData*)malloc(sizeof(panelData));
			panels[j]->style=revertPanels[j]->style;
			panels[j]->size=revertPanels[j]->size;
			if(revertPanels[j]->imagePath!=NULL)
				panels[j]->imagePath=strdup(revertPanels[j]->imagePath);
			else
				panels[j]->imagePath=NULL;
			panels[j]->red=revertPanels[j]->red;
			panels[j]->green=revertPanels[j]->green;
			panels[j]->blue=revertPanels[j]->blue;
			panels[j]->alpha=revertPanels[j]->alpha;
			panels[j]->panelNumber=panelNumbers[j];
		}
	setPanels();
}
