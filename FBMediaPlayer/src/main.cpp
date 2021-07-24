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
 
#include <getopt.h>

#include "globals.h"

struct option long_options[] =
	{
		{"noimages",0,0,'n'},
		{"version",0,0,'v'},
		{"help",0,0,'?'},
		{0, 0, 0, 0}
	};

void printHelp()
{
	printf("Usage: fbmediaplayer [OPTION]\n"
		"Frame Buffer Media Player\n"
		" -n, --noimages	Don't use images\n"
		" -v, --version	output version information and exit\n"
		" -h, -?, --help	print this help\n\n"
		"Report bugs to keithdhedger@gmail.com\n"
		);
}

int main(int argc, char **argv)
{
	while (1)
		{
			int	c;
			int	option_index=0;
			c=getopt_long(argc,argv,"v?hn",long_options,&option_index);
			if(c==-1)
				break;

			switch (c)
				{
					case 'n':
						useFBImages=false;
						break;

					case 'v':
						printf("fbmediaplayer %s\n",VERSION);
						return ALLOK;
						break;

					case '?':
					case 'h':
						printHelp();
						return ALLOK;
						break;

					default:
						fprintf(stderr,"?? Unknown argument ??\n");
						return UNKNOWNARG;
						break;
				}
		}

	mkdir(TEMPFILES,0700);
	musicFifoName=str(boost::format("%s/mplayerafifo%i") %TEMPFILES %getpid());
	videoFifoName=str(boost::format("%s/mplayervfifo%i") %TEMPFILES %getpid());
	outName=str(boost::format("%s/mplayerout%i") %TEMPFILES %getpid());
	mkfifo(musicFifoName.c_str(),0700);
	mkfifo(videoFifoName.c_str(),0700);

	mainApp=new CTK_mainAppClass();
	fbInfo=mainApp->CTK_getFBData();

	SETHIDECURS;
	makePrefsPage();
	makeMainPage();
	makeMoviesPage();
	makeTVPage();
	makeMusicPage();

//backdrop
	if(useFBImages==true)
		mainApp->CTK_setFBBackDrop(backDropPath->CTK_getText());

	mainApp->CTK_setPage(MAINPAGE);
	mainApp->CTK_clearScreen();//TODO//
	fflush(NULL);
	mainApp->CTK_updateScreen(mainApp,NULL);//TODO//
	mainApp->CTK_mainEventLoop(0,false,false);

	sendToPipe("q");
	system("rm -rf '" TEMPFILES "'");

	SETSHOWCURS;
	delete mainApp;

	return(0);
}

