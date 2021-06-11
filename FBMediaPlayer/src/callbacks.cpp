/*
 *
 * ©K. D. Hedger. Fri  4 Jun 11:44:03 BST 2021 keithdhedger@gmail.com

 * This file (callbacks.cpp) is part of FBMediaPlayer.

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

#include "callbacks.h"

void setFromBoxPath(CTK_cursesInputClass *box,const char *varname)
{
	const char	*folder;

	folder=box->CTK_getText();
	if(access(folder,F_OK)!=0)
		folder=getenv("HOME");
	mainApp->utils->CTK_fileChooserDialog(folder,CUOPENFOLDER);
	if(mainApp->utils->dialogReturnData.isValidData==true)
		{ 
			box->CTK_setText(mainApp->utils->dialogReturnData.stringValue.c_str());
			prefsData.at(mainApp->utils->CTK_getVarEntry(prefsData,varname)).charVar=box->CTK_getText();
			mainApp->utils->CTK_saveVars(prefsPath.c_str(),prefsData);
		}
}

bool buttonselectCB(void *inst,void *userdata)
{
	//CTK_cursesGadgetClass	*bc;
	//const char	*folder;

	//if(useFBImages==true)
		{
			//bc=static_cast<CTK_cursesGadgetClass*>(inst);
			fflush(NULL);
		}

	switch((long)userdata)
		{
			case OFFIMAGE:
				mainApp->runEventLoop=false;
				break;
			case HOMEIMAGE:
				mainApp->CTK_setPage(MAINPAGE);
				break;
			case FILMIMAGE:
				mainApp->CTK_setPage(FILMPAGE);
				break;
			case TVIMAGE:
				mainApp->CTK_setPage(TVPAGE);
				break;
			case MUSICIMAGE:
				mainApp->CTK_setPage(MUSICPAGE);
				runMusic();
				mainApp->CTK_setPage(MAINPAGE);
				break;
			case PREFSIMAGE:
				mainApp->CTK_setPage(PREFSPAGE);
				break;
//prefs
			case SETFILMPREFS:
				setFromBoxPath(videoPath,"filmpath");
				break;

			case SETTVPREFS:
				setFromBoxPath(tvPath,"tvpath");
				break;

			case SETMUSICPREFS:
				setFromBoxPath(musicPath,"musicpath");
				break;
//save prefs
			case SAVEIMAGE:
				updatePrefs();
				mainApp->CTK_setPage(MAINPAGE);
				break;

			default:
				break;
		}
	mainApp->CTK_updateScreen(mainApp,NULL);//TODO//
	//fprintf(stderr,"button=%i x=%i y=%i\n",(long)userdata,bc->sx,bc->sy);
	return(true);
}

