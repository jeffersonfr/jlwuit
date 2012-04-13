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

class MessageTest : public jlwuit::Scene {

	private:
		int _state;

	public:
		MessageTest():
			jlwuit::Scene(0, 0, 1920, 1080)
		{
			_state = -1;

			GetStyle()->SetIntegerParam("bg.color", 0x00000000);
		}

		virtual ~MessageTest()
		{
		}

		virtual bool Animated()
		{
			if (_state == 0) {
				// top
				jlwuit::Toast::Create(this)->SetMessage("Toast:: Top + Left")->SetGravity("top left")->Show();
				jlwuit::Toast::Create(this)->SetMessage("Toast:: Top + HCenter")->SetGravity("top hcenter")->Show();
				jlwuit::Toast::Create(this)->SetMessage("Toast:: Top + Right")->SetGravity("top right")->Show();

				// center
				jlwuit::Toast::Create(this)->SetMessage("Toast:: Left | VCenter")->SetGravity("left vcenter")->Show();
				jlwuit::Toast::Create(this)->SetMessage("Toast:: HCenter + VCenter")->SetGravity("hcenter vcenter")->Show();
				jlwuit::Toast::Create(this)->SetMessage("Toast:: Right + VCenter")->SetGravity("right vcenter")->Show(); 

				// bottom
				jlwuit::Toast::Create(this)->SetMessage("Toast:: Bottom + Left")->SetGravity("bottom left")->Show();
				jlwuit::Toast::Create(this)->SetMessage("Toast:: Bottom + HCenter (default)")->Show(); 
				jlwuit::Toast::Create(this)->SetMessage("Toast:: Bottom + Right")->SetGravity("bottom right")->Show();
			} else if (_state == 5) {
				jlwuit::Toast::Create(this)->SetMessage("Toast:: Top + HFill")->SetGravity("top hfill")->Show();
				jlwuit::Toast::Create(this)->SetMessage("Toast:: Center + HFill")->SetGravity("vcenter hfill")->Show();
				jlwuit::Toast::Create(this)->SetMessage("Toast:: Bottom + HFill")->SetGravity("bottom hfill")->Show();
			} else if (_state == 10) {
				jlwuit::Toast::Create(this)->SetMessage(
					"Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt " \
					"ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco " \
					"laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in " \
					"voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat " \
					"non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
				)->SetGravity("vcenter hfill")->Show();
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
