/*
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
