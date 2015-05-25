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
#include "animation.h"

namespace jlwuit {

Animation::Animation()
{
	_delay = 0;
	_interval = 2000;
}

Animation::~Animation()
{
}

bool Animation::Animate()
{
	return false;
}

void Animation::SetDelay(int n)
{
	_delay = n;
}

int Animation::GetDelay()
{
	return _delay;
}

void Animation::SetInterval(int n)
{
	_interval = n;
}

int Animation::GetInterval()
{
	return _interval;
}

}
