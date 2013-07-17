/*
 * Original author of parts of gtkpreview David D Lowe <daviddlowe.flimm@gmail.com>
 * Parts of cursor preveiw Copyright (c) 2008 Nick Schermer <nick@xfce.org> & Jannis Pohlmann <jannis@xfce.org>
 * from xfce4-settings-4.6.5/dialogs/mouse-settings
 *
 * Parts of xwm4 4.10pre
 *
 * oroborus - (c) 2001 Ken Lynch
 * xfwm4    - (c) 2002-2011 Olivier Fourdan
 *
 * Seriously mucked about by:
 *
 * K.D.Hedger 2012 <kdhedger68713@gmail.com>
 *
 */

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "../Xfce-Theme-Manager/src/globals.h"

int main(int argc,char **argv)
{
	for (int j=0;j<STOPWORD;j++)
		{
			printf("ENGLISH:%s\n",langStr[0][j]);
			printf("SPANISH:%s\n",langStr[1][j]);
			printf("GERMAN:%s\n",langStr[2][j]);
			printf("POLISH:%s\n\n",langStr[3][j]);
		}

	return(0);
}
