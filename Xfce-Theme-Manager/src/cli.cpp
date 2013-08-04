/******************************************************
*
*     ©keithhedger Tue 30 Jul 18:25:52 BST 2013
*     kdhedger68713@gmail.com
*
*     cli.cpp
* 
******************************************************/
#include <xfconf/xfconf.h>

#include "globals.h"
#include "callbacks.h"

char*				cliTheme=NULL;
char*				cliControls=NULL;
char*				cliBorder=NULL;
char*				cliIcons=NULL;
char*				cliCursors=NULL;
char*				cliWallpaper=NULL;
char*				listParts=NULL;
char*				cliFileName=NULL;
int					cliMonitor=0;
int					cliPanel=1;
int					cliPanelSize;
int					cliPanelStyle;
char*				cliPanelImage;
int					cliPanelAlpha;
char*				cliPanelColour;
int					cliPaperStyle=0;

void cliSetPanelColour(void)
{
	int red,green,blue,alpha;

	XfconfChannel*	channelptr=xfconf_channel_get(XFCEPANELS);

	sprintf((char*)&generalBuffer,"/panels/panel-%i/background-color",cliPanel);
	red=strtol(slice(cliPanelColour,0,1),NULL,16)*256;
	green=strtol(slice(cliPanelColour,2,3),NULL,16)*256;
	blue=strtol(slice(cliPanelColour,4,5),NULL,16)*256;
	alpha=65535;

	xfconf_channel_set_array(channelptr,(const gchar*)&generalBuffer,XFCONF_TYPE_UINT16,&red,XFCONF_TYPE_UINT16,&green,XFCONF_TYPE_UINT16,&blue,XFCONF_TYPE_UINT16,&alpha,G_TYPE_INVALID);
}

void cliSetPanelAlpha(void)
{
	sprintf((char*)&generalBuffer,"/panels/panel-%i/background-alpha",cliPanel);
	setValue(XFCEPANELS,generalBuffer,INT,(void*)(long)cliPanelAlpha);
}

void cliSetPanelSize(void)
{
	sprintf((char*)&generalBuffer,"/panels/panel-%i/size",cliPanel);
	setValue(XFCEPANELS,generalBuffer,INT,(void*)(long)cliPanelSize);
}

void cliSetPanelStyle(void)
{
	sprintf((char*)&generalBuffer,"/panels/panel-%i/background-style",cliPanel);
	setValue(XFCEPANELS,generalBuffer,INT,(void*)(long)cliPanelStyle);
}

void cliSetPanelImage(void)
{
	sprintf((char*)&generalBuffer,"/panels/panel-%i/background-image",cliPanel);
	setValue(XFCEPANELS,(const char*)generalBuffer,STRING,cliPanelImage);
}

int doCliTheme(void)
{
	char* tn=NULL;			

	asprintf(&tn,"%s/%s.db",customFolder,cliTheme);
	if (g_file_test(tn,G_FILE_TEST_EXISTS))
		{
			doMeta(tn);
			freeAndNull(&tn);
			return(0);
		}
	else
		freeAndNull(&tn);
	for (int j=0;j<2;j++)
		{
			asprintf(&tn,"%s/%i.%s.db",metaFolder,j,cliTheme);
			if (g_file_test(tn,G_FILE_TEST_EXISTS))
				{
					doMeta(tn);
					freeAndNull(&tn);
					return(0);
				}
			else
				freeAndNull(&tn);
		}
	return(1);
}

int doCliThemePart(char* name,long what)
{

	char*	papername=NULL;

	setValue(XTHEMER,METATHEMEPROP,STRING,(void*)"DEADBEEF");

	switch(what)
		{
			case WMBORDERS:
				setValue(XFWM,WMBORDERSPROP,STRING,name);
				return(0);
				break;
			case CONTROLS:
				setValue(XSETTINGS,CONTROLTHEMEPROP,STRING,name);
				return(0);
				break;
			case ICONS:
				setValue(XSETTINGS,ICONTHEMEPROP,STRING,name);
				return(0);
				break;
			case CURSORS:
				setValue(XSETTINGS,CURSORSPROP,STRING,name);
				return(0);
				break;
			case WALLPAPERS:
				for(int j=0;j<2;j++)
					{	
						sprintf((char*)&generalBuffer,"%s/%i.%s.db",wallpapersFolder,j,name);
						papername=getThemeNameFromDB(generalBuffer);
						if(papername!=NULL)
							{
								sprintf((char*)&generalBuffer[0],"%s%i/image-path",MONITORPROP,cliMonitor);
								setValue(XFCEDESKTOP,(char*)&generalBuffer[0],STRING,papername);
								return(0);
							}
					}
				break;
		}
	return(1);
}

void cliSetPaperStyle(void)
{
	sprintf((char*)&generalBuffer[0],"%s%i/image-style",MONITORPROP,cliMonitor);
	setValue(XFCEDESKTOP,(char*)&generalBuffer[0],INT,(void*)(long)cliPaperStyle);
}






