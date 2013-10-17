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
#include "photoslider.h"
#include "usbmanager.h"
#include "exception.h"

#include "jfile.h"
#include "jioexception.h"

#define TEXT_GAPX		8
#define TEXT_GAPY		8
#define TEXT_SIZE		80

#define MARGIN_LEFT		TEXT_GAPX
#define MARGIN_RIGHT	TEXT_GAPY
#define MARGIN_TOP		(TEXT_GAPY+TEXT_SIZE+TEXT_GAPY)
#define MARGIN_BOTTOM	TEXT_GAPY

PhotoSlider::PhotoSlider():
	jlwuit::Scene(0, 0, 1920, 1080)
{
	_index = -1;
	_message =  "Insira um Pen-Drive contendo imagens";

	jlwuit::USBManager::GetInstance()->RegisterUSBStatusListener(this);
	jlwuit::USBManager::GetInstance()->Start();
}

PhotoSlider::~PhotoSlider()
{
	jlwuit::USBManager::GetInstance()->RemoveUSBStatusListener(this);
	jlwuit::USBManager::GetInstance()->Stop();
}

void PhotoSlider::Paint(jlwuit::Graphics *g)
{
	jlwuit::LookAndFeel *laf = jlwuit::LookAndFeel::GetInstance();
	jlwuit::lwuit_region_t bounds = GetBounds();

	int sw = bounds.width-MARGIN_LEFT-MARGIN_RIGHT,
			sh = bounds.height-MARGIN_TOP-MARGIN_BOTTOM;

	if (_index < 0) {
		laf->DrawBox(g, NULL, MARGIN_LEFT, bounds.height/2, sw, TEXT_SIZE);
		laf->DrawText(g, NULL, "medium", _message, MARGIN_LEFT, bounds.height/2, sw, TEXT_SIZE);
	} else {
		laf->DrawBox(g, NULL, MARGIN_LEFT, TEXT_GAPY, sw, TEXT_SIZE);
		laf->DrawText(g, NULL, "large", "Image Viewer", MARGIN_LEFT, TEXT_GAPY, sw, TEXT_SIZE);
		
		laf->DrawBox(g, NULL, MARGIN_LEFT, bounds.height-TEXT_SIZE-TEXT_GAPY, sw, TEXT_SIZE);
		laf->DrawText(g, NULL, "large", "use direction arrows to view photos", MARGIN_LEFT, bounds.height-TEXT_SIZE-TEXT_GAPY, sw, TEXT_SIZE);
	}

	if (_images.size() == 0) {
		return;
	}

	int iw = -1,
			ih = -1;

	jlwuit::Image::GetImageSize(_images[_index], &iw, &ih);

	// by Sindolfo Filho
	float fw = iw,
				fh = ih,
				scale = 0.0;

	sh = sh - (TEXT_SIZE+TEXT_GAPY);

	if (iw > sw) {
		fw = sw;
		scale = fw/iw;
		fh = ih*scale;

		if (fh > sh) {
			fh = sh;
			scale = fh/ih;
			fw = iw*scale;
		}
	} else if (ih > sh) {
		fh = sh;
		scale = fh/ih;
		fw = iw*scale;

		if (fw > sw) {
			fw = sw;
			scale = fw/iw;
			fh = ih*scale;
		}
	}

	g->DrawImage(_images[_index], (int)((sw-fw)/2)+MARGIN_LEFT, (int)((sh-fh)/2)+MARGIN_TOP, (int)fw, (int)fh);
}

bool PhotoSlider::OnKeyDown(jlwuit::UserEvent *event)
{
	if (_images.size() == 0) {
		return false;
	}

	if (event->GetKeySymbol() == jlwuit::LKS_CURSOR_LEFT) {
		if (--_index < 0) {
			_index = _images.size()-1;
		}
	} else if (event->GetKeySymbol() == jlwuit::LKS_CURSOR_RIGHT) {
		_index = (_index+1)%_images.size();
	}

	Repaint();

	return true;
}

void PhotoSlider::EntryUSBDevice(jlwuit::USBStatusEvent *event)
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
									strcasecmp((const char *)audio.c_str()+audio.size()-3, "png") == 0 || 
									strcasecmp((const char *)audio.c_str()+audio.size()-3, "jpg") == 0
									)) {

							_images.push_back(audio);
						}
					}
				} catch (jio::IOException &e) {
				}
			}
		} catch (jio::IOException &e) {
			break;
		}
	}

	if (_images.size() == 0) {
		_index = -1;
		_message = "Nao existem imagens neste dispositivo";
	} else {
		_index = 0;
		_message = "";
	}
	
	Repaint();
}

void PhotoSlider::RemoveUSBDevice(jlwuit::USBStatusEvent *event)
{
	_index = -1;
	_message =  "Insira um Pen-Drive contendo imagens";

	_images.clear();

	Repaint();
}
