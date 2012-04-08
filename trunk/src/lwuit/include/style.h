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
#ifndef LWUIT_STYLE_H
#define LWUIT_STYLE_H

#include "color.h"
#include "stylelistener.h"
#include "image.h"
#include "parammapper.h"

#include <vector>

namespace jlwuit {

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class Style : public jlwuit::ParamMapper {

	private:
		std::vector<StyleListener *> _style_listeners;
		Image *_bg_image;
		struct lwuit_margin_t _padding,
			_margin;
		bool _is_modified,
			_is_scale_image;

	public:
		/**
		 * \brief Constructor
		 *
		 */
		Style();

		/**
		 * \brief Destructor
		 *
		 */
		virtual ~Style();

		/**
		 * \brief Returns true if the style was modified manually after it was created by the look and feel. 
		 * If the style was modified manually (by one of the set methods) then it should be merged rather than 
		 * overwritten.
		 *
		 */
		virtual bool IsModified();

		/**
		 * \brief
		 *
		 */
		virtual void SetModified(bool modified);

		/**
		 * \brief
		 *
		 */
		virtual const Color GetColor(std::string color_id);

		/**
		 * \brief Returns the background image for the component.
		 *
		 */
		virtual Image * GetBackgroundImage();

		/**
		 * \brief Sets the background image for the component.
		 *
		 */
		virtual void SetBackgroundImage(Image *image);

		/**
		 * \brief Indicates whether the image in the background is scaled.
		 *
		 */
		virtual bool IsScaleImage();

		/**
		 * \brief Set to true if the image in the background is scaled, false if it is tiled.
		 *
		 */
		virtual void SetScaleImage(bool scaleImage);

		/**
		 * \brief Sets the Style Padding.
		 *
		 */
		virtual void SetPadding(int left, int right, int top, int bottom);

		/**
		 * \brief Sets the Style Margin.
		 *
		 */
		virtual void SetMargin(int left, int right, int top, int bottom);

		/**
		 * \brief Returns the Padding.
		 *
		 */
		virtual struct lwuit_margin_t GetPadding();

		/**
		 * \brief
		 *
		 */
		virtual struct lwuit_margin_t GetMargin();

		/**
		 * \brief Adds a Style Listener to the Style Object.
		 *
		 */
		virtual void RegisterStyleListener(StyleListener *listener);

		/**
		 * \brief Removes a Style Listener from the Style Object.
		 *
		 */
		virtual void RemoveStyleListener(StyleListener *listener);

};

}

#endif
