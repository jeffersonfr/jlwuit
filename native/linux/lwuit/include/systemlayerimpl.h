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
#ifndef SYSTEMLAYERIMPL_H
#define SYSTEMLAYERIMPL_H

#include "component.h"
#include "layerimpl.h"

#include "jthread.h"

namespace jlwuit {

class Scene;

class SystemLayerImpl : public LayerImpl, public Component, public jthread::Thread {

	private:
		std::vector<Scene *> _scenes;
		jthread::Mutex _mutex;
		jthread::Condition _sem;
		Image *_buffer;
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
		virtual void Refresh();

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
		SystemLayerImpl();

		/**
		 * \brief
		 *
		 */
		virtual ~SystemLayerImpl();

			/**
		 * \brief
		 *
		 */
		virtual void Repaint(Component *cmp = NULL);
		
		/**
		 * \brief
		 *
		 */
		virtual void Paint(Graphics *g);
		
};

}

#endif
