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
#ifndef LWUIT_VIDEOPLAYERIMPL_H
#define LWUIT_VIDEOPLAYERIMPL_H

#include "player.h"

#include "jmedia/jplayer.h"
#include "jevent/jplayerlistener.h"

namespace jlwuit {

class VideoPlayerImpl : public jlwuit::Player, public jevent::PlayerListener {

	public:
		/** \brief */
		jmedia::Player *_player;
		/** \brief */
		jlwuit::Control *_video_size;
		/** \brief */
		jlwuit::Control *_video_format;
		/** \brief */
		jlwuit::Component *_component;

	public:
		/**
		 * \brief
		 *
		 */
		VideoPlayerImpl(std::string file);

		/**
		 * \brief
		 *
		 */
		virtual ~VideoPlayerImpl();

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
		virtual void SetCurrentTime(uint64_t i);

		/**
		 * \brief
		 *
		 */
		virtual uint64_t GetCurrentTime();

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
		virtual bool IsLoop();
		
		/**
		 * \brief
		 *
		 */
		virtual Component * GetVisualComponent();

		/*
		 * \brief
		 *
		 */
		virtual void DispatchPlayerEvent(PlayerEvent *event);
		
		/**
		 * \brief
		 *
		 */
		virtual void MediaStarted(jevent::PlayerEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual void MediaResumed(jevent::PlayerEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual void MediaPaused(jevent::PlayerEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual void MediaStopped(jevent::PlayerEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual void MediaFinished(jevent::PlayerEvent *event);
};

}

#endif
