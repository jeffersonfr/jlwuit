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
#include "goldenimagefilter.h"

#include <stdlib.h>
#include <math.h>

namespace jlwuit {

GoldenImageFilter::GoldenImageFilter(double period)
{
	_period = period;
}

GoldenImageFilter::~GoldenImageFilter()
{
}

void GoldenImageFilter::SetPeriod(double period)
{
	_period = period;
}

double GoldenImageFilter::GetPeriod()
{
	return _period;
}

bool GoldenImageFilter::Transform(uint8_t *data, int width, int height)
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
		uint8_t c = PIXEL(r * 0.30 + g * 0.59 + b * 0.11);

    c = PIXEL(abs((int)(0xff*sin((double)(M_PI*c)*k))));

    if (c <= 55) {
      r = PIXEL(3.45*c);
      g = PIXEL(c);
      b = 0x00;
    } else if (c > 55 && c <= 155) {
      r = PIXEL(0.65*(c - 55) + 190);
      g = PIXEL(1.35*(c - 55) + 55);
      b = PIXEL(0.50*(c - 55));
    } else if (c > 155) {
      r = 0xff;
      g = PIXEL(0.65*(c - 155) + 190);
      b = PIXEL(2.05*(c - 155) + 50);
    }

		data[i+3] = a;
		data[i+2] = r;
		data[i+1] = g;
		data[i+0] = b;
	}

	return true;
}

}
