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
#include "isdtvplayerimpl.h"
#include "device.h"
#include "controlexception.h"
#include "videosizecontrol.h"
#include "videolayerimpl.h"

namespace jlwuit {

VideoLayerImpl *impl = NULL;

class ISDTVSizeControlImpl : public VideoSizeControl {
	
	private:
		LayerSetup *_setup;

	public:
		ISDTVSizeControlImpl(LayerSetup *setup):
			VideoSizeControl()
		{
			_setup = setup;
		}

		virtual ~ISDTVSizeControlImpl()
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

ISDTVPlayerImpl::ISDTVPlayerImpl()
{
	impl = (VideoLayerImpl *)jlwuit::Device::GetDefaultScreen()->GetLayerByID("video");

	_controls.push_back(new ISDTVSizeControlImpl(impl->GetLayerSetup()));
}

ISDTVPlayerImpl::~ISDTVPlayerImpl()
{
}

void ISDTVPlayerImpl::Play()
{
	impl->Play();
}

void ISDTVPlayerImpl::Pause()
{
}

void ISDTVPlayerImpl::Stop()
{
	impl->Stop();
}

void ISDTVPlayerImpl::Resume()
{
}

void ISDTVPlayerImpl::Close()
{
}

uint64_t ISDTVPlayerImpl::GetMediaTime()
{
	return impl->GetMediaTime();
}

uint64_t ISDTVPlayerImpl::GetCurrentTime()
{
	return impl->GetCurrentTime();
}

void ISDTVPlayerImpl::SetLoop(bool b)
{
}

bool ISDTVPlayerImpl::IsPlaying()
{
	return false;
}

bool ISDTVPlayerImpl::IsLoop()
{
	return false;
}

}
