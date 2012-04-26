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
		int _gap_x;
		int _gap_y;
		int _index;
		int _longpress_timeout;
		bool _is_mouse_pressed;

	public:
		SlideComponent(int x, int y, int width, int height):
			jlwuit::Component(x, y, width, height)
		{
			_index = 0;
			_level = 1.0;
			_gap_x = 16;
			_gap_y = 64;

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

			for (std::vector<std::string>::iterator i=_images.begin(); i!=_images.end(); i++) {
				jlwuit::LookAndFeel::LoadImage((*i), "images/" + (*i) + ".png");
			}

			SetVisible(true);
		}

		virtual ~SlideComponent()
		{
			for (std::vector<std::string>::iterator i=_images.begin(); i!=_images.end(); i++) {
				jlwuit::LookAndFeel::ReleaseImage((*i));
			}
		}

		virtual int GetLevel() {
			return _level;
		}

		virtual void SetLvel(int level) {
			_level = level;
		}

		virtual int GetGapX() {
			return _gap_x;
		}

		virtual void SetGapX(int gap) {
			_gap_x = gap;
		}

		virtual int GetGapY() {
			return _gap_y;
		}

		virtual void SetGapY(int gap) {
			_gap_y = gap;
		}

		virtual bool Animated()
		{
			if (_is_mouse_pressed == true) {
				_longpress_timeout = _longpress_timeout - 1;

				if (_longpress_timeout == 0) {
					OnMouseLongPress(NULL);
				}
			
				return true;
			}

			return false;
		}

		virtual bool OnMouseLongPress(jlwuit::UserEvent *event)
		{
			jlwuit::Toast::Create((jlwuit::Scene *)GetParent())->SetMessage("Long Press")->Show(); 

			return false;
		}

		virtual bool OnMousePress(jlwuit::UserEvent *event)
		{
			_is_mouse_pressed = true;
			_longpress_timeout = 2;

			return true;
		}

		virtual bool OnMouseRelease(jlwuit::UserEvent *event)
		{
			_is_mouse_pressed = false;

			return true;
		}

		virtual bool OnKeyDown(jlwuit::UserEvent *event)
		{
			if (event->GetKeySymbol() == jlwuit::LKS_CURSOR_LEFT) {
				_index = _index - 1;

				if (_index < 0) {
					_index = _images.size()-1;
				}
			} else if (event->GetKeySymbol() == jlwuit::LKS_CURSOR_RIGHT) {
				_index = _index + 1;

				if (_index >= (int)_images.size()) {
					_index = 0;
				}
			}
				
			Repaint();

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

			int limit = _images.size()-1,
					limit_r = frames_length/2,
					limit_l = frames_length/2;

			if (limit > frames_length) {
				limit = frames_length;
			}

			frames[frames_length/2] = _index;

			for (int i=0; i<=limit_r; i++) {
				frames[frames_length/2+i] = (_index+i)%_images.size();
			}
			
			for (int i=0; i<=limit_l; i++) {
				int index = _index-i;

				if (index < 0) {
					index = index + _images.size();
				}

				frames[frames_length/2-i] = index%_images.size();
			}
		}

		virtual void Paint(jlwuit::Graphics *g)
		{
			jlwuit::LookAndFeel *laf = jlwuit::LookAndFeel::GetInstance();
			jlwuit::lwuit_region_t bounds = GetBounds();

			int factor = 2+1; // add more two images (left, right)
			int frames_length = 2*factor+1,
					frames[frames_length];
			int framew = bounds.width/(frames_length-2)-_gap_x*(frames_length-2-1),
					frameh = bounds.height;
			int dx = framew+_gap_x,
					dy;

			GetFrames(frames, frames_length);

			g->SetClip(0, 0, bounds.width, bounds.height);
			g->SetColor(jlwuit::Color::Blue);
			g->FillRectangle(0, 0, 1000, 1000);
			
			for (int i=0; i<factor; i++) {
				int idx1 = i,
						idx2 = frames_length-i-1;

				dy = exp(_level*(factor-i+1));

				if (frames[idx1] >= 0) {
					laf->DrawImage(g, _images[frames[idx1]], idx1*dx-dx, dy+exp(-i)*_gap_y, framew, frameh-2*dy);
				}

				if (frames[idx2] >= 0) {
					laf->DrawImage(g, _images[frames[idx2]], idx2*dx-dx, dy+exp(-i)*_gap_y, framew, frameh-2*dy);
				}
			}
			
			int idx = frames_length/2;

			dy = exp(factor-idx+1);
			
			if (frames[idx] >= 0) {
				laf->DrawImage(g, _images[frames[idx]], idx*dx-dx, dy, framew, frameh-2*dy);
			}
			
			// draw center image

			g->ReleaseClip();
		}

};

class SlideTest : public jlwuit::Scene {

	private:
		SlideComponent *_slide;

	public:
		SlideTest():
			jlwuit::Scene(0, 0, 1920, 1080)
		{
			Add(_slide = new SlideComponent(100, 100, 640, 240));
		}

		virtual ~SlideTest()
		{
			delete _slide;
		}

		virtual bool Animated()
		{
			return _slide->Animated();
		}

		virtual bool OnKeyDown(jlwuit::UserEvent *event)
		{
			return _slide->OnKeyDown(event);
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
