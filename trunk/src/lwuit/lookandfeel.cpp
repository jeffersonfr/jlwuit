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
#include "lookandfeel.h"
#include "font.h"

#include <stdio.h>

namespace jlwuit {

LookAndFeel *LookAndFeel::_instance = NULL;
std::map<std::string, struct lwuit_reference_t *> LookAndFeel::_fonts;
std::map<std::string, struct lwuit_reference_t *> LookAndFeel::_images;

LookAndFeel::LookAndFeel()
{
	_type = LST_NORMAL;

	_default_style = new Style();

	// CHANGE:: customize _default_style ...

	LoadFont("small", "resources/fonts/font.ttf", 20);
	LoadFont("medium", "resources/fonts/font.ttf", 24);
	LoadFont("large", "resources/fonts/font.ttf", 36);
	LoadFont("huge", "resources/fonts/font.ttf", 48);
}

LookAndFeel::~LookAndFeel()
{
	delete _default_style;
}

LookAndFeel * LookAndFeel::GetInstance()
{
	if (_instance == NULL) {
		_instance = new LookAndFeel();
	}

	return _instance;
}

void LookAndFeel::LoadImage(std::string resource_id, std::string path, int wp, int hp)
{
	Image *image = Image::CreateImage(path); 

	if (image == NULL) {
		return;
	}

	lwuit_size_t size = image->GetSize();

	if (wp > 0) {
		size.width = wp;
	}
	
	if (hp > 0) {
		size.height = hp;
	}
	
	if (wp > 0 || hp > 0) {
		Image *tmp = image;
		
		image = image->Scale(size.width, size.height);

		delete tmp;
	}

	AddReference(&_images, resource_id, (int *)image);
}

void LookAndFeel::LoadFont(std::string resource_id, std::string name, int size)
{
	AddReference(&_fonts, resource_id, (int *)Font::CreateFont(name, jlwuit::LFA_NORMAL, size));
}

void LookAndFeel::ReleaseImage(std::string resource_id)
{
	RemoveReference(&_images, resource_id);
}

void LookAndFeel::ReleaseFont(std::string resource_id)
{
	RemoveReference(&_fonts, resource_id);
}

int * LookAndFeel::GetReference(std::map<std::string, struct lwuit_reference_t *> *resources, std::string resource_id)
{
	std::map<std::string, struct lwuit_reference_t *>::iterator i = resources->find(resource_id);

	if (i != resources->end()) {
		return i->second->reference;
	}

	return NULL;
}

void LookAndFeel::AddReference(std::map<std::string, struct lwuit_reference_t *> *resources, std::string resource_id, int *reference)
{
	std::map<std::string, struct lwuit_reference_t *>::iterator i = resources->find(resource_id);

	if (i == resources->end()) {
		struct lwuit_reference_t *t = new struct lwuit_reference_t;

		t->reference = reference;
		t->count = 1;

		(*resources)[resource_id] = t;
	} else {
		struct lwuit_reference_t *t = i->second;

		t->count = t->count + 1;
	}
}

void LookAndFeel::RemoveReference(std::map<std::string, struct lwuit_reference_t *> *resources, std::string resource_id)
{
	std::map<std::string, struct lwuit_reference_t *>::iterator i = resources->find(resource_id);

	if (i != resources->end()) {
		struct lwuit_reference_t *t = i->second;

		t->count = t->count - 1;

		if (t->count == 0) {
			resources->erase(i);
			
			delete t->reference;
		}
	}
}

Style * LookAndFeel::GetDefaultStyle()
{
	return _default_style;
}

void LookAndFeel::SetType(lwuit_lookandfeel_status_t type)
{
	_type = type;
}

jlwuit::Color LookAndFeel::GetColor(Style *style, std::string color_id)
{
	std::string prefix;

	if (_type == LST_FOCUS) {
		prefix = "focus.";
	} else if (_type == LST_SELECT) {
		prefix = "selected.";
	} else if (_type == LST_DISABLE) {
		prefix = "disabled.";
	}

	if (style != NULL) {
		return style->GetColor(prefix + color_id);
	}

	return _default_style->GetColor(prefix + color_id);
}
	
void LookAndFeel::DrawBorder(jlwuit::Graphics *g, jlwuit::Style *style, int x, int y, int w, int h, int border_size)
{
	if (w < 0 || h < 0) {
		return;
	}

	g->SetColor(GetColor(style, "border.color"));

	for (int i=0; i<border_size; i++) {
		g->DrawRectangle(x+i, y+i, w-2*i, h-2*i);
	}
}

void LookAndFeel::DrawBox(jlwuit::Graphics *g, jlwuit::Style *style, int x, int y, int w, int h, int border_size)
{
	if (w < 0 || h < 0) {
		return;
	}

	g->SetColor(GetColor(style, "bg.color"));
	g->FillRectangle(x, y, w, h);
	
	DrawBorder(g, style, x, y, w, h, border_size);
}

void LookAndFeel::DrawProgressBar(jlwuit::Graphics *g, jlwuit::Style *style, int value, int x, int y, int w, int h)
{
	if (w < 0 || h < 0) {
		return;
	}

	value = (w*value)/100;

	if (value < 0) {
		value = 0;
	}

	if (value > w) {
		value = w;
	}

	int gap = 4,
			wp = value-2*gap,
			hp = h-2*gap;

	if (wp > 0 && hp > 0) {
		g->SetColor(GetColor(style, "scroll.color"));
		g->FillRectangle(x+gap, y+gap, value-2*gap, h-2*gap);
	}
	
	DrawBorder(g, style, x, y, w, h, 1);
}

int LookAndFeel::TextSize(std::string font_id, std::string text)
{
	jlwuit::Font *font = (jlwuit::Font *)GetReference(&_fonts, font_id);

	if (font == NULL) {
		return 0;
	}

	return font->GetStringWidth(text);
}

void LookAndFeel::DrawText(jlwuit::Graphics *g, jlwuit::Style *style, std::string font_id, std::string text, int x, int y, int w, int h, jlwuit::lwuit_horizontal_align_t halign, jlwuit::lwuit_vertical_align_t valign)
{
	jlwuit::Font *font = (jlwuit::Font *)GetReference(&_fonts, font_id);

	if (font == NULL) {
		return;
	}

	g->SetFont(font);
	g->SetColor(GetColor(style, "fg.color"));
	g->DrawString(font->TruncateString(text, "...", w), x, y, w, h, halign, valign);
}

void LookAndFeel::DrawTextBox(jlwuit::Graphics *g, jlwuit::Style *style, std::string font_id, std::string text, int x, int y, int w, int h, jlwuit::lwuit_horizontal_align_t halign, jlwuit::lwuit_vertical_align_t valign)
{
	lwuit_margin_t margin = _default_style->GetMargin();

	if (style != NULL) {
		margin = style->GetMargin();
	}

	DrawBox(g, style, x, y, w, h);
	DrawText(g, style, font_id, text, x+margin.left, y, w-margin.left-margin.right, h, halign, valign);
}

jlwuit::Font * LookAndFeel::GetFontByID(std::string id)
{
	return (jlwuit::Font *)GetReference(&_fonts, id);
}

jlwuit::Image * LookAndFeel::GetImageByID(std::string id)
{
	return (jlwuit::Image *)GetReference(&_images, id);
}

void LookAndFeel::DrawImage(jlwuit::Graphics *g, std::string image_id, int x, int y)
{
	jlwuit::Image *image = (jlwuit::Image *)GetReference(&_images, image_id);

	if (image == NULL) {
		return;
	}

	jlwuit::lwuit_composite_flags_t t = g->GetCompositeFlags();

	g->SetCompositeFlags(jlwuit::LCF_NONE);
	g->DrawImage(image, x, y);
	g->SetCompositeFlags(t);
}

void LookAndFeel::DrawImage(jlwuit::Graphics *g, std::string image_id, int x, int y, int w, int h)
{
	jlwuit::Image *image = (jlwuit::Image *)GetReference(&_images, image_id);

	if (image == NULL) {
		return;
	}

	jlwuit::lwuit_composite_flags_t t = g->GetCompositeFlags();

	g->SetCompositeFlags(jlwuit::LCF_NONE);
	g->DrawImage(image, x, y, w, h);
	g->SetCompositeFlags(t);
}

void LookAndFeel::DrawImage(jlwuit::Graphics *g, std::string image_id, int sx, int sy, int sw, int sh, int x, int y)
{
	jlwuit::Image *image = (jlwuit::Image *)GetReference(&_images, image_id);

	if (image == NULL) {
		return;
	}

	jlwuit::lwuit_composite_flags_t t = g->GetCompositeFlags();

	g->SetCompositeFlags(jlwuit::LCF_NONE);
	g->DrawImage(image, sx, sy, sw, sh, x, y);
	g->SetCompositeFlags(t);
}

void LookAndFeel::DrawImage(jlwuit::Graphics *g, std::string image_id, int sx, int sy, int sw, int sh, int x, int y, int w, int h)
{
	jlwuit::Image *image = (jlwuit::Image *)GetReference(&_images, image_id);

	if (image == NULL) {
		return;
	}

	jlwuit::lwuit_composite_flags_t t = g->GetCompositeFlags();

	g->SetCompositeFlags(jlwuit::LCF_NONE);
	g->DrawImage(image, sx, sy, sw, sh, x, y, w, h);
	g->SetCompositeFlags(t);
}

}
