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
#include "device.h"

#include <algorithm>
#include <mutex>

namespace jlwuit {

std::vector<Device *> Device::_devices;

std::mutex _device_mutex;

Device::Device()
{
}

Device::~Device()
{
}

std::vector<Device *> Device::GetDevices()
{
  std::unique_lock<std::mutex> lock(_device_mutex);

	return _devices;
}

void Device::AddDevice(Device *device)
{
  std::unique_lock<std::mutex> lock(_device_mutex);

	if (device == NULL) {
		return;
	}

	if (std::find(_devices.begin(), _devices.end(), device) == _devices.end()) {
		_devices.push_back(device);
	}
}

void Device::RemoveDevice(Device *device)
{
  std::unique_lock<std::mutex> lock(_device_mutex);

	if (device == NULL) {
		return;
	}

	std::vector<Device *>::iterator i = std::find(_devices.begin(), _devices.end(), device);

	if (i != _devices.end()) {
		_devices.erase(i);
	}
}

Screen * Device::GetDefaultScreen()
{
  std::unique_lock<std::mutex> lock(_device_mutex);

	Device *device = (*_devices.begin());

	return (*device->GetScreens().begin());
}

std::vector<Screen *> Device::GetScreens()
{
	return _screens;
}

}
