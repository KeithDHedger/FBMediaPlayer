/*
 *
 * ©K. D. Hedger. Sun  6 Jun 14:48:08 BST 2021 keithdhedger@gmail.com

 * This file (moviesgui.cpp) is part of FBMediaPlayer.

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
 
#include "movies.h"

CTK_cursesChooserClass		*videoList;
const char					*videoListFolder="./";
int							videoMidWay;
int							videoChooserWidth;
int							videoChooserHite;
bool						doQuitVideo=false;
int							movieControlsSY;
bool						vplaying=false;
bool						vpaused=false;

const char	*moviePlayerButtons[][2]={{"Start",DATADIR "/pixmaps/MusicPlayer/start.png"},
{"Prev",DATADIR "/pixmaps/MusicPlayer/prev.png"},
{"Play",DATADIR "/pixmaps/MusicPlayer/play.png"},
{"Stop",DATADIR "/pixmaps/MusicPlayer/stop.png"},
{"Pause",DATADIR "/pixmaps/MusicPlayer/pause.png"},
{"Next",DATADIR "/pixmaps/MusicPlayer/next.png"},
{"Last",DATADIR "/pixmaps/MusicPlayer/end.png"},
{"Quit",DATADIR "/pixmaps/MusicPlayer/quit.png"},
};

void sendToMoviePipe(const std::string command)
{
	std::string	buffer="echo -e \"";
	buffer+=command + "\" >\"" + videoFifoName + "\" &";
	std::cerr << buffer << std::endl;
	system(buffer.c_str());
}

bool moviesControlsCB(void *inst,void *userdata)
{
	long	ud=(long)userdata;

	switch(ud)
		{
//			case START:
//				if(playing==false)
//					return(true);
//				sendToMoviePipe(str(boost::format("load \\\"%s\\\"") %videoList->filePath));
//				playing=true;
//				paused=false;
//				break;
//
//			case PREVIOUS:
//				if(playing==false)
//					return(true);
//				sendToPipe("pt_step -1");
//				paused=false;
//				break;

			case PLAY:
				//if(vplaying==true)
				//	{
						sendToMoviePipe("p");
				//		vpaused=!vpaused;
				//	}
				//if(vplaying==true)
				//	return(true);
				break;

//			case STOP:
//				setLastPlayed();
//				if(playing==false)
//					return(true);
//				for(int j=0;j<songs.size();j++)
//					free(songs[j]);
//				songs.clear();
//				songList->CTK_clearList();
//				sendToPipe("stop");
//				albumArt->CTK_newFBImage(chooserWidth+6,artSY,artHite*2,artHite,"",false);
//				nowPlaying->CTK_updateText("");
//				playLists->lb->activeItem=-1;
//				mainApp->CTK_setDefaultGadget(playLists->lb);
//				mainApp->CTK_clearScreen();
//				mainApp->CTK_updateScreen(mainApp,(void*)1);
//				playing=false;
//				paused=false;
//				progressIndicator->CTK_setValue(0);
//				progressIndicator->CTK_setMinValue(0);
//				progressIndicator->CTK_setMaxValue(0);
//				progressIndicator->CTK_drawGadget();
//				updated=false;
//				mainApp->CTK_updateScreen(mainApp,NULL);
//				break;
//
			case PAUSE:
				//if(vplaying==false)
				//	return(true);
				sendToMoviePipe("p");
				//vpaused=!vpaused;
				break;
//
//			case END:
//				if(playing==false)
//					return(true);
//				sendToPipe(str(boost::format("p\\npausing_keep_force loadlist \\\"%s\\\"") %playLists->filePath));
//				sendToPipe(str(boost::format("pausing_keep_force pt_step %i\\np") %(songs.size()-1)));
//				playing=true;
//				paused=false;
//				break;
//
//			case NEXT:
//				if(playing==false)
//					return(true);
//				sendToPipe("pt_step 1");
//				paused=false;
//				break;
//

			case STOP:
			std::cerr << "got stop" << std::endl;
				sendToMoviePipe("q");
				sleep(1);
				mainApp->CTK_clearScreen();
				mainApp->CTK_updateScreen(mainApp,NULL);
				fflush(NULL);
				break;
			case QUIT:
				sendToMoviePipe("q");
				//vpaused=false;
				//vplaying=false;
				doQuitVideo=true;
				fflush(NULL);
				break;


//			case QUIT:
//				setLastPlayed();
//				for(int j=0;j<songs.size();j++)
//					free(songs[j]);
//				songs.clear();
//				songList->CTK_clearList();
//				playLists->lb->activeItem=-1;
//				sendToPipe("stop");
//				albumArt->CTK_newFBImage(chooserWidth+6,artSY,artHite*2,artHite,"",false);
//				nowPlaying->CTK_updateText("");
//				playing=false;
//				paused=false;
//				doQuitMusic=true;
//				progressIndicator->CTK_setValue(0);
//				progressIndicator->CTK_setMinValue(0);
//				progressIndicator->CTK_setMaxValue(0);
//				progressIndicator->CTK_drawGadget();
//				fflush(NULL);
//				break;
		}

//	switch(ud)
//		{
//			case QUIT:
//			case HOMEIMAGE:
//				doQuitVideo=true;
//				fflush(NULL);
//				break;
//		}
	return(true);
}

bool pagekeyVideoCB(CTK_mainAppClass *app,void *userdata)
{
	if(app->readKey->inputBuffer.length()!=0)
		{
			switch(toupper(app->readKey->inputBuffer.at(0)))
				{
					case 'F':
						sendToMoviePipe("seek +30");
						return(true);
						break;
					case 'R':
						sendToMoviePipe("seek -30");
						return(true);
						break;
					case ' ':
						moviesControlsCB(NULL,(void*)PAUSE);
						break;
					case 'Q':
						//controlsCB(NULL,(void*)QUIT);
						doQuitVideo=true;
						moviesControlsCB(NULL,(void*)QUIT);
						//fprintf(stderr,"---->>>>\n");
						break;
//					case 'N':
//					case '.':
//						controlsCB(NULL,(void*)NEXT);
//						break;
//					case 'P':
//					case ',':
//						controlsCB(NULL,(void*)PREVIOUS);
//						break;
					case 'S':
					case 'X':
						moviesControlsCB(NULL,(void*)STOP);
						break;
					default:
						return(false);
				}
		}
	else
		return(false);
	return(true);
}

bool playVideoCB(void *inst,void *userdata)
{
videoList->CTK_setVisible(false);
mainApp->CTK_clearScreen();
doQuitVideo=false;
fprintf(stderr,"here >>%s<<\n",videoList->filePath.c_str());
char *command;

//	if(useFBImages==false)
//		{
//			//mplayer -quiet -slave -input file=/tmp/vmp "/media/BigBackup/Homenet/Homenet/Movies/chinamovies/Beijing Caves.mp4"
//			system(str(boost::format("mplayer -quiet -slave -input file='%s' -idle >'%s' 2>/dev/null &") %videoFifoName %outName).c_str());
//
//		}
//	else
//		{
//		}
//ffprobe -v error -select_streams v:0 -show_entries stream=width,height,display_aspect_ratio -of default=nw=1:nk=1 "/media/BigBackup/Homenet/Homenet/Movies/Family/Airfield.mp4" 
//352
//288
//4:3
	if(useFBImages==false)
		system(str(boost::format("mplayer -quiet -slave -input file='%s' -idle -input nodefault-bindings >'%s' 2>/dev/null &") %videoFifoName %outName).c_str());
	else
		system(str(boost::format("mplayer -vo fbdev2 -quiet -slave -xy 1920 -zoom -input file='%s' -idle -input nodefault-bindings >'%s' 2>/dev/null &") %videoFifoName %outName).c_str());
//sleep(2);
	sendToMoviePipe(str(boost::format("loadfile \\\"%s\\\" 0 \n") %videoList->filePath));
//asprintf(&command,"mplayer '%s'",videoList->filePath.c_str());
//system(command);

//	do
//		{
//			mainApp->CTK_mainEventLoop(-250,false);
//			//getMeta();
//		}
//	while (doQuitVideo==false);
fprintf(stderr,">>>>fin\n");
//doQuitVideo=true;
mainApp->CTK_clearScreen();
mainApp->CTK_updateScreen(mainApp,NULL);
fflush(NULL);
vplaying=true;
return(true);
}

void makeMoviesPage(void)
{
	CTK_cursesGadgetClass	*gadget;
	int						gw=mainApp->maxCols/8;
	int						gh=gw/(fbInfo->charHeight/fbInfo->charWidth);
	int						yspread=2;
	int						yoffset=0;
	int						btnnumx=1;
	int						btnnumy=1;
	int						btncnt=2;	

	mainApp->CTK_addPage();

	if(useFBImages==false)
		gw=10;

	btnnumy++;
	if(useFBImages==true)
		{
			gw=gw/2;
			yspread=4;
			yoffset=2;
		}

//files
//	gadget=newButtonSpread(1,mainApp->maxCols,1,mainApp->maxRows,gw,gh,btncnt,yspread,btnnumx++,btnnumy,buttonNames[FILMIMAGE][int(useFBImages)],useFBImages);
//	gadget->CTK_setSelectCB(buttonselectCB,(void*)FILMIMAGE);

	videoMidWay=mainApp->maxCols/2;
	//dialogWidth=mainApp->maxCols-4;
	videoChooserWidth=((mainApp->maxCols/8)*5)-2;
	videoChooserHite=mainApp->maxRows-16;

	videoList=new CTK_cursesChooserClass(mainApp,3,2,videoChooserWidth,videoChooserHite);
	videoList->CTK_setShowTypes(ANYTYPE);
	videoList->CTK_setShowHidden(false);
	videoList->CTK_selectFolder(mainApp,videoListFolder);
	videoList->CTK_setSelectCB(playVideoCB,NULL);
	mainApp->CTK_addChooserBox(videoList);

//	if(useFBImages==false)
//		system(str(boost::format("mplayer -quiet -slave -input file='%s' -idle -input nodefault-bindings >'%s' 2>/dev/null &") %videoFifoName %outName).c_str());
//	else
//		system(str(boost::format("mplayer -vo fbdev2 -quiet -slave -xy 1920 -zoom -input file='%s' -idle -input nodefault-bindings >'%s' 2>/dev/null &") %videoFifoName %outName).c_str());
//keithhedger@LFS90Dev [ / ]$ mplayer -quiet -vo fbdev2 -xy 1920 -zoom "/media/BigBackup/Homenet/Homenet/Movies/chinamovies/Beijing Caves.mp4"

//line2
//	btnnumx=1;
//	btnnumy++;
//	if(useFBImages==true)
//		{
//			gw=gw/2;
//			yspread=4;
//			yoffset=2;
//		}
	movieControlsSY=mainApp->maxRows-4;
	btnnumx=1;
	for(int j=0;j<CONTROLCNT;j++)
		{
			if(useFBImages==true)
				gadget=mainApp->CTK_addNewFBImage(mainApp->utils->CTK_getGadgetPos(1,mainApp->maxCols,CONTROLCNT,4,btnnumx),movieControlsSY,4,4,moviePlayerButtons[j][int(useFBImages)]);
			else
				gadget=mainApp->CTK_addNewButton(mainApp->utils->CTK_getGadgetPos(1,mainApp->maxCols,CONTROLCNT,10,btnnumx),movieControlsSY,10,1,moviePlayerButtons[j][int(useFBImages)]);
				gadget->CTK_setSelectCB(moviesControlsCB,(void*)btnnumx++);
		}


//home
//	gadget=newButtonSpread(1,mainApp->maxCols,1,mainApp->maxRows,gw,gh,1,yspread,btnnumx,btnnumy+yoffset,buttonNames[HOMEIMAGE][int(useFBImages)],useFBImages);
//	gadget->CTK_setSelectCB(moviesControlsCB,(void*)HOMEIMAGE);

//keyboard control
	mainApp->pages[mainApp->pageNumber].pageKey=pagekeyVideoCB;
}

void runVideo(void)
{
	videoList->CTK_selectFolder(mainApp,videoListFolder);
	videoList->CTK_updateList();
//	getLastPlayed();
	mainApp->CTK_clearScreen();
	mainApp->CTK_updateScreen(mainApp,NULL);
	fflush(NULL);
	//mainApp->CTK_updateScreen(mainApp,NULL);

//return;
//	videoList->CTK_selectFolder(mainApp,videoListFolder);
//	videoList->CTK_updateList();
	//mainApp->CTK_clearScreen();
	//fflush(NULL);
	//mainApp->CTK_updateScreen(mainApp,NULL);
	doQuitVideo=false;
	//videoList->CTK_setVisible(false);
	//mainApp->CTK_clearScreen();
//	return;
	do
		{
			mainApp->CTK_mainEventLoop(-250,false);
			//getMeta();
		}
	while (doQuitVideo==false);
	mainApp->CTK_setPage(MAINPAGE);
	mainApp->runEventLoop=true;
	mainApp->CTK_clearScreen();
	mainApp->CTK_updateScreen(mainApp,NULL);
	fflush(NULL);
}

