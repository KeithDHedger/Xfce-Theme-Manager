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

#include "globals.h"

bool	panelChanging=false;
int		panelNumbers[10];

void setPanelData(bool fromwidget)
{
	panelData*	panel;
	GdkColor	colour;
	char		buffer[1024];

	if(panelChanging==false)
		{
			panel=panels[currentPanel];
//style
			if(fromwidget==true)
				panel->style=gtk_combo_box_get_active((GtkComboBox*)panelStyleWidget);
			sprintf((char*)&buffer,"xfconf-query -nt int -c xfce4-panel -p /panels/panel-%i/background-style -s %i",panel->panelNumber,panel->style);
			system(buffer);
//size
			if(fromwidget==true)
				panel->size=gtk_range_get_value((GtkRange*)panelSizeWidget);
			sprintf((char*)&buffer,"xfconf-query -nt int -c xfce4-panel -p /panels/panel-%i/size -s %i",panel->panelNumber,panel->size);
			system(buffer);
//image
			if(fromwidget==true)
				panel->imagePath=gtk_file_chooser_get_filename((GtkFileChooser*)panelImagePathWidget);
			sprintf((char*)&buffer,"xfconf-query -nt string -c xfce4-panel -p /panels/panel-%i/background-image -s %s",panel->panelNumber,panel->imagePath);
			system(buffer);
//alpha
			if(fromwidget==true)
				panel->alpha=gtk_range_get_value((GtkRange*)panelAlphaWidget);
			sprintf((char*)&buffer,"xfconf-query -nt int -c xfce4-panel -p /panels/panel-%i/background-alpha -s %i",panel->panelNumber,panel->alpha);
			system(buffer);
//colour
			if(fromwidget==true)
				{
					gtk_color_button_get_color((GtkColorButton*)panelColourWidget,&colour);
					panel->red=colour.red;
					panel->green=colour.green;
					panel->blue=colour.blue;
				}
			sprintf((char*)&buffer,"xfconf-query array -c xfce4-panel -p /panels/panel-%i/background-color -t uint -t uint -t uint -t uint -s %i -s %i -s %i -s %i",panel->panelNumber,panel->red,panel->green,panel->blue,65535);
			system(buffer);
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
                                                        
void populatePanels(void)
{
	FILE*	fp;
	char	buffer[1024];
	char	command[1024];
	int		cnt=0;

	fp=popen("xfconf-query  array -c xfce4-panel -p /panels","r");
	fgets(buffer,256,fp);
	fgets(buffer,256,fp);
	while(fgets(buffer,256,fp))
		{
			panelNumbers[cnt]=atoi(buffer);
			cnt++;
		}

	numOfPanels=cnt;
	pclose(fp);

	for(int j=0;j<numOfPanels;j++)
		{
			buffer[0]=0;
			panels[j]=(panelData*)malloc(sizeof(panelData));
			panels[j]->style=0;
			panels[j]->size=48;
			panels[j]->imagePath=NULL;
			panels[j]->red=56540;
			panels[j]->green=56026;
			panels[j]->blue=54741;
			panels[j]->alpha=100;

			sprintf((char*)&command,"xfconf-query  array -c xfce4-panel -p /panels/panel-%i/background-style 2>/dev/null",panelNumbers[j]);
			fp=popen(command,"r");
			fgets(buffer,1024,fp);
			pclose(fp);
			if(strlen(buffer)>0)
				panels[j]->style=atoi(buffer);

			buffer[0]=0;
			sprintf((char*)&command,"xfconf-query  array -c xfce4-panel -p /panels/panel-%i/size 2>/dev/null",panelNumbers[j]);
			fp=popen(command,"r");
			fgets(buffer,1024,fp);
			pclose(fp);
			if(strlen(buffer)>0)
				panels[j]->size=atoi(buffer);

			buffer[0]=0;
			sprintf((char*)&command,"xfconf-query  array -c xfce4-panel -p /panels/panel-%i/background-image 2>/dev/null",panelNumbers[j]);
			fp=popen(command,"r");
			fgets(buffer,1024,fp);
			pclose(fp);
			if(strlen(buffer)>0)
				{
					buffer[strlen(buffer)-1]=0;
					panels[j]->imagePath=strdup(buffer);
				}

			buffer[0]=0;
			sprintf((char*)&command,"xfconf-query  array -c xfce4-panel -p /panels/panel-%i/background-color 2>/dev/null",panelNumbers[j]);
			fp=popen(command,"r");
			fgets(buffer,1024,fp);
			if(strlen(buffer)>0)
				{
					fgets(buffer,1024,fp);

					fgets(buffer,1024,fp);
					panels[j]->red=atoi(buffer);
					fgets(buffer,1024,fp);
					panels[j]->green=atoi(buffer);
					fgets(buffer,1024,fp);
					panels[j]->blue=atoi(buffer);
				}
			pclose(fp);

			buffer[0]=0;
			sprintf((char*)&command,"xfconf-query  array -c xfce4-panel -p /panels/panel-%i/background-alpha 2>/dev/null",panelNumbers[j]);
			fp=popen(command,"r");
			fgets(buffer,1024,fp);
			pclose(fp);
			if(strlen(buffer)>0)
				panels[j]->alpha=atoi(buffer);

			panels[j]->panelNumber=panelNumbers[j];

			revertPanels[j]=(panelData*)malloc(sizeof(panelData));
			revertPanels[j]->style=panels[j]->style;
			revertPanels[j]->size=panels[j]->size;
			if(panels[j]->imagePath!=NULL)
				revertPanels[j]->imagePath=strdup(panels[j]->imagePath);
			else
				revertPanels[j]->imagePath=NULL;
			revertPanels[j]->red=panels[j]->red;
			revertPanels[j]->green=panels[j]->green;
			revertPanels[j]->blue=panels[j]->blue;
			revertPanels[j]->alpha=panels[j]->alpha;
			revertPanels[j]->panelNumber=panelNumbers[j];
		}
}

void setPanels(void)
{
	currentPanel=0;
	selectPanel((GtkComboBox*)panelSelect,NULL);

	panelChanging=false;
	for(int j=0;j<numOfPanels;j++)
		{
			currentPanel=j;
			setPanelData(false);
		}
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





