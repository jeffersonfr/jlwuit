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
#ifndef LWUIT_CAPABILITIES_H
#define LWUIT_CAPABILITIES_H

#include "defines.h"

#include <vector>

namespace jlwuit {

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class Capabilities {

	private:

	public:
		/**
		 * \brief Constructor.
		 *
		 */
		Capabilities();

		/**
		 * \brief Destructor.
		 *
		 */
		virtual ~Capabilities();

		/**
		 * \brief Provide all screen sizes supported by the layer associated with this instance of Capabilities.
		 *
		 */
		virtual std::vector<struct lwuit_size_t> GetSupportedScreenResolutions();

		/**
		 * \brief Provide all plane aspect ratios supported by the plane associated with this instance of 
		 * Capabilities.
		 *
		 */
		virtual std::vector<struct lwuit_size_t> GetSupportedPlaneAspectRatios();

		/**
		 * \brief Provide all pixel aspect ratios supported by the plane associated with this instance of 
		 * Capabilities.
		 *
		 */
		virtual std::vector<struct lwuit_size_t> GetSupportedPixelAspectRatios();

		/**
		 * \brief Indicate whether alpha blending is supported by the plane associated with this instance of 
		 * Capabilities. The return value is also true if the setup does not support real (hardware supported) 
		 * alpha blending, but uses a so-called switching plane. This switching plane, offered by some 
		 * implementations in order to spare hardware-supported alpha blending for video planes, is an additional 
		 * plane with one bit per pixel, just indicating for every pixel whether this plane or the underlying 
		 * plane should be visible.
		 *
		 * To indicate whether real (hardware supported) alpha blending is available, the IsRealAlphaBlendingSupported() 
		 * method has to be called.
		 *
		 */
		virtual bool IsAlphaBlendingSupported();

		/**
		 * \brief Indicate whether real alpha blending is supported by the plane associated with this instance of 
		 * Capabilities. The return value is only true if the plane supports real (hardware supported) alpha blending. 
		 * If alpha blending is just simulated by use of a so-called switching plane, the return value is false.
		 *
		 */
		virtual bool IsRealAlphaBlendingSupported();

		/**
		 * \brief Indicate whether the rendering of images is supported for the plane associated with this instance 
		 * of Capabilities. The return value could be true for setups suitable for graphics or video still planes, but 
		 * false for a setup suitable for a subtitle plane.
		 *
		 */
		virtual bool IsImageRenderingSupported();

		/**
		 * \brief Indicate whether the rendering of JPEG images is supported for the plane associated with this instance 
		 * of Capabilities. The return value can only be true if the return value of IsImageRenderingSupported(), called 
		 * for the same object, is also true.
		 *
		 */
		virtual bool IsJPGRenderingSupported();

		/**
		 * \brief Indicate whether the rendering of PNG images is supported for the plane associated with this instance of 
		 * Capabilities. The return value can only be true if the return value of isImageRenderingSupported(), called for 
		 * the same object, is also true.
		 *
		 */
		virtual bool IsPNGRenderingSupported();

		/**
		 * \brief Indicate whether the rendering of GIF images is supported for the plane associated with this instance of 
		 * Capabilities. The return value can only be true if the return value of IsImageRenderingSupported(), called for 
		 * the same object, is also true.
		 *
		 */
		virtual bool IsGIFRenderingSupported();

		/**
		 * \brief Indicate whether the rendering of videos is supported for the plane associated with this instance of 
		 * Capabilities. The return value could be true for setups suitable for video planes, but false for a setup suitable 
		 * for a background plane.
		 *
		 */
		virtual bool IsVideoRenderingSupported();

		/**
		 * \brief Indicates how many bits are used for coding of the pixels if images are rendered on the plane associated 
		 * with this instance of Capabilities. The call to this method makes only sense if image rendering is supported by 
		 * this kind of plane, i.e. if the return value of IsImageRenderingSupported() is true for this Capabilities object, 
		 * otherwise an exception is thrown.
		 *
		 */
		virtual int GetBitsPerPixel();

		/**
		 * \brief Indicate whether widget rendering is supported by the plane associated * with this instance of Capabilities. 
		 *
		 */
		virtual bool IsWidgetRenderingSupported();

		/**
		 * \brief Indicate whether graphics rendering is supported by the plane associated with this instance of Capabilities.
		 *
		 */
		virtual bool IsGraphicsRenderingSupported();

};

}

#endif
