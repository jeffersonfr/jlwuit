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
#include "state.h"
#include "jstringtokenizer.h"
#include "jstringutils.h"

#include <stdio.h>

namespace jlwuit {

State::State()
{
}

State::~State()
{
}

std::string State::GetState()
{
	return _state;
}

void State::SetState(std::string state)
{
	_state = state;
}

bool State::MatchToken(std::string current_state, std::string state)
{
	if (state.find("*") != std::string::npos) { 
		return true;
	} else if (current_state == state) {
		return true;
	}

	return false;
}

bool State::MatchState(std::string state)
{
	jcommon::StringTokenizer tokens1(_state, "."),
		tokens2(state, ".");

	if (tokens1.GetSize() != tokens2.GetSize()) {
		return false;
	}

	for (int i=0; i<tokens1.GetSize(); i++) {
		std::string token1 = jcommon::StringUtils::Trim(tokens1.GetToken(i)),
			token2 = jcommon::StringUtils::Trim(tokens2.GetToken(i));

		if (token2.find("[") != std::string::npos) {
			int i1 = token2.find("["),
				i2 = token2.rfind("]");

			if (i1 != i2) {
				jcommon::StringTokenizer tokens(token2.substr(i1+1, i2-1), ",");

				bool b = false;

				for (int j=0; j<tokens.GetSize(); j++) {
					std::string token = jcommon::StringUtils::Trim(tokens.GetToken(j));

					if (MatchToken(token1, token) == true) {
						b = true;
					}
				}

				if (b == false) {
					return false;
				}
			}
		} else {
			if (MatchToken(token1, token2) == false) {
				return false;
			}
		}
	}

	return true;
}

}

