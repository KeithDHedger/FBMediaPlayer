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

std::vector<varsStruct>		prefsData={
{"filmpath",CHARVAR,-1,false,-1,getenv("HOME") + std::string("/Videos")},
{"tvpath",CHARVAR,-1,false,-1,getenv("HOME") + std::string("/Videos")},
{"musicplaylistpath",CHARVAR,-1,false,-1,getenv("HOME") + std::string("/Music")},
{"musicfilespath",CHARVAR,-1,false,-1,getenv("HOME") + std::string("/Music")},
{"backdroppath",CHARVAR,-1,false,-1,getenv("HOME") + std::string("/Wallpapers")},
{"keypause",CHARVAR,-1,false,-1," "},
{"keystop",CHARVAR,-1,false,-1,"x"},
{"keyquit",CHARVAR,-1,false,-1,"q"},
{"keyfoward",CHARVAR,-1,false,-1,"f"},
{"keyreverse",CHARVAR,-1,false,-1,"r"},
{"keynext",CHARVAR,-1,false,-1,"."},
{"keyprev",CHARVAR,-1,false,-1,","},
{"keycontrol",CHARVAR,-1,false,-1,"\n"}
};
std::string					prefsPath;

CTK_cursesInputClass		*videoPath;
CTK_cursesInputClass		*tvPath;
CTK_cursesInputClass		*musicPlaylistPath;
CTK_cursesInputClass		*musicFilesPath;
CTK_cursesInputClass		*backDropPath;

void updatePrefs(void)
{
	prefsData.at(mainApp->utils->CTK_getVarEntry(prefsData,"filmpath")).charVar=videoPath->CTK_getText();
	prefsData.at(mainApp->utils->CTK_getVarEntry(prefsData,"tvpath")).charVar=tvPath->CTK_getText();
	prefsData.at(mainApp->utils->CTK_getVarEntry(prefsData,"musicplaylistpath")).charVar=musicPlaylistPath->CTK_getText();
	prefsData.at(mainApp->utils->CTK_getVarEntry(prefsData,"musicfilespath")).charVar=musicFilesPath->CTK_getText();
	prefsData.at(mainApp->utils->CTK_getVarEntry(prefsData,"backdroppath")).charVar=backDropPath->CTK_getText();
	mainApp->utils->CTK_saveVars(prefsPath.c_str(),prefsData);
}

void makePrefsPage(void)
{
	int						genx;
	int						geny;
	std::string				padstr;
	CTK_cursesButtonClass	*button;
	int						buttonwidth=10;
	varsStruct				vsitem;

	CTK_cursesGadgetClass	*gadget;
	int						gw=mainApp->maxCols/8;
	int						gh=gw/(fbInfo->charHeight/fbInfo->charWidth);
	int						yspread=4;
	int						yoffset=2;
	int						btnnumx=1;
	int						btnnumy=1;

	prefsPath=getenv("HOME");
	prefsPath+="/.FBMediaPlayer";
	mkdir(prefsPath.c_str(),0700);
	prefsPath+="/fbmediaplayerprefs.rc";

	if(access(prefsPath.c_str(),F_OK)==0)
		prefsData=mainApp->utils->CTK_loadVars(prefsPath.c_str(),false,prefsData);
	else
		mainApp->utils->CTK_saveVars(prefsPath.c_str(),prefsData);

mainApp->utils->CTK_saveVars("/tmp/2",prefsData);

	if(useFBImages==false)
		gw=10;

//return and save
	btnnumx=1;
	btnnumy++;
	if(useFBImages==true)
		{
			gw=gw/2;
			yspread=4;
			yoffset=2;
		}
//settings
	gadget=newButtonSpread(1,mainApp->maxCols,1,mainApp->maxRows,gw,gh,2,yspread,btnnumx++,btnnumy+yoffset,buttonNames[SAVEIMAGE][int(useFBImages)],useFBImages);
	gadget->CTK_setSelectCB(buttonselectCB,(void*)SAVEIMAGE);
//quit
	gadget=newButtonSpread(1,mainApp->maxCols,1,mainApp->maxRows,gw,gh,2,yspread,btnnumx,btnnumy+yoffset,buttonNames[HOMEIMAGE][int(useFBImages)],useFBImages);
	gadget->CTK_setSelectCB(buttonselectCB,(void*)HOMEIMAGE);

//set prefs
	buttonwidth=12;
	genx=2;
	geny=2;
//video path
	padstr=mainApp->utils->CTK_padString("Video Path",buttonwidth);
	button=mainApp->CTK_addNewButton(genx,geny,buttonwidth,1,padstr.c_str());
	button->CTK_setSelectCB(buttonselectCB,(void*)SETFILMPREFS);
	vsitem=mainApp->utils->CTK_findVar(prefsData,"filmpath");
	videoPath=mainApp->CTK_addNewInput(genx+buttonwidth+6,geny,buttonwidth*4,1,vsitem.charVar.c_str());
	videoPath->redrawAppWindow=true;
//tv path
	geny+=4;
	padstr=mainApp->utils->CTK_padString("TV Path",buttonwidth);
	button=mainApp->CTK_addNewButton(genx,geny,buttonwidth,1,padstr.c_str());
	button->CTK_setSelectCB(buttonselectCB,(void*)SETTVPREFS);
	vsitem=mainApp->utils->CTK_findVar(prefsData,"tvpath");
	tvPath=mainApp->CTK_addNewInput(genx+buttonwidth+6,geny,buttonwidth*4,1,vsitem.charVar.c_str());
//music playlist path
	geny+=4;
	padstr=mainApp->utils->CTK_padString("Playlists",buttonwidth);
	button=mainApp->CTK_addNewButton(genx,geny,buttonwidth,1,padstr.c_str());
	button->CTK_setSelectCB(buttonselectCB,(void*)SETMUSICPLAYLISTPREFS);
	vsitem=mainApp->utils->CTK_findVar(prefsData,"musicplaylistpath");
	musicPlaylistPath=mainApp->CTK_addNewInput(genx+buttonwidth+6,geny,buttonwidth*4,1,vsitem.charVar.c_str());
//music music path
//	geny+=4;
	padstr=mainApp->utils->CTK_padString("Files",buttonwidth);
	button=mainApp->CTK_addNewButton(genx-4+(buttonwidth*6),geny,buttonwidth,1,padstr.c_str());
	button->CTK_setSelectCB(buttonselectCB,(void*)SETMUSICFILESPREFS);
	vsitem=mainApp->utils->CTK_findVar(prefsData,"musicfilespath");
	musicFilesPath=mainApp->CTK_addNewInput(genx+2+(buttonwidth*7),geny,buttonwidth*4,1,vsitem.charVar.c_str());
//backdrop path
	geny+=4;
	padstr=mainApp->utils->CTK_padString("Backdrop",buttonwidth);
	button=mainApp->CTK_addNewButton(genx,geny,buttonwidth,1,padstr.c_str());
	button->CTK_setSelectCB(buttonselectCB,(void*)SETBACKDROPPREFS);
	vsitem=mainApp->utils->CTK_findVar(prefsData,"backdroppath");
	backDropPath=mainApp->CTK_addNewInput(genx+buttonwidth+6,geny,buttonwidth*4,1,vsitem.charVar.c_str());

}
