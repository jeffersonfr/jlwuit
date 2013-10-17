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
#ifndef LWUIT_CALC_H
#define LWUIT_CALC_H

#include "scene.h"

#include <string>
#include <vector>

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

class Display : public jlwuit::Component {

	private:

	public:
		/**
		 * \brief
		 *
		 */
		Display(int x, int y, int width, int height);
		
		/**
		 * \brief
		 *
		 */
		virtual ~Display();

		/**
		 * \brief
		 *
		 */
		virtual void SetText(std::string text);
		
		/**
		 * \brief
		 *
		 */
		virtual void SetOperation(std::string text);
		
		/**
		 * \brief
		 *
		 */
		virtual void Clear();

		/**
		 * \brief
		 *
		 */
		virtual void Paint(jlwuit::Graphics *g);

};

class Calc : public jlwuit::Scene {

	private:
		/** \brief */
		jthread::Mutex _mutex;
		/** \brief */
		std::string _number0;
		/** \brief */
		std::string _number1;
		/** \brief */
		std::string _operation;
		/** \brief */
		std::string _text;
		/** \brief */
		int _index;
		/** \brief */
		int _state;

	public:
		/**
		 * \brief
		 *
		 */
		Calc(int x, int y);
		
		/**
		 * \brief
		 *
		 */
		virtual ~Calc();
		
		/**
		 * \brief
		 *
		 */
		void Process(std::string type);
		
		/**
		 * \brief
		 *
		 */
		virtual bool OnKeyDown(jlwuit::UserEvent *event);
		
		/**
		 * \brief
		 *
		 */
		virtual void Paint(jlwuit::Graphics *g);
		
};

#endif 
