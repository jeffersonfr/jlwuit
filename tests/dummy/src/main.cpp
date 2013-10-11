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

#include <stdio.h>
#include <math.h>
#include <unistd.h>

class DummyTest : public jlwuit::Scene {

	public:
		DummyTest():
			jlwuit::Scene(0, 0, 1920, 1080)
		{
			GetStyle()->SetIntegerParam("bg.color", 0x00000000);
		}

		virtual ~DummyTest()
		{
		}

		virtual bool Animate()
		{
			return false;
		}

		virtual bool OnKeyPress(jlwuit::UserEvent *event)
		{
			return false;
		}

};

int main()
{
	jlwuit::Implementation::GetInstance()->Initialize();

	DummyTest app;

	app.Show();

	sleep(100000);

	return 0;
}
