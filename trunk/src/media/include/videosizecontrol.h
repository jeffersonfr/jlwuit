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
#ifndef LWUIT_VIDEOSIZECONTROL_H
#define LWUIT_VIDEOSIZECONTROL_H

#include "control.h"
#include "defines.h"

namespace jlwuit {

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class VideoSizeControl : public Control {

	public:
		/**
		 * \brief
		 *
		 */
		VideoSizeControl();

		/**
		 * \brief Destrutor virtual.
		 *
		 */
		virtual ~VideoSizeControl();

		/**
		 * \brief
		 *
		 */
		virtual void SetSource(lwuit_region_t t);

		/**
		 * \brief
		 *
		 */
		virtual void SetDestination(lwuit_region_t t);

		/**
		 * \brief
		 *
		 */
		virtual void SetSource(int x, int y, int width, int height);

		/**
		 * \brief
		 *
		 */
		virtual void SetDestination(int x, int y, int width, int height);

		/**
		 * \brief
		 *
		 */
		virtual lwuit_region_t GetSource();

		/**
		 * \brief
		 *
		 */
		virtual lwuit_region_t GetDestination();

};

}

#endif 
