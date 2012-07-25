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
#include "playermanager.h"
#include "device.h"

#include <stdio.h>
#include <math.h>

#define GAPX		16
#define GAPY		16

class VideoTest : public jlwuit::Scene {

	private:
		jlwuit::Player *_player;

	public:
		VideoTest():
			jlwuit::Scene(0, 0, 1920, 1080)
		{
			jlwuit::Device::GetDefaultScreen()->GetLayerByID("background")->SetEnabled(false);

			_player = jlwuit::PlayerManager::CreatePlayer("channels/channel1");

			jlwuit::Component *cmp = _player->GetVisualComponent();

			cmp->SetBounds(100, 100, 320, 240);

			Add(cmp);
			
			_player->Play();
				
			GetStyle()->SetIntegerParam("bg.color", 0x00000000);
		}

		virtual ~VideoTest()
		{
			jlwuit::Device::GetDefaultScreen()->GetLayerByID("background")->SetEnabled(true);
		}

		virtual void Paint(jlwuit::Graphics *g)
		{
			jlwuit::Scene::Paint(g);

			jlwuit::Component *cmp = _player->GetVisualComponent();
			jlwuit::lwuit_region_t bounds = cmp->GetBounds();

			g->SetColor(jlwuit::Color::Red);
			g->DrawRectangle(bounds.x, bounds.y, bounds.width, bounds.height);
		}

		virtual bool OnKeyPress(jlwuit::UserEvent *event)
		{
			jlwuit::Component *cmp = _player->GetVisualComponent();
			jlwuit::lwuit_region_t bounds = cmp->GetBounds();

			if (event->GetKeySymbol() == jlwuit::LKS_CURSOR_LEFT) {
				bounds.x = bounds.x - 10;

				if (bounds.x < 0) {
					bounds.x = 0;
				}
			} else if (event->GetKeySymbol() == jlwuit::LKS_CURSOR_RIGHT) {
				bounds.x = bounds.x + 10;

				if ((bounds.x+bounds.width) >= GetWidth()) {
					bounds.x = GetWidth()-bounds.width-1;
				}
			} else if (event->GetKeySymbol() == jlwuit::LKS_CURSOR_UP) {
				bounds.y = bounds.y - 10;

				if (bounds.y < 0) {
					bounds.y = 0;
				}
			} else if (event->GetKeySymbol() == jlwuit::LKS_CURSOR_DOWN) {
				bounds.y = bounds.y + 10;

				if ((bounds.y+bounds.height) >= GetHeight()) {
					bounds.y = GetHeight()-bounds.height-1;
				}
			} else if (event->GetKeySymbol() == jlwuit::LKS_p) {
				_player->Pause();
			} else if (event->GetKeySymbol() == jlwuit::LKS_r) {
				_player->Resume();
			}

			cmp->SetBounds(bounds);
			cmp->Repaint();

			return false;
		}

};

int main()
{
	jlwuit::Implementation::GetInstance()->Initialize();

	VideoTest app;

	app.Show();

	sleep(100000);

	return 0;
}
