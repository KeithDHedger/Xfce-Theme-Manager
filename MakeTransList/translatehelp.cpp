/*
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
			wprintf(L"POLISH:%ls\n",helpStr[3][j]);
			wprintf(L"FRENCH:%ls\n\n",helpStr[4][j]);
		}

	return(0);
}
