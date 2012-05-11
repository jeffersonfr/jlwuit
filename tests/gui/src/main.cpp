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
#include "font.h"
#include "image.h"
#include "lookandfeel.h"

#include "jthread.h"
#include "jthreadexception.h"

#include <iostream>
#include <map>

#include <stdio.h>

#define GAPX		16
#define GAPY		16

#define IMAGE_SIZE		100

#define TEXT_SIZE			80
#define TEXT_SPAN			(TEXT_SIZE+GAPY)

#define MENU_HEIGHT		(5*TEXT_SIZE)

#define ANIMATION_STEPS			20
#define ANIMATION_DELAY			100000

#define DEFAULT_DELAY				4000LL

#define DEFAULT_TEXT				"Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor" \
														"incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud " \
														"exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure" \
														"dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur." \
														"Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt " \
														"mollit anim id est laborum."

jlwuit::Style *style = NULL;

struct service_t {
	uint16_t sid,
		tsid,
		serviceType;
	std::string serviceName,
		shortServiceName,
		providerName,
		shortProviderName;
};

struct event_t {
	uint16_t tsid,
		sid,
		eid;
	uint32_t startTime,
		duration;
	std::string eventName,
		shortEventName,
		shortDescription;
};

void DrawSignal(jlwuit::Graphics *g, int size, int gapx, int gapy, int signal, int x, int y, int width, int height)
{
	int n = size,
			h = (height-gapy)/n;

	if (signal != -1) {
		signal = (signal*n)/100;
	} else {
		signal = n/2;
	}

	if (signal > n) {
		signal = n;
	}

	width = (width-n*gapx+gapx)/n;

	for (int i=0; i<n; i++) {
		if (i < signal) {
			g->SetColor(jlwuit::Color(jlwuit::Color::Green));
		} else {
			g->SetColor(jlwuit::Color(jlwuit::Color::White));
		}

		g->FillRectangle(x+i*(width+gapx), y+(height-i*h-gapy)/2, width, (height-(n-i)*h));
	}
}

class Information : public jlwuit::Component {

	private:
		std::string _title,
			_channel,
			_date,
			_hour,
			_s1_hour,
			_s1_name,
			_s1_rate,
			_s2_hour,
			_s2_name,
			_s2_rate;

	public:
		Information():
			jlwuit::Component(0, 0, 1280, 4*TEXT_SPAN+GAPY)
		{
			_title = "Information";
			_channel = "<channel name>";
			_date = "--/--/----";
			_hour = "--:--";
			_s1_hour = "--:--";
			_s1_name = "<program name 1>";
			_s1_rate = "L";
			_s2_hour = "--:--";
			_s2_name = "<program name 2>";
			_s2_rate = "L";

			SetLocation((1920-GetWidth())/2, 1080-GetHeight()-32);
		}

		virtual ~Information()
		{
		}

		virtual void RequestInformation()
		{
		}

		virtual void Paint(jlwuit::Graphics *g) 
		{
			jlwuit::LookAndFeel *laf = jlwuit::LookAndFeel::GetInstance();
			
			jlwuit::lwuit_region_t bounds = GetBounds();
			int size = (bounds.width - GAPX)/5 - GAPX;

			laf->DrawBox(g, NULL, 0, 0, bounds.width, bounds.height);

			// title
			laf->DrawText(g, NULL, "medium", _title, 0, GAPY, 1280, TEXT_SIZE);

			// primeira linha
			laf->DrawBox(g, NULL, GAPX+0*(size+GAPX), GAPY+1*TEXT_SPAN, 2*size+1*GAPX, TEXT_SIZE);
			laf->DrawBox(g, NULL, GAPX+2*(size+GAPX), GAPY+1*TEXT_SPAN, 1*size, TEXT_SIZE);
			laf->DrawBox(g, NULL, GAPX+3*(size+GAPX), GAPY+1*TEXT_SPAN, 1*size, TEXT_SIZE);
			
			laf->DrawText(g, NULL, "medium", _channel, 2*GAPX+0*(size+GAPX), GAPY+1*TEXT_SPAN, 2*size+0*GAPX, TEXT_SIZE, jlwuit::LHA_LEFT);
			laf->DrawText(g, NULL, "medium", _date, GAPX+2*(size+GAPX), GAPY+1*TEXT_SPAN, 1*size, TEXT_SIZE);
			laf->DrawText(g, NULL, "medium", _hour, GAPX+3*(size+GAPX), GAPY+1*TEXT_SPAN, 1*size, TEXT_SIZE);
			DrawSignal(g, 7, 4, 10, 60, GAPX+4*(size+GAPX)+(size-IMAGE_SIZE)/2, GAPY+1*TEXT_SPAN, IMAGE_SIZE, TEXT_SIZE);

			// segunda linha
			laf->DrawBox(g, NULL, GAPX+0*(size+GAPX), GAPY+2*TEXT_SPAN, 1*size, TEXT_SIZE);
			laf->DrawBox(g, NULL, GAPX+1*(size+GAPX), GAPY+2*TEXT_SPAN, 3*size+2*GAPX, TEXT_SIZE);
			laf->DrawBox(g, NULL, GAPX+4*(size+GAPX), GAPY+2*TEXT_SPAN, 1*size, TEXT_SIZE);

			laf->DrawText(g, NULL, "medium", _s1_hour, GAPX+0*(size+GAPX), GAPY+2*TEXT_SPAN, 1*size, TEXT_SIZE);
			laf->DrawText(g, NULL, "medium", _s1_name, 2*GAPX+1*(size+GAPX), GAPY+2*TEXT_SPAN, 3*size+1*GAPX, TEXT_SIZE, jlwuit::LHA_LEFT);
			laf->DrawText(g, NULL, "medium", "livre", GAPX+4*(size+GAPX), GAPY+2*TEXT_SPAN, 1*size, TEXT_SIZE);

			// terceira linha
			laf->DrawBox(g, NULL, GAPX+0*(size+GAPX), GAPY+3*TEXT_SPAN, 1*size, TEXT_SIZE);
			laf->DrawBox(g, NULL, GAPX+1*(size+GAPX), GAPY+3*TEXT_SPAN, 3*size+2*GAPX, TEXT_SIZE);
			laf->DrawBox(g, NULL, GAPX+4*(size+GAPX), GAPY+3*TEXT_SPAN, 1*size, TEXT_SIZE);

			laf->DrawText(g, NULL, "medium", _s2_hour, GAPX+0*(size+GAPX), GAPY+3*TEXT_SPAN, 1*size, TEXT_SIZE);
			laf->DrawText(g, NULL, "medium", _s2_name, 2*GAPX+1*(size+GAPX), GAPY+3*TEXT_SPAN, 3*size+GAPX, TEXT_SIZE, jlwuit::LHA_LEFT);
			laf->DrawText(g, NULL, "medium", "livre", GAPX+4*(size+GAPX), GAPY+3*TEXT_SPAN, 1*size, TEXT_SIZE);
		}

};

class EPG : public jlwuit::Component {

	struct event_t {
		std::string name,
			description,
			short_description;
		int id;
		time_t start_time,
					 end_time;
	};

	struct service_t {
		std::string provider_name,
			provider_short_name,
			name,
			short_name;
		int id,
				ts_id,
				type;
		bool present,
				 has_schedule;

		std::vector<struct event_t> events;
	};

	struct channel_t {
		std::string name;

		std::vector<struct service_t> services;
	};

	private:
	std::vector<struct channel_t> _channels;
	jthread::Mutex _mutex;
		jlwuit::Image *_image;
		std::string _duration, 
			_genre, 
			_rate,
			_comments;
		int _state,
			_channel_list_index,
			_service_list_index,
			_event_select_index,
			_event_list_index;

	public:
		EPG():
			jlwuit::Component(0, 0, 1920, 1080)
		{
			_image = jlwuit::Image::CreateImage(320, 240);
			
			_image->GetGraphics()->DrawImage("images/splash.png", 0, 0, 320, 240);

			_state = 0; // 0:channel_list, 1:service_list, 2:event_select, 3:event_list
			_channel_list_index = 0;
			_service_list_index = 0;
			_event_select_index = 0;
			_event_list_index = 0;

			_duration = "---";
			_genre = "---";
			_rate = "---";
		}

		virtual ~EPG()
		{
		}

		virtual void RequestInformation()
		{
		}

		virtual void ShowServices()
		{
		}

		virtual void ShowEvents()
		{
		}

		virtual bool OnKeyDown(jlwuit::UserEvent *event)
		{
			if (event->GetKeySymbol() == jlwuit::LKS_ENTER) {
				if (_state == 0) {
					_state = 1;

					ShowServices();
				} else if (_state == 1) {
					_state = 2;

					ShowEvents();
				}
			} else if (event->GetKeySymbol() == jlwuit::LKS_BACK) {
				if (_state == 1) {
					_state = 0;
				} else if (_state == 2) {
					_state = 1;
				}
			} else if (event->GetKeySymbol() == jlwuit::LKS_CURSOR_LEFT) {
				if (_state == 2) {
				}
			} else if (event->GetKeySymbol() == jlwuit::LKS_CURSOR_RIGHT) {
				if (_state == 2) {
				}
			} else if (event->GetKeySymbol() == jlwuit::LKS_CURSOR_UP) {
				if (_state == 0) {
					if (--_channel_list_index < 0) {
						_channel_list_index = 0;
					}

					_service_list_index = 0;
				} else if (_state == 1) {
					if (--_service_list_index < 0) {
						_service_list_index = 0;
					}
				}
			} else if (event->GetKeySymbol() == jlwuit::LKS_CURSOR_DOWN) {
				if (_state == 0) {
					if (++_channel_list_index >= (int)_channels.size()) {
						_channel_list_index = _channels.size()-1;
					}

					if (_channel_list_index < 0) {
						_channel_list_index = 0;
					}

					_service_list_index = 0;
				} else if (_state == 1) {
					if (_channels.size() > 0) {
						std::vector<struct service_t> &services = _channels[_channel_list_index].services;

						if (++_service_list_index >= (int)services.size()) {
							_service_list_index = services.size()-1;
						}

						if (_service_list_index < 0) {
							_service_list_index = 0;
						}
					}
				}
			}

			Repaint();

			return true;
		}

		virtual void Paint(jlwuit::Graphics *g) 
		{
			jlwuit::LookAndFeel *laf = jlwuit::LookAndFeel::GetInstance();

			jlwuit::lwuit_region_t bounds = GetBounds();
			int size = (bounds.width - 5*GAPX)/4,
					number_items = 9,
					number_events = 3,
					list_height = (number_items+1)*TEXT_SPAN,
					events_height = number_events*TEXT_SPAN-GAPY;

			laf->DrawBox(g, NULL, 0, 0, bounds.width, bounds.height);
			laf->DrawText(g, NULL, "medium", "Eletronic Program Guide", 0, GAPY, bounds.width, TEXT_SIZE);

			laf->DrawBox(g, NULL, GAPX+0*(size+GAPX), 1*TEXT_SPAN+GAPY, size+0*(size+GAPX), list_height);
			laf->DrawBox(g, NULL, GAPX+1*(size+GAPX), 1*TEXT_SPAN+GAPY, size+0*(size+GAPX), list_height);
			laf->DrawBox(g, NULL, GAPX+2*(size+GAPX), 1*TEXT_SPAN+GAPY, size+1*(size+GAPX), list_height);
			
			laf->DrawText(g, NULL, "medium", "Channels", GAPX+0*(size+GAPX)+GAPX, 1*TEXT_SPAN+2*GAPY, size, TEXT_SIZE);
			laf->DrawText(g, NULL, "medium", "Services", GAPX+1*(size+GAPX)+GAPX, 1*TEXT_SPAN+2*GAPY, size, TEXT_SIZE);
			laf->DrawText(g, NULL, "medium", "Events", GAPX+2*(size+GAPX)+GAPX, 1*TEXT_SPAN+2*GAPY, 2*size, TEXT_SIZE);

			// list da canais e servicos
			for (int i=0; i<number_items; i++) {
				laf->DrawBox(g, NULL, 2*GAPX+0*(size+GAPX), (i+2)*TEXT_SPAN+GAPY, size-2*GAPY, TEXT_SIZE);
				laf->DrawBox(g, NULL, 2*GAPX+1*(size+GAPX), (i+2)*TEXT_SPAN+GAPY, size-2*GAPY, TEXT_SIZE);
			}

			laf->DrawBox(g, NULL, 2*GAPX+0*(size+GAPX), (_channel_list_index+2)*TEXT_SPAN+GAPY, size-2*GAPY, TEXT_SIZE);
			laf->DrawBox(g, NULL, 2*GAPX+1*(size+GAPX), (_service_list_index+2)*TEXT_SPAN+GAPY, size-2*GAPY, TEXT_SIZE);

			// ultima camada
			int x = 2*(size+GAPX)+4*GAPX, 
					y = 1*TEXT_SPAN+2*GAPY,
					w = 2*size-5*GAPX;

			g->SetColor(jlwuit::Color::Yellow);
			g->FillTriangle(x, y, x-2*GAPX, y+(TEXT_SPAN-2*GAPY)/2, x, y+TEXT_SPAN-2*GAPY);
			g->FillTriangle(x+w, y, x+w+2*GAPX, y+(TEXT_SPAN-2*GAPY)/2, x+w, y+TEXT_SPAN-2*GAPY);

			// event box
			for (int i=0; i<number_events; i++) {
				laf->DrawBox(g, NULL, GAPX+2*(size+GAPX)+GAPX, (i+2)*TEXT_SPAN+GAPY, size+1*(size+GAPX)-2*GAPX, TEXT_SIZE);
			}

			laf->DrawBox(g, NULL, GAPX+2*(size+GAPX)+GAPX, (_event_list_index+2)*TEXT_SPAN+GAPY, size+1*(size+GAPX)-2*GAPX, TEXT_SIZE);

			// draw lists
			g->SetColor(jlwuit::Color::White);

			if (_channels.size() == 0) {
				laf->DrawText(g, NULL, "medium", "<no channels>",  2*GAPX+0*(size+GAPX), (0+2)*TEXT_SPAN+GAPY, size-2*GAPY, TEXT_SIZE);
				laf->DrawText(g, NULL, "medium", "<no services>",  2*GAPX+1*(size+GAPX), (0+2)*TEXT_SPAN+GAPY, size-2*GAPY, TEXT_SIZE);
			} else {
				int k = 0;

				// draw channel name
				for (std::vector<struct channel_t>::iterator i=_channels.begin(); i!=_channels.end(); i++, k++) {
					laf->DrawText(g, NULL, "medium", i->name,  2*GAPX+0*(size+GAPX), (k+2)*TEXT_SPAN+GAPY, size-2*GAPY, TEXT_SIZE);
				}

				std::vector<struct service_t> &services = _channels[_channel_list_index].services;
				
				k=0;

				// draw service name
				for (std::vector<struct service_t>::iterator i=services.begin(); i!=services.end(); i++, k++) {
					laf->DrawText(g, NULL, "medium", i->name,  2*GAPX+1*(size+GAPX), (k+2)*TEXT_SPAN+GAPY, size-2*GAPY, TEXT_SIZE);
				}

				if (services.size() > 0) {
					std::vector<struct event_t> &events = services[_service_list_index].events;

					k = 0;

					// draw event name
					for (std::vector<struct event_t>::iterator i=events.begin(); i!=events.end(); i++, k++) {
						laf->DrawText(g, NULL, "medium", i->name, GAPX+2*(size+GAPX)+GAPX, (k+2)*TEXT_SPAN+GAPY, size+1*(size+GAPX)-2*GAPX, TEXT_SIZE);
					}
				} else {
					laf->DrawText(g, NULL, "medium", "---", GAPX+2*(size+GAPX)+GAPX, (0+2)*TEXT_SPAN+GAPY, size+1*(size+GAPX)-2*GAPX, TEXT_SIZE);
				}
			}

			laf->DrawText(g, NULL, "medium", "Duracao", 2*(size+GAPX)+3*GAPX, (5+0)*TEXT_SPAN+2*GAPY, size/2, TEXT_SIZE);
			laf->DrawText(g, NULL, "medium", "Genero", 2*(size+GAPX)+3*GAPX, (5+2)*TEXT_SPAN+2*GAPY, size/2, TEXT_SIZE);
			laf->DrawText(g, NULL, "medium", "Classificacao", 2*(size+GAPX)+3*GAPX, (5+4)*(TEXT_SPAN)+2*GAPY, size/2, TEXT_SIZE);
			laf->DrawText(g, NULL, "medium", "Comentarios", 2*(size+GAPX)+size/2+4*GAPX, (5+0)*(TEXT_SPAN)+2*GAPY, size+size/2-3*GAPX, TEXT_SIZE);

			laf->DrawTextBox(g, NULL, "medium", _duration, 2*(size+GAPX)+3*GAPX, (5+1)*TEXT_SPAN+GAPY, size/2, TEXT_SIZE);
			laf->DrawTextBox(g, NULL, "medium", _genre, 2*(size+GAPX)+3*GAPX, (5+3)*TEXT_SPAN+GAPY, size/2, TEXT_SIZE);
			laf->DrawTextBox(g, NULL, "medium", _rate, 2*(size+GAPX)+3*GAPX, (5+5)*TEXT_SPAN+GAPY, size/2, TEXT_SIZE);
			laf->DrawTextBox(g, NULL, "medium", _comments, 2*(size+GAPX)+size/2+4*GAPX, (5+1)*TEXT_SPAN+GAPY, size+size/2-3*GAPX, 5*TEXT_SPAN-GAPY);
			
			// draw focus
			g->SetColor(jlwuit::Color(0xf0, 0xf0, 0xf0, 0xff));
			if (_state == 0) {
				g->DrawRectangle(0*(size+GAPX)+GAPX, TEXT_SPAN+GAPY, size+0*(size+GAPX), list_height);
			} else if (_state == 1) {
				g->DrawRectangle(1*(size+GAPX)+GAPX, TEXT_SPAN+GAPY, size+0*(size+GAPX), list_height);
			} else if (_state == 2) {
				g->DrawRectangle(2*(size+GAPX)+GAPX, TEXT_SPAN+2*GAPY, size+1*(size+GAPX)-GAPX, events_height);
			}
		}

};

class Interactive : public jlwuit::Component {

	private:

	public:
		Interactive():
			jlwuit::Component((1920-200)/2, 1080, 200, 200)
		{
			SetVisible(true);
		}

		virtual ~Interactive()
		{
		}

		virtual void Paint(jlwuit::Graphics *g) 
		{
			jlwuit::LookAndFeel::GetInstance()->DrawImage(g, "interatividade_on", 0, 0, GetWidth(), GetHeight());
		}

};

class ChannelInfo : public jlwuit::Component {

	private:
		std::string _channel;

	public:
		ChannelInfo():
			jlwuit::Component((1920-800)/2, 0, 800, 3*TEXT_SIZE)
		{
		}

		virtual ~ChannelInfo()
		{
		}

		virtual void SetChannel(char key) 
		{
			if (key == '0' ||
					key == '1' ||
					key == '2' ||
					key == '3' ||
					key == '4' ||
					key == '5' ||
					key == '6' ||
					key == '7' ||
					key == '8' ||
					key == '9' ||
					key == '.') {
				if (_channel.size() >= 5) {
					_channel = "";
				}
				
				_channel = _channel + key;
			}

			Repaint();
		}

		virtual void SetChannel(std::string channel) 
		{
			_channel = channel;

			Repaint();
		}

		virtual void Paint(jlwuit::Graphics *g) 
		{
			jlwuit::LookAndFeel *laf = jlwuit::LookAndFeel::GetInstance();
			jlwuit::lwuit_region_t bounds = GetBounds();
			
			int text_size = bounds.width-IMAGE_SIZE-3*GAPX;

			laf->DrawBox(g, NULL, 0, 0, bounds.width, bounds.height);
			laf->DrawText(g, NULL, "large", _channel, GAPX, TEXT_SIZE, text_size, TEXT_SIZE, jlwuit::LHA_LEFT);
			
			DrawSignal(g, 7, 4, 10, 60, text_size+2*GAPX, TEXT_SIZE, IMAGE_SIZE, TEXT_SIZE);
		}

};

class Volume : public jlwuit::Component {

	private:
		int _volume;
		bool _is_muted;

	public:
		Volume():
			jlwuit::Component((1920-800)/2, 1080-5*TEXT_SIZE, 800, 3*TEXT_SIZE)
		{
			_volume = 0;
			_is_muted = true;
		}

		virtual ~Volume()
		{
		}

		virtual void SetVolume(int volume)
		{
			_volume = volume;
			_is_muted = false;

			if (_volume < 0) {
				_volume = 0;
			} else if (_volume > 100) {
				_volume = 100;
			}
		}

		virtual int GetVolume()
		{
			return _volume;
		}

		virtual void SetMuteEnabled(bool b)
		{
			_is_muted = b;
		}

		virtual bool IsMuteEnabled()
		{
			return _is_muted;
		}

		virtual void Paint(jlwuit::Graphics *g) 
		{
			jlwuit::LookAndFeel *laf = jlwuit::LookAndFeel::GetInstance();
			jlwuit::lwuit_region_t bounds = GetBounds();

			int iw = IMAGE_SIZE+IMAGE_SIZE/2,
					ih = IMAGE_SIZE;

			laf->DrawBox(g, NULL, 0, 0, bounds.width, bounds.height);
			laf->DrawProgressBar(g, NULL, _volume, iw+2*GAPX, (bounds.height-TEXT_SIZE/2)/2, bounds.width-iw-3*GAPX, TEXT_SIZE/2);
			
			if (_is_muted == false) {
				laf->DrawImage(g, "volume_on", GAPX, (bounds.height-IMAGE_SIZE)/2, iw, ih);
			} else {
				laf->DrawImage(g, "volume_off", GAPX, (bounds.height-IMAGE_SIZE)/2, iw, ih);
			}
		}

};

class Menu : public jlwuit::Component {

	private:
		std::string _channel_name,
			_event_name;
		int _state,
			_channel_number,
			_event_rate,
			_index_button;
		bool _has_update,
			_is_active;

	public:
		Menu():
			jlwuit::Component(0, -MENU_HEIGHT, 1920, 1080)
		{
			_state = 1; // 0: list; 1: buttons
			_index_button = 0;
			_event_name = DEFAULT_TEXT;
			_channel_name = DEFAULT_TEXT;
			_event_rate = 0;
			_has_update = true;
			_is_active = false;
			_channel_number = -1;

			SetVisible(true);
		}

		virtual ~Menu()
		{
		}

		virtual void SetActivated(bool b) 
		{
			_is_active = b;
			_index_button = 0;
		}

		virtual bool IsActivated() 
		{
			return _is_active;
		}

		virtual bool OnKeyDown(jlwuit::UserEvent *event)
		{
			if (event->GetKeySymbol() == jlwuit::LKS_CURSOR_LEFT) {
				if (_state == 0) {
				} else if (_state == 1) {
					_index_button = (_index_button - 1) % 6;

					if (_index_button < 0) {
						_index_button = 5;
					}
				}
			} else if (event->GetKeySymbol() == jlwuit::LKS_CURSOR_RIGHT) {
				if (_state == 0) {
				} else if (_state == 1) {
					_index_button = (_index_button + 1) % 6;
				}
			} else if (event->GetKeySymbol() == jlwuit::LKS_CURSOR_UP) {
				_state = 0;
			} else if (event->GetKeySymbol() == jlwuit::LKS_CURSOR_DOWN) {
				_state = 1;
			} 

			return true;
		}
		
		virtual void Paint(jlwuit::Graphics *g)
		{
			jlwuit::LookAndFeel *laf = jlwuit::LookAndFeel::GetInstance();
			jlwuit::lwuit_region_t bounds = GetBounds();
			int x = 64,
					wbox = (1920-2*x)/10,
					hbox = MENU_HEIGHT;

			laf->DrawBox(g, NULL, 0, 0, bounds.width, hbox);
			laf->DrawText(g, NULL, "large", "Information Menu", 0, TEXT_SIZE, 1920, TEXT_SIZE);
			
			laf->DrawTextBox(g, NULL, "medium", DEFAULT_TEXT, x+1*(wbox+GAPX), 2*TEXT_SPAN, 4*(wbox+GAPX)-TEXT_SIZE, TEXT_SIZE);

			if (_event_rate == -1) {
				g->SetColor(0xfff0f0f0);
				// g->SetColor(jlwuit::Color::White);
			} else if (_event_rate == 0) {
				g->SetColor(0xff0c9447);
				// g->SetColor(jlwuit::Color::Green);
			} else if (_event_rate == 10) {
				g->SetColor(0xff0f7dc2);
				// g->SetColor(jlwuit::Color::Blue);
			} else if (_event_rate == 12) {
				g->SetColor(0xfff8c411);
				// g->SetColor(jlwuit::Color::Yellow);
			} else if (_event_rate == 14) {
				g->SetColor(0xffe67824);
				// g->SetColor(jlwuit::Color::Orange);
			} else if (_event_rate == 16) {
				g->SetColor(0xffdb2827);
				// g->SetColor(jlwuit::Color::Red);
			} else if (_event_rate == 18) {
				g->SetColor(0xff1d1815);
				// g->SetColor(jlwuit::Color::Black);
			}

			g->FillBevelRectangle(x+5*(wbox+GAPX)-TEXT_SIZE, 2*TEXT_SPAN, TEXT_SIZE, TEXT_SIZE, 4, 4);
			DrawSignal(g, 7, 4, 10, 60, x+5*(wbox+GAPX)+GAPX, 2*TEXT_SPAN, IMAGE_SIZE, TEXT_SIZE);

			int size = TEXT_SIZE/4;

			if (_state == 0) {
				laf->SetType(jlwuit::LST_FOCUS);
			}

			laf->DrawTextBox(g, NULL, "medium", DEFAULT_TEXT, x+1*(wbox+GAPX), 3*TEXT_SPAN, 4*(wbox+GAPX)-GAPX, TEXT_SIZE);
			laf->SetType(jlwuit::LST_NORMAL);

			g->SetColor(jlwuit::Color::Yellow);
			g->FillTriangle(
					x+1*(wbox+GAPX)-GAPX-0*size, 3*TEXT_SPAN+1*size, 
					x+1*(wbox+GAPX)-GAPX-0*size, 3*TEXT_SPAN+3*size, 
					x+1*(wbox+GAPX)-GAPX-1*size, 3*TEXT_SPAN+2*size);
			g->FillTriangle(
					x+5*(wbox+GAPX)+0*size, 3*TEXT_SPAN+1*size, 
					x+5*(wbox+GAPX)+0*size, 3*TEXT_SPAN+3*size, 
					x+5*(wbox+GAPX)+1*size, 3*TEXT_SPAN+2*size);

			laf->DrawImage(g, "data", x+7*(wbox+GAPX), 2*TEXT_SPAN, IMAGE_SIZE/2, IMAGE_SIZE/2);
			laf->DrawImage(g, "hora", x+7*(wbox+GAPX), 3*TEXT_SPAN, IMAGE_SIZE/2, IMAGE_SIZE/2);

			laf->DrawText(g, NULL, "medium", "18/01/2011", x+8*(wbox+GAPX)-wbox/2, 2*TEXT_SPAN-GAPY, wbox, TEXT_SIZE);
			laf->DrawText(g, NULL, "medium", "11:30 am", x+8*(wbox+GAPX)-wbox/2, 3*TEXT_SPAN-GAPY, wbox, TEXT_SIZE);

			if (_has_update == true) {
				laf->DrawImage(g, "update_on", x+6*(wbox+GAPX)+(wbox-IMAGE_SIZE/2)/2, 2*TEXT_SPAN+TEXT_SIZE/2, IMAGE_SIZE/2, IMAGE_SIZE/2);
			} else {
				laf->DrawImage(g, "update_off", x+6*(wbox+GAPX)+(wbox-IMAGE_SIZE/2)/2, 2*TEXT_SPAN+TEXT_SIZE/2, IMAGE_SIZE/2, IMAGE_SIZE/2);
			}
				
			laf->DrawText(g, NULL, "medium", "Update", x+6*(wbox+GAPX), 3*TEXT_SPAN, wbox, TEXT_SIZE);

			std::string rate = "ER";
			
			if (_event_rate == 0) {
				rate = "L";
			} else if (_event_rate == 10) {
				rate = "10";
			} else if (_event_rate == 12) {
				rate = "12";
			} else if (_event_rate == 14) {
				rate = "14";
			} else if (_event_rate == 16) {
				rate = "16";
			} else if (_event_rate == 18) {
				rate = "18";
			}

			laf->DrawText(g, NULL, "large", rate, x+5*(wbox+GAPX)-TEXT_SIZE, 2*TEXT_SPAN, TEXT_SIZE, TEXT_SIZE);
			
			if (_is_active == false) {
				return;
			}

			std::string options[] = {
				"canais_btn",
				"video_btn",
				"audio_btn",
				"interatividade_btn",
				"aplicativos_btn",
				"opcoes_btn",
			};

			int w = 235,
					h = 110;

			x = (1920-6*w)/2;

			if (_state == 0) {
				for (int i=0; i<6; i++) {
					laf->DrawImage(g, options[i], x+i*w, hbox+GAPY, w, h);
				}
			} else {
				for (int i=0; i<6; i++) {
					if (i != _index_button) {
						laf->DrawImage(g, options[i], x+i*w, hbox+GAPY, w, h);
					}
				}

				laf->DrawImage(g, options[_index_button], x+_index_button*w-GAPX, hbox, w+2*GAPX, h+2*GAPY);
			}
		}

};

class UIManager : public jlwuit::Scene {

	private:
		jthread::Mutex _mutex;
		Volume *_volume;
		ChannelInfo *_channel;
		Interactive *_interactive;
		Menu *_menu;
		Information *_info;
		EPG *_epg;
		uint64_t _volume_time,
			_channel_time,
			_info_time,
			_epg_time,
			_menu_time;
		int _menu_dy,
			_interactive_dy;

	private:
		uint64_t GetCurrentTime()
		{
			return jcommon::Date::CurrentTimeMillis();
		}

		uint64_t GetReleaseTime()
		{
			return jcommon::Date::CurrentTimeMillis() + (uint64_t)DEFAULT_DELAY;
		}

		virtual bool OnKeyDown(jlwuit::UserEvent *event)
		{
			if (event->GetKeySymbol() == jlwuit::LKS_MENU) {
				if (_menu_dy == 1 || _menu->IsActivated() == true) {
					HideMenu();
				} else {
					ShowMenu();
				}
			}

			if (event->GetKeySymbol() == jlwuit::LKS_INFO) {
				ShowInformation();
			}

			if (event->GetKeySymbol() == jlwuit::LKS_GUIDE) {
				ShowEPG();
			}

			if (event->GetKeySymbol() == jlwuit::LKS_CHANNEL_UP) {
				NextChannel();
			} else if (event->GetKeySymbol() == jlwuit::LKS_CHANNEL_DOWN) {
				PreviousChannel();
			}

			if (event->GetKeySymbol() == jlwuit::LKS_VOLUME_UP) {
				SetVolume(_volume->GetVolume()+5);
			} else if (event->GetKeySymbol() == jlwuit::LKS_VOLUME_DOWN) {
				SetVolume(_volume->GetVolume()-5);
			}

			if (event->GetKeySymbol() == jlwuit::LKS_MUTE) {
				if (IsMuteEnabled() == false) {
					SetMuteEnabled(true);
				} else {
					SetMuteEnabled(false);
				}
			}

			if (event->GetKeyCode() == '0' ||
					event->GetKeyCode() == '1' ||
					event->GetKeyCode() == '2' ||
					event->GetKeyCode() == '3' ||
					event->GetKeyCode() == '4' ||
					event->GetKeyCode() == '5' ||
					event->GetKeyCode() == '6' ||
					event->GetKeyCode() == '7' ||
					event->GetKeyCode() == '8' ||
					event->GetKeyCode() == '9' ||
					event->GetKeyCode() == '.') {
				SetChannel(event->GetKeyCode());
			} else {
				if (_menu->IsActivated() == true) {
					_menu->OnKeyDown(event);
					_menu_time = GetReleaseTime();
				}
			}

			Repaint();

			return true;
		}

		virtual bool Animated()
		{
			uint64_t current_time = GetCurrentTime();
			bool result = false;

			if (_volume_time != 0LL && _volume_time < current_time) {
				HideVolume();
			}

			if (_channel_time != 0LL && _channel_time < current_time) {
				OnChannelUpdate(_channel->GetName());
			}

			if (_info_time != 0LL && _info_time < current_time) {
				HideInformation();
			}

			if (_epg_time != 0LL && _epg_time < current_time) {
				HideEPG();
			}

			if (_interactive_dy != 0) {
				int y = _interactive->GetY() - _interactive_dy*ANIMATION_STEPS;

				if (_interactive_dy < 0) {
					if (y > GetHeight()) {
						y = GetHeight();
						_interactive_dy = 0;
					}
				} else {
					int pos = GetHeight()-_interactive->GetHeight()-100;

					if (y < pos) {
						y = pos;
						_interactive_dy = 0;
					}
				}

				_interactive->SetLocation(_interactive->GetX(), y);

				result = true;
			}

			if (_menu_dy != 0) {
				int y = _menu->GetY() + _menu_dy*ANIMATION_STEPS;

				if (_menu_dy < 0) {
					_menu_time = 0;

					if (y < -MENU_HEIGHT) {
						y = -MENU_HEIGHT;
						_menu_dy = 0;
					}
					
					_menu->SetActivated(false);
				} else {
					if (y > 0) {
						y = 0;
						_menu_time = GetReleaseTime();
						_menu_dy = 0;

						_menu->SetActivated(true);
					}
				}

				_menu->SetLocation(_menu->GetX(), y);

				result = true;
			} else if (_menu_time != 0LL && _menu_time < current_time) {
				_menu_dy = -1;
			}

			return result;
		}
		
	public:
		UIManager():
			Scene(0, 0, 1920, 1080)
		{
			_menu_dy = 0;
			_interactive_dy = 0;
			
			_volume_time = 0LL;
			_channel_time = 0LL;
			_menu_time = 0LL;

			jlwuit::LookAndFeel::LoadImage("update_on", "images/update_on.png");
			jlwuit::LookAndFeel::LoadImage("update_off", "images/update_off.png");
			jlwuit::LookAndFeel::LoadImage("volume_on", "images/volume_on.png");
			jlwuit::LookAndFeel::LoadImage("volume_off", "images/volume_off.png");
			jlwuit::LookAndFeel::LoadImage("data", "images/icone_data.png");
			jlwuit::LookAndFeel::LoadImage("hora", "images/icone_hora.png");
			jlwuit::LookAndFeel::LoadImage("interatividade_on", "images/interatividade.png");
			jlwuit::LookAndFeel::LoadImage("aplicativos_btn", "images/btn_aplicativos.png");
			jlwuit::LookAndFeel::LoadImage("audio_btn", "images/btn_audio.png");
			jlwuit::LookAndFeel::LoadImage("canais_btn", "images/btn_canais.png");
			jlwuit::LookAndFeel::LoadImage("interatividade_btn", "images/btn_interatividade.png");
			jlwuit::LookAndFeel::LoadImage("opcoes_btn", "images/btn_opcoes.png");
			jlwuit::LookAndFeel::LoadImage("video_btn", "images/btn_video.png");

			Add(_menu = new Menu());
			Add(_channel = new ChannelInfo());
			Add(_interactive = new Interactive());
			Add(_info = new Information());
			Add(_epg = new EPG());
			Add(_volume = new Volume());
			
			_volume->SetVolume(50);

			SetAnimationDelay(100);

			GetStyle()->SetIntegerParam("bg.color", 0x00000000);
		}

		virtual ~UIManager()
		{
			jlwuit::LookAndFeel::ReleaseImage("update_on");
			jlwuit::LookAndFeel::ReleaseImage("update_off");
			jlwuit::LookAndFeel::ReleaseImage("volume_on");
			jlwuit::LookAndFeel::ReleaseImage("volume_off");
			jlwuit::LookAndFeel::ReleaseImage("data");
			jlwuit::LookAndFeel::ReleaseImage("hora");
			jlwuit::LookAndFeel::ReleaseImage("interatividade_on");
			jlwuit::LookAndFeel::ReleaseImage("aplicativos_btn");
			jlwuit::LookAndFeel::ReleaseImage("audio_btn");
			jlwuit::LookAndFeel::ReleaseImage("canais_btn");
			jlwuit::LookAndFeel::ReleaseImage("interatividade_btn");
			jlwuit::LookAndFeel::ReleaseImage("opcoes_btn");
			jlwuit::LookAndFeel::ReleaseImage("video_btn");
		}

		virtual void SetVolume(int volume)
		{
			jthread::AutoLock lock(&_mutex);

			_volume->SetMuteEnabled(false);
			_volume->SetVolume(volume);
			_volume->SetVisible(true);
			_volume_time = GetReleaseTime();
		}

		virtual void SetMuteEnabled(bool b)
		{
			_volume->SetMuteEnabled(b);
			_volume->SetVisible(true);
			_volume_time = GetReleaseTime();
		}

		virtual bool IsMuteEnabled()
		{
			return _volume->IsMuteEnabled();
		}

		virtual void HideVolume()
		{
			jthread::AutoLock lock(&_mutex);

			_volume->SetVisible(false);
			_volume_time = 0LL;
		}

		virtual void SetChannel(char key)
		{
			jthread::AutoLock lock(&_mutex);

			HideMenu();

			_channel->SetVisible(true);
			_channel->SetChannel(key);
			_channel_time = GetReleaseTime();
		}

		virtual void SetChannel(std::string channel)
		{
			jthread::AutoLock lock(&_mutex);

			HideMenu();

			_channel->SetVisible(true);
			_channel->SetChannel(channel);
			_channel_time = GetReleaseTime();
		}

		virtual void NextChannel() 
		{
			SetChannel(-1);
		}

		virtual void PreviousChannel() 
		{
			SetChannel(-1);
		}

		virtual void HideChannel()
		{
			jthread::AutoLock lock(&_mutex);

			_channel->SetVisible(false);
			_channel->SetChannel("");
			_channel_time = 0LL;
		}

		virtual void OnChannelUpdate(std::string channel)
		{
			HideChannel();

			// Toast::ShowMessage("Channel: " + channel);
		}

		virtual void ShowInformation()
		{
			jthread::AutoLock lock(&_mutex);

			HideEPG();

			_info->SetVisible(true);
			_info_time = GetReleaseTime();
		}

		virtual void HideInformation()
		{
			jthread::AutoLock lock(&_mutex);

			_info->SetVisible(false);
			_info_time = 0LL;
		}

		virtual void ShowEPG()
		{
			jthread::AutoLock lock(&_mutex);

			HideInformation();
			HideMenu();
			HideChannel();
			
			_epg->SetVisible(true);
			_epg_time = GetReleaseTime();
		}

		virtual void HideEPG()
		{
			jthread::AutoLock lock(&_mutex);

			_epg->SetVisible(false);
			_epg_time = 0LL;
		}

		virtual void ShowMenu()
		{
			jthread::AutoLock lock(&_mutex);

			HideChannel();
			HideEPG();

			_menu_dy = 1;
		}

		virtual void HideMenu()
		{
			jthread::AutoLock lock(&_mutex);

			_menu_dy = -1;
		}

		virtual void ShowInteractive()
		{
			jthread::AutoLock lock(&_mutex);

			_interactive_dy = 1;
		}

		virtual void HideInteractive()
		{
			jthread::AutoLock lock(&_mutex);

			_interactive_dy = -1;
		}

};

int main (int argc, char **argv)
{
	jlwuit::Implementation::GetInstance()->Initialize();

	UIManager manager;

	manager.Show();

	manager.SetChannel("7.1 Globo High Definition");
	sleep(2);
	manager.ShowInteractive();
	sleep(2);
	manager.HideInteractive(); 

	sleep(1000);

  return 0;
}

