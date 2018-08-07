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
#ifndef IMAGEIMPL_H
#define IMAGEIMPL_H

#include "image.h"

#include "jgui/jimage.h"

#include <stdint.h>
#include <string.h>

namespace jlwuit {

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class ImageImpl : public Image {

	public:
		jgui::Image *_native_image;
		Graphics *_graphics;
		
	public:
		/**
		 * \brief
		 *
		 */
		ImageImpl(jgui::Image *image);

		/**
		 * \brief
		 *
		 */
		virtual ~ImageImpl();

		/**
		 * \brief
		 *
		 */
		static Image * CreateImage(int wp, int hp, lwuit_pixelformat_t pixelformat = LPF_ARGB);
		
		/**
		 * \brief
		 *
		 */
		static Image * CreateImage(uint32_t *data, int wp, int hp);

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
		virtual Image * Scale(int wp, int hp);

		/**
		 * \brief
		 *
		 */
		virtual Image * Rotate(double radians, bool resize = true);

		/**
		 * \brief
		 *
		 */
		virtual Image * Crop(int xp, int yp, int wp, int hp);

		/**
		 * \brief
		 *
		 */
		virtual Image * Blend(double alpha);

		/**
		 * \brief
		 *
		 */
		virtual Image * Rotate(double degrees);

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
