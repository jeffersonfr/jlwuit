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
#ifndef LWUIT_EVENTMANAGER_H
#define LWUIT_EVENTMANAGER_H

#include "usereventlistener.h"
#include "defines.h"

#include <vector>
#include <map>

namespace jlwuit {

class EventManager {

	protected:
		std::vector<UserEventListener *> _user_listeners;

	protected:
		/**
		 * \brief
		 *
		 */
		EventManager();

	public:
		/**
		 * \brief
		 *
		 */
		virtual ~EventManager();

		/**
		 * \brief
		 *
		 */
		static EventManager * GetInstance();

		/**
		 * \brief
		 *
		 */
		virtual void RegisterUserEventListener(UserEventListener *listener);

		/**
		 * \brief
		 *
		 */
		virtual void RemoveUserEventListener(UserEventListener *listener);

};

}

#endif