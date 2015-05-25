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
#include "usereventlistener.h"

#include <algorithm>

namespace jlwuit {

UserEventListener::UserEventListener()
{
}

UserEventListener::~UserEventListener()
{
}

void UserEventListener::Add(lwuit_key_symbol_t key)
{
	if (std::find(_keys.begin(), _keys.end(), key) == _keys.end()) {
		_keys.push_back(key);
	}
}

void UserEventListener::AddAllNumerics()
{
	RemoveAllNumerics();

	_keys.push_back(LKS_0);
	_keys.push_back(LKS_1);
	_keys.push_back(LKS_2);
	_keys.push_back(LKS_3);
	_keys.push_back(LKS_4);
	_keys.push_back(LKS_5);
	_keys.push_back(LKS_6);
	_keys.push_back(LKS_7);
	_keys.push_back(LKS_8);
	_keys.push_back(LKS_9);
}

void UserEventListener::RemoveAllNumerics()
{
	// TODO::
}

void UserEventListener::AddAllArrows()
{
	RemoveAllArrows();

	_keys.push_back(LKS_CURSOR_LEFT);
	_keys.push_back(LKS_CURSOR_RIGHT);
	_keys.push_back(LKS_CURSOR_UP);
	_keys.push_back(LKS_CURSOR_DOWN);
}

void UserEventListener::RemoveAllArrows()
{
	// TODO::
}

void UserEventListener::AddAllColors()
{
	RemoveAllColors();

	_keys.push_back(LKS_RED);
	_keys.push_back(LKS_GREEN);
	_keys.push_back(LKS_YELLOW);
	_keys.push_back(LKS_BLUE);
}

void UserEventListener::RemoveAllColors()
{
	// TODO::
}

void UserEventListener::AddAllMultimedia()
{
	RemoveAllMultimedia();

	_keys.push_back(LKS_PLAY);
	_keys.push_back(LKS_STOP);
	_keys.push_back(LKS_EJECT);
	_keys.push_back(LKS_REWIND);
	_keys.push_back(LKS_RECORD);
}

void UserEventListener::RemoveAllMultimedia()
{
	// TODO::
}

void UserEventListener::RemoveAll()
{
	_keys.clear();
}

std::vector<lwuit_key_symbol_t> UserEventListener::GetKeys()
{
	return _keys;
}

bool UserEventListener::IsMatch(UserEvent *event)
{
	return false;
}

bool UserEventListener::OnKeyDown(UserEvent *event)
{
	return false;
}

bool UserEventListener::OnKeyPress(UserEvent *event)
{
	return false;
}

bool UserEventListener::OnKeyUp(UserEvent *event)
{
	return false;
}

bool UserEventListener::OnKeyLongPress(UserEvent *event)
{
	return false;
}

bool UserEventListener::OnMousePress(UserEvent *event)
{
	return false;
}

bool UserEventListener::OnMouseRelease(UserEvent *event)
{
	return false;
}

bool UserEventListener::OnMouseLongPress(UserEvent *event)
{
	return false;
}

bool UserEventListener::OnMouseClick(UserEvent *event)
{
	return false;
}

bool UserEventListener::OnMouseMove(UserEvent *event)
{
	return false;
}

bool UserEventListener::OnMouseOver(UserEvent *event)
{
	return false;
}

bool UserEventListener::OnMouseOut(UserEvent *event)
{
	return false;
}

bool UserEventListener::OnMouseWheel(UserEvent *event)
{
	return false;
}

}
