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
#include "dialog.h"

#include <stdio.h>
#include <unistd.h>

class Sample : public jlwuit::Dialog {

	public:
		Sample(jlwuit::Scene *scene):
			jlwuit::Dialog(scene)
		{
			SetBounds(100, 100, 320, 240);
		}

		virtual ~Sample()
		{
		}

		virtual void Paint(jlwuit::Graphics *g)
		{
			g->SetColor(jlwuit::Color::Blue);
			g->FillRectangle(0, 0, GetWidth(), GetHeight());
		}
};

class DialogTest : public jlwuit::Scene {

	public:
		DialogTest():
			jlwuit::Scene(0, 0, 1920, 1080)
		{
			GetStyle()->SetIntegerParam("bg.color", 0x00000000);
		}

		virtual ~DialogTest()
		{
		}

		virtual bool Animate()
		{
			jlwuit::Dialog *dlg = new Sample(this);

			dlg->Show();
			sleep(2);
			dlg->Hide();
			sleep(2);

			delete dlg;

			return false;
		}

};

int main()
{
	jlwuit::Implementation::GetInstance()->Initialize();

	DialogTest app;

	app.Show();

	sleep(100000);

	return 0;
}
