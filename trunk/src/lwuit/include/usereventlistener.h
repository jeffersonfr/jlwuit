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
#ifndef LWUIT_USEREVENTLISTENER_H
#define LWUIT_USEREVENTLISTENER_H

#include "userevent.h"

namespace jlwuit {

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class UserEventListener {

	protected:
		/**
		 * \brief
		 *
		 */
		UserEventListener();

	public:
		/**
		 * \brief
		 *
		 */
		virtual ~UserEventListener();

		/**
		 * \brief
		 *
		 */
		virtual bool IsMatch(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnKeyDown(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnKeyPress(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnKeyUp(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnKeyLongPress(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnMousePress(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnMouseRelease(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnMouseLongPress(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnMouseClick(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnMouseMove(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnMouseOver(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnMouseOut(UserEvent *event);

		/**
		 * \brief
		 *
		 */
		virtual bool OnMouseWheel(UserEvent *event);

};

}

#endif
