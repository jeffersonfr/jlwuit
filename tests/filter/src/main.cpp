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
#include "filtergroup.h"
#include "bwimagefilter.h"

#include <stdio.h>

#define GAPX		8
#define GAPY		8

class FilterTest : public jlwuit::Scene {

	private:
		jlwuit::Image *_image;
		int _img_x,
			_img_y;

	public:
		FilterTest():
			jlwuit::Scene(0, 0, 1920, 1080)
		{
			_image = jlwuit::Image::CreateImage("images/teste.png");
			
			// INFO:: get pixels from image
			jlwuit::lwuit_size_t isize = _image->GetSize();
			uint32_t *rgb = NULL;
			
			_image->GetRGB(&rgb, 0, 0, isize.width, isize.height);
			
			delete _image;

			// INFO:: init filter
			jlwuit::FilterGroup filter;
			
			filter.AddFilter(new jlwuit::BWImageFilter());
			
			filter.Transform((uint8_t *)rgb, isize.width*isize.height*4);
			
			// INFO:: filtered image
			_image = jlwuit::Image::CreateImage(rgb, isize.width, isize.height);
		}

		virtual ~FilterTest()
		{
			delete _image;
			_image = NULL;
		}

		virtual bool Animated()
		{
			return true;
		}

		virtual void Paint(jlwuit::Graphics *g)
		{
			jlwuit::LookAndFeel *laf = jlwuit::LookAndFeel::GetInstance();
			jlwuit::lwuit_region_t bounds = GetBounds();
			jlwuit::lwuit_size_t isize = _image->GetSize();

			g->DrawImage(_image, (bounds.width-isize.width)/2, (bounds.height-isize.height)/2);
		}

};

int main()
{
	jlwuit::Implementation::GetInstance()->Initialize();

	FilterTest app;

	app.Show();

	sleep(100000);

	return 0;
}
