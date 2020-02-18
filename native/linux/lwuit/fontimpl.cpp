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

#include "strings.h"

namespace jlwuit {

FontImpl::FontImpl(std::string name, lwuit_font_attributes_t attributes, int size):
	Font()
{
	_attributes = attributes;

	_native_font = new jgui::Font(name, jgui::JFA_NORMAL, size);
}

FontImpl::~FontImpl()
{
  delete _native_font;
  _native_font = NULL;
}

bool FontImpl::SetEncoding(std::string code)
{
	jgui::jfont_encoding_t t = jgui::JFE_ISO_8859_1;

	if (strncasecmp(code.c_str(), "utf-8", 3) == 0) {
		t = jgui::JFE_UTF8;
	} else if (
			strncasecmp(code.c_str(), "latin-1", 3) == 0 ||
			strncasecmp(code.c_str(), "iso-8859-1", 3) == 0) {
		t = jgui::JFE_ISO_8859_1;
	} else {
		return false;
	}

	_native_font->SetEncoding(t);

	return true;
}

lwuit_font_attributes_t FontImpl::GetAttributes()
{
	return _attributes;
}

std::string FontImpl::GetName()
{
	return _native_font->GetName();
}

int FontImpl::GetSize()
{
	return _native_font->GetSize();
}

int FontImpl::GetLineSize()
{
	return _native_font->GetSize()+2;
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
	return _native_font->GetMaxAdvanceWidth();
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
	jgui::jfont_extends_t region = _native_font->GetStringExtends(text);

	return (lwuit_region_t){int(region.bearing.x), int(region.bearing.y), int(region.size.width), int(region.size.height)};
}

lwuit_region_t FontImpl::GetGlyphExtends(int symbol)
{
	jgui::jfont_extends_t region = _native_font->GetGlyphExtends(symbol);

	return (lwuit_region_t){int(region.bearing.x), int(region.bearing.y), int(region.size.width), int(region.size.height)};
}

std::string FontImpl::TruncateString(std::string text, std::string extension, int width)
{
	return _native_font->TruncateString(text, extension, width);
}

}
