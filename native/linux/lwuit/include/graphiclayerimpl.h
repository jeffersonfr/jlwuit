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
#ifndef GRAPHICLAYERIMPL_H
#define GRAPHICLAYERIMPL_H

#include "eventmanagerimpl.h"

#include "component.h"
#include "layerimpl.h"
#include "jcondition.h"
#include "jthread.h"
#include "jwindow.h"

namespace jlwuit {

class Scene;

class GraphicLayerImpl : public LayerImpl, public Component, public LayerSetup, public jthread::Thread {

	private:
		/** \brief */
		RootContainer *_root_container;
		/** \brief */
		jgui::Window *_window;
		/** \brief */
		std::vector<Scene *> _scenes;
		/** \brief */
		EventManagerImpl *_eventmanager;
		/** \brief */
		jthread::Mutex _mutex;
		/** \brief */
		jthread::Mutex _optirun_mutex;
		/** \brief */
		jthread::Condition _sem;
		/** \brief */
		jlwuit::lwuit_region_t dirty;
		/** \brief */
		Image *_buffer;
		/** \brief */
		bool _refresh;

	private:
		/**
		 * \brief
		 *
		 */
		virtual void Initialize();

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
		GraphicLayerImpl();

		/**
		 * \brief
		 *
		 */
		virtual ~GraphicLayerImpl();

		/**
		 * \brief
		 *
		 */
		virtual RootContainer * GetContainer();

		/**
		 * \brief
		 *
		 */
		virtual EventManager * GetEventManager();

		/**
		 * \brief
		 *
		 */
		virtual bool IsEnabled();

		/**
		 * \brief
		 *
		 */
		virtual void SetEnabled(bool b);

		/**
		 * \brief
		 *
		 */
		virtual void SetBounds(int x, int y, int w, int h);

		/**
		 * \brief
		 *
		 */
		virtual struct lwuit_region_t GetBounds();

		/**
		 * \brief
		 *
		 */
		virtual LayerSetup * GetLayerSetup();

		/**
		 * \brief
		 *
		 */
		virtual void Repaint(Component *cmp = NULL);
		
};

}

#endif
