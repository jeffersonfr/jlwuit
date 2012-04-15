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

#include "jimage.h"

namespace jlwuit {

ImageImpl::ImageImpl(jgui::Image *image)
{
	if (image == NULL) {
		throw Exception("ImageImpl::Constructor:: Null pointer exception");
	}

	_native_image = image;
	
	_size.width = image->GetWidth();
	_size.height = image->GetHeight();

	_graphics = new GraphicsImpl(image->GetGraphics());
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

Image * ImageImpl::Scaled(int wp, int hp)
{
	return new ImageImpl(_native_image->Scaled(wp, hp));
}

Image * ImageImpl::SubImage(int xp, int yp, int wp, int hp)
{
	return new ImageImpl(_native_image->SubImage(xp, yp, wp, hp));
}

void ImageImpl::GetRGB(uint32_t **rgb, int xp, int yp, int wp, int hp)
{
	_native_image->GetRGB(rgb, xp, yp, wp, hp);
}

lwuit_pixelformat_t ImageImpl::GetPixelFormat()
{
	return LPF_UNKNOWN;
}

struct lwuit_size_t ImageImpl::GetSize()
{
	return _size;
}

}
