/*
 *
 * ©K. D. Hedger. Sun  6 Jun 14:48:14 BST 2021 keithdhedger@gmail.com

 * This file (moviesgui.h) is part of FBMediaPlayer.

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

#ifndef _MOVIES_
#define _MOVIES_

#include "globals.h"

enum {VIDEOSTART=0,VIDEOSTOP,VIDEOQUIT,VIDEOSKIPAHEAD,VIDEOSKIPBACK,VIDEONOMORE};

extern CTK_cursesChooserClass	*videoList;
extern const char				*videoListFolder;

void makeMoviesPage(void);
void runVideo(void);

#endif
