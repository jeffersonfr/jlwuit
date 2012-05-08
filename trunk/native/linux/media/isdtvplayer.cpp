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
#include "isdtvplayer.h"
#include "device.h"
#include "controlexception.h"
#include "videosizecontrol.h"
#include "videolayerimpl.h"

namespace jlwuit {

VideoLayerImpl *impl = NULL;

class ISDTVSizeControl : public VideoSizeControl {
	
	private:
		LayerSetup *_setup;

	public:
		ISDTVSizeControl(LayerSetup *setup):
			VideoSizeControl()
		{
			_setup = setup;
		}

		virtual ~ISDTVSizeControl()
		{
		}

		virtual void SetSource(int x, int y, int w, int h)
		{
			throw ControlException("Main player cannot set source bounds");
		}

		virtual void SetDestination(int x, int y, int w, int h)
		{
			_setup->SetBounds(x, y, w, h);
		}

		virtual lwuit_region_t GetSource()
		{
			return GetDestination();
		}

		virtual lwuit_region_t GetDestination()
		{
			return _setup->GetBounds();
		}

};

ISDTVPlayer::ISDTVPlayer()
{
	impl = (VideoLayerImpl *)jlwuit::Device::GetDefaultScreen()->GetLayerByID("video");

	_controls.push_back(new ISDTVSizeControl(impl->GetLayerSetup()));
}

ISDTVPlayer::~ISDTVPlayer()
{
}

void ISDTVPlayer::Play()
{
	impl->Play();
}

void ISDTVPlayer::Pause()
{
}

void ISDTVPlayer::Stop()
{
	impl->Stop();
}

void ISDTVPlayer::Resume()
{
}

void ISDTVPlayer::Close()
{
}

void ISDTVPlayer::SetMediaTime(uint64_t time)
{
	impl->SetMediaTime(time);
}

uint64_t ISDTVPlayer::GetMediaTime()
{
	return impl->GetMediaTime();
}

void ISDTVPlayer::SetLoop(bool b)
{
}

bool ISDTVPlayer::IsPlaying()
{
	return false;
}

bool ISDTVPlayer::IsLoop()
{
	return false;
}

void ISDTVPlayer::SetDecodeRate(double rate)
{
	impl->SetDecodeRate(rate);
}

double ISDTVPlayer::GetDecodeRate()
{
	return impl->GetDecodeRate();
}

}
