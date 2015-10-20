/*
 *
 * ©K. D. Hedger. Tue 20 Oct 15:55:24 BST 2015 kdhedger68713@gmail.com

 * This file (panels.cpp) is part of Xfce-Theme-Manager.

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

#include <stdlib.h>
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

void populatePanels(void)
{
	char	buffer[1024];
	int		cnt=0;
	int		tempint;
	char*	tempstr=NULL;
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

			sprintf((char*)&buffer,"/panels/panel-%i/position",j);
			getValue(XFCEPANELS,(const char*)buffer,STRING,&tempstr);
			if(strcmp("DEADBEEF",tempstr)!=0)
				{
					if(gotthispanel==false)
						{
							gotthispanel=true;
							makeNewPanelData(cnt,j);
						}
					freeAndNull(&tempstr);
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
