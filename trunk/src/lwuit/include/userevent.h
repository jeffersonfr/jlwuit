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
#ifndef LWUIT_USEREVENT_H
#define LWUIT_USEREVENT_H

namespace jlwuit {

enum lwuit_userevent_type_t {
	LWT_KEY_DOWN,
	LWT_KEY_UP,
	LWT_KEY_PRESS,
	LWT_KEY_LONGPRESS,
	LWT_MOUSE_PRESS,
	LWT_MOUSE_RELEASE,
	LWT_MOUSE_MOVE,
	LWT_MOUSE_WHEEL,
	LWT_MOUSE_CLICK
};

/**
 * \brief
 *
 */
enum lwuit_key_modifiers_t {
	LIM_NONE				= 0x0000,
	LIM_SHIFT				= 0x0001,
	LIM_CONTROL			= 0x0002,
	LIM_ALT					= 0x0004,
	LIM_ALTGR				= 0x0008,
	LIM_META				= 0x0010,
	LIM_SUPER				= 0x0020,
	LIM_HYPER				= 0x0040,
	LIM_CAPS_LOCK		= 0x0080,
	LIM_NUM_LOCK		= 0x0100,
	LIM_SCROLL_LOCK	= 0x0200
};

/**
 * \brief
 *
 */
enum lwuit_key_symbol_t {
  LKS_UNKNOWN,
	LKS_EXIT,
	LKS_BACKSPACE,
	LKS_TAB,
	LKS_ENTER,
	LKS_CANCEL,
	LKS_ESCAPE,
	LKS_SPACE,
	LKS_EXCLAMATION_MARK,
	LKS_QUOTATION,
	LKS_NUMBER_SIGN,
	LKS_DOLLAR_SIGN,
	LKS_PERCENT_SIGN,
	LKS_AMPERSAND,
	LKS_APOSTROPHE,
	LKS_PARENTHESIS_LEFT,
	LKS_PARENTHESIS_RIGHT,
	LKS_STAR,
	LKS_SHARP,
	LKS_PLUS_SIGN,
	LKS_COMMA,
	LKS_MINUS_SIGN,
	LKS_PERIOD,
	LKS_SLASH,
	
	LKS_0,
	LKS_1,
	LKS_2,
	LKS_3,
	LKS_4,
	LKS_5,
	LKS_6,
	LKS_7,
	LKS_8,
	LKS_9,

	LKS_COLON,
	LKS_SEMICOLON,
	LKS_LESS_THAN_SIGN,
	LKS_EQUALS_SIGN,
	LKS_GREATER_THAN_SIGN, 
	LKS_QUESTION_MARK,
	LKS_AT,

	LKS_A,
	LKS_B,
	LKS_C,
	LKS_D,
	LKS_E,
	LKS_F,
	LKS_G,
	LKS_H,
	LKS_I,
	LKS_J,
	LKS_K,
	LKS_L,
	LKS_M, 
	LKS_N,
	LKS_O,
	LKS_P,
	LKS_Q,
	LKS_R,
	LKS_S,
	LKS_T,
	LKS_U,
	LKS_V,
	LKS_W,
	LKS_X,
	LKS_Y,
	LKS_Z,

	LKS_a,
	LKS_b,
	LKS_c,
	LKS_d,
	LKS_e,
	LKS_f,
	LKS_g,
	LKS_h,
	LKS_i,
	LKS_j,
	LKS_k,
	LKS_l,
	LKS_m,
	LKS_n,
	LKS_o,
	LKS_p,
	LKS_q,
	LKS_r,
	LKS_s,
	LKS_t,
	LKS_u,
	LKS_v,
	LKS_w,
	LKS_x,
	LKS_y,
	LKS_z,

	LKS_SQUARE_BRACKET_LEFT,
	LKS_BACKSLASH,
	LKS_SQUARE_BRACKET_RIGHT,
	LKS_CIRCUMFLEX_ACCENT,
	LKS_UNDERSCORE,
	LKS_GRAVE_ACCENT,
	LKS_CURLY_BRACKET_LEFT,
	LKS_VERTICAL_BAR,
	LKS_CURLY_BRACKET_RIGHT,
	LKS_TILDE,

	LKS_DELETE,
	LKS_INSERT,
	LKS_HOME,
	LKS_END,
	LKS_PAGE_UP,
	LKS_PAGE_DOWN,
	LKS_PRINT,
	LKS_PAUSE,

	LKS_CURSOR_LEFT,
	LKS_CURSOR_RIGHT,
	LKS_CURSOR_UP,
	LKS_CURSOR_DOWN,

	LKS_CURSOR_LEFT_UP,
	LKS_CURSOR_LEFT_DOWN,  
	LKS_CURSOR_UP_RIGHT,
	LKS_CURSOR_DOWN_RIGHT,

	LKS_RED,
	LKS_GREEN,
	LKS_YELLOW,
	LKS_BLUE,

	LKS_F1, 
	LKS_F2,
	LKS_F3,
	LKS_F4,
	LKS_F5,
	LKS_F6,
	LKS_F7,
	LKS_F8,
	LKS_F9,
	LKS_F10,
	LKS_F11,
	LKS_F12,

	LKS_SHIFT,
	LKS_CONTROL,
	LKS_ALT,
	LKS_ALTGR,
	LKS_META,
	LKS_SUPER,
	LKS_HYPER,

	LKS_POWER,
	LKS_MENU,
	LKS_FILE,
	LKS_INFO,
	LKS_BACK,
	LKS_GUIDE,
	LKS_MUTE,

	LKS_CHANNEL_UP,
	LKS_CHANNEL_DOWN,

	LKS_VOLUME_UP,
	LKS_VOLUME_DOWN,

	LKS_PLAY,
	LKS_STOP,
	LKS_EJECT,
	LKS_REWIND,
	LKS_RECORD,
};

enum lwuit_mouse_event_t {
	LME_UNKNOWN,
	LME_PRESSED,
	LME_RELEASED,
	LME_MOVED,
	LME_WHEEL
};

/**
 * \brief
 *
 */
enum lwuit_mouse_button_t {
	LMB_UNKNOWN = 0x0,
	LMB_BUTTON1 = 0x1,
	LMB_BUTTON2 = 0x2,
	LMB_BUTTON3 = 0x4,
	LMB_WHEEL 	= 0x08
};

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class UserEvent {

	private:
		double _vx,
			_vy;
		int _code,
			_x,
			_y,
			_click_count;
		lwuit_userevent_type_t _type;
		lwuit_key_symbol_t _symbol;
		lwuit_key_modifiers_t _modifiers;
		lwuit_mouse_button_t _button;

	public:
		/**
		 * \brief
		 *
		 */
		UserEvent(lwuit_userevent_type_t type, lwuit_key_modifiers_t modifiers, int code, lwuit_key_symbol_t symbol);

		/**
		 * \brief
		 *
		 */
		UserEvent(lwuit_userevent_type_t type, lwuit_mouse_button_t button, int click_count, int x, int y, double vx, double vy);

		/**
		 * \brief
		 *
		 */
		virtual ~UserEvent();

		/**
		 * \brief
		 *
		 */
		virtual lwuit_userevent_type_t GetType();

		/**
		 * \brief
		 *
		 */
		virtual int GetKeySymbol();

		/**
		 * \brief
		 *
		 */
		virtual int GetKeyCode();

		/**
		 * \brief
		 *
		 */
		virtual lwuit_key_modifiers_t GetModifiers();

		/**
		 * \brief
		 *
		 */
		virtual lwuit_mouse_button_t GetButton();

		/**
		 * \brief
		 *
		 */
		virtual int GetClickCount();

		/**
		 * \brief
		 *
		 */
		virtual int GetX();

		/**
		 * \brief
		 *
		 */
		virtual int GetY();

		/**
		 * \brief
		 *
		 */
		virtual double GetVelocityX();

		/**
		 * \brief
		 *
		 */
		virtual double GetVelocityY();

};

}

#endif
