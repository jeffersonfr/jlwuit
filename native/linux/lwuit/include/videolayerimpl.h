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

#include "jimage.h"

#include <directfb.h>

namespace jlwuit {

class VideoLayerImpl : public LayerImpl {

	private:
		/** \brief */
		IDirectFBVideoProvider *_provider;
		/** \brief */
		jthread::Mutex _mutex;
		/** \brief */
		std::string _file;

	private:
		/**
		 * \brief
		 *
		 */
		static void Callback(void *ctx);
		
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
		 * \brief
		 *
		 */
		virtual void SetDecodeRate(double rate);

		/**
		 * \brief
		 *
		 */
		virtual double GetDecodeRate();

		/**
		 * \brief
		 *
		 */
		virtual void SetMediaTime(int64_t time);

		/**
		 * \brief
		 *
		 */
		virtual int64_t GetMediaTime();

};

}

#endif
