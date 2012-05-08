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
#ifndef LWUIT_LINUXIMPLEMENTATION_H
#define LWUIT_LINUXIMPLEMENTATION_H

#include "implementation.h"

#include "jmutex.h"

#include <map>

namespace jlwuit {

class EventManager;
class Image;
class Scene;
class Font;

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class LinuxImplementation : public jlwuit::Implementation {

	private:
		jthread::Mutex _mutex;
		EventManager *_eventmanager;
		bool _is_initialized;

	public:
		/**
		 * \brief
		 *
		 */
		LinuxImplementation();

		/**
		 * \brief
		 *
		 */
		virtual ~LinuxImplementation();

		/**
		 * \brief
		 *
		 */
		virtual void Initialize();

		/**
		 * \brief
		 *
		 */
		virtual void Deinitialize();

		/**
		 * \brief
		 *
		 */
		virtual RootContainer * GetContainer(Layer *layer);

		/**
		 * \brief
		 *
		 */
		virtual EventManager * GetEventManager();

		/**
		 * \brief
		 *
		 */
		virtual Font * CreateFont(std::string name, lwuit_font_attributes_t attr, int height);

		/**
		 * \brief
		 *
		 */
		virtual bool GetImageSize(std::string img, int *width, int *height);
	
		/**
		 * \brief
		 *
		 */
		virtual Image * CreateImage(int width, int height, lwuit_pixelformat_t pixelformat);

		/**
		 * \brief
		 *
		 */
		virtual Image * CreateImage(uint32_t *data, int width, int height);

		/**
		 * \brief
		 *
		 */
		virtual Image * CreateImage(uint8_t *data, int size);

		/**
		 * \brief
		 *
		 */
		virtual Image * CreateImage(std::string file);

		/**
		 * \brief
		 *
		 */
		virtual Image * CreateImage(Image *image);

		/**
		 * \brief
		 *
		 */
		virtual void RegisterScene(Scene *scene);
		
		/**
		 * \brief
		 *
		 */
		virtual void UnregisterScene(Scene *scene);
		
		/**
		 * \brief
		 *
		 */
		virtual void Lock();

		/**
		 * \brief
		 *
		 */
		virtual void Unlock();

};

}

#endif
