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
#ifndef GRAPHICSIMPL_H
#define GRAPHICSIMPL_H

#include "graphics.h"

#include "jgraphics.h"

namespace jlwuit {

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class GraphicsImpl : public Graphics {

	private:
		jgui::Graphics *_native_graphics;
		jlwuit::Font *_font;
		jlwuit::lwuit_composite_flags_t _composite_flags;
		jlwuit::lwuit_drawing_flags_t _drawing_flags;
		jlwuit::lwuit_blitting_flags_t _blitting_flags;

	public:
		/**
		 * \brief
		 *
		 */
		GraphicsImpl(jgui::Graphics *graphics);

		/**
		 * \brief
		 *
		 */
		virtual ~GraphicsImpl();

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
		virtual lwuit_point_t Translate();

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
		virtual lwuit_region_t GetClip();

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
		virtual void SetDrawingFlags(lwuit_drawing_flags_t t);

		/**
		 * \brief
		 *
		 */
		virtual void SetBlittingFlags(lwuit_blitting_flags_t t);

		/**
		 * \brief
		 *
		 */
		virtual lwuit_composite_flags_t GetCompositeFlags();

		/**
		 * \brief
		 *
		 */
		virtual lwuit_drawing_flags_t GetDrawingFlags();

		/**
		 * \brief
		 *
		 */
		virtual lwuit_blitting_flags_t GetBlittingFlags();

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
		virtual jlwuit::Font * GetFont();

		/**
		 * \brief
		 *
		 */
		virtual void SetFont(jlwuit::Font *font);

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
		virtual void DrawPolygon(int xp, int yp, lwuit_point_t *lp, int npoints, bool closed);

		/**
		 * \brief
		 *
		 */
		virtual void FillPolygon(int xp, int yp, lwuit_point_t *lp, int npoints);

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
		virtual void DrawString(std::string text, int xp, int yp, int wp, int hp, lwuit_horizontal_align_t halign, lwuit_vertical_align_t valign);

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
		virtual void GetRGB(uint32_t **rgb, int xp, int yp, int wp, int hp, int scansize);

		/**
		 * \brief
		 *
		 */
		virtual void SetRGB(uint32_t rgb, int xp, int yp); 

		/**
		 * \brief
		 *
		 */
		virtual void SetRGB(uint32_t *rgb, int xp, int yp, int wp, int hp, int scanline); 
};

}

#endif
