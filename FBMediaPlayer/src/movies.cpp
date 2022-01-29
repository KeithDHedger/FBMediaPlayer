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

const char	*moviePlayerButtons[][2]={{"Play",DATADIR "/pixmaps/MusicPlayer/pause.png"},
{"Stop",DATADIR "/pixmaps/MusicPlayer/stop.png"},
{"Quit",DATADIR "/pixmaps/MusicPlayer/quit.png"},
{"Next",DATADIR "/pixmaps/MusicPlayer/next.png"},
{"Prev",DATADIR "/pixmaps/MusicPlayer/prev.png"},
};

void sendToVideoPipe(const std::string command)
{
	std::string	buffer="echo -e \"";
	buffer+=command + "\" >\"" + videoFifoName + "\" &";
	system(buffer.c_str());
}

bool moviePauseControlsCB(void *inst,void *userdata)
{
	long	ud=(long)userdata;

fprintf(stderr,"ud=%i\n",ud);

	switch(ud)
		{
			case VIDEOSTART:
				{
					vpaused=false;
					sendToVideoPipe("pause");
				}
				break;
			case VIDEOSTOP:
				sendToVideoPipe("stop");
				vplaying=false;
				vpaused=false;
				//doQuitVideo=true;
				//mainApp->CTK_setPage(2);
				break;
			case VIDEOQUIT:
				break;
			case VIDEOSKIPAHEAD:
				break;
			case VIDEOSKIPBACK:
				break;
		}
	return(true);
}

void makeMoviePausePage(void)
{
	CTK_mainAppClass	ma;
	CTK_cursesGadgetClass	*gadget;
	CTK_cursesGadgetClass	*gadget0;

	int						yspread=2;
	int						yoffset=0;
	long					btnnumx=1;
	int						btnnumy=1;
	int						btncnt=2;

	int						gw=ma.maxCols/8;
	int						gh=gw/(fbInfo->charHeight/fbInfo->charWidth);

	if(useFBImages==false)
		gw=10;


	movieControlsSY=ma.maxRows-4;

/*
	btnnumx=1;
	for(int j=0;j<CONTROLCNT;j++)
		{
			if(useFBImages==true)
				gadget=mainApp->CTK_addNewFBImage(mainApp->utils->CTK_getGadgetPos(1,mainApp->maxCols,CONTROLCNT,4,btnnumx),controlsSY,4,4,musicPlayerButtons[j][int(useFBImages)]);
			else
				gadget=mainApp->CTK_addNewButton(mainApp->utils->CTK_getGadgetPos(1,mainApp->maxCols,CONTROLCNT,10,btnnumx),controlsSY,10,1,musicPlayerButtons[j][int(useFBImages)]);
			gadget->CTK_setSelectCB(controlsCB,(void*)btnnumx++);
		}

*/
	btnnumx=0;
	for(int j=0;j<VIDEONOMORE;j++)
		{
			if(useFBImages==true)
				//gadget=ma.CTK_addNewFBImage(ma.utils->CTK_getGadgetPos(1,ma.maxCols,VIDEONOMORE,4,btnnumx),movieControlsSY,4,4,moviePlayerButtons[j][int(useFBImages)]);
				  gadget=ma.CTK_addNewFBImage(ma.utils->CTK_getGadgetPos(1,ma.maxCols,VIDEONOMORE,4,btnnumx),movieControlsSY,4,4,moviePlayerButtons[j][int(useFBImages)]);
			else
				gadget=ma.CTK_addNewButton(ma.utils->CTK_getGadgetPos(1,ma.maxCols,VIDEONOMORE,10,btnnumx+1),movieControlsSY,10,1,moviePlayerButtons[j][int(useFBImages)]);
if(btnnumx==0)
	gadget0=gadget;
			gadget->CTK_setSelectCB(moviePauseControlsCB,(void*)btnnumx++);
		}

//	while(vplaying==true)
		{
			ma.CTK_setDefaultGadget(gadget0,false);
			ma.CTK_clearScreen();
			ma.CTK_updateScreen(&ma,NULL);
			fflush(NULL);
			vpaused=true;
			do
				ma.CTK_mainEventLoop(-250,false);
			while (vpaused==true);
			ma.CTK_clearScreen();
		}
}

/*
CTK_mainAppClass	ma;
ma.eventLoopCBIn=mainloopCB;
	CTK_cursesGadgetClass	*gadget;
	int						yspread=2;
	int						yoffset=0;
	long					btnnumx=1;
	int						btnnumy=1;
	int						btncnt=2;

	movieControlsSY=ma.maxRows-4;

	btnnumx=0;
	for(int j=0;j<VIDEONOMORE;j++)
//int j=0;
		{
//			if(useFBImages==true)
//				gadget=ma.CTK_addNewFBImage(ma.utils->CTK_getGadgetPos(1,ma.maxCols,VIDEONOMORE,4,btnnumx),movieControlsSY,4,4,moviePlayerButtons[j][int(useFBImages)]);
//			else
				gadget=ma.CTK_addNewButton(ma.utils->CTK_getGadgetPos(1,ma.maxCols,VIDEONOMORE,10,btnnumx+1),movieControlsSY,10,1,moviePlayerButtons[j][int(useFBImages)]);
			gadget->CTK_setSelectCB(movieControlsCB,(void*)btnnumx++);


		}




ma.CTK_clearScreen();
mainApp->CTK_clearScreen();
ma.CTK_updateScreen(&ma,NULL);

fflush(NULL);
	do
		{
//fprintf(stderr,">>>>>>>>>>>>>>>>\n");
			ma.CTK_mainEventLoop(-250,false);
		}
	while (vplaying==true);


*/


//
//CTK_cursesChooserClass		*videoList;
//const char					*videoListFolder="./";
//int							videoMidWay;
//int							videoChooserWidth;
//int							videoChooserHite;
//bool						doQuitVideo=false;
//int							movieControlsSY;
//bool						vplaying=false;
//bool						vpaused=false;
//
//
//const char	*moviePlayerButtons[][2]={{"Play",DATADIR "/pixmaps/MusicPlayer/pause.png"},
//{"Stop",DATADIR "/pixmaps/MusicPlayer/stop.png"},
//{"Quit",DATADIR "/pixmaps/MusicPlayer/quit.png"},
//{"Next",DATADIR "/pixmaps/MusicPlayer/next.png"},
//{"Prev",DATADIR "/pixmaps/MusicPlayer/prev.png"},
//};

//void sendToMoviePipe(const std::string command)
//{
//	std::string	buffer="echo -e \"";
//	buffer+=command + "\" >\"" + videoFifoName + "\" &";
//	std::cerr << buffer << std::endl;
//	system(buffer.c_str());
//}


bool	isPaused=false;
bool	ignoreNL=false;

void mainloopCB(void *mainc,void *data)
{
	CTK_mainAppClass *mp=(CTK_mainAppClass *)mainc;
	if((mp->readKey->isHexString==true) && (mp->readKey->specialKeyName==CTK_KEY_RETURN))
		{
			sendToVideoPipe("pause");
			makeMoviePausePage();
		}
}

bool moviesControlsCB(void *inst,void *userdata)
{
//return(true);
	long	ud=(long)userdata;






//
//	switch(ud)
//		{
////			case START:
////				if(playing==false)
////					return(true);
////				sendToMoviePipe(str(boost::format("load \\\"%s\\\"") %videoList->filePath));
////				playing=true;
////				paused=false;
////				break;
////
////			case PREVIOUS:
////				if(playing==false)
////					return(true);
////				sendToAudioPipe("pt_step -1");
////				paused=false;
////				break;
//
//			case PLAY:
//				//if(vplaying==true)
//				//	{
//						sendToMoviePipe("p");
//				//		vpaused=!vpaused;
//				//	}
//				//if(vplaying==true)
//				//	return(true);
//				break;
//
////			case STOP:
////				setLastPlayed();
////				if(playing==false)
////					return(true);
////				for(int j=0;j<songs.size();j++)
////					free(songs[j]);
////				songs.clear();
////				songList->CTK_clearList();
////				sendToAudioPipe("stop");
////				albumArt->CTK_newFBImage(chooserWidth+6,artSY,artHite*2,artHite,"",false);
////				nowPlaying->CTK_updateText("");
////				playLists->lb->activeItem=-1;
////				mainApp->CTK_setDefaultGadget(playLists->lb);
////				mainApp->CTK_clearScreen();
////				mainApp->CTK_updateScreen(mainApp,(void*)1);
////				playing=false;
////				paused=false;
////				progressIndicator->CTK_setValue(0);
////				progressIndicator->CTK_setMinValue(0);
////				progressIndicator->CTK_setMaxValue(0);
////				progressIndicator->CTK_drawGadget();
////				updated=false;
////				mainApp->CTK_updateScreen(mainApp,NULL);
////				break;
////
//			case PAUSE:
//				//if(vplaying==false)
//				//	return(true);
//				sendToMoviePipe("p");
//				//vpaused=!vpaused;
//				break;
////
////			case END:
////				if(playing==false)
////					return(true);
////				sendToAudioPipe(str(boost::format("p\\npausing_keep_force loadlist \\\"%s\\\"") %playLists->filePath));
////				sendToAudioPipe(str(boost::format("pausing_keep_force pt_step %i\\np") %(songs.size()-1)));
////				playing=true;
////				paused=false;
////				break;
////
////			case NEXT:
////				if(playing==false)
////					return(true);
////				sendToAudioPipe("pt_step 1");
////				paused=false;
////				break;
////
//
//			case STOP:
//			std::cerr << "got stop" << std::endl;
//				sendToMoviePipe("q");
//				sleep(1);
//				mainApp->CTK_clearScreen();
//				mainApp->CTK_updateScreen(mainApp,NULL);
//				fflush(NULL);
//				break;
//			case QUIT:
//				sendToMoviePipe("q");
//				//vpaused=false;
//				//vplaying=false;
//				doQuitVideo=true;
//				fflush(NULL);
//				break;
//
//
////			case QUIT:
////				setLastPlayed();
////				for(int j=0;j<songs.size();j++)
////					free(songs[j]);
////				songs.clear();
////				songList->CTK_clearList();
////				playLists->lb->activeItem=-1;
////				sendToAudioPipe("stop");
////				albumArt->CTK_newFBImage(chooserWidth+6,artSY,artHite*2,artHite,"",false);
////				nowPlaying->CTK_updateText("");
////				playing=false;
////				paused=false;
////				doQuitMusic=true;
////				progressIndicator->CTK_setValue(0);
////				progressIndicator->CTK_setMinValue(0);
////				progressIndicator->CTK_setMaxValue(0);
////				progressIndicator->CTK_drawGadget();
////				fflush(NULL);
////				break;
//		}
//
	switch(ud)
		{
////			case QUIT:
			case HOMEIMAGE:
				doQuitVideo=true;
				fflush(NULL);
				break;
		}
	return(true);
}

//bool pagekeyVideoCB(CTK_mainAppClass *app,void *userdata)
//{
//	if(app->readKey->inputBuffer.length()!=0)
//		{
//			switch(toupper(app->readKey->inputBuffer.at(0)))
//				{
//					case 'F':
//						sendToMoviePipe("seek +30");
//						return(true);
//						break;
//					case 'R':
//						sendToMoviePipe("seek -30");
//						return(true);
//						break;
//					case ' ':
//						moviesControlsCB(NULL,(void*)PAUSE);
//						break;
//					case 'Q':
//						//controlsCB(NULL,(void*)QUIT);
//						doQuitVideo=true;
//						moviesControlsCB(NULL,(void*)QUIT);
//						//fprintf(stderr,"---->>>>\n");
//						break;
////					case 'N':
////					case '.':
////						controlsCB(NULL,(void*)NEXT);
////						break;
////					case 'P':
////					case ',':
////						controlsCB(NULL,(void*)PREVIOUS);
////						break;
//					case 'S':
//					case 'X':
//						moviesControlsCB(NULL,(void*)STOP);
//						break;
//					default:
//						return(false);
//				}
//		}
//	else
//		return(false);
//	return(true);
//}
//const char	*videoPlayerButtons[][2]={{"Start",DATADIR "/pixmaps/MusicPlayer/pause.png"},
//{"Stop",DATADIR "/pixmaps/MusicPlayer/stop.png"},
//{"Quit",DATADIR "/pixmaps/MusicPlayer/quit.png"}
//};

/*
			if(mp->readKey->inputBuffer.compare("q")==0)
				{
					sendToVideoPipe("quit");
					vplaying=false;
				}
			if(mp->readKey->inputBuffer.compare("s")==0)
				{
					sendToVideoPipe("stop");
					vplaying=false;
				}
			if(mp->readKey->inputBuffer.compare(">")==0)
				{
					sendToVideoPipe("seek +60.0" + std::string(keeppause));
				}
			if(mp->readKey->inputBuffer.compare("<")==0)
				{
					sendToVideoPipe("seek -60.0" + std::string(keeppause));
				}

*/
bool movieControlsCB(void *inst,void *userdata)
{
	long	ud=(long)userdata;

//if(isPaused==true)
//	ignoreNL=true;//TODO//MMMmmmm

fprintf(stderr,"ud=%i\n",ud);
			//const char	*keeppause="";
			//if(isPaused==true)
			//	ignoreNL=true;
			//	keeppause="\npause";
					ignoreNL=true;
		
//isPaused=false;
//			const char	*keeppause="";
//			if(isPaused==true)
//				keeppause="\npause";

	switch(ud)
		{
			case VIDEOSTART:
						{
						fprintf(stderr,"pause=%i inorenl=%i\n",isPaused,ignoreNL);
//				sendToVideoPipe("seek +60.0" );isPaused
				if(isPaused==true)
					{
						ignoreNL=true;
						sendToVideoPipe("pause");
					}
				else
					{
						ignoreNL=false;
						isPaused=!isPaused;
						sendToVideoPipe("pause\npause");
					}
				}

//				ignoreNL=false;//TODO//MMMmmmm
//				isPaused=false;
//				mainApp->readKey->inputBuffer="";
//				//mainApp->readKey->specialKeyName=CTK_KEY_NONE;
//				//sendToVideoPipe("pause");
//				sendToVideoPipe("pause\npause");
				break;
			case VIDEOSTOP:
				sendToVideoPipe("stop");
				vplaying=false;
				break;
			case VIDEOQUIT:
				sendToVideoPipe("quit");
				vplaying=false;
				break;
			case VIDEOSKIPAHEAD:
			{
				sendToVideoPipe("seek +60.0" );
				if(isPaused==false)
					sendToVideoPipe("pause");
				else
					ignoreNL=true;
				}
				break;
			case VIDEOSKIPBACK:
				//ignoreNL=true;//TODO//MMMmmmm
				//isPaused=false;
				//sendToVideoPipe("seek -60.0" + std::string(keeppause));
				break;
		}
	return(true);
}

bool playVideoCB(void *inst,void *userdata)
{
//TODO// set screen size in framebuffer
	std::string command;
	if(useFBImages==false)
		command=str(boost::format("mplayer -geometry 50:50 -quiet -slave -input file='%s' '%s' >'%s' 2>/dev/null &") %videoFifoName %videoList->filePath %outName);
	else
		command=str(boost::format("mplayer -vo fbdev2 -xy 1920 -zoom -fs -aspect 16:9 -quiet -slave -input file='%s' '%s' >'%s' 2>/dev/null &") %videoFifoName %videoList->filePath %outName);

	system(command.c_str());
	vplaying=true;
	CTK_mainAppClass	ma;
	ma.eventLoopCBIn=mainloopCB;
	ma.CTK_clearScreen();
	mainApp->CTK_clearScreen();
	ma.CTK_updateScreen(&ma,NULL);
	fflush(NULL);
	do
		{
			ma.CTK_mainEventLoop(-250,false);
		}
	while(vplaying==true);
	mainApp->CTK_clearScreen();
	mainApp->CTK_updateScreen(mainApp,NULL);
	//mainApp->CTK_setPage(3);
	return(true);
}

void makeKeyConf(void)
{
	FILE		*fp;
	varsStruct	retvs;

	fp=fopen(TEMPFILES "/mplayerkeyconf","w");

	if(fp!=NULL)
		{
//
////control
//			retvs=mainApp->utils->CTK_findVar(prefsData,"keycontrol");
//		//	if(retvs.charVar.c_str()[0]=='\n')
//				fprintf(stderr,">>%p<<\n",retvs.charVar.c_str()[0]);

//pause
			retvs=mainApp->utils->CTK_findVar(prefsData,"keypause");
			if(retvs.charVar.c_str()[0]==' ')
				fprintf(fp,"SPACE pause\n");
			else
				fprintf(fp,"%c pause\n",retvs.charVar.c_str()[0]);
//stop
			retvs=mainApp->utils->CTK_findVar(prefsData,"keystop");
			fprintf(fp,"%c stop\n",retvs.charVar.c_str()[0]);
//quit
			retvs=mainApp->utils->CTK_findVar(prefsData,"keyquit");
			fprintf(fp,"%c quit\n",retvs.charVar.c_str()[0]);
//ff
			retvs=mainApp->utils->CTK_findVar(prefsData,"keyfoward");
			fprintf(fp,"%c seek +30\n",retvs.charVar.c_str()[0]);
//rev
			retvs=mainApp->utils->CTK_findVar(prefsData,"keyreverse");
			fprintf(fp,"%c seek -30\n",retvs.charVar.c_str()[0]);
//next
			retvs=mainApp->utils->CTK_findVar(prefsData,"keynext");
			fprintf(fp,"%c pt_step 1\n",retvs.charVar.c_str()[0]);
//prev
			retvs=mainApp->utils->CTK_findVar(prefsData,"keyprev");
			fprintf(fp,"%c pt_step -1\n",retvs.charVar.c_str()[0]);

			fclose(fp);
		}
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
fprintf(stderr,"page=%i\n",mainApp->pageNumber);
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
	videoChooserHite=gh;
	videoChooserHite=mainApp->maxRows-16;
	//int						gh=gw/(fbInfo->charHeight/fbInfo->charWidth);
	
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
	if(useFBImages==true)
		{
			gw=gw/2;
			yspread=4;
			yoffset=2;
		}
	movieControlsSY=mainApp->maxRows-4;
	btnnumx=1;
btnnumy=1;
//newButtonSpread(int bx,int bw,int by,int bh,int gadw,int gadh,int gadcntx,int gadcnty,int gadnumx,int gadnumy,const char *path,bool useimage)
	gadget=newButtonSpread(1,mainApp->maxCols,1,mainApp->maxRows,gw,gh,3,6,2,6,buttonNames[HOMEIMAGE][int(useFBImages)],useFBImages);
	gadget->CTK_setSelectCB(moviesControlsCB,(void*)HOMEIMAGE);


//gadget=mainApp->CTK_addNewFBImage(mainApp->utils->CTK_getGadgetPos(1,mainApp->maxCols,(buttonSymbolicNames)QUITBTN,10,btnnumx),movieControlsSY,10,1,moviePlayerButtons[QUITBTN][int(useFBImages)]);

//	for(int j=0;j<CONTROLCNT;j++)
//		{
//			if(useFBImages==true)
//				gadget=mainApp->CTK_addNewFBImage(mainApp->utils->CTK_getGadgetPos(1,mainApp->maxCols,CONTROLCNT,4,btnnumx),movieControlsSY,4,4,moviePlayerButtons[j][int(useFBImages)]);
//			else
//				gadget=mainApp->CTK_addNewButton(mainApp->utils->CTK_getGadgetPos(1,mainApp->maxCols,CONTROLCNT,10,btnnumx),movieControlsSY,10,1,moviePlayerButtons[j][int(useFBImages)]);
////				gadget->CTK_setSelectCB(moviesControlsCB,(void*)btnnumx++);
//			btnnumx++;
//		}


//home
//	gadget=newButtonSpread(1,mainApp->maxCols,1,mainApp->maxRows,gw,gh,1,yspread,btnnumx,btnnumy+yoffset,buttonNames[HOMEIMAGE][int(useFBImages)],useFBImages);
//	gadget->CTK_setSelectCB(moviesControlsCB,(void*)HOMEIMAGE);

//keyboard control
////	mainApp->pages[mainApp->pageNumber].pageKey=pagekeyVideoCB;
makeKeyConf();
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
//mainApp->eventLoopCBIn=mainloopCB;
//mainApp->eventLoopCBOut=mainloopCB;
//mainApp->eventLoopCBIn=mainloopCB;

	do
		{
//
////control
//			retvs=mainApp->utils->CTK_findVar(prefsData,"keycontrol");
//		//	if(retvs.charVar.c_str()[0]=='\n')
//				fprintf(stderr,">>%p<<\n",retvs.charVar.c_str()[0]);

//fprintf(stderr,">>>>>>>>>>>>>>>>\n");
			mainApp->CTK_mainEventLoop(-250,false);
			//getMeta();
		}
	while (doQuitVideo==false);
	mainApp->CTK_setPage(FILMPAGE);
	mainApp->runEventLoop=true;
	mainApp->CTK_clearScreen();
	mainApp->CTK_updateScreen(mainApp,NULL);
	fflush(NULL);
}

