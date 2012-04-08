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
#include "fontimpl.h"

namespace jlwuit {

FontImpl::FontImpl(std::string name, lwuit_font_attributes_t attributes, int height):
	Font()
{
	_attributes = attributes;

	_native_font = jgui::Font::CreateFont(name, jgui::JFA_NORMAL, height);
}

FontImpl::~FontImpl()
{
}

bool FontImpl::SetEncoding(std::string code)
{
	return _native_font->SetEncoding(code);
}

lwuit_font_attributes_t FontImpl::GetAttributes()
{
	return _attributes;
}

std::string FontImpl::GetName()
{
	return _native_font->GetName();
}

int FontImpl::GetHeight()
{
	return _native_font->GetHeight();
}

int FontImpl::GetAscender()
{
	return _native_font->GetAscender();
}

int FontImpl::GetDescender()
{
	return _native_font->GetDescender();
}

int FontImpl::GetMaxAdvanced()
{
	return _native_font->GetMaxAdvanced();
}

int FontImpl::GetLeading()
{
	return _native_font->GetLeading();
}

int FontImpl::GetStringWidth(std::string text)
{
	return _native_font->GetStringWidth(text);
}

lwuit_region_t FontImpl::GetStringExtends(std::string text)
{
	jgui::jregion_t region = _native_font->GetStringExtends(text);

	return (lwuit_region_t){region.x, region.y, region.width, region.height};
}

lwuit_region_t FontImpl::GetGlyphExtends(int symbol)
{
	jgui::jregion_t region = _native_font->GetGlyphExtends(symbol);

	return (lwuit_region_t){region.x, region.y, region.width, region.height};
}

std::string FontImpl::TruncateString(std::string text, std::string extension, int width)
{
	return _native_font->TruncateString(text, extension, width);
}

}
