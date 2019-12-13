/*
 *
 * ©K. D. Hedger. Tue 20 Oct 15:52:37 BST 2015 keithdhedger@gmail.com

 * This file (callbacks.cpp) is part of Xfce-Theme-Manager.

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
#include <unistd.h>

#include "gui.h"
#include "database.h"
#include "thumbnails.h"
#include "panels.h"
#include "cli.h"
#include "config.h"

char		filedata[8192];
GtkWidget*	entryBox;
char*		filename;
char*		metaThemeSelected=NULL;
int		currentPage;

void themeIconCallback(GtkIconView *view,gpointer doWhat);

void doResize(GtkWindow *window,gpointer user_data)
{
	GtkAllocation	allocation;
	int			widgetWidth;
	int			maxWidgets=0;
	int			barWidth;
	GtkWidget*		scrollBar;
	int			colSize=0;

	scrollBar=gtk_scrolled_window_get_vscrollbar(previewBox[currentPage].scrollBox);
	gtk_widget_get_allocation(scrollBar,&allocation);
	barWidth=allocation.width;

	gtk_widget_get_allocation((GtkWidget*)previewBox[currentPage].scrollBox,&allocation);

	widgetWidth=allocation.width-(barWidth*3);

	maxWidgets=(int)widgetWidth/previewSize;

	if (widgetWidth > 0)
		maxWidgets=(int)widgetWidth/previewSize;
	else
		return;

	if(maxWidgets>=previewBox[currentPage].itemCnt)
		maxWidgets=previewBox[currentPage].itemCnt;

	if ((widgetWidth > 0) && (maxWidgets > 0))
		colSize=(int)widgetWidth/maxWidgets;
	else
		return;;

	gtk_icon_view_set_item_width(previewBox[currentPage].iconView,colSize);
	gtk_icon_view_set_columns(previewBox[currentPage].iconView,maxWidgets);
	gtk_icon_view_set_column_spacing(previewBox[currentPage].iconView,BORDER);

	gtk_widget_set_size_request((GtkWidget*)previewBox[currentPage].iconView,widgetWidth,-1);

}

gboolean doChangePage(GtkNotebook *notebook,gpointer arg1,guint arg2,gpointer user_data)
{
	currentPage=arg2;
	doResize((GtkWindow*)window,(void*)(long)arg2);
	return(TRUE);
}

void rerunAndUpdate(bool rebuild,bool resetmeta)
{
	GtkSettings*	settings;

	if (rebuild==true)
		rebuildDB((void*)1);

	if(resetmeta==true)
		{
			setValue(XTHEMER,METATHEMEPROP,STRING,currentMetaTheme);
		}
	else
		{
			setValue(XTHEMER,METATHEMEPROP,STRING,(void*)"DEADBEEF");
			freeAndSet(&currentMetaTheme,(char*)"DEADBEEF");
		}

	for (int j=THEMES; j<=WALLPAPERS; j++)
		{
			gtk_list_store_clear(previewBox[j].store);
		}

	buildPages();
	gtk_widget_show_all(window);

	settings=gtk_settings_get_default();
	g_object_set(settings,"gtk-theme-name",currentGtkTheme,"gtk-color-scheme","default",NULL);
}

//do config stuff
void doSetConfigs(void)
{
	gtk_widget_set_sensitive(metaCheck,showGlobal);
	gtk_widget_set_sensitive(borderCheck,showGlobal);
	gtk_widget_set_sensitive(gtkCheck,showGlobal);
	gtk_widget_set_sensitive(iconsCheck,showGlobal);
	gtk_widget_set_sensitive(paperCheck,showGlobal);
	gtk_widget_set_sensitive(cursorsCheck,showGlobal);
}

void changeView(GtkWidget* widget,gpointer data)
{
	showGlobal=(int)gtk_toggle_button_get_active((GtkToggleButton*)widget);

	setValue(XTHEMER,SHOWSYSTEMPROP,INT,(void*)(long)showGlobal);
	doSetConfigs();
	rerunAndUpdate(false,true);
}

void changeViewWhat(GtkWidget* widget,gpointer data)
{
	switch ((long)data)
		{
		case THEMES:
			showMeta=(int)gtk_toggle_button_get_active((GtkToggleButton*)widget);
			setValue(XTHEMER,SHOWMETAPROP,INT,(void*)(long)showMeta);
			break;

		case WMBORDERS:
			showDecs=(int)gtk_toggle_button_get_active((GtkToggleButton*)widget);
			setValue(XTHEMER,SHOWWMBORDERPROP,INT,(void*)(long)showMeta);
			break;

		case CONTROLS:
			showGtk=(int)gtk_toggle_button_get_active((GtkToggleButton*)widget);
			setValue(XTHEMER,SHOWGTKPROP,INT,(void*)(long)showGtk);
			break;

		case ICONS:
			showIcons=(int)gtk_toggle_button_get_active((GtkToggleButton*)widget);
			setValue(XTHEMER,SHOWICONSPROP,INT,(void*)(long)showIcons);
			break;

		case CURSORS:
			showCursors=(int)gtk_toggle_button_get_active((GtkToggleButton*)widget);
			setValue(XTHEMER,SHOWCURSORSPROP,INT,(void*)(long)showCursors);
			break;

		case WALLPAPERS:
			showBackdrop=(int)gtk_toggle_button_get_active((GtkToggleButton*)widget);
			setValue(XTHEMER,SHOWBACKDROPSPROP,INT,(void*)(long)showBackdrop);
			break;

		case CUSTOMMETA:
			showOnlyCustom=(int)gtk_toggle_button_get_active((GtkToggleButton*)widget);
			setValue(XTHEMER,SHOWCUSTOMPROP,INT,(void*)(long)showOnlyCustom);
			break;
		}
	rerunAndUpdate(false,true);
}

void buildCustomDB(const char* chan,const char* prop,dataType type,const char* key)
{
	char*	strdata=NULL;
	int		intdata;
	double	floatdata;

	switch(type)
		{
		case INT:
			getValue(chan,prop,type,&intdata);
			sprintf(filedata,"%s%s=%i\n",filedata,key,intdata);
			break;

		case STRING:
			getValue(chan,prop,type,&strdata);
			sprintf(filedata,"%s%s=%s\n",filedata,key,strdata);
			g_free(strdata);
			break;

		case FLOAT:
			getValue(chan,prop,type,&floatdata);
			sprintf(filedata,"%s%s=%f\n",filedata,key,floatdata);
			break;

		case COLOURARRAY:
			break;

		case BOOLEAN:
			break;
		}
}

void response(GtkDialog *dialog,gint response_id,gpointer user_data)
{
	switch (response_id)
		{
		case GTK_RESPONSE_OK:
			asprintf(&filename,"%s",gtk_entry_get_text((GtkEntry*)entryBox));
			break;
		case DELETETHEME:
			asprintf(&filename,"%s",gtk_entry_get_text((GtkEntry*)entryBox));
			if (filename!=NULL && strlen(filename)>0)
				{
					sprintf(generalBuffer,"%s/%s.db",customFolder,filename);
					remove(generalBuffer);
					sprintf(generalBuffer,"%s/%s.png",customFolder,filename);
					remove(generalBuffer);
					freeAndNull(&filename);
					rerunAndUpdate(true,true);
				}
			break;
		}
	gtk_widget_destroy((GtkWidget*)dialog);
}

//custom theme
void customTheme(GtkWidget* window,gpointer data)
{
	GtkWidget*	getFilename;
	GtkWidget*	content_area;
	FILE*		fd=NULL;
	char*		dbname;
	char*		gtk;
	char*		frame;
	char*		thumbfile;
	bool		flag=false;
	char*		holdgtk=currentGtkTheme;
	char		buffer[2048];
	gchar*		stdout=NULL;
	char*		customname=NULL;

	filename=NULL;

	if (cliFileName==NULL)
		{
			if (metaThemeSelected==NULL)
				{
					getValue(XFWM,WMBORDERSPROP,STRING,&stdout);
					if (strcasecmp(stdout,"DEADBEEF")!=0)
						{
							asprintf(&customname,"%s %s",stdout,_translate(CUSTOM));
							freeAndNull(&stdout);
						}
				}
			else
				{
					if(g_str_has_suffix((const gchar *)metaThemeSelected,_translate(CUSTOM)))
						asprintf(&customname,"%s",metaThemeSelected);
					else
						asprintf(&customname,"%s %s",metaThemeSelected,_translate(CUSTOM));
				}

			getFilename=gtk_dialog_new_with_buttons(_translate(ENTERNAME),NULL,GTK_DIALOG_MODAL,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,GTK_STOCK_SAVE,GTK_RESPONSE_OK,GTK_STOCK_DELETE,100,NULL);
			gtk_dialog_set_default_response((GtkDialog*)getFilename,GTK_RESPONSE_OK);
			g_signal_connect(G_OBJECT(getFilename),"response",G_CALLBACK(response),NULL);
			content_area=gtk_dialog_get_content_area(GTK_DIALOG(getFilename));

			entryBox=gtk_entry_new();
			gtk_entry_set_text((GtkEntry*)entryBox,customname);
			gtk_entry_set_activates_default((GtkEntry*)entryBox,true);
			gtk_container_add(GTK_CONTAINER(content_area),entryBox);

			gtk_widget_show  (entryBox);
			gtk_dialog_run((GtkDialog *)getFilename);
		}
	else
		filename=cliFileName;

	if (filename!=NULL && strlen(filename)>0)
		{
			getValue(XSETTINGS,CONTROLTHEMEPROP,STRING,&gtk);
			getValue(XFWM,WMBORDERSPROP,STRING,&frame);
			getValue(XSETTINGS,ICONTHEMEPROP,STRING,&iconTheme);
			getValue(XSETTINGS,CURSORSPROP,STRING,&cursorTheme);

			asprintf(&thumbfile,"%s/%s.png",customFolder,filename);

			sprintf(buffer,"%s/%s",themesArray[0],frame);
			if (!g_file_test(buffer,G_FILE_TEST_IS_DIR))
				sprintf(buffer,"%s/%s",themesArray[1],frame);

			g_mkdir_with_parents(customFolder,493);
			asprintf(&dbname,"%s/%s.db",customFolder,filename);
			fd=fopen(dbname,"w");
			if(fd!=NULL)
				{
					sprintf(filedata,"[Data]\nName=%s\nThumbnail=%s\n",filename,thumbfile);
					buildCustomDB(XSETTINGS,CONTROLTHEMEPROP,STRING,"GtkTheme");
					buildCustomDB(XSETTINGS,ICONTHEMEPROP,STRING,"IconTheme");
					buildCustomDB(XSETTINGS,CURSORSPROP,STRING,"CursorTheme");
					buildCustomDB(XFWM,WMBORDERSPROP,STRING,"Xfwm4Theme");

					buildCustomDB(XFWM,BUTTONLAYOUTPROP,STRING,"TitleButtonLayout");
					buildCustomDB(XFWM,TITLEALIGNPROP,STRING,"TitlePosition");
					buildCustomDB(XFWM,WMFONTPROP,STRING,"WMFont");
					buildCustomDB(XSETTINGS,APPFONTPROP,STRING,"AppFont");

					buildCustomDB(XSETTINGS,CURSORSIZEPROP,INT,"CursorSize");

//backdrop stuff
					for(int j=0; j<numberOfMonitors; j++)
						{
							sprintf(filedata,"%s[Monitor-%i]\n",filedata,j);
							sprintf(filedata,"%sBackgroundImage=%s\n",filedata,monitorData[j]->imagePath);
							sprintf(filedata,"%sBackdropStyle=%i\n",filedata,monitorData[j]->style);
							sprintf(filedata,"%sBackdropBright=%i\n",filedata,monitorData[j]->brightness);
							sprintf(filedata,"%sBackdropSatu=%f\n",filedata,monitorData[j]->satu);
						}

//panel stuff
					for(int j=0; j<numOfPanels; j++)
						{
							sprintf(filedata,"%s[Panel-%i]\n",filedata,panels[j]->panelNumber);
							sprintf(filedata,"%sPanelImage=%s\n",filedata,panels[j]->imagePath);
							sprintf(filedata,"%sPanelStyle=%i\n",filedata,panels[j]->style);
							sprintf(filedata,"%sPanelSize=%i\n",filedata,panels[j]->size);
							sprintf(filedata,"%sPanelAlpha=%i\n",filedata,panels[j]->alpha);
							sprintf(filedata,"%sPanelRed=%i\n",filedata,panels[j]->red);
							sprintf(filedata,"%sPanelGreen=%i\n",filedata,panels[j]->green);
							sprintf(filedata,"%sPanelBlue=%i\n",filedata,panels[j]->blue);
						}
					fprintf(fd,"%s\n",filedata);
					fclose(fd);

					controlWidth=400;
					controlHeight=200;
					currentGtkTheme=gtk;
					controlsPixbuf=create_gtk_theme_pixbuf(gtk);
					currentGtkTheme=holdgtk;

					if(controlsPixbuf!=NULL)
						{
							getspace(buffer);
							makeborder(buffer,thumbfile);
							g_object_unref(controlsPixbuf);
							controlsPixbuf=NULL;
							controlWidth=200;
							controlHeight=50;
						}
					flag=true;
					setValue(XTHEMER,METATHEMEPROP,STRING,filename);
					freeAndSet(&currentMetaTheme,filename);
				}

			freeAndNull(&dbname);

			if (cliFileName==NULL)
				freeAndNull(&filename);
			freeAndNull(&gtk);
			freeAndNull(&frame);
			freeAndNull(&iconTheme);
			freeAndNull(&cursorTheme);
			freeAndNull(&thumbfile);
		}

	freeAndNull(&customname);

	if ((flag==true) && (cliFileName==NULL))
		rerunAndUpdate(true,true);
}

//rebuild db
void rerunAndBuild(GtkWidget* window,gpointer data)
{
	char*	datax[]= {(char*)"xfce-theme-manager",(char*)"-r",NULL};

	gtk_main_quit();
	execvp("xfce-theme-manager",datax);
}

//information!
void infoDialog(const char* message,char* filename,GtkMessageType type)
{
	GtkWidget*	dialog=gtk_message_dialog_new((GtkWindow*)window,GTK_DIALOG_DESTROY_WITH_PARENT,type,GTK_BUTTONS_CLOSE,"%s - %s",message,filename);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}

//set title position
void setTitlePos(GtkComboBoxText* widget,gpointer data)
{
	int			position=gtk_combo_box_get_active((GtkComboBox*)widget);

	switch (position)
		{
		case 0:
			setValue(XFWM,TITLEALIGNPROP,STRING,(void*)"left");
			break;
		case 1:
			setValue(XFWM,TITLEALIGNPROP,STRING,(void*)"center");
			break;
		case 2:
			setValue(XFWM,TITLEALIGNPROP,STRING,(void*)"right");
			break;
		}
}

int installWallpaper(char* filename)
{
	char*		command;
	int		retval=-1;

	asprintf(&command,"cp \"%s\" \"%s\"",filename,papersArray[0]);
	retval=system(command);

	if(retval==0)
		infoDialog("Installed",filename,GTK_MESSAGE_INFO);
	else
		infoDialog("Can't Install",filename,GTK_MESSAGE_ERROR);

	freeAndNull(&command);
	return(retval);
}

int extractAndInstall(char* filename,int ziptype)
{
	gchar*	stdout=NULL;
	gchar*	stderr=NULL;
	int		retval=-1;
	gint	spawnret=-1;
	char*	commandtest;
	char*	commandextracttheme;
	char*	commandextracticon;

	if(ziptype==2)
		{
			asprintf(&commandtest,"unzip -t");
			asprintf(&commandextracttheme,"unzip -od %s ",themesArray[0]);
			asprintf(&commandextracticon,"unzip -od %s ",iconsArray[0]);
		}
	else
		{
			asprintf(&commandtest,"tar --wildcards -tf");
			asprintf(&commandextracttheme,"tar -C %s -xf ",themesArray[0]);
			asprintf(&commandextracticon,"tar -C %s -xf ",iconsArray[0]);
		}

	while(true)
		{
			sprintf(generalBuffer,"%s \"%s\" */gtkrc",commandtest,filename);
			g_spawn_command_line_sync((char*)generalBuffer,&stdout,&stderr,&spawnret,NULL);
			if (spawnret==0)
				{
					stdout[strlen(stdout)-1]=0;
					if(strlen(stdout)>1)
						{
							sprintf(generalBuffer,"%s \"%s\"",commandextracttheme,filename);
							retval=system(generalBuffer);
							freeAndNull(&stdout);
							break;
						}
					freeAndNull(&stdout);
				}

			sprintf(generalBuffer,"%s \"%s\" */themerc",commandtest,filename);
			g_spawn_command_line_sync((char*)generalBuffer,&stdout,&stderr,&spawnret,NULL);
			if (spawnret==0)
				{
					stdout[strlen(stdout)-1]=0;
					if(strlen(stdout)>1)
						{
							sprintf(generalBuffer,"%s \"%s\"",commandextracttheme,filename);
							retval=system(generalBuffer);
							freeAndNull(&stdout);
							freeAndNull(&stderr);
							break;
						}
					freeAndNull(&stdout);
					freeAndNull(&stderr);
				}

			sprintf(generalBuffer,"%s \"%s\" */index.theme",commandtest,filename);
			g_spawn_command_line_sync((char*)generalBuffer,&stdout,&stderr,&spawnret,NULL);
			if (spawnret==0)
				{
					stdout[strlen(stdout)-1]=0;
					if(strlen(stdout)>1)
						{
							sprintf(generalBuffer,"%s \"%s\"",commandextracticon,filename);
							retval=system(generalBuffer);
							freeAndNull(&stdout);
							freeAndNull(&stderr);
							break;
						}
					freeAndNull(&stdout);
					freeAndNull(&stderr);
				}
			break;
		}

	if(retval!=0)
		infoDialog("Can't Install",filename,GTK_MESSAGE_ERROR);

	freeAndNull(&stdout);

	return(retval);
}

//dnd install
void dropUri(GtkWidget *widget,GdkDragContext *context,gint x,gint y,GtkSelectionData *selection_data,guint info,guint32 time,gpointer user_data)
{
	gchar**	array=gtk_selection_data_get_uris(selection_data);
	int		cnt=g_strv_length(array);
	char*		filename;
	const char*	ziptype[]= {".tgz",".gz",".zip",".tar",".bz2",NULL};
	const char* pictype[]= {".jpg",".png",".bmp",".gif",NULL};
	int		doupdate=1;
	int doneinstalls=0;

	gchar*	lowername=NULL;

//make sure folders are there
//themes
	sprintf(generalBuffer,"mkdir -p %s/.themes",homeFolder);
	system(generalBuffer);
//icons etc
	sprintf(generalBuffer,"mkdir -p %s/.icons",homeFolder);
	system(generalBuffer);
//pics
	sprintf(generalBuffer,"mkdir -p %s/.local/share/xfce4/backdrops",homeFolder);
	system(generalBuffer);

//themes
	for(int j=0; j<cnt; j++)
		{
			filename=g_filename_from_uri(array[j],NULL,NULL);
			lowername=g_ascii_strdown(filename,-1);
			for(int k=0; k<5; k++)
				{
					if(g_str_has_suffix(lowername,ziptype[k]))
						{
							doupdate=extractAndInstall(filename,k);
							if (doupdate==0)
								doneinstalls++;
							break;
						}
				}
			freeAndNull(&filename);
			freeAndNull(&lowername);
		}

//pics
	for(int j=0; j<cnt; j++)
		{
			filename=g_filename_from_uri(array[j],NULL,NULL);
			lowername=g_ascii_strdown(filename,-1);
			for(int k=0; k<4; k++)
				{
					if(g_str_has_suffix(lowername,pictype[k]))
						{
							doupdate=installWallpaper(filename);
							break;
							if (doupdate==0)
								doneinstalls++;
						}
				}
			freeAndNull(&filename);
			freeAndNull(&lowername);
		}

	if(doneinstalls>1)
		infoDialog("Installed",(char*)"Multiple Theme Archives",GTK_MESSAGE_INFO);

	if(doneinstalls==1)
		{
			filename=g_filename_from_uri(array[0],NULL,NULL);
			infoDialog("Installed",filename,GTK_MESSAGE_INFO);
			freeAndNull(&filename);
		}

	g_strfreev(array);

	if(doupdate==0)
		rerunAndUpdate(true,true);
}

void wallStyleChanged(GtkWidget* widget,gpointer data)
{
	monitorData[currentMonitor]->style=gtk_combo_box_get_active((GtkComboBox*)widget);
#ifdef _411_
	sprintf((char*)&generalBuffer[0],"%s%s/workspace0/image-style",MONITORPROP,monitorData[currentMonitor]->name);
#else
	sprintf((char*)&generalBuffer[0],"%s%i/image-style",MONITORPROP,currentMonitor);
#endif
	setValue(XFCEDESKTOP,(char*)&generalBuffer[0],INT,(void*)(long)monitorData[currentMonitor]->style);
}

void previewSizeChanged(GtkWidget* widget,gpointer data)
{
	int index=-1;

	index=gtk_combo_box_get_active((GtkComboBox*)widget);
	switch(index)
		{
		case 0:
			previewSize=256;
			break;

		case 1:
			previewSize=128;
			break;

		case 2:
			previewSize=64;
			break;

		case 3:
			previewSize=48;
			break;
		case -1:
			return;
			break;
		}
	setValue(XTHEMER,PREVSIZEPROP,INT,(void*)(long)previewSize);
	rerunAndUpdate(false,true);
}

void removeTheme(const char* name)
{
	int		namelen;
	GtkWidget*	dialog;

	if(strstr(name,".config/XfceThemeManager/custom")==NULL)
		return;

	dialog=gtk_message_dialog_new(NULL,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_WARNING,GTK_BUTTONS_YES_NO,"%s:\n%s",_translate(REMOVETHEME),name);

	if(gtk_dialog_run (GTK_DIALOG(dialog))==GTK_RESPONSE_YES)
		{
			namelen=strlen(name);
			sprintf(generalBuffer,"%s",name);
			remove(name);
			generalBuffer[namelen-2]='p';
			generalBuffer[namelen-1]='n';
			generalBuffer[namelen]='g';
			generalBuffer[namelen+1]=0;
			remove(generalBuffer);
			rerunAndUpdate(true,true);
		}

	gtk_widget_destroy (dialog);
}

gboolean mouseMove(GtkWidget* widget,GdkEvent* event,gpointer user_data)
{
	GtkTreePath* path=NULL;

	path=gtk_icon_view_get_path_at_pos((GtkIconView *)widget,event->button.x,event->button.y);
	if (path!=NULL)
		gtk_icon_view_select_path((GtkIconView *)widget,path);
	else
		gtk_icon_view_unselect_all((GtkIconView*)widget);

	return(FALSE);
}

gboolean clickIt(GtkWidget* widget,GdkEvent* event,gpointer data)
{
	GtkTreePath* path=NULL;

	gdk_window_set_cursor (gdkWindow,watchCursor);

	path=gtk_icon_view_get_path_at_pos((GtkIconView *)widget,event->button.x,event->button.y);
	if (path!=NULL)
		themeIconCallback((GtkIconView *)widget,(void*)data);

	gdk_window_set_cursor(gdkWindow,NULL);

	return(TRUE);
}

bool fromSetMonitor=false;

void monitorChanged(GtkWidget* widget,gpointer data)
{
	if(initing==true)
		return;

	if(fromSetMonitor==true)
		{
			currentMonitor=0;
			gtk_combo_box_set_active((GtkComboBox*)screenNumber,0);
		}
	else
		currentMonitor=gtk_combo_box_get_active((GtkComboBox*)widget);
	gtk_combo_box_set_active((GtkComboBox*)styleComboBox,monitorData[currentMonitor]->style);
	gtk_range_set_value((GtkRange*)briteRange,monitorData[currentMonitor]->brightness);
	gtk_range_set_value((GtkRange*)satuRange,monitorData[currentMonitor]->satu);

	previewBox[WALLPAPERS].itemCnt=0;
	freeIter(WALLPAPERS);
	gtk_list_store_clear(previewBox[WALLPAPERS].store);

	addNewIcons(folders[WALLPAPERS],previewBox[WALLPAPERS].iconView,WALLPAPERS);

	g_signal_connect(G_OBJECT(previewBox[WALLPAPERS].iconView),"motion-notify-event",G_CALLBACK(mouseMove),NULL);
	g_signal_connect(G_OBJECT(previewBox[WALLPAPERS].iconView),"button-press-event",G_CALLBACK(clickIt),(void*)(long)WALLPAPERS);

	scrollToCurrent(WALLPAPERS);
}

void setMonitorData(void)
{
	for(int i=0; i<numberOfMonitors; i++)
		{
#ifdef _411_
			sprintf((char*)&generalBuffer[0],"%s%s/workspace0/image-style",MONITORPROP,monitorData[i]->name);
#else
			sprintf((char*)&generalBuffer[0],"%s%i/image-style",MONITORPROP,i);
#endif
			setValue(XFCEDESKTOP,(char*)&generalBuffer[0],INT,(void*)(long)monitorData[i]->style);

			sprintf((char*)&generalBuffer[0],"%s%i/brightness",MONITORPROP,i);
			setValue(XFCEDESKTOP,(char*)&generalBuffer[0],INT,(void*)(long)monitorData[i]->brightness);

			sprintf((char*)&generalBuffer[0],"%s%i/saturation",MONITORPROP,i);
			setValue(XFCEDESKTOP,(char*)&generalBuffer[0],FLOAT,&monitorData[i]->satu);

#ifdef _411_
			sprintf((char*)&generalBuffer[0],"%s%s/workspace0/last-image",MONITORPROP,monitorData[i]->name);
#else
			sprintf((char*)&generalBuffer[0],"%s%i/image-path",MONITORPROP,i);
#endif
			setValue(XFCEDESKTOP,(char*)&generalBuffer[0],STRING,monitorData[i]->imagePath);
		}

	currentMonitor=0;
	gtk_combo_box_set_active((GtkComboBox*)styleComboBox,monitorData[currentMonitor]->style);
	gtk_range_set_value((GtkRange*)briteRange,monitorData[currentMonitor]->brightness);
	gtk_range_set_value((GtkRange*)satuRange,monitorData[currentMonitor]->satu);

	fromSetMonitor=true;
	monitorChanged(NULL,NULL);
	fromSetMonitor=false;

}

//do meta theme
void doMeta(char* metaFilename)
{
	GKeyFile*		keyfile=g_key_file_new();
	int				keycnt=10;
	char*			keydata=NULL;
	GdkModifierType	mask;
	char			buffer[64];
	const char*		keys[]= {"CursorTheme","Xfwm4Theme","IconTheme","TitleButtonLayout","TitlePosition","WMFont","AppFont","GtkTheme","CursorSize","Name"};

	const char*		panelkeys[]= {"PanelImage","PanelStyle","PanelSize","PanelRed","PanelGreen","PanelBlue","PanelAlpha"};
	int				panelkeycnt=7;

	const char*		monitorkeys[]= {"BackgroundImage","BackdropStyle","BackdropBright","BackdropSatu"};
	int				monitorkeycnt=4;

	gdk_window_get_pointer(NULL,NULL,NULL,&mask);
	if (GDK_CONTROL_MASK & mask )
		{
			removeTheme(metaFilename);
			return;
		}
	if(g_key_file_load_from_file(keyfile,metaFilename,G_KEY_FILE_NONE,NULL))
		{
			metaThemeSelected=g_key_file_get_string(keyfile,"Data",(char*)"Name",NULL);
			setValue(XTHEMER,METATHEMEPROP,STRING,metaThemeSelected);
			freeAndSet(&currentMetaTheme,metaThemeSelected);
			for (int j=0; j<keycnt; j++)
				{
					keydata=g_key_file_get_string(keyfile,"Data",(char*)keys[j],NULL);
					if(keydata!=NULL)
						{
							switch(j)
								{
								case 0:
									setValue(XSETTINGS,CURSORSPROP,STRING,keydata);
									freeAndSet(&currentCursorTheme,keydata);
									break;
								case 1:
									setValue(XFWM,WMBORDERSPROP,STRING,keydata);
									freeAndSet(&currentWMTheme,keydata);
									break;
								case 2:
									setValue(XSETTINGS,ICONTHEMEPROP,STRING,keydata);
									freeAndSet(&currentIconTheme,keydata);
									break;
								case 3:
									setValue(XFWM,BUTTONLAYOUTPROP,STRING,(void*)keydata);
									gtk_entry_set_text((GtkEntry*)layoutEntry,keydata);
									break;
								case 4:
									setValue(XFWM,TITLEALIGNPROP,STRING,(void*)keydata);
									gtk_combo_box_set_active((GtkComboBox*)titlePos,positionToInt(keydata));
									break;
								case 5:
									setValue(XFWM,WMFONTPROP,STRING,(void*)keydata);
									gtk_font_button_set_font_name((GtkFontButton*)wmFontButton,keydata);
									break;
								case 6:
									setValue(XSETTINGS,APPFONTPROP,STRING,(void*)keydata);
									gtk_font_button_set_font_name((GtkFontButton*)appFontButton,keydata);
									break;
								case 7:
									setValue(XSETTINGS,CONTROLTHEMEPROP,STRING,keydata);
									freeAndSet(&currentGtkTheme,keydata);
									break;
								case 8:
									setValue(XSETTINGS,CURSORSIZEPROP,INT,(void*)(long)atol(keydata));
									gtk_range_set_value((GtkRange*)cursorSize,atol(keydata));
									break;
								case 9:
									setValue(XTHEMER,METATHEMEPROP,STRING,keydata);
									freeAndSet(&currentMetaTheme,keydata);
									break;
								}
						}
				}
			rerunAndUpdate(false,true);

			for (int j=0; j<numOfPanels; j++)
				{
					sprintf((char*)&buffer,"Panel-%i",panels[j]->panelNumber);
					for(int k=0; k<panelkeycnt; k++)
						{
							keydata=g_key_file_get_string(keyfile,buffer,(char*)panelkeys[k],NULL);
							if(keydata!=NULL)
								{
									switch(k)
										{
										case 0:
											freeAndSet(&panels[j]->imagePath,keydata);
											break;
										case 1:
											panels[j]->style=atoi(keydata);
											break;
										case 2:
											panels[j]->size=atoi(keydata);
											break;
										case 3:
											panels[j]->red=atoi(keydata);
											break;
										case 4:
											panels[j]->green=atoi(keydata);
											break;
										case 5:
											panels[j]->blue=atoi(keydata);
											break;
										case 6:
											panels[j]->alpha=atoi(keydata);
											break;
										}
									freeAndNull(&keydata);
								}
						}
				}
			setPanels();

			for(int j=0; j<numberOfMonitors; j++)
				{
					sprintf((char*)&buffer,"Monitor-%i",j);
					for(int k=0; k<monitorkeycnt; k++)
						{
							keydata=g_key_file_get_string(keyfile,buffer,(char*)monitorkeys[k],NULL);
							if(keydata!=NULL)
								{
									switch(k)
										{
										case 0:
											freeAndSet(&monitorData[j]->imagePath,keydata);
											break;
										case 1:
											monitorData[j]->style=atoi(keydata);
#ifdef _411_
											if(monitorData[j]->style==0)
												monitorData[j]->style=3;
#endif

											break;
										case 2:
											monitorData[j]->brightness=atoi(keydata);
											break;
										case 3:
											monitorData[j]->satu=atof(keydata);
											break;
										}
									freeAndNull(&keydata);
								}
						}
				}
			setMonitorData();
		}

	if(keydata!=NULL)
		g_key_file_free(keyfile);

	system("xfdesktop --reload");
}

void setPieceNewNew(const char* filePath,long doWhat)
{
	GKeyFile*	keyfile=g_key_file_new();
	char*		dataset;

	if(g_key_file_load_from_file(keyfile,filePath,G_KEY_FILE_NONE,NULL))
		{
			dataset=g_key_file_get_string(keyfile,"Data","ThemeName",NULL);
			if(dataset!=NULL)
				{
					switch(doWhat)
						{
						case WMBORDERS:
							setValue(XFWM,WMBORDERSPROP,STRING,dataset);
							freeAndSet(&currentWMTheme,dataset);
							break;
						case CONTROLS:
							setValue(XSETTINGS,CONTROLTHEMEPROP,STRING,dataset);
							freeAndSet(&currentGtkTheme,dataset);
							break;
						case ICONS:
							setValue(XSETTINGS,ICONTHEMEPROP,STRING,dataset);
							freeAndSet(&currentIconTheme,dataset);
							break;
						case CURSORS:
							setValue(XSETTINGS,CURSORSPROP,STRING,dataset);
							freeAndSet(&currentCursorTheme,dataset);
							break;
						case WALLPAPERS:
#ifdef _411_
							setValue(XFCEDESKTOP,(char*)"/backdrop/single-workspace-mode",BOOLEAN,(void*)true);
							setValue(XFCEDESKTOP,(char*)"/backdrop/single-workspace-number",INT,(void*)0);
							sprintf((char*)&generalBuffer[0],"%s%s/workspace0/last-image",MONITORPROP,monitorData[currentMonitor]->name);
#else
							sprintf((char*)&generalBuffer[0],"%s%i/image-path",MONITORPROP,currentMonitor);
#endif
							setValue(XFCEDESKTOP,(char*)&generalBuffer[0],STRING,dataset);
							freeAndSet(&monitorData[currentMonitor]->imagePath,dataset);
							break;
						}
				}
		}
	rerunAndUpdate(false,false);
	if(keyfile!=NULL)
		g_key_file_free(keyfile);
}

void themeIconCallback(GtkIconView *view,gpointer doWhat)
{
	GtkTreeModel*	model;
	GList*		selected;
	GtkTreePath*	path;
	GtkTreeIter		iter;
	char*			text;
	char			*script;
	GdkEventClient	event;

	selected=gtk_icon_view_get_selected_items(view);
	if (!selected)
		return;

	model=gtk_icon_view_get_model(view);
	path=(GtkTreePath *)selected->data;
	gtk_tree_model_get_iter(model,&iter,path);
	gtk_tree_path_free(path);

	gtk_tree_model_get(model,&iter,FILE_NAME,&text,-1);

	switch((long)doWhat)
		{
		case THEMES:
			doMeta(text);
			asprintf(&script,"%s/Scripts/XfceMetaScript \"%s\"",getenv("HOME"),text);
			break;

		case WMBORDERS:
			setPieceNewNew(text,WMBORDERS);
			asprintf(&script,"%s/Scripts/XfceWMScript set \"%s\"",getenv("HOME"),text);
			break;

		case CONTROLS:
			setPieceNewNew(text,CONTROLS);
			asprintf(&script,"%s/Scripts/XfceControlsScript set \"%s\"",getenv("HOME"),text);
			break;

		case ICONS:
			setPieceNewNew(text,ICONS);
			asprintf(&script,"%s/Scripts/XfceIconsScript set \"%s\"",getenv("HOME"),text);
			break;

		case CURSORS:
			setPieceNewNew(text,CURSORS);
			asprintf(&script,"%s/Scripts/XfceCursorScript set \"%s\"",getenv("HOME"),text);
			break;

		case WALLPAPERS:
			setPieceNewNew(text,WALLPAPERS);
			{
				char	mname[4096]= {0,};
				char	*ptr=&mname[0];
				int		cnt=0;
				for(int j=0; j<numberOfMonitors; j++)
					{
						cnt=sprintf(ptr,"%i ",monitorData[j]->style);
						ptr+=cnt;
						cnt=sprintf(ptr,"\"%s\" ",monitorData[j]->imagePath);
						ptr+=cnt;
					}
				asprintf(&script,"%s/Scripts/XfceBackdropScript %i %s",getenv("HOME"),spanMonitors,mname);
			}
			break;
		}

	system(script);
	free(script);

	g_free(text);
	g_list_free(selected);

	event.type=GDK_CLIENT_EVENT;
	event.send_event=TRUE;
	event.window=NULL;
	event.message_type=gdk_atom_intern("_GTK_READ_RCFILES",FALSE);
	event.data_format=8;
	gdk_event_send_clientmessage_toall((GdkEvent *)&event);
}

void launchCompEd(GtkWidget* window,gpointer data)
{
	if(data==NULL)
		system("xfce4-composite-editor");
	else
		system("xdg-open http://khapplications.freeddns.org/pages/apps.html#xfcecomp");
}

void resetBright(GtkWidget* widget,gpointer data)
{
	gtk_range_set_value((GtkRange*)data,0);
	monitorData[currentMonitor]->brightness=0;

	sprintf((char*)&generalBuffer[0],"%s%i/brightness",MONITORPROP,currentMonitor);
	setValue(XFCEDESKTOP,(char*)&generalBuffer[0],INT,(void*)0);
}

gboolean setBright(GtkWidget *widget,GdkEvent *event,gpointer user_data)
{
	gdouble val=gtk_range_get_value((GtkRange*)widget);
	monitorData[currentMonitor]->brightness=val;

	sprintf((char*)&generalBuffer[0],"%s%i/brightness",MONITORPROP,currentMonitor);
	setValue(XFCEDESKTOP,(char*)&generalBuffer[0],INT,(void*)(long)monitorData[currentMonitor]->brightness);

	return(false);
}

void resetSatu(GtkWidget* widget,gpointer data)
{
	double	d=1.0;

	monitorData[currentMonitor]->satu=d;
	gtk_range_set_value((GtkRange*)data,1.0);

	sprintf((char*)&generalBuffer[0],"%s%i/saturation",MONITORPROP,currentMonitor);
	setValue(XFCEDESKTOP,(char*)&generalBuffer[0],FLOAT,&monitorData[currentMonitor]->satu);
}

gboolean setSatu(GtkWidget *widget,GdkEvent *event,gpointer user_data)
{
	gdouble	val=gtk_range_get_value((GtkRange*)widget);
	monitorData[currentMonitor]->satu=val;
	sprintf((char*)&generalBuffer[0],"%s%i/saturation",MONITORPROP,currentMonitor);
	setValue(XFCEDESKTOP,(char*)&generalBuffer[0],FLOAT,&monitorData[currentMonitor]->satu);

	return(false);
}

void setSpanMonitors(GtkWidget* widget,gpointer data)
{
	long val=(int)gtk_toggle_button_get_active((GtkToggleButton*)widget);
	//sprintf((char*)&generalBuffer[0],"%s",SCREENPROP);
	setValue(XFCEDESKTOP,SCREENPROP,BOOLEAN,(void*)val);
	spanMonitors=val;
}

void resetLayout(GtkWidget* widget,gpointer data)
{
	gtk_entry_set_text((GtkEntry*)data,"O|SHMC");
	setValue(XFWM,BUTTONLAYOUTPROP,STRING,(void*)"O|SHMC");
}

void changeLayout(GtkWidget* widget,gpointer data)
{
	if(strcasecmp(gtk_entry_get_text((GtkEntry*)widget),"")==0)
		{
			setValue(XFWM,BUTTONLAYOUTPROP,STRING,(void*)"|");
			gtk_entry_set_text((GtkEntry*)widget,"|");
		}
	else
		setValue(XFWM,BUTTONLAYOUTPROP,STRING,(void*)gtk_entry_get_text((GtkEntry*)widget));
}

void setFont(GtkWidget* widget,gpointer data)
{
	if((long)data==0)
		setValue(XFWM,WMFONTPROP,STRING,(void*)gtk_font_button_get_font_name((GtkFontButton*)widget));
	else
		setValue(XSETTINGS,APPFONTPROP,STRING,(void*)gtk_font_button_get_font_name((GtkFontButton*)widget));
}

void resetFont(GtkWidget* widget,gpointer data)
{
	if((long)data==0)
		{
			gtk_font_button_set_font_name((GtkFontButton*)wmFontButton,"Sans 10");
			setValue(XFWM,WMFONTPROP,STRING,(void*)"Sans 10");
		}
	else
		{
			gtk_font_button_set_font_name((GtkFontButton*)appFontButton,"Sans 10");
			setValue(XSETTINGS,APPFONTPROP,STRING,(void*)"Sans 10");
		}
}

void setCursSize(GtkWidget* widget,gpointer data)
{
	gdouble val=gtk_range_get_value((GtkRange*)widget);
	setValue(XSETTINGS,CURSORSIZEPROP,INT,(void*)(long)val);
}

void resetCursSize(GtkWidget* widget,gpointer data)
{
	gtk_range_set_value((GtkRange*)cursorSize,16);
	setValue(XSETTINGS,CURSORSIZEPROP,INT,(void*)16);
}

int checkFolders(void)
{
	char*	command;
	FILE*	fp;
	char	line[256];

	asprintf(&command,"find -L %s %s %s %s %s %s -maxdepth 2 2>/dev/null|md5sum | awk '{print $1}'",themesArray[0],themesArray[1],iconsArray[0],iconsArray[1],papersArray[0],papersArray[1]);

	fp=popen(command,"r");
	fgets(line,256,fp);
	pclose(fp);
	g_free(command);

	line[strlen(line)-1]=0;
	setValue(XTHEMER,HASHPROP,STRING,(void*)line);

	return(strcmp(homeThemesHash,line));
}






