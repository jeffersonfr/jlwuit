/***************************************************************************
 *   Copyright (C) 2005 by Jeff Ferr                                       *
 *   root@sat                                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "remotecontrol.h"

namespace jlwuit {

RemoteControl::RemoteControl()
{
}

RemoteControl::~RemoteControl()
{
}

bool RemoteControl::IsSupported(lwuit_key_symbol_t symbol)
{
	switch (symbol) {
		case LKS_EXIT:
		case LKS_ENTER:
		case LKS_CANCEL:

		case LKS_0:
		case LKS_1:
		case LKS_2:
		case LKS_3:
		case LKS_4:
		case LKS_5:
		case LKS_6:
		case LKS_7:
		case LKS_8:
		case LKS_9:

		case LKS_CURSOR_LEFT:
		case LKS_CURSOR_RIGHT:
		case LKS_CURSOR_UP:
		case LKS_CURSOR_DOWN:

		case LKS_RED:
		case LKS_GREEN:
		case LKS_YELLOW:
		case LKS_BLUE:

		case LKS_POWER:
		case LKS_MENU:
		case LKS_FILE:
		case LKS_INFO:
		case LKS_BACK:
		case LKS_GUIDE:
		case LKS_MUTE:

		case LKS_CHANNEL_UP:
		case LKS_CHANNEL_DOWN:

		case LKS_VOLUME_UP:
		case LKS_VOLUME_DOWN:

		case LKS_PLAY:
		case LKS_STOP:
		case LKS_EJECT:
		case LKS_REWIND:
		case LKS_RECORD:
			return true;
		default:
			break;
	};

	return false;
}

}
