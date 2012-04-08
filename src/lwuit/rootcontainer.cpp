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
#include "layer.h"
#include "scene.h"
#include "exception.h"

namespace jlwuit {

RootContainer::RootContainer(Layer *layer, int x, int y, int width, int height):
	Component(x, y, width, height)
{
	_layer = layer;

	SetVisible(true);
}

RootContainer::~RootContainer()
{
}

Layer * RootContainer::GetLayer()
{
	return _layer;
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

}

