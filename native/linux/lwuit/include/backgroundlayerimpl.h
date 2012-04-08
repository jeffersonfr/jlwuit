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
#ifndef BACKGROUNDLAYERIMPL_H
#define BACKGROUNDLAYERIMPL_H

#include "color.h"
#include "layerimpl.h"

#include "jimage.h"

namespace jlwuit {

class BackgroundLayerImpl : public LayerImpl {

	private:
		jgui::Image *_image;
		std::string _image_file;
		int _red,
				_green,
				_blue;

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
		virtual void Paint(jgui::Graphics *g);

	public:
		/**
		 * \brief
		 *
		 */
		BackgroundLayerImpl();

		/**
		 * \brief
		 *
		 */
		virtual ~BackgroundLayerImpl();

		/**
		 * \brief
		 *
		 */
		virtual void SetColor(Color color);

		/**
		 * \brief
		 *
		 */
		virtual Color GetColor();

		/**
		 * \brief
		 *
		 */
		virtual void SetImage(std::string image);

		/**
		 * \brief
		 *
		 */
		virtual std::string GetImage();

};

}

#endif
