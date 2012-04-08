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
#include "videolayerimpl.h"

namespace jlwuit {

VideoLayerImpl *impl = NULL;

ISDTVPlayer::ISDTVPlayer()
{
	impl = (VideoLayerImpl *)jlwuit::Device::GetDefaultScreen()->GetLayerByID("video");
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

Control * ISDTVPlayer::GetControl(lwuit_media_control_t type)
{
	return NULL;
}

Component * ISDTVPlayer::GetVisualComponent()
{
	return NULL;
}

}
