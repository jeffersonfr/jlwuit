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

#define DISPATCH_KEY_EVENT(method) 			\
	Component *focus = GetFocusOwner();		\
																				\
	if (focus != NULL) {									\
		return focus->method(event);				\
	}																			\

#define DISPATCH_MOUSE_EVENT(method) 																																		\
	jthread::AutoLock lock(&_container_mutex); 																														\
																																																				\
	for (std::vector<Component *>::reverse_iterator i=_components.rbegin(); i!=_components.rend(); i++) {	\
		Component *cmp = (*i);																																							\
																																																				\
		if (cmp->IsVisible() == true && cmp->IsEnabled() == true && cmp->Intersect(event->GetX(), event->GetY())) {	\
			return cmp->method(event);																																				\
		}																																																		\
	}																																																			\

namespace jlwuit {

Scene::Scene(int x, int y, int w, int h):
	Component(x, y, w, h)
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

	jthread::AutoLock lock(&_container_mutex); 																														\

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
	_timer.Schedule(this, (uint64_t)0LL, GetAnimationDelay()*1000LL, true);
	
	SetVisible(true);
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

	DISPATCH_KEY_EVENT(OnKeyDown);

	return false;
}

bool Scene::OnKeyPress(UserEvent *event)
{
	if (_activity != NULL) {
		if (_activity->OnKeyPress(event) == true) {
			return true;
		}
	}

	DISPATCH_KEY_EVENT(OnKeyPress);

	return false;
}

bool Scene::OnKeyUp(UserEvent *event)
{
	if (_activity != NULL) {
		if (_activity->OnKeyUp(event) == true) {
			return true;
		}
	}

	DISPATCH_KEY_EVENT(OnKeyUp);

	return false;
}

bool Scene::OnKeyLongPress(UserEvent *event)
{
	if (_activity != NULL) {
		if (_activity->OnKeyLongPress(event) == true) {
			return true;
		}
	}

	DISPATCH_KEY_EVENT(OnKeyLongPress);

	return false;
}

bool Scene::OnMousePress(UserEvent *event)
{
	if (_activity != NULL) {
		if (_activity->OnMousePress(event) == true) {
			return true;
		}
	}
	
	DISPATCH_MOUSE_EVENT(OnMousePress)

	return false;
}

bool Scene::OnMouseRelease(UserEvent *event)
{
	if (_activity != NULL) {
		if (_activity->OnMouseRelease(event) == true) {
			return true;
		}
	}

	DISPATCH_MOUSE_EVENT(OnMouseRelease)

	return false;
}

bool Scene::OnMouseClick(UserEvent *event)
{
	if (_activity != NULL) {
		if (_activity->OnMouseClick(event) == true) {
			return true;
		}
	}

	DISPATCH_MOUSE_EVENT(OnMouseClick)

	return false;
}

Component *_component = NULL;
bool Scene::OnMouseMove(UserEvent *event)
{
	if (_activity != NULL) {
		if (_activity->OnMouseMove(event) == true) {
			return true;
		}
	}

	jthread::AutoLock lock(&_container_mutex); 																														\

	Component *cmp = NULL;

	for (std::vector<Component *>::reverse_iterator i=_components.rbegin(); i!=_components.rend(); i++) {	
		if ((*i)->Intersect(event->GetX(), event->GetY()) == true) {
			cmp = (*i);

			break;
		}
	}

	if (_component != cmp) {
		if (_component != NULL) {
			_component->OnMouseOut(event);
		}

		if (cmp != NULL) {
			cmp->OnMouseOver(event);
		}

		_component = cmp;
	}
		
	if (cmp != NULL && cmp->IsVisible() == true && cmp->IsEnabled() == true && cmp->Intersect(event->GetX(), event->GetY())) {
		return cmp->OnMouseMove(event);
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

	DISPATCH_MOUSE_EVENT(OnMouseWheel)

	return false;
}

}

