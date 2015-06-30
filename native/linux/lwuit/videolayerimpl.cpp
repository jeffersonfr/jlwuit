/***************************************************************************
 *   Copyright (C) 2005 by Jeff Ferr                                       *
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
#include "videolayerimpl.h"
#include "imageimpl.h"
#include "jgfxhandler.h"
#include "preferences.h"
#include "device.h"
#include "backgroundlayerimpl.h"
#include "jautolock.h"

namespace jlwuit {

VideoLayerImpl::VideoLayerImpl():
	LayerImpl("video")
{
	_player = NULL;
}

VideoLayerImpl::~VideoLayerImpl()
{
	if (_player != NULL) {
		_player->Stop();

		delete _player;
	}
}

void VideoLayerImpl::Initialize()
{
	jlwuit::Document *ds = jlwuit::Preferences::Create("system");
	jlwuit::Element *es = ds->GetElementByIndex(0);
	jlwuit::Document *dc = jlwuit::Preferences::Create("channels");
	jlwuit::Element *ec = dc->GetElementByIndex(es->GetIntegerParam("channel"));

	if (ec->GetTextParam("type") == "local") {
		SetFile(ec->GetTextParam("path"));
	
		Play();
	} else {
		std::cout << "Video source <" << ec->GetTextParam("type") << "> not supported !" << std::endl;
	}
}

void VideoLayerImpl::SetFile(std::string file)
{
	jmedia::PlayerManager::SetHint(jmedia::JPH_LIGHTWEIGHT, false);

	_player = jmedia::PlayerManager::CreatePlayer(file);

	jgui::Component *cmp = _player->GetVisualComponent();

	cmp->SetVisible(true);
}

void VideoLayerImpl::Play() 
{
	_player->Play();
}

void VideoLayerImpl::Stop() 
{
	_player->Stop();
}

uint64_t VideoLayerImpl::GetCurrentTime()
{
	return _player->GetCurrentTime();
}

uint64_t VideoLayerImpl::GetMediaTime()
{
	return _player->GetMediaTime();
}

bool VideoLayerImpl::IsEnabled()
{
	return _player->GetVisualComponent()->IsVisible();
}

void VideoLayerImpl::SetEnabled(bool b)
{
	_player->GetVisualComponent()->SetVisible(b);
}

void VideoLayerImpl::SetBounds(int x, int y, int w, int h)
{
	Layer *layer = jlwuit::Device::GetDefaultScreen()->GetLayerByID("background");

	_player->GetVisualComponent()->SetBounds(x, y, w, h);

	dynamic_cast<BackgroundLayerImpl *>(layer)->Repaint();
}

struct lwuit_region_t VideoLayerImpl::GetBounds()
{
	jgui::jregion_t bounds = _player->GetVisualComponent()->GetVisibleBounds();

	struct lwuit_region_t t;

	t.x = bounds.x;
	t.y = bounds.y;
	t.width = bounds.width;
	t.height = bounds.height;
	
	return t;
}

LayerSetup * VideoLayerImpl::GetLayerSetup()
{
	return this;
}

};

