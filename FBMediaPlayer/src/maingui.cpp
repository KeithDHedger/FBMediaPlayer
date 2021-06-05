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

void makeMainPage(void)
{
	int						genx;
	int						geny;
	std::string				padstr;
	CTK_cursesButtonClass	*button;
	CTK_cursesFBImageClass	*img;

	if(useimages==true)
		{
			int gw=fbInfo->charWidth*3;
			int gh=gw/2;

//main buttons
			//genx=mainApp->utils->CTK_getGadgetPosX(1,mainApp->maxCols,3,gw,0);
			genx=mainApp->utils->CTK_getGadgetPos(1,mainApp->maxCols,3,gw,1);
			geny=mainApp->utils->CTK_getGadgetPos(1,mainApp->maxRows,2,gh,1);
			img=mainApp->CTK_addNewFBImage(genx,geny,gw,gw,imagePaths[FILMIMAGE]);
			img->CTK_setSelectCB(buttonselectCB,(void*)1);

//			genx=mainApp->utils->CTK_getGadgetPosX(1,mainApp->maxCols,3,gw,1);
			genx=mainApp->utils->CTK_getGadgetPos(1,mainApp->maxCols,3,gw,2);
			img=mainApp->CTK_addNewFBImage(genx,geny,gw,gw,imagePaths[TVIMAGE]);
			img->CTK_setSelectCB(buttonselectCB,(void*)2);


//			genx=mainApp->utils->CTK_getGadgetPosX(1,mainApp->maxCols,3,gw,2);
			genx=mainApp->utils->CTK_getGadgetPos(1,mainApp->maxCols,3,gw,3);
			img=mainApp->CTK_addNewFBImage(genx,geny,gw,gw,imagePaths[MUSICIMAGE]);
			img->CTK_setSelectCB(buttonselectCB,(void*)3);

//quit
			//genx=mainApp->utils->CTK_getGadgetPosX(1,mainApp->maxCols,1,gw,0);
			genx=mainApp->utils->CTK_getGadgetPos(2,mainApp->maxCols,1,gw,1);
			geny=mainApp->utils->CTK_getGadgetPos(1,mainApp->maxRows,2,gh,2);
			img=mainApp->CTK_addNewFBImage(genx,geny,gw,gw,imagePaths[OFFIMAGE]);
			img->CTK_setSelectCB(buttonselectCB,(void*)4);
		}
	else
		{
			int buttonwidth=10;

			genx=mainApp->utils->CTK_getGadgetPosX(2,mainApp->maxCols-4,3,buttonwidth,0);
			geny=mainApp->utils->CTK_getGadgetPosX(1,mainApp->maxRows,2,1,0);
			padstr=mainApp->utils->CTK_padString("Movies",buttonwidth);
			button=mainApp->CTK_addNewButton(genx,geny,buttonwidth,1,padstr.c_str());
			button->CTK_setSelectCB(buttonselectCB,(void*)1);

			genx=mainApp->utils->CTK_getGadgetPosX(2,mainApp->maxCols-4,3,buttonwidth,1);
			padstr=mainApp->utils->CTK_padString("TV Shows",buttonwidth);
			button=mainApp->CTK_addNewButton(genx,geny,buttonwidth,1,padstr.c_str());
			button->CTK_setSelectCB(buttonselectCB,(void*)2);

			genx=mainApp->utils->CTK_getGadgetPosX(2,mainApp->maxCols-4,3,buttonwidth,2);
			padstr=mainApp->utils->CTK_padString("Music",buttonwidth);
			button=mainApp->CTK_addNewButton(genx,geny,buttonwidth,1,padstr.c_str());
			button->CTK_setSelectCB(buttonselectCB,(void*)3);

			genx=mainApp->utils->CTK_getGadgetPosX(2,mainApp->maxCols-4,1,buttonwidth,0);
			geny=mainApp->utils->CTK_getGadgetPosX(1,mainApp->maxRows,2,1,1);
			padstr=mainApp->utils->CTK_padString("Quit",buttonwidth);
			button=mainApp->CTK_addNewButton(genx,geny,buttonwidth,1,padstr.c_str());
			button->CTK_setSelectCB(buttonselectCB,(void*)4);
		}
}
