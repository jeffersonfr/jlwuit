/***************************************************************************
 *   Copyright (C) 2010 by Jeff Ferr                                       *
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
#include "screensaver.h"

#include <stdio.h>
#include <unistd.h>

#define TIME_DEFAULT	10000000
#define TIME_STEP			200000

#define LOGO_STEPX		16
#define LOGO_STEPY		16

ScreenSaver::ScreenSaver(jlwuit::Scene *scene, std::string logo):
	jlwuit::Dialog(scene)
{
	jlwuit::lwuit_region_t bounds = scene->GetBounds();

	_is_released = false;
	_is_freeze = false;
	_time = TIME_DEFAULT;

	_logo_x = random()%bounds.width/2;
	_logo_y = random()%bounds.height/2;

	_logo_dx = 1;
	_logo_dy = 1;

	SetBounds(bounds.x, bounds.y, bounds.width, bounds.height);
	
	jlwuit::LookAndFeel::LoadImage("logo", logo);
}

ScreenSaver::~ScreenSaver()
{
	jlwuit::LookAndFeel::ReleaseImage("logo");
}

void ScreenSaver::Freeze()
{
	_is_freeze = true;
}

void ScreenSaver::Resume()
{
	_time = TIME_DEFAULT;
	_is_freeze = false;
}

void ScreenSaver::Release()
{
	_is_released = true;

	WaitThread();
}

void ScreenSaver::Paint(jlwuit::Graphics *g)
{
	jlwuit::LookAndFeel *laf = jlwuit::LookAndFeel::GetInstance();
	jlwuit::lwuit_region_t bounds = GetBounds();

	jlwuit::Image *logo = laf->GetImageByID("logo");
	jlwuit::lwuit_size_t size = logo->GetSize();

	g->SetColor(jlwuit::Color::Black);
	g->FillRectangle(0, 0, GetWidth(), GetHeight());

	_logo_x = _logo_x + _logo_dx*LOGO_STEPX;
	_logo_y = _logo_y + _logo_dy*LOGO_STEPY;

	if (_logo_x < 0) {
		_logo_x = 0;
		_logo_dx = 1;
	}

	if ((_logo_x+size.width) > bounds.width) {
		_logo_x = bounds.width-size.width;
		_logo_dx = -1;
	}

	if (_logo_y < 0) {
		_logo_y = 0;
		_logo_dy = 1;
	}

	if ((_logo_y+size.height) > bounds.height) {
		_logo_y = bounds.height-size.height;
		_logo_dy = -1;
	}

	laf->DrawImage(g, "logo", _logo_x, _logo_y);
}

void ScreenSaver::Run()
{
	while (_is_released == false) {
		if (_is_freeze == false) {
			_time = _time - TIME_STEP;
		}

		usleep(TIME_STEP);

		if (_time < 0) {
			Show();
		} else {
			Hide();
		}
	}
}

