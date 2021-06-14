/*
 *
 * ©K. D. Hedger. Sun  6 Jun 18:21:35 BST 2021 keithdhedger@gmail.com

 * This file (prefs.h) is part of FBMediaPlayer.

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

#ifndef _PREFS_
#define _PREFS_

#include "globals.h"

extern std::vector<varsStruct> filmPrefs;
extern std::vector<varsStruct> tvPrefs;
extern std::vector<varsStruct> musicPrefs;

extern std::vector<varsStruct>	prefsData;
extern std::string				prefsPath;

extern CTK_cursesInputClass		*videoPath;
extern CTK_cursesInputClass		*tvPath;
extern CTK_cursesInputClass		*musicPlaylistPath;
extern CTK_cursesInputClass		*musicFilesPath;
extern CTK_cursesInputClass		*backDropPath;

void updatePrefs(void);
void makePrefsPage(void);

#endif
