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
bool	isPaused=false;
bool	ignoreNL=false;

CTK_mainAppClass	*pausedma;

const char	*moviePlayerButtons[][2]={{"Play",DATADIR "/pixmaps/MusicPlayer/pause.png"},
{"Stop",DATADIR "/pixmaps/MusicPlayer/stop.png"},
{"Next",DATADIR "/pixmaps/MusicPlayer/next.png"},
{"Prev",DATADIR "/pixmaps/MusicPlayer/prev.png"},
};

void sendToVideoPipe(const std::string command)
{
	std::string	buffer="echo -e \"";
	buffer+=command + "\" >\"" + videoFifoName + "\" &";
	system(buffer.c_str());
}

bool movieControlsCB(void *inst,void *userdata)
{
	long	ud=(long)userdata;

	ignoreNL=true;

	switch(ud)
		{
			case HOMEIMAGE:
				doQuitVideo=true;
				fflush(NULL);
				break;

			case VIDEOSTART:
			
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
				break;

			case VIDEOSTOP:
				sendToVideoPipe("stop");
				vplaying=false;
				doQuitVideo=true;
				break;
			case VIDEOSKIPAHEAD:
				sendToVideoPipe("pausing_keep seek +60");
				break;
			case VIDEOSKIPBACK:
				sendToVideoPipe("pausing_keep seek -60.0" );
				break;
		}
	fflush(NULL);
	return(true);
}

bool moviePauseControlsCB(void *inst,void *userdata)
{
	long	ud=(long)userdata;
	bool	retval;

	if(inst!=NULL)
		pausedma->CTK_updateScreen(pausedma,NULL);
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
				break;
			case VIDEOSKIPAHEAD:
				retval=movieControlsCB(inst,userdata);
				break;
			case VIDEOSKIPBACK:
				retval=movieControlsCB(inst,userdata);
				break;
		}
	
	if(inst!=NULL)
		{
			pausedma->CTK_setDefaultGadget((CTK_cursesGadgetClass*)inst,false);
			pausedma->CTK_updateScreen(pausedma,NULL);
		}
	return(true);
}

bool pagekeyVideoCB(CTK_mainAppClass *app,void *userdata)
{
	if(app->readKey->inputBuffer.length()!=0)
		{
			switch(toupper(app->readKey->inputBuffer.at(0)))
				{
					case 'F':
						moviePauseControlsCB(NULL,(void*)VIDEOSKIPAHEAD);
						return(true);
						break;
					case 'R':
						moviePauseControlsCB(NULL,(void*)VIDEOSKIPBACK);
						return(true);
						break;
					case ' ':
						moviePauseControlsCB(NULL,(void*)VIDEOSTART);
						vpaused=true;
						return(true);
						break;
//					case 'Q':
//						//controlsCB(NULL,(void*)QUIT);
//						doQuitVideo=true;
//						//moviesControlsCB(NULL,(void*)QUIT);
//						//fprintf(stderr,"---->>>>\n");
//						break;
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
						moviePauseControlsCB(NULL,(void*)VIDEOSTOP);
						break;
					default:
						return(false);
				}
		}
	else
		return(false);
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

	btnnumx=0;
	for(int j=0;j<VIDEONOMORE;j++)
		{
			if(useFBImages==true)
				  gadget=ma.CTK_addNewFBImage(ma.utils->CTK_getGadgetPos(1,ma.maxCols,VIDEONOMORE,4,btnnumx+1),movieControlsSY,4,4,moviePlayerButtons[j][int(useFBImages)]);
			else
				gadget=ma.CTK_addNewButton(ma.utils->CTK_getGadgetPos(1,ma.maxCols,VIDEONOMORE,10,btnnumx+1),movieControlsSY,10,1,moviePlayerButtons[j][int(useFBImages)]);
			if(btnnumx==0)
				gadget0=gadget;
			gadget->CTK_setSelectCB(moviePauseControlsCB,(void*)btnnumx++);
		}

	ma.CTK_setDefaultGadget(gadget0,false);
	//ma.CTK_clearScreen();
	ma.CTK_updateScreen(&ma,NULL);
	fflush(NULL);
	vpaused=true;
	pausedma=&ma;
	ma.CTK_updateScreen(pausedma,NULL);
	do
	{
		ma.CTK_updateScreen(pausedma,NULL);
		ma.CTK_mainEventLoop(-10,false);
	}
	while (vpaused==true);
	ma.CTK_clearScreen();
}

void mainloopCB(void *mainc,void *data)
{
	CTK_mainAppClass *mp=(CTK_mainAppClass *)mainc;
	if((mp->readKey->isHexString==true) && (mp->readKey->specialKeyName==CTK_KEY_RETURN))
		{
			if(vpaused==false)
				sendToVideoPipe("pause");
			makeMoviePausePage();
		}
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
	ma.pages[0].pageKey=pagekeyVideoCB;

	do
		{
			ma.CTK_mainEventLoop(-250,false);
		}
	while(vplaying==true);
	mainApp->CTK_clearScreen();
	mainApp->CTK_updateScreen(mainApp,NULL);
	fflush(NULL);
	return(true);
}

void makeKeyConf(void)
{
	FILE		*fp;
	varsStruct	retvs;

	fp=fopen(TEMPFILES "/mplayerkeyconf","w");

	if(fp!=NULL)
		{
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
	videoMidWay=mainApp->maxCols/2;
	videoChooserWidth=((mainApp->maxCols/8)*5)-2;
	videoChooserHite=mainApp->maxRows-16;
	videoChooserHite=gh;
	videoChooserHite=mainApp->maxRows-16;
	
	videoList=new CTK_cursesChooserClass(mainApp,3,2,videoChooserWidth,videoChooserHite);
	videoList->CTK_setShowTypes(ANYTYPE);
	videoList->CTK_setShowHidden(false);
	videoList->CTK_selectFolder(mainApp,videoListFolder);
	videoList->CTK_setSelectCB(playVideoCB,NULL);
	mainApp->CTK_addChooserBox(videoList);

//line2
	if(useFBImages==true)
		{
			gw=gw/2;
			yspread=4;
			yoffset=2;
		}
	movieControlsSY=mainApp->maxRows-4;
	btnnumx=1;
	btnnumy=1;
	gadget=newButtonSpread(1,mainApp->maxCols,1,mainApp->maxRows,gw,gh,3,6,2,6,buttonNames[HOMEIMAGE][int(useFBImages)],useFBImages);
	gadget->CTK_setSelectCB(movieControlsCB,(void*)HOMEIMAGE);

//home

//keyboard control
//	mainApp->pages[mainApp->pageNumber].pageKey=pagekeyVideoCB;
	makeKeyConf();
}


void runVideo(void)
{
	videoList->CTK_selectFolder(mainApp,videoListFolder);
	videoList->CTK_updateList();
	mainApp->CTK_clearScreen();
	mainApp->CTK_updateScreen(mainApp,NULL);
	fflush(NULL);
	doQuitVideo=false;
	//mainApp->pages[mainApp->pageNumber].pageKey=pagekeyVideoCB;

	do
		{
			mainApp->CTK_mainEventLoop(-250,false);
		}
	while (doQuitVideo==false);
	mainApp->CTK_setPage(FILMPAGE);
	mainApp->runEventLoop=true;
	mainApp->CTK_clearScreen();
	mainApp->CTK_updateScreen(mainApp,NULL);
	fflush(NULL);
}

