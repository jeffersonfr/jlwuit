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
#include "layersetupimpl.h"
#include "backgroundlayerimpl.h"
#include "device.h"

namespace jlwuit {

LayerSetupImpl::LayerSetupImpl(jgui::Window *window)
{
	_window = window;
}

LayerSetupImpl::~LayerSetupImpl()
{
}

void LayerSetupImpl::SetBounds(int x, int y, int w, int h)
{
	jgui::jregion_t bounds = _window->GetVisibleBounds();

	if (bounds.x == x && bounds.y == y && bounds.width == w && bounds.height == h) {
		return;
	}

	Layer *layer = jlwuit::Device::GetDefaultScreen()->GetLayerByID("background");

	_window->SetBounds(x, y, w, h);

	dynamic_cast<BackgroundLayerImpl *>(layer)->Repaint();
}

void LayerSetupImpl::SetBounds(struct lwuit_point_t point, struct lwuit_size_t size)
{
	SetBounds(point.x, point.y, size.width, size.height);
}

void LayerSetupImpl::SetBounds(struct lwuit_region_t region)
{
	SetBounds(region.x, region.y, region.width, region.height);
}

void LayerSetupImpl::SetLocation(int x, int y)
{
	SetBounds(x, y, GetWidth(), GetHeight());
}

void LayerSetupImpl::SetLocation(struct lwuit_point_t point)
{
	SetLocation(point.x, point.y);
}

void LayerSetupImpl::SetSize(int width, int height)
{
	SetBounds(GetX(), GetY(), width, height);
}

void LayerSetupImpl::SetSize(struct lwuit_size_t size)
{
	SetSize(size.width, size.height);
}

int LayerSetupImpl::GetX()
{
	return _window->GetX();
}

int LayerSetupImpl::GetY()
{
	return _window->GetY();
}

int LayerSetupImpl::GetWidth()
{
	return _window->GetWidth();
}

int LayerSetupImpl::GetHeight()
{
	return _window->GetHeight();
}

struct lwuit_point_t LayerSetupImpl::GetLocation()
{
	struct lwuit_point_t t;

	t.x = GetX();
	t.y = GetY();

	return t;
}

struct lwuit_size_t LayerSetupImpl::GetSize()
{
	struct lwuit_size_t t;

	t.width = GetWidth();
	t.height = GetHeight();

	return t;
}

struct lwuit_region_t LayerSetupImpl::GetBounds()
{
	struct lwuit_region_t t;

	t.x = GetX();
	t.y = GetY();
	t.width = GetWidth();
	t.height = GetHeight();

	return t;
}

}
