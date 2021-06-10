/*
 *
 * ©K. D. Hedger. Sun  6 Jun 18:20:54 BST 2021 keithdhedger@gmail.com

 * This file (music.cpp) is part of FBMediaPlayer.

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
 
#include "music.h"

LFSTK_findClass				*files=new LFSTK_findClass();;
CTK_cursesChooserClass		*playLists;
CTK_cursesListBoxClass		*songList;
CTK_cursesFBImageClass		*image;
CTK_cursesFBImageClass		*albumArt;
CTK_cursesTextBoxClass		*nowPlaying;

const char					*folder="./";
int							midWay;
int							chooserWidth;
int							songsWidth;

std::string					resources=DATADIR "/pixmaps";
int							dialogWidth;
int							chooserHite;
int							songsHite;
int							controlsSY;
int							artSY;
int							artHite;
std::vector<char*>			songs;
bool						playing=false;
bool						paused=false;
char						*oldfile=NULL;
bool						updated=false;
bool						doQuitMusic=false;

char* oneLiner(const char* fmt,...)
{
	FILE	*fp;
	va_list	ap;
	char	*buffer,*subbuffer;

	buffer=(char*)alloca(PATH_MAX);
	subbuffer=(char*)alloca(PATH_MAX);

	buffer[0]=0;
	subbuffer[0]=0;
	va_start(ap, fmt);
	while (*fmt)
		{
			subbuffer[0]=0;
			if(fmt[0]=='%')
				{
					fmt++;
					switch(*fmt)
						{
							case 's':
								sprintf(subbuffer,"%s",va_arg(ap,char*));
								break;
							case 'i':
								sprintf(subbuffer,"%i",va_arg(ap,int));
								break;
							case '%':
								sprintf(subbuffer,"%%");
								break;
							default:
								sprintf(subbuffer,"%c",fmt[0]);
								break;
						}
				}
			else
				sprintf(subbuffer,"%c",fmt[0]);
			strcat(buffer,subbuffer);
			fmt++;
		}
	va_end(ap);

	fp=popen(buffer,"r");
	if(fp!=NULL)
		{
			buffer[0]=0;
			fgets(buffer,PATH_MAX,fp);
			if(strlen(buffer)>0)
				{
					if(buffer[strlen(buffer)-1] =='\n')
						buffer[strlen(buffer)-1]=0;
				}
			pclose(fp);
			return(strdup(buffer));
		}
	return(NULL);
}

void sendToPipe(const std::string command)
{
	std::string	buffer="echo -e \"";
	buffer+=command + "\" >\"" + fifoName + "\" &";
	system(buffer.c_str());
}

void getMeta(void)
{
	char	*filename;
	char	*album;
	char	*title;
	char	*artist;
	char	*all;
	char	*jpeg;

	if((playing==false) || (paused==true) || (doQuitMusic==true))
		return;

	commandString="get_property path\\nget_meta_album\\nget_meta_title\\nget_meta_artist";
	sendToPipe(commandString);

	filename=oneLiner("tail -n4 '%s' |sed -n '1p'|awk -F= '{print $2}'",outName.c_str());

	if(strcmp(filename,"(null)")==0)
		{
			for(int j=0;j<songs.size();j++)
				free(songs[j]);
			songs.clear();
			songList->CTK_clearList();
			albumArt->CTK_newFBImage(chooserWidth+6,artSY,artHite*2,artHite,"",false);
			nowPlaying->CTK_updateText("");
			mainApp->CTK_setDefaultGadget(playLists->lb);
			mainApp->CTK_clearScreen();
			mainApp->CTK_updateScreen(mainApp,(void*)1);
			playing=false;
			paused=false;
			doQuitMusic=true;
			return;
		}

	if(oldfile!=NULL)
		{
			if(strcmp(filename,oldfile)==0)
				{
					while(updated==false)
						{
							album=oneLiner("tail -n4 '%s' |sed -n '2p'|awk -F= '{print $2}'|sed -n 's/^.\\(.*\\).$/\\1/p'",outName.c_str());
							title=oneLiner("tail -n4 '%s' |sed -n '3p'|awk -F= '{print $2}'|sed -n 's/^.\\(.*\\).$/\\1/p'",outName.c_str());
							artist=oneLiner("tail -n4 '%s' |sed -n '4p'|awk -F= '{print $2}'|sed -n 's/^.\\(.*\\).$/\\1/p'",outName.c_str());
							asprintf(&all,"Album:  %s\nArtist: %s\nSong:   %s\n",album,artist,title);

							nowPlaying->CTK_updateText(all,false,false);
							updated=true;
							free(title);
							free(album);
							free(artist);
							free(all);

							commandString=":>'";
							commandString+=outName + "'";
							system(commandString.c_str());
							asprintf(&jpeg,"%s/folder.jpg",dirname(filename));
							albumArt->CTK_newFBImage(chooserWidth+6,artSY,artHite*2,artHite,jpeg,false);
							mainApp->CTK_updateScreen(mainApp,NULL);
							free(jpeg);
						}

					free(filename);
					commandString=":>'";
					commandString+=outName + "'";
					system(commandString.c_str());
					return;
				}
		}
	if(oldfile!=NULL)
		free(oldfile);
	oldfile=strdup(filename);
	if(filename!=NULL)
		free(filename);
	updated=false;
}

bool selectSongCB(void *inst,void *userdata)
{
	CTK_cursesListBoxClass	*sl=static_cast<CTK_cursesListBoxClass*>(inst);

	if(sl->listItems.size()==0)
		return(true);

	commandString="p\\npausing_keep_force loadlist \\\"";
	commandString+=playLists->filePath + "\\\"";
	sendToPipe(commandString);

	if((long)sl->listItems[sl->listItemNumber]->userData!=0)
		{
			commandString="pausing_keep_force pt_step ";
			commandString+=std::to_string((long)sl->listItems[sl->listItemNumber]->userData) + "\\np";
			sendToPipe(commandString);
		}
	else
		sendToPipe("p");

	playing=true;
	paused=false;
	return(true);
}

bool controlsCB(void *inst,void *userdata)
{
	long	ud=(long)userdata;

	switch(ud)
		{
			case START:
				if(playing==false)
					return(true);
				commandString="loadlist \\\"";
				commandString+=playLists->filePath + "\\\"";
				sendToPipe(commandString);
				playing=true;
				paused=false;
				break;

			case PREVIOUS:
				if(playing==false)
					return(true);
				sendToPipe("pt_step -1");
				paused=false;
				break;

			case PLAY:
				if(playing==true)
					{
						sendToPipe("p");
						paused=!paused;
					}
				if(playing==true)
					return(true);
				break;

			case STOP:
				if(playing==false)
					return(true);
				for(int j=0;j<songs.size();j++)
					free(songs[j]);
				songs.clear();
				songList->CTK_clearList();
				sendToPipe("stop");
				albumArt->CTK_newFBImage(chooserWidth+6,artSY,artHite*2,artHite,"",false);
				nowPlaying->CTK_updateText("");
				mainApp->CTK_setDefaultGadget(playLists->lb);
				mainApp->CTK_clearScreen();
				mainApp->CTK_updateScreen(mainApp,(void*)1);
				playing=false;
				paused=false;
				break;

			case PAUSE:
				if(playing==false)
					return(true);
				sendToPipe("p");
				paused=!paused;
				break;

			case END:
				if(playing==false)
					return(true);
				commandString="p\\npausing_keep_force loadlist \\\"";
				commandString+=playLists->filePath + "\\\"";
				sendToPipe(commandString);
				commandString="pausing_keep_force pt_step ";
				commandString+=std::to_string(songs.size()-1) + "\\np";
				sendToPipe(commandString);
				playing=true;
				paused=false;
				break;

			case NEXT:
				if(playing==false)
					return(true);
				sendToPipe("pt_step 1");
				paused=false;
				break;

			case QUIT:
				for(int j=0;j<songs.size();j++)
					free(songs[j]);
				songs.clear();
				songList->CTK_clearList();
				sendToPipe("stop");
				albumArt->CTK_newFBImage(chooserWidth+6,artSY,artHite*2,artHite,"",false);
				nowPlaying->CTK_updateText("");
				mainApp->CTK_setDefaultGadget(playLists->lb);
				mainApp->CTK_clearScreen();
				mainApp->CTK_updateScreen(mainApp,(void*)1);
				playing=false;
				paused=false;
				doQuitMusic=true;
				break;
		}
	return(true);
}

bool playListsCB(void *inst,void *userdata)
{
	CTK_cursesChooserClass	*ch=static_cast<CTK_cursesChooserClass*>(inst);
	FILE					*fd=NULL;
	char					buffer[PATH_MAX];
	char					buffer2[PATH_MAX];

	if((ch->files->data[ch->lb->listItemNumber].fileType==FOLDERTYPE) || (ch->files->data[ch->lb->listItemNumber].fileType==FILELINKTYPE))
		return(true);
	folder=ch->folderPath.c_str();
	for(int j=0;j<songs.size();j++)
		free(songs[j]);
	songs.clear();
	songList->CTK_clearList();

	fd=fopen(ch->filePath.c_str(),"r");
	if(fd!=NULL)
		{
			while(feof(fd)==0)
				{
					buffer[0]=0;
					fgets(buffer,2048,fd);
					if(strlen(buffer)>0)
						{
							buffer[strlen(buffer)-1]=0;
							sprintf(buffer2,"%s/%s",folder,buffer);
							songs.push_back(strdup(buffer2));
						}
				}
			fclose(fd);
		}
	for(long j=0;j<songs.size();j++)
		{
			char	*ptr=strrchr(songs[j],'/');
			songList->CTK_addListItem(++ptr,(void*)j);
		}

	commandString="loadlist '";
	commandString+=ch->filePath + "'";
	sendToPipe(commandString);
	playing=true;
	return(true);
}

void makeMusicPage(void)
{
	char					imagepath[PATH_MAX];

	mainApp->CTK_addPage();
	midWay=mainApp->maxCols/2;
	dialogWidth=mainApp->maxCols-4;
	chooserWidth=((mainApp->maxCols/8)*5)-2;
	chooserHite=mainApp->maxRows-16;
	controlsSY=mainApp->maxRows-5;
	songsWidth=mainApp->maxCols-chooserWidth-7;
	songsHite=(chooserHite+4)/2;
	artSY=songsHite+4;
	artHite=songsHite;
	fifoName="/tmp/mplayerfifo" + std::to_string(getpid());
	outName="/tmp/mplayerout" + std::to_string(getpid());
	commandString="mkfifo '";
	commandString+=fifoName + "'";
	system(commandString.c_str());

//start mplayer
	commandString="";
	commandString+="mplayer -quiet -slave -input file='" + fifoName + "' -idle >'" + outName + "' 2>/dev/null &";
	system(commandString.c_str());

	mainApp->colours.fancyGadgets=true;
	mainApp->colours.boxType=NOBOX;
	mainApp->colours.textBoxType=INBOX;
	mainApp->colours.windowBackCol=BACK_WHITE;
	mainApp->colours.backCol=BACK_WHITE;
	mainApp->colours.foreCol=FORE_BLACK;
	playLists=new CTK_cursesChooserClass(mainApp,3,2,chooserWidth,chooserHite);
	playLists->CTK_setShowFileTypes(".m3u;");
	playLists->CTK_setShowTypes(ANYTYPE);
	playLists->CTK_setShowHidden(false);
	playLists->CTK_selectFolder(mainApp,folder);
	playLists->CTK_setSelectCB(playListsCB,NULL);
	mainApp->CTK_addChooserBox(playLists);

	songList=mainApp->CTK_addNewListBox(chooserWidth+6,2,songsWidth,songsHite);
	songList->CTK_setSelectCB(selectSongCB,NULL);

	nowPlaying=mainApp->CTK_addNewTextBox(3,chooserHite+4,chooserWidth,3,"");
	nowPlaying->CTK_setSelectable(false);

	sprintf(imagepath,"%s/MusicPlayer/start.png",resources.c_str());
	image=mainApp->CTK_addNewFBImage(mainApp->utils->CTK_getGadgetPosX(midWay-(dialogWidth/2),dialogWidth,CONTROLCNT,4,0),controlsSY,4,4,imagepath);
	image->CTK_setSelectCB(controlsCB,(void*)START);
	sprintf(imagepath,"%s/MusicPlayer/prev.png",resources.c_str());
	image=mainApp->CTK_addNewFBImage(mainApp->utils->CTK_getGadgetPosX(midWay-(dialogWidth/2),dialogWidth,CONTROLCNT,4,1),controlsSY,4,4,imagepath);
	image->CTK_setSelectCB(controlsCB,(void*)PREVIOUS);
	sprintf(imagepath,"%s/MusicPlayer/play.png",resources.c_str());
	image=mainApp->CTK_addNewFBImage(mainApp->utils->CTK_getGadgetPosX(midWay-(dialogWidth/2),dialogWidth,CONTROLCNT,4,2),controlsSY,4,4,imagepath);
	image->CTK_setSelectCB(controlsCB,(void*)PLAY);
	sprintf(imagepath,"%s/MusicPlayer/stop.png",resources.c_str());
	image=mainApp->CTK_addNewFBImage(mainApp->utils->CTK_getGadgetPosX(midWay-(dialogWidth/2),dialogWidth,CONTROLCNT,4,3),controlsSY,4,4,imagepath);
	image->CTK_setSelectCB(controlsCB,(void*)STOP);
	sprintf(imagepath,"%s/MusicPlayer/pause.png",resources.c_str());
	image=mainApp->CTK_addNewFBImage(mainApp->utils->CTK_getGadgetPosX(midWay-(dialogWidth/2),dialogWidth,CONTROLCNT,4,4),controlsSY,4,4,imagepath);
	image->CTK_setSelectCB(controlsCB,(void*)PAUSE);
	sprintf(imagepath,"%s/MusicPlayer/next.png",resources.c_str());
	image=mainApp->CTK_addNewFBImage(mainApp->utils->CTK_getGadgetPosX(midWay-(dialogWidth/2),dialogWidth,CONTROLCNT,4,5),controlsSY,4,4,imagepath);
	image->CTK_setSelectCB(controlsCB,(void*)NEXT);
	sprintf(imagepath,"%s/MusicPlayer/end.png",resources.c_str());
	image=mainApp->CTK_addNewFBImage(mainApp->utils->CTK_getGadgetPosX(midWay-(dialogWidth/2),dialogWidth,CONTROLCNT,4,6),controlsSY,4,4,imagepath);
	image->CTK_setSelectCB(controlsCB,(void*)END);

	sprintf(imagepath,"%s/MusicPlayer/quit.png",resources.c_str());
	image=mainApp->CTK_addNewFBImage(mainApp->utils->CTK_getGadgetPosX(midWay-(dialogWidth/2),dialogWidth,CONTROLCNT,4,7),controlsSY,4,4,imagepath);
	image->CTK_setSelectCB(controlsCB,(void*)QUIT);

	albumArt=mainApp->CTK_addNewFBImage(chooserWidth+6,artSY,artHite,artHite,NULL,false);
	albumArt->CTK_setSelectable(false);
}

void runMusic(void)
{
	folder=musicPath->CTK_getText();
	playLists->CTK_selectFolder(mainApp,musicPath->CTK_getText());
	playLists->CTK_updateList();
	mainApp->CTK_clearScreen();//TODO//
	fflush(NULL);
	mainApp->CTK_updateScreen(mainApp,NULL);//TODO//
	doQuitMusic=false;
	do
		{
			mainApp->CTK_mainEventLoop(-250,false);
			getMeta();
		}
	while (doQuitMusic==false);
	mainApp->runEventLoop=true;
	free(oldfile);
	oldfile=NULL;
}
