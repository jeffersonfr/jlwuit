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

#include "jautolock.h"

#include <stdio.h>
#include <unistd.h>

#define BOX_NUMS	4
#define BOX_STEP	32
#define BOX_SIZE	240

class MediaStart : public jthread::Thread {

	public:
		jlwuit::Player *_player;
		int _dx;
		int _dy;

	public:
		MediaStart(jlwuit::Player *player, int dx, int dy)
		{
			_player = player;
			_dx = dx;
			_dy = dy;
		}

		virtual ~MediaStart()
		{
			delete _player;
		}

		virtual void Release()
		{
			_player->Stop();
				
			WaitThread();
		}

		virtual void Run()
		{
			_player->Play();
		}

};

class SceneTest : public jlwuit::Scene {

	private:
		std::vector<MediaStart *> _players;
		jthread::Mutex _mutex;
		bool _is_playing;

	public:
		SceneTest():
			jlwuit::Scene(0, 0, 1920, 1080)
		{
			jlwuit::lwuit_size_t size = GetSize();

			for (int i=0; i<BOX_NUMS; i++) {
				jlwuit::Player *player = jlwuit::PlayerManager::CreatePlayer("channels/channel2");
				jlwuit::Component *cmp = player->GetVisualComponent();

				cmp->SetBounds(random()%(size.width-BOX_SIZE), random()%(size.height-BOX_SIZE), BOX_SIZE, BOX_SIZE);

				Add(cmp);

				_players.push_back(new MediaStart(player, ((random()%2) == 0)?-1:1, ((random()%2) == 0)?-1:1));
			}

			SetAnimationDelay(100);

			GetStyle()->SetIntegerParam("bg.color", 0x00000000);

			jlwuit::Device::GetDefaultScreen()->GetLayerByID("background")->SetEnabled(false);
			
			_is_playing = false;
		}

		virtual ~SceneTest()
		{
			jlwuit::Device::GetDefaultScreen()->GetLayerByID("background")->SetEnabled(true);

			jthread::AutoLock lock(&_mutex);

			for (int i=0; i<(int)_players.size(); i++) {
				MediaStart *media = _players[i];

				delete media;
			}
		}

		virtual void StartMedia()
		{
			jthread::AutoLock lock(&_mutex);

			// INFO:: MediaStart starts all players in parallel
			int k = 0;

			for (std::vector<MediaStart *>::iterator i=_players.begin(); i!=_players.end(); i++) {
				(*i)->Start();
			}
			
			_is_playing = true;
		}

		virtual void StopMedia()
		{
			jthread::AutoLock lock(&_mutex);

			for (std::vector<MediaStart *>::iterator i=_players.begin(); i!=_players.end(); i++) {
				(*i)->Release();
			}

			RemoveAll();

			_is_playing = false;
		}

		virtual bool Animate()
		{
			jthread::AutoLock lock(&_mutex);

			if (_is_playing == false) {
				return false;
			}

			jlwuit::lwuit_size_t size = GetSize();

			for (std::vector<MediaStart *>::iterator i=_players.begin(); i!=_players.end(); i++) {
				MediaStart *media = (*i);
	
				jlwuit::Component *cmp = media->_player->GetVisualComponent();
				jlwuit::lwuit_point_t location = cmp->GetLocation();

				location.x = location.x+media->_dx*BOX_STEP;
				location.y = location.y+media->_dy*BOX_STEP;

				if (location.x < 0) {
					location.x = 0;
					media->_dx = 1;
				}

				if ((location.x+BOX_SIZE) > size.width) {
					location.x = size.width-BOX_SIZE;
					media->_dx = -1;
				}

				if (location.y < 0) {
					location.y = 0;
					media->_dy = 1;
				}

				if ((location.y+BOX_SIZE) > size.height) {
					location.y = size.height-BOX_SIZE;
					media->_dy = -1;
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
	sleep(10);
	app.StopMedia();
	sleep(10);

	return 0;
}
