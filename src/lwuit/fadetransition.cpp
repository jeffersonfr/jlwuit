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
#include "image.h"

namespace jlwuit {

FadeTransition::FadeTransition()
{
	_alpha = 0xff;
}

FadeTransition::~FadeTransition()
{
}

bool FadeTransition::IsRunning()
{
	return (_alpha > 0);
}

bool FadeTransition::Animate()
{
	_alpha = _alpha - 0x10;

	if (_alpha >= 0) {
		return true;
	}

	return false;
}

void FadeTransition::Start()
{
	_alpha = 0xff;
}

void FadeTransition::Stop()
{
	_alpha = 0x00;
}

void FadeTransition::Paint(Component *cmp, Graphics *g)
{
	Image *buffer = Image::CreateImage(cmp->GetWidth(), cmp->GetHeight());

	cmp->Paint(buffer->GetGraphics());
	
	Image *image = buffer->Blend(_alpha/255.0);

	g->DrawImage(image, cmp->GetX(), cmp->GetY());

	delete image;
	delete buffer;
}

}
