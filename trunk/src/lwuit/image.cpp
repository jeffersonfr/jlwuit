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
#include "image.h"
#include "implementation.h"

namespace jlwuit {

Image::Image()
{
}

Image::~Image()
{
}

bool Image::GetImageSize(std::string img, int *wp, int *hp)
{
	return Implementation::GetInstance()->GetImageSize(img, wp, hp);
}

Image * Image::CreateImage(int wp, int hp, lwuit_pixelformat_t pixelformat)
{
	return Implementation::GetInstance()->CreateImage(wp, hp, pixelformat);
}

Image * Image::CreateImage(uint32_t *data, int wp, int hp)
{
	return Implementation::GetInstance()->CreateImage(data, wp, hp);
}

Image * Image::CreateImage(uint8_t *data, int size)
{
	return Implementation::GetInstance()->CreateImage(data, size);
}

Image * Image::CreateImage(std::string file)
{
	return Implementation::GetInstance()->CreateImage(file);
}

Image * Image::CreateImage(Image *image)
{
	return Implementation::GetInstance()->CreateImage(image);
}

Graphics * Image::GetGraphics()
{
	return NULL;
}

Image * Image::Scaled(int wp, int hp)
{
	return NULL;
}

Image * Image::SubImage(int xp, int yp, int wp, int hp)
{
	return NULL;
}

void Image::GetRGB(uint32_t **rgb, int xp, int yp, int wp, int hp)
{
	(*rgb) = NULL;
}

lwuit_pixelformat_t Image::GetPixelFormat()
{
	return LPF_UNKNOWN;
}

struct lwuit_size_t Image::GetSize()
{
	struct lwuit_size_t t;

	t.width = 0;
	t.height = 0;

	return t;
}

}
