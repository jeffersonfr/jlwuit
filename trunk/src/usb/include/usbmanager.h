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
#ifndef LWUIT_USBMANAGER_H
#define LWUIT_USBMANAGER_H

#include "usbstatuslistener.h"

#include "jthread.h"
#include "jmutex.h"

namespace jlwuit {

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class USBManager : public jthread::Thread {

	private:
		/** \brief */
		static USBManager *_instance;

	private:
		/** \brief */
		std::vector<USBStatusListener *> _status_listeners;
		/** \brief */
		jthread::Mutex _mutex;
		/** \brief */
		bool _mounted;
		/** \brief */
		bool _running;

	protected:
		/**
		 * \brief
		 *
		 */
		USBManager();

	public:
		/**
		 * \brief
		 *
		 */
		virtual ~USBManager();
		
		/**
		 * \brief
		 *
		 */
		static USBManager * GetInstance();
		
		/**
		 * \brief
		 *
		 */
		void RegisterUSBStatusListener(USBStatusListener *listener);
		
		/**
		 * \brief
		 *
		 */
		void RemoveUSBStatusListener(USBStatusListener *listener);
		
		/**
		 * \brief
		 *
		 */
		void DispatchUSBStatusEvent(USBStatusEvent *event);
		
		/**
		 * \brief
		 *
		 */
		virtual void Stop();
		
		/**
		 * \brief
		 *
		 */
		virtual void Run();
};

}

#endif

