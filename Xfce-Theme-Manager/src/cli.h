/******************************************************
*
*     ©keithhedger Tue 30 Jul 18:25:52 BST 2013
*     kdhedger68713@gmail.com
*
*     cli.h
* 
******************************************************/

#ifndef _CLI_
#define _CLI_

extern char*			cliTheme;
extern char*			cliControls;
extern char*			cliBorder;
extern char*			cliIcons;
extern char*			cliCursors;
extern char*			cliWallpaper;
extern char*			listParts;
extern char*			cliFileName;
extern int				cliMonitor;
extern int				cliPanel;
extern int				cliPanelSize;
extern int				cliPanelStyle;
extern char*			cliPanelImage;
extern int				cliPanelAlpha;
extern char*			cliPanelColour;

void cliSetPanelSize(void);
int doCliTheme(void);
int doCliThemePart(char* name,long what);
void cliSetPanelStyle(void);
void cliSetPanelImage(void);
void cliSetPanelAlpha(void);
void cliSetPanelColour(void);

#endif
