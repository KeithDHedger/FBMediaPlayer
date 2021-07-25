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
CTK_cursesProgressBarClass	*progressIndicator;

const char	*musicPlayerButtons[][2]={{"Start",DATADIR "/pixmaps/MusicPlayer/start.png"},
{"Prev",DATADIR "/pixmaps/MusicPlayer/prev.png"},
{"Play",DATADIR "/pixmaps/MusicPlayer/play.png"},
{"Stop",DATADIR "/pixmaps/MusicPlayer/stop.png"},
{"Pause",DATADIR "/pixmaps/MusicPlayer/pause.png"},
{"Next",DATADIR "/pixmaps/MusicPlayer/next.png"},
{"Last",DATADIR "/pixmaps/MusicPlayer/end.png"},
{"Quit",DATADIR "/pixmaps/MusicPlayer/quit.png"},
};

const char					*playListFolder="./";
const char					*musicFilesFolder="./";
const char					*musicFolder="./";
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

std::vector<std::string> runApplication(std::string com)
{
	FILE						*fp;
	char						*buffer=(char*)alloca(1024);
	std::vector<std::string>	splits;
	std::string					retstr="";

	fp=popen(com.c_str(),"r");
	if(fp!=NULL)
		{
			buffer[0]=0;
			while(fgets(buffer,1024,fp))
				retstr+=buffer;
			pclose(fp);
		}
	boost::algorithm::split(splits,retstr,boost::is_any_of("\n"));

	return(splits);
}

void sendToPipe(const std::string command)
{
	std::string	buffer="echo -e \"";
	buffer+=command + "\" >\"" + musicFifoName + "\" &";
	system(buffer.c_str());
}

double oldval=0.0;

bool playListsCB(void *inst,void *userdata)
{
	CTK_cursesChooserClass	*ch=static_cast<CTK_cursesChooserClass*>(inst);
	FILE					*fd=NULL;
	char					buffer[PATH_MAX];
	char					buffer2[PATH_MAX];


	if((ch->files->data[ch->lb->listItemNumber].fileType==FOLDERTYPE) || (ch->files->data[ch->lb->listItemNumber].fileType==FILELINKTYPE))
		return(true);
	playListFolder=ch->folderPath.c_str();
	songList->CTK_setItem(0xdeadbeef,false);
	for(int j=0;j<songs.size();j++)
		free(songs[j]);
	songs.clear();
	songList->CTK_clearList();

	if(ch->CTK_getCBUserData()==(void*)MUSICFILEIMAGE)
		{
			sprintf(buffer,": > '%s'",tempPlaylist);
			system(buffer);
			for(int j=ch->lb->listItemNumber;j<ch->lb->listItems.size();j++)
				{
					sprintf(buffer2,"%s/%s",playListFolder,ch->lb->listItems.at(j)->label.c_str());
					songs.push_back(strdup(buffer2));
					sprintf(buffer,"echo -e '%s' >> '%s'",buffer2,tempPlaylist);
					system(buffer);
				}
			playLists->filePath=tempPlaylist;
		}
	else
		{
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
									sprintf(buffer2,"%s/%s",playListFolder,buffer);
									songs.push_back(strdup(buffer2));
								}
						}
					fclose(fd);
				}
		}

	for(long j=0;j<songs.size();j++)
		{
			char	*ptr=strrchr(songs[j],'/');
			songList->CTK_addListItem(++ptr,(void*)j);
		}

	commandString="loadlist '";
	if(ch->CTK_getCBUserData()==(void*)MUSICFILEIMAGE)
		{
			commandString+=tempPlaylist;
			commandString+="'";
		}
	else
		{
			commandString+=ch->filePath + "'";
		}

	sendToPipe(commandString);
	playing=true;
	songList->CTK_drawGadget();
	fflush(NULL);
	return(true);
}

void getMeta(void)
{
	std::string album="";
	std::string title="";
	std::string artist="";
	std::string percent="";
	std::string songlen="";
	std::string all="";

	if((playing==false) || (paused==true) || (doQuitMusic==true))
		return;

	sendToPipe("get_property path\\nget_file_name\\nget_meta_album\\nget_meta_title\\nget_meta_artist\\nget_time_pos\\nget_time_length");

	std::vector<std::string> lines=runApplication(str(boost::format("tail -n7 '%s'") %outName));
	if(lines.size()==8)
		{
			if(lines.at(0).find("ANS_path=") != 0)
				return;
		}
	else
		return;

	boost::filesystem::path folder=lines.at(0).substr(lines.at(0).find("=")+1);
	if (boost::filesystem::is_regular_file(folder))
		folder.remove_filename();
	folder+="/folder.jpg";

	if(oldfile!=NULL)
		{
			if(lines.at(0).compare(oldfile)==0)
				{
					percent=lines.at(5).substr(lines.at(5).find("=")+1,lines.at(5).length()-lines.at(5).find("="));
					if((percent=="(null)" ))
						{
							playing=true;
							controlsCB(NULL,(void*)STOP);
							if(oldfile!=NULL)
								free(oldfile);
							oldfile=strdup("0xdeadbeef");
							updated=false;
							return;
						}

					progressIndicator->CTK_setValue(std::stod(percent));
					if(oldval!=std::stod(percent))
						{
							oldval=std::stod(percent);
							progressIndicator->CTK_drawGadget(false);
						}
					while(updated==false)
						{
							songlen=lines.at(6).substr(lines.at(6).find("=")+1,lines.at(6).length()-lines.at(6).find("="));
							progressIndicator->CTK_setMaxValue(std::stod(songlen));
							progressIndicator->CTK_drawGadget(false);
						
							album=lines.at(2).substr(lines.at(2).find("='")+2,lines.at(2).length()-lines.at(2).find("='")-3);
							title=lines.at(3).substr(lines.at(3).find("='")+2,lines.at(3).length()-lines.at(3).find("='")-3);
							artist=lines.at(4).substr(lines.at(4).find("='")+2,lines.at(4).length()-lines.at(4).find("='")-3);
							all=str(boost::format("Album:  %s\nArtist: %s\nSong:   %s\n") %album %artist %title);
							nowPlaying->CTK_updateText(all.c_str(),false,false);
							updated=true;

							commandString=str(boost::format(":>'%s'") %outName);
							system(commandString.c_str());

							albumArt->CTK_newFBImage(chooserWidth+5,artSY,artHite*2,artHite,folder.c_str(),false);
							songList->CTK_setItem(songList->CTK_findByLabel(lines.at(1).substr(lines.at(1).find("='")+2,lines.at(1).length()-lines.at(1).find("='")-3)),true);
							mainApp->CTK_updateScreen(mainApp,NULL);
						}
					commandString=str(boost::format(":>'%s'") %outName);
					system(commandString.c_str());
					return;
				}
		}

	if(oldfile!=NULL)
		free(oldfile);
	oldfile=strdup(lines.at(0).c_str());
	updated=false;
}

bool selectSongCB(void *inst,void *userdata)
{
	CTK_cursesListBoxClass	*sl=static_cast<CTK_cursesListBoxClass*>(inst);

	if(sl->listItems.size()==0)
		return(true);

	sendToPipe(str(boost::format("p\\npausing_keep_force loadlist \\\"%s\\\"") %playLists->filePath));

	if((long)sl->listItems[sl->listItemNumber]->userData!=0)
		sendToPipe(str(boost::format("pausing_keep_force pt_step %i") %(long)sl->listItems[sl->listItemNumber]->userData));
	else
		sendToPipe("p");

	playing=true;
	paused=false;
	return(true);
}

void getLastPlayed(void)
{
	varsStruct				vsplaylistitem;
	varsStruct				vsitem;
	std::vector<varsStruct> invars;
	std::string				filepath;
	int						itemnum;

	filepath=getenv("HOME");
	filepath+="/.FBMediaPlayer";
	mkdir(filepath.c_str(),0700);
	filepath+="/lastmusicplayed.rc";

	invars=mainApp->utils->CTK_loadVars(filepath.c_str());
	if(invars.empty())
		return;

	vsplaylistitem=mainApp->utils->CTK_findVar(invars,"playlist");
	if(vsplaylistitem.vType==BADTYPE)
		return;
	vsitem=mainApp->utils->CTK_findVar(invars,"song");
	if(vsitem.vType==BADTYPE)
		return;
	itemnum=playLists->lb->CTK_findByLabel(vsplaylistitem.charVar);

	if(itemnum==-1)
		return;
	playLists->lb->CTK_selectItem(itemnum);
	playLists->fileName=playLists->files->data[itemnum].name;
	playLists->filePath=playLists->files->data[itemnum].path;
	playListsCB(playLists,(void*)PLAYLISTIMAGE);
	itemnum=songList->CTK_findByLabel(vsitem.charVar);
	if(itemnum==-1)
		return;
	songList->CTK_selectItem(itemnum);
	selectSongCB(songList,NULL);
}

void setLastPlayed(void)
{
	varsStruct				vsitem;
	std::vector<varsStruct> outvars;
	std::string				filepath;

	vsitem.vType=CHARVAR;
	if((songList->listItems.empty()) || (songList->CTK_getActiveItem()==-1))
		return;
	vsitem.charVar=songList->listItems.at(songList->CTK_getActiveItem())->label;
	vsitem.varName="song";
	outvars.push_back(vsitem);

	vsitem.vType=CHARVAR;
	vsitem.charVar=playLists->fileName;
	vsitem.varName="playlist";
	outvars.push_back(vsitem);

	filepath=getenv("HOME");
	filepath+="/.FBMediaPlayer";
	mkdir(filepath.c_str(),0700);
	filepath+="/lastmusicplayed.rc";

	mainApp->utils->CTK_saveVars(filepath.c_str(),outvars);
}

bool controlsCB(void *inst,void *userdata)
{
	long	ud=(long)userdata;

	switch(ud)
		{
			case START:
				if(playing==false)
					return(true);
				sendToPipe(str(boost::format("loadlist \\\"%s\\\"") %playLists->filePath));
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
				setLastPlayed();
				if(playing==false)
					return(true);
				for(int j=0;j<songs.size();j++)
					free(songs[j]);
				songs.clear();
				songList->CTK_clearList();
				sendToPipe("stop");
				albumArt->CTK_newFBImage(chooserWidth+6,artSY,artHite*2,artHite,"",false);
				nowPlaying->CTK_updateText("");
				playLists->lb->activeItem=-1;
				mainApp->CTK_setDefaultGadget(playLists->lb);
				mainApp->CTK_clearScreen();
				mainApp->CTK_updateScreen(mainApp,(void*)1);
				playing=false;
				paused=false;
				progressIndicator->CTK_setValue(0);
				progressIndicator->CTK_setMinValue(0);
				progressIndicator->CTK_setMaxValue(0);
				progressIndicator->CTK_drawGadget();
				updated=false;
				mainApp->CTK_updateScreen(mainApp,NULL);
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
				sendToPipe(str(boost::format("p\\npausing_keep_force loadlist \\\"%s\\\"") %playLists->filePath));
				sendToPipe(str(boost::format("pausing_keep_force pt_step %i\\np") %(songs.size()-1)));
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
				setLastPlayed();
				for(int j=0;j<songs.size();j++)
					free(songs[j]);
				songs.clear();
				songList->CTK_clearList();
				playLists->lb->activeItem=-1;
				sendToPipe("stop");
				albumArt->CTK_newFBImage(chooserWidth+6,artSY,artHite*2,artHite,"",false);
				nowPlaying->CTK_updateText("");
				playing=false;
				paused=false;
				doQuitMusic=true;
				progressIndicator->CTK_setValue(0);
				progressIndicator->CTK_setMinValue(0);
				progressIndicator->CTK_setMaxValue(0);
				progressIndicator->CTK_drawGadget();
				fflush(NULL);
				break;
		}
	return(true);
}

bool pagekeyCB(CTK_mainAppClass *app,void *userdata)
{
	if(app->readKey->inputBuffer.length()!=0)
		{
			switch(toupper(app->readKey->inputBuffer.at(0)))
				{
					case 'F':
						sendToPipe("seek +30");
						return(true);
						break;
					case 'R':
						sendToPipe("seek -30");
						return(true);
						break;
					case ' ':
						controlsCB(NULL,(void*)PAUSE);
						break;
					case 'Q':
						controlsCB(NULL,(void*)QUIT);
						break;
					case 'N':
					case '.':
						controlsCB(NULL,(void*)NEXT);
						break;
					case 'P':
					case ',':
						controlsCB(NULL,(void*)PREVIOUS);
						break;
					case 'S':
					case 'X':
						controlsCB(NULL,(void*)STOP);
						break;
					default:
						return(false);
				}
		}
	else
		return(false);
	return(true);
}

void makeMusicPage(void)
{
	CTK_cursesGadgetClass	*gadget;
	int						gw=mainApp->maxCols/8;
	int						gh=gw/(fbInfo->charHeight/fbInfo->charWidth);
	int						yspread=2;
	int						yoffset=0;
	long					btnnumx=1;
	int						btnnumy=1;
	int						btncnt=2;

	if(useFBImages==false)
		gw=10;

//main music
	mainApp->CTK_addPage();

//line1
//playlists
	gadget=newButtonSpread(1,mainApp->maxCols,1,mainApp->maxRows,gw,gh,btncnt,yspread,btnnumx++,btnnumy,buttonNames[PLAYLISTIMAGE][int(useFBImages)],useFBImages);
	gadget->CTK_setSelectCB(buttonselectCB,(void*)PLAYLISTIMAGE);
//files
	gadget=newButtonSpread(1,mainApp->maxCols,1,mainApp->maxRows,gw,gh,btncnt,yspread,btnnumx++,btnnumy,buttonNames[MUSICFILEIMAGE][int(useFBImages)],useFBImages);
	gadget->CTK_setSelectCB(buttonselectCB,(void*)MUSICFILEIMAGE);
//line2
	btnnumx=1;
	btnnumy++;
	if(useFBImages==true)
		{
			gw=gw/2;
			yspread=4;
			yoffset=2;
		}

//home
	gadget=newButtonSpread(1,mainApp->maxCols,1,mainApp->maxRows,gw,gh,1,yspread,btnnumx,btnnumy+yoffset,buttonNames[HOMEIMAGE][int(useFBImages)],useFBImages);
	gadget->CTK_setSelectCB(buttonselectCB,(void*)HOMEIMAGE);

//playlists
	mainApp->CTK_addPage();

//keyboard control
	mainApp->pages[mainApp->pageNumber].pageKey=pagekeyCB;

	midWay=mainApp->maxCols/2;
	dialogWidth=mainApp->maxCols-4;
	chooserWidth=((mainApp->maxCols/8)*5)-2;
	chooserHite=mainApp->maxRows-16;
	controlsSY=mainApp->maxRows-4;
	songsWidth=mainApp->maxCols-chooserWidth-7;
	songsHite=(chooserHite+4)/2;
	artSY=songsHite+3;
	artHite=(chooserHite-songsHite)+5;

//start mplayer
	system(str(boost::format("mplayer -quiet -slave -input file='%s' -idle >'%s' 2>/dev/null &") %musicFifoName %outName).c_str());

	playLists=new CTK_cursesChooserClass(mainApp,3,2,chooserWidth,chooserHite);
	playLists->CTK_setShowTypes(ANYTYPE);
	playLists->CTK_setShowHidden(false);
	playLists->CTK_selectFolder(mainApp,playListFolder);
	playLists->CTK_setSelectCB(playListsCB,NULL);
	mainApp->CTK_addChooserBox(playLists);

	songList=mainApp->CTK_addNewListBox(chooserWidth+6,2,songsWidth,songsHite);
	songList->CTK_setSelectCB(selectSongCB,NULL);

	nowPlaying=mainApp->CTK_addNewTextBox(3,chooserHite+4,chooserWidth,3,"");
	nowPlaying->CTK_setSelectable(false);

	progressIndicator=mainApp->CTK_addNewProgressBar(3,chooserHite+9,mainApp->maxCols-4,0.0,100.0,0.0);
	progressIndicator->CTK_setFillStyle(BAR);
	progressIndicator->CTK_setShowValues(SHOWGAUGE);
	progressIndicator->CTK_setShowRealValue(false);
	progressIndicator->CTK_setShowValuesAsTime(true);
	progressIndicator->CTK_setScale(0);
	progressIndicator->CTK_setValue(0);
	progressIndicator->CTK_setMinValue(0);
	progressIndicator->CTK_setMaxValue(0);

	btnnumx=1;
	for(int j=0;j<CONTROLCNT;j++)
		{
			if(useFBImages==true)
				gadget=mainApp->CTK_addNewFBImage(mainApp->utils->CTK_getGadgetPos(1,mainApp->maxCols,CONTROLCNT,4,btnnumx),controlsSY,4,4,musicPlayerButtons[j][int(useFBImages)]);
			else
				gadget=mainApp->CTK_addNewButton(mainApp->utils->CTK_getGadgetPos(1,mainApp->maxCols,CONTROLCNT,10,btnnumx),controlsSY,10,1,musicPlayerButtons[j][int(useFBImages)]);
				gadget->CTK_setSelectCB(controlsCB,(void*)btnnumx++);
		}

	albumArt=mainApp->CTK_addNewFBImage(chooserWidth+7,artSY,artHite,artHite,NULL,false);
	albumArt->CTK_setSelectable(false);
}

void runMusic(void)
{
	playLists->CTK_selectFolder(mainApp,musicFolder);
	playLists->CTK_updateList();
	getLastPlayed();
	mainApp->CTK_clearScreen();
	fflush(NULL);
	mainApp->CTK_updateScreen(mainApp,NULL);
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
