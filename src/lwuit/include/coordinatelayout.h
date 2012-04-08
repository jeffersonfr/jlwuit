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
#ifndef LWUIT_COORDINATELAYOUT_H
#define LWUIT_COORDINATELAYOUT_H

#include "layout.h"

#include <iostream>
#include <cstdlib>
#include <map>

namespace jlwuit {

class Component;

/**
 * \brief
 *
 */
enum lwuit_coordinate_layout_t {
	LCL_HORIZONTAL	= 1,
	LCL_VERTICAL		= 2
};

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class CoordinateLayout : public Layout {

	private:
		lwuit_coordinate_layout_t _type;
		int _width,
			_height;

	public:
		/**
		 * \brief
		 *
		 */
		CoordinateLayout(int width = -1, int height = -1, lwuit_coordinate_layout_t type = (lwuit_coordinate_layout_t)(LCL_HORIZONTAL | LCL_VERTICAL));
		
		/**
		 * \brief
		 *
		 */
		virtual ~CoordinateLayout();

		/**
		 * \brief
		 *
		 */
		virtual void SetWidth(int width);
		
		/**
		 * \brief
		 *
		 */
		virtual void SetHeight(int height);
		
		/**
		 * \brief
		 *
		 */
		virtual void SetType(lwuit_coordinate_layout_t type);

		/**
		 * \brief
		 *
		 */
		virtual int GetWidth();
		
		/**
		 * \brief
		 *
		 */
		virtual int GetHeight();
		
		/**
		 * \brief
		 *
		 */
		virtual lwuit_coordinate_layout_t GetType();

		/**
		 * \brief
		 *
		 */
		virtual struct lwuit_size_t GetPreferredSize(Component *target);

		/**
		 * \brief
		 *
		 */
		virtual void DoLayout(Component *parent);

};

}

#endif

