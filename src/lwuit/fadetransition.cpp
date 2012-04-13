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
#include "fadetransition.h"

namespace jlwuit {

FadeTransition::FadeTransition(Component *cmp)
{
	_alpha = 0xff;
	_component = cmp;
}

FadeTransition::~FadeTransition()
{
}

bool FadeTransition::IsRunning()
{
	return (_alpha > 0);
}

bool FadeTransition::Animated()
{
	_alpha = _alpha - 0x10;

	if (_alpha < 0) {
		_alpha = 0;
	}
}

void FadeTransition::Start()
{
	_alpha = 0xff;
}

void FadeTransition::Stop()
{
	_alpha = 0x00;
}

void FadeTransition::Paint(Graphics *g)
{
	Image *buffer = Image::CreateImage(1920, 1080);

	_c1->Paint(buffer->GetGraphics());
	
	g->SetBlittingFlags(jlwuit::LBF_COLORALPHA);
	g->SetColor(Color(0x00, 0x00, 0x00, _alpha));
	g->DrawImage(buffer, _c1->GetX(), _c1->GetY());

	delete buffer;
}

}
