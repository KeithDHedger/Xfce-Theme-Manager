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

#include "globals.h"
#include "gui.h"
#include "database.h"
#include "thumbnails.h"


char		filedata[1024];
GtkWidget*	entryBox;
char*		filename;
char*		metaThemeSelected=NULL;
bool		destroy=false;
//GtkTreePath* holdPath=NULL;
//gtk_icon_view_scroll_to_path((GtkIconView *)view,path,FALSE,0,0);
//update gui
#if 1
void doResizeX(GtkWindow *window,gpointer user_data)
{
	GtkAllocation	allocation;
	int			widgetWidth;
	int			maxWidgets=0;
	int			barWidth;
	GtkWidget*		scrollBar;
	int			colSize;
//	GtkWidget*		icon_view;

	for (int j=0;j<1;j++)
		{
			scrollBar=gtk_scrolled_window_get_vscrollbar((GtkScrolledWindow *)previewBoxes[j][SCROLLBOX]);

			gtk_widget_get_allocation(scrollBar,&allocation);
			barWidth=allocation.width;
			gtk_widget_get_allocation(previewBoxes[j][SCROLLBOX],&allocation);
			widgetWidth=allocation.width-barWidth;

			maxWidgets=widgetWidth/previewSize;

		//	if(maxWidgets>8)
		//		maxWidgets=8;

			colSize=(widgetWidth/maxWidgets);

			gtk_icon_view_set_item_width((GtkIconView *)previewBoxes[j][ICONVIEW],colSize);
			gtk_icon_view_set_columns((GtkIconView *)previewBoxes[j][ICONVIEW],maxWidgets);
			gtk_icon_view_set_column_spacing((GtkIconView *)previewBoxes[j][ICONVIEW],0);
			gtk_icon_view_set_item_padding((GtkIconView *)previewBoxes[j][ICONVIEW],0);
			gtk_widget_set_size_request((GtkWidget *)previewBoxes[j][ICONVIEW],widgetWidth,-1);
		}
}
#endif

void doResize(GtkWindow *window,gpointer user_data)
{
	GtkAllocation	allocation;
	int			widgetWidth;
	int			maxWidgets=0;
	int			barWidth;
	GtkWidget*		scrollBar;
	int			colSize;

	for (int j=0;j<1;j++)
		{
			scrollBar=gtk_scrolled_window_get_vscrollbar(previewBox[THEMES].scrollBox);

			gtk_widget_get_allocation(scrollBar,&allocation);
			//allocation.width=0;
			//if (allocation.width>0)
			barWidth=allocation.width;
			//else
			//	barWidth=0;

			gtk_widget_get_allocation((GtkWidget*)previewBox[THEMES].hBox,&allocation);
			//allocation.width=0;
			widgetWidth=allocation.width-(barWidth*2);

			maxWidgets=widgetWidth/previewSize;

			if(maxWidgets>=previewBox[THEMES].itemCnt)
				maxWidgets=previewBox[THEMES].itemCnt;

			colSize=(widgetWidth/maxWidgets);

			gtk_icon_view_set_item_width(previewBox[THEMES].iconView,colSize);
			gtk_icon_view_set_columns(previewBox[THEMES].iconView,maxWidgets);
			gtk_icon_view_set_column_spacing(previewBox[THEMES].iconView,0);
			gtk_icon_view_set_item_padding(previewBox[THEMES].iconView,0);
			gtk_widget_set_size_request((GtkWidget*)previewBox[THEMES].iconView,widgetWidth,-1);
			gtk_window_get_size(window,&previewBox[THEMES].width,NULL);
		}
}

void rerunAndUpdate(bool rebuild,bool resetmeta)
{
	if (rebuild==true)
		rebuildDB((void*)1);

	setValue(XCONFGETCONTROLS,STRING,&lastGtkTheme);
	setValue(XCONFGETICONS,STRING,&lastIconTheme);
	setValue(XCONFGETFRAME,STRING,&lastWmTheme);
	setValue(XCONFGETPAPER,STRING,&lastWallPaper);
	setValue(XCONFGETCURSOR,STRING,&lastCursorTheme);
	if(resetmeta==true)
		setValue(XMTGETMETATHEME,STRING,&lastMetaTheme);
	else
		{
			freeAndNull(&lastMetaTheme);
			asprintf(&lastMetaTheme,"DEADBEEFANDOXO");
			sprintf(generalBuffer,"%s\"\"",XMTSETMETATHEME);
			system(generalBuffer);
		}

	gtk_widget_destroy((GtkWidget*)previewBox[THEMES].scrollBox);
	gtk_widget_destroy((GtkWidget*)previewBox[WMBORDERS].scrollBox);
	gtk_widget_destroy((GtkWidget*)previewBox[CONTROLS].scrollBox);
	gtk_widget_destroy((GtkWidget*)previewBox[ICONS].scrollBox);
	gtk_widget_destroy((GtkWidget*)previewBox[CURSORS].scrollBox);
	gtk_widget_destroy((GtkWidget*)previewBox[WALLPAPERS].scrollBox);

	buildPages();

	gtk_widget_show_all(window);
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
	filename=NULL;
	gchar*	stdout;
	char*		customname=NULL;
	gint   	spawnret=0;

	if (metaThemeSelected==NULL)
		{
			g_spawn_command_line_sync(XCONFGETFRAME,&stdout,NULL,&spawnret,NULL);
			if (spawnret==0)
				{
					stdout[strlen(stdout)-1]=0;
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

	if (filename!=NULL && strlen(filename)>0)
		{
			setValue(XCONFGETCONTROLS,STRING,&gtk);
			setValue(XCONFGETFRAME,STRING,&frame);
			setValue(XCONFGETICONS,STRING,&iconTheme);
			setValue(XCONFGETCURSOR,STRING,&cursorTheme);

			asprintf(&thumbfile,"%s/%s.png",customFolder,filename);

			sprintf(buffer,"%s/%s",themesArray[0],frame);
			if (!g_file_test(buffer, G_FILE_TEST_IS_DIR))
				sprintf(buffer,"%s/%s",themesArray[1],frame);

			g_mkdir_with_parents(customFolder,493);
			asprintf(&dbname,"%s/%s.db",customFolder,filename);
			fd=fopen(dbname,"w");
			if(fd!=NULL)
				{
					sprintf(filedata,"[Data]\nName=%s\nThumbnail=%s\n",filename,thumbfile);
					buildCustomDB(XCONFGETCONTROLS,"GtkTheme");
					buildCustomDB(XCONFGETICONS,"IconTheme");
					buildCustomDB(XCONFGETCURSOR,"CursorTheme");
					buildCustomDB(XCONFGETFRAME,"Xfwm4Theme");
					buildCustomDB(XCONFGETPAPER,"BackgroundImage");
					buildCustomDB(XCONFGETLAYOUT,"TitleButtonLayout");
					buildCustomDB(XCONFGETTITLEPOS,"TitlePosition");
					buildCustomDB(XCONFGETWMFONT,"WMFont");
					buildCustomDB(XCONFGETAPPFONT,"AppFont");
					buildCustomDB(XCONFGETSTYLE,"BackdropStyle");
					buildCustomDB(XCONFGETBRIGHT,"BackdropBright");
					buildCustomDB(XCONFGETSATU,"BackdropSatu");
					buildCustomDB(XCONFGETCURSORSIZE,"CursorSize");

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

					freeAndNull(&lastMetaTheme);
					asprintf(&lastMetaTheme,"%s",filename);
					sprintf(generalBuffer,"%s\"%s\"",XMTSETMETATHEME,lastMetaTheme);
					system(generalBuffer);
				}

			freeAndNull(&dbname);
			freeAndNull(&filename);
			freeAndNull(&gtk);
			freeAndNull(&frame);
			freeAndNull(&iconTheme);
			freeAndNull(&cursorTheme);
			freeAndNull(&thumbfile);
		}

	freeAndNull(&customname);

	if (flag==true)
		rerunAndUpdate(true,true);
}

//rebuild db
void rerunAndBuild(GtkWidget* window,gpointer data)
{
	char*	datax[]={(char*)"xfce-theme-manager",(char*)"-m",NULL};

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

int extractAndInstall(char* filename)
{
	gchar*	stdout=NULL;
	int		retval=-1;
	gint		spawnret=-1;

	while(true)
	{
		sprintf(generalBuffer,"tar --wildcards -tf %s */gtkrc",filename);
		g_spawn_command_line_sync((char*)generalBuffer,&stdout,NULL,&spawnret,NULL);
		if (spawnret==0)
			{
				stdout[strlen(stdout)-1]=0;
				if(strlen(stdout)>1)
					{
						sprintf(generalBuffer,"tar -C %s -xf %s",themesArray[0],filename);
						retval=system(generalBuffer);
						freeAndNull(&stdout);
						break;
					}
				freeAndNull(&stdout);
			}

		sprintf(generalBuffer,"tar --wildcards -tf %s */themerc",filename);
		g_spawn_command_line_sync((char*)generalBuffer,&stdout,NULL,&spawnret,NULL);
		if (spawnret==0)
			{
				stdout[strlen(stdout)-1]=0;
				if(strlen(stdout)>1)
					{
						sprintf(generalBuffer,"tar -C %s -xf %s",themesArray[0],filename);
						retval=system(generalBuffer);
						freeAndNull(&stdout);
						break;
					}
				freeAndNull(&stdout);
			}

		sprintf(generalBuffer,"tar --wildcards -tf %s */index.theme",filename);
		g_spawn_command_line_sync((char*)generalBuffer,&stdout,NULL,&spawnret,NULL);
		if (spawnret==0)
			{
				stdout[strlen(stdout)-1]=0;
				if(strlen(stdout)>1)
					{
						sprintf(generalBuffer,"tar -C %s -xf %s",iconsArray[0],filename);
						retval=system(generalBuffer);
						freeAndNull(&stdout);
						break;
					}
				freeAndNull(&stdout);
			}
		break;
	}

	if(retval==0)
		infoDialog("Installed",filename,GTK_MESSAGE_INFO);
	else
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
	bool		doupdate=false;
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
							doupdate=extractAndInstall(filename);
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
						}
				}
			freeAndNull(&filename);
			freeAndNull(&lowername);
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
void doMeta(char* metaFilename)
{
	GKeyFile*		keyfile=g_key_file_new();
	int			keycnt=14;
	char*			keydata=NULL;
	char*			comma;
	GdkModifierType	mask;
	const char*		keys[]={"CursorTheme","Xfwm4Theme","IconTheme","BackgroundImage","BackdropStyle","TitleButtonLayout","TitlePosition","WMFont","AppFont","BackdropBright","BackdropSatu","GtkTheme","CursorSize","Name"};
	const char*		xconf[]={XCONFSETCURSOR,XCONFSETFRAME,XCONFSETICONS,XCONFSETPAPER,XCONFSETSTYLE,XCONFSETLAYOUT,XCONFSETTITLEPOS,XCONFSETWMFONT,XCONFSETAPPFONT,XCONFSETBRIGHT,XCONFSETSATU,XCONFSETCONTROLS,XCONFSETCURSORSIZE,XMTSETMETATHEME};

	GtkSettings *settings=gtk_settings_get_default();;

	gdk_window_get_pointer(NULL,NULL,NULL,&mask);
	if (GDK_CONTROL_MASK & mask )
		{
			removeTheme(metaFilename);
			return;
		}

	if(g_key_file_load_from_file(keyfile,metaFilename,G_KEY_FILE_NONE,NULL))
		{
			metaThemeSelected=g_key_file_get_string(keyfile,"Data",(char*)"Name",NULL);
			for (int j=0;j<keycnt;j++)
				{
					keydata=g_key_file_get_string(keyfile,"Data",(char*)keys[j],NULL);
					if(keydata!=NULL)
						{
							switch (j)
								{
									case 4:
										gtk_combo_box_set_active((GtkComboBox*)styleComboBox,atoi(keydata));
										break;
									case 5:
										gtk_entry_set_text((GtkEntry*)layoutEntry,keydata);
										break;
									case 6:
										gtk_combo_box_set_active((GtkComboBox*)titlePos,positionToInt(keydata));
										break;
									case 7:
										 gtk_font_button_set_font_name((GtkFontButton*)wmFontButton,keydata);
										break;
									case 8:
										 gtk_font_button_set_font_name((GtkFontButton*)appFontButton,keydata);
										break;
									case 9:
										gtk_range_set_value((GtkRange*)briteRange,atoi(keydata));
										break;
									case 10:
										gtk_range_set_value((GtkRange*)satuRange,atof(keydata));
										comma=strchr(keydata,',');
										if(comma!=NULL)
											*comma='.';										
										break;
									case 11:
										g_object_set(settings,"gtk-theme-name",keydata,"gtk-color-scheme","default",NULL);
										break;
									case 12:
										gtk_range_set_value((GtkRange*)cursorSize,atoi(keydata));
										break;
								}
							sprintf(generalBuffer,"%s\"%s\"",(char*)xconf[j],keydata);
							system(generalBuffer);
							freeAndNull(&keydata);
							rerunAndUpdate(false,true);
						}
				}
			g_key_file_free(keyfile);
		}

	system("xfdesktop --reload");
}

void setPiece(char* filePath,const char* doCommand)
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
					rerunAndUpdate(false,false);
				}
		}
	g_key_file_free(keyfile);
}

//controls
void doControls(char* controlsFilename)
{
	GKeyFile*	keyfile=g_key_file_new();
	char*		command;
	char*		controlset;
	GtkSettings *settings;

	settings=gtk_settings_get_default();

	if(g_key_file_load_from_file(keyfile,controlsFilename,G_KEY_FILE_NONE,NULL))
		{
			controlset=g_key_file_get_string(keyfile,"Data","ThemeName",NULL);

			if(controlset!=NULL)
				{
					asprintf(&command,"%s\"%s\"",XCONFSETCONTROLS,controlset);
					system(command);
					g_object_set(settings,"gtk-theme-name",controlset,"gtk-color-scheme","default",NULL);
					freeAndNull(&command);
					freeAndNull(&controlset);
					rerunAndUpdate(false,false);
				}
			g_key_file_free(keyfile);
		}
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
				doMeta(text);
				break;

			case WMBORDERS:
				setPiece(text,XCONFSETFRAME);
				break;

			case CONTROLS:
				doControls(text);
				break;

			case ICONS:
				setPiece(text,XCONFSETICONS);
				break;

			case CURSORS:
				setPiece(text,XCONFSETCURSOR);
				break;

			case WALLPAPERS:
				setPiece(text,XCONFSETPAPER);
				break;
		}
	g_free (text);
	g_list_free (selected);
	
	//gtk_icon_view_scroll_to_path((GtkIconView *)view,path,FALSE,0,0);
}

gboolean mouseMove(GtkWidget* widget,GdkEvent* event,gpointer user_data)
{
	GtkTreePath* path=NULL;

	path=gtk_icon_view_get_path_at_pos((GtkIconView *)widget,event->button.x,event->button.y);
	if (path!=NULL)
		gtk_icon_view_select_path((GtkIconView *)widget,path);
	else
		gtk_icon_view_unselect_all((GtkIconView*)widget);

	return(TRUE);
}
                                                        
gboolean clickIt(GtkWidget* widget,GdkEvent* event,gpointer data)
{
	GtkTreePath* path=NULL;

	path=gtk_icon_view_get_path_at_pos((GtkIconView *)widget,event->button.x,event->button.y);
	if (path!=NULL)
		{
			gtk_icon_view_select_path((GtkIconView *)widget,path);
			themeIconCallback((GtkIconView *)widget,(void*)data);
			//gtk_icon_view_scroll_to_path((GtkIconView *)widget,path,FALSE,0,0);
			//holdPath=path;
		}
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

gboolean setBright(GtkWidget *widget, GdkEvent *event, gpointer user_data)
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

gboolean setSatu(GtkWidget *widget, GdkEvent *event, gpointer user_data)
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

