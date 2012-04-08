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
#ifndef LWUIT_TOAST_H
#define LWUIT_TOAST_H

#include "defines.h"

#include <string>

namespace jlwuit {

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class Toast {

	private:
		/** \brief */
		std::string _id;
		/** \brief */
		std::string _message;
		/** \brief */
		std::string _icon;
		/** \brief */
		lwuit_horizontal_align_t _halign;
		/** \brief */
		lwuit_vertical_align_t _valign;
		/** \brief */
		int _timeout;

	protected:
		/**
		 * \brief
		 *
		 */
		Toast(std::string id);

	public:
		/**
		 * \brief
		 *
		 */
		virtual ~Toast();
		
		/**
		 * \brief
		 *
		 */
		static Toast * Create(std::string msg);

		/**
		 * \brief
		 *
		 */
		virtual Toast * SetMessage(std::string msg);

		/**
		 * \brief
		 *
		 */
		virtual Toast * SetIcon(std::string icon);

		/**
		 * \brief
		 *
		 */
		virtual Toast * SetHorizontalAlign(lwuit_horizontal_align_t align);

		/**
		 * \brief
		 *
		 */
		virtual Toast * SetVerticalAlign(lwuit_vertical_align_t align);

		/**
		 * \brief
		 *
		 */
		virtual Toast * SetTimeout(int ms);

		/**
		 * \brief
		 *
		 */
		virtual void Show();

		/**
		 * \brief
		 *
		 */
		virtual void Hide();

};

}

#endif
