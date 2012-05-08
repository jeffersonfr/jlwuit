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
#include "layerimpl.h"
#include "layersetupimpl.h"

#include "jautolock.h"

#include <algorithm>

namespace jlwuit {

LayerImpl::LayerImpl(std::string id, int width, int height):
	Layer(id)
{
	_root_container = NULL;

	_window = new jgui::Window(0, 0, width, height, width, height);

	_window->SetBorder(jgui::JCB_EMPTY);
	_window->SetUndecorated(true);
	_window->SetBackgroundColor(jgui::Color::Black);

	_setup = new LayerSetupImpl(_window);
}

LayerImpl::~LayerImpl()
{
	if (_window != NULL) {
		delete _window;
		_window = NULL;
	}
}

void LayerImpl::Initialize()
{
}

RootContainer * LayerImpl::GetContainer()
{
	return _root_container;
}

bool LayerImpl::IsEnabled()
{
	return _window->IsVisible();
}

void LayerImpl::SetEnabled(bool b)
{
	_window->SetVisible(b);
}

void LayerImpl::Repaint(jgui::Component *cmp)
{
	jgui::Graphics *g = _window->GetGraphics();

	if (g == NULL) {
		return;
	}

	g->Reset();
	g->SetWorkingScreenSize(_window->GetWorkingScreenSize());

	Paint(g);

	g->Flip();
}

void LayerImpl::Paint(jgui::Graphics *g)
{
}

LayerSetup * LayerImpl::GetLayerSetup()
{
	return _setup;
}

}
