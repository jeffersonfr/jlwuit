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
#ifndef LWUIT_IMAGE_H
#define LWUIT_IMAGE_H

#include "graphics.h"

#include <stdint.h>
#include <string.h>

namespace jlwuit {

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class Image {

	protected:
		/**
		 * \brief
		 *
		 */
		Image();
		
	public:
		/**
		 * \brief
		 *
		 */
		virtual ~Image();

		/**
		 * \brief
		 *
		 */
		static bool GetImageSize(std::string img, int *width, int *height);
		
		/**
		 * \brief
		 *
		 */
		static Image * CreateImage(int width, int height, lwuit_pixelformat_t pixelformat = LPF_ARGB);
		
		/**
		 * \brief
		 *
		 */
		static Image * CreateImage(uint32_t *data, int width, int height);

		/**
		 * \brief
		 *
		 */
		static Image * CreateImage(uint8_t *data, int size);

		/**
		 * \brief
		 *
		 */
		static Image * CreateImage(std::string image);
		
		/**
		 * \brief
		 *
		 */
		static Image * CreateImage(Image *image);

		/**
		 * \brief
		 *
		 */
		virtual Graphics * GetGraphics();

		/**
		 * \brief
		 *
		 */
		virtual Image * Scaled(int width, int height);

		/**
		 * \brief
		 *
		 */
		virtual Image * SubImage(int x, int y, int width, int height);

		/**
		 * \brief
		 *
		 */
		virtual void GetRGB(uint32_t **rgb, int xp, int yp, int wp, int hp);
		
		/**
		 * \brief
		 *
		 */
		virtual lwuit_pixelformat_t GetPixelFormat();

		/**
		 * \brief
		 *
		 */
		virtual struct lwuit_size_t GetSize();

};

}

#endif 
