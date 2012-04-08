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
#include "coordinatelayout.h"
#include "component.h"

namespace jlwuit {

CoordinateLayout::CoordinateLayout(int width, int height, lwuit_coordinate_layout_t type)
{
	if (width <= 0 || height <= 0) {
		// throw Exception("CoordinateLayout cannot work with limits lower than zero");
	}

	_width = width;
	_height = height;
	_type = type;
}

CoordinateLayout::~CoordinateLayout()
{
}

void CoordinateLayout::SetWidth(int width)
{
	_width = width;
}

void CoordinateLayout::SetHeight(int height)
{
	_height = height;
}

void CoordinateLayout::SetType(lwuit_coordinate_layout_t type)
{
	_type = type;
}

int CoordinateLayout::GetWidth()
{
	return _width;
}

int CoordinateLayout::GetHeight()
{
	return _height;
}

lwuit_coordinate_layout_t CoordinateLayout::GetType()
{
	return _type;
}

struct lwuit_size_t CoordinateLayout::GetPreferredSize(Component *target) 
{
	if ((void *)target == NULL) {
		struct lwuit_size_t t = {0, 0};

		return t;
	}

	struct lwuit_margin_t insets = target->GetInsets();
	struct lwuit_size_t t = {0, 0};

	int members = target->GetComponents().size();

	for (int i=0; i<members; i++) {
		Component *cmp = target->GetComponents()[i];

		struct lwuit_point_t point = cmp->GetLocation();
		struct lwuit_size_t size = cmp->GetSize();

		t.width = std::max(t.width, point.x+size.width+(insets.left+insets.right));
		t.height = std::max(t.height, point.y+size.height+(insets.top+insets.bottom));
	}

	return t;
}

void CoordinateLayout::DoLayout(Component *target)
{
	if ((void *)target == NULL) {
		return;
	}

	struct lwuit_size_t tsize = target->GetSize();

	if (tsize.width <= 0 || tsize.height <= 0) {
		return;
	}

	int nmembers = target->GetComponents().size();

	double sx = 1.0,
				 sy = 1.0;

	if (_width < 0) {
		_width = tsize.width;
	}

	if (_height < 0) {
		_height = tsize.height;
	}

	if ((_type & LCL_HORIZONTAL) != 0) {
		sx = (double)tsize.width/_width;
	}

	if ((_type & LCL_VERTICAL) != 0) {
		sy = (double)tsize.height/_height;
	}

	for (int i = 0 ; i < nmembers ; i++) {
		Component *c = target->GetComponents()[i];

		struct lwuit_point_t point = c->GetLocation();
		struct lwuit_size_t size = c->GetPreferredSize();

		// c->SetLocation((int)(point.x*sx), (int)(point.y*sy));
		c->SetBounds((int)(point.x*sx), (int)(point.y*sy), size.width, size.height);
	}

	_width = tsize.width;
	_height = tsize.height;
}

}

