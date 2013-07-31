/*
 *
 * K.D.Hedger 2012 <kdhedger68713@gmail.com>
 *
 */

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "../Xfce-Theme-Manager/src/globals.h"

const char*	language[]={"ENGLISH","SPANISH","GERMAN","POLISH","FRENCH"};
const char*	suffix[]={"","es","de","pl","fr"};
char		buffer[256];

int main(int argc,char **argv)
{
	FILE*	fp;

	for(int i=SPANISH;i<NONE;i++)
		{
			sprintf((char*)&buffer[0],"./GUITranslation.%s",suffix[i]);
			fp=fopen(buffer,"w");
			for (int j=0;j<STOPWORD;j++)
				{
					fprintf(fp,"ENGLISH:%s\n",langStr[0][j]);
					fprintf(fp,"%s:%s\n\n",language[i],langStr[i][j]);
				}
			fclose(fp);
		}
	return(0);
}
