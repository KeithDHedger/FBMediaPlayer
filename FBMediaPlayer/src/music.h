/*
 *
 * ©K. D. Hedger. Sun  6 Jun 18:21:03 BST 2021 keithdhedger@gmail.com

 * This file (music.h) is part of FBMediaPlayer.

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

#ifndef _MUSIC_
#define _MUSIC_

#include "globals.h"
#include <libgen.h>
#include <cursesGlobals.h>
#include <stdarg.h>
#include <getopt.h>
#include "config.h"

#define CONTROLCNT 8
enum {START=1,PREVIOUS,PLAY,STOP,PAUSE,NEXT,END,QUIT};

void getMeta(void);
void makeMusicPage(void);
void runMusic(void);
void sendToPipe(const std::string command);

#endif
