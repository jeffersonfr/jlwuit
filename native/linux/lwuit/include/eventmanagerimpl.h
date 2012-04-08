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
#ifndef EVENTMANAGERIMPL_H
#define EVENTMANAGERIMPL_H

#define LONG_PRESS_TIME	2

#include "eventmanager.h"

#include "jkeylistener.h"
#include "jmouselistener.h"

#include <vector>
#include <map>

namespace jlwuit {

class EventManagerImpl : public EventManager, public jgui::KeyListener, public jgui::MouseListener {

	private:
		struct event_t {
			bool key_down;
			long start_time;
		};

	private:
		static EventManagerImpl *_instance;

	private:
		std::map<lwuit_key_symbol_t, event_t *> _events;
		lwuit_point_t _last_mouse_location;
		uint64_t _last_mouse_move;

	private:
		/**
		 * \brief
		 *
		 */
		lwuit_key_modifiers_t TranslateKeyModifiers(jgui::jkeyevent_modifiers_t modifiers);

		/**
		 * \brief
		 *
		 */
		lwuit_key_symbol_t TranslateKeySymbol(jgui::jkeyevent_symbol_t symbol);

		/**
		 * \brief
		 *
		 */
		lwuit_mouse_button_t TranslateMouseButton(jgui::jmouseevent_button_t button);

		/**
		 * \brief
		 *
		 */
		virtual void KeyPressed(jgui::KeyEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual void MousePressed(jgui::MouseEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual void MouseReleased(jgui::MouseEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual void MouseMoved(jgui::MouseEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual void MouseWheel(jgui::MouseEvent *event);
		
		/**
		 * \brief
		 *
		 */
		virtual void DispatchUserEvent(UserEvent *event);

	public:
		/**
		 * \brief
		 *
		 */
		EventManagerImpl();

		/**
		 * \brief
		 *
		 */
		virtual ~EventManagerImpl();

};

}

#endif
