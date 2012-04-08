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
	LayerImpl("background", 1920, 1080)
{
	_image = NULL;

	_red = 0x00;
	_green = 0x00;
	_blue = 0x00;
}

BackgroundLayerImpl::~BackgroundLayerImpl()
{
}

void BackgroundLayerImpl::Initialize()
{
	if (_window != NULL) {
		_window->Show();
	}

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

std::string BackgroundLayerImpl::GetImage()
{
	return _image_file;
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
	lwuit_region_t vrect = layer->GetLayerSetup()->GetBounds();
	lwuit_size_t vscale = layer->GetLayerSetup()->GetWorkingScreenSize(),
		bscale = GetLayerSetup()->GetWorkingScreenSize();

	double sx = (double)bscale.width/(double)vscale.width,
		sy = (double)bscale.height/(double)bscale.height;
	int rx = (int)(vrect.x*sx),
		ry = (int)(vrect.y*sy),
		rw = (int)(vrect.width*sx),
		rh = (int)(vrect.height*sy);

	g->Clear(rx,ry, rw, rh);
	// g->Clear(vrect.x, vrect.y, vrect.width, vrect.height);
}

}

