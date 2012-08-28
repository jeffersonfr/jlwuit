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

#include "jinputmanager.h"
#include "jdate.h"

#include <algorithm>

namespace jlwuit {

EventManagerImpl::EventManagerImpl()
{
	_last_mouse_move = 0LL;
	_last_mouse_location.x = 0LL;
	_last_mouse_location.y = 0LL;

	jgui::InputManager::GetInstance()->RegisterKeyListener(this);
	jgui::InputManager::GetInstance()->RegisterMouseListener(this);
}

EventManagerImpl::~EventManagerImpl()
{
	jgui::InputManager::GetInstance()->RemoveKeyListener(this);
	jgui::InputManager::GetInstance()->RemoveMouseListener(this);
}

lwuit_key_modifiers_t EventManagerImpl::TranslateKeyModifiers(jgui::jkeyevent_modifiers_t modifiers)
{
	lwuit_key_modifiers_t t = LIM_NONE;

	if (modifiers & jgui::JKM_SHIFT) {
		t = LIM_SHIFT;
	} else if (modifiers & jgui::JKM_CONTROL) {
		t = LIM_CONTROL;
	} else if (modifiers & jgui::JKM_ALT) {
		t = LIM_ALT;
	} else if (modifiers & jgui::JKM_ALTGR) {
		t = LIM_ALTGR;
	} else if (modifiers & jgui::JKM_META) {
		t = LIM_META;
	} else if (modifiers & jgui::JKM_SUPER) {
		t = LIM_SUPER;
	} else if (modifiers & jgui::JKM_HYPER) {
		t = LIM_HYPER;
	} else if (modifiers & jgui::JKM_CAPS_LOCK) {
		t = LIM_CAPS_LOCK;
	} else if (modifiers & jgui::JKM_NUM_LOCK) {
		t = LIM_NUM_LOCK;
	} else if (modifiers & jgui::JKM_SCROLL_LOCK) {
		t = LIM_SCROLL_LOCK;
	}

	return t;
}

lwuit_key_symbol_t EventManagerImpl::TranslateKeySymbol(jgui::jkeyevent_symbol_t symbol)
{
	lwuit_key_symbol_t t = LKS_UNKNOWN;

	if (symbol == jgui::JKS_EXIT) {
		t = LKS_EXIT;
	} else if (symbol == jgui::JKS_BACKSPACE) {
		// t = LKS_BACKSPACE;
		t = LKS_BACK;
	} else if (symbol == jgui::JKS_TAB) {
		t = LKS_TAB;
	} else if (symbol == jgui::JKS_ENTER) {
		t = LKS_ENTER;
	} else if (symbol == jgui::JKS_CANCEL) {
		t = LKS_CANCEL;
	} else if (symbol == jgui::JKS_ESCAPE) {
		// t = LKS_ESCAPE;
		t = LKS_EXIT;
	} else if (symbol == jgui::JKS_SPACE) {
		t = LKS_SPACE;
	} else if (symbol == jgui::JKS_EXCLAMATION_MARK) {
		t = LKS_EXCLAMATION_MARK;
	} else if (symbol == jgui::JKS_QUOTATION) {
		t = LKS_QUOTATION;
	} else if (symbol == jgui::JKS_NUMBER_SIGN) {
		t = LKS_NUMBER_SIGN;
	} else if (symbol == jgui::JKS_DOLLAR_SIGN) {
		t = LKS_DOLLAR_SIGN;
	} else if (symbol == jgui::JKS_PERCENT_SIGN) {
		t = LKS_PERCENT_SIGN;
	} else if (symbol == jgui::JKS_AMPERSAND) {
		t = LKS_AMPERSAND;
	} else if (symbol == jgui::JKS_APOSTROPHE) {
		t = LKS_APOSTROPHE;
	} else if (symbol == jgui::JKS_PARENTHESIS_LEFT) {
		t = LKS_PARENTHESIS_LEFT;
	} else if (symbol == jgui::JKS_PARENTHESIS_RIGHT) {
		t = LKS_PARENTHESIS_RIGHT;
	} else if (symbol == jgui::JKS_STAR) {
		t = LKS_STAR;
	} else if (symbol == jgui::JKS_SHARP) {
		t = LKS_SHARP;
	} else if (symbol == jgui::JKS_PLUS_SIGN) {
		t = LKS_PLUS_SIGN;
	} else if (symbol == jgui::JKS_COMMA) {
		t = LKS_COMMA;
	} else if (symbol == jgui::JKS_MINUS_SIGN) {
		t = LKS_MINUS_SIGN;
	} else if (symbol == jgui::JKS_PERIOD) {
		t = LKS_PERIOD;
	} else if (symbol == jgui::JKS_SLASH) {
		t = LKS_SLASH;
	} else if (symbol == jgui::JKS_0) {
		t = LKS_0;
	} else if (symbol == jgui::JKS_1) {
		t = LKS_1;
	} else if (symbol == jgui::JKS_2) {
		t = LKS_2;
	} else if (symbol == jgui::JKS_3) {
		t = LKS_3;
	} else if (symbol == jgui::JKS_4) {
		t = LKS_4;
	} else if (symbol == jgui::JKS_5) {
		t = LKS_5;
	} else if (symbol == jgui::JKS_6) {
		t = LKS_6;
	} else if (symbol == jgui::JKS_7) {
		t = LKS_7;
	} else if (symbol == jgui::JKS_8) {
		t = LKS_8;
	} else if (symbol == jgui::JKS_9) {
		t = LKS_9;
	} else if (symbol == jgui::JKS_COLON) {
		t = LKS_COLON;
	} else if (symbol == jgui::JKS_SEMICOLON) {
		t = LKS_SEMICOLON;
	} else if (symbol == jgui::JKS_LESS_THAN_SIGN) {
		t = LKS_LESS_THAN_SIGN;
	} else if (symbol == jgui::JKS_EQUALS_SIGN) {
		t = LKS_EQUALS_SIGN;
	} else if (symbol == jgui::JKS_GREATER_THAN_SIGN) {
		t = LKS_GREATER_THAN_SIGN;
	} else if (symbol == jgui::JKS_QUESTION_MARK) {
		t = LKS_QUESTION_MARK;
	} else if (symbol == jgui::JKS_AT) {
		t = LKS_AT;
	} else if (symbol == jgui::JKS_A) {
		t = LKS_A;
	} else if (symbol == jgui::JKS_B) {
		t = LKS_B;
	} else if (symbol == jgui::JKS_C) {
		// t = LKS_C;
		t = LKS_CHANNEL_UP;
	} else if (symbol == jgui::JKS_D) {
		t = LKS_D;
	} else if (symbol == jgui::JKS_E) {
		// t = LKS_E;
		t = LKS_GUIDE;
	} else if (symbol == jgui::JKS_F) {
		t = LKS_F;
	} else if (symbol == jgui::JKS_G) {
		t = LKS_G;
	} else if (symbol == jgui::JKS_H) {
		t = LKS_H;
	} else if (symbol == jgui::JKS_I) {
		// t = LKS_I;
		t = LKS_INFO;
	} else if (symbol == jgui::JKS_J) {
		t = LKS_J;
	} else if (symbol == jgui::JKS_K) {
		t = LKS_K;
	} else if (symbol == jgui::JKS_L) {
		t = LKS_L;
	} else if (symbol == jgui::JKS_M) {
		// t = LKS_M;
		t = LKS_MENU;
	} else if (symbol == jgui::JKS_N) {
		t = LKS_N;
	} else if (symbol == jgui::JKS_O) {
		t = LKS_O;
	} else if (symbol == jgui::JKS_P) {
		t = LKS_P;
	} else if (symbol == jgui::JKS_Q) {
		t = LKS_Q;
	} else if (symbol == jgui::JKS_R) {
		t = LKS_R;
	} else if (symbol == jgui::JKS_S) {
		t = LKS_S;
	} else if (symbol == jgui::JKS_T) {
		t = LKS_T;
	} else if (symbol == jgui::JKS_U) {
		t = LKS_U;
	} else if (symbol == jgui::JKS_V) {
		// t = LKS_V;
		t = LKS_VOLUME_UP;
	} else if (symbol == jgui::JKS_W) {
		t = LKS_W;
	} else if (symbol == jgui::JKS_X) {
		t = LKS_X;
	} else if (symbol == jgui::JKS_Y) {
		t = LKS_Y;
	} else if (symbol == jgui::JKS_Z) {
		// t = LKS_Z;
		t = LKS_MUTE;
	} else if (symbol == jgui::JKS_a) {
		t = LKS_a;
	} else if (symbol == jgui::JKS_b) {
		t = LKS_b;
	} else if (symbol == jgui::JKS_c) {
		// t = LKS_c;
		t = LKS_CHANNEL_DOWN;
	} else if (symbol == jgui::JKS_d) {
		t = LKS_d;
	} else if (symbol == jgui::JKS_e) {
		// t = LKS_e;
		t = LKS_GUIDE;
	} else if (symbol == jgui::JKS_f) {
		t = LKS_f;
	} else if (symbol == jgui::JKS_g) {
		t = LKS_g;
	} else if (symbol == jgui::JKS_h) {
		t = LKS_h;
	} else if (symbol == jgui::JKS_i) {
		// t = LKS_i;
		t = LKS_INFO;
	} else if (symbol == jgui::JKS_j) {
		t = LKS_j;
	} else if (symbol == jgui::JKS_k) {
		t = LKS_k;
	} else if (symbol == jgui::JKS_l) {
		t = LKS_l;
	} else if (symbol == jgui::JKS_m) {
		// t = LKS_m;
		t = LKS_MENU;
	} else if (symbol == jgui::JKS_n) {
		t = LKS_n;
	} else if (symbol == jgui::JKS_o) {
		t = LKS_o;
	} else if (symbol == jgui::JKS_p) {
		t = LKS_p;
	} else if (symbol == jgui::JKS_q) {
		t = LKS_q;
	} else if (symbol == jgui::JKS_r) {
		t = LKS_r;
	} else if (symbol == jgui::JKS_s) {
		t = LKS_s;
	} else if (symbol == jgui::JKS_t) {
		t = LKS_t;
	} else if (symbol == jgui::JKS_u) {
		t = LKS_u;
	} else if (symbol == jgui::JKS_v) {
		// t = LKS_v;
		t = LKS_VOLUME_DOWN;
	} else if (symbol == jgui::JKS_w) {
		t = LKS_w;
	} else if (symbol == jgui::JKS_x) {
		t = LKS_x;
	} else if (symbol == jgui::JKS_y) {
		t = LKS_y;
	} else if (symbol == jgui::JKS_z) {
		// t = LKS_z;
		t = LKS_MUTE;
	} else if (symbol == jgui::JKS_SQUARE_BRACKET_LEFT) {
		t = LKS_SQUARE_BRACKET_LEFT;
	} else if (symbol == jgui::JKS_BACKSLASH) {
		t = LKS_BACKSLASH;
	} else if (symbol == jgui::JKS_SQUARE_BRACKET_RIGHT) {
		t = LKS_SQUARE_BRACKET_RIGHT;
	} else if (symbol == jgui::JKS_CIRCUMFLEX_ACCENT) {
		t = LKS_CIRCUMFLEX_ACCENT;
	} else if (symbol == jgui::JKS_UNDERSCORE) {
		t = LKS_UNDERSCORE;
	} else if (symbol == jgui::JKS_GRAVE_ACCENT) {
		t = LKS_GRAVE_ACCENT;
	} else if (symbol == jgui::JKS_CURLY_BRACKET_LEFT) {
		t = LKS_CURLY_BRACKET_LEFT;
	} else if (symbol == jgui::JKS_VERTICAL_BAR) {
		t = LKS_VERTICAL_BAR;
	} else if (symbol == jgui::JKS_CURLY_BRACKET_RIGHT) {
		t = LKS_CURLY_BRACKET_RIGHT;
	} else if (symbol == jgui::JKS_TILDE) {
		t = LKS_TILDE;
	} else if (symbol == jgui::JKS_DELETE) {
		t = LKS_DELETE;
	} else if (symbol == jgui::JKS_INSERT) {
		t = LKS_INSERT;
	} else if (symbol == jgui::JKS_HOME) {
		t = LKS_HOME;
	} else if (symbol == jgui::JKS_END) {
		// t = LKS_END;
		t = LKS_EXIT;
	} else if (symbol == jgui::JKS_PAGE_UP) {
		t = LKS_PAGE_UP;
	} else if (symbol == jgui::JKS_PAGE_DOWN) {
		t = LKS_PAGE_DOWN;
	} else if (symbol == jgui::JKS_PRINT) {
		t = LKS_PRINT;
	} else if (symbol == jgui::JKS_PAUSE) {
		t = LKS_PAUSE;
	} else if (symbol == jgui::JKS_CURSOR_LEFT) {
		t = LKS_CURSOR_LEFT;
	} else if (symbol == jgui::JKS_CURSOR_RIGHT) {
		t = LKS_CURSOR_RIGHT;
	} else if (symbol == jgui::JKS_CURSOR_UP) {
		t = LKS_CURSOR_UP;
	} else if (symbol == jgui::JKS_CURSOR_DOWN) {
		t = LKS_CURSOR_DOWN;
	} else if (symbol == jgui::JKS_CURSOR_LEFT_UP) {
		t = LKS_CURSOR_LEFT_UP;
	} else if (symbol == jgui::JKS_CURSOR_LEFT_DOWN) {
		t = LKS_CURSOR_LEFT_DOWN;
	} else if (symbol == jgui::JKS_CURSOR_UP_RIGHT) {
		t = LKS_CURSOR_UP_RIGHT;
	} else if (symbol == jgui::JKS_CURSOR_DOWN_RIGHT) {
		t = LKS_CURSOR_DOWN_RIGHT;
	} else if (symbol == jgui::JKS_RED) {
		t = LKS_RED;
	} else if (symbol == jgui::JKS_GREEN) {
		t = LKS_GREEN;
	} else if (symbol == jgui::JKS_YELLOW) {
		t = LKS_YELLOW;
	} else if (symbol == jgui::JKS_BLUE) {
		t = LKS_BLUE;
	} else if (symbol == jgui::JKS_F1) {
		// t = LKS_F1;
		t = LKS_RED;
	} else if (symbol == jgui::JKS_F2) {
		// t = LKS_F2;
		t = LKS_GREEN;
	} else if (symbol == jgui::JKS_F3) {
		// t = LKS_F3;
		t = LKS_YELLOW;
	} else if (symbol == jgui::JKS_F4) {
		// t = LKS_F4;
		t = LKS_BLUE;
	} else if (symbol == jgui::JKS_F5) {
		t = LKS_F5;
	} else if (symbol == jgui::JKS_F6) {
		t = LKS_F6;
	} else if (symbol == jgui::JKS_F7) {
		t = LKS_F7;
	} else if (symbol == jgui::JKS_F8) {
		t = LKS_F8;
	} else if (symbol == jgui::JKS_F9) {
		t = LKS_F9;
	} else if (symbol == jgui::JKS_F10) {
		t = LKS_F10;
	} else if (symbol == jgui::JKS_F11) {
		t = LKS_F11;
	} else if (symbol == jgui::JKS_F12) {
		t = LKS_F12;
	} else if (symbol == jgui::JKS_SHIFT) {
		t = LKS_SHIFT;
	} else if (symbol == jgui::JKS_CONTROL) {
		t = LKS_CONTROL;
	} else if (symbol == jgui::JKS_ALT) {
		t = LKS_ALT;
	} else if (symbol == jgui::JKS_ALTGR) {
		t = LKS_ALTGR;
	} else if (symbol == jgui::JKS_META) {
		t = LKS_META;
	} else if (symbol == jgui::JKS_SUPER) {
		t = LKS_SUPER;
	} else if (symbol == jgui::JKS_HYPER) {
		t = LKS_HYPER;
	} else if (symbol == jgui::JKS_POWER) {
		t = LKS_POWER;
	} else if (symbol == jgui::JKS_MENU) {
		t = LKS_MENU;
	} else if (symbol == jgui::JKS_FILE) {
		t = LKS_FILE;
	} else if (symbol == jgui::JKS_INFO) {
		t = LKS_INFO;
	} else if (symbol == jgui::JKS_BACK) {
		t = LKS_BACK;
	} else if (symbol == jgui::JKS_GUIDE) {
		t = LKS_GUIDE;
	} else if (symbol == jgui::JKS_CHANNEL_UP) {
		t = LKS_CHANNEL_UP;
	} else if (symbol == jgui::JKS_CHANNEL_DOWN) {
		t = LKS_CHANNEL_DOWN;
	} else if (symbol == jgui::JKS_VOLUME_UP) {
		t = LKS_CHANNEL_UP;
	} else if (symbol == jgui::JKS_VOLUME_DOWN) {
		t = LKS_VOLUME_DOWN;
	} else if (symbol == jgui::JKS_PLAY) {
		t = LKS_PLAY;
	} else if (symbol == jgui::JKS_STOP) {
		t = LKS_STOP;
	} else if (symbol == jgui::JKS_EJECT) {
		t = LKS_EJECT;
	} else if (symbol == jgui::JKS_REWIND) {
		t = LKS_REWIND;
	} else if (symbol == jgui::JKS_RECORD) {
		t = LKS_RECORD;
	}

	return t;
}

lwuit_mouse_button_t EventManagerImpl::TranslateMouseButton(jgui::jmouseevent_button_t button)
{
	lwuit_mouse_button_t t = LMB_UNKNOWN;

	if (button & jgui::JMB_BUTTON1) {
		t = (lwuit_mouse_button_t)(t | LMB_BUTTON1);
	} else if (button & jgui::JMB_BUTTON2) {
		t = (lwuit_mouse_button_t)(t | LMB_BUTTON2);
	} else if (button & jgui::JMB_BUTTON3) {
		t = (lwuit_mouse_button_t)(t | LMB_BUTTON3);
	} else if (button & jgui::JMB_WHEEL) {
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

void EventManagerImpl::KeyPressed(jgui::KeyEvent *event)
{
	if (event->GetType() == jgui::JKT_PRESSED) {
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
	} else if (event->GetType() == jgui::JKT_RELEASED) {
		struct event_t *t = _events[TranslateKeySymbol(event->GetSymbol())];

		if ((void *)t != NULL) {
			t->key_down = false;

			DispatchUserEvent(new UserEvent(LWT_KEY_UP, TranslateKeyModifiers(event->GetModifiers()), event->GetKeyCode(), TranslateKeySymbol(event->GetSymbol())));
		}
	}
}

void EventManagerImpl::MousePressed(jgui::MouseEvent *event)
{
	DispatchUserEvent(new UserEvent(LWT_MOUSE_PRESS, TranslateMouseButton(event->GetButton()), TranslateMouseButton(event->GetButtons()), event->GetClickCount(), event->GetX(), event->GetY(), 0.0, 0.0));
}

void EventManagerImpl::MouseReleased(jgui::MouseEvent *event)
{
	DispatchUserEvent(new UserEvent(LWT_MOUSE_RELEASE, TranslateMouseButton(event->GetButton()), TranslateMouseButton(event->GetButtons()), event->GetClickCount(), event->GetX(), event->GetY(), 0.0, 0.0));
}

void EventManagerImpl::MouseMoved(jgui::MouseEvent *event)
{
	double tdiff = (double)(jcommon::Date::CurrentTimeMillis()-_last_mouse_move),
				 mdiff = (tdiff > -10 && tdiff < 10)?10:tdiff,
				 vx = (event->GetX()-_last_mouse_location.x)/mdiff,
				 vy = (event->GetY()-_last_mouse_location.y)/mdiff;

	DispatchUserEvent(new UserEvent(LWT_MOUSE_MOVE, TranslateMouseButton(event->GetButton()), TranslateMouseButton(event->GetButtons()), event->GetClickCount(), event->GetX(), event->GetY(), vx, vy));

	_last_mouse_move = jcommon::Date::CurrentTimeMillis();
	_last_mouse_location.x = event->GetX();
	_last_mouse_location.y = event->GetY();
}

void EventManagerImpl::MouseWheel(jgui::MouseEvent *event)
{
	DispatchUserEvent(new UserEvent(LWT_MOUSE_WHEEL, TranslateMouseButton(event->GetButton()), TranslateMouseButton(event->GetButtons()), event->GetClickCount(), event->GetX(), event->GetY(), 0.0, 0.0));
}

}
