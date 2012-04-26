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
#include "metalicimagefilter.h"

#include <stdlib.h>
#include <math.h>

namespace jlwuit {

MetalicImageFilter::MetalicImageFilter(double period)
{
	_period = period;
}

MetalicImageFilter::~MetalicImageFilter()
{
}

void MetalicImageFilter::SetPeriod(double period)
{
	_period = period;
}

double MetalicImageFilter::GetPeriod()
{
	return _period;
}

bool MetalicImageFilter::Transform(uint8_t *data, int width, int height)
{
	if (IsEnabled() == false) {
		return false;
	}

	double k = _period/256.0;
	int size = width*height*4;

	for (int i=0; i<size; i+=4) {
		uint8_t a = data[i+3],
						r = data[i+2],
						g = data[i+1],
						b = data[i+0];
		uint8_t _y = PIXEL(0.299*r + 0.587*g + 0.114*b),
						_i = PIXEL(0.596*r - 0.274*g - 0.322*b),
						_q = PIXEL(0.211*r - 0.523*g + 0.312*b);

    _y = PIXEL(abs((int)(255*sin((double)(3.1415*_y)*k))));

		data[i+3] = a;
		data[i+2] = PIXEL(_y + 0.956*_i + 0.621*_q);
		data[i+1] = PIXEL(_y - 0.272*_i - 0.647*_q);
		data[i+0] = PIXEL(_y - 1.105*_i + 1.702*_q);
	}

	return true;
}

}
