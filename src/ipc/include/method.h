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
#ifndef LWUIT_METHOD_H
#define LWUIT_METHOD_H

#include "parammapper.h"

#include <string>
#include <map>

namespace jlwuit {

class Method : public ParamMapper {

	private:
		std::string _name;

	public:
		/**
		 * \Constructor.
		 *
		 */
		Method(std::string name);

		/**
		 * \brief Destructor.
		 *
		 */
		virtual ~Method();

		/**
		 * \brief
		 *
		 */
		virtual void Initialize(std::string str);

		/**
		 * \brief
		 *
		 */
		virtual std::string GetName();

		/**
		 * \brief
		 *
		 */
		virtual void SetName(std::string name);

		/**
		 * \brief
		 *
		 */
		virtual std::string what();
		
};

}

#endif
