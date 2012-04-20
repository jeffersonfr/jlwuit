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
#include "jautolock.h"

namespace jlwuit {

VideoLayerImpl::VideoLayerImpl():
	LayerImpl("video", 1920, 1080)
{
	_provider = NULL;

	_buffer = jgui::Image::CreateImage(GetLayerSetup()->GetWidth(), GetLayerSetup()->GetHeight());
}

VideoLayerImpl::~VideoLayerImpl()
{
}

void VideoLayerImpl::Initialize()
{
	if (_window != NULL) {
		_window->Show();
	}

	SetFile("channels/channel0");
	
	Play();
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
		return;
	}
}

void VideoLayerImpl::Play() 
{
	jthread::AutoLock lock(&_mutex);

	if (_provider != NULL) {
		IDirectFBSurface *surface = (IDirectFBSurface *)_buffer->GetGraphics()->GetNativeSurface();

		_provider->PlayTo(_provider, surface, NULL, VideoLayerImpl::Callback, this);
	}
}

void VideoLayerImpl::Stop() 
{
	jthread::AutoLock lock(&_mutex);

	if (_provider != NULL) {
		_provider->Stop(_provider);
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

void VideoLayerImpl::Paint(jgui::Graphics *g)
{
	struct lwuit_region_t region = GetLayerSetup()->GetBounds();

	g->DrawImage(_buffer, 0, 0, region.width, region.height);
	// CHANGE:: g->Flip();
}

};

