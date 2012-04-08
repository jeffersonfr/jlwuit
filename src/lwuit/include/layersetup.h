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
#ifndef LWUIT_LAYERSETUP_H
#define LWUIT_LAYERSETUP_H

#include "defines.h"

namespace jlwuit {

class LayerSetup {

	private:

	public:
		/**
		 * \brief
		 *
		 */
		LayerSetup();

		/**
		 * \brief
		 *
		 */
		virtual ~LayerSetup();

		/**
		 * \brief
		 *
		 */
		virtual void SetWorkingScreenSize(int w, int h);

		/**
		 * \brief
		 *
		 */
		virtual void SetWorkingScreenSize(lwuit_size_t size);

		/**
		 * \brief
		 *
		 */
		virtual void SetBounds(int x, int y, int w, int h);

		/**
		 * \brief
		 *
		 */
		virtual void SetBounds(struct lwuit_point_t point, struct lwuit_size_t size);

		/**
		 * \brief
		 *
		 */
		virtual void SetBounds(struct lwuit_region_t region);

		/**
		 * \brief
		 *
		 */
		virtual void SetLocation(int x, int y);

		/**
		 * \brief
		 *
		 */
		virtual void SetLocation(struct lwuit_point_t point);

		/**
		 * \brief
		 *
		 */
		virtual void SetSize(int width, int height);

		/**
		 * \brief
		 *
		 */
		virtual void SetSize(struct lwuit_size_t size);

		/**
		 * \brief
		 *
		 */
		virtual lwuit_size_t GetWorkingScreenSize();

		/**
		 * \brief
		 *
		 */
		virtual int GetX();

		/**
		 * \brief
		 *
		 */
		virtual int GetY();

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
		virtual struct lwuit_point_t GetLocation();

		/**
		 * \brief
		 *
		 */
		virtual struct lwuit_size_t GetSize();

		/**
		 * \brief
		 *
		 */
		virtual struct lwuit_region_t GetBounds();

};

}

#endif
