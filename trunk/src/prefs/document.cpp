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
#include "document.h"

#include "jio/jfile.h"

#include <iostream>
#include <sstream>
#include <algorithm>

namespace jlwuit {

Document::Document(std::string name)
{
	_name = name;
}

Document::~Document()
{
}

std::string Document::GetName()
{
	return _name;
}

void Document::AddElement(Element *e)
{
	if (std::find(_elements.begin(), _elements.end(), e) != _elements.end()) {
		return;
	}

	_elements.push_back(e);
}

void Document::RemoveElementByID(std::string id)
{
	for (std::vector<Element *>::iterator i=_elements.begin(); i!=_elements.end(); i++) {
		Element *element = (*i);

		if (element->GetAttributes()->GetTextParam("id") == id) {
			_elements.erase(i);

			delete element;

			break;
		}
	}
}

void Document::RemoveElementByIndex(int index)
{
	if (index < 0 || index >= (int)_elements.size()) {
		return;
	}

	Element *element = _elements[index];

	_elements.erase(_elements.begin()+index);

	delete element;
}

void Document::RemoveElements()
{
	_elements.clear();
}

Element * Document::GetElementByID(std::string id)
{
	for (std::vector<Element *>::iterator i=_elements.begin(); i!=_elements.end(); i++) {
		Element *element = (*i);

		if (element->GetAttributes()->GetTextParam("id") == id) {
			return element;
		}
	}

	return NULL;
}

Element * Document::GetElementByIndex(int index)
{
	if (index < 0 || index >= (int)_elements.size()) {
		return NULL;
	}

	return _elements[index];
}

std::vector<Element *> Document::GetElements()
{
	return _elements;
}

}
