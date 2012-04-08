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
#ifndef LWUIT_PLAYER_H
#define LWUIT_PLAYER_H

#include "playereventlistener.h"
#include "control.h"
#include "component.h"

#include <vector>

namespace jlwuit {

class Player {

	protected:
		/**
		 * \brief
		 *
		 */
		Player();

	public:
		/**
		 * \brief
		 *
		 */
		virtual ~Player();

		/**
		 * \brief Starts media decode.
		 *
		 */
		virtual void Play();

		/**
		 * \brief Pause media decode.
		 *
		 */
		virtual void Pause();

		/**
		 * \brief Stops media decode.
		 *
		 */
		virtual void Stop();

		/**
		 * \brief Resume media decode.
		 *
		 */
		virtual void Resume();

		/**
		 * \brief Release resources associated with this player.
		 *
		 */
		virtual void Close();

		/**
		 * \brief Seeks media forward or back.
		 *
		 */
		virtual void SetMediaTime(uint64_t time);

		/**
		 * \brief Gets current media time.
		 *
		 */
		virtual uint64_t GetMediaTime();

		/**
		 * \brief Set loop mode.
		 *
		 * \param b
		 */
		virtual void SetLoop(bool b);

		/**
		 * \brief Return if this player still decoding the media.
		 *
		 * \return
		 */
		virtual bool IsPlaying();
		
		/**
		 * \brief 
		 *
		 */
		virtual bool IsLoop();
		
		/**
		 * \brief Set a decode rate to this player.
		 *
		 * \param rate
		 *
		 */
		virtual double GetDecodeRate();

		/**
		 * \brief Set a decode rate to this player.
		 *
		 * \param rate
		 *
		 */
		virtual void SetDecodeRate(double rate);

		/**
		 * \brief Returns a list with all controls associated with this player.
		 *
		 * \return controls
		 */
		virtual std::vector<Control *> GetControls();

		/**
		 * \brief Return a specific control related with the type.
		 *
		 * \return
		 */
		virtual Control * GetControl(lwuit_media_control_t type);

		/**
		 * \brief If exists, return a visual component associated with this player.
		 *
		 * \return
		 */
		virtual Component * GetVisualComponent();

		/**
		 * \brief Registry a listener.
		 *
		 * \param listener
		 */
		virtual void RegisterPlayerListener(PlayerEventListener *listener);

		/**
		 * \brief Remove a listener.
		 *
		 * \param listener
		 */
		virtual void RemovePlayerListener(PlayerEventListener *listener);

};

}

#endif
