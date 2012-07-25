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
#include "heimagefilter.h"

#include <algorithm>

namespace jlwuit {

HEImageFilter::HEImageFilter()
{
}

HEImageFilter::~HEImageFilter()
{
}

bool HEImageFilter::Transform(uint8_t *data, int width, int height)
{
	if (IsEnabled() == false) {
		return false;
	}

	int size = width*height*4;
	uint8_t min_r = 0xff,
					min_g = 0xff,
					min_b = 0xff;
	uint8_t max_r = 0x00,
					max_g = 0x00,
					max_b = 0x00;

	for (int i=0; i<size; i+=4) {
		uint8_t // a = data[i+3],
						r = data[i+2],
						g = data[i+1],
						b = data[i+0];
      
		min_r = std::min(min_r, r);
		min_g = std::min(min_g, g);
		min_b = std::min(min_b, b);

		max_r = std::max(max_r, r);
		max_g = std::max(max_g, g);
		max_b = std::max(max_b, b);
	}

	for (int i=0; i<size; i+=4) {
		uint8_t a = data[i+3],
						r = data[i+2],
						g = data[i+1],
						b = data[i+0];

		data[i+3] = a;
		data[i+2] = PIXEL(255.0*(r-min_r)/(max_r-min_r));
		data[i+1] = PIXEL(255.0*(g-min_g)/(max_g-min_g));
		data[i+0] = PIXEL(255.0*(b-min_b)/(max_b-min_b));
	}

	return true;
}

}
