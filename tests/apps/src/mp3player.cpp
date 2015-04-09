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
#include "mp3player.h"
#include "usbmanager.h"
#include "playermanager.h"
#include "videosizecontrol.h"
#include "device.h"
#include "jfile.h"
#include "jioexception.h"

MP3Player::MP3Player():
	jlwuit::Scene(0, 0, 1920, 1080)
{
	_progress = 0;
	_index = -1;
	_action = LPA_PLAY;
	_state = LPA_STOP;
	_player = NULL;

	jlwuit::Device::GetDefaultScreen()->GetLayerByID("video")->SetEnabled(false);

	jlwuit::Player *player = jlwuit::PlayerManager::CreatePlayer("isdtv://0");

	if (player != NULL) {
		player->Stop();
	}
	
	jlwuit::LookAndFeel::LoadImage("rewind", "images/rewind.png");
	jlwuit::LookAndFeel::LoadImage("stop", "images/stop.png");
	jlwuit::LookAndFeel::LoadImage("play", "images/play.png");
	jlwuit::LookAndFeel::LoadImage("pause", "images/pause.png");
	jlwuit::LookAndFeel::LoadImage("forward", "images/forward.png");

	jlwuit::USBManager::GetInstance()->RegisterUSBStatusListener(this);
	jlwuit::USBManager::GetInstance()->Start();
}

MP3Player::~MP3Player()
{
	_screensaver->Release();

	delete _screensaver;
	_screensaver = NULL;

	jlwuit::USBManager::GetInstance()->RemoveUSBStatusListener(this);
	jlwuit::USBManager::GetInstance()->Stop();

	Hide();

	if (_player != NULL) {
		_player->Stop();
		_player->Close();

		ReleasePlayer();
	}
	
	jlwuit::Player *player = jlwuit::PlayerManager::CreatePlayer("isdtv://0");

	if (player != NULL) {
		player->Play();
	}
	
	jlwuit::Device::GetDefaultScreen()->GetLayerByID("video")->SetEnabled(true);
	
	jlwuit::LookAndFeel::ReleaseImage("rewind");
	jlwuit::LookAndFeel::ReleaseImage("stop");
	jlwuit::LookAndFeel::ReleaseImage("play");
	jlwuit::LookAndFeel::ReleaseImage("pause");
	jlwuit::LookAndFeel::ReleaseImage("forward");
}

void MP3Player::Initialize()
{
	_screensaver = new ScreenSaver(this, "images/mp3-logo.png");

	_screensaver->Start();
}

void MP3Player::Finalize()
{
}

void MP3Player::ReleasePlayer()
{
	{
		jthread::AutoLock lock(&_mutex);

		delete _player;
		_player = NULL;
	}

	WaitThread();
}

bool MP3Player::Animate()
{
	return false;
}

void MP3Player::Run()
{
	while (true) {
		uint64_t mediatime = 0;
		uint64_t currenttime = 0;

		{
			jthread::AutoLock lock(&_mutex);

			if (_player == NULL) {
				break;
			}

			mediatime = _player->GetMediaTime();
			currenttime = _player->GetCurrentTime();
		}

		if (mediatime != 0LL) {
			_progress = (100*currenttime)/mediatime;

			Repaint();
		}

		usleep(1);
	}
}

void MP3Player::Paint(jlwuit::Graphics *g)
{
	jlwuit::LookAndFeel *laf = jlwuit::LookAndFeel::GetInstance();
	jlwuit::lwuit_region_t bounds = GetBounds();

	int sw = bounds.width-2*GAPX,
			sh = bounds.height-2*GAPY;
	int num_items = 5,
			w = (sw-GAPX)/2,
			h = (num_items+1)*TEXT_SPAN+GAPY;
	int boxw = (w-2*GAPX)/4;

	laf->DrawBox(g, NULL, 0, 0, bounds.width, bounds.height);

	laf->DrawText(g, NULL, "medium", "MP3 Player", 0, GAPY, bounds.width, TEXT_SIZE);

	laf->DrawBox(g, NULL, 0*(w+GAPX)+GAPX, 1*TEXT_SPAN+GAPY, w, h);
	laf->DrawBox(g, NULL, 1*(w+GAPX)+GAPX, 1*TEXT_SPAN+GAPY, w, h);

	laf->DrawText(g, NULL, "medium", "Musics", 0*(w+GAPX)+2*GAPX, 1*TEXT_SPAN+2*GAPY, w-2*GAPX, TEXT_SIZE);
	
	laf->DrawText(g, NULL, "medium", "Artist", 1*(w+GAPX)+2*GAPX, 1*TEXT_SPAN+2*GAPY, boxw, TEXT_SIZE, jlwuit::LHA_LEFT);
	laf->DrawText(g, NULL, "medium", "Track", 1*(w+GAPX)+2*GAPX, 2*TEXT_SPAN+2*GAPY, boxw, TEXT_SIZE, jlwuit::LHA_LEFT);
	laf->DrawText(g, NULL, "medium", "Album", 1*(w+GAPX)+2*GAPX, 3*TEXT_SPAN+2*GAPY, boxw, TEXT_SIZE, jlwuit::LHA_LEFT);
	laf->DrawText(g, NULL, "medium", "Genre", 1*(w+GAPX)+2*GAPX, 4*TEXT_SPAN+2*GAPY, boxw, TEXT_SIZE, jlwuit::LHA_LEFT);
	laf->DrawText(g, NULL, "medium", "Year", 1*(w+GAPX)+2*GAPX, 5*TEXT_SPAN+2*GAPY, boxw, TEXT_SIZE, jlwuit::LHA_LEFT);
	laf->DrawText(g, NULL, "medium", "Comments", 1*(w+GAPX)+2*GAPX, 6*TEXT_SPAN+2*GAPY, boxw, TEXT_SIZE, jlwuit::LHA_LEFT);

	laf->DrawTextBox(g, NULL, "medium", _artist, 1*(w+GAPX)+boxw+2*GAPX, 1*TEXT_SPAN+2*GAPY, w-boxw-2*GAPX, TEXT_SIZE, jlwuit::LHA_LEFT);
	laf->DrawTextBox(g, NULL, "medium", _track, 1*(w+GAPX)+boxw+2*GAPX, 2*TEXT_SPAN+2*GAPY, w-boxw-2*GAPX, TEXT_SIZE, jlwuit::LHA_LEFT);
	laf->DrawTextBox(g, NULL, "medium", _album, 1*(w+GAPX)+boxw+2*GAPX, 3*TEXT_SPAN+2*GAPY, w-boxw-2*GAPX, TEXT_SIZE, jlwuit::LHA_LEFT);
	laf->DrawTextBox(g, NULL, "medium", _genre, 1*(w+GAPX)+boxw+2*GAPX, 4*TEXT_SPAN+2*GAPY, w-boxw-2*GAPX, TEXT_SIZE, jlwuit::LHA_LEFT);
	laf->DrawTextBox(g, NULL, "medium", _year, 1*(w+GAPX)+boxw+2*GAPX, 5*TEXT_SPAN+2*GAPY, w-boxw-2*GAPX, TEXT_SIZE, jlwuit::LHA_LEFT);
	laf->DrawTextBox(g, NULL, "medium", _comments, 1*(w+GAPX)+boxw+2*GAPX, 6*TEXT_SPAN+2*GAPY, w-boxw-2*GAPX, TEXT_SIZE, jlwuit::LHA_LEFT);

	// draw items
	for (int i=0; i<num_items; i++) {
		laf->DrawBorder(g, NULL, 0*(w+GAPX)+2*GAPX, (i+2)*TEXT_SPAN+2*GAPY, w-2*GAPX, TEXT_SIZE);
	}

	if (_index >= 0) {
		num_items = num_items + _index;

		if (num_items > (int)_musics.size()) {
			num_items = (int)_musics.size();
		}

		for (int k=_index; k<num_items; k++) {
			std::string music = _musics[k];
			std::string::size_type n = music.rfind("/");

			if (n != std::string::npos) {
				music = music.substr(n+1);
			}

			int i = k-_index;

			if (k == _index) {
				laf->SetType(jlwuit::LST_FOCUS);
				laf->DrawBox(g, NULL, 0*(w+GAPX)+2*GAPX, (i+2)*TEXT_SPAN+2*GAPY, w-2*GAPX, TEXT_SIZE);
				laf->SetType(jlwuit::LST_NORMAL);
			}

			laf->DrawText(g, NULL, "medium", music, 0*(w+GAPX)+2*GAPX, (i+2)*TEXT_SPAN+2*GAPY, w-2*GAPX, TEXT_SIZE);
		}
	}

	int x = (1920-1*180-2*150-2*120-4*GAPX)/2,
			y = bounds.height-180-10*GAPY;

	laf->DrawImage(g, "rewind", x, y+(180-120)/2, 120, 120);
	laf->DrawImage(g, "stop", x+(120+GAPX), y + (180-150)/2, 150, 150);
	laf->DrawImage(g, "play", x+(120+150+2*GAPX), y, 180 + (180-180)/2, 180);
	laf->DrawImage(g, "pause", x+(120+150+180+3*GAPX), y + (180-150)/2, 150, 150);
	laf->DrawImage(g, "forward", x+(120+2*150+180+4*GAPX), y + (180-120)/2, 120, 120);
	
	if (_action == LPA_PREVIOUS) {
		laf->DrawBorder(g, NULL, x, y+(180-120)/2, 120, 120);
	} else if (_action == LPA_STOP) {
		laf->DrawBorder(g, NULL, x+(120+GAPX), y + (180-150)/2, 150, 150);
	} else if (_action == LPA_PLAY) {
		laf->DrawBorder(g, NULL, x+(120+150+2*GAPX), y, 180 + (180-180)/2, 180);
	} else if (_action == LPA_PAUSE) {
		laf->DrawBorder(g, NULL, x+(120+150+180+3*GAPX), y + (180-150)/2, 150, 150);
	} else if (_action == LPA_NEXT) {
		laf->DrawBorder(g, NULL, x+(120+2*150+180+4*GAPX), y + (180-120)/2, 120, 120);
	}

	// laf->DrawBorder(g, NULL, 5*GAPX, bounds.height-6*GAPY, bounds.width-10*GAPX, GAPY);
	laf->DrawProgressBar(g, NULL, _progress, 5*GAPX, bounds.height-6*GAPY, bounds.width-10*GAPX, GAPY);
	
	/*
	stop->SetImageFocus("./icons/stop_check.png");
	play->SetImageFocus("./icons/play_check.png");
	pause->SetImageFocus("./icons/pause_check.png");
	*/
	
	if (_index == -1) {
		laf->DrawTextBox(g, NULL, "medium", "Insert a usb device", GAPX, bounds.height/2, sw, TEXT_SIZE);
	} else if (_index == -2) {
		laf->DrawTextBox(g, NULL, "large", "USB device has no images", GAPX, GAPY, sw, TEXT_SIZE);
	}
}

bool MP3Player::OnKeyDown(jlwuit::UserEvent *event)
{
	if (_index < 0 || _musics.size() == 0) {
		return true;
	}

	lwuit_player_action_t actions[5] = {
		LPA_PREVIOUS,
		LPA_STOP,
		LPA_PLAY,
		LPA_PAUSE,
		LPA_NEXT
	};
	int actions_size = 5;
	int action = 0;
	
	for (int i=0; i<actions_size; i++) {
		if (_action == actions[i]) {
			action = i;

			break;
		}
	}

	// _screensaver->Resume();
	
	if (event->GetKeySymbol() == jlwuit::LKS_ENTER) {
		if (_action == LPA_PREVIOUS) {
			GoPrevious();
		} else if (_action == LPA_STOP) {
			GoStop();
		} else if (_action == LPA_PLAY) {
			GoPlay();
		} else if (_action == LPA_PAUSE) {
			GoPause();
		} else if (_action == LPA_NEXT) {
			GoNext();
		}
	} else if (event->GetKeySymbol() == jlwuit::LKS_CURSOR_LEFT) {
		action = action - 1;

		if (action < 0) {
			action = actions_size-1;
		}
	} else if (event->GetKeySymbol() == jlwuit::LKS_CURSOR_RIGHT) {
		action = action + 1;

		if (action >= actions_size) {
			action = 0;
		}
	}

	_action = actions[action];

	Repaint();

	return true;
}

void MP3Player::GoLeft()
{
}

void MP3Player::GoRight()
{
}

void MP3Player::GoPrevious()
{
	_index = _index - 1;

	if (_index < 0) {
		_index = 0;
		// _index = _musics.size()-1;
	}

	if (_state == LPA_PLAY) {
		GoPlay();
	}
}

void MP3Player::GoNext()
{
	_index = _index + 1;

	if (_index >= (int)_musics.size()) {
		// _index = 0;
		_index = (int)_musics.size()-1;
	}

	if (_state == LPA_PLAY) {
		GoPlay();
	}
}

void MP3Player::GoTo(int index)
{
	// playListBox->SetSelected(index);
}

void MP3Player::GoPlay()
{
	std::string music = _musics[_index];

	if (_state == LPA_PAUSE) {
		_player->Resume();

		_state = LPA_PLAY;

		return;
	}

	// INFO:: chamar Stop ou Close estah quebrando a criacao de novos players
	if (_player != NULL) {
		ReleasePlayer();
	}

	_player = jlwuit::PlayerManager::CreatePlayer(music);

	if (_player != NULL) {
		_player->Play();

		Start();
	
		_state = LPA_PLAY;
	} else {
		ReleasePlayer();

		_T("Media cannot be played"); 
	}
}

void MP3Player::GoStop()
{
	if (_player != NULL) {
		_player->Stop();
		_player->Close();

		ReleasePlayer();
	}
		
	_state = LPA_STOP;
}

void MP3Player::GoPause()
{
	if (_player != NULL) {
		_player->Pause();
	
		_state = LPA_PAUSE;
	}
}

void MP3Player::GoInfo()
{
}

void MP3Player::SetMusicDurationString(std::string length)
{
	//Atualizar GUI para exibir a duracao da musica
}

void MP3Player::SetPlayList(std::vector<std::string> playList, int playListIndex)
{
	/*
	std::string aux;

	for (int i=0; i<(int)playList.size(); i++) {
		aux = playList[i].substr(playList[i].rfind('/') + 1,playList[i].length());
		if(aux != "")
			playListBox->AddTextItem(aux);
		else
			playListBox->AddTextItem(playList[i]);
	}

	playListBox->SetCurrentIndex(playListIndex);

	playListBox->Repaint();
	*/
}

int MP3Player::GetSelectedIndex()
{
	return 0;//playListBox->GetCurrentIndex();
}

int MP3Player::GetAction()
{
	return _action;
}

void MP3Player::EntryUSBDevice(jlwuit::USBStatusEvent *event)
{
	std::vector<std::string> folders;
	std::string mount_point = event->GetMountPoint();

	folders.push_back(".");

	while (folders.size() > 0) {
		std::string path = *folders.begin();
		std::string current_mount_point = mount_point + "/" + path;

		folders.erase(folders.begin());

		try {
			jio::File file(current_mount_point);
			std::vector<std::string> files;
			
			file.ListFiles(&files);

			for (std::vector<std::string>::iterator i=files.begin(); i!=files.end(); i++) {
				std::string s = (*i);

				try {
					jio::File f(current_mount_point + "/" + s);

					if (f.GetType() == jio::JFT_DIRECTORY) {
						if (s != "." && s != "..") {
							folders.push_back(path + "/" + s);
						}
					} else if (f.GetType() == jio::JFT_REGULAR) {
						std::string audio = (current_mount_point + "/" + s);

						if (audio.size() > 4 && (
									strcasecmp((const char *)audio.c_str()+audio.size()-3, "mp3") == 0 || 
									strcasecmp((const char *)audio.c_str()+audio.size()-3, "ogg") == 0 || 
									strcasecmp((const char *)audio.c_str()+audio.size()-3, "wav") == 0
									)) {

							_musics.push_back(audio);
						}
					}
				} catch (jio::IOException &e) {
				}
			}
		} catch (jio::IOException &e) {
			break;
		}
	}

	if (_musics.size() == 0) {
		_index = -2;
	} else {
		_index = 0;
	}
	
	Repaint();
}

void MP3Player::RemoveUSBDevice(jlwuit::USBStatusEvent *event)
{
	_index = -1;
	_musics.clear();

	Repaint();
}
