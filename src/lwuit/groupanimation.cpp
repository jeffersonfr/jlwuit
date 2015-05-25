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
#include "groupanimation.h"

namespace jlwuit {

GroupAnimation::GroupAnimation()
{
}

GroupAnimation::~GroupAnimation()
{
}

void AddAnimation(Animation *animation)
{
	std::vector<Animation *>::iterator i = std::find(_animations.begin(), _animations.end(), animation);

	if (i == _animations.end()) {
		_animtions.push_back(animation);
	}
}

void Remove(Animation *animation)
{
	std::vector<Animation *>::iterator i = std::find(_animations.begin(), _animations.end(), animation);

	if (i != _animations.end()) {
		_animtions.erase(animation);
	}
}

void RemoveAll()
{
	_animations.clear();
}

void Reset()
{
	for (std::vector<Animation *>::iterator i=_animations.begin(); i!=_animations.end(); i++) {
		Animation *animation = (*i);

		animation->Reset();
	}
}

std::vector<Animation *> & GetAnimations()
{
	return _animations;
}

bool GroupAnimation::Animate()
{
	for (std::vector<Animation *>::iterator i=_animations.begin(); i!=_animations.end(); i++) {
		Animation *animation = (*i);

		animation->Animate();
	}

	return false;
}

void GroupAnimation::SetAnimationDelay(int delay)
{
}

int GroupAnimation::GetAnimationDelay()
{
	return -1;
}

void GroupAnimation::Paint(Graphics *g)
{
}

}
