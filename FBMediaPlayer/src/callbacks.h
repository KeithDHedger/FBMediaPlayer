/*
 *
 * ©K. D. Hedger. Fri  4 Jun 11:44:11 BST 2021 keithdhedger@gmail.com

 * This file (callbacks.h) is part of FBMediaPlayer.

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

#ifndef _CALLBACKS_
#define _CALLBACKS_

#include "globals.h"

bool buttonselectCB(void *inst,void *userdata);
bool pagekeyCB(CTK_mainAppClass *app,void *userdata);

#endif
