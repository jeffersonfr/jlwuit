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
#include "dialog.h"
#include "implementation.h"
#include "exception.h"

namespace jlwuit {
	
Dialog::Dialog(Scene *scene)
{
	if (scene == NULL) {
		throw Exception("Dialog cannot refer a null scene");
	}

	_scene = scene;
	_timeout = -1;
	
	_scene->RegisterDialog(this);
}

Dialog::~Dialog()
{
	_scene->UnregisterDialog(this);
	
	jthread::TimerTask::Cancel();
}

void Dialog::SetTimeout(int ms)
{
	_timeout = ms;
}

void Dialog::Show()
{
	SetVisible(true);
	
	_scene->Repaint();
	
	_timer.RemoveSchedule(this);

	if (_timeout > 0) {
		_timer.Schedule(this, _timeout*1000LL, true);
	}
}

void Dialog::Hide()
{
	_timer.RemoveSchedule(this);

	SetVisible(false);
	
	_scene->Repaint();
}

void Dialog::Run() 
{
	Hide();
}

}
