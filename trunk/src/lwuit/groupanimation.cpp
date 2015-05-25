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

#include <algorithm>

namespace jlwuit {

GroupAnimation::GroupAnimation(janimation_mode_t mode, bool stack)
{
	_mode = mode;
	_stack = stack;
}

GroupAnimation::~GroupAnimation()
{
}

janimation_mode_t GroupAnimation::GetMode()
{
	return _mode;
}

void GroupAnimation::Add(Animation *animation)
{
	std::map<Animation *, bool>::iterator i = _animations.find(animation);

	if (i == _animations.end()) {
		_animations[animation] = true;
	}
}

void GroupAnimation::Remove(Animation *animation)
{
	std::map<Animation *, bool>::iterator i = _animations.find(animation);

	if (i != _animations.end()) {
		_animations.erase(i);
	}
}

void GroupAnimation::RemoveAll()
{
	_animations.clear();
}

void GroupAnimation::Reset()
{
	for (std::map<Animation *, bool>::iterator i=_animations.begin(); i!=_animations.end(); i++) {
		Animation *animation = i->first;

		animation->Reset();
	}
}

std::vector<Animation *> GroupAnimation::GetAnimations()
{
	std::vector<Animation *> t;

	for (std::map<Animation *, bool>::iterator i=_animations.begin(); i!=_animations.end(); i++) {
		Animation *animation = i->first;

		t.push_back(animation);
	}

	return t;
}

bool GroupAnimation::Animate()
{
	if (_animations.size() == 0) {
		return false;
	}

	if (_mode == JAM_SERIAL) {
		for (std::map<Animation *, bool>::iterator i=_animations.begin(); i!=_animations.end(); i++) {
			Animation *animation = i->first;

			if (i->second == false) {
				if (_stack == true) {
					animation->Animate();
				}
			} else {
				i->second = animation->Animate();

				return true;
			}
		}
	} else if (_mode == JAM_PARALLEL) {
		bool any = false;

		for (std::map<Animation *, bool>::iterator i=_animations.begin(); i!=_animations.end(); i++) {
			Animation *animation = i->first;

			if (i->second == false) {
				if (_stack == true) {
					animation->Animate();
				}
			} else {
				i->second = animation->Animate();

				any = true;
			}
		}

		if (any == true) {
			return true;
		}
	}

	return false;
}

}
