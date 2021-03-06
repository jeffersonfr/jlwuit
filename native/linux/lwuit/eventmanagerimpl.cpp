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
#include "eventmanagerimpl.h"

#include <algorithm>
#include <thread>

namespace jlwuit {

EventManagerImpl::EventManagerImpl()
{
	_last_mouse_move = 0LL;
	_last_mouse_location.x = 0LL;
	_last_mouse_location.y = 0LL;
}

EventManagerImpl::~EventManagerImpl()
{
}

lwuit_key_modifiers_t EventManagerImpl::TranslateKeyModifiers(jevent::jkeyevent_modifiers_t modifiers)
{
	lwuit_key_modifiers_t t = LIM_NONE;

	if (modifiers & jevent::JKM_SHIFT) {
		t = LIM_SHIFT;
	} else if (modifiers & jevent::JKM_CONTROL) {
		t = LIM_CONTROL;
	} else if (modifiers & jevent::JKM_ALT) {
		t = LIM_ALT;
	} else if (modifiers & jevent::JKM_ALTGR) {
		t = LIM_ALTGR;
	} else if (modifiers & jevent::JKM_META) {
		t = LIM_META;
	} else if (modifiers & jevent::JKM_SUPER) {
		t = LIM_SUPER;
	} else if (modifiers & jevent::JKM_HYPER) {
		t = LIM_HYPER;
	} else if (modifiers & jevent::JKM_CAPS_LOCK) {
		t = LIM_CAPS_LOCK;
	} else if (modifiers & jevent::JKM_NUM_LOCK) {
		t = LIM_NUM_LOCK;
	} else if (modifiers & jevent::JKM_SCROLL_LOCK) {
		t = LIM_SCROLL_LOCK;
	}

	return t;
}

lwuit_key_symbol_t EventManagerImpl::TranslateKeySymbol(jevent::jkeyevent_symbol_t symbol)
{
	lwuit_key_symbol_t t = LKS_UNKNOWN;

	if (symbol == jevent::JKS_EXIT) {
		t = LKS_EXIT;
	} else if (symbol == jevent::JKS_BACKSPACE) {
		// t = LKS_BACKSPACE;
		t = LKS_BACK;
	} else if (symbol == jevent::JKS_TAB) {
		t = LKS_TAB;
	} else if (symbol == jevent::JKS_ENTER) {
		t = LKS_ENTER;
	} else if (symbol == jevent::JKS_CANCEL) {
		t = LKS_CANCEL;
	} else if (symbol == jevent::JKS_ESCAPE) {
		// t = LKS_ESCAPE;
		t = LKS_EXIT;
	} else if (symbol == jevent::JKS_SPACE) {
		t = LKS_SPACE;
	} else if (symbol == jevent::JKS_EXCLAMATION_MARK) {
		t = LKS_EXCLAMATION_MARK;
	} else if (symbol == jevent::JKS_QUOTATION) {
		t = LKS_QUOTATION;
	} else if (symbol == jevent::JKS_NUMBER_SIGN) {
		t = LKS_NUMBER_SIGN;
	} else if (symbol == jevent::JKS_DOLLAR_SIGN) {
		t = LKS_DOLLAR_SIGN;
	} else if (symbol == jevent::JKS_PERCENT_SIGN) {
		t = LKS_PERCENT_SIGN;
	} else if (symbol == jevent::JKS_AMPERSAND) {
		t = LKS_AMPERSAND;
	} else if (symbol == jevent::JKS_APOSTROPHE) {
		t = LKS_APOSTROPHE;
	} else if (symbol == jevent::JKS_PARENTHESIS_LEFT) {
		t = LKS_PARENTHESIS_LEFT;
	} else if (symbol == jevent::JKS_PARENTHESIS_RIGHT) {
		t = LKS_PARENTHESIS_RIGHT;
	} else if (symbol == jevent::JKS_STAR) {
		t = LKS_STAR;
	} else if (symbol == jevent::JKS_SHARP) {
		t = LKS_SHARP;
	} else if (symbol == jevent::JKS_PLUS_SIGN) {
		t = LKS_PLUS_SIGN;
	} else if (symbol == jevent::JKS_COMMA) {
		t = LKS_COMMA;
	} else if (symbol == jevent::JKS_MINUS_SIGN) {
		t = LKS_MINUS_SIGN;
	} else if (symbol == jevent::JKS_PERIOD) {
		t = LKS_PERIOD;
	} else if (symbol == jevent::JKS_SLASH) {
		t = LKS_SLASH;
	} else if (symbol == jevent::JKS_0) {
		t = LKS_0;
	} else if (symbol == jevent::JKS_1) {
		t = LKS_1;
	} else if (symbol == jevent::JKS_2) {
		t = LKS_2;
	} else if (symbol == jevent::JKS_3) {
		t = LKS_3;
	} else if (symbol == jevent::JKS_4) {
		t = LKS_4;
	} else if (symbol == jevent::JKS_5) {
		t = LKS_5;
	} else if (symbol == jevent::JKS_6) {
		t = LKS_6;
	} else if (symbol == jevent::JKS_7) {
		t = LKS_7;
	} else if (symbol == jevent::JKS_8) {
		t = LKS_8;
	} else if (symbol == jevent::JKS_9) {
		t = LKS_9;
	} else if (symbol == jevent::JKS_COLON) {
		t = LKS_COLON;
	} else if (symbol == jevent::JKS_SEMICOLON) {
		t = LKS_SEMICOLON;
	} else if (symbol == jevent::JKS_LESS_THAN_SIGN) {
		t = LKS_LESS_THAN_SIGN;
	} else if (symbol == jevent::JKS_EQUALS_SIGN) {
		t = LKS_EQUALS_SIGN;
	} else if (symbol == jevent::JKS_GREATER_THAN_SIGN) {
		t = LKS_GREATER_THAN_SIGN;
	} else if (symbol == jevent::JKS_QUESTION_MARK) {
		t = LKS_QUESTION_MARK;
	} else if (symbol == jevent::JKS_AT) {
		t = LKS_AT;
	} else if (symbol == jevent::JKS_A) {
		t = LKS_A;
	} else if (symbol == jevent::JKS_B) {
		t = LKS_B;
	} else if (symbol == jevent::JKS_C) {
		// t = LKS_C;
		t = LKS_CHANNEL_UP;
	} else if (symbol == jevent::JKS_D) {
		t = LKS_D;
	} else if (symbol == jevent::JKS_E) {
		// t = LKS_E;
		t = LKS_GUIDE;
	} else if (symbol == jevent::JKS_F) {
		t = LKS_F;
	} else if (symbol == jevent::JKS_G) {
		t = LKS_G;
	} else if (symbol == jevent::JKS_H) {
		t = LKS_H;
	} else if (symbol == jevent::JKS_I) {
		// t = LKS_I;
		t = LKS_INFO;
	} else if (symbol == jevent::JKS_J) {
		t = LKS_J;
	} else if (symbol == jevent::JKS_K) {
		t = LKS_K;
	} else if (symbol == jevent::JKS_L) {
		t = LKS_L;
	} else if (symbol == jevent::JKS_M) {
		// t = LKS_M;
		t = LKS_MENU;
	} else if (symbol == jevent::JKS_N) {
		t = LKS_N;
	} else if (symbol == jevent::JKS_O) {
		t = LKS_O;
	} else if (symbol == jevent::JKS_P) {
		t = LKS_P;
	} else if (symbol == jevent::JKS_Q) {
		t = LKS_Q;
	} else if (symbol == jevent::JKS_R) {
		t = LKS_R;
	} else if (symbol == jevent::JKS_S) {
		t = LKS_S;
	} else if (symbol == jevent::JKS_T) {
		t = LKS_T;
	} else if (symbol == jevent::JKS_U) {
		t = LKS_U;
	} else if (symbol == jevent::JKS_V) {
		// t = LKS_V;
		t = LKS_VOLUME_UP;
	} else if (symbol == jevent::JKS_W) {
		t = LKS_W;
	} else if (symbol == jevent::JKS_X) {
		t = LKS_X;
	} else if (symbol == jevent::JKS_Y) {
		t = LKS_Y;
	} else if (symbol == jevent::JKS_Z) {
		// t = LKS_Z;
		t = LKS_MUTE;
	} else if (symbol == jevent::JKS_a) {
		t = LKS_a;
	} else if (symbol == jevent::JKS_b) {
		t = LKS_b;
	} else if (symbol == jevent::JKS_c) {
		// t = LKS_c;
		t = LKS_CHANNEL_DOWN;
	} else if (symbol == jevent::JKS_d) {
		t = LKS_d;
	} else if (symbol == jevent::JKS_e) {
		// t = LKS_e;
		t = LKS_GUIDE;
	} else if (symbol == jevent::JKS_f) {
		t = LKS_f;
	} else if (symbol == jevent::JKS_g) {
		t = LKS_g;
	} else if (symbol == jevent::JKS_h) {
		t = LKS_h;
	} else if (symbol == jevent::JKS_i) {
		// t = LKS_i;
		t = LKS_INFO;
	} else if (symbol == jevent::JKS_j) {
		t = LKS_j;
	} else if (symbol == jevent::JKS_k) {
		t = LKS_k;
	} else if (symbol == jevent::JKS_l) {
		t = LKS_l;
	} else if (symbol == jevent::JKS_m) {
		// t = LKS_m;
		t = LKS_MENU;
	} else if (symbol == jevent::JKS_n) {
		t = LKS_n;
	} else if (symbol == jevent::JKS_o) {
		t = LKS_o;
	} else if (symbol == jevent::JKS_p) {
		t = LKS_p;
	} else if (symbol == jevent::JKS_q) {
		t = LKS_q;
	} else if (symbol == jevent::JKS_r) {
		t = LKS_r;
	} else if (symbol == jevent::JKS_s) {
		t = LKS_s;
	} else if (symbol == jevent::JKS_t) {
		t = LKS_t;
	} else if (symbol == jevent::JKS_u) {
		t = LKS_u;
	} else if (symbol == jevent::JKS_v) {
		// t = LKS_v;
		t = LKS_VOLUME_DOWN;
	} else if (symbol == jevent::JKS_w) {
		t = LKS_w;
	} else if (symbol == jevent::JKS_x) {
		t = LKS_x;
	} else if (symbol == jevent::JKS_y) {
		t = LKS_y;
	} else if (symbol == jevent::JKS_z) {
		// t = LKS_z;
		t = LKS_MUTE;
	} else if (symbol == jevent::JKS_SQUARE_BRACKET_LEFT) {
		t = LKS_SQUARE_BRACKET_LEFT;
	} else if (symbol == jevent::JKS_BACKSLASH) {
		t = LKS_BACKSLASH;
	} else if (symbol == jevent::JKS_SQUARE_BRACKET_RIGHT) {
		t = LKS_SQUARE_BRACKET_RIGHT;
	} else if (symbol == jevent::JKS_CIRCUMFLEX_ACCENT) {
		t = LKS_CIRCUMFLEX_ACCENT;
	} else if (symbol == jevent::JKS_UNDERSCORE) {
		t = LKS_UNDERSCORE;
	} else if (symbol == jevent::JKS_GRAVE_ACCENT) {
		t = LKS_GRAVE_ACCENT;
	} else if (symbol == jevent::JKS_CURLY_BRACKET_LEFT) {
		t = LKS_CURLY_BRACKET_LEFT;
	} else if (symbol == jevent::JKS_VERTICAL_BAR) {
		t = LKS_VERTICAL_BAR;
	} else if (symbol == jevent::JKS_CURLY_BRACKET_RIGHT) {
		t = LKS_CURLY_BRACKET_RIGHT;
	} else if (symbol == jevent::JKS_TILDE) {
		t = LKS_TILDE;
	} else if (symbol == jevent::JKS_DELETE) {
		t = LKS_DELETE;
	} else if (symbol == jevent::JKS_INSERT) {
		t = LKS_INSERT;
	} else if (symbol == jevent::JKS_HOME) {
		t = LKS_HOME;
	} else if (symbol == jevent::JKS_END) {
		// t = LKS_END;
		t = LKS_EXIT;
	} else if (symbol == jevent::JKS_PAGE_UP) {
		t = LKS_PAGE_UP;
	} else if (symbol == jevent::JKS_PAGE_DOWN) {
		t = LKS_PAGE_DOWN;
	} else if (symbol == jevent::JKS_PRINT) {
		t = LKS_PRINT;
	} else if (symbol == jevent::JKS_PAUSE) {
		t = LKS_PAUSE;
	} else if (symbol == jevent::JKS_CURSOR_LEFT) {
		t = LKS_CURSOR_LEFT;
	} else if (symbol == jevent::JKS_CURSOR_RIGHT) {
		t = LKS_CURSOR_RIGHT;
	} else if (symbol == jevent::JKS_CURSOR_UP) {
		t = LKS_CURSOR_UP;
	} else if (symbol == jevent::JKS_CURSOR_DOWN) {
		t = LKS_CURSOR_DOWN;
	} else if (symbol == jevent::JKS_CURSOR_LEFT_UP) {
		t = LKS_CURSOR_LEFT_UP;
	} else if (symbol == jevent::JKS_CURSOR_LEFT_DOWN) {
		t = LKS_CURSOR_LEFT_DOWN;
	} else if (symbol == jevent::JKS_CURSOR_UP_RIGHT) {
		t = LKS_CURSOR_UP_RIGHT;
	} else if (symbol == jevent::JKS_CURSOR_DOWN_RIGHT) {
		t = LKS_CURSOR_DOWN_RIGHT;
	} else if (symbol == jevent::JKS_RED) {
		t = LKS_RED;
	} else if (symbol == jevent::JKS_GREEN) {
		t = LKS_GREEN;
	} else if (symbol == jevent::JKS_YELLOW) {
		t = LKS_YELLOW;
	} else if (symbol == jevent::JKS_BLUE) {
		t = LKS_BLUE;
	} else if (symbol == jevent::JKS_F1) {
		// t = LKS_F1;
		t = LKS_RED;
	} else if (symbol == jevent::JKS_F2) {
		// t = LKS_F2;
		t = LKS_GREEN;
	} else if (symbol == jevent::JKS_F3) {
		// t = LKS_F3;
		t = LKS_YELLOW;
	} else if (symbol == jevent::JKS_F4) {
		// t = LKS_F4;
		t = LKS_BLUE;
	} else if (symbol == jevent::JKS_F5) {
		t = LKS_F5;
	} else if (symbol == jevent::JKS_F6) {
		t = LKS_F6;
	} else if (symbol == jevent::JKS_F7) {
		t = LKS_F7;
	} else if (symbol == jevent::JKS_F8) {
		t = LKS_F8;
	} else if (symbol == jevent::JKS_F9) {
		t = LKS_F9;
	} else if (symbol == jevent::JKS_F10) {
		t = LKS_F10;
	} else if (symbol == jevent::JKS_F11) {
		t = LKS_F11;
	} else if (symbol == jevent::JKS_F12) {
		t = LKS_F12;
	} else if (symbol == jevent::JKS_SHIFT) {
		t = LKS_SHIFT;
	} else if (symbol == jevent::JKS_CONTROL) {
		t = LKS_CONTROL;
	} else if (symbol == jevent::JKS_ALT) {
		t = LKS_ALT;
	} else if (symbol == jevent::JKS_ALTGR) {
		t = LKS_ALTGR;
	} else if (symbol == jevent::JKS_META) {
		t = LKS_META;
	} else if (symbol == jevent::JKS_SUPER) {
		t = LKS_SUPER;
	} else if (symbol == jevent::JKS_HYPER) {
		t = LKS_HYPER;
	} else if (symbol == jevent::JKS_POWER) {
		t = LKS_POWER;
	} else if (symbol == jevent::JKS_MENU) {
		t = LKS_MENU;
	} else if (symbol == jevent::JKS_FILE) {
		t = LKS_FILE;
	} else if (symbol == jevent::JKS_INFO) {
		t = LKS_INFO;
	} else if (symbol == jevent::JKS_BACK) {
		t = LKS_BACK;
	} else if (symbol == jevent::JKS_GUIDE) {
		t = LKS_GUIDE;
	} else if (symbol == jevent::JKS_CHANNEL_UP) {
		t = LKS_CHANNEL_UP;
	} else if (symbol == jevent::JKS_CHANNEL_DOWN) {
		t = LKS_CHANNEL_DOWN;
	} else if (symbol == jevent::JKS_VOLUME_UP) {
		t = LKS_CHANNEL_UP;
	} else if (symbol == jevent::JKS_VOLUME_DOWN) {
		t = LKS_VOLUME_DOWN;
	} else if (symbol == jevent::JKS_PLAY) {
		t = LKS_PLAY;
	} else if (symbol == jevent::JKS_STOP) {
		t = LKS_STOP;
	} else if (symbol == jevent::JKS_EJECT) {
		t = LKS_EJECT;
	} else if (symbol == jevent::JKS_REWIND) {
		t = LKS_REWIND;
	} else if (symbol == jevent::JKS_RECORD) {
		t = LKS_RECORD;
	}

	return t;
}

lwuit_mouse_button_t EventManagerImpl::TranslateMouseButton(jevent::jmouseevent_button_t button)
{
	lwuit_mouse_button_t t = LMB_UNKNOWN;

	if (button & jevent::JMB_BUTTON1) {
		t = (lwuit_mouse_button_t)(t | LMB_BUTTON1);
	} else if (button & jevent::JMB_BUTTON2) {
		t = (lwuit_mouse_button_t)(t | LMB_BUTTON2);
	} else if (button & jevent::JMB_BUTTON3) {
		t = (lwuit_mouse_button_t)(t | LMB_BUTTON3);
	} else if (button & jevent::JMB_WHEEL) {
		t = (lwuit_mouse_button_t)(t | LMB_WHEEL);
	}

	return t;
}

void EventManagerImpl::DispatchUserEvent(UserEvent *event)
{
	if (event == NULL) {
		return;
	}

	int k = 0,
			size = (int)_user_listeners.size();

	while (k++ < (int)_user_listeners.size()) {
		UserEventListener *listener = _user_listeners[k-1];

		if (event->GetType() == LWT_KEY_DOWN) {
			listener->OnKeyDown(event);
		} else if (event->GetType() == LWT_KEY_UP) {
			listener->OnKeyUp(event);
		} else if (event->GetType() == LWT_KEY_PRESS) {
			listener->OnKeyPress(event);
		} else if (event->GetType() == LWT_KEY_LONGPRESS) {
			listener->OnKeyLongPress(event);
		} else if (event->GetType() == LWT_MOUSE_PRESS) {
			listener->OnMousePress(event);
		} else if (event->GetType() == LWT_MOUSE_RELEASE) {
			listener->OnMouseRelease(event);
		} else if (event->GetType() == LWT_MOUSE_MOVE) {
			listener->OnMouseMove(event);
		} else if (event->GetType() == LWT_MOUSE_WHEEL) {
			listener->OnMouseWheel(event);
		} else if (event->GetType() == LWT_MOUSE_CLICK) {
			listener->OnMouseClick(event);
		}

		if (size != (int)_user_listeners.size()) {
			size = (int)_user_listeners.size();

			k--;
		}
	}

	delete event;
}

bool EventManagerImpl::KeyPressed(jevent::KeyEvent *event)
{
	struct event_t *t = _events[TranslateKeySymbol(event->GetSymbol())];

	if ((void *)t == NULL) {
		t = new struct event_t;

		t->key_down = false;
		t->start_time = -1L;
	}

	if (t->key_down == false) {
		_events[TranslateKeySymbol(event->GetSymbol())] = t;

		t->key_down = true;
		t->start_time = time(NULL);

		DispatchUserEvent(new UserEvent(LWT_KEY_DOWN, TranslateKeyModifiers(event->GetModifiers()), event->GetKeyCode(), TranslateKeySymbol(event->GetSymbol())));
	}

	long current_time = time(NULL);

	if ((current_time-t->start_time) >= LONG_PRESS_TIME) {
		t->start_time = time(NULL);

		DispatchUserEvent(new UserEvent(LWT_KEY_LONGPRESS, TranslateKeyModifiers(event->GetModifiers()), event->GetKeyCode(), TranslateKeySymbol(event->GetSymbol())));
	}

	DispatchUserEvent(new UserEvent(LWT_KEY_PRESS, TranslateKeyModifiers(event->GetModifiers()), event->GetKeyCode(), TranslateKeySymbol(event->GetSymbol())));

	return true;
}

bool EventManagerImpl::KeyReleased(jevent::KeyEvent *event)
{
	struct event_t *t = _events[TranslateKeySymbol(event->GetSymbol())];

	if ((void *)t != NULL) {
		t->key_down = false;

		DispatchUserEvent(new UserEvent(LWT_KEY_UP, TranslateKeyModifiers(event->GetModifiers()), event->GetKeyCode(), TranslateKeySymbol(event->GetSymbol())));
	}

	return true;
}

bool EventManagerImpl::MousePressed(jevent::MouseEvent *event)
{
  jgui::jpoint_t location = event->GetLocation();

	DispatchUserEvent(new UserEvent(LWT_MOUSE_PRESS, TranslateMouseButton(event->GetButton()), TranslateMouseButton(event->GetButtons()), event->GetClicks(), location.x, location.y, 0.0, 0.0));

	return true;
}

bool EventManagerImpl::MouseReleased(jevent::MouseEvent *event)
{
  jgui::jpoint_t location = event->GetLocation();

	DispatchUserEvent(new UserEvent(LWT_MOUSE_RELEASE, TranslateMouseButton(event->GetButton()), TranslateMouseButton(event->GetButtons()), event->GetClicks(), location.x, location.y, 0.0, 0.0));

	return true;
}

bool EventManagerImpl::MouseMoved(jevent::MouseEvent *event)
{
  jgui::jpoint_t location = event->GetLocation();
	double 
    tdiff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() - _last_mouse_move,
		mdiff = (tdiff > -10 && tdiff < 10)?10:tdiff,
		vx = (location.x-_last_mouse_location.x)/mdiff,
		vy = (location.y-_last_mouse_location.y)/mdiff;

	DispatchUserEvent(new UserEvent(LWT_MOUSE_MOVE, TranslateMouseButton(event->GetButton()), TranslateMouseButton(event->GetButtons()), event->GetClicks(), location.x, location.y, vx, vy));

	_last_mouse_move = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();

	_last_mouse_location.x = location.x;
	_last_mouse_location.y = location.y;

	return true;
}

bool EventManagerImpl::MouseWheel(jevent::MouseEvent *event)
{
  jgui::jpoint_t location = event->GetLocation();

	DispatchUserEvent(new UserEvent(LWT_MOUSE_WHEEL, TranslateMouseButton(event->GetButton()), TranslateMouseButton(event->GetButtons()), event->GetClicks(), location.x, location.y, 0.0, 0.0));

	return true;
}

}
