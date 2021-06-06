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

bool				useimages=true;

const char			*infoStrings[]={"FBMediaPlayer","A media player for the linux framebuffer","Copyright (c) 2021 K.D.Hedger","keithdhedger@gmail.com","https://keithdhedger.github.io","K. D. Hedger","GPL 3.0"};
const char			*imagePaths[]={DATADIR "/pixmaps/film.png",DATADIR "/pixmaps/tv.png",DATADIR "/pixmaps/music.png",DATADIR "/pixmaps/off.png",DATADIR "/pixmaps/settings.png",DATADIR "/pixmaps/home.png"};

struct fbData		*fbInfo;

CTK_mainAppClass	*mainApp;
