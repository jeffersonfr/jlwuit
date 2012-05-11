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
#include "jfile.h"
#include "jioexception.h"

#define GAPX		16
#define GAPY		16

#define IMAGE_SIZE		100

#define TEXT_SIZE			80
#define TEXT_SPAN			(TEXT_SIZE+GAPY)

#define SCREEN_SAVER_TIMEOUT	60

namespace jlwuit {

MP3Player::MP3Player():
	jlwuit::Scene(0, 0, 1920, 1080)
{
	_progress = 0;
	_index = -1;
	_action = LPA_STOP;
	_player = NULL;

	_screen_saver_timeout = 0;
	_screen_saver_state = 0;
	_image.x = 0;
	_image.y = 0;

	jlwuit::Player *player = jlwuit::PlayerManager::CreatePlayer("isdtv://0");

	if (player != NULL) {
		player->Stop();
	}
	
	jlwuit::LookAndFeel::LoadImage("rewind", "images/rewind.png");
	jlwuit::LookAndFeel::LoadImage("stop", "images/stop.png");
	jlwuit::LookAndFeel::LoadImage("play", "images/play.png");
	jlwuit::LookAndFeel::LoadImage("pause", "images/pause.png");
	jlwuit::LookAndFeel::LoadImage("forward", "images/forward.png");
	jlwuit::LookAndFeel::LoadImage("logo", "images/mp3-logo.png");

	jlwuit::USBManager::GetInstance()->RegisterUSBStatusListener(this);
	jlwuit::USBManager::GetInstance()->Start();
}

MP3Player::~MP3Player()
{
	jlwuit::USBManager::GetInstance()->RemoveUSBStatusListener(this);
	jlwuit::USBManager::GetInstance()->Stop();

	Hide();

	if (_player != NULL) {
		delete _player;
		_player = NULL;
	}
	
	jlwuit::Player *player = jlwuit::PlayerManager::CreatePlayer("isdtv://0");

	if (player != NULL) {
		player->Play();
	}
	
	jlwuit::LookAndFeel::ReleaseImage("rewind");
	jlwuit::LookAndFeel::ReleaseImage("stop");
	jlwuit::LookAndFeel::ReleaseImage("play");
	jlwuit::LookAndFeel::ReleaseImage("pause");
	jlwuit::LookAndFeel::ReleaseImage("forward");
	jlwuit::LookAndFeel::ReleaseImage("logo");
}

bool MP3Player::Animated()
{
	_screen_saver_state = 0;
	_screen_saver_timeout = _screen_saver_timeout + 1;

	if (_screen_saver_timeout >= SCREEN_SAVER_TIMEOUT) {
		std::cout << "Screen Saver" << std::endl;

		_screen_saver_state = 1;

		_image.x = random()%(1920-640);
		_image.y = random()%(1080-240);
	}

	return true;
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

	if (_screen_saver_state == 1) {
		laf->DrawImage(g, "logo", _image.x, _image.y, 640, 240);

		return;
	}

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
	int dindex = 0;

	if (_index > num_items) {
		dindex = _index-num_items;
	}

	for (int i=0; i<num_items; i++) {
		laf->DrawBorder(g, NULL, 0*(w+GAPX)+2*GAPX, (i+2)*TEXT_SPAN+2*GAPY, w-2*GAPX, TEXT_SIZE);
	}

	for (int i=dindex; i<num_items && i<(int)_musics.size(); i++) {
		laf->DrawText(g, NULL, "medium", _musics[i+dindex], 0*(w+GAPX)+2*GAPX, (i+2)*TEXT_SPAN+2*GAPY, w-2*GAPX, TEXT_SIZE);
	}

	int x = (1920-1*180-2*150-2*120-4*GAPX)/2,
			y = bounds.height-180-10*GAPY;

	laf->DrawImage(g, "rewind", x, y + (180-120)/2, 120, 120);
	laf->DrawImage(g, "stop", x + (120+GAPX), y + (180-150)/2, 150, 150);
	laf->DrawImage(g, "play", x + (120+150+2*GAPX), y, 180 + (180-180)/2, 180);
	laf->DrawImage(g, "pause", x + (120+150+180+3*GAPX), y + (180-150)/2, 150, 150);
	laf->DrawImage(g, "forward", x + (120+2*150+180+4*GAPX), y + (180-120)/2, 120, 120);
	
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
	_screen_saver_timeout = 0;

	/*
	if (event->GetKeySymbol() == jlwuit::JKS_ENTER) {
		tuner::Locator locator(_musics[playListBox->GetCurrentIndex()]);

		if (_player != NULL) {
			delete _player;
		}

		_player = media::PlayerManager::GetInstance()->CreatePlayer(&locator);

		if (_player != NULL) {
			_player->Play();
		}
	}
	*/

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
	/*
	int index = playListBox->GetCurrentIndex();

	if(index == 0) {
		playListBox->SetCurrentIndex(playListBox->GetItemsSize()-1);
	} else {
		playListBox->SetCurrentIndex(index-1);
	}
	*/
}

void MP3Player::GoNext()
{
	/*
	int index = playListBox->GetCurrentIndex();

	if(index == playListBox->GetItemsSize()-1) {
		playListBox->SetCurrentIndex(0);
	} else {
		playListBox->SetCurrentIndex(index+1);
	}
	*/
}

void MP3Player::GoTo(int index)
{
	// playListBox->SetSelected(index);
}

void MP3Player::GoPlay()
{
	_action = LPA_PLAY;

	// watch->Resume();
}

void MP3Player::GoStop()
{
	_action = LPA_STOP;

	// watch->Reset();
	// watch->Pause();
}

void MP3Player::GoPause()
{
	_action = LPA_PAUSE;
	
	// watch->Pause();
}

void MP3Player::GoInfo()
{
}

void MP3Player::TransitionState(bool flag)
{
	/*
	if(flag == true) {
		watch->Pause();
		watch->Reset();
	} else {
		watch->Resume();
	}
	*/
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

void MP3Player::SetProgress(double value)
{
	_progress = value;
}

void MP3Player::SetElapsedTime(int hour, int minute, int second)
{
	/*
	watch->SetHours(hour);
	watch->SetMinutes(minute);
	watch->SetSeconds(second);
	*/
}

void MP3Player::ResetElapsedTime()
{
	// watch->Reset();
}

void MP3Player::SetFullTime(std::string time)
{
	/*
	total_time->SetText(time);
	if(time.size() == 8)
	{
		watch->SetMaxCount(atoi(time.substr(0, 2).c_str()), atoi(time.substr(3, 5).c_str()), atoi(time.substr(6, 8).c_str()));
	}
	else
	{
		watch->SetMaxCount(0, atoi(time.substr(0, 2).c_str()), atoi(time.substr(3, 5).c_str()));
	}
	*/
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
			std::vector<std::string> files = file.ListFiles();

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
									strcasecmp((const char *)audio.c_str()+audio.size()-3, "png") == 0 || 
									strcasecmp((const char *)audio.c_str()+audio.size()-3, "jpg") == 0
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

}
