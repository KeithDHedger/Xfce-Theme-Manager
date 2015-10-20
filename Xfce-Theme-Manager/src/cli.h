/*
 *
 * ©K. D. Hedger. Tue 20 Oct 15:53:13 BST 2015 kdhedger68713@gmail.com

 * This file (cli.h) is part of Xfce-Theme-Manager.

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
extern int				cliPaperStyle;

void cliSetPanelSize(void);
int doCliTheme(void);
int doCliThemePart(char* name,long what);
void cliSetPanelStyle(void);
void cliSetPanelImage(void);
void cliSetPanelAlpha(void);
void cliSetPanelColour(void);
void cliSetPaperStyle(void);

#endif
