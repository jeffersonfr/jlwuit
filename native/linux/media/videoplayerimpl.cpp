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

#include "jgui/jbufferedimage.h"
#include "jmedia/jvolumecontrol.h"
#include "jmedia/jvideosizecontrol.h"
#include "jmedia/jvideoformatcontrol.h"
#include "jmedia/jvideodevicecontrol.h"
#include "jmedia/jplayermanager.h"
#include "jevent/jframegrabberlistener.h"

namespace jlwuit {

class VideoComponentImpl : public jlwuit::Component, public jevent::FrameGrabberListener {

	public:
		std::mutex _mutex;
		jgui::Image *_image;
		jlwuit::ImageImpl *_buffer;
		jlwuit::lwuit_region_t _src;
		jlwuit::lwuit_region_t _dst;
		bool _diff;

	public:
		VideoComponentImpl(int x, int y, int w, int h):
			jlwuit::Component(x, y, w, h)
			// TODOO:: _mutex(jthread::JMT_RECURSIVE)
		{
			_image = new jgui::BufferedImage(jgui::JPF_ARGB, {w, h});
			_buffer = new jlwuit::ImageImpl(_image);

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
			_mutex.lock();

			if (_buffer != NULL) {
				delete _buffer;
				_buffer = NULL;
			}

			if (_image != NULL) {
				delete _image;
				_image = NULL;
			}

			_mutex.unlock();
		}

		virtual void FrameGrabbed(jevent::FrameGrabberEvent *event)
		{
			jgui::Image *image = reinterpret_cast<jgui::Image *>(event->GetSource());
			
			_mutex.lock();

      jgui::jsize_t size = image->GetSize();
			uint32_t *ptr = NULL;

			image->GetGraphics()->GetRGBArray(ptr, {0, 0, size.width, size.height});
			_image->GetGraphics()->SetRGBArray(ptr, {0, 0, size.width, size.height});

			delete [] ptr;
			
			_mutex.unlock();
		}

		virtual void Paint(jlwuit::Graphics *g)
		{
			jlwuit::Component::Paint(g);

			_mutex.lock();

      jlwuit::lwuit_size_t size = GetSize();

			if (_diff == false) {
				g->DrawImage(_buffer, 0, 0, size.width, size.height);
			} else {
				jlwuit::lwuit_region_t clip = g->GetClip();

				g->SetClip(0, 0, size.width, size.height);
				g->DrawImage(_buffer, _src.x, _src.y, _src.width, _src.height, _dst.x, _dst.y, _dst.width, _dst.height);
				g->SetClip(clip.x, clip.y, clip.width, clip.height);
			}

			_mutex.unlock();
		}

};

class VolumeControlImpl : public VolumeControl {
	
	private:
		/** \brief */
		jmedia::VolumeControl *_control;
		/** \brief */
		int _level;
		/** \brief */
		bool _is_muted;

	public:
		VolumeControlImpl(VideoPlayerImpl *impl):
			VolumeControl()
		{
			jmedia::Control *control = impl->_player->GetControl("audio.volume");

			if (control != NULL) {
				_control = dynamic_cast<jmedia::VolumeControl *>(control);
			}

			_level = 50;
			_is_muted = false;
		}

		virtual ~VolumeControlImpl()
		{
		}

		virtual int GetLevel()
		{
			if (_control != NULL) {
				return _control->GetLevel();
			}

			return 0;
		}

		virtual void SetLevel(int level)
		{
			if (_control != NULL) {
				return _control->SetLevel(level);
			}
		}
		
		virtual bool IsMuted()
		{
			if (_control != NULL) {
				return _control->IsMute();
			}

			return false;
		}

		virtual void SetMute(bool b)
		{
			if (_control != NULL) {
				return _control->SetMute(b);
			}
		}

};

class VideoSizeControlImpl : public VideoSizeControl {
	
	private:
		jmedia::VideoSizeControl *_control;

	public:
		VideoSizeControlImpl(VideoPlayerImpl *impl):
			VideoSizeControl()
		{
			jmedia::Control *control = impl->_player->GetControl("video.size");

			if (control != NULL) {
				_control = dynamic_cast<jmedia::VideoSizeControl *>(control);
			}
		}

		virtual ~VideoSizeControlImpl()
		{
		}

		virtual void SetSource(int x, int y, int w, int h)
		{
			if (_control != NULL) {
				_control->SetSource(x, y, w, h);
			}
		}

		virtual void SetDestination(int x, int y, int w, int h)
		{
			if (_control != NULL) {
				_control->SetDestination(x, y, w, h);
			}
		}

		virtual lwuit_region_t GetSource()
		{
			lwuit_region_t t;

			if (_control != NULL) {
				jgui::jrect_t src = _control->GetSource();

				t.x = src.point.x;
				t.y = src.point.y;
				t.width = src.size.width;
				t.height = src.size.height;
			}

			return t;
		}

		virtual lwuit_region_t GetDestination()
		{
			lwuit_region_t t;

			if (_control != NULL) {
				jgui::jrect_t src = _control->GetDestination();

				t.x = src.point.x;
				t.y = src.point.y;
				t.width = src.size.width;
				t.height = src.size.height;
			}

			return t;
		}

};

class VideoDeviceControlImpl : public jmedia::VideoDeviceControl {
	
	private:
		jmedia::VideoDeviceControl *_control;

	public:
		VideoDeviceControlImpl(VideoPlayerImpl *impl):
			VideoDeviceControl()
		{
			_control = dynamic_cast<jmedia::VideoDeviceControl *>(impl->_player->GetControl("video.device"));
		}

		virtual ~VideoDeviceControlImpl()
		{
		}

		virtual const std::vector<jmedia::jvideo_control_t> & GetControls()
		{
			if (_control != NULL) {
				return _control->GetControls();
			}

			return jmedia::VideoDeviceControl::GetControls();
		}

		virtual bool HasControl(jmedia::jvideo_control_t id)
		{
			if (_control != NULL) {
				return _control->HasControl(id);
			}
			
			return false;
		}

		virtual int GetValue(jmedia::jvideo_control_t id)
		{
			if (_control != NULL) {
				return _control->GetValue(id);
			}
			
			return 0;
		}

		virtual bool SetValue(jmedia::jvideo_control_t id, int value)
		{
			if (_control != NULL) {
				return _control->SetValue(id, value);
			}

			return 0;
		}

		virtual void Reset(jmedia::jvideo_control_t id)
		{
			if (_control != NULL) {
				return _control->Reset(id);
			}
		}

};

VideoPlayerImpl::VideoPlayerImpl(std::string file)
{
	jmedia::PlayerManager::SetHint(jmedia::JPH_LIGHTWEIGHT, true);

	_player = jmedia::PlayerManager::CreatePlayer(file);

	jgui::Component *cmp = _player->GetVisualComponent();
  jgui::jsize_t size = cmp->GetSize();

	VideoComponentImpl *impl = new VideoComponentImpl(0, 0, size.width, size.height);

	_player->RegisterFrameGrabberListener(impl);

	_component = impl;
}

VideoPlayerImpl::~VideoPlayerImpl()
{
	_player->Close();

	delete _player;
	_player = NULL;
	
	delete _component;
	_component = NULL;
}

void VideoPlayerImpl::Play()
{
	_player->Play();
}

void VideoPlayerImpl::Pause()
{
	_player->Pause();
}

void VideoPlayerImpl::Resume()
{
	_player->Resume();
}

void VideoPlayerImpl::Stop()
{
	_player->Stop();
}

void VideoPlayerImpl::Close()
{
	_player->Close();
}

void VideoPlayerImpl::SetCurrentTime(uint64_t time)
{
	_player->SetCurrentTime(time);
}

uint64_t VideoPlayerImpl::GetCurrentTime()
{
	return _player->GetCurrentTime();
}

uint64_t VideoPlayerImpl::GetMediaTime()
{
	return _player->GetMediaTime();
}

void VideoPlayerImpl::SetLoop(bool b)
{
	return _player->SetLoop(b);
}

bool VideoPlayerImpl::IsLoop()
{
	return _player->IsLoop();
}

Component * VideoPlayerImpl::GetVisualComponent()
{
	return _component;
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

void VideoPlayerImpl::MediaStarted(jevent::PlayerEvent *event)
{
	DispatchPlayerEvent(new PlayerEvent(this, LPE_STARTED));
}

void VideoPlayerImpl::MediaResumed(jevent::PlayerEvent *event)
{
	DispatchPlayerEvent(new PlayerEvent(this, LPE_RESUMED));
}

void VideoPlayerImpl::MediaPaused(jevent::PlayerEvent *event)
{
	DispatchPlayerEvent(new PlayerEvent(this, LPE_PAUSED));
}

void VideoPlayerImpl::MediaStopped(jevent::PlayerEvent *event)
{
	DispatchPlayerEvent(new PlayerEvent(this, LPE_STOPPED));
}

void VideoPlayerImpl::MediaFinished(jevent::PlayerEvent *event)
{
	DispatchPlayerEvent(new PlayerEvent(this, LPE_FINISHED));
}

}
