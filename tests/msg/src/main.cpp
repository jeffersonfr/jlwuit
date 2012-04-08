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

	public:
		MessageTest():
			jlwuit::Scene(0, 0, 1920, 1080)
		{
			jlwuit::Toast::Create("info1")
				->SetMessage("Information Test")
				->SetHorizontalAlign(jlwuit::LHA_CENTER)
				->SetVerticalAlign(jlwuit::LVA_CENTER)
				->Show();
		}

		virtual ~MessageTest()
		{
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
