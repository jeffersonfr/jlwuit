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
#ifndef LWUIT_GRAPHICS_H
#define LWUIT_GRAPHICS_H

#include "color.h"
#include "defines.h"

#include "jgui/jcolor.h"

#include <string>

#include <stdint.h>

namespace jlwuit {

/**
 * \brief
 *
 */
enum lwuit_composite_flags_t {
	LCF_CLEAR			= 0x0001,	// fs: 0.0 fd: 0.0
	LCF_SRC				= 0x0002,	// fs: 1.0 fd: 0.0
	LCF_SRC_OVER	= 0x0004,	// fs: 1.0 fd: 1.0-sa
	LCF_SRC_IN		= 0x0008,	// fs: da fd: 0.0
	LCF_SRC_OUT		= 0x0010,	// fs: 1.0-da fd: 0.0
	LCF_SRC_ATOP	= 0x0020,	// fs: da fd: 1.0-sa
	LCF_DST				= 0x0040,	// fs: 1.0 fd: 0.0
	LCF_DST_OVER	= 0x0080,	// fs: 1.0-da fd: 1.0
	LCF_DST_IN		= 0x0100,	// fs: 0.0 fd: sa
	LCF_DST_OUT		= 0x0200,	// fs: 0.0 fd: 1.0-sa
	LCF_DST_ATOP	= 0x0400,	// fs: 1.0-da fd: sa
	LCF_XOR				= 0x0800	// fs: 1.0-da fd: 1.0-sa 
};

/**
 * \brief
 *
 */
enum lwuit_line_join_t {
	LLJ_BEVEL	= 0x01,
	LLJ_ROUND	= 0x02,
	LLJ_MITER	= 0x04,
};

/**
 * \brief
 *
 */
enum lwuit_line_style_t {
	LLS_ROUND			= 0x01,
	LLS_BUTT			= 0x02,
	LLS_SQUARE		= 0x04,
};

/**
 * \brief
 *
 */
enum lwuit_line_type_t {
	LLT_SOLID			= 0x01,
	LLT_DASH			= 0x02,
	LLT_DASH_DOT	= 0x04,
	LLT_DOT				= 0x08
};

/**
 * \brief
 *
 */
enum lwuit_hints_t {
	LHT_NONE
};

/**
 * \brief
 *
 */
struct lwuit_pen_t {
	lwuit_line_join_t join;
	lwuit_line_style_t style;
	lwuit_line_type_t type;
	int size;
};

class Image;
class Font;

class Graphics {

	public:
		/**
		 * \brief Constructor
		 *
		 */
		Graphics();

		/**
		 * \brief Destructor
		 *
		 */
		virtual ~Graphics();

		/**
		 * \brief
		 *
		 */
		virtual void Reset();

		/**
		 * \brief
		 *
		 */
		virtual void Translate(int x, int y);

		/**
		 * \brief
		 *
		 */
		virtual struct lwuit_point_t Translate();

		/**
		 * \brief
		 *
		 */
		virtual void Rotate(double radians);

		/**
		 * \brief
		 *
		 */
		virtual double Rotate();

		/**
		 * \brief
		 *
		 */
		virtual void ClipRect(int xp, int yp, int wp, int hp);

		/**
		 * \brief
		 *
		 */
		virtual void SetClip(int xp, int yp, int wp, int hp);

		/**
		 * \brief
		 *
		 */
		virtual struct lwuit_region_t GetClip();

		/**
		 * \brief
		 *
		 */
		virtual void ReleaseClip();

		/**
		 * \brief
		 *
		 */
		virtual void SetCompositeFlags(lwuit_composite_flags_t t);

		/**
		 * \brief
		 *
		 */
		virtual lwuit_composite_flags_t GetCompositeFlags();

		/**
		 * \brief
		 *
		 */
		virtual void Clear();

		/**
		 * \brief
		 *
		 */
		virtual void Clear(int xp, int yp, int wp, int hp);

		/**
		 * \brief
		 *
		 */
		virtual void Sync();

		/**
		 * \brief
		 *
		 */
		virtual Font * GetFont();

		/**
		 * \brief
		 *
		 */
		virtual void SetFont(Font *font);

		/**
		 * \brief
		 *
		 */
		virtual Color GetColor();

		/**
		 * \brief
		 *
		 */
		virtual void SetColor(Color color);

		/**
		 * \brief
		 *
		 */
		virtual void SetPen(lwuit_pen_t pen);

		/**
		 * \brief
		 *
		 */
		virtual lwuit_pen_t GetPen();

		/**
		 * \brief
		 *
		 */
		virtual void DrawLine(int xp, int yp, int xf, int yf);

		/**
		 * \brief
		 *
		 */
		virtual void FillRectangle(int xp, int yp, int wp, int hp);

		/**
		 * \brief
		 *
		 */
		virtual void DrawRectangle(int xp, int yp, int wp, int hp);

		/**
		 * \brief
		 *
		 */
		virtual void FillBevelRectangle(int xp, int yp, int wp, int hp, int dx, int dy);

		/**
		 * \brief
		 *
		 */
		virtual void DrawBevelRectangle(int xp, int yp, int wp, int hp, int dx, int dy);

		/**
		 * \brief
		 *
		 */
		virtual void FillRoundRectangle(int xp, int yp, int wp, int hp, int dx, int dy);

		/**
		 * \brief
		 *
		 */
		virtual void DrawRoundRectangle(int xp, int yp, int wp, int hp, int dx, int dy);

		/**
		 * \brief
		 *
		 */
		virtual void FillCircle(int xcp, int ycp, int rp);

		/**
		 * \brief
		 *
		 */
		virtual void DrawCircle(int xcp, int ycp, int rp);

		/**
		 * \brief
		 *
		 */
		virtual void FillEllipse(int xcp, int ycp, int rxp, int ryp);

		/**
		 * \brief
		 *
		 */
		virtual void DrawEllipse(int xcp, int ycp, int rxp, int ryp);

		/**
		 * \brief
		 *
		 */
		virtual void FillChord(int xcp, int ycp, int rxp, int ryp, double arc0, double arc1);

		/**
		 * \brief
		 *
		 */
		virtual void DrawChord(int xcp, int ycp, int rxp, int ryp, double arc0, double arc1);

		/**
		 * \brief
		 *
		 */
		virtual void FillArc(int xcp, int ycp, int rxp, int ryp, double arc0, double arc1);

		/**
		 * \brief
		 *
		 */
		virtual void DrawArc(int xcp, int ycp, int rxp, int ryp, double arc0, double arc1);

		/**
		 * \brief
		 *
		 */
		virtual void FillPie(int xcp, int ycp, int rxp, int ryp, double arc0, double arc1);

		/**
		 * \brief
		 *
		 */
		virtual void DrawPie(int xcp, int ycp, int rxp, int ryp, double arc0, double arc1);

		/**
		 * \brief
		 *
		 */
		virtual void FillTriangle(int x1p, int y1p, int x2p, int y2p, int x3p, int y3p);

		/**
		 * \brief
		 *
		 */
		virtual void DrawTriangle(int x1p, int y1p, int x2p, int y2p, int x3p, int y3p);

		/**
		 * \brief
		 *
		 */
		virtual void DrawPolygon(int xp, int yp, struct lwuit_point_t *lp, int npoints, bool closed);

		/**
		 * \brief
		 *
		 */
		virtual void FillPolygon(int xp, int yp, struct lwuit_point_t *lp, int npoints);

		/**
		 * \brief
		 *
		 */
		virtual void FillRadialGradient(int xp, int yp, int wp, int hp, Color scolor, Color dcolor);

		/**
		 * \brief
		 *
		 */
		virtual void DrawGlyph(int symbol, int xp, int yp);

		/**
		 * \brief
		 *
		 */
		virtual void DrawString(std::string text, int xp, int yp);

		/**
		 * \brief
		 *
		 */
		virtual void DrawString(std::string text, int xp, int yp, int wp, int hp, lwuit_horizontal_align_t halign = LHA_CENTER, lwuit_vertical_align_t valign = LVA_CENTER);

		/**
		 * \brief
		 *
		 */
		virtual bool DrawImage(std::string img, int xp, int yp);

		/**
		 * \brief
		 *
		 */
		virtual bool DrawImage(std::string img, int xp, int yp, int wp, int hp);

		/**
		 * \brief
		 *
		 */
		virtual bool DrawImage(std::string img, int sxp, int syp, int swp, int shp, int xp, int yp);

		/**
		 * \brief
		 *
		 */
		virtual bool DrawImage(std::string img, int sxp, int syp, int swp, int shp, int xp, int yp, int wp, int hp);

		/**
		 * \brief
		 *
		 */
		virtual bool DrawImage(Image *img, int xp, int yp);

		/**
		 * \brief
		 *
		 */
		virtual bool DrawImage(Image *img, int xp, int yp, int wp, int hp);

		/**
		 * \brief
		 *
		 */
		virtual bool DrawImage(Image *img, int sxp, int syp, int swp, int shp, int xp, int yp);

		/**
		 * \brief
		 *
		 */
		virtual bool DrawImage(Image *img, int sxp, int syp, int swp, int shp, int xp, int yp, int wp, int hp);

		/**
		 * \brief
		 *
		 */
		virtual uint32_t GetRGB(int xp, int yp, uint32_t pixel);

		/**
		 * \brief
		 *
		 */
		virtual void GetRGB(uint32_t **rgb, int xp, int yp, int wp, int hp);

		/**
		 * \brief
		 *
		 */
		virtual void SetRGB(uint32_t rgb, int xp, int yp);

		/**
		 * \brief
		 *
		 */
		virtual void SetRGB(uint32_t *rgb, int xp, int yp, int wp, int hp);

};

}

#endif
