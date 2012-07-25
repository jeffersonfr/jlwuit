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
#ifndef LWUIT_PLAYEREVENT_H
#define LWUIT_PLAYEREVENT_H

namespace jlwuit {

/** 
 * \brief Supported events
 *
 */
enum lwuit_player_event_t {
	LPE_STARTED,
	LPE_PAUSED,
	LPE_RESUMED,
	LPE_STOPPED,
	LPE_FINISHED
};

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class PlayerEvent { // : public Event {

	private:
		lwuit_player_event_t _type;

	public:
		/**
		 * \brief 
		 *
		 */
		PlayerEvent(void *source, lwuit_player_event_t type);

		/**
		 * \brief
		 *
		 */
		virtual ~PlayerEvent();

		/**
		 * \brief
		 *
		 */
		lwuit_player_event_t GetType();

};

}

#endif
