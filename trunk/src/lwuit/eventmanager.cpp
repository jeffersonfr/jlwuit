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
#include "eventmanager.h"
#include "implementation.h"

#include <algorithm>

namespace jlwuit {

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

EventManager * EventManager::GetInstance()
{
	return Implementation::GetInstance()->GetEventManager();
}

void EventManager::RegisterUserEventListener(UserEventListener *listener)
{
	if (listener == NULL) {
		return;
	}

	if (std::find(_user_listeners.begin(), _user_listeners.end(), listener) == _user_listeners.end()) {
		_user_listeners.push_back(listener);
	}
}

void EventManager::RemoveUserEventListener(UserEventListener *listener)
{
	if (listener == NULL) {
		return;
	}

	std::vector<UserEventListener *>::iterator i = std::find(_user_listeners.begin(), _user_listeners.end(), listener);

	if (i != _user_listeners.end()) {
		_user_listeners.erase(i);
	}
}

}
