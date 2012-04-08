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
#include "graphics.h"

namespace jlwuit {

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}

void Graphics::Reset()
{
}

void Graphics::Translate(int x, int y)
{
}

struct lwuit_point_t Graphics::Translate()
{
	struct lwuit_point_t t = {0, 0};

	return t;
}

void Graphics::Rotate(double radians)
{
}

double Graphics::Rotate()
{
	return 0.0;
}

void Graphics::ClipRect(int xp, int yp, int wp, int hp)
{
}

void Graphics::SetClip(int xp, int yp, int wp, int hp)
{
}

struct lwuit_region_t Graphics::GetClip()
{
	struct lwuit_region_t t = {0, 0, 0, 0};

	return t;
}

void Graphics::ReleaseClip()
{
}

void Graphics::SetCompositeFlags(lwuit_composite_flags_t t)
{
}

void Graphics::SetDrawingFlags(lwuit_drawing_flags_t t)
{
}

void Graphics::SetBlittingFlags(lwuit_blitting_flags_t t)
{
}

lwuit_composite_flags_t Graphics::GetCompositeFlags()
{
	return LCF_NONE;
}

lwuit_drawing_flags_t Graphics::GetDrawingFlags()
{
	return LDF_NOFX;
}

lwuit_blitting_flags_t Graphics::GetBlittingFlags()
{
	return LBF_NOFX;
}

void Graphics::Clear()
{
}

void Graphics::Clear(int xp, int yp, int wp, int hp)
{
}

void Graphics::Sync()
{
}

Font * Graphics::GetFont()
{
	return NULL;
}

void Graphics::SetFont(Font *font)
{
} 

Color Graphics::GetColor()
{
	return Color(jlwuit::Color::Black);
} 

void Graphics::SetColor(Color color)
{
} 

void Graphics::SetHints(lwuit_hints_t hints)
{
	_hints = hints;
}

lwuit_hints_t Graphics::GetHints()
{
	return _hints;
}

void Graphics::SetPen(lwuit_pen_t pen)
{
	_pen = pen;
}

lwuit_pen_t Graphics::GetPen()
{
	return _pen;
}

void Graphics::DrawLine(int xp, int yp, int xf, int yf)
{
}

void Graphics::FillRectangle(int xp, int yp, int wp, int hp)
{
}

void Graphics::DrawRectangle(int xp, int yp, int wp, int hp)
{
}

void Graphics::FillBevelRectangle(int xp, int yp, int wp, int hp, int dx, int dy)
{
}

void Graphics::DrawBevelRectangle(int xp, int yp, int wp, int hp, int dx, int dy)
{
}

void Graphics::FillRoundRectangle(int xp, int yp, int wp, int hp, int dx, int dy)
{
}

void Graphics::DrawRoundRectangle(int xp, int yp, int wp, int hp, int dx, int dy)
{
}

void Graphics::FillCircle(int xcp, int ycp, int rp)
{
}

void Graphics::DrawCircle(int xcp, int ycp, int rp)
{
}

void Graphics::FillEllipse(int xcp, int ycp, int rxp, int ryp)
{
}

void Graphics::DrawEllipse(int xcp, int ycp, int rxp, int ryp)
{
}

void Graphics::FillChord(int xcp, int ycp, int rxp, int ryp, double arc0, double arc1)
{
}

void Graphics::DrawChord(int xcp, int ycp, int rxp, int ryp, double arc0, double arc1)
{
}

void Graphics::FillArc(int xcp, int ycp, int rxp, int ryp, double arc0, double arc1)
{
}

void Graphics::DrawArc(int xcp, int ycp, int rxp, int ryp, double arc0, double arc1)
{
}

void Graphics::FillPie(int xcp, int ycp, int rxp, int ryp, double arc0, double arc1)
{
}

void Graphics::DrawPie(int xcp, int ycp, int rxp, int ryp, double arc0, double arc1)
{
}

void Graphics::FillTriangle(int x1p, int y1p, int x2p, int y2p, int x3p, int y3p)
{
}

void Graphics::DrawTriangle(int x1p, int y1p, int x2p, int y2p, int x3p, int y3p)
{
}

void Graphics::DrawPolygon(int xp, int yp, struct lwuit_point_t *p, int npoints, bool close)
{
}

void Graphics::FillPolygon(int xp, int yp, struct lwuit_point_t *p, int npoints)
{
}

void Graphics::FillRadialGradient(int xp, int yp, int wp, int hp, Color scolor, Color dcolor)
{
}

void Graphics::DrawGlyph(int symbol, int xp, int yp)
{
}

void Graphics::DrawString(std::string text, int xp, int yp)
{
}

void Graphics::DrawString(std::string text, int xp, int yp, int wp, int hp, lwuit_horizontal_align_t halign, lwuit_vertical_align_t valign)
{
}

bool Graphics::DrawImage(std::string img, int xp, int yp)
{
	return false;
}

bool Graphics::DrawImage(std::string img, int xp, int yp, int wp, int hp)
{
	return false;
}

bool Graphics::DrawImage(std::string img, int sxp, int syp, int swp, int shp, int xp, int yp)
{
	return false;
}

bool Graphics::DrawImage(std::string img, int sxp, int syp, int swp, int shp, int xp, int yp, int wp, int hp)
{
	return false;
}

bool Graphics::DrawImage(Image *img, int xp, int yp)
{
	return false;
}

bool Graphics::DrawImage(Image *img, int xp, int yp, int wp, int hp)
{
	return false;
}

bool Graphics::DrawImage(Image *img, int sxp, int syp, int swp, int shp, int xp, int yp)
{
	return false;
}

bool Graphics::DrawImage(Image *img, int sxp, int syp, int swp, int shp, int xp, int yp, int wp, int hp)
{
	return false;
}

uint32_t Graphics::GetRGB(int xp, int yp, uint32_t pixel)
{
	return 0x00000000;
}

void Graphics::GetRGB(uint32_t **rgb, int xp, int yp, int wp, int hp, int scansize)
{
}

void Graphics::SetRGB(uint32_t argb, int xp, int yp) 
{
}

void Graphics::SetRGB(uint32_t *rgb, int xp, int yp, int wp, int hp, int scanline) 
{
}

}
