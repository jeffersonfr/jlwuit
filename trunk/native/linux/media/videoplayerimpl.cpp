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
#include "videoplayerimpl.h"
#include "controlexception.h"
#include "videosizecontrol.h"
#include "videoformatcontrol.h"
#include "mediaexception.h"
#include "imageimpl.h"

#include "jautolock.h"
#include "jgfxhandler.h"

namespace jlwuit {

class VideoComponentImpl : public jlwuit::Component {

	private:
		jlwuit::ImageImpl *_buffer;

	public:
		VideoComponentImpl(int x, int y, int w, int h, int iw, int ih):
			jlwuit::Component(x, y, w, h)
		{
			_buffer = new jlwuit::ImageImpl(jgui::Image::CreateImage(w, h, jgui::JPF_ARGB, w, h));
		}

		virtual ~VideoComponentImpl()
		{
			delete _buffer;
		}

		virtual void Paint(jlwuit::Graphics *g)
		{
			g->DrawImage(_buffer, 0, 0, GetWidth(), GetHeight());
		}

		virtual jlwuit::Image * GetBuffer()
		{
			return _buffer;
		}

}

class VideoSizeControlImpl : public VideoSizeControl {
	
	private:
		Player *_player;

	public:
		VideoSizeControlImpl(Player *player):
			VideoSizeControl()
		{
			_player = player;
		}

		virtual ~VideoSizeControlImpl()
		{
		}

		virtual void SetSource(int x, int y, int w, int h)
		{
			throw ControlException("Main player cannot set source bounds");
		}

		virtual void SetDestination(int x, int y, int w, int h)
		{
		}

		virtual lwuit_region_t GetSource()
		{
			return GetDestination();
		}

		virtual lwuit_region_t GetDestination()
		{
			throw jlwuit::MediaException("VideoSizeControlImpl::GetDestination() not implemented");
		}

};

class VideoFormatControlImpl : public VideoFormatControl {
	
	private:
		Player *_player;

	public:
		VideoFormatControlImpl(Player *player):
			VideoFormatControl()
		{
			_player = player;
		}

		virtual ~VideoFormatControlImpl()
		{
		}

		virtual void SetAspectRatio(lwuit_aspect_ratio_t t)
		{
		}

		virtual void SetContentMode(lwuit_video_mode_t t)
		{
		}

		virtual void SetVideoFormatHD(lwuit_hd_video_format_t vf)
		{
		}

		virtual void SetVideoFormatSD(lwuit_sd_video_format_t vf)
		{
		}

		virtual void SetContrast(int value)
		{
		}

		virtual void SetSaturation(int value)
		{
		}

		virtual void SetHUE(int value)
		{
		}

		virtual void SetBrightness(int value)
		{
		}

		virtual void SetSharpness(int value)
		{
		}

		virtual lwuit_aspect_ratio_t GetAspectRatio()
		{
			return LAR_16x9;
		}

		virtual lwuit_video_mode_t GetContentMode()
		{
			return LVM_FULL;
		}

		virtual lwuit_hd_video_format_t GetVideoFormatHD()
		{
			return LHVF_1080p;
		}

		virtual lwuit_sd_video_format_t GetVideoFormatSD()
		{
			return LSVF_PAL_M;
		}

		virtual int GetContrast()
		{
			return 0;
		}

		virtual int GetSaturation()
		{
			return 0;
		}

		virtual int GetHUE()
		{
			return 0;
		}

		virtual int GetBrightness()
		{
			return 0;
		}

		virtual int GetSharpness()
		{
			return 0;
		}

};

VideoPlayerImpl::VideoPlayerImpl(std::string file)
{
	_file = file;

	IDirectFB *directfb = (IDirectFB *)jgui::GFXHandler::GetInstance()->GetGraphicEngine();

	if (directfb->CreateVideoProvider(directfb, _file.c_str(), &_provider) != DFB_OK) {
		_provider = NULL;

		throw jlwuit::MediaException("Media format not supported");
	}
		
	DFBSurfaceDescription sdsc;
	
	_provider->GetSurfaceDescription(_provider, &sdsc);

	_component = new VideoComponentImpl(0, 0, sdsc.width, sdsc.height);

	_controls.push_back(new VideoSizeControlImpl(this));
	_controls.push_back(new VideoFormatControlImpl(this));
}

VideoPlayerImpl::~VideoPlayerImpl()
{
	if (_provider != NULL) {
		_provider->Release(_provider);
	}
}

void VideoPlayerImpl::Callback(void *ctx)
{
	// TODO:: otimizacao
	// if (random() < 80%) {
	// 	draw()
	// } 
	// return;
	reinterpret_cast<VideoPlayerImpl *>(ctx)->GetVisualComponent()->Repaint();
}
		
void VideoPlayerImpl::Play()
{
	jthread::AutoLock lock(&_mutex);

	if (_provider != NULL) {
		IDirectFBSurface *surface = (IDirectFBSurface *)_component->GetBuffer()->GetGraphics()->GetNativeSurface();

		_provider->PlayTo(_provider, surface, NULL, VideoPlayerImpl::Callback, (void *)this);

		usleep(500000);
	}
}

void VideoPlayerImpl::Pause()
{
}

void VideoPlayerImpl::Stop()
{
	jthread::AutoLock lock(&_mutex);

	if (_provider != NULL) {
		_provider->Stop(_provider);
		_window->Repaint();
	}
}

void VideoPlayerImpl::Resume()
{
}

void VideoPlayerImpl::Close()
{
}

void VideoPlayerImpl::SetMediaTime(uint64_t time)
{
	jthread::AutoLock lock(&_mutex);

	if (_provider != NULL) {
		_provider->SeekTo(_provider, time/1000LL);
	}
}

uint64_t VideoPlayerImpl::GetMediaTime()
{
	jthread::AutoLock lock(&_mutex);

	double time = 0.0;

	if (_provider != NULL) {
		_provider->GetPos(_provider, &time);
	}

	return time*1000LL;
}

void VideoPlayerImpl::SetLoop(bool b)
{
}

bool VideoPlayerImpl::IsPlaying()
{
	return false;
}

bool VideoPlayerImpl::IsLoop()
{
	return false;
}

void VideoPlayerImpl::SetDecodeRate(double rate)
{
	jthread::AutoLock lock(&_mutex);

	if (_provider != NULL) {
		_provider->SetSpeed(_provider, rate);
	}
}

double VideoPlayerImpl::GetDecodeRate()
{
	jthread::AutoLock lock(&_mutex);

	double rate = 1.0;

	if (_provider != NULL) {
		_provider->GetSpeed(_provider, &rate);
	}

	return rate;
}

Component * VideoPlayerImpl::GetVisualComponent()
{
	return _component;
}

}
