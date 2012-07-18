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
#include "toast.h"

#include <stdio.h>
#include <math.h>

#define GAPX		16
#define GAPY		16

#define IMAGE_SIZE		128

class SlideComponent : public jlwuit::Component {

	private:
		std::vector<std::string> _images;
		double _level;
		int _index;
		int _next_index;
		int _offset;
		int _factor;
		int _longpress_timeout;
		int _step;
		bool _is_mouse_pressed;
		std::string _state;

	public:
		SlideComponent(int x, int y, int width, int height):
			jlwuit::Component(x, y, width, height)
		{
			_step = 32;
			_index = 0;
			_factor = 3;
			_offset = 0;

			_images.push_back("chat");
			_images.push_back("favorite");
			_images.push_back("interactive");
			_images.push_back("mms");
			_images.push_back("record");
			_images.push_back("reload");
			_images.push_back("rss");
			_images.push_back("share");
			_images.push_back("sms");
			_images.push_back("star");
			_images.push_back("twitter");
			_images.push_back("upload");
			/*
			*/

			for (std::vector<std::string>::iterator i=_images.begin(); i!=_images.end(); i++) {
				jlwuit::LookAndFeel::LoadImage((*i), "images/" + (*i) + ".png");
			}
				
			jlwuit::LookAndFeel::LoadImage("square", "images/square.png");

			SetVisible(true);
		}

		virtual ~SlideComponent()
		{
			for (std::vector<std::string>::iterator i=_images.begin(); i!=_images.end(); i++) {
				jlwuit::LookAndFeel::ReleaseImage((*i));
			}
		}

		virtual bool OnMouseLongPress(jlwuit::UserEvent *event)
		{
			jlwuit::Toast::Create((jlwuit::Scene *)GetParent())->SetMessage("Long Press")->Show(); 

			return false;
		}

		virtual bool OnMousePress(jlwuit::UserEvent *event)
		{
			_is_mouse_pressed = true;
			_longpress_timeout = 20;

			return true;
		}

		virtual bool OnMouseRelease(jlwuit::UserEvent *event)
		{
			_is_mouse_pressed = false;

			return true;
		}

		virtual bool Animate()
		{
			jlwuit::lwuit_size_t items_size = GetItemsSize();

			std::string state = _state;
			bool flag = false;

			if (_state == "forward") {
				_offset = _offset - _step;

				if (_offset < -items_size.width) {
					_state = "";
					_offset = 0;
					_index = _next_index;
				}
	
				flag = true;
			} else if (_state == "backward") {
				_offset = _offset + _step;
				
				if (_offset > items_size.width) {
					_state = "";
					_offset = 0;
					_index = _next_index;
				}
					
				flag = true;
			} else if (_state == "back") {
				if (_offset <= 0) {
					_offset = _offset + _step;

					if (_offset >= 0) {
						_offset = 0;
						_state = "";
					}
				} else {
					_offset = _offset - _step;

					if (_offset <= 0) {
						_offset = 0;
						_state = "";
					}
				}

				flag = true;
			}

			if (_step > 32) {
				_step = _step - 4;

				if (_state == "") {
					if (state == "backward") {
						Previous();
					} else if (state == "forward") {
						Next();
					} else if (state == "back") {
						// TODO:: depois de ir para frente, segurar <direcao contraria> e a lista trava
					}
				}
			}

			return flag;
		}

		virtual void Previous()
		{
			if (_state == "forward") {
				_next_index = _index;
				_state = "back";
			} else {
				if (_state == "") {
					_offset = 0;
				}

				_next_index = _index - 1;

				if (_next_index < 0) {
					_next_index = 0; // _images.size()-1;
					_state = "";
					_offset = 0;
				} else {
					_state = "backward";
				}
			}
		}

		virtual void Next()
		{
			if (_state == "backward") {
				_next_index = _index;
				_state = "back";
			} else {
				if (_state == "") {
					_offset = 0;
				}

				_next_index = _index + 1;

				if (_next_index >= (int)_images.size()) {
					_next_index = (int)_images.size()-1; // 0;

					if (_next_index < 0) {
						_next_index = 0;
					}

					_state = "";
					_offset = 0;
				} else {
					_state = "forward";
				}
			}
		}

		virtual bool OnKeyDown(jlwuit::UserEvent *event)
		{
			if (event->GetKeySymbol() == jlwuit::LKS_CURSOR_LEFT) {
				Previous();
			} else if (event->GetKeySymbol() == jlwuit::LKS_CURSOR_RIGHT) {
				Next();
			}
				
			return true;
		}

		virtual bool OnKeyPress(jlwuit::UserEvent *event)
		{
			if ((event->GetKeySymbol() == jlwuit::LKS_CURSOR_LEFT || event->GetKeySymbol() == jlwuit::LKS_CURSOR_RIGHT)) {
				_step = _step + 8;

				if (_step > 64) {
					_step = 64;
				}

				return true;
			}

			return false;
		}

		virtual bool OnKeyUp(jlwuit::UserEvent *event)
		{
			return true;
		}

		virtual void GetFrames(int *frames, int frames_length)
		{
			for (int i=0; i<frames_length; i++) {
				frames[i] = -1;
			}
			
			if ((frames_length%2) == 0 || _images.size() == 0) {
				return;
			}

			int climit = frames_length/2,
					rlimit = climit,
					llimit = climit;

			if (rlimit > (_images.size()-_index-1)) {
				rlimit = _images.size()-_index-1;
			}

			if (llimit > _index) {
				llimit = _index;
			}

			frames[climit] = _index;

			for (int i=1; i<=rlimit; i++) {
				frames[climit+i] = (_index+i)%_images.size();
			}
			
			for (int i=1; i<=llimit; i++) {
				int index = _index-i;

				if (index < 0) {
					index = index + _images.size();
				}

				frames[climit-i] = index%_images.size();
			}
		}

		virtual void SetFactor(int factor)
		{
			_factor = factor;
		}

		virtual int GetFactor()
		{
			return _factor;
		}

		virtual jlwuit::lwuit_size_t GetItemsSize()
		{
			jlwuit::lwuit_region_t bounds = GetBounds();

			struct jlwuit::lwuit_size_t t;

			t.width = (bounds.width-2*_factor*GAPX)/(2*_factor+1);
			t.height = bounds.height-2*GAPY;

			return t;
		}

		virtual void Paint(jlwuit::Graphics *g)
		{
			jlwuit::LookAndFeel *laf = jlwuit::LookAndFeel::GetInstance();
			jlwuit::lwuit_region_t bounds = GetBounds();

			jlwuit::lwuit_size_t items_size = GetItemsSize();
			int frames_length = 2*(_factor+1)+1,
					frames[frames_length];
			int dx = (_factor/2)*(items_size.width+GAPX),
					dw = (items_size.width+GAPX)*((_factor+1)/2);

			GetFrames(frames, frames_length);

			g->SetClip(0, 0, bounds.width, bounds.height);
			g->FillRectangle(0, 0, bounds.width, bounds.height);
			
			laf->DrawImage(g, "background", 0, 0, bounds.width, bounds.height);
			
			if (_images.size() == 0) {
				return;
			}

			for (int i=0; i<frames_length; i++) {
				int ix = i-_factor+(_factor-1)/2;

				if (frames[i] >= 0) {
					laf->DrawImage(g, _images[frames[i]], ix*(items_size.width+GAPX)+dx+_offset, GAPY, items_size.width, items_size.height);
				}
			}
					
			g->ReleaseClip();

			laf->DrawImage(g, "square", dx+dw-GAPX, 0, items_size.width+2*GAPX, items_size.height+2*GAPY);
		}

};

class SlideTest : public jlwuit::Scene {

	private:
		SlideComponent *_slide;

	public:
		SlideTest():
			jlwuit::Scene(0, 0, 1920, 1080)
		{
			SetAnimationDelay(100);

			Add(_slide = new SlideComponent(100, 100, 1280, 240));
		}

		virtual ~SlideTest()
		{
			delete _slide;
		}

		virtual bool Animate()
		{
			return _slide->Animate();
		}

		virtual bool OnKeyDown(jlwuit::UserEvent *event)
		{
			return _slide->OnKeyDown(event);
		}

		virtual bool OnKeyPress(jlwuit::UserEvent *event)
		{
			return _slide->OnKeyPress(event);
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
