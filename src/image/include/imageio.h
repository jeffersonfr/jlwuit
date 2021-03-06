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
#ifndef LWUIT_IMAGEIO_H 
#define LWUIT_IMAGEIO_H

#include "defines.h"

#include <string>

namespace jlwuit {

/**
 * \brief ImageIO
 *
 * \author Jeff Ferr
 */
class ImageIO {

	private:
		/** \brief */
		std::string _image;
		/** \brief */
		int _quality;
		/** \brief */
		int _compression_level;
		/** \brief */
		lwuit_pixelformat_t _pixelformat;

	public:
		/**
		 * \brief
		 *
		 */
		ImageIO(std::string image, lwuit_pixelformat_t format);

		/**
		 * \brief
		 *
		 */
		virtual ~ImageIO();

		/**
		 * \brief
		 *
		 */
		virtual void SetQuality(int quality);

		/**
		 * \brief
		 *
		 */
		virtual int GetQuality();

		/**
		 * \brief
		 *
		 */
		virtual void SetCompressionLevel(int level);

		/**
		 * \brief
		 *
		 */
		virtual int GetCompressionLevel();

		/**
		 * \brief
		 *
		 */
		virtual bool Encode(uint32_t *rgb, int width, int height);
	
};

}

#endif
