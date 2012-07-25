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
#include "sharpimagefilter.h"

namespace jlwuit {

SharpImageFilter::SharpImageFilter(int factor)
{
	_factor = factor;
}

SharpImageFilter::~SharpImageFilter()
{
}

void SharpImageFilter::SetFactor(int factor)
{
	_factor = factor;
}

int SharpImageFilter::GetFactor()
{
	return _factor;
}

bool SharpImageFilter::Transform(uint8_t *data, int width, int height)
{
	if (IsEnabled() == false) {
		return false;
	}

  int left, 
			top, 
			right, 
			bottom;
	int size = width*height*4;
	uint8_t buffer[size];

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
			uint8_t a = buffer[index+3];
							// r = buffer[index+2],
							// g = buffer[index+1],
							// b = buffer[index+0];

      left = i-_factor;
			right = i+_factor;

			if (left < 0) {
				left = 0;
			}

			if (right > (width-1)) {
				right = width-1;
			}

  		int mediaR = 0, 
					mediaG = 0, 
					mediaB = 0;

      for (int dx=left; dx<=right; dx++) {
        for (int dy=top; dy<=bottom; dy++) {
					int dindex = (dy*width+dx)*4;

          // mediaA = mediaA + data[dindex+3];
          mediaR = mediaR + buffer[dindex+2];
          mediaG = mediaG + buffer[dindex+1];
          mediaB = mediaB + buffer[dindex+0];
        }
      }

      int length = (right-left+1)*(bottom-top+1);

			data[index+3] = a;
			data[index+2] = mediaR/length;
			data[index+1] = mediaG/length;
			data[index+0] = mediaB/length;
		}
	}

	return true;
}

}
