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
#include "deviceimpl.h"
#include "screenimpl.h"

namespace jlwuit {

DeviceImpl::DeviceImpl()
{
	_screens.push_back(new ScreenImpl());
}

DeviceImpl::~DeviceImpl()
{
	while (_screens.size() > 0) {
		Screen *screen = (*_screens.begin());

		_screens.erase(_screens.begin());

		delete screen;
	}
}

void DeviceImpl::Initialize()
{
	for (std::vector<Screen *>::iterator i=_screens.begin(); i!=_screens.end(); i++) {
		dynamic_cast<ScreenImpl *>(*i)->Initialize();
	}
}

}
