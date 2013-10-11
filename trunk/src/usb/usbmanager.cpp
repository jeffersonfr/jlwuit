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
#include "usbmanager.h"
#include "jautolock.h"

#include <iostream>
#include <stdexcept>
#include <algorithm>

#include <fcntl.h>
#include <unistd.h>

#define USB_MOUNT_POINT	"/mnt/usb"

#define MOUNTED_COMMAND	"./resources/scripts/usb-mounted.sh"
#define MOUNT_COMMAND		"./resources/scripts/usb-mount.sh"
#define UMOUNT_COMMAND	"./resources/scripts/usb-umount.sh"

namespace jlwuit {

USBManager *USBManager::_instance = NULL;

USBManager::USBManager(): 
	jthread::Thread()
{
	_mounted = false;
	_running = false;
	
	system(UMOUNT_COMMAND);
}

USBManager::~USBManager()
{
	system(UMOUNT_COMMAND);
}

USBManager * USBManager::GetInstance()
{
	if (_instance == NULL) {
		_instance = new USBManager();
	}

	return _instance;
}

void USBManager::RegisterUSBStatusListener(USBStatusListener *listener)
{
	if (listener == NULL) {
		return;
	}

	jthread::AutoLock lock(&_mutex);

	std::vector<USBStatusListener *>::iterator i = std::find(_status_listeners.begin(), _status_listeners.end(), listener);

	if (i == _status_listeners.end()) {
		_status_listeners.push_back(listener);
	}
}

void USBManager::RemoveUSBStatusListener(USBStatusListener *listener)
{
	if (listener == NULL) {
		return;
	}

	jthread::AutoLock lock(&_mutex);

	std::vector<USBStatusListener *>::iterator i = std::find(_status_listeners.begin(), _status_listeners.end(), listener);

	if (i != _status_listeners.end()) {
		_status_listeners.erase(i);
	}
}

void USBManager::DispatchUSBStatusEvent(USBStatusEvent *event)
{
	if (event == NULL) {
		return;
	}

	jthread::AutoLock lock(&_mutex);

	for (std::vector<USBStatusListener *>::iterator i=_status_listeners.begin(); i!=_status_listeners.end(); i++) {
		USBStatusListener *listener = (*i);

		if (event->GetType() == LET_ENTRY_USB) {
			listener->EntryUSBDevice(event);
		} else if (event->GetType() == LET_REMOVE_USB) {
			listener->RemoveUSBDevice(event);
		}
	}

	delete event;
}

void USBManager::Stop()
{
	_mounted = false;
	_running = false;
	
	WaitThread();

	DispatchUSBStatusEvent(new USBStatusEvent(LET_REMOVE_USB, ""));
}

void USBManager::Run()
{
	_running = true;

	do {
		if (_mounted == true) {
			_mounted = false;

			system(UMOUNT_COMMAND);

			DispatchUSBStatusEvent(new USBStatusEvent(LET_REMOVE_USB, ""));
		}

		_mounted = false;

		do {
			for (int i=0; i<10; i++) {
				if (_running == false) {
					goto _run_exit;
				}

				usleep(200000);
			}
		} while (system(MOUNT_COMMAND) != 0);
			
		DispatchUSBStatusEvent(new USBStatusEvent(LET_ENTRY_USB, USB_MOUNT_POINT));

		_mounted = true;
		
		do {
			for (int i=0; i<10; i++) {
				if (_running == false) {
					goto _run_exit;
				}

				usleep(200000);
			}
		} while (system(MOUNTED_COMMAND) != 0);
	} while(_running == true);
	
_run_exit:
	system(UMOUNT_COMMAND);
}

}
