/***************************************************************************
 *   Copyright (C) 2005 by Jeff Ferr                                       *
 *   root@sat                                                              *
 *                                                                         *
 *   This program is free software you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "style.h"

#include <algorithm>

namespace jlwuit {

Style::Style()
{
	_is_modified = false;

	SetIntegerParam("bg.color", 0xa0000000);
	SetIntegerParam("fg.color", 0xfff0f0f0);
	SetIntegerParam("border.color", 0xff808080);
	SetIntegerParam("scroll.color", 0xfff0f0f0);
	SetIntegerParam("focus.bg.color", 0xa0a0a0a0);
	SetIntegerParam("focus.fg.color", 0xff000000);
	SetIntegerParam("focus.border.color", 0xff808080);
	SetIntegerParam("focus.scroll.color", 0xfff0f0f0);
	SetIntegerParam("selected.bg.color", 0xfff0f0f0);
	SetIntegerParam("selected.fg.color", 0xff000000);
	SetIntegerParam("selected.border.color", 0xff808080);
	SetIntegerParam("selected.scroll.color", 0xfff0f0f0);
	SetIntegerParam("disabled.bg.color", 0x00000000);
	SetIntegerParam("disabled.fg.color", 0xfff0f0f0);
	SetIntegerParam("disabled.border.color", 0xff808080);
	SetIntegerParam("disabled.scroll.color", 0xff808080);

	SetBackgroundImage(NULL);
	SetScaleImage(true);
	SetPadding(0, 0, 0, 0);
	SetMargin(0, 0, 0, 0);
}

Style::~Style()
{
}

bool Style::IsModified()
{
	return _is_modified;
}

void Style::SetModified(bool modified)
{
	_is_modified = modified;
}

const Color Style::GetColor(std::string color_id)
{
	return jlwuit::Color(GetIntegerParam(color_id, 0xff000000));
}

Image * Style::GetBackgroundImage()
{
	return _bg_image;
}

void Style::SetBackgroundImage(Image *image)
{
	_bg_image = image;
}

bool Style::IsScaleImage()
{
	return _is_scale_image;
}

void Style::SetScaleImage(bool scale_image)
{
	_is_scale_image = scale_image;
}

void Style::SetPadding(int left, int right, int top, int bottom)
{
	_padding.left = left;
	_padding.right = right;
	_padding.top = top;
	_padding.bottom = bottom;
}

void Style::SetMargin(int left, int right, int top, int bottom)
{
	_margin.left = left;
	_margin.right = right;
	_margin.top = top;
	_margin.bottom = bottom;
}

struct lwuit_margin_t Style::GetPadding()
{
	return _padding;
}

struct lwuit_margin_t Style::GetMargin()
{
	return _margin;
}

void Style::RegisterStyleListener(StyleListener *listener)
{
	if (listener == NULL) {
		return;
	}

	if (std::find(_style_listeners.begin(), _style_listeners.end(), listener) == _style_listeners.end()) {
		_style_listeners.push_back(listener);
	}
}

void Style::RemoveStyleListener(StyleListener *listener)
{
	if (listener == NULL) {
		return;
	}

	std::vector<StyleListener *>::iterator i = std::find(_style_listeners.begin(), _style_listeners.end(), listener);

	if (i != _style_listeners.end()) {
		_style_listeners.erase(i);
	}
}

}
