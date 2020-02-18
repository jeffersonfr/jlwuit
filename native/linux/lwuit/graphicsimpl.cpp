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
#include "graphicsimpl.h"
#include "imageimpl.h"
#include "fontimpl.h"
#include "exception.h"

#include "jgui/jbufferedimage.h"

namespace jlwuit {

GraphicsImpl::GraphicsImpl(jgui::Graphics *graphics)
{
	if (graphics == NULL) {
		throw Exception("GraphicsImpl::Constructor:: Null pointer exception");
	}

	_native_graphics = graphics;

	_font = NULL;
}

GraphicsImpl::~GraphicsImpl()
{
}

void GraphicsImpl::Reset()
{
	_native_graphics->Reset();
	
	SetCompositeFlags(jlwuit::LCF_SRC_OVER);
}

void GraphicsImpl::Translate(int x, int y)
{
	_native_graphics->Translate({x, y});
}

lwuit_point_t GraphicsImpl::Translate()
{
	jgui::jpoint_t<int> jt = _native_graphics->Translate();
	lwuit_point_t lt;

	lt.x = jt.x;
	lt.y = jt.y;

	return lt;
}

void GraphicsImpl::ClipRect(int xp, int yp, int wp, int hp)
{
	_native_graphics->ClipRect({xp, yp, wp, hp});
}

void GraphicsImpl::SetClip(int xp, int yp, int wp, int hp)
{
	_native_graphics->SetClip({xp, yp, wp, hp});
}

lwuit_region_t GraphicsImpl::GetClip()
{
	jgui::jrect_t jt = _native_graphics->GetClip();
	lwuit_region_t lt;

	lt.x = jt.point.x;
	lt.y = jt.point.y;
	lt.width = jt.size.width;
	lt.height = jt.size.height;

	return lt;
}

void GraphicsImpl::ReleaseClip()
{
	_native_graphics->ReleaseClip();
}

void GraphicsImpl::SetCompositeFlags(lwuit_composite_flags_t t)
{
	_composite_flags = t;

	if (t == LCF_CLEAR) {
		_native_graphics->SetCompositeFlags(jgui::JCF_CLEAR);
	} else if (t == LCF_SRC) {
		_native_graphics->SetCompositeFlags(jgui::JCF_SRC);
	} else if (t == LCF_DST) {
		_native_graphics->SetCompositeFlags(jgui::JCF_DST);
	} else if (t == LCF_SRC_OVER) {
		_native_graphics->SetCompositeFlags(jgui::JCF_SRC_OVER);
	} else if (t == LCF_DST_OVER) {
		_native_graphics->SetCompositeFlags(jgui::JCF_DST_OVER);
	} else if (t == LCF_SRC_IN) {
		_native_graphics->SetCompositeFlags(jgui::JCF_SRC_IN);
	} else if (t == LCF_DST_IN) {
		_native_graphics->SetCompositeFlags(jgui::JCF_DST_IN);
	} else if (t == LCF_SRC_OUT) {
		_native_graphics->SetCompositeFlags(jgui::JCF_SRC_OUT);
	} else if (t == LCF_DST_OUT) {
		_native_graphics->SetCompositeFlags(jgui::JCF_DST_OUT);
	} else if (t == LCF_SRC_ATOP) {
		_native_graphics->SetCompositeFlags(jgui::JCF_SRC_ATOP);
	} else if (t == LCF_DST_ATOP) {
		_native_graphics->SetCompositeFlags(jgui::JCF_DST_ATOP);
	} else if (t == LCF_XOR) {
		_native_graphics->SetCompositeFlags(jgui::JCF_XOR);
	}
}

lwuit_composite_flags_t GraphicsImpl::GetCompositeFlags()
{
	return _composite_flags;
}

void GraphicsImpl::Clear()
{
	_native_graphics->Clear();
}

void GraphicsImpl::SetPen(lwuit_pen_t pen)
{
	jgui::jline_join_t join = jgui::JLJ_MITER;;
	jgui::jline_style_t style = jgui::JLS_BUTT;

	if (pen.join == LLJ_BEVEL) {
		join = jgui::JLJ_BEVEL;
	} else if (pen.join == LLJ_ROUND) {
		join = jgui::JLJ_ROUND;
	} else if (pen.join == LLJ_MITER) {
		join = jgui::JLJ_MITER;
	}

	// TODO:: fix
	if (pen.type == LLT_SOLID) {
	} else if (pen.type == LLT_DASH) {
	} else if (pen.type == LLT_DASH_DOT) {
	} else if (pen.type == LLT_DOT) {
	}

	if (pen.style == LLS_ROUND) {
		style = jgui::JLS_ROUND;
	} else if (pen.style == LLS_BUTT) {
		style = jgui::JLS_BUTT;
	} else if (pen.style == LLS_SQUARE) {
		style = jgui::JLS_SQUARE;
	}

	jgui::jpen_t t;

	t.join = join;
	t.style = style;
	t.width = pen.size;
	
	_native_graphics->SetPen(t);
}

lwuit_pen_t GraphicsImpl::GetPen()
{
	jgui::jpen_t t = _native_graphics->GetPen();
	lwuit_pen_t pen;

	if (t.join == jgui::JLJ_BEVEL) {
		pen.join = LLJ_BEVEL;
	} else if (t.join == jgui::JLJ_ROUND) {
		pen.join = LLJ_ROUND;
	} else if (t.join == jgui::JLJ_MITER) {
		pen.join = LLJ_MITER;
	}

	// TODO:: fix
	/*
	if (type == LLS_SOLID) {
	} else if (type== LLS_DASH) {
	} else if (type== LLS_DASH_DOT) {
	} else if (type == LLS_DOT) {
	}
	*/

	if (t.style == jgui::JLS_ROUND) {
		pen.style = LLS_ROUND;
	} else if (t.style == jgui::JLS_BUTT) {
		pen.style = LLS_BUTT;
	} else if (t.style == jgui::JLS_SQUARE) {
		pen.style = LLS_SQUARE;
	}

	pen.size = t.width;

	return pen;
}

void GraphicsImpl::Clear(int xp, int yp, int wp, int hp)
{
	_native_graphics->Clear({xp, yp, wp, hp});
}

void GraphicsImpl::Sync()
{
	// TODO:: _native_graphics->Flip();
}

jlwuit::Font * GraphicsImpl::GetFont()
{
	return _font;
}

void GraphicsImpl::SetFont(jlwuit::Font *font)
{
	_font = font;

	FontImpl *impl = dynamic_cast<FontImpl *>(font);

	if (impl != NULL) {
		_native_graphics->SetFont(impl->_native_font);
	}
} 

Color GraphicsImpl::GetColor()
{
	return Color(uint32_t(_native_graphics->GetColor()));
} 

void GraphicsImpl::SetColor(Color color)
{
	_native_graphics->SetColor(color.GetARGB());
} 

void GraphicsImpl::DrawLine(int xp, int yp, int xf, int yf)
{
	_native_graphics->DrawLine({xp, yp}, {xf, yf});
}

void GraphicsImpl::FillRectangle(int xp, int yp, int wp, int hp)
{
	_native_graphics->FillRectangle({xp, yp, wp, hp});
}

void GraphicsImpl::DrawRectangle(int xp, int yp, int wp, int hp)
{
	_native_graphics->DrawRectangle({xp, yp, wp, hp});
}

void GraphicsImpl::FillBevelRectangle(int xp, int yp, int wp, int hp, int dx, int dy)
{
	_native_graphics->FillBevelRectangle({xp, yp, wp, hp}, dx, dy);
}

void GraphicsImpl::DrawBevelRectangle(int xp, int yp, int wp, int hp, int dx, int dy)
{
	_native_graphics->DrawBevelRectangle({xp, yp, wp, hp}, dx, dy);
}

void GraphicsImpl::FillRoundRectangle(int xp, int yp, int wp, int hp, int dx, int dy)
{
	_native_graphics->FillRoundRectangle({xp, yp, wp, hp}, dx, dy);
}

void GraphicsImpl::DrawRoundRectangle(int xp, int yp, int wp, int hp, int dx, int dy)
{
	_native_graphics->DrawRoundRectangle({xp, yp, wp, hp}, dx, dy);
}

void GraphicsImpl::FillCircle(int xcp, int ycp, int rp)
{
	_native_graphics->FillCircle({xcp, ycp}, rp);
}

void GraphicsImpl::DrawCircle(int xcp, int ycp, int rp)
{
	_native_graphics->DrawCircle({xcp, ycp}, rp);
}

void GraphicsImpl::FillEllipse(int xcp, int ycp, int rxp, int ryp)
{
	_native_graphics->FillEllipse({xcp, ycp}, {rxp, ryp});
}

void GraphicsImpl::DrawEllipse(int xcp, int ycp, int rxp, int ryp)
{
	_native_graphics->DrawEllipse({xcp, ycp}, {rxp, ryp});
}

void GraphicsImpl::FillChord(int xcp, int ycp, int rxp, int ryp, double arc0, double arc1)
{
	_native_graphics->FillChord({xcp, ycp}, {rxp, ryp}, arc0, arc1);
}

void GraphicsImpl::DrawChord(int xcp, int ycp, int rxp, int ryp, double arc0, double arc1)
{
	_native_graphics->DrawChord({xcp, ycp}, {rxp, ryp}, arc0, arc1);
}

void GraphicsImpl::FillArc(int xcp, int ycp, int rxp, int ryp, double arc0, double arc1)
{
	_native_graphics->FillArc({xcp, ycp}, {rxp, ryp}, arc0, arc1);
}

void GraphicsImpl::DrawArc(int xcp, int ycp, int rxp, int ryp, double arc0, double arc1)
{
	_native_graphics->DrawArc({xcp, ycp}, {rxp, ryp}, arc0, arc1);
}

void GraphicsImpl::FillPie(int xcp, int ycp, int rxp, int ryp, double arc0, double arc1)
{
	_native_graphics->FillPie({xcp, ycp}, {rxp, ryp}, arc0, arc1);
}

void GraphicsImpl::DrawPie(int xcp, int ycp, int rxp, int ryp, double arc0, double arc1)
{
	_native_graphics->DrawPie({xcp, ycp}, {rxp, ryp}, arc0, arc1);
}

void GraphicsImpl::FillTriangle(int x1p, int y1p, int x2p, int y2p, int x3p, int y3p)
{
	_native_graphics->FillTriangle({x1p, y1p}, {x2p, y2p}, {x3p, y3p});
}

void GraphicsImpl::DrawTriangle(int x1p, int y1p, int x2p, int y2p, int x3p, int y3p)
{
	_native_graphics->DrawTriangle({x1p, y1p}, {x2p, y2p}, {x3p, y3p});
}

void GraphicsImpl::DrawPolygon(int xp, int yp, lwuit_point_t *lp, int npoints, bool closed)
{
  std::vector<jgui::jpoint_t<int>> jp;

	for (int i=0; i<npoints; i++) {
    jp.emplace_back(jgui::jpoint_t<int>{lp[i].x, lp[i].y});
	}

	_native_graphics->DrawPolygon({xp, yp}, jp, closed);
}

void GraphicsImpl::FillPolygon(int xp, int yp, lwuit_point_t *lp, int npoints)
{
  std::vector<jgui::jpoint_t<int>> jp;

	for (int i=0; i<npoints; i++) {
    jp.emplace_back(jgui::jpoint_t<int>{lp[i].x, lp[i].y});
	}

	_native_graphics->FillPolygon({xp, yp}, jp);
}

void GraphicsImpl::FillRadialGradient(int xp, int yp, int wp, int hp, Color scolor, Color dcolor)
{
	jgui::jcolor_t<float> 
    c1(scolor.GetARGB()),
		c2(dcolor.GetARGB());

	_native_graphics->SetGradientStop(0.0, uint32_t(c1));
	_native_graphics->SetGradientStop(1.0, uint32_t(c2));
	_native_graphics->FillRadialGradient({xp, yp}, {wp, hp}, {0, 0}, 0);
	_native_graphics->ResetGradientStop();
}

void GraphicsImpl::DrawGlyph(int symbol, int xp, int yp)
{
	_native_graphics->DrawGlyph(symbol, {xp, yp});
}

void GraphicsImpl::DrawString(std::string text, int xp, int yp)
{
	_native_graphics->DrawString(text, jgui::jpoint_t<int>{xp, yp});
}

void GraphicsImpl::DrawString(std::string text, int xp, int yp, int wp, int hp, lwuit_horizontal_align_t halign, lwuit_vertical_align_t valign)
{
	jgui::jhorizontal_align_t a1 = jgui::JHA_LEFT;
	jgui::jvertical_align_t a2 = jgui::JVA_TOP;

	if (halign == LHA_CENTER) {
		a1 = jgui::JHA_CENTER;
	} else if (halign == LHA_RIGHT) {
		a1 = jgui::JHA_RIGHT;
	} else if (halign == LHA_JUSTIFY) {
		a1 = jgui::JHA_JUSTIFY;
	}

	if (valign == LVA_CENTER) {
		a2 = jgui::JVA_CENTER;
	} else if (valign == LVA_BOTTOM) {
		a2 = jgui::JVA_BOTTOM;
	} else if (valign == LVA_JUSTIFY) {
		a2 = jgui::JVA_JUSTIFY;
	}

	_native_graphics->DrawString(text, {xp, yp, wp, hp}, a1, a2, false);
}

bool GraphicsImpl::DrawImage(std::string img, int xp, int yp)
{
	jgui::Image *image = new jgui::BufferedImage(img);

	bool b = _native_graphics->DrawImage(image, jgui::jpoint_t<int>{xp, yp});

	delete image;

	return b;
}

bool GraphicsImpl::DrawImage(std::string img, int xp, int yp, int wp, int hp)
{
	jgui::Image *image = new jgui::BufferedImage(img);

	bool b = _native_graphics->DrawImage(image, {xp, yp, wp, hp});

	delete image;

	return b;
}

bool GraphicsImpl::DrawImage(std::string img, int sxp, int syp, int swp, int shp, int xp, int yp)
{
	jgui::Image *image = new jgui::BufferedImage(img);

	bool b = _native_graphics->DrawImage(image, {sxp, syp, swp, shp}, jgui::jpoint_t<int>{xp, yp});

	delete image;

	return b;
}

bool GraphicsImpl::DrawImage(std::string img, int sxp, int syp, int swp, int shp, int xp, int yp, int wp, int hp)
{
	jgui::Image *image = new jgui::BufferedImage(img);

	bool b = _native_graphics->DrawImage(image, {sxp, syp, swp, shp}, {xp, yp, wp, hp});

	delete image;

	return b;
}

bool GraphicsImpl::DrawImage(Image *img, int xp, int yp)
{
	if ((void *)img == NULL) {
		return false;
	}

	struct lwuit_size_t size = img->GetSize();

	return DrawImage(img, 0, 0, size.width, size.height, xp, yp);
}

bool GraphicsImpl::DrawImage(Image *img, int xp, int yp, int wp, int hp)
{
	if ((void *)img == NULL) {
		return false;
	}

	struct lwuit_size_t size = img->GetSize();

	return DrawImage(img, 0, 0, size.width, size.height, xp, yp, wp, hp);
}

bool GraphicsImpl::DrawImage(Image *img, int sxp, int syp, int swp, int shp, int xp, int yp)
{
	ImageImpl *impl = dynamic_cast<ImageImpl *>(img);

	if (impl == NULL) {
		return false;
	}

	return _native_graphics->DrawImage(impl->_native_image, {sxp, syp, swp, shp}, jgui::jpoint_t<int>{xp, yp});
}

bool GraphicsImpl::DrawImage(Image *img, int sxp, int syp, int swp, int shp, int xp, int yp, int wp, int hp)
{
	ImageImpl *impl = dynamic_cast<ImageImpl *>(img);

	if (impl == NULL) {
		return false;
	}

	return _native_graphics->DrawImage(impl->_native_image, {sxp, syp, swp, shp}, {xp, yp, wp, hp});
}

uint32_t GraphicsImpl::GetRGB(int xp, int yp, uint32_t pixel)
{
	return _native_graphics->GetRGB({xp, yp}, pixel);
}

void GraphicsImpl::GetRGB(uint32_t *rgb, int xp, int yp, int wp, int hp)
{
	_native_graphics->GetRGBArray(rgb, {xp, yp, wp, hp});
}

void GraphicsImpl::SetRGB(uint32_t rgb, int xp, int yp) 
{
	_native_graphics->SetRGB(rgb, {xp, yp});
}

void GraphicsImpl::SetRGB(uint32_t *rgb, int xp, int yp, int wp, int hp) 
{
	_native_graphics->SetRGBArray(rgb, {xp, yp, wp, hp});
}

}
