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
#ifndef LWUIT_LOOKANDFILL_H
#define LWUIT_LOOKANDFILL_H

#include "style.h"
#include "reference.h"

#include <map>

namespace jlwuit {

enum lwuit_lookandfeel_status_t {
	LST_NORMAL,
	LST_FOCUS,
	LST_DISABLE
};

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class LookAndFeel {

	private:
		/** \brief */
		static LookAndFeel *_instance;
		/** \brief */
		static std::map<std::string, struct lwuit_reference_t *> _fonts;
		/** \brief */
		static std::map<std::string, struct lwuit_reference_t *> _images;

	private:
		/** \brief */
		Style *_default_style;
		/** \brief */
		lwuit_lookandfeel_status_t _type;
	
	private:
		/**
		 * \brief
		 *
		 */
		static int * GetReference(std::map<std::string, struct lwuit_reference_t *> *resources, std::string resource_id);

		/**
		 * \brief
		 *
		 */
		static void AddReference(std::map<std::string, struct lwuit_reference_t *> *resources, std::string resource_id, int *reference);

		/**
		 * \brief
		 *
		 */
		static void RemoveReference(std::map<std::string, struct lwuit_reference_t *> *resources, std::string resource_id);
		
		/**
		 * \brief
		 *
		 */
		virtual jlwuit::Color GetColor(Style *style, std::string color_id);

	protected:
		/**
		 * \brief
		 *
		 */
		LookAndFeel();

	public:
		/**
		 * \brief
		 *
		 */
		virtual ~LookAndFeel();
		
		/**
		 * \brief
		 *
		 */
		static LookAndFeel * GetInstance();
		
		/**
		 * \brief
		 *
		 */
		static void LoadImage(std::string resource_id, std::string path);
		
		/**
		 * \brief
		 *
		 */
		static void LoadFont(std::string resource_id, std::string name, int size);
		
		/**
		 * \brief
		 *
		 */
		static void ReleaseImage(std::string resource_id);
		
		/**
		 * \brief
		 *
		 */
		static void ReleaseFont(std::string resource_id);
		
		/**
		 * \brief
		 *
		 */
		void SetType(lwuit_lookandfeel_status_t type);

		/**
		 * \brief
		 *
		 */
		virtual Style * GetDefaultStyle();
		
		/**
		 * \brief
		 *
		 */
		void DrawBorder(jlwuit::Graphics *g, jlwuit::Style *style, int x, int y, int w, int h);
		
		/**
		 * \brief
		 *
		 */
		void DrawBox(jlwuit::Graphics *g, jlwuit::Style *style, int x, int y, int w, int h);
		
		/**
		 * \brief
		 *
		 */
		void DrawProgressBar(jlwuit::Graphics *g, jlwuit::Style *style, int value, int x, int y, int w, int h);
		
		/**
		 * \brief
		 *
		 */
		void DrawText(jlwuit::Graphics *g, jlwuit::Style *style, std::string font_id, std::string text, int x, int y, int w, int h, jlwuit::lwuit_horizontal_align_t halign = jlwuit::LHA_CENTER, jlwuit::lwuit_vertical_align_t valign = jlwuit::LVA_CENTER);
		
		/**
		 * \brief
		 *
		 */
		void DrawTextBox(jlwuit::Graphics *g, jlwuit::Style *style, std::string font_id, std::string text, int x, int y, int w, int h, 
				jlwuit::lwuit_horizontal_align_t halign = jlwuit::LHA_CENTER, jlwuit::lwuit_vertical_align_t valign = jlwuit::LVA_CENTER);
		
		/**
		 * \brief
		 *
		 */
		void DrawImage(jlwuit::Graphics *g, std::string image_id, int x, int y, int w, int h);

		/**
		 * \brief
		 *
		 */
		void DrawImage(jlwuit::Graphics *g, std::string image_id, int sx, int sy, int sw, int sh, int x, int y, int w, int h);

};

}

#endif
