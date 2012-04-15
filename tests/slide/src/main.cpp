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

#define GAPX		8
#define GAPY		8

#define IMAGE_SIZE		128

class SlideTest : public jlwuit::Scene {

	private:
		std::vector<std::string> _buttons;
		int _index;

	public:
		SlideTest():
			jlwuit::Scene(0, 0, 1920, 1080)
		{
			_buttons.push_back("chat");
			_buttons.push_back("favorite");
			_buttons.push_back("interactive");
			_buttons.push_back("mms");
			_buttons.push_back("record");
			_buttons.push_back("reload");
			_buttons.push_back("rss");
			_buttons.push_back("share");
			_buttons.push_back("sms");
			_buttons.push_back("star");
			_buttons.push_back("twitter");
			_buttons.push_back("upload");

			for (std::vector<std::string>::iterator i=_buttons.begin(); i!=_buttons.end(); i++) {
				jlwuit::LookAndFeel::LoadImage((*i), "images/" + (*i) + ".png");
			}
		}

		virtual ~SlideTest()
		{
			for (std::vector<std::string>::iterator i=_buttons.begin(); i!=_buttons.end(); i++) {
				jlwuit::LookAndFeel::ReleaseImage((*i));
			}
		}

		virtual bool Animated()
		{
			return true;
		}

		virtual void Paint(jlwuit::Graphics *g)
		{
			// jlwuit::LookAndFeel *laf = jlwuit::LookAndFeel::GetInstance();
			jlwuit::lwuit_region_t bounds = GetBounds();

			for (int i=0; i<(int)_buttons.size(); i++) {
				laf->DrawImage(g, _buttons[i], i*(IMAGE_SIZE+GAPX), 100, IMAGE_SIZE, IMAGE_SIZE);
			}
		}

};

int main()
{
	jlwuit::Implementation::GetInstance()->Initialize();

	SlideTest app;

	app.Show();

	sleep(100000);

	return 0;
}
