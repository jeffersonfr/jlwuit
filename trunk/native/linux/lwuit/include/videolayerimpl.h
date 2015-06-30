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
#ifndef VIDEOLAYERIMPL_H
#define VIDEOLAYERIMPL_H

#include "layerimpl.h"
#include "jplayermanager.h"

#include <directfb.h>

namespace jlwuit {

class VideoLayerImpl : public LayerImpl, public LayerSetup {

	private:
		/** \brief */
		jmedia::Player *_player;

	private:
		/**
		 * \brief
		 *
		 */
		virtual void Initialize();

	public:
		/**
		 * \brief
		 *
		 */
		VideoLayerImpl();

		/**
		 * \brief
		 *
		 */
		virtual ~VideoLayerImpl();

		/**
		 * \brief
		 *
		 */
		virtual void SetFile(std::string file);

		/**
		 * \brief
		 *
		 */
		virtual void Play();

		/**
		 * \brief
		 *
		 */
		virtual void Stop();

		/**
		 * \brief Gets current media time.
		 *
		 */
		virtual uint64_t GetCurrentTime();

		/**
		 * \brief Gets full media time.
		 *
		 */
		virtual uint64_t GetMediaTime();

		/**
		 * \brief
		 *
		 */
		virtual bool IsEnabled();

		/**
		 * \brief
		 *
		 */
		virtual void SetEnabled(bool b);

		/**
		 * \brief
		 *
		 */
		virtual void SetBounds(int x, int y, int w, int h);

		/**
		 * \brief
		 *
		 */
		virtual struct lwuit_region_t GetBounds();

		/**
		 * \brief
		 *
		 */
		virtual LayerSetup * GetLayerSetup();

};

}

#endif
