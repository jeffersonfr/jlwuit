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
#include "videolayerimpl.h"
#include "imageimpl.h"
#include "jgfxhandler.h"
#include "preferences.h"
#include "jautolock.h"

namespace jlwuit {

VideoLayerImpl::VideoLayerImpl():
	LayerImpl("video", DEFAULT_SCALE_WIDTH, DEFAULT_SCALE_HEIGHT)
{
	_provider = NULL;
}

VideoLayerImpl::~VideoLayerImpl()
{
	if (_provider != NULL) {
		_provider->Release(_provider);
	}
}

void VideoLayerImpl::Initialize()
{
	if (_window != NULL) {
		_window->Show();
	}

	jlwuit::Document *ds = jlwuit::Preferences::Create("system");
	jlwuit::Element *es = ds->GetElementByIndex(0);
	jlwuit::Document *dc = jlwuit::Preferences::Create("channels");
	jlwuit::Element *ec = dc->GetElementByIndex(es->GetIntegerParam("channel"));

	if (ec->GetTextParam("type") == "local") {
		SetFile(ec->GetTextParam("path"));
	
		Play();
	} else {
		std::cout << "Video source <" << ec->GetTextParam("type") << "> not supported !" << std::endl;
	}
}

void VideoLayerImpl::Callback(void *ctx)
{
	reinterpret_cast<VideoLayerImpl *>(ctx)->Repaint();
}

void VideoLayerImpl::SetFile(std::string file)
{
	jthread::AutoLock lock(&_mutex);

	_file = file;

	IDirectFB *directfb = (IDirectFB *)jgui::GFXHandler::GetInstance()->GetGraphicEngine();

	if (directfb->CreateVideoProvider(directfb, _file.c_str(), &_provider) != DFB_OK) {
		_provider = NULL;

		return;
	}
		
	IDirectFBDisplayLayer *layer = NULL;
	IDirectFBWindow *window = NULL;
	IDirectFBSurface *surface = NULL;
	DFBSurfaceDescription sdsc;
	DFBWindowDescription desc;

	desc.flags = (DFBWindowDescriptionFlags)(DWDESC_POSX | DWDESC_POSY | DWDESC_WIDTH | DWDESC_HEIGHT | DWDESC_STACKING);
	desc.stacking = DWSC_LOWER;
	desc.posx = 0;
	desc.posy = 0;
	desc.width = jgui::GFXHandler::GetInstance()->GetScreenWidth();
	desc.height = jgui::GFXHandler::GetInstance()->GetScreenHeight();

	_provider->GetSurfaceDescription(_provider, &sdsc);

	if (sdsc.flags & DSDESC_CAPS) {
		desc.flags = (DFBWindowDescriptionFlags)(desc.flags | DWDESC_SURFACE_CAPS);
		desc.surface_caps = sdsc.caps;
	}

	directfb->GetDisplayLayer(directfb, DLID_PRIMARY, &layer);
	layer->CreateWindow(layer, &desc, &window);
	window->GetSurface(window, &surface);
	window->SetOpacity(window, 0xff);

	// TODO:: delete previous native window

	_window->SetNativeWindow(window);
}

void VideoLayerImpl::Play() 
{
	jthread::AutoLock lock(&_mutex);

	if (_provider != NULL) {
		IDirectFBSurface *surface = (IDirectFBSurface *)_window->GetGraphics()->GetNativeSurface();

		_provider->PlayTo(_provider, surface, NULL, VideoLayerImpl::Callback, (void *)this);

		usleep(500000);
	}
}

void VideoLayerImpl::Stop() 
{
	jthread::AutoLock lock(&_mutex);

	if (_provider != NULL) {
		_provider->Stop(_provider);
		_window->Repaint();
	}
}

void VideoLayerImpl::SetDecodeRate(double rate)
{
	jthread::AutoLock lock(&_mutex);

	if (_provider != NULL) {
		_provider->SetSpeed(_provider, rate);
	}
}

double VideoLayerImpl::GetDecodeRate()
{
	jthread::AutoLock lock(&_mutex);

	double rate = 1.0;

	if (_provider != NULL) {
		_provider->GetSpeed(_provider, &rate);
	}

	return rate;
}

void VideoLayerImpl::SetMediaTime(int64_t time)
{
	jthread::AutoLock lock(&_mutex);

	if (_provider != NULL) {
		_provider->SeekTo(_provider, time/1000LL);
	}
}

int64_t VideoLayerImpl::GetMediaTime()
{
	jthread::AutoLock lock(&_mutex);

	double time = 0.0;

	if (_provider != NULL) {
		_provider->GetPos(_provider, &time);
	}

	return time*1000LL;
}

};

