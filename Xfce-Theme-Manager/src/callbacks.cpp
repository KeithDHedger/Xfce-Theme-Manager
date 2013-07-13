/*
 *
 * K.D.Hedger 2012 <kdhedger68713@gmail.com>
 *
 *
 * callbacks.cpp
 */

#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "globals.h"
#include "gui.h"
#include "database.h"
#include "thumbnails.h"
#include "panels.h"


char		filedata[8192];
GtkWidget*	entryBox;
char*		filename;
char*		metaThemeSelected=NULL;
bool		destroy=false;
int		currentPage;

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
			freeAndSet(&currentMetaTheme,"DEADBEEF");
		}

	for (int j=THEMES;j<=WALLPAPERS;j++)
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
	char*		command;
	showGlobal=(int)gtk_toggle_button_get_active((GtkToggleButton*)widget);

	asprintf(&command,"%s %i",XMTSETSHOWSYSTEM,showGlobal);

	system(command);
	freeAndNull(&command);

	doSetConfigs();
	rerunAndUpdate(false,true);
}

void changeViewWhat(GtkWidget* widget,gpointer data)
{
	char*		command;

	switch ((long)data)
		{
			case THEMES:
				showMeta=(int)gtk_toggle_button_get_active((GtkToggleButton*)widget);
				asprintf(&command,"%s %i",XMTSETSHOWMETA,showMeta);
				break;

			case WMBORDERS:
				showDecs=(int)gtk_toggle_button_get_active((GtkToggleButton*)widget);
				asprintf(&command,"%s %i",XMTSETSHOWWMB,showDecs);
				break;

			case CONTROLS:
				showGtk=(int)gtk_toggle_button_get_active((GtkToggleButton*)widget);
				asprintf(&command,"%s %i",XMTSETSHOWGTK,showGtk);
				break;

			case ICONS:
				showIcons=(int)gtk_toggle_button_get_active((GtkToggleButton*)widget);
				asprintf(&command,"%s %i",XMTSETSHOWICONS,showIcons);
				break;

			case CURSORS:
				showCursors=(int)gtk_toggle_button_get_active((GtkToggleButton*)widget);
				asprintf(&command,"%s %i",XMTSETSHOWCURSORS,showCursors);
				break;

			case WALLPAPERS:
				showBackdrop=(int)gtk_toggle_button_get_active((GtkToggleButton*)widget);
				asprintf(&command,"%s %i",XMTSETSHOWPAPER,showBackdrop);
				break;

			case CUSTOMMETA:
				showOnlyCustom=(int)gtk_toggle_button_get_active((GtkToggleButton*)widget);
				asprintf(&command,"%s %i",XMTSETSHOWCUSTOM,showOnlyCustom);
				break;
		}
	system(command);
	freeAndNull(&command);
	rerunAndUpdate(false,true);
}

void buildCustomDBNEW(const char* chan,const char* prop,dataType type,const char* key)
{
	char*	stdout;

	getValue(chan,prop,type,&stdout);
	sprintf(filedata,"%s%s=%s\n",filedata,key,stdout);
	freeAndNull(&stdout);
}
//TOGO//
void buildCustomDB(const char* xconfline,const char* key)
{
	char*	stdout;
	gint   spawnret=0;

	g_spawn_command_line_sync(xconfline,&stdout,NULL,&spawnret,NULL);
	if (spawnret==0)
		{
			stdout[strlen(stdout)-1]=0;
			sprintf(filedata,"%s%s=%s\n",filedata,key,stdout);
			freeAndNull(&stdout);
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
	gint   		spawnret=0;

	filename=NULL;
//TOGO//
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
					buildCustomDBNEW(XSETTINGS,CONTROLTHEMEPROP,STRING,"GtkTheme");
					buildCustomDBNEW(XSETTINGS,ICONTHEMEPROP,STRING,"IconTheme");
					buildCustomDBNEW(XSETTINGS,CURSORSPROP,STRING,"CursorTheme");
					buildCustomDBNEW(XFWM,WMBORDERSPROP,STRING,"Xfwm4Theme");
					buildCustomDBNEW(XFCEDESKTOP,PAPERSPROP,STRING,"BackgroundImage");

//TOGO//
					buildCustomDB(XCONFGETLAYOUT,"TitleButtonLayout");
					buildCustomDB(XCONFGETTITLEPOS,"TitlePosition");
					buildCustomDB(XCONFGETWMFONT,"WMFont");
					buildCustomDB(XCONFGETAPPFONT,"AppFont");
					buildCustomDB(XCONFGETSTYLE,"BackdropStyle");
					buildCustomDB(XCONFGETBRIGHT,"BackdropBright");
					buildCustomDB(XCONFGETSATU,"BackdropSatu");
					buildCustomDB(XCONFGETCURSORSIZE,"CursorSize");
//panel stuff
					for(int j=0;j<numOfPanels;j++)
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
	char*	datax[]={(char*)"xfce-theme-manager",(char*)"-r",NULL};

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
	char*		command;
	int		position=gtk_combo_box_get_active((GtkComboBox*)widget);

	switch (position)
		{
			case 0:
				asprintf(&command,"%s %s",XCONFSETTITLEPOS,"left");
				break;
			case 1:
				asprintf(&command,"%s %s",XCONFSETTITLEPOS,"center");
				break;
			case 2:
				asprintf(&command,"%s %s",XCONFSETTITLEPOS,"right");
				break;
		}

	system(command);
	freeAndNull(&command);
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
	const char*	ziptype[]={".tgz",".gz",".zip",".tar",".bz2",NULL};
	const char* pictype[]={".jpg",".png",".bmp",".gif",NULL};
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
	for(int j=0;j<cnt;j++)
		{
			filename=g_filename_from_uri(array[j],NULL,NULL);
			lowername=g_ascii_strdown(filename,-1);
			for(int k=0;k<5;k++)
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
	for(int j=0;j<cnt;j++)
		{
			filename=g_filename_from_uri(array[j],NULL,NULL);
			lowername=g_ascii_strdown(filename,-1);
			for(int k=0;k<4;k++)
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
	char*	command;

	wallStyle=gtk_combo_box_get_active((GtkComboBox*)widget);
	asprintf(&command,"%s%i",XCONFSETSTYLE,wallStyle);
	system(command);
}

void previewSizeChanged(GtkWidget* widget,gpointer data)
{
	char*	command;
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
		}

	asprintf(&command,"%s%i",XMTSETPRESIZE,previewSize);
	system(command);
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

//do meta theme
void doMeta(char* metaFilename,bool update)
{
	GKeyFile*		keyfile=g_key_file_new();
	int				keycnt=14;
	char*			keydata=NULL;
	GdkModifierType	mask;
	char			buffer[64];	
	const char*		keys[]={"CursorTheme","Xfwm4Theme","IconTheme","BackgroundImage","BackdropStyle","TitleButtonLayout","TitlePosition","WMFont","AppFont","BackdropBright","BackdropSatu","GtkTheme","CursorSize","Name"};

	const char*		panelkeys[]={"PanelImage","PanelStyle","PanelSize","PanelRed","PanelGreen","PanelBlue","PanelAlpha"};
	int				panelkeycnt=7;

	GtkSettings*	settings=gtk_settings_get_default();

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
			for (int j=0;j<keycnt;j++)
				{
					keydata=g_key_file_get_string(keyfile,"Data",(char*)keys[j],NULL);
					if(keydata!=NULL)
						{
							if(update==true)
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
												setValue(XFCEDESKTOP,PAPERSPROP,STRING,keydata);
												freeAndSet(&currentWallPaper,keydata);
												break;
											case 4:
											case 5:
											case 6:
											case 7:
											case 8:
											case 9:
											case 10:
												break;
											case 11:
												setValue(XSETTINGS,CONTROLTHEMEPROP,STRING,keydata);
												freeAndSet(&currentGtkTheme,keydata);
												break;
											case 12:
												break;
											case 13:
												setValue(XTHEMER,METATHEMEPROP,STRING,keydata);
												freeAndSet(&currentMetaTheme,keydata);
												break;
										}
								}
						}
				}
			rerunAndUpdate(false,true);

			if(update==true)
				{
					for (int j=0;j<numOfPanels;j++)
						{
							sprintf((char*)&buffer,"Panel-%i",panels[j]->panelNumber);
							for(int k=0;k<panelkeycnt;k++)
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
				}
		}
	
	if(keydata!=NULL)
		g_key_file_free(keyfile);

	system("xfdesktop --reload");
}

void setPieceNew(char* filePath,const char* doCommand,bool update,long doWhat)
{
	GKeyFile*	keyfile=g_key_file_new();
	char*		command;
	char*		dataset;

	if(g_key_file_load_from_file(keyfile,filePath,G_KEY_FILE_NONE,NULL))
		{
			dataset=g_key_file_get_string(keyfile,"Data","ThemeName",NULL);

			if(dataset!=NULL)
				{
					asprintf(&command,"%s\"%s\"",doCommand,dataset);
					system(command);
					switch(doWhat)
						{
							case CONTROLS:
								if(currentGtkTheme!=NULL)
									g_free(currentGtkTheme);
								currentGtkTheme=strdup(dataset);
								break;
							case ICONS:
								if(currentIconTheme!=NULL)
									g_free(currentIconTheme);
								currentIconTheme=strdup(dataset);
								break;
							case WMBORDERS:
								if(currentWMTheme!=NULL)
									g_free(currentWMTheme);
								currentWMTheme=strdup(dataset);
								break;
							case CURSORS:
								if(currentCursorTheme!=NULL)
									g_free(currentCursorTheme);
								currentCursorTheme=strdup(dataset);
								break;
							case WALLPAPERS:
								if(currentWallPaper!=NULL)
									g_free(currentWallPaper);
								currentWallPaper=strdup(dataset);
								break;
							
						}

					freeAndNull(&command);
					freeAndNull(&dataset);
					if (update==true)
						rerunAndUpdate(false,false);
				}
		}
	g_key_file_free(keyfile);
}

void setPiece(char* filePath,const char* doCommand,bool update)
{
	GKeyFile*	keyfile=g_key_file_new();
	char*		command;
	char*		dataset;

	if(g_key_file_load_from_file(keyfile,filePath,G_KEY_FILE_NONE,NULL))
		{
			dataset=g_key_file_get_string(keyfile,"Data","ThemeName",NULL);

			if(dataset!=NULL)
				{
					asprintf(&command,"%s\"%s\"",doCommand,dataset);
					system(command);
					freeAndNull(&command);
					freeAndNull(&dataset);
					if (update==true)
						rerunAndUpdate(false,false);
				}
		}
	g_key_file_free(keyfile);
}

void themeIconCallback(GtkIconView *view,gpointer doWhat)
{
	GtkTreeModel*	model;
	GList*		selected;
	GtkTreePath*	path;
	GtkTreeIter		iter;
	char*			text;

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
				doMeta(text,true);
				break;

			case WMBORDERS:
				setPieceNew(text,XCONFSETFRAME,true,WMBORDERS);
				break;

			case CONTROLS:
				setPieceNew(text,XCONFSETCONTROLS,true,CONTROLS);
				break;

			case ICONS:
				setPieceNew(text,XCONFSETICONS,true,ICONS);
				break;

			case CURSORS:
				setPieceNew(text,XCONFSETCURSOR,true,CURSORS);
				break;

			case WALLPAPERS:
				setPieceNew(text,XCONFSETPAPER,true,WALLPAPERS);
				break;
		}
	g_free(text);
	g_list_free(selected);
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
		{
			themeIconCallback((GtkIconView *)widget,(void*)data);
		}

	gdk_window_set_cursor(gdkWindow,NULL); 

	return(TRUE);
}
                                                        
void launchCompEd(GtkWidget* window,gpointer data)
{
	system("xfce4-composite-editor");
}

void resetBright(GtkWidget* widget,gpointer data)
{
	char*		command;

	gtk_range_set_value((GtkRange*)data,0);
	asprintf(&command,"%s 0",XCONFSETBRIGHT);
	system(command);
	freeAndNull(&command);
}

gboolean setBright(GtkWidget *widget,GdkEvent *event,gpointer user_data)
{
	char*		command;
	
	gdouble val=gtk_range_get_value((GtkRange*)widget);

	asprintf(&command,"%s\"%i\"",XCONFSETBRIGHT,(int)val);
	system(command);
	freeAndNull(&command);

	return(false);
}

void resetSatu(GtkWidget* widget,gpointer data)
{
	char*		command;

	gtk_range_set_value((GtkRange*)data,1.0);
	asprintf(&command,"%s 1.0",XCONFSETSATU);
	system(command);
	freeAndNull(&command);
}

gboolean setSatu(GtkWidget *widget,GdkEvent *event,gpointer user_data)
{
	char*		command;
	char*		doublestr;

	gdouble	val=gtk_range_get_value((GtkRange*)widget);

	doublestr=doubleToStr(val);
	asprintf(&command,"%s\"%s\"",XCONFSETSATU,doublestr);
	system(command);
	freeAndNull(&command);
	freeAndNull(&doublestr);
	return(false);
}

void resetLayout(GtkWidget* widget,gpointer data)
{
	char*		command;

	gtk_entry_set_text((GtkEntry*)data,currentButtonLayout);
	asprintf(&command,"%s \"%s\"",XCONFSETLAYOUT,currentButtonLayout);
	system(command);
	freeAndNull(&command);
}

void changeLayout(GtkWidget* widget,gpointer data)
{
	char*		command;

	asprintf(&command,"%s \"%s\"",XCONFSETLAYOUT,gtk_entry_get_text((GtkEntry*)widget));
	system(command);
	freeAndNull(&command);
}

void setFont(GtkWidget* widget,gpointer data)
{
	char*		command;

	if((long)data==0)
		asprintf(&command,"%s \"%s\"",XCONFSETWMFONT,gtk_font_button_get_font_name((GtkFontButton*)widget));
	else
		asprintf(&command,"%s \"%s\"",XCONFSETAPPFONT,gtk_font_button_get_font_name((GtkFontButton*)widget));

	system(command);
	freeAndNull(&command);
}

void resetFont(GtkWidget* widget,gpointer data)
{
	char*		command;

	if((long)data==0)
		{
			asprintf(&command,"%s \"%s\"",XCONFSETWMFONT,currentWMFont);
			gtk_font_button_set_font_name((GtkFontButton*)wmFontButton,currentWMFont);
		}
	else
		{
			asprintf(&command,"%s \"%s\"",XCONFSETAPPFONT,currentAppFont);
			gtk_font_button_set_font_name((GtkFontButton*)appFontButton,currentAppFont);
		}

	system(command);
	freeAndNull(&command);
}

void setCursSize(GtkWidget* widget,gpointer data)
{
	char*		command;
	
	gdouble val=gtk_range_get_value((GtkRange*)widget);

	asprintf(&command,"%s\"%i\"",XCONFSETCURSORSIZE,(int)val);
	system(command);
	freeAndNull(&command);
}

void resetCursSize(GtkWidget* widget,gpointer data)
{
	char*		command;

	gtk_range_set_value((GtkRange*)cursorSize,16);
	asprintf(&command,"%s 16",XCONFSETCURSORSIZE);
	system(command);
	freeAndNull(&command);
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
	asprintf(&command,"%s %s",XMTSETHASH,line);
	system(command);
	g_free(command);
	return(strcmp(homeThemesHash,line));
}

