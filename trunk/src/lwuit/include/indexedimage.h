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
#ifndef LWUIT_INDEXEDIMAGE_H
#define LWUIT_INDEXEDIMAGE_H

#include "image.h"

#include <vector>

#include <stdint.h>
#include <string.h>

namespace jlwuit {

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class IndexedImage : public Image {

	private:
		/** \brief */
		std::vector<int> _palette;
		/** \brief */
		Image *_image;

	public:
		/**
		 * \brief
		 *
		 */
		IndexedImage(Image *image, int colors = 255);
		
		/**
		 * \brief
		 *
		 */
		virtual ~IndexedImage();

		/**
		 * \brief
		 *
		 */
		virtual Image * GetDrawable();

		/**
		 * \brief
		 *
		 */
		virtual std::vector<int> & GetPalette();

		/**
		 * \brief
		 *
		 */
		virtual Graphics * GetGraphics();

		/**
		 * \brief
		 *
		 */
		virtual Image * Scaled(int wp, int hp);

		/**
		 * \brief
		 *
		 */
		virtual Image * SubImage(int xp, int yp, int wp, int hp);

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
