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
#include "lheimagefilter.h"

namespace jlwuit {

LHEImageFilter::LHEImageFilter(int factor)
{
	_factor = factor;
	_domain = 256;
}

LHEImageFilter::~LHEImageFilter()
{
}

void LHEImageFilter::SetFactor(int factor)
{
	_factor = factor;
}

int LHEImageFilter::GetFactor()
{
	return _factor;
}

void LHEImageFilter::SetDomain(int domain)
{
	_domain = domain;
}

int LHEImageFilter::GetDomain()
{
	return _domain;
}

bool LHEImageFilter::Transform(uint8_t *data, int width, int height)
{
	if (IsEnabled() == false) {
		return false;
	}

	int size = width*height*4;
  int left, 
			top, 
			right, 
			bottom;
	int acc[3],
			win[3][_domain];
	uint8_t buffer[size];

	acc[0] = 0;
	acc[1] = 0;
	acc[2] = 0;

	for (int j=0; j<3; j++) {
		for (int i=0; i<_domain; i++) {
			win[j][i] = 0;
		}
	}

	for (int i=0; i<size; i++) {
		buffer[i] = data[i];
	}

	for (int j=0; j<height-1; j++) {
		top = j-_factor;
    bottom = j+_factor;

		if (top < 0) {
			top = 0;
		}

		if (bottom > (height-1)) {
			bottom = height-1;
		}

		for (int i=0; i<width-1; i++) {
			int index = (j*width+i)*4;
			uint8_t a = buffer[index+3],
							r = buffer[index+2],
							g = buffer[index+1],
							b = buffer[index+0];

      left = i-_factor;
			right = i+_factor;

			if (left < 0) {
				left = 0;
			}

			if (right > (width-1)) {
				right = width-1;
			}

      for (int dx=left; dx<=right; dx++) {
        for (int dy=top; dy<=bottom; dy++) {
					int dindex = (dy*width+dx)*4;

					win[2][data[dindex + 2]]++;
					win[1][data[dindex + 1]]++;
					win[0][data[dindex + 0]]++;
        }
      }

      int length = (right-left+1)*(bottom-top+1);

			acc[0] = 0;
			acc[1] = 0;
			acc[2] = 0;

			for (int l=0; l<=data[index + 0]; l++) {
				acc[0] = acc[0] + win[0][l];
			}

			for (int l=0; l<=data[index + 1]; l++) {
				acc[1] = acc[1] + win[1][l];
			}

			for (int l=0; l<=data[index + 2]; l++) {
				acc[2] = acc[2] + win[2][l];
			}

			data[index+3] = a;
			data[index+2] = PIXEL(_domain*acc[2]/length);
			data[index+1] = PIXEL(_domain*acc[1]/length);
			data[index+0] = PIXEL(_domain*acc[0]/length);
			
      for (int dx=left; dx<=right; dx++) {
        for (int dy=top; dy<=bottom; dy++) {
					int dindex = (dy*width+dx)*4;

					win[2][data[dindex + 2]] = 0;
					win[1][data[dindex + 1]] = 0;
					win[0][data[dindex + 0]] = 0;
        }
      }
		}
	}

	return true;
}

}
