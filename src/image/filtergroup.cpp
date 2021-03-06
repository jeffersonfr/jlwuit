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
#include "filtergroup.h"

#include <algorithm>

namespace jlwuit {

FilterGroup::FilterGroup()
{
}

FilterGroup::~FilterGroup()
{
  std::unique_lock<std::mutex> lock(_mutex);

	_filters.clear();
}

void FilterGroup::AddFilter(Filter *codec)
{
  std::unique_lock<std::mutex> lock(_mutex);

	if (std::find(_filters.begin(), _filters.end(), codec) == _filters.end()) {
		_filters.push_back(codec);
	}
}

void FilterGroup::RemoveFilter(Filter *codec)
{
  std::unique_lock<std::mutex> lock(_mutex);

	std::vector<Filter *>::iterator i = std::find(_filters.begin(), _filters.end(), codec);

	if (i != _filters.end()) {
		_filters.erase(i);
	}
}

void FilterGroup::RemoveAllFilters()
{
  std::unique_lock<std::mutex> lock(_mutex);

	_filters.clear();
}

bool FilterGroup::Transform(uint8_t *data, int width, int height)
{
  std::unique_lock<std::mutex> lock(_mutex);

	for (std::vector<Filter *>::iterator i=_filters.begin(); i!=_filters.end(); i++) {
		(*i)->Transform(data, width, height);
	}

	return true;
}

}
