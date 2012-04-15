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
#include "scene.h"
#include "device.h"
#include "eventmanager.h"
#include "implementation.h"
#include "dialog.h"

#include <algorithm>

namespace jlwuit {

Scene::Scene(int x, int y, int width, int height):
	Component(x, y, width, height)
{
	_activity = NULL;

	SetAnimationDelay(1000);
	SetVisible(false);
	
	Implementation::GetInstance()->RegisterScene(this);
}

Scene::~Scene()
{
	Implementation::GetInstance()->UnregisterScene(this);
	
	jthread::TimerTask::Cancel();

	_dialogs.clear();
	
	if (_activity != NULL) {
		delete _activity;
		_activity = NULL;
	}
}

void Scene::Run() 
{
	if (Animated() == true) {
		Repaint();
	}
}

void Scene::StartActivity(Scene *scene)
{
	if (scene == NULL) {
		return;
	}

	Implementation::GetInstance()->GetEventManager()->RemoveUserEventListener(scene);

	if (_activity != NULL) {
		delete _activity;
		_activity = NULL;
	}

	SetVisible(false);

	_activity = scene;
	_activity->Show();
}

void Scene::SendToLayer(std::string layer)
{
}

void Scene::RegisterDialog(Dialog *dialog)
{
	if (dialog == NULL) {
		return;
	}

	jthread::AutoLock lock(&_dialogs_mutex);

	std::vector<Dialog *>::iterator i = std::find(_dialogs.begin(), _dialogs.end(), dialog);

	if (i == _dialogs.end()) {
		_dialogs.push_back(dialog);
	}
}

void Scene::UnregisterDialog(Dialog *dialog)
{
	if (dialog == NULL) {
		return;
	}

	jthread::AutoLock lock(&_dialogs_mutex);

	std::vector<Dialog *>::iterator i = std::find(_dialogs.begin(), _dialogs.end(), dialog);

	if (i != _dialogs.end()) {
		_dialogs.erase(i);
	}
}

void Scene::PaintDialogs(Graphics *g)
{
	jthread::AutoLock lock(&_dialogs_mutex);

	struct lwuit_region_t clip = g->GetClip();

	for (std::vector<Dialog *>::iterator i=_dialogs.begin(); i!=_dialogs.end(); i++) {
		Dialog *c = (*i);

		if (c->IsVisible() == true) {
			int cx = c->GetX()-_scroll.x,
					cy = c->GetY()-_scroll.y,
					cw = c->GetWidth(),
					ch = c->GetHeight();

			if (cx > clip.width) {
				cx = clip.width;
			}

			if (cy > clip.height) {
				cy = clip.height;
			}

			if (cw > (clip.width-cx)) {
				cw = clip.width-cx;
			}

			if (ch > (clip.height-cy)) {
				ch = clip.height-cy;
			}

			if (cw > 0 && ch > 0) {
				g->Translate(cx, cy);
				g->SetClip(0, 0, cw-1, ch-1);
				c->Paint(g);
				g->ReleaseClip();
				g->Translate(-cx, -cy);
			}
		}
	}
}

void Scene::Paint(Graphics *g)
{
	Component::Paint(g);

	PaintDialogs(g);
}

void Scene::SetAnimationDelay(int ms)
{
	jthread::TimerTask::SetDelay(ms*1000LL);
}

int Scene::GetAnimationDelay()
{
	return jthread::TimerTask::GetDelay()/1000LL;
}

void Scene::Show()
{
	SetVisible(true);

	_timer.Schedule(this, (uint64_t)0LL, GetAnimationDelay()*1000LL, true);
}

void Scene::Hide()
{
	jthread::TimerTask::Cancel();
	_timer.RemoveSchedule(this);

	SetVisible(false);
}

std::string Scene::GetState()
{
	return _state;
}

void Scene::SetState(std::string state)
{
	_state = state;
}

bool Scene::OnKeyDown(UserEvent *event)
{
	if (_activity != NULL) {
		if (event->GetKeySymbol() == LKS_BACK) {
			_activity->Hide();

			delete _activity;
			_activity = NULL;

			SetVisible(true);

			return true;
		}
		
		if (_activity->OnKeyDown(event) == true) {
			return true;
		}
		
	}

	return false;
}

bool Scene::OnKeyPress(UserEvent *event)
{
	if (_activity != NULL) {
		if (_activity->OnKeyPress(event) == true) {
			return true;
		}
	}

	return false;
}

bool Scene::OnKeyUp(UserEvent *event)
{
	if (_activity != NULL) {
		if (_activity->OnKeyUp(event) == true) {
			return true;
		}
	}

	return false;
}

bool Scene::OnKeyLongPress(UserEvent *event)
{
	if (_activity != NULL) {
		if (_activity->OnKeyLongPress(event) == true) {
			return true;
		}
	}

	return false;
}

bool Scene::OnMousePress(UserEvent *event)
{
	if (_activity != NULL) {
		if (_activity->OnMousePress(event) == true) {
			return true;
		}
	}

	return false;
}

bool Scene::OnMouseRelease(UserEvent *event)
{
	if (_activity != NULL) {
		if (_activity->OnMouseRelease(event) == true) {
			return true;
		}
	}

	return false;
}

bool Scene::OnMouseClick(UserEvent *event)
{
	if (_activity != NULL) {
		if (_activity->OnMouseClick(event) == true) {
			return true;
		}
	}

	return false;
}

bool Scene::OnMouseMove(UserEvent *event)
{
	if (_activity != NULL) {
		if (_activity->OnMouseMove(event) == true) {
			return true;
		}
	}

	return false;
}

bool Scene::OnMouseWheel(UserEvent *event)
{
	if (_activity != NULL) {
		if (_activity->OnMouseWheel(event) == true) {
			return true;
		}
	}

	return false;
}

}

