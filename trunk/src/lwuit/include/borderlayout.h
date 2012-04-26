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
#ifndef LWUIT_BORDERLAYOUT_H
#define LWUIT_BORDERLAYOUT_H

#include "component.h"
#include "layout.h"

#include <iostream>
#include <cstdlib>
#include <map>

namespace jlwuit {

/**
 * \brief
 *
 */
enum lwuit_borderlayout_align_t {
	BLA_UNKNOWN,
	BLA_NORTH,
	BLA_SOUTH,
	BLA_EAST,
	BLA_WEST,
	BLA_CENTER,
	BLA_BEFORE_FIRST_LINE,
	BLA_AFTER_LAST_LINE,
	BLA_BEFORE_LINE_BEGINS,
	BLA_AFTER_LINE_ENDS,
	BLA_PAGE_START = BLA_BEFORE_FIRST_LINE,
	BLA_PAGE_END = BLA_AFTER_LAST_LINE,
	BLA_LINE_START = BLA_BEFORE_LINE_BEGINS,
	BLA_LINE_END = BLA_AFTER_LINE_ENDS
};

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class BorderLayout : public Layout {

	private:
		Component *north,
			*west,
			*east,
			*south,
			*center,
			*firstLine,
			*lastLine,
			*firstItem,
			*lastItem;
		int _hgap,
			_vgap;

	public:
		/**
		 * \brief
		 *
		 */
		BorderLayout(int hgap = 10, int vgap = 10);
		
		/**
		 * \brief
		 *
		 */
		virtual ~BorderLayout();

		/**
		 * \brief
		 *
		 */
		virtual int GetHGap();
		
		/**
		 * \brief
		 *
		 */
		virtual int GetVGap();
		
		/**
		 * \brief
		 *
		 */
		virtual void SetHGap(int hgap);
		
		/**
		 * \brief
		 *
		 */
		virtual void SetVgap(int vgap);

		/**
		 * \brief
		 *
		 */
		virtual void AddLayoutComponent(Component *c, lwuit_borderlayout_align_t align);
		
		/**
		 * \brief
		 *
		 */
		virtual void RemoveLayoutComponent(Component *c);
		
		/**
		 * \brief
		 *
		 */
		virtual void RemoveLayoutComponents();

		/**
		 * \brief
		 *
		 */
		virtual lwuit_borderlayout_align_t GetConstraints(Component *c);

		/**
		 * \brief
		 *
		 */
		virtual Component * GetLayoutComponent(lwuit_borderlayout_align_t align);
		
		/**
		 * \brief
		 *
		 */
		virtual Component * GetLayoutComponent(Component *target, lwuit_borderlayout_align_t align);
		
		/**
		 * \brief
		 *
		 */
		virtual Component * GetChild(lwuit_borderlayout_align_t key, bool ltr);

		/**
		 * \brief
		 *
		 */
    virtual struct lwuit_size_t GetPreferredLayoutSize(Component *parent);

		/**
		 * \brief
		 *
		 */
		virtual void DoLayout(Component *target);

};

}

#endif

