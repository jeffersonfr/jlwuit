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
#include "toast.h"
#include "device.h"
#include "style.h"
#include "lookandfeel.h"

#include "jcommon/jstringtokenizer.h"

#include <map>

#define GAPX	16
#define GAPY	16

#define TOAST_TIMEOUT	4000

namespace jlwuit {
	
std::map<Component *, std::vector<Toast *> > toasts;

Toast::Toast(Component *cmp):
	Dialog(cmp)
{
	SetTimeout(TOAST_TIMEOUT);

	_font = Font::CreateFont("resources/fonts/font.ttf", jlwuit::LFA_NORMAL, 32);

	_gravity = (lwuit_gravity_t)(LGR_BOTTOM | LGR_HCENTER);
			
	GetStyle()->SetIntegerParam("bg.color", 0x00000000);
}

Toast::~Toast()
{
	delete _font;
	_font = NULL;
}

void Toast::InitRowString(std::vector<std::string> *lines, std::string text, int width)
{
	lines->clear();

	if (width < 0) {
		lines->push_back(text);

		return;
	}

	jcommon::StringTokenizer tokens(text, " ", jcommon::JTT_STRING, false);
	std::string line;

	for (int i=0; i<tokens.GetSize(); i++) {
		std::string temp = line + " " + tokens.GetToken(i);

		if (_font->GetStringWidth(temp) > width) {
			lines->push_back(line);
			
			line = tokens.GetToken(i);

			continue;
		}

		line = temp;
	}

	if (line.empty() == false) {
		lines->push_back(line);
	}
}

void Toast::Release(Component *cmp)
{
	std::map<Component *, std::vector<Toast *> >::iterator i =  toasts.find(cmp);

	if (i != toasts.end()) {
		for (std::vector<Toast *>::iterator j=i->second.begin(); j!=i->second.end(); j++) {
			Toast *toast = (*j);

			delete toast;
		}

		toasts.erase(i);
	}
}

Toast * Toast::Create(Component *cmp)
{
	Toast *toast = new Toast(cmp);

	toasts[cmp].push_back(toast);

	return toast;
}

Toast * Toast::SetMessage(std::string msg)
{
	_message = msg;

	return this;
}

Toast * Toast::SetGravity(lwuit_gravity_t gravity)
{
	_gravity = gravity;

	return this;
}

Toast * Toast::SetGravity(std::string gravity)
{
	jcommon::StringTokenizer tokens(gravity, " ", jcommon::JTT_STRING, false);
	
	_gravity = (lwuit_gravity_t)0;

	for (int i=0; i<tokens.GetSize(); i++) {
		std::string token = tokens.GetToken(i);

		if (strcasecmp(token.c_str(), "start") == 0) {
			_gravity = (lwuit_gravity_t)(_gravity | LGR_START);
		} else if (strcasecmp(token.c_str(), "end") == 0) {
			_gravity = (lwuit_gravity_t)(_gravity | LGR_END);
		} else if (strcasecmp(token.c_str(), "left") == 0) {
			_gravity = (lwuit_gravity_t)(_gravity | LGR_LEFT);
		} else if (strcasecmp(token.c_str(), "right") == 0) {
			_gravity = (lwuit_gravity_t)(_gravity | LGR_RIGHT);
		} else if (strcasecmp(token.c_str(), "top") == 0) {
			_gravity = (lwuit_gravity_t)(_gravity | LGR_TOP);
		} else if (strcasecmp(token.c_str(), "bottom") == 0) {
			_gravity = (lwuit_gravity_t)(_gravity | LGR_BOTTOM);
		} else if (strcasecmp(token.c_str(), "hfill") == 0) {
			_gravity = (lwuit_gravity_t)(_gravity | LGR_HFILL);
		} else if (strcasecmp(token.c_str(), "vfill") == 0) {
			_gravity = (lwuit_gravity_t)(_gravity | LGR_VFILL);
		} else if (strcasecmp(token.c_str(), "hcenter") == 0) {
			_gravity = (lwuit_gravity_t)(_gravity | LGR_HCENTER);
		} else if (strcasecmp(token.c_str(), "vcenter") == 0) {
			_gravity = (lwuit_gravity_t)(_gravity | LGR_VCENTER);
		}
	}

	return this;
}

void Toast::Show()
{
	lwuit_region_t bounds = jlwuit::Device::GetDefaultScreen()->GetLayerByID("graphics")->GetLayerSetup()->GetBounds();
	int w = (bounds.width-2*GAPX),
			h = (bounds.height-2*GAPY);
	
	InitRowString(&_lines, _message, w);
	
	int nlines = _lines.size();

	if (nlines == 0) {
		return;
	}

	if (nlines == 1) {
		int width = _font->GetStringWidth(_lines[0]) + 2*GAPX;

		if (width > w) {
			width = w;
		}

		w = width;
	}

	h = nlines * _font->GetLineSize() + 2*GAPY;

	int x = GAPX,
			y = GAPY;

	if (_gravity & LGR_HFILL) {
			w = bounds.width-2*GAPX;
	}

	if (_gravity & LGR_VFILL) {
		w = (bounds.width-2*GAPX)/2;
		h = bounds.height-2*GAPY;
	
		InitRowString(&_lines, _message, w);
	}

	if (_gravity & LGR_RIGHT) {
		x = bounds.width-w-GAPX;
	}

	if (_gravity & LGR_BOTTOM) {
		y = bounds.height-h-GAPY;
	}

	if (_gravity & LGR_HCENTER) {
		x = (bounds.width-w)/2;
	}

	if (_gravity & LGR_VCENTER) {
		y = (bounds.height-h)/2;
	}
	
	SetBounds(x, y, w, h);

	Dialog::Show();
}

void Toast::Paint(Graphics *g)
{
	lwuit_region_t bounds = GetBounds();
	Style *style = LookAndFeel::GetInstance()->GetDefaultStyle();
	
	g->SetColor(style->GetColor("bg.color"));
	g->FillRectangle(0, 0, bounds.width, bounds.height);
	
	g->SetColor(style->GetColor("border.color"));
	g->DrawRectangle(0, 0, bounds.width, bounds.height);
	
	g->SetFont(_font);
	g->SetColor(style->GetColor("fg.color"));

	for (int i=0; i<(int)_lines.size(); i++) {
		g->DrawString(_lines[i], 0, GAPY+i*_font->GetLineSize(), bounds.width, _font->GetLineSize());
	}
}

}
