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

void setFromBoxPath(CTK_cursesInputClass *box,const char *varname,bool isfolder)
{
	boost::filesystem::path folder=box->CTK_getText();
	if (boost::filesystem::is_regular_file(folder))
		folder.remove_filename();

	if(access(folder.c_str(),F_OK)!=0)
		folder=getenv("HOME");
	if(isfolder==true)
		mainApp->utils->CTK_fileChooserDialog(folder.c_str(),CUOPENFOLDER);
	else
		mainApp->utils->CTK_fileChooserDialog(folder.c_str(),CUOPENFILE);
	if(mainApp->utils->dialogReturnData.isValidData==true)
		{ 
			box->CTK_setText(mainApp->utils->dialogReturnData.stringValue.c_str());
			if(mainApp->utils->CTK_getVarEntry(prefsData,varname)==-1)
				prefsData.push_back({varname,CHARVAR,-1,false,-1,getenv("HOME")});
			prefsData.at(mainApp->utils->CTK_getVarEntry(prefsData,varname)).charVar=box->CTK_getText();
			mainApp->utils->CTK_saveVars(prefsPath.c_str(),prefsData);
		}
}

bool buttonselectCB(void *inst,void *userdata)
{
	fflush(NULL);

	switch((long)userdata)
		{
			case OFFIMAGE:
				mainApp->runEventLoop=false;
				break;
			case HOMEIMAGE:
				//mainApp->runEventLoop=true;
				mainApp->CTK_setPage(MAINPAGE);
				break;
			case TVIMAGE:
				//mainApp->CTK_setPage(TVPAGE);
			case FILMIMAGE:
				mainApp->CTK_setPage(FILMPAGE);
				videoList->CTK_setShowFileTypes(".mp4;.iso;.mpeg;.mpg;.avi;");
				videoList->CTK_setCBUserData((void*)FILMIMAGE);
				videoListFolder=prefsData.at(mainApp->utils->CTK_getVarEntry(prefsData,"filmpath")).charVar.c_str();
				videoList->CTK_selectFolder(mainApp,videoListFolder);
				videoList->CTK_updateList();
				mainApp->CTK_updateScreen(mainApp,NULL);
				fflush(NULL);

				runVideo();
				mainApp->CTK_setPage(MAINPAGE);
				mainApp->CTK_updateScreen(mainApp,NULL);
				break;

//music	
			case MUSICIMAGE:
				mainApp->CTK_setPage(MUSICPAGE);
				break;

			case PLAYLISTIMAGE:
				mainApp->CTK_setPage(PLAYLISTSPAGE);
				playLists->files->LFSTK_setIgnoreNavLinks(true);
				playLists->CTK_setShowFileTypes(".m3u;");
				playLists->CTK_setCBUserData((void*)PLAYLISTIMAGE);
				musicFolder=prefsData.at(mainApp->utils->CTK_getVarEntry(prefsData,"musicplaylistpath")).charVar.c_str();
				runMusic();
				//system("clear");
				mainApp->CTK_setPage(MUSICPAGE);
				//mainApp->CTK_clearScreen();
				mainApp->CTK_updateScreen(mainApp,NULL);
				fflush(NULL);

				break;

			case MUSICFILEIMAGE:
				mainApp->CTK_setPage(PLAYLISTSPAGE);
				playLists->files->LFSTK_setIgnoreNavLinks(false);
				playLists->CTK_setShowFileTypes(".mp3;.flac;.m4a;.mp4;");
				playLists->CTK_setCBUserData((void*)MUSICFILEIMAGE);
				musicFolder=prefsData.at(mainApp->utils->CTK_getVarEntry(prefsData,"musicfilespath")).charVar.c_str();
				runMusic();
				mainApp->CTK_setPage(MUSICPAGE);
				break;

			case PREFSIMAGE:
				mainApp->CTK_setPage(PREFSPAGE);
				break;
//prefs
			case SETFILMPREFS:
				setFromBoxPath(videoPath,"filmpath",true);
				break;

			case SETTVPREFS:
				setFromBoxPath(tvPath,"tvpath",true);
				break;

//playlists
			case SETMUSICPLAYLISTPREFS:
				setFromBoxPath(musicPlaylistPath,"musicplaylistpath",true);
				break;
//music files
			case SETMUSICFILESPREFS:
				setFromBoxPath(musicFilesPath,"musicfilespath",true);
				break;
//backdrop
			case SETBACKDROPPREFS:
				setFromBoxPath(backDropPath,"backdroppath",false);
//backdrop
				if(useFBImages==true)
					mainApp->CTK_setFBBackDrop(backDropPath->CTK_getText());
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
	return(true);
}

