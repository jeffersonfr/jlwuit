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
#include "implementation.h"
#include "scene.h"
#include "toast.h"

#include <stdio.h>
#include <unistd.h>

#define _T(x, g) jlwuit::Toast::Create(this)->SetMessage(x)->SetGravity(g)->Show();

class MessageTest : public jlwuit::Scene {

	private:
		int _state;

	public:
		MessageTest():
			jlwuit::Scene(0, 0, 1920, 1080)
		{
			_state = 0;

			GetStyle()->SetIntegerParam("bg.color", 0x00000000);
		}

		virtual ~MessageTest()
		{
		}

		virtual bool Animate()
		{
			if (_state == 0) {
				// top
				_T("Toast:: Top + Left", "top left");
				_T("Toast:: Top + HCenter", "top hcenter");
				_T("Toast:: Top + Right", "top right");

				// center
				_T("Toast:: Left + VCenter", "left vcenter");
				_T("Toast:: HCenter + VCenter", "hcenter vcenter");
				_T("Toast:: Right + VCenter", "right vcenter"); 

				// bottom
				_T("Toast:: Bottom + Left", "bottom left");
				_T("Toast:: Bottom + HCenter (default)", "bottom hcenter"); 
				_T("Toast:: Bottom + Right", "bottom right");
			} else if (_state == 5) {
				_T("Toast:: Top + HFill", "top hfill");
				_T("Toast:: Center + HFill", "vcenter hfill");
				_T("Toast:: Bottom + HFill", "bottom hfill");
			} else if (_state == 10) {
				_T(
					"Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt " \
					"ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco " \
					"laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in " \
					"voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat " \
					"non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.",
					"vcenter hfill");
			} else if (_state == 15) {
				_T(
					"Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt " \
					"ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco " \
					"laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in " \
					"voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat " \
					"non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.", 
				  "left vfill");
			} 

			_state = _state + 1;
			
			return false;
		}
};

int main()
{
	jlwuit::Implementation::GetInstance()->Initialize();

	MessageTest app;

	app.Show();

	sleep(100000);

	return 0;
}
