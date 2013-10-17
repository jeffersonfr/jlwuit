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
#include "volumecontrol.h"
#include "mediaexception.h"
#include "imageimpl.h"

#include "jautolock.h"
#include "jgfxhandler.h"

namespace jlwuit {

class VideoComponentImpl : public jlwuit::Component {

	public:
		/** \brief */
		jthread::Mutex _mutex;
		/** \brief */
		jlwuit::ImageImpl *_buffer;
		/** \brief */
		jgui::Image *_image;
		/** \brief */
		jlwuit::lwuit_region_t _src;
		/** \brief */
		jlwuit::lwuit_region_t _dst;
		/** \brief */
		bool _diff;

	public:
		VideoComponentImpl(int x, int y, int w, int h, int iw, int ih):
			jlwuit::Component(x, y, w, h),
			_mutex(jthread::JMT_RECURSIVE)
		{
			_buffer = new jlwuit::ImageImpl(_image = jgui::Image::CreateImage(w, h, jgui::JPF_ARGB, iw, ih));

			_src.x = 0;
			_src.y = 0;
			_src.width = w;
			_src.height = h;

			_dst.x = 0;
			_dst.y = 0;
			_dst.width = w;
			_dst.height = h;

			_diff = false;

			SetVisible(true);
		}

		virtual ~VideoComponentImpl()
		{
			delete _buffer;
		}

		virtual void Paint(jlwuit::Graphics *g)
		{
			jlwuit::Component::Paint(g);

			if (_diff == false) {
				g->DrawImage(_buffer, 0, 0, GetWidth(), GetHeight());
			} else {
				jlwuit::lwuit_region_t clip = g->GetClip();

				g->SetClip(0, 0, GetWidth(), GetHeight());
				g->DrawImage(_buffer, _src.x, _src.y, _src.width, _src.height, _dst.x, _dst.y, _dst.width, _dst.height);
				g->SetClip(clip.x, clip.y, clip.width, clip.height);
			}
		}

		virtual jgui::Image * GetImage()
		{
			return _image;
		}

		virtual jlwuit::Image * GetBuffer()
		{
			return _buffer;
		}

};

class VolumeControlImpl : public VolumeControl {
	
	private:
		/** \brief */
		VideoPlayerImpl *_player;
		/** \brief */
		int _level;
		/** \brief */
		bool _is_muted;

	public:
		VolumeControlImpl(VideoPlayerImpl *player):
			VolumeControl()
		{
			_player = player;
			_level = 50;
			_is_muted = false;
		}

		virtual ~VolumeControlImpl()
		{
		}

		virtual int GetLevel()
		{
			jthread::AutoLock lock(&_player->_mutex);

			float level = 0.0f;

			if (_player->_provider != NULL) {
				_player->_provider->GetVolume(_player->_provider, &level);
			}

			return (int)(level*100.0f);
		}

		virtual void SetLevel(int level)
		{
			jthread::AutoLock lock(&_player->_mutex);

			_level = level;

			if (_level <= 0) {
				_level = 0;
				_is_muted = true;
			} else {
				if (_level > 100) {
					_level = 100;
				}

				_is_muted = false;
			}

			if (_player->_provider != NULL) {
				_player->_provider->SetVolume(_player->_provider, _level/100.0f);
			}
		}
		
		virtual bool IsMuted()
		{
			return _is_muted;
		}

		virtual void SetMute(bool b)
		{
			jthread::AutoLock lock(&_player->_mutex);

			if (_is_muted == b) {
				return;
			}

			if (_is_muted == false) {
				float level = _level/100.0f;

				if (_player->_provider != NULL) {
					_player->_provider->SetVolume(_player->_provider, level);
				}
			} else {
				if (_player->_provider != NULL) {
					_player->_provider->SetVolume(_player->_provider, 0.0f);
				}
			}
		}

};

class VideoSizeControlImpl : public VideoSizeControl {
	
	private:
		VideoPlayerImpl *_player;

	public:
		VideoSizeControlImpl(VideoPlayerImpl *player):
			VideoSizeControl()
		{
			_player = player;
		}

		virtual ~VideoSizeControlImpl()
		{
		}

		virtual void SetSource(int x, int y, int w, int h)
		{
			jthread::AutoLock lock(&_player->_component->_mutex);
			
			_player->_component->_src.x = x;
			_player->_component->_src.y = y;
			_player->_component->_src.width = w;
			_player->_component->_src.height = h;
			
			_player->_component->_diff = false;

			if (_player->_component->_src.x != _player->_component->_dst.x ||
					_player->_component->_src.y != _player->_component->_dst.y ||
					_player->_component->_src.width != _player->_component->_dst.width ||
					_player->_component->_src.height != _player->_component->_dst.height) {
				_player->_component->_diff = true;
			}
		}

		virtual void SetDestination(int x, int y, int w, int h)
		{
			_player->_component->_dst.x = x;
			_player->_component->_dst.y = y;
			_player->_component->_dst.width = w;
			_player->_component->_dst.height = h;
			
			_player->_component->_diff = false;

			if (_player->_component->_src.x != _player->_component->_dst.x ||
					_player->_component->_src.y != _player->_component->_dst.y ||
					_player->_component->_src.width != _player->_component->_dst.width ||
					_player->_component->_src.height != _player->_component->_dst.height) {
				_player->_component->_diff = true;
			}
		}

		virtual lwuit_region_t GetSource()
		{
			return _player->_component->_src;
		}

		virtual lwuit_region_t GetDestination()
		{
			return _player->_component->_dst;
		}

};

class VideoFormatControlImpl : public VideoFormatControl {
	
	private:
		VideoPlayerImpl *_player;

	public:
		VideoFormatControlImpl(VideoPlayerImpl *player):
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
			jthread::AutoLock lock(&_player->_mutex);

			if (_player->_provider != NULL) {
				DFBColorAdjustment adj;

				adj.flags = (DFBColorAdjustmentFlags)(DCAF_CONTRAST);
				adj.contrast = value;

				_player->_provider->SetColorAdjustment(_player->_provider, &adj);
			}
		}

		virtual void SetSaturation(int value)
		{
			jthread::AutoLock lock(&_player->_mutex);

			if (_player->_provider != NULL) {
				DFBColorAdjustment adj;

				adj.flags = (DFBColorAdjustmentFlags)(DCAF_SATURATION);
				adj.saturation = value;

				_player->_provider->SetColorAdjustment(_player->_provider, &adj);
			}
		}

		virtual void SetHUE(int value)
		{
			jthread::AutoLock lock(&_player->_mutex);

			if (_player->_provider != NULL) {
				DFBColorAdjustment adj;

				adj.flags = (DFBColorAdjustmentFlags)(DCAF_HUE);
				adj.hue = value;

				_player->_provider->SetColorAdjustment(_player->_provider, &adj);
			}
		}

		virtual void SetBrightness(int value)
		{
			jthread::AutoLock lock(&_player->_mutex);

			if (_player->_provider != NULL) {
				DFBColorAdjustment adj;

				adj.flags = (DFBColorAdjustmentFlags)(DCAF_BRIGHTNESS);
				adj.brightness = value;

				_player->_provider->SetColorAdjustment(_player->_provider, &adj);
			}
		}

		virtual void SetSharpness(int value)
		{
			// TODO::
		}

		virtual lwuit_aspect_ratio_t GetAspectRatio()
		{
			jthread::AutoLock lock(&_player->_mutex);

			double aspect = _player->_aspect;

			if (aspect == (1.0/1.0)) {
				return LAR_1x1;
			} else if (aspect == (2.0/3.0)) {
				return LAR_2x3;
			} else if (aspect == (4.0/3.0)) {
				return LAR_4x3;
			} else if (aspect == (16.0/9.0)) {
				return LAR_16x9;
			}

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
			jthread::AutoLock lock(&_player->_mutex);

			if (_player->_provider != NULL) {
				DFBColorAdjustment adj;

				adj.flags = (DFBColorAdjustmentFlags)(DCAF_CONTRAST);

				_player->_provider->GetColorAdjustment(_player->_provider, &adj);
			
				return adj.contrast;
			}
				
			return 0;
		}

		virtual int GetSaturation()
		{
			jthread::AutoLock lock(&_player->_mutex);

			if (_player->_provider != NULL) {
				DFBColorAdjustment adj;

				adj.flags = (DFBColorAdjustmentFlags)(DCAF_SATURATION);

				_player->_provider->GetColorAdjustment(_player->_provider, &adj);
			
				return adj.saturation;
			}
				
			return 0;
		}

		virtual int GetHUE()
		{
			jthread::AutoLock lock(&_player->_mutex);

			if (_player->_provider != NULL) {
				DFBColorAdjustment adj;

				adj.flags = (DFBColorAdjustmentFlags)(DCAF_HUE);

				_player->_provider->GetColorAdjustment(_player->_provider, &adj);
			
				return adj.hue;
			}
				
			return 0;
		}

		virtual int GetBrightness()
		{
			jthread::AutoLock lock(&_player->_mutex);

			if (_player->_provider != NULL) {
				DFBColorAdjustment adj;

				adj.flags = (DFBColorAdjustmentFlags)(DCAF_BRIGHTNESS);

				_player->_provider->GetColorAdjustment(_player->_provider, &adj);
			
				return adj.brightness;
			}
				
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
	_is_paused = false;
	_decode_rate = 1.0;
	_is_loop = false;
	_is_closed = false;
	_has_audio = false;
	_has_video = false;
	_component = NULL;

	IDirectFB *directfb = (IDirectFB *)jgui::GFXHandler::GetInstance()->GetGraphicEngine();
	
	if (directfb->CreateVideoProvider(directfb, _file.c_str(), &_provider) != DFB_OK) {
		_provider = NULL;

		throw jlwuit::MediaException("Media format not supported");
	}
		
	DFBSurfaceDescription sdsc;
	DFBStreamDescription mdsc;
	
	_provider->SetPlaybackFlags(_provider, DVPLAY_NOFX);
	_provider->GetSurfaceDescription(_provider, &sdsc);
	_provider->GetStreamDescription(_provider, &mdsc);
	_provider->CreateEventBuffer(_provider, &_events);

	_aspect = 16.0/9.0;
	
	_media_info.title = std::string(mdsc.title);
	_media_info.author = std::string(mdsc.author);
	_media_info.album = std::string(mdsc.album);
	_media_info.genre = std::string(mdsc.genre);
	_media_info.comments = std::string(mdsc.comment);
	_media_info.year = mdsc.year;

	if (mdsc.caps & DVSCAPS_AUDIO) {
		_has_audio = true;
	
		_controls.push_back(new VolumeControlImpl(this));
	}

	if (mdsc.caps & DVSCAPS_VIDEO) {
		_has_video = true;
		_aspect = mdsc.video.aspect;

		_controls.push_back(new VideoSizeControlImpl(this));
		_controls.push_back(new VideoFormatControlImpl(this));
	}

	_component = new VideoComponentImpl(0, 0, sdsc.width, sdsc.height, sdsc.width, sdsc.height);

	Start();
}

VideoPlayerImpl::~VideoPlayerImpl()
{
	Close();
	
	delete _component;
	_component = NULL;

	for (std::vector<Control *>::iterator i=_controls.begin(); i!=_controls.end(); i++) {
		Control *control = (*i);

		delete control;
	}

	_controls.clear();
}

void VideoPlayerImpl::Callback(void *ctx)
{
	jlwuit::Component *cmp = reinterpret_cast<jlwuit::Component *>(ctx);
	
	if (cmp->IsVisible() != false) {
		cmp->Repaint();
	}
}
		
void VideoPlayerImpl::Play()
{
	jthread::AutoLock lock(&_mutex);

	if (_is_paused == false && _provider != NULL) {
		jgui::Graphics *graphics = dynamic_cast<VideoComponentImpl *>(_component)->GetImage()->GetGraphics();

		if (_has_video == true) {
			_provider->PlayTo(_provider, (IDirectFBSurface *)graphics->GetNativeSurface(), NULL, VideoPlayerImpl::Callback, (void *)_component);
		} else {
			_provider->PlayTo(_provider, (IDirectFBSurface *)graphics->GetNativeSurface(), NULL, NULL, NULL);
		}

		usleep(500000);
	}
}

void VideoPlayerImpl::Pause()
{
	jthread::AutoLock lock(&_mutex);

	if (_is_paused == false) {
		_is_paused = true;
		_decode_rate = GetDecodeRate();

		SetDecodeRate(0.0);
		
		DispatchPlayerEvent(new PlayerEvent(this, LPE_PAUSED));
	}
}

void VideoPlayerImpl::Resume()
{
	jthread::AutoLock lock(&_mutex);

	if (_is_paused == true) {
		_is_paused = false;

		SetDecodeRate(_decode_rate);
		
		DispatchPlayerEvent(new PlayerEvent(this, LPE_RESUMED));
	}
}

void VideoPlayerImpl::Stop()
{
	jthread::AutoLock lock(&_mutex);

	if (_provider != NULL) {
		_provider->Stop(_provider);

		if (_has_video == true) {
			_component->Repaint();
		}

		_is_paused = false;
	}
}

void VideoPlayerImpl::Close()
{
	jthread::AutoLock lock(&_mutex);

	if (_is_closed == true) {
		return;
	}

	_is_closed = true;

	WaitThread();

	if (_provider != NULL) {
		// INFO:: cause crashes when release and create players
		//_events->Release(_events);
		_events = NULL;

		_provider->Release(_provider);
		_provider = NULL;
	}
}

void VideoPlayerImpl::SetCurrentTime(uint64_t time)
{
	jthread::AutoLock lock(&_mutex);

	if (_provider != NULL) {
		_provider->SeekTo(_provider, (double)time/1000.0);
	}
}

uint64_t VideoPlayerImpl::GetCurrentTime()
{
	jthread::AutoLock lock(&_mutex);

	double time = 0.0;

	if (_provider != NULL) {
		_provider->GetPos(_provider, &time);
	}

	return (uint64_t)(time*1000LL);
}

uint64_t VideoPlayerImpl::GetMediaTime()
{
	jthread::AutoLock lock(&_mutex);

	double time = 0.0;

	if (_provider != NULL) {
		_provider->GetLength(_provider, &time);
	}

	return (uint64_t)(time*1000LL);
}

void VideoPlayerImpl::SetLoop(bool b)
{
	jthread::AutoLock lock(&_mutex);

	_is_loop = b;

	if (_provider != NULL) {
		if (_is_loop == false) {
			_provider->SetPlaybackFlags(_provider, DVPLAY_NOFX);
		} else {
			_provider->SetPlaybackFlags(_provider, DVPLAY_LOOPING);
		}
	}
}

bool VideoPlayerImpl::IsLoop()
{
	return _is_loop;
}

void VideoPlayerImpl::SetDecodeRate(double rate)
{
	jthread::AutoLock lock(&_mutex);

	if (rate != 0.0) {
		_is_paused = false;
	}

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

void VideoPlayerImpl::Run()
{
	while (_is_closed == false) {
		_events->WaitForEventWithTimeout(_events, 0, 100);

		while (_events->HasEvent(_events) == DFB_OK) {
			DFBVideoProviderEvent event;

			_events->GetEvent(_events, DFB_EVENT(&event));

			if (event.clazz == DFEC_VIDEOPROVIDER) {
				// TODO:: disparar eventos de midia
				if (event.type == DVPET_STARTED) {
					DispatchPlayerEvent(new PlayerEvent(this, LPE_STARTED));
				} else if (event.type == DVPET_STOPPED) {
					DispatchPlayerEvent(new PlayerEvent(this, LPE_STOPPED));
				} else if (event.type == DVPET_FINISHED) {
					DispatchPlayerEvent(new PlayerEvent(this, LPE_FINISHED));
				}
			}
		}
	}
}

void VideoPlayerImpl::DispatchPlayerEvent(PlayerEvent *event)
{
	if (event == NULL) {
		return;
	}

	int k = 0,
			size = (int)_player_listeners.size();

	while (k++ < (int)_player_listeners.size()) {
		PlayerEventListener *listener = _player_listeners[k-1];

		if (event->GetType() == LPE_STARTED) {
			listener->MediaStarted(event);
		} else if (event->GetType() == LPE_PAUSED) {
			listener->MediaPaused(event);
		} else if (event->GetType() == LPE_RESUMED) {
			listener->MediaResumed(event);
		} else if (event->GetType() == LPE_STOPPED) {
			listener->MediaStopped(event);
		} else if (event->GetType() == LPE_FINISHED) {
			listener->MediaFinished(event);
		}

		if (size != (int)_player_listeners.size()) {
			size = (int)_player_listeners.size();

			k--;
		}
	}

	delete event;
}

}
