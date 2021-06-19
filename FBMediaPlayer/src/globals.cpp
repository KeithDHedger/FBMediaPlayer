/*
 *
 * ©K. D. Hedger. Thu  3 Jun 12:21:15 BST 2021 keithdhedger@gmail.com

 * This file (globals.cpp) is part of FBMediaPlayer.

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

#include "globals.h"

struct fbData		*fbInfo;

const char			*infoStrings[]={"FBMediaPlayer","A media player for the linux framebuffer","Copyright (c) 2021 K.D.Hedger","keithdhedger@gmail.com","https://keithdhedger.github.io","K. D. Hedger","GPL 3.0"};

const char			*buttonNames[][2]={
{"Movies",DATADIR "/pixmaps/film.png"},
{"TV Shows",DATADIR "/pixmaps/tv.png"},
{"Music",DATADIR "/pixmaps/music.png"},
{"Quit",DATADIR "/pixmaps/off.png"},
{"Settings",DATADIR "/pixmaps/settings.png"},
{"Home",DATADIR "/pixmaps/home.png"},
{"Save",DATADIR "/pixmaps/save.png"},
{"Cancel",DATADIR "/pixmaps/cancel.png"},
{"Up",DATADIR "/pixmaps/up.png"},
{"Playlists",DATADIR "/pixmaps/playlist.png"},
{"Files",DATADIR "/pixmaps/save.png"}
};

bool				useFBImages=true;
std::string			outName="";
const char			*tempPlaylist=TEMPFILES "/tmppl.m3u";
std::string			musicFifoName="";
std::string			videoFifoName="";
std::string			commandString="";

CTK_mainAppClass	*mainApp;

