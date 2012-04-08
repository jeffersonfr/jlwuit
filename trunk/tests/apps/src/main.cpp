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

#include "calc.h"
#include "mp3player.h"
#include "mp4player.h"
#include "photoslider.h"

#include <stdio.h>

#define GAPX		16
#define GAPY		16

#define MARGIN_X	128
#define MARGIN_Y	128

#define TEXT_SIZE	80
#define TEXT_SPAN	(TEXT_SIZE+GAPY)

class AppSwitch : public jlwuit::Scene {

	public:
		/**
		 * \brief
		 *
		 */
		AppSwitch():
			jlwuit::Scene(0, 0, 1920, 1080)
		{
			GetStyle()->SetMargin(16, 16, 0, 0);
		}
		
		/**
		 * \brief
		 *
		 */
		virtual ~AppSwitch()
		{
		}
		
		/**
		 * \brief
		 *
		 */
		virtual bool OnKeyDown(jlwuit::UserEvent *event)
		{
			if (jlwuit::Scene::OnKeyDown(event) == true) {
				return true;
			}

			if (event->GetKeySymbol() == jlwuit::LKS_1) {
				StartActivity(new jlwuit::Calc(100, 100));

				return true;
			} else if (event->GetKeySymbol() == jlwuit::LKS_2) {
				StartActivity(new jlwuit::PhotoSlider());

				return true;
			} else if (event->GetKeySymbol() == jlwuit::LKS_3) {
				StartActivity(new jlwuit::MP3Player());

				return true;
			} else if (event->GetKeySymbol() == jlwuit::LKS_4) {
				StartActivity(new jlwuit::MP4Player());

				return true;
			}

			return false;
		}
		
		/**
		 * \brief
		 *
		 */
		virtual void Paint(jlwuit::Graphics *g)
		{
			jlwuit::LookAndFeel *laf = jlwuit::LookAndFeel::GetInstance();
			jlwuit::lwuit_region_t bounds = GetBounds();

			jlwuit::Style *s = GetStyle();
			int x = bounds.x+MARGIN_X,
					y = bounds.y+MARGIN_Y,
					w = bounds.width-2*MARGIN_X,
					h = bounds.height-2*MARGIN_Y;

			laf->DrawBox(g, s, x, y, w, h);
			laf->DrawTextBox(g, s, "medium", "1. Calculator", x+GAPX, y+GAPY+0*TEXT_SPAN, w-2*GAPX, TEXT_SIZE, jlwuit::LHA_LEFT);
			laf->DrawTextBox(g, s, "medium", "2. Photo Viewer", x+GAPX, y+GAPY+1*TEXT_SPAN, w-2*GAPX, TEXT_SIZE, jlwuit::LHA_LEFT);
			laf->DrawTextBox(g, s, "medium", "3. Audio Player", x+GAPX, y+GAPY+2*TEXT_SPAN, w-2*GAPX, TEXT_SIZE, jlwuit::LHA_LEFT);
			laf->DrawTextBox(g, s, "medium", "4. Video Player", x+GAPX, y+GAPY+3*TEXT_SPAN, w-2*GAPX, TEXT_SIZE, jlwuit::LHA_LEFT);
		}
		
};

int main (int argc, char **argv)
{
	jlwuit::Implementation::GetInstance()->Initialize();

	AppSwitch appSwitch;
	appSwitch.Show();
	
	sleep(1000);

  return 0;
}

