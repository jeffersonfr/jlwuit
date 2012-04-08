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
#ifndef LWUIT_ISDTVPLAYER_H
#define LWUIT_ISDTVPLAYER_H

#include "player.h"

namespace jlwuit {

class ISDTVPlayer : public jlwuit::Player {

	public:
		/**
		 * \brief
		 *
		 */
		ISDTVPlayer();

		/**
		 * \brief
		 *
		 */
		virtual ~ISDTVPlayer();

		/**
		 * \brief
		 *
		 */
		virtual void Play();

		/**
		 * \brief
		 *
		 */
		virtual void Pause();

		/**
		 * \brief
		 *
		 */
		virtual void Stop();

		/**
		 * \brief
		 *
		 */
		virtual void Resume();

		/**
		 * \brief
		 *
		 */
		virtual void Close();

		/**
		 * \brief
		 *
		 */
		virtual void SetMediaTime(uint64_t i);

		/**
		 * \brief
		 *
		 */
		virtual uint64_t GetMediaTime();

		/**
		 * \brief
		 *
		 */
		virtual void SetLoop(bool b);

		/**
		 * \brief
		 *
		 */
		virtual bool IsPlaying();
		
		/**
		 * \brief
		 *
		 */
		virtual bool IsLoop();
		
		/**
		 * \brief
		 *
		 */
		virtual Control * GetControl(lwuit_media_control_t type);

		/**
		 * \brief
		 *
		 */
		virtual double GetDecodeRate();

		/**
		 * \brief
		 *
		 */
		virtual void SetDecodeRate(double rate);

		/**
		 * \brief
		 *
		 */
		virtual Component * GetVisualComponent();

};

}

#endif
