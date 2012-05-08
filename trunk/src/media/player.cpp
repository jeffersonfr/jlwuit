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
#include <stdio.h>

namespace jlwuit {

Player::Player()
{
}

Player::~Player()
{
	while (_controls.size() > 0) {
		Control *control = (*_controls.begin());

		_controls.erase(_controls.begin());

		delete control;
	}
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

std::vector<Control *> & Player::GetControls()
{
	return _controls;
}

Control * Player::GetControl(std::string id)
{
	for (std::vector<Control *>::iterator i=_controls.begin(); i!=_controls.end(); i++) {
		Control *control = (*i);

		if (control->GetID() == id) {
			return control;
		}
	}

	return NULL;
}

void Player::RegisterPlayerListener(PlayerEventListener *listener)
{
}

void Player::RemovePlayerListener(PlayerEventListener *listener)
{
}

}
