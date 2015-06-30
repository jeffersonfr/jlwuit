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
#include "backgroundlayerimpl.h"
#include "videolayerimpl.h"
#include "device.h"

namespace jlwuit {

BackgroundLayerImpl::BackgroundLayerImpl():
	LayerImpl("background")
{
	jgui::jsize_t screen = jgui::GFXHandler::GetInstance()->GetScreenSize();

	_image = NULL;

	_red = 0x00;
	_green = 0x00;
	_blue = 0x00;

	_window = new jgui::Window(0, 0, screen.width, screen.height);

	_window->SetBorder(jgui::JCB_EMPTY);
	_window->SetUndecorated(true);
	_window->SetBackgroundColor(jgui::Color::Black);
}

BackgroundLayerImpl::~BackgroundLayerImpl()
{
	if (_window != NULL) {
		delete _window;
		_window = NULL;
	}
}

void BackgroundLayerImpl::Initialize()
{
	_window->Show();

	SetImage("resources/images/background.png");
}

void BackgroundLayerImpl::SetColor(Color color)
{
	_red = color.GetRed();
	_green = color.GetGreen();
	_blue = color.GetBlue();

	Repaint();
}

Color BackgroundLayerImpl::GetColor()
{
	return Color(_red, _green, _blue);
}
	
void BackgroundLayerImpl::SetImage(std::string image)
{
	_image_file = image;

	if (_image != NULL) {
		delete _image;
		_image = NULL;
	}

	_image = jgui::Image::CreateImage(image);

	Repaint();
}

bool BackgroundLayerImpl::IsEnabled()
{
	return _window->IsVisible();
}

void BackgroundLayerImpl::SetEnabled(bool b)
{
	return _window->SetVisible(b);
}

std::string BackgroundLayerImpl::GetImage()
{
	return _image_file;
}
	
LayerSetup * BackgroundLayerImpl::GetLayerSetup()
{
	return this;
}

void BackgroundLayerImpl::SetBounds(int x, int y, int w, int h)
{
	// _window->SetBounds(x, y, w, h);
}

struct lwuit_region_t BackgroundLayerImpl::GetBounds()
{
	jgui::jregion_t bounds = _window->GetVisibleBounds();

	struct lwuit_region_t t;

	t.x = bounds.x;
	t.y = bounds.y;
	t.width = bounds.width;
	t.height = bounds.height;
	
	return t;
}

void BackgroundLayerImpl::Repaint(jgui::Component *cmp)
{
	jgui::Graphics *g = _window->GetGraphics();

	if (g == NULL) {
		return;
	}

	g->Reset();

	Paint(g);

	g->Flip();
}

void BackgroundLayerImpl::Paint(jgui::Graphics *g)
{
	LayerSetup *setup = GetLayerSetup();

	if (_image != NULL) {
		g->DrawImage(_image, 0, 0, setup->GetWidth(), setup->GetHeight());
	} else {
		g->SetColor(_red, _green, _blue);
		g->FillRectangle(0, 0, setup->GetWidth(), setup->GetHeight());
	}

	// INFO:: clear video region
	jlwuit::Layer *layer = jlwuit::Device::GetDefaultScreen()->GetLayerByID("video");

	if (layer == NULL) {
		return;
	}

	lwuit_region_t vrect = layer->GetLayerSetup()->GetBounds();

	int rx = (int)(vrect.x),
		ry = (int)(vrect.y),
		rw = (int)(vrect.width),
		rh = (int)(vrect.height);

	g->Clear(rx, ry, rw, rh);
}

}
