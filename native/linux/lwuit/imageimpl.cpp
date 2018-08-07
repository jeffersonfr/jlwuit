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
#include "imageimpl.h"
#include "graphicsimpl.h"
#include "exception.h"

#include "jgui/jimage.h"

namespace jlwuit {

ImageImpl::ImageImpl(jgui::Image *image)
{
	if (image == NULL) {
		throw Exception("ImageImpl::Constructor:: Null pointer exception");
	}

	_native_image = image;

	_graphics = new GraphicsImpl(_native_image->GetGraphics());
}

ImageImpl::~ImageImpl()
{
	delete _native_image;
	delete _graphics;
}

Graphics * ImageImpl::GetGraphics()
{
	return _graphics;
}

Image * ImageImpl::Scale(int wp, int hp)
{
	return new ImageImpl(_native_image->Scale(wp, hp));
}

Image * ImageImpl::Rotate(double radians, bool resize)
{
	return new ImageImpl(_native_image->Rotate(radians, resize));
}

Image * ImageImpl::Crop(int xp, int yp, int wp, int hp)
{
	return new ImageImpl(_native_image->Crop(xp, yp, wp, hp));
}

Image * ImageImpl::Blend(double alpha)
{
	return new ImageImpl(_native_image->Blend(alpha));
}

Image * ImageImpl::Rotate(double degrees)
{
	return new ImageImpl(_native_image->Rotate(degrees));
}

void ImageImpl::GetRGB(uint32_t **rgb, int xp, int yp, int wp, int hp)
{
	_native_image->GetRGBArray(rgb, xp, yp, wp, hp);
}

lwuit_pixelformat_t ImageImpl::GetPixelFormat()
{
	return LPF_UNKNOWN;
}

struct lwuit_size_t ImageImpl::GetSize()
{
	jgui::jsize_t jsize = _native_image->GetSize();
	lwuit_size_t lsize;

	lsize.width = jsize.width;
	lsize.height = jsize.height;

	return lsize;
}

}
