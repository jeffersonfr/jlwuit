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
#include "playermanager.h"

#include <stdio.h>

#define BOX_NUMS	4
#define BOX_STEP	32
#define BOX_SIZE	240

struct box_t {
	jlwuit::Player *player;
	int dx;
	int dy;
};

class MediaStart : public jthread::Thread {

	private:
		jlwuit::Player *_player;

	public:
		MediaStart(jlwuit::Player *player)
		{
			_player = player;
		}

		virtual ~MediaStart()
		{
		}

		virtual void Run()
		{
			_player->Play();
		}

};

class SceneTest : public jlwuit::Scene {

	private:
		std::vector<struct box_t *> _boxes;

	public:
		SceneTest():
			jlwuit::Scene(0, 0, 1920, 1080)
		{
			jlwuit::lwuit_size_t size = GetSize();

			for (int i=0; i<BOX_NUMS; i++) {
				jlwuit::Player *player = jlwuit::PlayerManager::CreatePlayer("channels/channel1");
				jlwuit::Component *cmp = player->GetVisualComponent();

				cmp->SetBounds(random()%(size.width-BOX_SIZE), random()%(size.height-BOX_SIZE), BOX_SIZE, BOX_SIZE);

				Add(cmp);

				struct box_t *box = new struct box_t;

				box->player = player;
				box->dx = ((random()%2) == 0)?-1:1;
				box->dy = ((random()%2) == 0)?-1:1;

				_boxes.push_back(box);
			}

			SetAnimationDelay(100);

			GetStyle()->SetIntegerParam("bg.color", 0x00000000);
		}

		virtual ~SceneTest()
		{
			// TODO:: delete boxes
		}

		virtual void StartMedia()
		{
			// INFO:: MediaStart starts all players in parallel
			MediaStart **ms = new MediaStart*[_boxes.size()];
			int k = 0;

			for (std::vector<struct box_t *>::iterator i=_boxes.begin(); i!=_boxes.end(); i++) {
				ms[k++] = new MediaStart((*i)->player);

				ms[k-1]->Start();
			}

			for (int i=0; i<k; i++) {
				ms[i]->WaitThread();

				delete ms[i];
			}

			delete [] ms;
		}

		virtual void StopMedia()
		{
			for (std::vector<struct box_t *>::iterator i=_boxes.begin(); i!=_boxes.end(); i++) {
				(*i)->player->Stop();
				(*i)->player->Close();
			}
		}

		virtual bool Animate()
		{
			jlwuit::lwuit_size_t size = GetSize();

			for (std::vector<struct box_t *>::iterator i=_boxes.begin(); i!=_boxes.end(); i++) {
				struct box_t *box = (*i);
	
				jlwuit::Component *cmp = box->player->GetVisualComponent();
				jlwuit::lwuit_point_t location = cmp->GetLocation();

				location.x = location.x+box->dx*BOX_STEP;
				location.y = location.y+box->dy*BOX_STEP;

				if (location.x < 0) {
					location.x = 0;
					box->dx = 1;
				}

				if ((location.x+BOX_SIZE) > size.width) {
					location.x = size.width-BOX_SIZE;
					box->dx = -1;
				}

				if (cmp->GetY() < 0) {
					location.y = 0;
					box->dy = 1;
				}

				if ((location.y+BOX_SIZE) > size.height) {
					location.y = size.height-BOX_SIZE;
					box->dy = -1;
				}

				cmp->SetLocation(location);
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
	app.StartMedia();

	sleep(100000);

	return 0;
}
