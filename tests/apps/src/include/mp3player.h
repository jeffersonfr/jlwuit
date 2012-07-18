/***************************************************************************
 *   Copyright (C) 2010 by Jeff Ferr                                       *
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
#ifndef LWUIT_MP3PLAYER_H
#define LWUIT_MP3PLAYER_H

#include "scene.h"
#include "player.h"
#include "usbstatuslistener.h"

#include <string>

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

namespace jlwuit {

enum lwuit_player_action_t {
	LPA_PLAY, 
	LPA_STOP, 
	LPA_PAUSE, 
	LPA_NEXT, 
	LPA_PREVIOUS, 
	LPA_REWIND, 
	LPA_FASTFORWARD
};

class MP3Player : public jlwuit::Scene, public jlwuit::USBStatusListener {

	private:
		/** \brief */
		std::vector<std::string> _musics;
		/** \brief */
		jlwuit::Player *_player;
		/** \brief */
		std::string _track;
		/** \brief */
		std::string _artist;
		/** \brief */
		std::string _album;
		/** \brief */
		std::string _genre;
		/** \brief */
		std::string _year;
		/** \brief */
		std::string _comments;
		/** \brief */
		int _index;
		/** \brief */
		int _progress;
		/** \brief */
		int _action;
		/** \brief */
		int _screen_saver_timeout;
		/** \brief */
		int _screen_saver_state;
		/** \brief */
		jlwuit::lwuit_point_t _image;

	public:
		/**
		 * \brief
		 *
		 */
		MP3Player();

		/**
		 * \brief
		 *
		 */
		virtual ~MP3Player();

		/**
		 * \brief
		 *
		 */
		virtual void GoLeft();

		/**
		 * \brief
		 *
		 */
		virtual void GoRight();

		/**
		 * \brief
		 *
		 */
		virtual void GoNext();

		/**
		 * \brief
		 *
		 */
		virtual void GoTo(int index);

		/**
		 * \brief
		 *
		 */
		virtual void GoPrevious();

		/**
		 * \brief
		 *
		 */
		virtual void GoPlay();

		/**
		 * \brief
		 *
		 */
		virtual void GoStop();

		/**
		 * \brief
		 *
		 */
		virtual void GoPause();

		/**
		 * \brief
		 *
		 */
		virtual void GoInfo();

		/**
		 * \brief
		 *
		 */
		virtual void TransitionState(bool flag);

		/**
		 * \brief
		 *
		 */
		virtual void SetMusicDurationString(std::string length);

		/**
		 * \brief
		 *
		 */
		virtual void SetPlayList(std::vector<std::string> playList, int playListIndex);

		/**
		 * \brief
		 *
		 */
		virtual int GetSelectedIndex();

		/**
		 * \brief
		 *
		 */
		virtual int GetAction();

		/**
		 * \brief
		 *
		 */
		virtual void SetProgress(double value);

		/**
		 * \brief
		 *
		 */
		virtual void SetElapsedTime(int hour, int minute, int second);

		/**
		 * \brief
		 *
		 */
		virtual void ResetElapsedTime();

		/**
		 * \brief
		 *
		 */
		virtual void SetFullTime(std::string time);

		/**
		 * \brief
		 *
		 */
		virtual bool Animate();

		/**
		 * \brief
		 *
		 */
		virtual void Paint(jlwuit::Graphics *g);

		/**
		 * \brief
		 *
		 */
		virtual bool OnKeyDown(jlwuit::UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual void EntryUSBDevice(jlwuit::USBStatusEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual void RemoveUSBDevice(jlwuit::USBStatusEvent *event);

};

}

#endif

