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
#ifndef LWUIT_ROOTCONTAINER_H
#define LWUIT_ROOTCONTAINER_H

#include "component.h"
#include "userevent.h"

#include "jtimer.h"

namespace jlwuit {

class Scene;
class Layer;

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class RootContainer : public Component {

	protected:
		Layer *_layer;

	protected:
		/**
		 * \brief
		 *
		 */
		RootContainer(Layer *layer, int x, int y, int width, int height);

	public:
		/**
		 * \brief
		 *
		 */
		virtual ~RootContainer();

		/**
		 * \brief
		 *
		 */
		Layer * GetLayer();

		/**
		 * \brief
		 *
		 */
		virtual void Add(Component *c, int index);

		/**
		 * \brief
		 *
		 */
		virtual void Add(Component *c);

		/**
		 * \brief
		 *
		 */
		virtual void Add(Component *c, GridBagConstraints *constraints);

		/**
		 * \brief
		 *
		 */
		virtual void Add(Component *c, std::string align);

};

}

#endif
