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

#include "config.h"

#include <cursesGlobals.h>

#include "info.h"
#include "maingui.h"
#include "callbacks.h"

#define ALLOK 0
#define UNKNOWNARG 1

#undef DATADIR
#define DATADIR "/media/LinuxData/Development64/Projects/FBMediaPlayer/FBMediaPlayer/resources"

enum {INFOAPPNAME=0,INFOAPPINFO,INFOCOPYRITE,INFOEMAIL,INFOWEBSITE,INFOCREDITS,INFOLICENCE,DIALOGWIDTH};
enum {FILMIMAGE=0,TVIMAGE,MUSICIMAGE,OFFIMAGE};

extern bool					useimages;
extern const char			*infoStrings[];
extern const char			*imagePaths[];
extern struct fbData		*fbInfo;
extern CTK_mainAppClass		*mainApp;

#endif


