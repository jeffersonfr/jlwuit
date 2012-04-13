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

#include "dialog.h"
#include "defines.h"
#include "font.h"

#include <string>

namespace jlwuit {

class Scene;

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class Toast : public Dialog {

	private:
		/** \brief */
		std::vector<std::string> _lines;
		/** \brief */
		Font *_font;
		/** \brief */
		std::string _message;
		/** \brief */
		lwuit_gravity_t _gravity;

	private:
		
		/**
		 * \brief
		 *
		 */
		void InitRowString(std::vector<std::string> *lines, std::string text, int width);

		/**
		 * \brief
		 *
		 */
		static void ReleaseScene(Scene *scene);

	protected:
		/**
		 * \brief
		 *
		 */
		Toast(Scene *scene);

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
		static Toast * Create(Scene *scene);

		/**
		 * \brief
		 *
		 */
		virtual Toast * SetMessage(std::string msg);

		/**
		 * \brief
		 *
		 */
		virtual Toast * SetGravity(lwuit_gravity_t gravity);

		/**
		 * \brief
		 *
		 */
		virtual Toast * SetGravity(std::string gravity);

		/**
		 * \brief
		 *
		 */
		virtual void Show();

		/**
		 * \brief
		 *
		 */
		virtual void Paint(Graphics *g);

};

}

#endif
