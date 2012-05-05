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
#include "font.h"
#include "component.h"
#include "image.h"
#include "imageio.h"

class Dump : public jlwuit::Component {

	private:
		jlwuit::Image *_off;
		jlwuit::Font *_sfont;

	public:
		Dump():
			jlwuit::Component(0, 0, 320, 240)
		{
			_off = jlwuit::Image::CreateImage(GetWidth(), GetHeight(), jlwuit::LPF_ARGB);
			_sfont = jlwuit::Font::CreateFont("./comic.ttf", jlwuit::LFA_NORMAL, 20);
		}

		virtual ~Dump()
		{
			delete _sfont;
			delete _off;
		}

		virtual void Paint(jlwuit::Graphics *g) 
		{
			jlwuit::Component::Paint(g);

			g->SetColor(jlwuit::Color::Blue);
			g->FillRectangle(10, 10, 50, 50);
			g->DrawImage("images/teste.png", 20, 20, 50, 50);
		}
		
		virtual bool Render(std::string filename) 
		{
			jlwuit::Graphics *g = _off->GetGraphics();
			jlwuit::lwuit_point_t t = g->Translate();

			g->Translate(-t.x, -t.y);
			g->ReleaseClip();

			Paint(_off->GetGraphics());

			jlwuit::ImageIO *io = new jlwuit::ImageIO(filename, jlwuit::LPF_ARGB);
			jlwuit::lwuit_size_t size = _off->GetSize();
			uint32_t *rgb = NULL;

			g->GetRGB(&rgb, 0, 0, size.width, size.height, size.width);
			io->Encode(rgb, size.width, size.height);

			return true;
		}

};

int main()
{
	jlwuit::Implementation::GetInstance()->Initialize();

	Dump app;

	app.Render("/tmp/frame.png");

	sleep(100000);

	return 0;
}
