/*
 *
 * ©K. D. Hedger. Thu  3 Jun 12:21:25 BST 2021 keithdhedger@gmail.com

 * This file (globals.h) is part of FBMediaPlayer.

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

#ifndef _GLOBALS_
#define _GLOBALS_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/format.hpp>
#include <boost/filesystem.hpp>

#include <cursesGlobals.h>

#if defined _DEBUGCODE_ || defined _WARN_ENABLEDEBUG_
#include "/media/LinuxData/Development/DevelopmentFiles/Debugging/debug.h"
#endif

#include "info.h"
#include "maingui.h"
#include "callbacks.h"
#include "movies.h"
#include "tv.h"
#include "music.h"
#include "prefs.h"

#define ALLOK 0
#define UNKNOWNARG 1
#define TEMPFILES "/run/" PACKAGE

enum {INFOAPPNAME=0,INFOAPPINFO,INFOCOPYRITE,INFOEMAIL,INFOWEBSITE,INFOCREDITS,INFOLICENCE,DIALOGWIDTH};
enum {FILMIMAGE=0,TVIMAGE,MUSICIMAGE,OFFIMAGE,PREFSIMAGE,HOMEIMAGE,SAVEIMAGE,CANCELIMAGE,UPIMAGE,PLAYLISTIMAGE,MUSICFILEIMAGE};
enum {SETFILMPREFS=100,SETTVPREFS,SETMUSICPLAYLISTPREFS,SETMUSICFILESPREFS,SETBACKDROPPREFS};
enum {PREFSPAGE=0,MAINPAGE,FILMPAGE,TVPAGE,MUSICPAGE,PLAYLISTSPAGE,};

extern struct fbData			*fbInfo;
extern const char				*infoStrings[];
extern const char				*buttonNames[][2];
extern bool						useFBImages;
extern std::string				outName;
extern const char				*tempPlaylist;
extern std::string				musicFifoName;
extern std::string				videoFifoName;
extern std::string				commandString;

extern CTK_mainAppClass			*mainApp;
#endif


