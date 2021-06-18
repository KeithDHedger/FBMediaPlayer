/*
 *
 * ©K. D. Hedger. Fri  4 Jun 11:36:28 BST 2021 keithdhedger@gmail.com

 * This file (maingui.cpp) is part of FBMediaPlayer.

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

#include "maingui.h"

CTK_cursesGadgetClass* newButtonSpread(int bx,int bw,int by,int bh,int gadw,int gadh,int gadcntx,int gadcnty,int gadnumx,int gadnumy,const char *path,bool useimage)
{
	CTK_cursesButtonClass	*button=NULL;
	CTK_cursesFBImageClass	*img=NULL;

	int						genx;
	int						geny;
	std::string				padstr;

	genx=mainApp->utils->CTK_getGadgetPos(bx,bw,gadcntx,gadw,gadnumx);
	if(useFBImages==true)
		{
			geny=mainApp->utils->CTK_getGadgetPos(by,bh,gadcnty,gadh,gadnumy);
			img=mainApp->CTK_addNewFBImage(genx,geny,gadw,gadh,path);
			return(img);
		}
	else
		{
			geny=mainApp->utils->CTK_getGadgetPos(by,bh,gadcnty,1,gadnumy);
			padstr=mainApp->utils->CTK_padString(path,gadw);
			button=mainApp->CTK_addNewButton(genx,geny,gadw,1,padstr.c_str());
			return(button);
		}
	return(NULL);
}

void makeMainPage(void)
{
	CTK_cursesGadgetClass	*gadget;

	int gw=mainApp->maxCols/8;
	int gh=gw/(fbInfo->charHeight/fbInfo->charWidth);
	int	yspread=2;
	int yoffset=0;
	int	btnnumx=1;
	int	btnnumy=1;

	mainApp->CTK_addPage();

	if(useFBImages==false)
		gw=10;

//line1
//film
	gadget=newButtonSpread(1,mainApp->maxCols,1,mainApp->maxRows,gw,gh,3,yspread,btnnumx++,btnnumy,buttonNames[FILMIMAGE][int(useFBImages)],useFBImages);
	gadget->CTK_setSelectCB(buttonselectCB,(void*)FILMIMAGE);
//tv
	gadget=newButtonSpread(1,mainApp->maxCols,1,mainApp->maxRows,gw,gh,3,yspread,btnnumx++,btnnumy,buttonNames[TVIMAGE][int(useFBImages)],useFBImages);
	gadget->CTK_setSelectCB(buttonselectCB,(void*)TVIMAGE);
//music
	gadget=newButtonSpread(1,mainApp->maxCols,1,mainApp->maxRows,gw,gh,3,yspread,btnnumx,btnnumy,buttonNames[MUSICIMAGE][int(useFBImages)],useFBImages);
	gadget->CTK_setSelectCB(buttonselectCB,(void*)MUSICIMAGE);

//line2
	btnnumx=1;
	btnnumy++;
	if(useFBImages==true)
		{
			gw=gw/2;
			yspread=4;
			yoffset=2;
		}
//settings
	gadget=newButtonSpread(1,mainApp->maxCols,1,mainApp->maxRows,gw,gh,2,yspread,btnnumx++,btnnumy+yoffset,buttonNames[PREFSIMAGE][int(useFBImages)],useFBImages);
	gadget->CTK_setSelectCB(buttonselectCB,(void*)PREFSIMAGE);
//quit
	gadget=newButtonSpread(1,mainApp->maxCols,1,mainApp->maxRows,gw,gh,2,yspread,btnnumx,btnnumy+yoffset,buttonNames[OFFIMAGE][int(useFBImages)],useFBImages);
	gadget->CTK_setSelectCB(buttonselectCB,(void*)OFFIMAGE);
}
