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
#include "borderlayout.h"
#include "component.h"

namespace jlwuit {

BorderLayout::BorderLayout(int hgap, int vgap):
	Layout()
{
	_hgap = hgap;
	_vgap = vgap;
	
	north = NULL;
	west = NULL;
	east = NULL;
	south = NULL;
	center = NULL;
	firstLine = NULL;
	lastLine = NULL;
	firstItem = NULL;
	lastItem = NULL;
}

BorderLayout::~BorderLayout()
{
}

int BorderLayout::GetHGap() 
{
	return _hgap;
}

void BorderLayout::SetHGap(int hgap) 
{
	_hgap = hgap;
}

int BorderLayout::GetVGap() 
{
	return _vgap;
}

void BorderLayout::SetVgap(int vgap) 
{
	_vgap = vgap;
}

struct lwuit_size_t BorderLayout::GetPreferredLayoutSize(Component *parent)
{
	struct lwuit_size_t t = {0, 0};

	return t;
}

void BorderLayout::DoLayout(Component *target)
{
	// WARN:: sync with jframe
	struct lwuit_margin_t insets = target->GetInsets();
	int top = insets.top,
			bottom = target->GetHeight() - insets.bottom,
			left = insets.left,
			right = target->GetWidth() - insets.right;
	struct lwuit_size_t psize;
	bool ltr = (target->GetComponentOrientation() == LCO_LEFT_TO_RIGHT);
	Component *c = NULL;

	if ((c = GetChild(BLA_NORTH, ltr)) != NULL) {
		c->SetSize(right - left, c->GetHeight());

		psize = c->GetPreferredSize();

		c->SetBounds(left, top, right - left, psize.height);
		top += psize.height + _vgap;
	}

	if ((c = GetChild(BLA_SOUTH, ltr)) != NULL) {
		c->SetSize(right - left, c->GetHeight());

		psize = c->GetPreferredSize();

		c->SetBounds(left, bottom - psize.height, right - left, psize.height);
		bottom -= psize.height + _vgap;
	}

	if ((c = GetChild(BLA_EAST, ltr)) != NULL) {
		c->SetSize(c->GetWidth(), bottom - top);

		psize = c->GetPreferredSize();

		c->SetBounds(right - psize.width, top, psize.width, bottom - top);
		right -= psize.width + _hgap;
	}

	if ((c = GetChild(BLA_WEST, ltr)) != NULL) {
		c->SetSize(c->GetWidth(), bottom - top);

		psize = c->GetPreferredSize();

		c->SetBounds(left, top, psize.width, bottom - top);
		left += psize.width + _hgap;
	}

	if ((c = GetChild(BLA_CENTER, ltr)) != NULL) {
		c->SetBounds(left, top, right - left, bottom - top);
	}
}

void BorderLayout::AddLayoutComponent(Component *c, lwuit_borderlayout_align_t align) 
{
	// WARN:: sync with jframe
	if (align == BLA_CENTER) {
		center = c;
	} else if (align == BLA_NORTH) {
		north = c;
	} else if (align == BLA_SOUTH) {
		south = c;
	} else if (align == BLA_EAST) {
		east = c;
	} else if (align == BLA_WEST) {
		west = c;
	} else if (align == BLA_BEFORE_FIRST_LINE) {
		firstLine = c;
	} else if (align == BLA_AFTER_LAST_LINE) {
		lastLine = c;
	} else if (align == BLA_BEFORE_LINE_BEGINS) {
		firstItem = c;
	} else if (align == BLA_AFTER_LINE_ENDS) {
		lastItem = c;
	}
}

void BorderLayout::RemoveLayoutComponent(Component *c) 
{
	// WARN:: sync with jframe
	if (c == center) {
		center = NULL;
	} else if (c == north) {
		north = NULL;
	} else if (c == south) {
		south = NULL;
	} else if (c == east) {
		east = NULL;
	} else if (c == west) {
		west = NULL;
	}

	if (c == firstLine) {
		firstLine = NULL;
	} else if (c == lastLine) {
		lastLine = NULL;
	} else if (c == firstItem) {
		firstItem = NULL;
	} else if (c == lastItem) {
		lastItem = NULL;
	}
}

void BorderLayout::RemoveLayoutComponents() 
{
	// WARN:: sync with jframe
	center = NULL;
	north = NULL;
	south = NULL;
	east = NULL;
	west = NULL;
	firstLine = NULL;
	lastLine = NULL;
	firstItem = NULL;
	lastItem = NULL;
}

Component * BorderLayout::GetLayoutComponent(lwuit_borderlayout_align_t align) 
{
	if (align == BLA_CENTER) {
		return center;
	} else if (align == BLA_NORTH) {
		return north;
	} else if (align == BLA_SOUTH) {
		return south;
	} else if (align == BLA_WEST) {
		return west;
	} else if (align == BLA_EAST) {
		return east;
	} else if (align == BLA_PAGE_START) {
		return firstLine;
	} else if (align == BLA_PAGE_END) {
		return lastLine;
	} else if (align == BLA_LINE_START) {
		return firstItem;
	} else if (align == BLA_LINE_END) {
		return lastItem;
	}

	return NULL;
}

Component * BorderLayout::GetLayoutComponent(Component *target, lwuit_borderlayout_align_t align) 
{
	Component *result = NULL;
	bool ltr = (target->GetComponentOrientation() == LCO_LEFT_TO_RIGHT);

	if (align == BLA_NORTH) {
		result = (firstLine != NULL) ? firstLine : north;
	} else if (align == BLA_SOUTH) {
		result = (lastLine != NULL) ? lastLine : south;
	} else if (align == BLA_WEST) {
		result = ltr ? firstItem : lastItem;
		
		if (result == NULL) {
			result = west;
		}
	} else if (align == BLA_EAST) {
		result = ltr ? lastItem : firstItem;
		
		if (result == NULL) {
			result = east;
		}
	} else if (align == BLA_CENTER) {
		result = center;
	}

	return result;
}

lwuit_borderlayout_align_t BorderLayout::GetConstraints(Component *c) 
{
	if (c == NULL){
		return BLA_UNKNOWN;
	}

	if (c == center) {
		return BLA_CENTER;
	} else if (c == north) {
		return BLA_NORTH;
	} else if (c == south) {
		return BLA_SOUTH;
	} else if (c == west) {
		return BLA_WEST;
	} else if (c == east) {
		return BLA_EAST;
	} else if (c == firstLine) {
		return BLA_PAGE_START;
	} else if (c == lastLine) {
		return BLA_PAGE_END;
	} else if (c == firstItem) {
		return BLA_LINE_START;
	} else if (c == lastItem) {
		return BLA_LINE_END;
	}

	return BLA_UNKNOWN;
}

Component * BorderLayout::GetChild(lwuit_borderlayout_align_t key, bool ltr) 
{
	Component *result = NULL;

	if (key == BLA_NORTH) {
		result = (firstLine != NULL) ? firstLine : north;
	} else if (key == BLA_SOUTH) {
		result = (lastLine != NULL) ? lastLine : south;
	} else if (key == BLA_WEST) {
		result = ltr ? firstItem : lastItem;
		if (result == NULL) {
			result = west;
		}
	} else if (key == BLA_EAST) {
		result = ltr ? lastItem : firstItem;
		if (result == NULL) {
			result = east;
		}
	} else if (key == BLA_CENTER) {
		result = center;
	}

	if (result != NULL && !result->IsVisible()) {
		result = NULL;
	}

	return result;
}

}

