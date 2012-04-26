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
#include "brightnessimagefilter.h"

namespace jlwuit {

BrightnessImageFilter::BrightnessImageFilter(double factor)
{
	_factor = factor;
}

BrightnessImageFilter::~BrightnessImageFilter()
{
}

void BrightnessImageFilter::SetFactor(double factor)
{
	_factor = factor;
}

double BrightnessImageFilter::GetFactor()
{
	return _factor;
}

bool BrightnessImageFilter::Transform(uint8_t *data, int width, int height)
{
	if (IsEnabled() == false) {
		return false;
	}

	int size = width*height*4;

	for (int i=0; i<size; i+=4) {
		uint8_t a = data[i+3],
						r = data[i+2],
						g = data[i+1],
						b = data[i+0];

		data[i+3] = a;
		data[i+2] = PIXEL(r * _factor);
		data[i+1] = PIXEL(g * _factor);
		data[i+0] = PIXEL(b * _factor);
	}

	return true;
}

}
