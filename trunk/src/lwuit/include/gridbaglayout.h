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
 *   aint64_t with this program; if not, write to the                      *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef LWUIT_GRIDBAGLAYOUT_H
#define LWUIT_GRIDBAGLAYOUT_H

#include "graphics.h"
#include "layout.h"
#include "component.h"

#include <iostream>
#include <cstdlib>
#include <map>

namespace jlwuit {

enum lwuit_gridbaglayout_constraints_t {
	// column or row (<code>gridwidth</code>, <code>gridheight</code>), or that this component be 
	// placed next to the previously added component (<code>gridx</code>, <code>gridy</code>). 
	LGC_RELATIVE = -1,
	// Specifies that this component is the 
	// last component in its column or row. 
	LGC_REMAINDER = 0,
	// Do not resize the component. 
	LGC_NONE = 0,
	// Resize the component both horizontally and vertically. 
	LGC_BOTH = 1,
	// Resize the component horizontally but not vertically. 
	LGC_HORIZONTAL = 2,
	// Resize the component vertically but not horizontally. 
	LGC_VERTICAL = 3,
	// Put the component in the center of its display area.
	LGC_CENTER = 10,
	// Put the component at the top of its display area, centered horizontally. 
	LGC_NORTH = 11,
	// Put the component at the top-right corner of its display area. 
	LGC_NORTHEAST = 12,
	// Put the component on the right side of its display area, centered vertically.
	LGC_EAST = 13,
	// Put the component at the bottom-right corner of its display area. 
	LGC_SOUTHEAST = 14,
	// Put the component at the bottom of its display area, centered horizontally. 
	LGC_SOUTH = 15,
	// Put the component at the bottom-left corner of its display area. 
	LGC_SOUTHWEST = 16,
	// Put the component on the left side of its display area, centered vertically.
	LGC_WEST = 17,
	// Put the component at the top-left corner of its display area. 
	LGC_NORTHWEST = 18,
	// Place the component centered aint64_t the edge of its display area associated with the start of a 
	// page for the current <code>ComponentOrienation</code>.  Equal to NORTH for horizontal orientations. 
	LGC_PAGE_START = 19,
	// Place the component centered aint64_t the edge of its display area  associated with the end of a 
	// page for the current <code>ComponentOrienation</code>.  Equal to SOUTH for horizontal orientations.
	LGC_PAGE_END = 20,
	// Place the component centered aint64_t the edge of its display area where lines of text would normally 
	// begin for the current <code>ComponentOrienation</code>.  Equal to WEST for horizontal, left-to-right 
	// orientations and EAST for horizontal, right-to-left orientations.
	LGC_LINE_START = 21,
	// Place the component centered aint64_t the edge of its display area where lines of text would normally 
	// end for the current <code>ComponentOrienation</code>.  Equal to EAST for horizontal, left-to-right 
	// orientations and WEST for horizontal, right-to-left orientations.
	LGC_LINE_END = 22,
	// Place the component in the corner of its display area where the first line of text on a page would 
	// normally begin for the current <code>ComponentOrienation</code>.  Equal to NORTHWEST for horizontal, 
	// left-to-right orientations and NORTHEAST for horizontal, right-to-left orientations.
	LGC_FIRST_LINE_START = 23,
	// Place the component in the corner of its display area where the first line of text on a page would 
	// normally end for the current <code>ComponentOrienation</code>.  Equal to NORTHEAST for horizontal, 
	// left-to-right orientations and NORTHWEST for horizontal, right-to-left orientations.
	LGC_FIRST_LINE_END = 24,
	// Place the component in the corner of its display area where the last line of text on a page would 
	// normally start for the current <code>ComponentOrienation</code>.  Equal to SOUTHWEST for horizontal, 
	// left-to-right orientations and SOUTHEAST for horizontal, right-to-left orientations.
	LGC_LAST_LINE_START = 25,
	// Place the component in the corner of its display area where the last line of text on a page would 
	// normally end for the current <code>ComponentOrienation</code>.  Equal to SOUTHEAST for horizontal, 
	// left-to-right orientations and SOUTHWEST for horizontal, right-to-left orientations.
	LGC_LAST_LINE_END = 26,
	// Possible value for the <code>anchor</code> field.  Specifies that the component should be horizontally 
	// centered and vertically aligned aint64_t the baseline of the prevailing row.  If the component does not 
	// have a baseline it will be vertically centered.
	LGC_BASELINE = 0x100,
	// Possible value for the <code>anchor</code> field.  Specifies that the component should be horizontally 
	// placed aint64_t the leading edge.  For components with a left-to-right orientation, the leading edge is 
	// the left edge.  Vertically the component is aligned aint64_t the baseline of the prevailing row. If the 
	// component does not have a baseline it will be vertically centered.
	LGC_BASELINE_LEADING = 0x200,
	// Possible value for the <code>anchor</code> field.  Specifies that the component should be horizontally 
	// placed aint64_t the trailing edge.  For components with a left-to-right orientation, the trailing edge 
	// is the right edge.  Vertically the component is aligned aint64_t the baseline of the prevailing row. If 
	// the component does not have a baseline it will be vertically centered.
	LGC_BASELINE_TRAILING = 0x300,
	// Possible value for the <code>anchor</code> field.  Specifies that the component should be horizontally 
	// centered.  Vertically the component is positioned so that its bottom edge touches the baseline of the 
	// starting row.  If the starting row does not have a baseline it will be vertically centered.
	LGC_ABOVE_BASELINE = 0x400,
	// Possible value for the <code>anchor</code> field.  Specifies that the component should be horizontally 
	// placed aint64_t the leading edge.  For components with a left-to-right orientation, the leading edge is 
	// the left edge.  Vertically the component is positioned so that its bottom edge touches the baseline of 
	// the starting row.  If the starting row does not have a baseline it will be vertically centered.
	LGC_ABOVE_BASELINE_LEADING = 0x500,
	// Possible value for the <code>anchor</code> field.  Specifies that the component should be horizontally 
	// placed aint64_t the trailing edge.  For components with a left-to-right orientation, the trailing edge 
	// is the right edge.  Vertically the component is positioned so that its bottom edge touches the baseline 
	// of the starting row.  If the starting row does not have a baseline it will be vertically centered.
	LGC_ABOVE_BASELINE_TRAILING = 0x600,
	// Possible value for the <code>anchor</code> field.  Specifies that the component should be horizontally 
	// centered.  Vertically the component is positioned so that its top edge touches the baseline of the starting 
	// row. If the starting row does not have a baseline it will be vertically centered.
	LGC_BELOW_BASELINE = 0x700,
	// Possible value for the <code>anchor</code> field.  Specifies that the component should be horizontally 
	// placed aint64_t the leading edge.  For components with a left-to-right orientation, the leading edge is 
	// the left edge.  Vertically the component is positioned so that its top edge touches the baseline of the 
	// starting row.  If the starting row does not have a baseline it will be vertically centered.
	LGC_BELOW_BASELINE_LEADING = 0x800,
	// Possible value for the <code>anchor</code> field.  Specifies that the component should be horizontally 
	// placed aint64_t the trailing edge.  For components with a left-to-right orientation, the trailing edge 
	// is the right edge.  Vertically the component is positioned so that its top edge touches the baseline of 
	// the starting row.  If the starting row does not have a baseline it will be vertically centered.
	LGC_BELOW_BASELINE_TRAILING = 0x900
};

enum lwuit_gridbaglayout_style_t {
	LGS_EMPIRICMULTIPLIER,
  // This field is no int64_ter used to reserve arrays and keeped for backward compatibility. Previously, this 
	// was the maximum number of grid positions (both horizontal and vertical) that could be laid out by the grid 
	// bag layout. Current implementation doesn't impose any limits on the size of a grid. 
	LGS_MAXGRIDSIZE,
  // The smallest grid that can be laid out by the grid bag layout.
	LGS_MINSIZE,
  // The preferred grid size that can be laid out by the grid bag layout.
	LGS_PREFERREDSIZE
};

class Component;

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class GridBagConstraints {

	public:
    struct lwuit_margin_t _margins;
    double _weightx,
					 _weighty;
		int anchor,
				fill,
				ipadx,
				ipady,
				tempX,
				tempY,
				tempWidth,
				tempHeight,
				minWidth,
				minHeight,
				ascent,
				descent,
				centerPadding,
				centerOffset,
				gridx,
				gridy,
				gridwidth,
				gridheight;
		lwuit_component_baseline_t _baseline_resize_behavior;

	public:
		/**
		 * \brief
		 *
		 */
		GridBagConstraints() 
		{
			this->gridx = LGC_RELATIVE;
			this->gridy = LGC_RELATIVE;
			this->gridwidth = 1;
			this->gridheight = 1;

			this->_weightx = 0;
			this->_weighty = 0;
			this->anchor = LGC_CENTER;
			this->fill = LGC_NONE;

			this->ipadx = 0;
			this->ipady = 0;

			this->_margins.left = 0;
			this->_margins.right = 0;
			this->_margins.top = 0;
			this->_margins.bottom = 0;

			this->tempX = 0;
			this->tempY = 0;
			this->tempWidth = 0;
			this->tempHeight = 0;
			this->minWidth = 0;
			this->minHeight = 0;
			this->ascent = 0;
			this->descent = 0;
			this->centerPadding = 0;
			this->centerOffset = 0;
			this->_baseline_resize_behavior = LCB_UNKNOWN;
		}

		/**
		 * \brief
		 *
		 */
		GridBagConstraints(int gridx, int gridy, int gridwidth, int gridheight, 
				double weightx, double weighty, int anchor, int fill, struct lwuit_margin_t margins, int ipadx, int ipady) 
		{
			this->gridx = gridx;
			this->gridy = gridy;
			this->gridwidth = gridwidth;
			this->gridheight = gridheight;
			this->fill = fill;
			this->ipadx = ipadx;
			this->ipady = ipady;
			this->_margins = margins;
			this->anchor  = anchor;
			this->_weightx = weightx;
			this->_weighty = weighty;

			this->tempX = 0;
			this->tempY = 0;
			this->tempWidth = 0;
			this->tempHeight = 0;
			this->minWidth = 0;
			this->minHeight = 0;
			this->ascent = 0;
			this->descent = 0;
			this->centerPadding = 0;
			this->centerOffset = 0;
			this->_baseline_resize_behavior = LCB_UNKNOWN;
		}

		/**
		 * \brief
		 *
		 */
		virtual ~GridBagConstraints()
		{
		}

		/**
		 * \brief
		 *
		 */
		virtual bool IsVerticallyResizable() 
		{
			return (fill == LGC_BOTH || fill == LGC_VERTICAL);
		}
};

class GridBagLayoutInfo {

	public:
		int width, 
				height;						// number of  cells: horizontal and vertical
		int startx, 
				starty;						// starting point for layout
		int *minWidth,				// largest minWidth in each column
				*minHeight,				// largest minHeight in each row
				*maxAscent,				// Max ascent (baseline)
				*maxDescent;			// Max descent (height - baseline)
		double *weightX,			// largest weight in each column
					 *weightY;			// largest weight in each row
		bool hasBaseline;			// Whether or not baseline layout has been requested and one of the components has a valid baseline
		short *baselineType;	// These are only valid if hasBaseline is true and are indexed by row 
		// The type of baseline for a particular row.  A mix of the BaselineResizeBehavior constants (1 << ordinal())
		int minWidthSize,
				minHeightSize,
				maxAscentSize,
				maxDescentSize,
				weightXSize,
				weightYSize,
				baselineTypeSize;

	public:
		/**
		 * \brief
		 *
		 */
		GridBagLayoutInfo(int width, int height) 
		{
			this->width = width;
			this->height = height;
			this->startx = 0;
			this->starty = 0;	
			this->minWidth = NULL;
			this->minHeight = NULL;	
			this->maxAscent = NULL;	
			this->maxDescent = NULL;
			this->weightX = NULL;
			this->weightY = NULL;
			this->hasBaseline = false;
			this->baselineType = NULL;
			this->minWidthSize = 0;
			this->minHeightSize = 0;
			this->maxAscentSize = 0;
			this->maxDescentSize = 0;
			this->weightXSize = 0;
			this->weightYSize = 0;
			this->baselineTypeSize = 0;
		}

		/**
		 * \brief
		 *
		 */
		virtual ~GridBagLayoutInfo() 
		{
			if (minWidth != NULL) {
				delete minWidth;
			}

			if (minHeight != NULL) {
				delete minHeight;
			}

			if (maxAscent != NULL) {
				delete maxAscent;
			}

			if (maxDescent != NULL) {
				delete maxDescent;
			}

			if (weightX != NULL) {
				delete weightX;
			}

			if (weightY != NULL) {
				delete weightY;
			}

			if (baselineType != NULL) {
				delete baselineType;
			}
		}

		/**
		 * \brief
		 *
		 */
		virtual bool HasConstantDescent(int row) 
		{
			int ordinal = 0; // TODO:: Component.BaselineResizeBehavior.CONSTANT_DESCENT.ordinal();

			return ((baselineType[row] & (1 << ordinal)) != 0);
		}

		/**
		 * \brief
		 *
		 */
		virtual bool HasBaseline(int row) 
		{
			return (hasBaseline && baselineType[row] != 0);
		}
};

class GridBagLayout : public Layout{

	private:
		std::map<Component *, GridBagConstraints *> comptable;
		GridBagConstraints *defaultConstraints;
		GridBagLayoutInfo *layoutInfo;
		Component *componentAdjusting;
		int columnWidthsSize,
				rowHeightsSize,
				columnWeightsSize,
				rowWeightsSize;
		bool rightToLeft;

	public:
		/**
		 * \brief
		 *
		 */
		GridBagLayout();
		
		/**
		 * \brief
		 *
		 */
		virtual ~GridBagLayout();

		/**
		 * \brief
		 *
		 */
		virtual void SetConstraints(Component *comp, GridBagConstraints *constraints);
		
		/**
		 * \brief
		 *
		 */
		virtual GridBagConstraints * GetConstraints(Component *comp);
		
		/**
		 * \brief
		 *
		 */
		virtual GridBagConstraints * LookupConstraints(Component *comp);
		
		/**
		 * \brief
		 *
		 */
		virtual void RemoveConstraints(Component *comp);
		
		/**
		 * \brief
		 *
		 */
		virtual lwuit_point_t GetLayoutOrigin();
		
		/**
		 * \brief
		 *
		 */
		virtual void AddLayoutComponent(Component *comp, GridBagConstraints *constraints);
		
		/**
		 * \brief
		 *
		 */
		virtual void RemoveLayoutComponent(Component *comp);
		
		/**
		 * \brief
		 *
		 */
		virtual GridBagLayoutInfo * GetLayoutInfo(Component *parent, int sizeflag);
		
		/**
		 * \brief
		 *
		 */
		virtual int64_t * PreInitMaximumArraySizes(Component *parent);
		
		/**
		 * \brief
		 *
		 */
		virtual bool CalculateBaseline(Component *c, GridBagConstraints *constraints, struct lwuit_size_t size);
		
		/**
		 * \brief
		 *
		 */
		virtual void AdjustForGravity(GridBagConstraints *constraints, struct lwuit_region_t *r);
		
		/**
		 * \brief
		 *
		 */
		virtual void AlignOnBaseline(GridBagConstraints *cons, struct lwuit_region_t *r, int cellY, int cellHeight);
		
		/**
		 * \brief
		 *
		 */
		virtual void AlignAboveBaseline(GridBagConstraints *cons, struct lwuit_region_t *r, int cellY, int cellHeight);
		
		/**
		 * \brief
		 *
		 */
		virtual void AlignBelowBaseline(GridBagConstraints *cons, struct lwuit_region_t *r, int cellY, int cellHeight);
		
		/**
		 * \brief
		 *
		 */
		virtual void CenterVertically(GridBagConstraints *cons, struct lwuit_region_t *r, int cellHeight);
		
		/**
		 * \brief
		 *
		 */
		virtual struct lwuit_size_t GetMinSize(Component *parent, GridBagLayoutInfo *info);
		
		/**
		 * \brief
		 *
		 */
		virtual void ArrangeGrid(Component *parent);

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

