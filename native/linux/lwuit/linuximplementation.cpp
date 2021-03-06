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
#include "linuximplementation.h"
#include "deviceimpl.h"
#include "imageimpl.h"
#include "fontimpl.h"
#include "backgroundlayerimpl.h"
#include "videolayerimpl.h"
#include "graphiclayerimpl.h"
#include "scene.h"
#include "exception.h"

#include "jgui/jbufferedimage.h"

#include <stdlib.h>

namespace jlwuit {

LinuxImplementation::LinuxImplementation()
{
	_is_initialized = false;
}

LinuxImplementation::~LinuxImplementation()
{
}

void LinuxImplementation::Initialize()
{
	if (_is_initialized == true) {
		return;
	}

	DeviceImpl *device = new DeviceImpl();

	Device::AddDevice(device);

	device->Initialize();

	_is_initialized = true;
}

void LinuxImplementation::Deinitialize()
{
	if (_is_initialized == false) {
		return;
	}

	std::vector<Device *> devices = Device::GetDevices();

	for (std::vector<Device *>::iterator i=devices.begin(); i!=devices.end(); i++) {
		Device *device = (*i);

		Device::RemoveDevice(device);

		delete device;
		device = NULL;
	}

	_is_initialized = false;
}

RootContainer * LinuxImplementation::GetContainer(Layer *layer)
{
	if (layer != NULL) {
		return dynamic_cast<LayerImpl *>(layer)->GetContainer();
	}

	return NULL;
}

EventManager * LinuxImplementation::GetEventManager()
{
	GraphicLayerImpl *impl = dynamic_cast<GraphicLayerImpl *>(Device::GetDefaultScreen()->GetLayerByID("graphics"));

	return impl->GetEventManager();
}

Font * LinuxImplementation::CreateFont(std::string name, lwuit_font_attributes_t attributes, int height)
{
	return new FontImpl(name, attributes, height);
}

bool LinuxImplementation::GetImageSize(std::string img, int *width, int *height)
{
  jgui::Image *itmp = new jgui::BufferedImage(img);
	jgui::jsize_t isize = itmp->GetSize();

	(*width) = isize.width;
	(*height) = isize.height;

  delete itmp;

	if (isize.width > 0 && isize.height > 0) {
		return true;
	}

	return false;
}

Image * LinuxImplementation::CreateImage(int width, int height, lwuit_pixelformat_t pixelformat)
{
	try {
		jgui::jpixelformat_t t = jgui::JPF_UNKNOWN;

		if (pixelformat == LPF_ARGB1555) {
			t = jgui::JPF_ARGB1555;
		} else if (pixelformat == LPF_RGB16) {
			t = jgui::JPF_RGB16;
		} else if (pixelformat == LPF_RGB24) {
			t = jgui::JPF_RGB24;
		} else if (pixelformat == LPF_RGB32) {
			t = jgui::JPF_RGB32;
		} else if (pixelformat == LPF_ARGB) {
			t = jgui::JPF_ARGB;
		} else if (pixelformat == LPF_A8) {
			t = jgui::JPF_A8;
		} else if (pixelformat == LPF_YUY2) {
			t = jgui::JPF_YUY2;
		} else if (pixelformat == LPF_RGB332) {
			t = jgui::JPF_RGB332;
		} else if (pixelformat == LPF_UYVY) {
			t = jgui::JPF_UYVY;
		} else if (pixelformat == LPF_I420) {
			t = jgui::JPF_I420;
		} else if (pixelformat == LPF_YV12) {
			t = jgui::JPF_YV12;
		} else if (pixelformat == LPF_LUT8) {
			t = jgui::JPF_LUT8;
		} else if (pixelformat == LPF_ALUT44) {
			t = jgui::JPF_ALUT44;
		} else if (pixelformat == LPF_AiRGB) {
			t = jgui::JPF_AiRGB;
		} else if (pixelformat == LPF_A1) {
			t = jgui::JPF_A1;
		} else if (pixelformat == LPF_NV12) {
			t = jgui::JPF_NV12;
		} else if (pixelformat == LPF_NV16) {
			t = jgui::JPF_NV16;
		} else if (pixelformat == LPF_ARGB2554) {
			t = jgui::JPF_ARGB2554;
		} else if (pixelformat == LPF_ARGB4444) {
			t = jgui::JPF_ARGB4444;
		} else if (pixelformat == LPF_RGBA4444) {
			t = jgui::JPF_RGBA4444;
		} else if (pixelformat == LPF_NV21) {
			t = jgui::JPF_NV21;
		} else if (pixelformat == LPF_AYUV) {
			t = jgui::JPF_AYUV;
		} else if (pixelformat == LPF_A4) {
			t = jgui::JPF_A4;
		} else if (pixelformat == LPF_ARGB1666) {
			t = jgui::JPF_ARGB1666;
		} else if (pixelformat == LPF_ARGB6666) {
			t = jgui::JPF_ARGB6666;
		} else if (pixelformat == LPF_RGB18) {
			t = jgui::JPF_RGB18;
		} else if (pixelformat == LPF_LUT2) {
			t = jgui::JPF_LUT2;
		} else if (pixelformat == LPF_RGB444) {
			t = jgui::JPF_RGB444;
		} else if (pixelformat == LPF_RGB555) {
			t = jgui::JPF_RGB555;
		} else if (pixelformat == LPF_BGR555) {
			t = jgui::JPF_BGR555;
		} else if (pixelformat == LPF_RGBA5551) {
			t = jgui::JPF_RGBA5551;
		} else if (pixelformat == LPF_AVYU) {
			t = jgui::JPF_AVYU;
		} else if (pixelformat == LPF_VYU) {
			t = jgui::JPF_VYU;
		}

		return new ImageImpl(new jgui::BufferedImage(t, {width, height}));
	} catch (Exception &e) {
	}

	return NULL;
}

Image * LinuxImplementation::CreateImage(uint32_t *data, int width, int height)
{
  /* TODO::
	try {
		return new ImageImpl(new jgui::BufferedImage(data, width, height));
	} catch (Exception &e) {
	}
  */

	return NULL;
}

Image * LinuxImplementation::CreateImage(char *data, int size)
{
  /* TODO::
	try {
		return new ImageImpl(new jgui::BufferedImage(data, size));
	} catch (Exception &e) {
	}
  */

	return NULL;
}

Image * LinuxImplementation::CreateImage(std::string file)
{
	try {
		jgui::Image *image = new jgui::BufferedImage(file);

		return new ImageImpl(image);
	} catch (Exception &e) {
	}

	return NULL;
}

Image * LinuxImplementation::CreateImage(Image *image)
{
	if (image == NULL) {
		return NULL;
	}

	lwuit_size_t size = image->GetSize();
	Image *clone = NULL;

	try {
		clone = new ImageImpl(new jgui::BufferedImage(jgui::JPF_ARGB, {size.width, size.height}));

		clone->GetGraphics()->DrawImage(image, 0, 0);
	} catch (Exception &e) {
	}

	return clone;
}

void LinuxImplementation::RegisterScene(Scene *scene)
{
	RootContainer *container = GetContainer(Device::GetDefaultScreen()->GetLayerByID("graphics"));

	if (container != NULL) {
		container->Add(scene);
	}
}

void LinuxImplementation::UnregisterScene(Scene *scene)
{
	RootContainer *container = GetContainer(Device::GetDefaultScreen()->GetLayerByID("graphics"));

	if (container != NULL) {
		scene->DeinitImpl();
		container->Remove(scene);
	}
}

void LinuxImplementation::Lock()
{
	_mutex.lock();
}

void LinuxImplementation::Unlock()
{
	_mutex.unlock();
}

}
