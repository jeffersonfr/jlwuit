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
#include "device.h"

#include <stdio.h>
#include <unistd.h>

#define BOX_NUMS 	64
#define BOX_STEP	32
#define BOX_SIZE	540

struct box_t {
	int x;
	int y;
	int dx;
	int dy;
	uint32_t color;
};

class SceneTest : public jlwuit::Scene {

	private:
		std::vector<struct box_t> _boxes;
		int _video_delay;

	public:
		SceneTest():
			jlwuit::Scene(0, 0, 1920, 1080)
		{
			_video_delay = 0;

			jlwuit::lwuit_size_t size = GetSize();

			for (int i=0; i<BOX_NUMS; i++) {
				struct box_t box;

				box.x = random()%(size.width-BOX_SIZE);
				box.y = random()%(size.height-BOX_SIZE);
				box.dx = random()%2;
				box.dy = random()%2;
				box.color = random()%0xffffff;

				box.dx = (box.dx == 0)?-1:1;
				box.dy = (box.dy == 0)?-1:1;
				box.color |= 0x20000000;

				_boxes.push_back(box);
			}
		
			SetAnimationDelay(100);
		}

		virtual ~SceneTest()
		{
		}

		virtual void Paint(jlwuit::Graphics *g)
		{
			for (std::vector<struct box_t>::iterator i=_boxes.begin(); i!=_boxes.end(); i++) {
				struct box_t box = (*i);

				g->SetColor(box.color);
				g->FillRectangle(box.x, box.y, BOX_SIZE, BOX_SIZE);
			}
		}

		virtual bool Animate()
		{
			jlwuit::lwuit_size_t size = GetSize();

			_video_delay = (_video_delay+1)%100;

			if (_video_delay == 0) {
				int x = random()%960,
						y = random()%540;

				jlwuit::Device::GetDefaultScreen()->GetLayerByID("video")->GetLayerSetup()->SetBounds(x, y, 960, 540);
			}

			for (std::vector<struct box_t>::iterator i=_boxes.begin(); i!=_boxes.end(); i++) {
				struct box_t &box = (*i);

				box.x = box.x + box.dx*BOX_STEP;
				box.y = box.y + box.dy*BOX_STEP;

				if (box.x < 0) {
					box.x = 0;
					box.dx = 1;
				}

				if ((box.x+BOX_SIZE) > size.width) {
					box.x = size.width-BOX_SIZE;
					box.dx = -1;
				}

				if (box.y < 0) {
					box.y = 0;
					box.dy = 1;
				}

				if ((box.y+BOX_SIZE) > size.height) {
					box.y = size.height-BOX_SIZE;
					box.dy = -1;
				}
			}

			return true;
		}

};

int main()
{
	jlwuit::Implementation::GetInstance()->Initialize();

	srand(time(NULL));

	SceneTest app;

	app.Show();

	sleep(100000);

	return 0;
}
