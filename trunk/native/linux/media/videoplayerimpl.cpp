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

namespace jlwuit {

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
			std::cout << "VideoSizeControlImpl::GetDestination() not implemented." << std::endl;
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

VideoPlayerImpl::VideoPlayerImpl()
{
	_controls.push_back(new VideoSizeControlImpl(this));
	_controls.push_back(new VideoFormatControlImpl(this));
}

VideoPlayerImpl::~VideoPlayerImpl()
{
}

void VideoPlayerImpl::Play()
{
}

void VideoPlayerImpl::Pause()
{
}

void VideoPlayerImpl::Stop()
{
}

void VideoPlayerImpl::Resume()
{
}

void VideoPlayerImpl::Close()
{
}

void VideoPlayerImpl::SetMediaTime(uint64_t time)
{
}

uint64_t VideoPlayerImpl::GetMediaTime()
{
	return 0LL;
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
}

double VideoPlayerImpl::GetDecodeRate()
{
	return 0.0;
}

}
