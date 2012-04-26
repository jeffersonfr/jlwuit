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
#ifndef LWUIT_PREFERENCEDOCUMENT_H
#define LWUIT_PREFERENCEDOCUMENT_H

#include "element.h"

#include <vector>
#include <string>

namespace jlwuit {

class Preferences;

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class Document {

	friend class Preferences;

	private:
		/** \brief */
		std::vector<Element *> _elements;
		/** \brief Comment */
		std::string _name;

	public:
		/**
		 * \brief Construtor default.
		 *
		 */
		Document(std::string name);

		/**
		 * \brief Destrutor virtual.
		 *
		 */
		virtual ~Document();

		/**
		 * \brief 
		 *
		 */
		virtual std::string GetName();

		/**
		 * \brief
		 *
		 */
		virtual void AddElement(Element *e);

		/**
		 * \brief
		 *
		 */
		virtual void RemoveElementByID(std::string id);

		/**
		 * \brief
		 *
		 */
		virtual void RemoveElementByIndex(int index);
		/**
		 * \brief
		 *
		 */
		virtual void RemoveElements();

		/**
		 * \brief
		 *
		 */
		virtual Element * GetElementByID(std::string id);

		/**
		 * \brief
		 *
		 */
		virtual Element * GetElementByIndex(int index);

		/**
		 * \brief
		 *
		 */
		virtual std::vector<Element *> GetElements();

};

}

#endif

