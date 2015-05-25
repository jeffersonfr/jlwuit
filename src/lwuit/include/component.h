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
#ifndef LWUIT_COMPONENT_H
#define LWUIT_COMPONENT_H

#include "graphics.h"
#include "userevent.h"
#include "font.h"
#include "layout.h"
#include "animation.h"
#include "usereventlistener.h"

#include "jthread.h"

#include <vector>

namespace jlwuit {

class GridBagConstraints;

enum lwuit_component_alignment_t {
	LCA_TOP,
	LCA_CENTER,
	LCA_BOTTOM,
	LCA_LEFT,
	LCA_RIGHT
};

enum lwuit_component_orientation_t {
	LCO_LEFT_TO_RIGHT,
	LCO_RIGHT_TO_LEFT,
	LCO_TOP_TO_BOTTOM,
	LCO_BOTTOM_TO_TOP,
};

enum lwuit_component_border_t {
	LCB_EMPTY,
	LCB_LINE,
	LCB_BEVEL,
	LCB_ROUND,
	LCB_RAISED_GRADIENT,
	LCB_LOWERED_GRADIENT,
	LCB_RAISED_BEVEL,
	LCB_LOWERED_BEVEL,
	LCB_RAISED_ETCHED,
	LCB_LOWERED_ETCHED
};

// component baseline resize behavior
enum lwuit_component_baseline_t {
	LCB_UNKNOWN,
	LCB_ASCENT,
	LCB_DESCENT,
	LCB_CENTER
};

class Component;
class Style;
class Layout;

class Component : public UserEventListener, public Animation {

	protected:
		std::vector<Component *> _components;
		jthread::Mutex _container_mutex;
		Component *_focus;
		Style *_style;
		Layout *_layout;
		struct lwuit_margin_t _margins;
		struct lwuit_size_t _scale;
		Component *_parent;
		Component *_left, 
			*_right,
			*_up,
			*_down;
		struct lwuit_point_t _location;
		struct lwuit_size_t _size,
			_preferred_size;
		std::string _name,
			_uiid;
		bool _has_focus,
			_is_visible,
			_is_focusable,
			_enabled,
			_is_valid,
			_is_opaque,
			_is_cycle_root;
		lwuit_component_alignment_t _alignment_x,
			_alignment_y;
		lwuit_component_orientation_t _orientation;

	public:
		/**
		 * \Constructor.
		 *
		 */
		Component(lwuit_region_t bounds);

		/**
		 * \Constructor.
		 *
		 */
		Component(lwuit_point_t location, lwuit_size_t size);

		/**
		 * \Constructor.
		 *
		 */
		Component(int x = 0, int y = 0, int width = 0, int height = 0);

		/**
		 * \brief Destructor.
		 *
		 */
		virtual ~Component();

		/**
		 * \brief
		 *
		 */
		virtual void SetUIID(std::string uiid);

		/**
		 * \brief
		 *
		 */
		virtual std::string GetUIID();

		/**
		 * \brief
		 *
		 */
		virtual void Invalidate();

		/**
		 * \brief
		 *
		 */
		virtual void Revalidate();

		/**
		 * \brief
		 *
		 */
		virtual void InvalidateAll();
		
		/**
		 * \brief
		 *
		 */
		virtual void RevalidateAll();

		/**
		 * \brief
		 *
		 */
		virtual bool IsValid();

		/**
		 * \brief
		 *
		 */
		Style * GetStyle();
		
		/**
		 * \brief
		 *
		 */
		void SetStyle(Style *style);

		/**
		 * \brief
		 *
		 */
		virtual int GetBaseline(int w, int h);

		/**
		 * \brief
		 *
		 */
		virtual lwuit_component_baseline_t GetBaselineResizeBehavior();

		/**
		 * \brief
		 *
		 */
		virtual lwuit_component_alignment_t GetAlignmentX();

		/**
		 * \brief
		 *
		 */
		virtual lwuit_component_alignment_t GetAlignmentY();

		/**
		 * \brief
		 *
		 */
		virtual void SetAlignmentX(lwuit_component_alignment_t align);

		/**
		 * \brief
		 *
		 */
		virtual void SetAlignmentY(lwuit_component_alignment_t align);

		/**
		 * \brief
		 *
		 */
		virtual void SetComponentOrientation(lwuit_component_orientation_t orientation);

		/**
		 * \brief
		 *
		 */
		virtual lwuit_component_orientation_t GetComponentOrientation();

		/**
		 * \brief
		 *
		 */
		virtual bool Intersects(int x, int y);

		/**
		 * \brief
		 *
		 */
		virtual void SetOpaque(bool b);

		/**
		 * \brief
		 *
		 */
		virtual bool IsOpaque();

		/**
		 * \brief
		 *
		 */
		virtual bool Intersects(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

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

		/**
		 * \brief
		 *
		 */
		virtual void Paint(Graphics *g);

		/**
		 * \brief
		 *
		 */
		virtual Component * GetParent();

		/**
		 * \brief
		 *
		 */
		virtual Component * GetTopLevelAncestor();

		/**
		 * \brief
		 *
		 */
		virtual bool IsEnabled();

		/**
		 * \brief
		 *
		 */
		virtual void SetEnabled(bool b);

		/**
		 * \brief
		 *
		 */
		virtual void SetParent(Component *parent);

		/**
		 * \brief
		 *
		 */
		virtual void Repaint(Component *cmp = NULL);

		/**
		 * \brief
		 *
		 */
		virtual void SetBounds(int x, int y, int w, int h);

		/**
		 * \brief
		 *
		 */
		virtual void SetBounds(struct lwuit_point_t point, struct lwuit_size_t size);

		/**
		 * \brief
		 *
		 */
		virtual void SetBounds(struct lwuit_region_t region);

		/**
		 * \brief
		 *
		 */
		virtual void SetLocation(int x, int y);

		/**
		 * \brief
		 *
		 */
		virtual void SetLocation(struct lwuit_point_t point);

		/**
		 * \brief
		 *
		 */
		virtual void SetSize(int w, int h);

		/**
		 * \brief
		 *
		 */
		virtual void SetSize(struct lwuit_size_t size);

		/**
		 * \brief
		 *
		 */
		virtual int GetX();

		/**
		 * \brief
		 *
		 */
		virtual int GetY();

		/**
		 * \brief
		 *
		 */
		virtual int GetAbsoluteX();

		/**
		 * \brief
		 *
		 */
		virtual int GetAbsoluteY();

		/**
		 * \brief
		 *
		 */
		virtual int GetWidth();

		/**
		 * \brief
		 *
		 */
		virtual int GetHeight();

		/**
		 * \brief
		 *
		 */
		virtual struct lwuit_point_t GetLocation();

		/**
		 * \brief
		 *
		 */
		virtual struct lwuit_size_t GetSize();

		/**
		 * \brief
		 *
		 */
		virtual struct lwuit_region_t GetBounds();

		/**
		 * \brief
		 *
		 */
		virtual void RaiseToTop();

		/**
		 * \brief
		 *
		 */
		virtual void LowerToBottom();

		/**
		 * \brief
		 *
		 */
		virtual void PutAtop(Component *c);

		/**
		 * \brief
		 *
		 */
		virtual void PutBelow(Component *c);

		/**
		 * \brief
		 *
		 */
		virtual void SetNavigation(Component *left, Component *right, Component *up, Component *down);

		/**
		 * \brief
		 *
		 */
		virtual Component * GetLeftComponent();

		/**
		 * \brief
		 *
		 */
		virtual Component * GetRightComponent();

		/**
		 * \brief
		 *
		 */
		virtual Component * GetUpComponent();

		/**
		 * \brief
		 *
		 */
		virtual Component * GetDownComponent();

		/**
		 * \brief
		 *
		 */
		virtual void RequestFocus();

		/**
		 * \brief
		 *
		 */
		virtual void ReleaseFocus();

		/**
		 * \brief
		 *
		 */
		virtual bool HasFocus();

		/**
		 * \brief
		 *
		 */
		virtual bool IsVisible();

		/**
		 * \brief
		 *
		 */
		virtual void SetVisible(bool b);

		/**
		 * \brief
		 *
		 */
		virtual void SetLayout(Layout *layout);

		/**
		 * \brief
		 *
		 */
		virtual Layout * GetLayout();

		/**
		 * \brief
		 *
		 */
		virtual void DoLayout();

		/**
		 * \brief
		 *
		 */
		virtual struct lwuit_margin_t GetInsets();
		
		/**
		 * \brief
		 *
		 */
		virtual void SetInsets(struct lwuit_margin_t insets);
		
		/**
		 * \brief
		 *
		 */
		virtual void SetInsets(int left, int top, int right, int bottom);

		/**
		 * \brief
		 *
		 */
		virtual void Add(Component *c, int index);

		/**
		 * \brief
		 *
		 */
		virtual void Add(Component *c);

		/**
		 * \brief
		 *
		 */
		virtual void Add(Component *c, GridBagConstraints *constraints);

		/**
		 * \brief
		 *
		 */
		virtual void Add(Component *c, std::string align);

		/**
		 * \brief
		 *
		 */
		virtual void Remove(Component *c);

		/**
		 * \brief
		 *
		 */
		virtual void RemoveAll();

		/**
		 * \brief
		 *
		 */
		virtual std::vector<Component *> GetComponents();

		/**
		 * \brief
		 *
		 */
		virtual void RequestComponentFocus(Component *c);

		/**
		 * \brief
		 *
		 */
		virtual void ReleaseComponentFocus(Component *c);

		/**
		 * \brief
		 *
		 */
		virtual Component * GetFocusOwner();

		/**
		 * \brief
		 *
		 */
		virtual void RaiseComponentToTop(Component *c);

		/**
		 * \brief
		 *
		 */
		virtual void LowerComponentToBottom(Component *c);

		/**
		 * \brief
		 *
		 */
		virtual void PutComponentATop(Component *c, Component *c1);

		/**
		 * \brief
		 *
		 */
		virtual void PutComponentBelow(Component *c, Component *c1);

		/**
		 * \brief
		 *
		 */
		virtual void SetName(std::string name);
		
		/**
		 * \brief
		 *
		 */
		virtual std::string GetName();

		/**
		 * \brief
		 *
		 */
		virtual bool IsCyclicFocus();

		/**
		 * \brief
		 *
		 */
		virtual void SetCyclicFocus(bool b);

		/**
		 * \brief
		 *
		 */
		virtual lwuit_point_t GetAbsoluteLocation();
		
		/**
		 * \brief
		 *
		 */
		virtual lwuit_region_t GetVisibleBounds();
		
		/**
		 * \brief
		 *
		 */
		virtual void SetNavigationEnabled(bool b);

		/**
		 * \brief
		 *
		 */
		virtual bool IsNavigationEnabled();

		/**
		 * \brief
		 *
		 */
		virtual Component * GetNextFocusLeft();
		
		/**
		 * \brief
		 *
		 */
		virtual Component * GetNextFocusRight();
		
		/**
		 * \brief
		 *
		 */
		virtual Component * GetNextFocusUp();
		
		/**
		 * \brief
		 *
		 */
		virtual Component * GetNextFocusDown();
		
		/**
		 * \brief
		 *
		 */
		virtual void SetNextFocusLeft(Component *cmp);
		
		/**
		 * \brief
		 *
		 */
		virtual void SetNextFocusRight(Component *cmp);
		
		/**
		 * \brief
		 *
		 */
		virtual void SetNextFocusUp(Component *cmp);
		
		/**
		 * \brief
		 *
		 */
		virtual void SetNextFocusDown(Component *cmp);
		
		/**
		 * \brief
		 *
		 */
		virtual void SetNextComponentFocus(Component *left, Component *right, Component *up, Component *down);

		/**
		 * \brief
		 *
		 */
		virtual void SetMinimumSize(lwuit_size_t size);
		
		/**
		 * \brief
		 *
		 */
		virtual void SetMaximumSize(lwuit_size_t size);
		
		/**
		 * \brief
		 *
		 */
		virtual void SetPreferredSize(lwuit_size_t size);
		
		/**
		 * \brief
		 *
		 */
		virtual lwuit_size_t GetMinimumSize();
		
		/**
		 * \brief
		 *
		 */
		virtual lwuit_size_t GetMaximumSize();
		
		/**
		 * \brief
		 *
		 */
		virtual lwuit_size_t GetPreferredSize();

		/**
		 * \brief
		 *
		 */
		virtual void Move(int x, int y);
		
		/**
		 * \brief
		 *
		 */
		virtual void Move(lwuit_point_t location);
		
		/**
		 * \brief
		 *
		 */
		virtual void SetFocusable(bool b);
		
		/**
		 * \brief
		 *
		 */
		virtual bool IsFocusable();

		/**
		 * \brief
		 *
		 */
		virtual bool IsFocusCycleRoot();

		/**
		 * \brief
		 *
		 */
		virtual void SetFocusCycleRoot(bool b);

		/**
		 * \brief
		 *
		 */
		virtual Component * GetFocusCycleRootAncestor();

};

}

#endif
