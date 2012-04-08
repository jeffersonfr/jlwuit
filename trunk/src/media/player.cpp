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
#include "player.h"

namespace jlwuit {

Player::Player()
{
}

Player::~Player()
{
}

void Player::Play()
{
}

void Player::Pause()
{
}

void Player::Stop()
{
}

void Player::Resume()
{
}

void Player::Close()
{
}

void Player::SetMediaTime(uint64_t i)
{
}

uint64_t Player::GetMediaTime()
{
	return -1LL;
}

void Player::SetLoop(bool b)
{
}

bool Player::IsPlaying()
{
	return false;
}

bool Player::IsLoop()
{
	return false;
}

double Player::GetDecodeRate()
{
	return 0.0;
}

void Player::SetDecodeRate(double rate)
{
}

std::vector<Control *> Player::GetControls()
{
	std::vector<Control *> controls;

	return controls;
}

Control * Player::GetControl(lwuit_media_control_t type)
{
	return NULL;
}

Component * Player::GetVisualComponent()
{
	return NULL;
}

void Player::RegisterPlayerListener(PlayerEventListener *listener)
{
}

void Player::RemovePlayerListener(PlayerEventListener *listener)
{
}

}
