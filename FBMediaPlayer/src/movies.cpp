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

void makeMoviesPage(void)
{
	CTK_cursesGadgetClass	*gadget;
	int						gw=mainApp->maxCols/8;
	int						gh=gw/(fbInfo->charHeight/fbInfo->charWidth);
	int						yspread=2;
	int						yoffset=0;
	int						btnnumx=1;
	int						btnnumy=1;
	
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

//line2
	btnnumx=2;
//home
	gadget=newButtonSpread(1,mainApp->maxCols,1,mainApp->maxRows,gw,gh,3,yspread,btnnumx,btnnumy+yoffset,buttonNames[HOMEIMAGE][int(useFBImages)],useFBImages);
	gadget->CTK_setSelectCB(buttonselectCB,(void*)HOMEIMAGE);
}
