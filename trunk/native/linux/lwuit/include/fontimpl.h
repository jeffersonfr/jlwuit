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
#ifndef FONTIMPL_H
#define FONTIMPL_H

#include "font.h"

#include "jgui/jfont.h"

namespace jlwuit {

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class FontImpl : public Font {

	private:
		lwuit_font_attributes_t _attributes;

	public:
		jgui::Font *_native_font;

	public:
		/**
		 * \brief
		 *
		 */
		FontImpl(std::string name, lwuit_font_attributes_t attributes, int size);

		/**
		 * \brief
		 *
		 */
		virtual ~FontImpl();

		/**
		 * \brief
		 *
		 */
		virtual bool SetEncoding(std::string code);
		
		/**
		 * \brief
		 *
		 */
		virtual lwuit_font_attributes_t GetAttributes();
		
		/**
		 * \brief
		 *
		 */
		virtual std::string GetName();
		
		/**
		 * \brief
		 *
		 */
		virtual int GetSize();
		
		/**
		 * \brief
		 *
		 */
		virtual int GetLineSize();
		
		/**
		 * \brief
		 *
		 */
		virtual int GetAscender();
		
		/**
		 * \brief
		 *
		 */
		virtual int GetDescender();
		
		/**
		 * \brief
		 *
		 */
		virtual int GetMaxAdvanced();
		
		/**
		 * \brief
		 *
		 */
		virtual int GetLeading();
		
		/**
		 * \brief
		 *
		 */
		virtual int GetStringWidth(std::string text);
		
		/**
		 * \brief
		 *
		 */
		virtual lwuit_region_t GetStringExtends(std::string text);

		/**
		 * \brief
		 *
		 */
		virtual lwuit_region_t GetGlyphExtends(int symbol);

		/**
		 * \brief
		 *
		 */
		virtual std::string TruncateString(std::string text, std::string extension, int width);
};

}

#endif
