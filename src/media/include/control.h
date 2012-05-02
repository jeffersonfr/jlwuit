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
#ifndef LWUIT_CONTROL_H
#define LWUIT_CONTROL_H

#include "control.h"

namespace jlwuit {

/**
 * \brief
 *
 */
enum lwuit_media_control_t {
	LMC_VOLUME,
	LMC_AUDIO_CONFIGURATION,
	LMC_VIDEO_CONFIGURATION,
	LMC_VIDEO_TRANSFORMATION
};

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class Control {
	
	private:
		lwuit_media_control_t _type;

	protected:
		/**
		 * \brief
		 *
		 */
		Control(lwuit_media_control_t type);

	public:

		/**
		 * \brief
		 *
		 */
		virtual ~Control();

		/**
		 * \brief
		 *
		 */
		lwuit_media_control_t GetType();

};

}

#endif