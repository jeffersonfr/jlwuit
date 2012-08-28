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
#include "userevent.h"

namespace jlwuit {

UserEvent::UserEvent(lwuit_userevent_type_t type, lwuit_key_modifiers_t modifiers, int code, lwuit_key_symbol_t symbol)
{
	_type = type;
	_code = code;
	_symbol = symbol;
	_modifiers = modifiers;
}

UserEvent::UserEvent(lwuit_userevent_type_t type, lwuit_mouse_button_t button, lwuit_mouse_button_t buttons, int click_count, int x, int y, double vx, double vy)
{
	_button = button;
	_buttons = buttons;
	_type = type;
	_click_count = click_count;
	_x = x;
	_y = y;
	_vx = vx;
	_vy = vy;
}

UserEvent::~UserEvent()
{
}

lwuit_userevent_type_t UserEvent::GetType()
{
	return _type;
}

lwuit_key_symbol_t UserEvent::GetKeySymbol()
{
	return _symbol;
}

int UserEvent::GetKeyCode()
{
	return _code;
}

lwuit_key_modifiers_t UserEvent::GetModifiers()
{
	return _modifiers;
}

lwuit_mouse_button_t UserEvent::GetButton()
{
	return _button;
}

lwuit_mouse_button_t UserEvent::GetButtons()
{
	return _button;
}

int UserEvent::GetClickCount()
{
	return _click_count;
}

int UserEvent::GetX()
{
	return _x;
}

int UserEvent::GetY()
{
	return _y;
}

double UserEvent::GetVelocityX()
{
	return _vx;
}

double UserEvent::GetVelocityY()
{
	return _vy;
}

}
