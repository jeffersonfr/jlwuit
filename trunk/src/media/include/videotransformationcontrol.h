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
#ifndef LWUIT_VIDEOTRANSFORMATIONCONTROL_H
#define LWUIT_VIDEOTRANSFORMATIONCONTROL_H

#include "control.h"

namespace jlwuit {

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class VideoTransformationControl : public Control {

	public:
		/**
		 * \brief
		 *
		 */
		VideoTransformationControl();

		/**
		 * \brief
		 *
		 */
		virtual ~VideoTransformationControl();

		/**
		 * \brief
		 *
		 */
		virtual void SetLocation(int x, int y);

		/**
		 * \brief
		 *
		 */
		virtual void SetSize(int width, int height);

		/**
		 * \brief
		 *
		 */
		virtual void SetBounds(int x, int y, int width, int height);

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

};

}

#endif 
