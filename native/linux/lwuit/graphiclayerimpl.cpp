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
#include "graphiclayerimpl.h"
#include "scene.h"
#include "imageimpl.h"

namespace jlwuit {

jgui::Graphics *_ng = NULL;
jgui::Image *_ni = NULL;
jlwuit::Graphics *_lg = NULL;

class RootContainerImpl : public RootContainer {

	private:
		GraphicLayerImpl *_layer_impl;

	public:
		RootContainerImpl(GraphicLayerImpl *layer, Component *parent, int x, int y, int w, int h):
			RootContainer(layer, x, y, w, h)
		{
			_layer_impl = layer;

			GetStyle()->SetIntegerParam("bg.color", 0x00000000);
		}

		virtual ~RootContainerImpl()
		{
		}

		virtual void Repaint(jlwuit::Component *cmp)
		{
			_layer_impl->Repaint();
		}

};

GraphicLayerImpl::GraphicLayerImpl():
	LayerImpl("graphics", DEFAULT_SCALE_WIDTH, DEFAULT_SCALE_HEIGHT)
{
	_refresh = false;

	LayerSetup *setup = GetLayerSetup();
	int w = setup->GetWidth(),
			h = setup->GetHeight();

	_root_container = new RootContainerImpl(this, this, 0, 0, w, h);
	_buffer = new ImageImpl(jgui::Image::CreateImage(w, h, jgui::JPF_ARGB, w, h));
}

GraphicLayerImpl::~GraphicLayerImpl()
{
}

void GraphicLayerImpl::Initialize()
{
	if (_window != NULL) {
		_window->Show();
	}

	_window->Show();

	_ng = _window->GetGraphics();
	_ni = dynamic_cast<ImageImpl *>(_buffer)->_native_image;
	_lg = _buffer->GetGraphics();

	_ng->SetBlittingFlags(jgui::JBF_NOFX);
	_ng->Clear();

	Start();
}

void GraphicLayerImpl::Run()
{
	while (true) {
		_mutex.Lock();

		while (_refresh == false) {
			_sem.Wait(&_mutex);
		}

		_refresh = false;
		_optirun_mutex.Lock();
		
		_lg->Reset();
		_lg->Clear();

		if (_root_container->IsVisible() == true) {
			_root_container->InvalidateAll();
			_root_container->Paint(_lg);
			_root_container->RevalidateAll();
		}

		_mutex.Unlock();
		_ng->DrawImage(_ni, 0, 0);
		_ng->Flip();
		_optirun_mutex.Unlock();
	}
}

void GraphicLayerImpl::Repaint(jlwuit::Component *cmp)
{
	jthread::AutoLock lock(&_mutex);

	if (_refresh == true) {
		return;
	}

	// INFO:: otimization for small updates made by components's call "cmp->Repaint(cmp)"
	if (cmp != NULL) {
		lwuit_point_t location = cmp->GetAbsoluteLocation();
		lwuit_size_t size = cmp->GetSize();

		jthread::AutoLock lock(&_optirun_mutex);

		Component *parent = cmp,
			*last_parent = parent;

		while (parent != NULL) {
			lwuit_point_t plocation = parent->GetAbsoluteLocation();

			parent->Invalidate();

			for (std::vector<Component *>::iterator i=parent->GetComponents().begin(); i!=parent->GetComponents().end(); i++) {
				Component *c = (*i);
				lwuit_region_t t = c->GetBounds();

				if (cmp->Intersects(location.x, location.y, size.width, size.height, plocation.x+t.x, plocation.y+t.y, t.width, t.height) == true) {
					c->Invalidate();
				}
			}

			last_parent = parent;

			if (parent->IsOpaque() == true) {
				break;
			}

			parent = parent->GetParent();
		}

		parent = last_parent;

		/*
		jgui::Image *ni = jgui::Image::CreateImage(size.width, size.height, jgui::JPF_ARGB, size.width, size.height);
		jlwuit::Image *li = new ImageImpl(ni);
		jlwuit::Graphics *lg = li->GetGraphics();

		if (parent->IsVisible() == true) {
			lwuit_point_t t = parent->GetAbsoluteLocation();

			lg->Translate(t.x, t.y);
			parent->Paint(lg);
			lg->Translate(-t.x, -t.y);
			parent->Revalidate();
		}

		_ng->DrawImage(ni, location.x, location.y);
		_ng->Flip(location.x, location.y, size.width, size.height);
		
		delete li;
		*/

		_lg->SetClip(location.x, location.y, size.width, size.height);

		if (parent->IsVisible() == true) {
			lwuit_point_t t = parent->GetAbsoluteLocation();

			_lg->Translate(t.x, t.y);
			parent->Paint(_lg);
			_lg->Translate(-t.x, -t.y);
			parent->Revalidate();
		}

		_ng->DrawImage(_ni, location.x, location.y);
		_ng->Flip(location.x, location.y, size.width, size.height);

		return;
	}

	_refresh = true;

	_sem.Notify();
}

}
