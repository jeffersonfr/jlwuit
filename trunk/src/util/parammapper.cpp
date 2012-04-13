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
#include "method.h"
#include "ipchelper.h"
#include "jstringtokenizer.h"
#include "joutofboundsexception.h"

#include <sstream>

namespace jlwuit {

ParamMapper::ParamMapper()
{
}

ParamMapper::~ParamMapper()
{
}

std::map<std::string, std::string> & ParamMapper::GetParameters()
{
	return _params;
}

std::string ParamMapper::GetTextParam(std::string key, std::string value)
{
	if (_params.find(key) != _params.end()) {
		return _params[key];
	}

	return value;
}

bool ParamMapper::GetBooleanParam(std::string key, bool value)
{
	if (_params.find(key) != _params.end()) {
		std::string str = _params[key];

		if (str == "0" || str == "false") {
			return false;
		} else {
			return true;
		}
	}

	return value;
}

int64_t ParamMapper::GetIntegerParam(std::string key, int64_t value)
{
	if (_params.find(key) != _params.end()) {
		std::string str = _params[key];

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

double ParamMapper::GetDecimalParam(std::string key, double value)
{
	if (_params.find(key) != _params.end()) {
		return atof(_params[key].c_str());
	}

	return value;
}

void ParamMapper::SetTextParam(std::string key, std::string value)
{
	_params[key] = value;
}

void ParamMapper::SetBooleanParam(std::string key, bool value)
{
	char *str = (char *)"false";

	if (value == true) {
		str = (char *)"true";
	}

	_params[key] = str;
}

void ParamMapper::SetIntegerParam(std::string key, int64_t value)
{
	char str[32];
	
	snprintf(str, 30, "%lld", value);

	_params[key] = str;
}

void ParamMapper::SetDecimalParam(std::string key, double value)
{
	char str[32];
	
	snprintf(str, 30, "%.2f", value);

	_params[key] = str;
}

void ParamMapper::RemoveParamByID(std::string id)
{
	std::map<std::string, std::string>::iterator i=_params.find(id);

	if (i != _params.end()) {
		_params.erase(i);
	}
}

void ParamMapper::Copy(ParamMapper *mapper)
{
	if (mapper == NULL) {
		return;
	}

	std::map<std::string, std::string> params = mapper->GetParameters();

	for (std::map<std::string, std::string>::iterator i=params.begin(); i!=params.end(); i++) {
		SetTextParam(i->first, i->second);
	}
}

}
