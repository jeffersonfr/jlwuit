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
#include "keyboard.h"

namespace jlwuit {

Keyboard::Keyboard()
{
}

Keyboard::~Keyboard()
{
}

bool Keyboard::IsSupported(lwuit_key_symbol_t symbol)
{
	switch (symbol) {
		case LKS_BACKSPACE:
		case LKS_TAB:
		case LKS_ENTER:
		case LKS_CANCEL:
		case LKS_ESCAPE:
		case LKS_SPACE:
		case LKS_EXCLAMATION_MARK:
		case LKS_QUOTATION:
		case LKS_NUMBER_SIGN:
		case LKS_DOLLAR_SIGN:
		case LKS_PERCENT_SIGN:
		case LKS_AMPERSAND:
		case LKS_APOSTROPHE:
		case LKS_PARENTHESIS_LEFT:
		case LKS_PARENTHESIS_RIGHT:
		case LKS_STAR:
		case LKS_SHARP:
		case LKS_PLUS_SIGN:
		case LKS_COMMA:
		case LKS_MINUS_SIGN:
		case LKS_PERIOD:
		case LKS_SLASH:

		case LKS_0:
		case LKS_1:
		case LKS_2:
		case LKS_3:  
		case LKS_4:
		case LKS_5:
		case LKS_6:
		case LKS_7:
		case LKS_8:
		case LKS_9:

		case LKS_COLON:
		case LKS_SEMICOLON:
		case LKS_LESS_THAN_SIGN:
		case LKS_EQUALS_SIGN:
		case LKS_GREATER_THAN_SIGN:
		case LKS_QUESTION_MARK:
		case LKS_AT:

		case LKS_A:
		case LKS_B:
		case LKS_C:
		case LKS_D:
		case LKS_E:
		case LKS_F:
		case LKS_G:
		case LKS_H:
		case LKS_I:         
		case LKS_J:
		case LKS_K:
		case LKS_L:
		case LKS_M:
		case LKS_N:
		case LKS_O:
		case LKS_P:
		case LKS_Q:
		case LKS_R:
		case LKS_S:
		case LKS_T:
		case LKS_U:
		case LKS_V:
		case LKS_W:
		case LKS_X:           
		case LKS_Y:
		case LKS_Z:

		case LKS_a:      
		case LKS_b:   
		case LKS_c:
		case LKS_d:
		case LKS_e:
		case LKS_f:
		case LKS_g:
		case LKS_h:
		case LKS_i:
		case LKS_j:
		case LKS_k:             
		case LKS_l:
		case LKS_m:
		case LKS_n:
		case LKS_o:
		case LKS_p:
		case LKS_q: 
		case LKS_r:
		case LKS_s:
		case LKS_t:
		case LKS_u:
		case LKS_v:
		case LKS_w:
		case LKS_x:
		case LKS_y:
		case LKS_z:

		case LKS_SQUARE_BRACKET_LEFT:
		case LKS_BACKSLASH:
		case LKS_SQUARE_BRACKET_RIGHT:
		case LKS_CIRCUMFLEX_ACCENT:
		case LKS_UNDERSCORE:
		case LKS_GRAVE_ACCENT:
		case LKS_CURLY_BRACKET_LEFT:
		case LKS_VERTICAL_BAR:
		case LKS_CURLY_BRACKET_RIGHT:
		case LKS_TILDE:

		case LKS_DELETE:
		case LKS_INSERT:
		case LKS_HOME:
		case LKS_END:
		case LKS_PAGE_UP:
		case LKS_PAGE_DOWN:
		case LKS_PRINT:
		case LKS_PAUSE:

		case LKS_CURSOR_LEFT:
		case LKS_CURSOR_RIGHT:
		case LKS_CURSOR_UP:
		case LKS_CURSOR_DOWN:

		case LKS_CURSOR_LEFT_UP:
		case LKS_CURSOR_LEFT_DOWN:  
		case LKS_CURSOR_UP_RIGHT:
		case LKS_CURSOR_DOWN_RIGHT:

		case LKS_F1:
		case LKS_F2:
		case LKS_F3:
		case LKS_F4:
		case LKS_F5:
		case LKS_F6:         
		case LKS_F7:
		case LKS_F8:
		case LKS_F9:
		case LKS_F10:  
		case LKS_F11:
		case LKS_F12:

		case LKS_SHIFT:
		case LKS_CONTROL:
		case LKS_ALT:
		case LKS_ALTGR:
		case LKS_META:
		case LKS_SUPER:
		case LKS_HYPER:
			return true;
		default:
			break;
	};

	return false;
}

}
