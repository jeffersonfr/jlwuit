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
#include "device.h"
#include "exception.h"

namespace jlwuit {
	
Dialog::Dialog(Component *cmp):
	Component()
{
	if (cmp == NULL || dynamic_cast<RootContainer *>(cmp->GetTopLevelAncestor()) == NULL) {
		cmp = RootContainer::GetContainer(Device::GetDefaultScreen()->GetLayerByID("graphics"));
	}

	_root = dynamic_cast<RootContainer *>(cmp->GetTopLevelAncestor());
	_timeout = -1;
	
	_root->RegisterDialog(this);

	_timer.Start();
}

Dialog::~Dialog()
{
	jthread::TimerTask::Cancel();

	_timer.RemoveSchedule(this);
	_timer.Stop();
	
	_root->UnregisterDialog(this);
}

void Dialog::SetTimeout(int ms)
{
	_timeout = ms;
}

void Dialog::Show()
{
	SetVisible(true);
	
	_root->Repaint();
	
	_timer.RemoveSchedule(this);

	if (_timeout > 0) {
		_timer.Schedule(this, _timeout*1000LL, true);
	}
}

void Dialog::Hide()
{
	SetVisible(false);
	
	_root->Repaint();
}

void Dialog::Run() 
{
	Hide();
}

}
