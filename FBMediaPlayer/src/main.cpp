/*
 *
 * ©K. D. Hedger. Tue 31 Jul 12:13:46 BST 2018 keithdhedger@gmail.com

 * This file (main.cpp) is part of FBMediaPlayer.

 * FBMediaPlayer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.

 * FBMediaPlayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with FBMediaPlayer.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <cursesGlobals.h>

#define VERSION "0.0.0"
#define UNKNOWNARG -100

enum {INFOAPPNAME=1,INFOAPPINFO,INFOCOPYRITE,INFOEMAIL,INFOWEBSITE,INFOCREDITS,INFOLICENCE,DIALOGWIDTH};

int main(int argc, char **argv)
{
	CTK_cursesUtilsClass	*cu;
	CTK_mainAppClass		*mainApp;

	if(argc<8)
		{
			printf("USAGE:\naboutbox \"App name\" \"App info\" \"Copyright\" \"Email\" \"Website\" \"Credits\" \"Licence File\" Width.\n");
			exit(1);
		}

	mainApp=new CTK_mainAppClass();
	cu=new CTK_cursesUtilsClass();

	cu->CTK_aboutDialog(argv[INFOAPPNAME],argv[INFOAPPINFO],argv[INFOCOPYRITE],argv[INFOEMAIL],argv[INFOWEBSITE],argv[INFOCREDITS],argv[INFOLICENCE],atoi(argv[DIALOGWIDTH]));

	SETSHOWCURS;
	delete mainApp;
	delete cu;
	return(0);
}

