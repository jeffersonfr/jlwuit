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
#ifndef LWUIT_DEVICE_H
#define LWUIT_DEVICE_H

#include "screen.h"

namespace jlwuit {

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class Device {

	private:
		static std::vector<Device *> _devices;
	
	protected:
		std::vector<Screen *> _screens;

	public:
		/**
		 * \brief
		 *
		 */
		Device();

		/**
		 * \brief
		 *
		 */
		virtual ~Device();

		/**
		 * \brief
		 *
		 */
		static std::vector<Device *> GetDevices();

		/**
		 * \brief
		 *
		 */
		static void AddDevice(Device *device);

		/**
		 * \brief
		 *
		 */
		static void RemoveDevice(Device *device);

		/**
		 * \brief
		 *
		 */
		static Screen * GetDefaultScreen();

		/**
		 * \brief
		 *
		 */
		virtual std::vector<Screen *> GetScreens();

};

}

#endif
