/*
 *
 * ©K. D. Hedger. Fri  4 Jun 11:44:03 BST 2021 keithdhedger@gmail.com

 * This file (callbacks.cpp) is part of FBMediaPlayer.

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

#include "callbacks.h"

bool buttonselectCB(void *inst,void *userdata)
{
	CTK_cursesGadgetClass	*bc;
//if(useimages==true)
	{
		bc=static_cast<CTK_cursesGadgetClass*>(inst);
	}
if((long)userdata==4)
	mainApp->runEventLoop=false;
fprintf(stderr,"button=%i x=%i y=%i\n",(long)userdata,bc->sx,bc->sy);
return(true);
}

