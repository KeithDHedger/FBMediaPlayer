/*
 *
 * ©K. D. Hedger. Sun  6 Jun 18:21:23 BST 2021 keithdhedger@gmail.com

 * This file (prefs.cpp) is part of FBMediaPlayer.

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
 
#include "prefs.h"

std::vector<varsStruct> filmPrefs={{"filmpath",CHARVAR,-1,false,-1,""}};
std::vector<varsStruct> tvPrefs;
std::vector<varsStruct> musicPrefs;

std::vector<varsStruct>	prefsData={{"filmpath",CHARVAR,-1,false,-1,getenv("HOME") + std::string("/Videos")},{"tvpath",CHARVAR,-1,false,-1,getenv("HOME") + std::string("/Videos")},{"musicpath",CHARVAR,-1,false,-1,getenv("HOME") + std::string("/Music")}};
std::string				prefsPath;

void makePrefsPage(void)
{
	int						genx;
	int						geny;
	std::string				padstr;
	CTK_cursesButtonClass	*button;
	CTK_cursesFBImageClass	*img;
	varsStruct				vsfilm;

	prefsPath=getenv("HOME");
	prefsPath+="/.FBMediaPlayer";
	mkdir(prefsPath.c_str(),0700);
	prefsPath+="/fbmediaplayerprefs.rc";

	if(access(prefsPath.c_str(),F_OK)==0)
		{
			prefsData=mainApp->utils->CTK_loadVars(prefsPath.c_str());
		}
	else
		{
			mainApp->utils->CTK_saveVars(prefsPath.c_str(),prefsData);
		}

fprintf(stderr,"prefsPath=%s\n",prefsPath.c_str());
mainApp->utils->CTK_saveVars("2",prefsData);

	mainApp->CTK_addPage();
	if(useimages==true)
		{
			int gw=mainApp->maxCols/8;
			int gh=gw/(fbInfo->charHeight/fbInfo->charWidth);
			geny=mainApp->utils->CTK_getGadgetPosX(1,mainApp->maxRows,4,1,3);
//home
			genx=mainApp->utils->CTK_getGadgetPos(1,mainApp->maxCols,3,gw,2);
			img=mainApp->CTK_addNewFBImage(genx,geny,gw/2,gw,imagePaths[HOMEIMAGE]);
			img->CTK_setSelectCB(buttonselectCB,(void*)HOMEIMAGE);
		}
	else
		{
			int buttonwidth=10;
//home
			geny=mainApp->utils->CTK_getGadgetPosX(1,mainApp->maxRows,4,1,3);
			genx=mainApp->utils->CTK_getGadgetPos(0,mainApp->maxCols,3,buttonwidth,2);
			padstr=mainApp->utils->CTK_padString("Home",buttonwidth);
			button=mainApp->CTK_addNewButton(genx,geny,buttonwidth,1,padstr.c_str());
			button->CTK_setSelectCB(buttonselectCB,(void*)HOMEIMAGE);
		}
}
