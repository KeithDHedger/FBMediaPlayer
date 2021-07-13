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

bool pagekeyVideoCB(CTK_mainAppClass *app,void *userdata)
{
	if(app->readKey->inputBuffer.length()!=0)
		{
			switch(toupper(app->readKey->inputBuffer.at(0)))
				{
//					case 'F':
//						sendToPipe("seek +30");
//						return(true);
//						break;
//					case 'R':
//						sendToPipe("seek -30");
//						return(true);
//						break;
//					case ' ':
//						controlsCB(NULL,(void*)PAUSE);
//						break;
					case 'Q':
						//controlsCB(NULL,(void*)QUIT);
						doQuitVideo=true;
						fprintf(stderr,"---->>>>\n");
						break;
//					case 'N':
//					case '.':
//						controlsCB(NULL,(void*)NEXT);
//						break;
//					case 'P':
//					case ',':
//						controlsCB(NULL,(void*)PREVIOUS);
//						break;
//					case 'S':
//					case 'X':
//						controlsCB(NULL,(void*)STOP);
//						break;
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
fprintf(stderr,"here\n");
//	do
//		{
//			mainApp->CTK_mainEventLoop(-250,false);
//			//getMeta();
//		}
//	while (doQuitVideo==false);
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

	mainApp->colours.fancyGadgets=true;
	mainApp->colours.boxType=NOBOX;
	mainApp->colours.textBoxType=INBOX;
	mainApp->colours.windowBackCol=BACK_WHITE;
	mainApp->colours.backCol=BACK_WHITE;
	mainApp->colours.foreCol=FORE_BLACK;
	videoList=new CTK_cursesChooserClass(mainApp,3,2,videoChooserWidth,videoChooserHite);
	videoList->CTK_setShowTypes(ANYTYPE);
	videoList->CTK_setShowHidden(false);
	videoList->CTK_selectFolder(mainApp,videoListFolder);
	videoList->CTK_setSelectCB(playVideoCB,NULL);
	mainApp->CTK_addChooserBox(videoList);

//line2
	btnnumx=2;
//home
	gadget=newButtonSpread(1,mainApp->maxCols,1,mainApp->maxRows,gw,gh,3,yspread,btnnumx,btnnumy+yoffset,buttonNames[HOMEIMAGE][int(useFBImages)],useFBImages);
	gadget->CTK_setSelectCB(buttonselectCB,(void*)HOMEIMAGE);

//keyboard control
	mainApp->pages[mainApp->pageNumber].pageKey=pagekeyVideoCB;
}

void runVideo(void)
{
return;
	videoList->CTK_selectFolder(mainApp,videoListFolder);
	videoList->CTK_updateList();
	//mainApp->CTK_clearScreen();
	//fflush(NULL);
	//mainApp->CTK_updateScreen(mainApp,NULL);
	doQuitVideo=false;
	//videoList->CTK_setVisible(false);
	//mainApp->CTK_clearScreen();
	return;
	do
		{
			mainApp->CTK_mainEventLoop(-250,false);
			//getMeta();
		}
	while (doQuitVideo==false);
	mainApp->CTK_setPage(MAINPAGE);
	mainApp->runEventLoop=true;
	
}

