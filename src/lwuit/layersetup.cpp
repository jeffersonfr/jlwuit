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
#include "layersetup.h"

namespace jlwuit {

LayerSetup::LayerSetup()
{
}

LayerSetup::~LayerSetup()
{
}

void LayerSetup::SetBounds(int x, int y, int w, int h)
{
}

void LayerSetup::SetBounds(struct lwuit_point_t point, struct lwuit_size_t size)
{
	SetBounds(point.x, point.y, size.width, size.height);
}

void LayerSetup::SetBounds(struct lwuit_region_t region)
{
	SetBounds(region.x, region.y, region.width, region.height);
}

void LayerSetup::SetLocation(int x, int y)
{
	SetBounds(x, y, GetWidth(), GetHeight());
}

void LayerSetup::SetLocation(struct lwuit_point_t point)
{
	SetLocation(point.x, point.y);
}

void LayerSetup::SetSize(int w, int h)
{
	SetBounds(GetX(), GetY(), w, h);
}

void LayerSetup::SetSize(struct lwuit_size_t size)
{
	SetBounds(GetX(), GetY(), size.width, size.height);
}

int LayerSetup::GetX()
{
	return GetBounds().x;
}

int LayerSetup::GetY()
{
	return GetBounds().x;
}

int LayerSetup::GetWidth()
{
	return GetBounds().width;
}

int LayerSetup::GetHeight()
{
	return GetBounds().height;
}

struct lwuit_point_t LayerSetup::GetLocation()
{
	struct lwuit_point_t t;

	t.x = GetBounds().x;
	t.y = GetBounds().y;

	return t;
}

struct lwuit_size_t LayerSetup::GetSize()
{
	struct lwuit_size_t t;

	t.width = GetBounds().width;
	t.height = GetBounds().height;

	return t;
}

struct lwuit_region_t LayerSetup::GetBounds()
{
	struct lwuit_region_t t;

	t.x = -1;
	t.y = -1;
	t.width = -1;
	t.height = -1;

	return t;
}

}
