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

jgui::Graphics *g = NULL;
jgui::Image *img = NULL;
Graphics *gb = NULL;

class RootContainerImpl : public RootContainer {

	public:
		RootContainerImpl(Layer *layer, Component *parent, int x, int y, int w, int h):
			RootContainer(layer, x, y, w, h)
		{
			SetParent(parent);
						
			GetStyle()->SetIntegerParam("bg.color", 0x00000000);
		}

		virtual ~RootContainerImpl()
		{
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

	g = _window->GetGraphics();
	img = dynamic_cast<ImageImpl *>(_buffer)->_native_image;
	gb = _buffer->GetGraphics();

	g->SetBlittingFlags(jgui::JBF_NOFX);
	g->Clear();

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

		Paint(gb);

		_mutex.Unlock();

		g->DrawImage(img, 0, 0);
		g->Flip();

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
		int absx = cmp->GetAbsoluteX(),
				absy = cmp->GetAbsoluteY();
		int cmpw = cmp->GetWidth(),
				cmph = cmp->GetHeight();

		_optirun_mutex.Lock();

		Paint(gb);

		g->DrawImage(img, absx, absy, cmpw, cmph, absx, absy);
		g->Flip(absx, absy, cmpw, cmph);

		_optirun_mutex.Unlock();

		return;
	}

	_refresh = true;

	_sem.Notify();
}

void GraphicLayerImpl::Paint(jlwuit::Graphics *g)
{
	g->Reset();
	g->Clear();

	if (_root_container->IsVisible() == true) {
		_root_container->InvalidateAll();
		_root_container->Paint(g);
		_root_container->RevalidateAll();
	}
}

}
