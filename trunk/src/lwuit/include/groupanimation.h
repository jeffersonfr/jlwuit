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
#ifndef LWUIT_GROUPANIMATION_H
#define LWUIT_GROUPANIMATION_H

#include "animation.h"

#include <vector>
#include <map>

namespace jlwuit {

enum janimation_mode_t {
	JAM_SERIAL,
	JAM_PARALLEL
};

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class GroupAnimation : public Animation {

	protected:
		/** \brief */
		std::map<Animation *, bool> _animations;
		/** \brief */
		janimation_mode_t _mode;
		/** \brief */
		bool _stack;

	public:
		/**
		 * \brief
		 *
		 * \param mode serial or parallel
		 * \param stack if true, continues painting animations even if they have already finalized
		 *
		 */
		GroupAnimation(janimation_mode_t mode, bool stack);

		/**
		 * \brief
		 *
		 */
		virtual ~GroupAnimation();
		
		/**
		 * \brief
		 *
		 */
		virtual janimation_mode_t GetMode();

		/**
		 * \brief
		 *
		 */
		virtual void Add(Animation *animation);

		/**
		 * \brief
		 *
		 */
		virtual void Remove(Animation *animation);

		/**
		 * \brief
		 *
		 */
		virtual void RemoveAll();

		/**
		 * \brief
		 *
		 */
		virtual void Reset();

		/**
		 * \brief
		 *
		 */
		virtual bool Animate();

		/**
		 * \brief
		 *
		 */
		virtual std::vector<Animation *> GetAnimations();

};

}

#endif
