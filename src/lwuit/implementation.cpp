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
#include "implementation.h"

#ifdef LWUIT_LINUX_IMPLEMENTATION
#include "linuximplementation.h"
#endif

#include <stdlib.h>

namespace jlwuit {

Implementation *Implementation::_instance = NULL;

Implementation::Implementation()
{
}

Implementation::~Implementation()
{
}

Implementation * Implementation::GetInstance()
{
	if (_instance == NULL) {
#ifdef LWUIT_LINUX_IMPLEMENTATION
		_instance = new LinuxImplementation();
#endif
	}

	return _instance;
}

void Implementation::Initialize()
{
}

void Implementation::Deinitialize()
{
}

RootContainer * Implementation::GetContainer(Layer *layer)
{
	return NULL;
}

EventManager * Implementation::GetEventManager()
{
	return NULL;
}

Font * Implementation::CreateFont(std::string name, lwuit_font_attributes_t attributes, int height)
{
	return NULL;
}

bool Implementation::GetImageSize(std::string img, int *width, int *height)
{
	return NULL;
}

Image * Implementation::CreateImage(int width, int height, lwuit_pixelformat_t pixelformat)
{
	return NULL;
}

Image * Implementation::CreateImage(uint32_t *data, int width, int height)
{
	return NULL;
}

Image * Implementation::CreateImage(char *data, int size)
{
	return NULL;
}

Image * Implementation::CreateImage(std::string file)
{
	return NULL;
}

Image * Implementation::CreateImage(Image *image)
{
	return NULL;
}

void Implementation::RegisterScene(Scene *scene)
{
}

void Implementation::UnregisterScene(Scene *scene)
{
}

void Implementation::Lock()
{
}

void Implementation::Unlock()
{
}

}
