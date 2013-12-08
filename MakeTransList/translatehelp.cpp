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

const wchar_t*	language[]={L"ENGLISH",L"SPANISH",L"GERMAN",L"POLISH",L"FRENCH",L"PORTUGUESE"};
const char*	suffix[]={"","es","de","pl","fr","pt"};
char		buffer[1024];

int main(int argc,char **argv)
{
	FILE*	fp;
	setlocale(LC_ALL, "");

	for(int i=SPANISH;i<NONE;i++)
		{
			sprintf((char*)&buffer[0],"./HELPTranslation.%s",suffix[i]);
			fp=fopen(buffer,"w");
			for (int j=0;j<HELPSTOP;j++)
				{
					fwprintf(fp,L"ENGLISH:%ls\n",helpStr[0][j]);
					fwprintf(fp,L"%ls:%ls\n\n",language[i],helpStr[i][j]);
				}
			fclose(fp);
		}
	return(0);
}
