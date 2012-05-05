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
#ifndef LAYERIMPL_H
#define LAYERIMPL_H

#include "layer.h"
#include "rootcontainer.h"

#include "jwindow.h"

#include <vector>

namespace jlwuit {

class LayerImpl : public Layer {

	protected:
		jgui::Window *_window;
		LayerSetup *_setup;
		RootContainer *_root_container;

	public:
		/**
		 * \brief Constructor.
		 *
		 */
		LayerImpl(std::string id, int width, int height);

		/**
		 * \brief
		 *
		 */
		virtual ~LayerImpl();

		/**
		 * \brief
		 *
		 */
		virtual void Initialize();

		/**
		 * \brief
		 *
		 */
		RootContainer * GetRootContainer();

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
		virtual LayerSetup * GetLayerSetup();

		/**
		 * \brief
		 *
		 */
		virtual void Repaint(jgui::Component *cmp = NULL);

		/**
		 * \brief
		 *
		 */
		virtual void Paint(jgui::Graphics *g);

};

}

#endif
