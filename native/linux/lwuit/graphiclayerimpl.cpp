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
#include "imageimpl.h"
#include "scene.h"

#include "jgui/jbufferedimage.h"

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
			_layer_impl->Repaint(cmp);
		}

};

GraphicLayerImpl::GraphicLayerImpl():
	LayerImpl("graphics")
{
	jgui::jsize_t<int> screen = {1920, 1080}; // TODO:: jgui::GFXHandler::GetInstance()->GetScreenSize();

	_refresh = false;

	_theme.SetIntegerParam("window.bg", uint32_t(jgui::jcolor_name_t::Black));
	_theme.SetIntegerParam("window.border.type", jgui::JCB_EMPTY);

	_window = new jgui::Window({screen.width, screen.height});

	_window->SetTheme(_theme);
	_window->SetUndecorated(true);

	_root_container = new RootContainerImpl(this, this, 0, 0, screen.width, screen.height);
	_buffer = new ImageImpl(new jgui::BufferedImage(jgui::JPF_ARGB, screen));

	_eventmanager = new EventManagerImpl();

  // TODO::
	// _window->GetInputManager()->RegisterKeyListener(_eventmanager);
	// _window->GetInputManager()->RegisterMouseListener(_eventmanager);
}

GraphicLayerImpl::~GraphicLayerImpl()
{
	if (_window != NULL) {
		delete _window;
		_window = NULL;
	}
  
  _thread.join();
}

void GraphicLayerImpl::Initialize()
{
	// TODO:: _window->Show();

	// TODO:: _ng = _window->GetGraphics();
	_ni = dynamic_cast<ImageImpl *>(_buffer)->_native_image;
	_lg = _buffer->GetGraphics();

	_ng->Clear();

  _thread = std::thread(&GraphicLayerImpl::Run, this);
}

RootContainer * GraphicLayerImpl::GetContainer()
{
	return _root_container;
}

EventManager * GraphicLayerImpl::GetEventManager()
{
	return _eventmanager;
}

bool GraphicLayerImpl::IsEnabled()
{
	return _window->IsVisible();
}

void GraphicLayerImpl::SetEnabled(bool b)
{
	_window->SetVisible(b);
}

void GraphicLayerImpl::SetBounds(int x, int y, int w, int h)
{
	// _window->SetBounds(x, y, w, h);
}

struct lwuit_region_t GraphicLayerImpl::GetBounds()
{
	jgui::jrect_t bounds = _window->GetVisibleBounds();

	struct lwuit_region_t t;

	t.x = bounds.point.x;
	t.y = bounds.point.y;
	t.width = bounds.size.width;
	t.height = bounds.size.height;
	
	return t;
}

LayerSetup * GraphicLayerImpl::GetLayerSetup()
{
	return this;
}

void GraphicLayerImpl::Run()
{
	while (true) {
    {
      std::unique_lock<std::mutex> lock(_mutex);

      while (_refresh == false) {
        _sem.wait(lock);
      }

      _refresh = false;

      _optirun_mutex.lock();

      _lg->Reset();
      _lg->Clear();

      if (_root_container->IsVisible() == true) {
        _root_container->InvalidateAll();
        _root_container->Paint(_lg);
        _root_container->RevalidateAll();
      }
    }

		_ng->SetCompositeFlags(jgui::JCF_SRC);
		_ng->DrawImage(_ni, jgui::jpoint_t<int>{0, 0});
		// TODO:: _ng->Flip();
		_optirun_mutex.unlock();
	}
}

void GraphicLayerImpl::Repaint(jlwuit::Component *cmp)
{
  std::unique_lock<std::mutex> lock(_mutex);

	if (_refresh == true) {
		return;
	}

	// INFO:: otimization for small updates made by static components that call "Repaint(cmp)"
	if (cmp != NULL) {
		lwuit_point_t location = cmp->GetAbsoluteLocation();
		lwuit_size_t size = cmp->GetSize();

    std::unique_lock<std::mutex> lock(_optirun_mutex);

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

		_lg->Reset();
		_lg->Clear(location.x, location.y, size.width, size.height);

		if (parent->IsVisible() == true) {
			lwuit_point_t t = parent->GetAbsoluteLocation();

			_lg->Translate(t.x, t.y);
			parent->Paint(_lg);
			_lg->Translate(-t.x, -t.y);
			parent->Revalidate();
		}

		_ng->DrawImage(_ni, {location.x, location.y, size.width, size.height}, jgui::jpoint_t<int>{location.x, location.y});
		// TODO:: _ng->Flip(location.x, location.y, size.width, size.height);

		return;
	}

	_refresh = true;

	_sem.notify_all();
}

}
