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
#include "rootcontainer.h"
#include "implementation.h"
#include "layer.h"
#include "scene.h"
#include "exception.h"
#include "dialog.h"

#include <algorithm>

namespace jlwuit {

RootContainer::RootContainer(Layer *layer, int x, int y, int w, int h):
	Component(x, y, w, h)
{
	_layer = layer;

	SetVisible(true);
}

RootContainer::~RootContainer()
{
	_dialogs.clear();
}

RootContainer * RootContainer::GetContainer(Layer *layer)
{
	return Implementation::GetInstance()->GetContainer(layer);
}

void RootContainer::RegisterDialog(Dialog *dialog)
{
	if (dialog == NULL) {
		return;
	}

	jthread::AutoLock lock(&_dialogs_mutex);

	std::vector<Dialog *>::iterator i = std::find(_dialogs.begin(), _dialogs.end(), dialog);

	if (i == _dialogs.end()) {
		_dialogs.push_back(dialog);
	}
}

void RootContainer::UnregisterDialog(Dialog *dialog)
{
	if (dialog == NULL) {
		return;
	}

	jthread::AutoLock lock(&_dialogs_mutex);

	std::vector<Dialog *>::iterator i = std::find(_dialogs.begin(), _dialogs.end(), dialog);

	if (i != _dialogs.end()) {
		_dialogs.erase(i);
	}
}

void RootContainer::PaintDialogs(Graphics *g)
{
	jthread::AutoLock lock(&_dialogs_mutex);

	struct lwuit_region_t clip = g->GetClip();

	for (std::vector<Dialog *>::iterator i=_dialogs.begin(); i!=_dialogs.end(); i++) {
		Dialog *c = (*i);

		if (c->IsVisible() == true) {
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
				g->Translate(cx, cy);
				g->SetClip(0, 0, cw-1, ch-1);
				c->Paint(g);
				g->ReleaseClip();
				g->Translate(-cx, -cy);
			}
		}
	}
}

Layer * RootContainer::GetLayer()
{
	return _layer;
}

Component * RootContainer::GetTopLevelAncestor()
{
	return this;
}

void RootContainer::Add(Component *c, int index)
{
	if (dynamic_cast<Scene *>(c) == NULL) {
		throw Exception("Component does not inherit from Scene");
	}

	Component::Add(c, index);
}

void RootContainer::Add(Component *c)
{
	if (dynamic_cast<Scene *>(c) == NULL) {
		throw Exception("Component does not inherit from Scene");
	}

	Component::Add(c);
}

void RootContainer::Add(Component *c, GridBagConstraints *constraints)
{
	if (dynamic_cast<Scene *>(c) == NULL) {
		throw Exception("Component does not inherit from Scene");
	}

	Component::Add(c, constraints);
}

void RootContainer::Add(Component *c, std::string align)
{
	if (dynamic_cast<Scene *>(c) == NULL) {
		throw Exception("Component does not inherit from Scene");
	}

	Component::Add(c, align);
}

void RootContainer::Paint(Graphics *g)
{
	Component::Paint(g);

	PaintDialogs(g);
}

}

