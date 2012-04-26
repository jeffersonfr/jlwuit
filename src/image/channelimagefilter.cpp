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
#include "channelimagefilter.h"

namespace jlwuit {

ChannelImageFilter::ChannelImageFilter(uint8_t rmask, uint8_t gmask, uint8_t bmask, uint8_t amask)
{
	_rmask = rmask;
	_gmask = gmask;
	_bmask = bmask;
	_amask = amask;
}

ChannelImageFilter::~ChannelImageFilter()
{
}

bool ChannelImageFilter::Transform(uint8_t *data, int width, int height)
{
	if (IsEnabled() == false) {
		return false;
	}

	int size = width*height*4;

	for (int i=0; i<size; i+=4) {
		data[i+3] = data[i+3] & _amask;
		data[i+2] = data[i+2] & _rmask;
		data[i+1] = data[i+1] & _gmask;
		data[i+0] = data[i+0] & _bmask;
	}

	return true;
}

}
