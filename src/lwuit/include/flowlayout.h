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
#ifndef LWUIT_FLOWLAYOUT_H
#define LWUIT_FLOWLAYOUT_H

#include "layout.h"

#include <iostream>
#include <cstdlib>
#include <map>

namespace jlwuit {

class Component;

/**
 * \brief
 *
 */
enum lwuit_flowlayout_align_t {
	LFA_LEFT,
	LFA_CENTER,
	LFA_RIGHT,
	LFA_LEADING,
	LFA_TRAILING
};

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class FlowLayout : public Layout {

	private:
		lwuit_flowlayout_align_t _align,
			_newalign;
		int _hgap,
			_vgap;
		bool _align_on_baseline;

	public:
		/**
		 * \brief
		 *
		 */
		FlowLayout(lwuit_flowlayout_align_t align = LFA_CENTER, int hgap = 10, int vgap = 10);
		
		/**
		 * \brief
		 *
		 */
		virtual ~FlowLayout();

		/**
		 * \brief
		 *
		 */
		virtual lwuit_flowlayout_align_t GetAlign();

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
		virtual bool GetAlignOnBaseline();
		
		/**
		 * \brief
		 *
		 */
		virtual void SetAlign(lwuit_flowlayout_align_t align);
		
		/**
		 * \brief
		 *
		 */
		virtual void SetHGap(int hgap);
		
		/**
		 * \brief
		 *
		 */
		virtual void SetVGap(int vgap);
		
		/**
		 * \brief
		 *
		 */
		virtual void SetAlignOnBaseline(bool align_on_baseline);

		/**
		 * \brief
		 *
		 */
		virtual int MoveComponents(Component *target, int x, int y, int width, int height, 
				int rowStart, int rowEnd, bool ltr, bool useBaseline, int *ascent, int *descent);

		/**
		 * \brief
		 *
		 */
    virtual struct lwuit_size_t GetPreferredLayoutSize(Component *parent);
	
		/**
		 * \brief
		 *
		 */
		virtual void DoLayout(Component *parent);

};

}

#endif

