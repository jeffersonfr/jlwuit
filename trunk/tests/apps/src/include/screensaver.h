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
#ifndef LWUIT_SCREENSAVER_H
#define LWUIT_SCREENSAVER_H

#include "dialog.h"
#include "scene.h"
#include "jthread.h"

#include <string>

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

class ScreenSaver : public jlwuit::Dialog, public jthread::Thread {

	private:
		int _time;
		int _logo_x;
		int _logo_y;
		int _logo_dx;
		int _logo_dy;
		bool _is_released;

	public:
		ScreenSaver(jlwuit::Scene *scene);
		
		virtual ~ScreenSaver();

		virtual void Resume();
		virtual void Release();

		virtual void Paint(jlwuit::Graphics *g);
		virtual void Run();

};

#endif
