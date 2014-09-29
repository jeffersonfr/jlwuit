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
#include "font.h"
#include "implementation.h"

namespace jlwuit {

Font::Font()
{
}

Font::~Font()
{
}

Font * Font::CreateFont(std::string name, lwuit_font_attributes_t attributes, int size)
{
	return Implementation::GetInstance()->CreateFont(name, attributes, size);
}

bool Font::SetEncoding(std::string code)
{
	return false;
}

lwuit_font_attributes_t Font::GetAttributes()
{
	return LFA_NORMAL;
}

std::string Font::GetName()
{
	return "";
}

int Font::GetSize()
{
	return -1;
}

int Font::GetLineSize()
{
	return -1;
}

int Font::GetAscender()
{
	return -1;
}

int Font::GetDescender()
{
	return -1;
}

int Font::GetMaxAdvanced()
{
	return -1;
}

int Font::GetLeading()
{
	return -1;
}

int Font::GetStringWidth(std::string text)
{
	return -1;
}

struct lwuit_region_t Font::GetStringExtends(std::string text)
{
	struct lwuit_region_t t = {0, 0, 0, 0};

	return t;
}

struct lwuit_region_t Font::GetGlyphExtends(int symbol)
{
	struct lwuit_region_t t = {0, 0, 0, 0};

	return t;
}

std::string Font::TruncateString(std::string text, std::string extension, int width)
{
	return text;
}

}
