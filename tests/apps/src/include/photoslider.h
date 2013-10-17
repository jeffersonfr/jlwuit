/***************************************************************************
 *   Copyright (C) 2010 by Jeff Ferr                                       *
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
#ifndef LWUIT_PHOTOSLIDER_H
#define LWUIT_PHOTOSLIDER_H

#include "scene.h"
#include "usbstatuslistener.h"

#include <string>
#include <vector>

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

class PhotoSlider : public jlwuit::Scene, public jthread::Thread, public jlwuit::USBStatusListener {

	private:
		jthread::Mutex _mutex;
		std::vector<std::string> _images;
		std::string _message;
		int _index;

	public:
		PhotoSlider();
		virtual ~PhotoSlider();

		virtual void Paint(jlwuit::Graphics *g);
		virtual bool OnKeyDown(jlwuit::UserEvent *event);
		virtual void EntryUSBDevice(jlwuit::USBStatusEvent *event);
		virtual void RemoveUSBDevice(jlwuit::USBStatusEvent *event);

};

#endif
