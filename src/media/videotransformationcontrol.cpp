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
#include "videotransformationcontrol.h"

namespace jlwuit {

VideoTransformationControl::VideoTransformationControl():
	Control(LMC_VIDEO_TRANSFORMATION)
{
}

VideoTransformationControl::~VideoTransformationControl()
{
}

void VideoTransformationControl::SetLocation(int x, int y)
{
}

void VideoTransformationControl::SetSize(int width, int height)
{
}

void VideoTransformationControl::SetBounds(int x, int y, int width, int height)
{
}

int VideoTransformationControl::GetX()
{
	return 0;
}

int VideoTransformationControl::GetY()
{
	return 0;
}

int VideoTransformationControl::GetWidth()
{
	return 0;
}

int VideoTransformationControl::GetHeight()
{
	return 0;
}

}
