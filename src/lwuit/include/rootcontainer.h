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
class Dialog;

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class RootContainer : public Component {

	friend class Dialog;

	private:
		/** \brief */
		std::vector<Dialog *> _dialogs;
		/** \brief */
		jthread::Mutex _dialogs_mutex;

	private:
		/**
		 * \brief
		 *
		 */
		virtual void RegisterDialog(Dialog *dialog);
		
		/**
		 * \brief
		 *
		 */
		virtual void UnregisterDialog(Dialog *dialog);

		/**
		 * \brief
		 *
		 */
		virtual void PaintDialogs(Graphics *g);

	protected:
		/** \brief */
		Layer *_layer;

	protected:
		/**
		 * \brief
		 *
		 */
		RootContainer(Layer *layer, int x, int y, int w, int h);

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
		static RootContainer * GetContainer(Layer *layer);

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

		/**
		 * \brief
		 *
		 */
		virtual Component * GetTopLevelAncestor();

		/**
		 * \brief
		 *
		 */
		virtual void Paint(Graphics *g);

};

}

#endif
