/*
 *
 * ©K. D. Hedger. Thu  3 Jun 12:17:04 BST 2021 keithdhedger@gmail.com

 * This file (info.cpp) is part of FBMediaPlayer.

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

#include "info.h"

void showAboutBox(void)
{
	CTK_cursesUtilsClass	*cu;

	cu=new CTK_cursesUtilsClass();
cu->CTK_aboutDialog(infoStrings[INFOAPPNAME],infoStrings[INFOAPPINFO],infoStrings[INFOCOPYRITE],infoStrings[INFOEMAIL],infoStrings[INFOWEBSITE],infoStrings[INFOCREDITS],infoStrings[INFOLICENCE],-1);
}
