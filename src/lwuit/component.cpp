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
#include "component.h"
#include "gridbaglayout.h"
#include "borderlayout.h"
#include "exception.h"
#include "lookandfeel.h"

#include "jcommon/jstringutils.h"

#include <algorithm>

#include <stdio.h>

namespace jlwuit {

Component::Component(lwuit_region_t bounds)
{
	Component(bounds.x, bounds.y, bounds.width, bounds.height);
}

Component::Component(lwuit_point_t location, lwuit_size_t size)
{
	Component(location.x, location.y, size.width, size.height);
}

Component::Component(int x, int y, int w, int h)
{
	SetUIID("Component");

	_preferred_size.width = 64;
	_preferred_size.height = 32;

	_layout = NULL;
	_focus = NULL;
	_parent = NULL;
	_left = NULL;
	_right = NULL;
	_up = NULL;
	_down = NULL;
	
	_alignment_x = LCA_CENTER;
	_alignment_y = LCA_CENTER;

	_location.x = x;
	_location.y = y;
	_size.width = w;
	_size.height = h;

	_orientation = LCO_LEFT_TO_RIGHT;
	
	_is_opaque = false;
	_is_cycle_root = false;
	_is_valid = true;
	_is_focusable = false;
	_enabled = true;
	_has_focus = false;
	_is_visible = false;

	_margins.left = 0;
	_margins.right = 0;
	_margins.top = 0;
	_margins.bottom = 0;

	_style = new Style(); 

	_style->Copy(LookAndFeel::GetInstance()->GetDefaultStyle());
}

Component::~Component()
{
	if (_parent != NULL) {
		_parent->Remove(this);
	}

	delete _style;
	_style = NULL;
}

void Component::SetUIID(std::string uiid)
{
	_uiid = uiid;
}

std::string Component::GetUIID()
{
	return _uiid;
}

void Component::Invalidate()
{
	_is_valid = false;
}

void Component::Revalidate()
{
	_is_valid = true;
}

void Component::InvalidateAll()
{
  std::unique_lock<std::mutex> lock(_container_mutex);

	for (std::vector<jlwuit::Component *>::iterator i=_components.begin(); i!=_components.end(); i++) {
		(*i)->InvalidateAll();
	}

	_is_valid = false;
}

void Component::RevalidateAll()
{
  std::unique_lock<std::mutex> lock(_container_mutex);

	for (std::vector<jlwuit::Component *>::iterator i=_components.begin(); i!=_components.end(); i++) {
		(*i)->RevalidateAll();
	}
	
	_is_valid = true;
}

bool Component::IsValid()
{
	return _is_valid;
}

Style * Component::GetStyle()
{
	return _style;
}

void Component::SetStyle(Style *style)
{
	_style->Copy(style);
}

int Component::GetBaseline(int w, int h)
{
	return -1;
}

lwuit_component_baseline_t Component::GetBaselineResizeBehavior() 
{
	return LCB_UNKNOWN;
}

lwuit_component_alignment_t Component::GetAlignmentX()
{
	return _alignment_x;
}

lwuit_component_alignment_t Component::GetAlignmentY()
{
	return _alignment_y;
}

void Component::SetAlignmentX(lwuit_component_alignment_t align)
{
	_alignment_x = align;
}

void Component::SetAlignmentY(lwuit_component_alignment_t align)
{
	_alignment_y = align;
}

void Component::SetComponentOrientation(lwuit_component_orientation_t orientation)
{
	_orientation = orientation;
}

lwuit_component_orientation_t Component::GetComponentOrientation()
{
	return _orientation;
}

Component * Component::GetParent()
{
	return _parent;
}

Component * Component::GetTopLevelAncestor()
{
	Component *parent = GetParent();

	while ((void *)parent != NULL) {
		if (parent->GetParent() == NULL) {
			return parent;
		}

		parent = parent->GetParent();
	}

	return NULL;
}

void Component::SetOpaque(bool b)
{
	_is_opaque = b;
}

bool Component::IsOpaque()
{
	return _is_opaque;
}

bool Component::IsEnabled()
{
	return _enabled;
}

void Component::SetEnabled(bool b)
{
	if (_enabled == b) {
		return;
	}

	_enabled = b;

	Repaint();
}

void Component::SetParent(Component *parent)
{
	_parent = parent;
}

void Component::SetPreferredSize(struct lwuit_size_t size)
{
	_preferred_size.width = size.width;
	_preferred_size.height = size.height;

	if (_preferred_size.width < 1) {
		_preferred_size.width = 1;
	}

	if (_preferred_size.height < 1) {
		_preferred_size.height = 1;
	}
}

struct lwuit_size_t Component::GetPreferredSize()
{
	return _preferred_size;
}

void Component::Move(int x, int y)
{
	SetLocation(_location.x+x, _location.y+y);
}

void Component::Move(lwuit_point_t location)
{
	Move(location.x, location.y);
}

bool Component::IsCyclicFocus()
{
	return false;
}

void Component::SetCyclicFocus(bool b)
{
}

lwuit_point_t Component::GetAbsoluteLocation()
{
	Component *parent = GetParent();

	lwuit_point_t t;

	t.x = _location.x;
	t.y = _location.y;

	if ((void *)parent == NULL) {
		return t;
	}

	do {
		if (parent->GetParent() != NULL) {
			t.x = t.x + parent->GetX();	
			t.y = t.y + parent->GetY();	
		}

		parent = parent->GetParent();
	} while ((void *)parent != NULL);

	return t;
}

lwuit_region_t Component::GetVisibleBounds()
{
	lwuit_region_t t;

	t.x = 0;
	t.y = 0;
	t.width = 0;
	t.height = 0;

	return t;
}

void Component::SetNavigationEnabled(bool b)
{
}

bool Component::IsNavigationEnabled()
{
	return false;
}

void Component::SetLayout(Layout *layout)
{
	_layout = layout;
}

Component * Component::GetNextFocusLeft()
{
	return NULL;
}

Component * Component::GetNextFocusRight()
{
	return NULL;
}

Component * Component::GetNextFocusUp()
{
	return NULL;
}

Component * Component::GetNextFocusDown()
{
	return NULL;
}

void Component::SetNextFocusLeft(Component *cmp)
{
}

void Component::SetNextFocusRight(Component *cmp)
{
}

void Component::SetNextFocusUp(Component *cmp)
{
}

void Component::SetNextFocusDown(Component *cmp)
{
}

void Component::SetNextComponentFocus(Component *left, Component *right, Component *up, Component *down)
{
}

void Component::SetBounds(int x, int y, int w, int h)
{
	_location.x = x;
	_location.y = y;

	if (_size.width != w || _size.height != h) {
		_size.width = w;
		_size.height = h;

		if (_size.width < 1) {
			_size.width = 1;
		}

		if (_size.height < 1) {
			_size.height = 1;
		}
	}

	Repaint();
}

void Component::SetBounds(struct lwuit_point_t point, struct lwuit_size_t size)
{
	SetBounds(point.x, point.y, size.width, size.height);
}

void Component::SetBounds(struct lwuit_region_t region)
{
	SetBounds(region.x, region.y, region.width, region.height);
}

void Component::SetLocation(int x, int y)
{
	_location.x = x;
	_location.y = y;

	Repaint();
}

void Component::SetLocation(struct lwuit_point_t point)
{
	SetLocation(point.x, point.y);
}

void Component::SetSize(int w, int h)
{
	if (_size.width == w && _size.height == h) {
		return;
	}

	_size.width = w;
	_size.height = h;

	if (_size.width < 1) {
		_size.width = 1;
	}

	if (_size.height < 1) {
		_size.height = 1;
	}

	Repaint();
}

void Component::SetSize(struct lwuit_size_t size)
{
	SetSize(size.width, size.height);
}

int Component::GetX()
{
	return _location.x;
}

int Component::GetY()
{
	return _location.y;
}

int Component::GetAbsoluteX()
{
	Component *parent = GetParent();

	if ((void *)parent == NULL) {
		return -1;
	}

	int location = _location.x;

	do {
		if (parent->GetParent() != NULL) {
			location = location + parent->GetX();	
		}

		parent = parent->GetParent();
	} while ((void *)parent != NULL);

	return location;
}

int Component::GetAbsoluteY()
{
	Component *parent = GetParent();

	if ((void *)parent == NULL) {
		return -1;
	}

	int location = _location.y;

	do {
		if (parent->GetParent() != NULL) {
			location = location + parent->GetY();	
		}

		parent = parent->GetParent();
	} while ((void *)parent != NULL);

	return location;
}

int Component::GetWidth()
{
	return _size.width;
}

int Component::GetHeight()
{
	return _size.height;
}

struct lwuit_point_t Component::GetLocation()
{
	return _location;
}

struct lwuit_size_t Component::GetSize()
{
	return _size;
}

struct lwuit_region_t Component::GetBounds()
{
	struct lwuit_region_t t;

	t.x = _location.x;
	t.y = _location.y;
	t.width = _size.width;
	t.height = _size.height;

	return t;
}

void Component::RaiseToTop()
{
	if (_parent == NULL) {
		return;
	}

	_parent->RaiseComponentToTop(this);
}

void Component::LowerToBottom()
{
	if (_parent == NULL) {
		return;
	}

	_parent->LowerComponentToBottom(this);
}

void Component::PutAtop(Component *c)
{
	if (_parent == NULL) {
		return;
	}

	if ((void *)c == NULL) {
		return;
	}

	_parent->PutComponentATop(this, c);
}

void Component::PutBelow(Component *c)
{
	if (_parent == NULL) {
		return;
	}

	if ((void *)c == NULL) {
		return;
	}

	_parent->PutComponentBelow(this, c);
}

void Component::SetNavigation(Component *left, Component *right, Component *up, Component *down)
{
	_left = left;
	_right = right;
	_up = up;
	_down = down;
}

Component * Component::GetLeftComponent()
{
	return _left;
}

Component * Component::GetRightComponent()
{
	return _right;
}

Component * Component::GetUpComponent()
{
	return _up;
}

Component * Component::GetDownComponent()
{
	return _down;
}

void Component::RequestFocus()
{
	if (_has_focus == false) {
		if (_parent != NULL) {
			_has_focus = true;

			_parent->RequestComponentFocus(this);
		}
	}
}

void Component::ReleaseFocus()
{
	if (_has_focus == true) {
		if (_parent != NULL) {
			_has_focus = false;

			_parent->ReleaseComponentFocus(this);
		}
	}
}

bool Component::HasFocus()
{
	return _has_focus;
}

bool Component::IsFocusable()
{
	return _is_focusable;
}

void Component::SetFocusable(bool b)
{
	_is_focusable = b;
}

bool Component::IsVisible()
{
	return _is_visible;
}

void Component::SetVisible(bool b)
{
	if (_is_visible == b) {
		return;
	}

	_is_visible = b;

	Repaint();
}

Layout * Component::GetLayout()
{
	return _layout;
}

void Component::DoLayout()
{
	if (_layout != NULL) {
		_layout->DoLayout(this);

		for (std::vector<Component *>::iterator i=_components.begin(); i!=_components.end(); i++) {
			Component *container = dynamic_cast<Component *>(*i);
			
			if (container != NULL) {
				container->DoLayout();
			}
		}
	}
}

bool Component::Intersects(int x, int y)
{
	if ((x>_location.x && x<(_location.x+_size.width)) && (y>_location.y && y<(_location.y+_size.height))) {
		return true;
	}

	return false;
}

bool Component::Intersects(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	int ax = x1,
			ay = y1,
			bx = ax+w1,
			by = ay+h1;
	int cx = x2,
			cy = y2,
			dx = cx+w2,
			dy = cy+h2;

	return (((ax > dx)||(bx < cx)||(ay > dy)||(by < cy)) == 0);
}


bool Component::OnKeyDown(UserEvent *event)
{
	return false;
}

bool Component::OnKeyPress(UserEvent *event)
{
	return false;
}

bool Component::OnKeyUp(UserEvent *event)
{
	return false;
}

bool Component::OnKeyLongPress(UserEvent *event)
{
	return false;
}

bool Component::OnMousePress(UserEvent *event)
{
	return false;
}

bool Component::OnMouseRelease(UserEvent *event)
{
	return false;
}

bool Component::OnMouseClick(UserEvent *event)
{
	return false;
}

bool Component::OnMouseWheel(UserEvent *event)
{
	return false;
}

bool Component::OnMouseMove(UserEvent *event)
{
	return false;
}

bool Component::OnMouseOver(UserEvent *event)
{
	return false;
}

bool Component::OnMouseOut(UserEvent *event)
{
	return false;
}

void Component::Paint(Graphics *g)
{
  std::unique_lock<std::mutex> lock(_container_mutex);

	struct lwuit_region_t clip = g->GetClip();

	jlwuit::Color bgcolor = _style->GetColor("bg.color");

	if (bgcolor.GetARGB() != 0x00000000) {
		g->SetColor(bgcolor.GetARGB());
		g->FillRectangle(0, 0, GetWidth(), GetHeight());
	}

	DoLayout();

	for (std::vector<Component *>::iterator i=_components.begin(); i!=_components.end(); i++) {
		Component *c = (*i);

		if (c->IsVisible() == true && c->IsValid() == false) {
			int cx = c->GetX(),
					cy = c->GetY(),
					cw = c->GetWidth(),
					ch = c->GetHeight();

			if (cx > clip.width) {
				cx = clip.width;
			}

			if (cy > clip.height) {
				cy = clip.height;
			}

			if (cw > (clip.width-cx)) {
				cw = clip.width-cx;
			}

			if (ch > (clip.height-cy)) {
				ch = clip.height-cy;
			}

			if (cw > 0 && ch > 0) {
				g->SetClip(clip.x, clip.y, clip.width, clip.height);
				g->Translate(cx, cy);
				c->Paint(g);
				g->Translate(-cx, -cy);

				g->Reset();
			}

			c->Revalidate();
		}
	}

	g->SetClip(clip.x, clip.y, clip.width, clip.height);
	g->Reset();

	Revalidate();
}

void Component::Repaint(Component *cmp)
{
	Invalidate();

	if (_parent != NULL) {
		_parent->Repaint(cmp);
	}
}

struct lwuit_margin_t Component::GetInsets()
{
	return _margins;
}

void Component::SetInsets(struct lwuit_margin_t insets)
{
	_margins.left = insets.left;
	_margins.top = insets.top;
	_margins.right = insets.right;
	_margins.bottom = insets.bottom;
}

void Component::SetInsets(int left, int top, int right, int bottom)
{
	_margins.left = left;
	_margins.top = top;
	_margins.right = right;
	_margins.bottom = bottom;
}

void Component::Add(Component *c, int index)
{
	if (index < 0 || index > (int)_components.size()) {
		throw Exception("Index out of range");
	}

	if (c == NULL) {
		throw Exception("Adding null component to container");
	}

	if (dynamic_cast<Component *>(c) == this) {
		throw Exception("Adding own container");
	}

  std::unique_lock<std::mutex> lock(_container_mutex);

	if (std::find(_components.begin(), _components.end(), c) == _components.end()) {
		_components.insert(_components.begin()+index, c);

		Component *container = dynamic_cast<Component *>(c);

		if (container != NULL) {
			Component *focus = container->GetFocusOwner();

			c->SetParent(this);

			if ((void *)focus != NULL) {
				RequestComponentFocus(focus);
			}
		} else {
			c->SetParent(this);
		}
	}
}

void Component::Add(Component *c)
{
	Add(c, _components.size());
}

void Component::Add(Component *c, GridBagConstraints *constraints)
{
	Add(c, _components.size());

	if (_layout != NULL) {
		GridBagLayout *layout = dynamic_cast<GridBagLayout *>(_layout);

		if (layout != NULL) {
			layout->AddLayoutComponent(c, constraints);
		}
	}
}

void Component::Add(Component *c, std::string align)
{
	Add(c, _components.size());

	if (_layout != NULL) {
		BorderLayout *layout = dynamic_cast<BorderLayout *>(_layout);

		if (layout != NULL) {
			lwuit_borderlayout_align_t t = BLA_UNKNOWN;
			
			align = jcommon::StringUtils::ToLower(align);

			if (align == "north") {
				t = BLA_NORTH;
			} else if (align == "south") {
				t = BLA_SOUTH;
			} else if (align == "east") {
				t = BLA_EAST;
			} else if (align == "west") {
				t = BLA_WEST;
			} else if (align == "center") {
				t = BLA_CENTER;
			}

			layout->AddLayoutComponent(c, t);
		}
	}
}

void Component::Remove(Component *c)
{
  std::unique_lock<std::mutex> lock(_container_mutex);

	Component *container = dynamic_cast<Component *>(c);

	if (container != NULL) {
		Component *focus = GetFocusOwner();

		if ((void *)focus != NULL) {
			Component *parent = focus->GetParent();

			while ((void *)parent != NULL) {
				if (parent == container) {
					focus->ReleaseFocus();

					break;
				}

				if (parent->GetParent() == NULL) {
					break;
				}

				parent = parent->GetParent();
			}
		}
	} else {
		c->ReleaseFocus();
	}

	if (_layout != NULL) {
		BorderLayout *layout = dynamic_cast<BorderLayout *>(_layout);

		if (layout != NULL) {
			layout->RemoveLayoutComponent(c);
		}
	}

	for (std::vector<Component *>::iterator i=_components.begin(); i!=_components.end(); i++) {
		if (c == (*i)) {
			c->SetParent(NULL);

			_components.erase(i);

			return;
		}
	}
}

void Component::RemoveAll()
{
	Component *focus = GetFocusOwner();

	if ((void *)focus != NULL) {
		Component *parent = focus->GetParent();

		while ((void *)parent != NULL) {
			if (parent == this) {
				focus->ReleaseFocus();

				break;
			}

			if (parent->GetParent() == NULL) {
				break;
			}

			parent = parent->GetParent();
		}
	}

  _container_mutex.lock();

  _components.clear();

  _container_mutex.unlock();

	Repaint();
}

std::vector<Component *> Component::GetComponents()
{
	return _components;
}

void Component::RequestComponentFocus(Component *c)
{
	if (c == NULL || c->IsFocusable() == false) {
		return;
	}

	if (_parent != NULL) {
		_parent->RequestComponentFocus(c);
	} else {
		if (_focus != NULL && _focus != c) {
			_focus->ReleaseFocus();
		}

		_focus = c;

		_focus->Invalidate();
		// _focus->Repaint();

		Repaint();
	}
}

void Component::ReleaseComponentFocus(Component *c)
{
	if (c == NULL) {
		return;
	}

	if (_parent != NULL) {
		_focus = NULL;

		_parent->ReleaseComponentFocus(c);
	} else {
		if (_focus != NULL && _focus == c) {
			// _focus->Repaint();
		}

		_focus = NULL;

		Repaint();
	}
}

Component * Component::GetFocusOwner()
{
	if (_parent != NULL) {
		return _parent->GetFocusOwner();
	}

	return _focus;
}

void Component::RaiseComponentToTop(Component *c)
{
	bool b = false;

  std::unique_lock<std::mutex> lock(_container_mutex);

	for (std::vector<Component *>::iterator i=_components.begin(); i!=_components.end(); i++) {
		if (c == (*i)) {
			_components.erase(i);

			b = true;

			break;
		}
	}

	if (b == true) {
		_components.push_back(c);
	}
}

void Component::LowerComponentToBottom(Component *c)
{
	bool b = false;

  std::unique_lock<std::mutex> lock(_container_mutex);

	for (std::vector<Component *>::iterator i=_components.begin(); i!=_components.end(); i++) {
		if (c == (*i)) {
			_components.erase(i);

			b = true;

			break;
		}
	}

	if (b == true) {
		_components.insert(_components.begin(), c);
	}
}

void Component::PutComponentATop(Component *c, Component *c1)
{
  std::unique_lock<std::mutex> lock(_container_mutex);

	std::vector<Component *>::iterator i;

	i = std::find(_components.begin(), _components.end(), c1);

	if (i == _components.end()) {
		return;
	}

	_components.insert(i+1, c);
}

void Component::PutComponentBelow(Component *c, Component *c1)
{
  std::unique_lock<std::mutex> lock(_container_mutex);

	std::vector<Component *>::iterator i;

	i = std::find(_components.begin(), _components.end(), c1);

	if (i == _components.end()) {
		return;
	}

	_components.insert(i, c);
}

void Component::SetName(std::string name)
{
	_name = name;
}

std::string Component::GetName()
{
	return _name;
}

void Component::SetMinimumSize(lwuit_size_t size)
{
}

void Component::SetMaximumSize(lwuit_size_t size)
{
}

lwuit_size_t Component::GetMinimumSize()
{
	lwuit_size_t t;

	t.width = 0;
	t.height = 0;

	return t;
}

lwuit_size_t Component::GetMaximumSize()
{
	lwuit_size_t t;

	t.width = 1000;
	t.height = 1000;

	return t;
}

bool Component::IsFocusCycleRoot()
{
	return _is_cycle_root;
}

void Component::SetFocusCycleRoot(bool b)
{
}

Component * Component::GetFocusCycleRootAncestor()
{
	return NULL;
}

}
