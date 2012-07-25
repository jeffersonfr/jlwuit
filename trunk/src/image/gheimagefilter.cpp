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
#include "gheimagefilter.h"

#include <map>

#include <math.h>

namespace jlwuit {

GHEImageFilter::GHEImageFilter(int domain)
{
	_domain = domain;
}

GHEImageFilter::~GHEImageFilter()
{
}

void GHEImageFilter::SetDomain(int domain)
{
	_domain = domain;
}

int GHEImageFilter::GetDomain()
{
	return _domain;
}

bool GHEImageFilter::Transform(uint8_t *data, int width, int height)
{
	if (IsEnabled() == false) {
		return false;
	}

	int acc[3],
			win[3][_domain],
			sum[3][_domain];

	for (int j=0; j<3; j++) {
		acc[j] = 0;

		for (int i=0; i<_domain; i++) {
			win[j][i] = 0;
			sum[j][i] = 0;
		}
	}

	int size = width*height*4;

	for (int i=0; i<size; i+=4) {
		uint8_t // a = data[i+3],
						r = data[i+2],
						g = data[i+1],
						b = data[i+0];

		win[2][r]++;
		win[1][g]++;
		win[0][b]++;
	}

	double rc = _domain/(double)(width*height);

	for (int i=0; i<size; i+=4) {
		uint8_t a = data[i+3];
						// r = data[i+2],
						// g = data[i+1],
						// b = data[i+0];

		for (int l=0; l<3; l++) {
			if (sum[l][data[i + l]] != 0) {
				acc[l] = sum[l][data[i + l]];
			} else {
				acc[l] = 0;

				for (int k=0; k<data[i + l]; k++) {
					acc[l] += win[l][k];
				}

				sum[l][data[i + l]] = acc[l];
			}
		}

		data[i+3] = a;
		data[i+2] = PIXEL(acc[2]*rc);
		data[i+1] = PIXEL(acc[1]*rc);
		data[i+0] = PIXEL(acc[0]*rc);
	}

	return true;
}

}
