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
#include "nativeproxy.h"
#include "exception.h"

namespace jlwuit {

NativeProxy::NativeProxy(Attributes *attributes):
	jlwuit::Proxy(attributes)
{
	_native_interface = NULL;
}

NativeProxy::~NativeProxy()
{
}

void NativeProxy::Load()
{
}

void NativeProxy::Start()
{
	if (_native_interface != NULL) {
		_native_interface->Start();
	}
}

void NativeProxy::Pause()
{
	if (_native_interface != NULL) {
		_native_interface->Pause();
	}
}

void NativeProxy::Resume()
{
	if (_native_interface != NULL) {
		_native_interface->Resume();
	}
}

void NativeProxy::Stop()
{
	if (_native_interface != NULL) {
		_native_interface->Destroy();

		{
			APPLICATIONLIFECYCLE_INTERFACE * (*ptrFN)(APPLICATIONLIFECYCLE_INTERFACE *) = 0;

			// ptrFN = (APPLICATIONLIFECYCLE_INTERFACE * (*)(APPLICATIONLIFECYCLE_INTERFACE *))dlsym(_handler, "DestroyModule");

			if (ptrFN == NULL) {
				throw Exception("Invalid application");
			}

			(*ptrFN)(_native_interface);
	
			if (_native_interface != NULL) {
				// dlclose(_handler);
			}

			_native_interface = NULL;
		}
	}

	NotifyDestroy();
}

void NativeProxy::NotifyDestroy()
{
}

}
