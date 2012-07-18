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
#include "averageimagefilter.h"
#include "brightnessimagefilter.h"
#include "bwimagefilter.h"
#include "contrastimagefilter.h"
#include "gammaimagefilter.h"
#include "gheimagefilter.h"
#include "goldenimagefilter.h"
#include "grayimagefilter.h"
#include "heimagefilter.h"
#include "lheimagefilter.h"
#include "metalicimagefilter.h"
#include "negativeimagefilter.h"
#include "sharpimagefilter.h"
#include "silverimagefilter.h"

#include <stdio.h>

#define GAPX		16
#define GAPY		8

#define TEXT_SIZE			60
#define TEXT_SPAN			(TEXT_SIZE+GAPY)

class FilterTest : public jlwuit::Scene {

	private:
		std::map<std::string, jlwuit::Filter *> _filters;
		jthread::Mutex _mutex;
		jlwuit::Image *_original,
			*_modified;
		jlwuit::lwuit_size_t isize;
		int _current;

	public:
		FilterTest():
			jlwuit::Scene(0, 0, 1920, 1080)
		{
			_current = 0;

			_original = jlwuit::Image::CreateImage("images/teste.png");
			_modified = jlwuit::Image::CreateImage(_original);
	
			isize = _modified->GetSize();

			_filters["Average"] = new jlwuit::AverageImageFilter();
			_filters["Brightness"] = new jlwuit::BrightnessImageFilter();
			_filters["Black & White"] = new jlwuit::BWImageFilter();
			_filters["Contrast"] = new jlwuit::ContrastImageFilter();
			_filters["Gamma"] = new jlwuit::GammaImageFilter();
			_filters["Global Histogram Eq"] = new jlwuit::GHEImageFilter();
			_filters["Golden"] = new jlwuit::GoldenImageFilter();
			_filters["Gray"] = new jlwuit::GrayImageFilter();
			_filters["Histogram Eq"] = new jlwuit::HEImageFilter();
			_filters["Local Histogram Eq"] = new jlwuit::LHEImageFilter();
			_filters["Metalic"] = new jlwuit::MetalicImageFilter();
			_filters["Negative"] = new jlwuit::NegativeImageFilter();
			_filters["Sharp"] = new jlwuit::SharpImageFilter();
			_filters["Silver"] = new jlwuit::SilverImageFilter();
				
			for (std::map<std::string, jlwuit::Filter *>::iterator i=_filters.begin(); i!=_filters.end(); i++) {
				i->second->SetEnabled(false);
			}
		}

		virtual ~FilterTest()
		{
		}

		virtual bool Animate()
		{
			return false;
		}

		virtual bool OnKeyDown(jlwuit::UserEvent *event)
		{
			jthread::AutoLock lock(&_mutex);

			if (event->GetKeySymbol() == jlwuit::LKS_ENTER) {
				int k = 0;
				
				for (std::map<std::string, jlwuit::Filter *>::iterator i=_filters.begin(); i!=_filters.end(); i++, k++) {
					if (k == _current) {
						if (i->second->IsEnabled() == false) {
							i->second->SetEnabled(true);
						} else {
							i->second->SetEnabled(false);
						}
					}
				}

				uint32_t *rgb = NULL;

				_original->GetRGB(&rgb, 0, 0, isize.width, isize.height);

				for (std::map<std::string, jlwuit::Filter *>::iterator i=_filters.begin(); i!=_filters.end(); i++) {
					i->second->Transform((uint8_t *)rgb, isize.width, isize.height);
				}

				if (_modified != NULL) {
					delete _modified;
				}

				_modified = jlwuit::Image::CreateImage(rgb, isize.width, isize.height);

				delete [] rgb;
			} else if (event->GetKeySymbol() == jlwuit::LKS_CURSOR_UP) {
				_current = _current - 1;

				if (_current < 0) {
					_current = 0;
				}
			} else if (event->GetKeySymbol() == jlwuit::LKS_CURSOR_DOWN) {
				_current = _current + 1;

				if (_current >= (int)_filters.size()) {
					_current = _filters.size()-1;
				}
			}
				
			Repaint();

			return true;
		}

		virtual void Paint(jlwuit::Graphics *g)
		{
			jthread::AutoLock lock(&_mutex);

			jlwuit::LookAndFeel *laf = jlwuit::LookAndFeel::GetInstance();
			jlwuit::lwuit_region_t bounds = GetBounds();

			int k = 0;

			for (std::map<std::string, jlwuit::Filter *>::iterator i=_filters.begin(); i!=_filters.end(); i++, k++) {
				laf->SetType(jlwuit::LST_NORMAL);

				if (i->second->IsEnabled() == true) {
					laf->SetType(jlwuit::LST_SELECT);
				}
				
				laf->DrawTextBox(g, GetStyle(), "medium", i->first, GAPX, GAPY+(k+1)*(TEXT_SPAN), 5*TEXT_SIZE, TEXT_SIZE);

				if (_current == k) {
					laf->SetType(jlwuit::LST_FOCUS);
					laf->DrawTextBox(g, GetStyle(), "medium", i->first, GAPX, GAPY+(k+1)*(TEXT_SPAN), 5*TEXT_SIZE, TEXT_SIZE);
				}
			}
				
			g->DrawImage(_modified, (bounds.width-5*TEXT_SIZE-isize.width)/2+5*TEXT_SIZE, (bounds.height-isize.height)/2);
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
