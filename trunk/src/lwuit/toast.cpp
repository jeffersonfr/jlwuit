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
#include "toast.h"

#include <map>

namespace jlwuit {
	
std::map<std::string, Toast *> toasts;

Toast::Toast(std::string id)
{
	_id = id;
}

Toast::~Toast()
{
}

Toast * Toast::Create(std::string id)
{
	std::map<std::string, Toast *>::iterator i = toasts.find(id);

	if (i != toasts.end()) {
		return i->second;
	}

	Toast *toast = new Toast(id);

	toasts[id] = toast;
	
	return toast;
}

Toast * Toast::SetMessage(std::string msg)
{
	_message = msg;

	return this;
}

Toast * Toast::SetIcon(std::string icon)
{
	_icon = icon;

	return this;
}

Toast * Toast::SetHorizontalAlign(lwuit_horizontal_align_t align)
{
	_halign = align;

	return this;
}

Toast * Toast::SetVerticalAlign(lwuit_vertical_align_t align)
{
	_valign = align;

	return this;
}

Toast * Toast::SetTimeout(int ms)
{
	_timeout = ms;

	return this;
}

void Toast::Show()
{
}

void Toast::Hide()
{
}

}
