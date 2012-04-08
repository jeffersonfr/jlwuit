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

#include "jgfxhandler.h"

#include <directfb.h>

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
	
	SetCompositeFlags(jlwuit::LCF_NONE);
	SetDrawingFlags(jlwuit::LDF_NOFX);
	SetBlittingFlags(jlwuit::LBF_ALPHACHANNEL);
}

void GraphicsImpl::Translate(int x, int y)
{
	_native_graphics->Translate(x, y);
}

lwuit_point_t GraphicsImpl::Translate()
{
	jgui::jpoint_t jt = _native_graphics->Translate();

	lwuit_point_t lt;

	lt.x = jt.x;
	lt.y = jt.y;

	return lt;
}

void GraphicsImpl::Rotate(double radians)
{
	_native_graphics->Rotate(radians);
}

double GraphicsImpl::Rotate()
{
	return _native_graphics->Rotate();
}

void GraphicsImpl::ClipRect(int xp, int yp, int wp, int hp)
{
	// _native_graphics->ClipRect(xp, yp, wp, hp);
}

void GraphicsImpl::SetClip(int xp, int yp, int wp, int hp)
{
	// _native_graphics->SetClip(xp, yp, wp, hp);
}

lwuit_region_t GraphicsImpl::GetClip()
{
	jgui::jregion_t jt = _native_graphics->GetClip();

	lwuit_region_t lt;

	lt.x = jt.x;
	lt.y = jt.y;
	lt.width = jt.width;
	lt.height = jt.height;

	return lt;
}

void GraphicsImpl::ReleaseClip()
{
	_native_graphics->ReleaseClip();
}

void GraphicsImpl::SetCompositeFlags(lwuit_composite_flags_t t)
{
	_composite_flags = t;

	if (t == LCF_NONE) {
		_native_graphics->SetCompositeFlags(jgui::JCF_NONE);
	} else if (t == LCF_CLEAR) {
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
	} else if (t == LCF_ADD) {
		_native_graphics->SetCompositeFlags(jgui::JCF_ADD);
	} else if (t == LCF_XOR) {
		_native_graphics->SetCompositeFlags(jgui::JCF_XOR);
	}
}

void GraphicsImpl::SetDrawingFlags(lwuit_drawing_flags_t t)
{
	_drawing_flags = t;

	if (t == LDF_NOFX) {
		_native_graphics->SetDrawingFlags(jgui::JDF_NOFX);
	} else if (t == LDF_BLEND) {
		_native_graphics->SetDrawingFlags(jgui::JDF_BLEND);
	} else if (t == LDF_XOR) {
		_native_graphics->SetDrawingFlags(jgui::JDF_XOR);
	}
}

void GraphicsImpl::SetBlittingFlags(lwuit_blitting_flags_t t)
{
	_blitting_flags = t;

	if (t == LBF_NOFX) {
		_native_graphics->SetBlittingFlags(jgui::JBF_NOFX);
	} else if (t == LBF_ALPHACHANNEL) {
		_native_graphics->SetBlittingFlags(jgui::JBF_ALPHACHANNEL);
	} else if (t == LBF_COLORALPHA) {
		_native_graphics->SetBlittingFlags(jgui::JBF_COLORALPHA);
	} else if (t == LBF_COLORIZE) {
		_native_graphics->SetBlittingFlags(jgui::JBF_COLORIZE);
	} else if (t == LBF_XOR) {
		_native_graphics->SetBlittingFlags(jgui::JBF_XOR);
	}
}

lwuit_composite_flags_t GraphicsImpl::GetCompositeFlags()
{
	return _composite_flags;
}

lwuit_drawing_flags_t GraphicsImpl::GetDrawingFlags()
{
	return _drawing_flags;
}

lwuit_blitting_flags_t GraphicsImpl::GetBlittingFlags()
{
	return _blitting_flags;
}

void GraphicsImpl::Clear()
{
	_native_graphics->Clear();
}

void GraphicsImpl::Clear(int xp, int yp, int wp, int hp)
{
	_native_graphics->Clear(xp, yp, wp, hp);
}

void GraphicsImpl::Sync()
{
	IDirectFB *directfb = (IDirectFB *)jgui::GFXHandler::GetInstance()->GetGraphicEngine();
	IDirectFBSurface *surface = (IDirectFBSurface *)_native_graphics->GetNativeSurface();

	directfb->WaitIdle(directfb);

	surface->Flip(surface, NULL, (DFBSurfaceFlipFlags)(DSFLIP_WAITFORSYNC));
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
	return Color(_native_graphics->GetColor().GetARGB());
} 

void GraphicsImpl::SetColor(Color color)
{
	_native_graphics->SetColor(color.GetARGB());
} 

void GraphicsImpl::DrawLine(int xp, int yp, int xf, int yf)
{
	_native_graphics->DrawLine(xp, yp, xf, yf);
}

void GraphicsImpl::FillRectangle(int xp, int yp, int wp, int hp)
{
	_native_graphics->FillRectangle(xp, yp, wp, hp);
}

void GraphicsImpl::DrawRectangle(int xp, int yp, int wp, int hp)
{
	_native_graphics->DrawRectangle(xp, yp, wp, hp);
}

void GraphicsImpl::FillBevelRectangle(int xp, int yp, int wp, int hp, int dx, int dy)
{
	_native_graphics->FillBevelRectangle(xp, yp, wp, hp, dx, dy);
}

void GraphicsImpl::DrawBevelRectangle(int xp, int yp, int wp, int hp, int dx, int dy)
{
	_native_graphics->DrawBevelRectangle(xp, yp, wp, hp, dx, dy);
}

void GraphicsImpl::FillRoundRectangle(int xp, int yp, int wp, int hp, int dx, int dy)
{
	_native_graphics->FillRoundRectangle(xp, yp, wp, hp, dx, dy);
}

void GraphicsImpl::DrawRoundRectangle(int xp, int yp, int wp, int hp, int dx, int dy)
{
	_native_graphics->DrawRoundRectangle(xp, yp, wp, hp, dx, dy);
}

void GraphicsImpl::FillCircle(int xcp, int ycp, int rp)
{
	_native_graphics->FillCircle(xcp, ycp, rp);
}

void GraphicsImpl::DrawCircle(int xcp, int ycp, int rp)
{
	_native_graphics->DrawCircle(xcp, ycp, rp);
}

void GraphicsImpl::FillEllipse(int xcp, int ycp, int rxp, int ryp)
{
	_native_graphics->FillEllipse(xcp, ycp, rxp, ryp);
}

void GraphicsImpl::DrawEllipse(int xcp, int ycp, int rxp, int ryp)
{
	_native_graphics->DrawEllipse(xcp, ycp, rxp, ryp);
}

void GraphicsImpl::FillChord(int xcp, int ycp, int rxp, int ryp, double arc0, double arc1)
{
	_native_graphics->FillChord(xcp, ycp, rxp, ryp, arc0, arc1);
}

void GraphicsImpl::DrawChord(int xcp, int ycp, int rxp, int ryp, double arc0, double arc1)
{
	_native_graphics->DrawChord(xcp, ycp, rxp, ryp, arc0, arc1);
}

void GraphicsImpl::FillArc(int xcp, int ycp, int rxp, int ryp, double arc0, double arc1)
{
	_native_graphics->FillArc(xcp, ycp, rxp, ryp, arc0, arc1);
}

void GraphicsImpl::DrawArc(int xcp, int ycp, int rxp, int ryp, double arc0, double arc1)
{
	_native_graphics->DrawArc(xcp, ycp, rxp, ryp, arc0, arc1);
}

void GraphicsImpl::FillPie(int xcp, int ycp, int rxp, int ryp, double arc0, double arc1)
{
	_native_graphics->FillPie(xcp, ycp, rxp, ryp, arc0, arc1);
}

void GraphicsImpl::DrawPie(int xcp, int ycp, int rxp, int ryp, double arc0, double arc1)
{
	_native_graphics->DrawPie(xcp, ycp, rxp, ryp, arc0, arc1);
}

void GraphicsImpl::FillTriangle(int x1p, int y1p, int x2p, int y2p, int x3p, int y3p)
{
	_native_graphics->FillTriangle(x1p, y1p, x2p, y2p, x3p, y3p);
}

void GraphicsImpl::DrawTriangle(int x1p, int y1p, int x2p, int y2p, int x3p, int y3p)
{
	_native_graphics->DrawTriangle(x1p, y1p, x2p, y2p, x3p, y3p);
}

void GraphicsImpl::DrawPolygon(int xp, int yp, lwuit_point_t *lp, int npoints, bool closed)
{
	jgui::jpoint_t jp[npoints];

	for (int i=0; i<npoints; i++) {
		jp[i].x = lp[i].x;
		jp[i].y = lp[i].y;
	}

	_native_graphics->DrawPolygon(xp, yp, jp, npoints, closed);
}

void GraphicsImpl::FillPolygon(int xp, int yp, lwuit_point_t *lp, int npoints)
{
	jgui::jpoint_t jp[npoints];

	for (int i=0; i<npoints; i++) {
		jp[i].x = lp[i].x;
		jp[i].y = lp[i].y;
	}

	_native_graphics->FillPolygon(xp, yp, jp, npoints);
}

void GraphicsImpl::FillRadialGradient(int xp, int yp, int wp, int hp, Color scolor, Color dcolor)
{
	jgui::Color c1(scolor.GetARGB()),
		c2(dcolor.GetARGB());

	_native_graphics->SetGradientStop(0.0, scolor.GetARGB());
	_native_graphics->SetGradientStop(1.0, dcolor.GetARGB());
	_native_graphics->FillRadialGradient(xp, yp, wp, hp, 0, 0, 0);
	_native_graphics->ResetGradientStop();
}

void GraphicsImpl::DrawGlyph(int symbol, int xp, int yp)
{
	_native_graphics->DrawGlyph(symbol, xp, yp);
}

void GraphicsImpl::DrawString(std::string text, int xp, int yp)
{
	_native_graphics->DrawString(text, xp, yp);
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

	_native_graphics->DrawString(text, xp, yp, wp, hp, a1, a2, false);
}

bool GraphicsImpl::DrawImage(std::string img, int xp, int yp)
{
	return _native_graphics->DrawImage(img, xp, yp);
}

bool GraphicsImpl::DrawImage(std::string img, int xp, int yp, int wp, int hp)
{
	return _native_graphics->DrawImage(img, xp, yp, wp, hp);
}

bool GraphicsImpl::DrawImage(std::string img, int sxp, int syp, int swp, int shp, int xp, int yp)
{
	return _native_graphics->DrawImage(img, sxp, syp, swp, shp, xp, yp);
}

bool GraphicsImpl::DrawImage(std::string img, int sxp, int syp, int swp, int shp, int xp, int yp, int wp, int hp)
{
	return _native_graphics->DrawImage(img, sxp, syp, swp, shp, xp, yp, wp, hp);
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

	return _native_graphics->DrawImage(impl->_native_image, sxp, syp, swp, shp, xp, yp);
}

bool GraphicsImpl::DrawImage(Image *img, int sxp, int syp, int swp, int shp, int xp, int yp, int wp, int hp)
{
	ImageImpl *impl = dynamic_cast<ImageImpl *>(img);

	if (impl == NULL) {
		return false;
	}

	return _native_graphics->DrawImage(impl->_native_image, sxp, syp, swp, shp, xp, yp, wp, hp);
}

uint32_t GraphicsImpl::GetRGB(int xp, int yp, uint32_t pixel)
{
	return _native_graphics->GetRGB(xp, yp, pixel);
}

void GraphicsImpl::GetRGB(uint32_t **rgb, int xp, int yp, int wp, int hp, int scansize)
{
	_native_graphics->GetRGB(rgb, xp, yp, wp, hp, scansize);
}

void GraphicsImpl::SetRGB(uint32_t rgb, int xp, int yp) 
{
	_native_graphics->SetRGB(rgb, xp, yp);
}

void GraphicsImpl::SetRGB(uint32_t *rgb, int xp, int yp, int wp, int hp, int scanline) 
{
	_native_graphics->SetRGB(rgb, xp, yp, wp, hp, scanline);
}

}
