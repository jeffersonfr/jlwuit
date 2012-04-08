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
#ifndef LWUIT_APPMANAGER_H
#define LWUIT_APPMANAGER_H

#include "proxy.h"

#include <string>
#include <vector>

namespace jlwuit {

class AppDatabase {

	private:
		/** \brief Comment */
		static AppDatabase *_instance;

	private:
		/** \brief Comment */
		std::vector<jlwuit::Attributes *> _applications;

	private:
		/**
		 * \brief
		 *
		 */
		virtual void Initialize();

	public:
		/**
		 * \brief Construtor default.
		 *
		 */
		AppDatabase();

		/**
		 * \brief Destrutor virtual.
		 *
		 */
		virtual ~AppDatabase();

		/**
		 * \brief
		 *
		 */
		static AppDatabase * GetInstance();

		/**
		 * \brief
		 *
		 */
		virtual void Update();

		/**
		 * \brief
		 *
		 */
		virtual std::vector<Attributes *> & GetApplications();

		/**
		 * \brief
		 *
		 */
		virtual Attributes * GetApplication(std::string id);

		/**
		 * \brief
		 *
		 */
		virtual void AddApplication(Attributes *attr);

		/**
		 * \brief
		 *
		 */
		virtual void RemoveApplication(Attributes *attr);

		/**
		 * \brief
		 *
		 */
		virtual Proxy * GetProxy(std::string id);

		/**
		 * \brief
		 *
		 */
		virtual Proxy * GetProxy(Attributes *attr);

};

}

#endif
