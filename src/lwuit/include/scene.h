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
#ifndef LWUIT_SCENE_H
#define LWUIT_SCENE_H

#include "component.h"
#include "lookandfeel.h"
#include "transition.h"

#include "jcommon/jtimer.h"

#include <vector>
#include <mutex>

namespace jlwuit {

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class Scene : public Component { // TODO::, public jthread::TimerTask {

	private:
		/** \brief */
		std::mutex _input_mutex;
		/** \brief */
		Scene *_activity;
		/** \brief */
		Component *_component;
		/** \brief */
		Transition *_transition_in;
		/** \brief */
		Transition *_transition_out;
		/** \brief */
		Transition *_default_transition_in;
		/** \brief */
		Transition *_default_transition_out;
		/** \brief */
		// TODO:: jthread::Timer _timer;

	private:
		/**
		 * \brief
		 *
		 */
		virtual void Run();

	public:
		/**
		 * \brief
		 *
		 */
		Scene(int x, int y, int w, int h);

		/**
		 * \brief
		 *
		 */
		virtual ~Scene();

		/**
		 * \brief
		 *
		 */
		virtual void InitImpl();

		/**
		 * \brief
		 *
		 */
		virtual void DeinitImpl();

		/**
		 * \brief
		 *
		 */
		virtual void Initialize();

		/**
		 * \brief
		 *
		 */
		virtual void Finalize();

		/**
		 * \brief
		 *
		 */
		virtual void StartActivity(Scene *scene);

		/**
		 * \brief
		 *
		 */
		virtual void SendToLayer(std::string layer);

		/**
		 * \brief
		 *
		 */
		virtual void SetAnimationDelay(int ms);

		/**
		 * \brief
		 *
		 */
		virtual int GetAnimationDelay();

		/**
		 * \brief
		 *
		 */
		virtual void SetTransitionIn(Transition *transition);

		/**
		 * \brief
		 *
		 */
		virtual void SetTransitionOut(Transition *transition);
		
		/**
		 * \brief
		 *
		 */
		virtual Transition * GetTransitionIn();

		/**
		 * \brief
		 *
		 */
		virtual Transition * GetTransitionOut();

		/**
		 * \brief
		 *
		 */
		virtual void Show();

		/**
		 * \brief
		 *
		 */
		virtual void Hide();

		/**
		 * \brief
		 *
		 */
		virtual bool OnKeyDown(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnKeyPress(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnKeyUp(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnKeyLongPress(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnMousePress(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnMouseRelease(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnMouseClick(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnMouseMove(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnMouseWheel(UserEvent *event);

};

}

#endif
