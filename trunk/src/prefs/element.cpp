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
#include "element.h"
#include "jstringutils.h"
#include "jfile.h"
#include "jruntimeexception.h"

#include <iostream>
#include <sstream>

#include <fcntl.h>

namespace jlwuit {

Element::Element(std::string name)
{
	_name = name;
}

Element::~Element()
{
}

std::string Element::GetName()
{
	return _name;
}

std::map<std::string, std::string> & Element::GetAttributes()
{
	return _attributes;
}
	
std::string Element::GetLiteralAttribute(std::string key, std::string value)
{
	if (_attributes.find(key) != _attributes.end()) {
		return _attributes[key];
	}

	return value;
}
	
bool Element::GetBooleanAttribute(std::string key, bool value)
{
	if (_attributes.find(key) != _attributes.end()) {
		std::string str = _attributes[key];

		if (str == "0" || str == "false") {
			return false;
		} else {
			return true;
		}
	}

	return value;
}
	
int64_t Element::GetIntegerAttribute(std::string key, int64_t value)
{
	if (_attributes.find(key) != _attributes.end()) {
		std::string str = _attributes[key];

		if (str.size() == 0 || str.size() > 10) {
			return -1;
		}

		int radix = 10;
		char *tmp = (char *)str.c_str();
		char *err;

		if (tmp[0] == '0') {
			if (strnlen(tmp, 2) > 1 && (tmp[1] == 'x' || tmp[1] == 'X')) {
				radix = 16;
				tmp = tmp+2;
			} else {
				radix = 8;
				tmp = tmp+1;
			}
		}

		return strtoll(tmp, &err, radix);
	}

	return value;
}
	
double Element::GetDecimalAttribute(std::string key, double value)
{
	if (_attributes.find(key) != _attributes.end()) {
		return atof(_attributes[key].c_str());
	}

	return value;
}
	
void Element::SetLiteralAttribute(std::string key, std::string value)
{
	_attributes[key] = value;
}
	
void Element::SetBooleanAttribute(std::string key, bool value)
{
	std::string str = "false";

	if (value == true) {
		str = "true";
	}

	_attributes[key] = value;
}
	
void Element::SetIntegerAttribute(std::string key, int64_t value)
{
	std::string str = "0";

	if (value == true) {
		// todo
	}

	_attributes[key] = value;
}
	
void Element::SetDecimalAttribute(std::string key, double value)
{
	std::string str = "0";

	if (value == true) {
		// todo
	}

	_attributes[key] = value;
}
	
}
