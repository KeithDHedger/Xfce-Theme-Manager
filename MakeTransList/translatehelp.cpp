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
#include <wchar.h>
#include <gtk/gtk.h>
#include <locale.h>

#include "../Xfce-Theme-Manager/src/globals.h"

int main(int argc,char **argv)
{
	setlocale(LC_ALL, "");
	for (int j=0;j<HELPSTOP;j++)
		{
			wprintf(L"ENGLISH:%ls\n",helpStr[0][j]);
			wprintf(L"SPANISH:%ls\n",helpStr[1][j]);
			wprintf(L"GERMAN:%ls\n",helpStr[2][j]);
			wprintf(L"POLISH:%ls\n\n",helpStr[3][j]);
		}

	return(0);
}
