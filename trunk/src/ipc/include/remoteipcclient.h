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
#ifndef LWUIT_REMOTEIPCCLIENT_H
#define LWUIT_REMOTEIPCCLIENT_H

#include "ipcclient.h"

namespace jlwuit {

/**
 * \brief
 *
 * \author Jeff Ferr
 */
class RemoteIPCClient : public IPCClient {

	private:
		/** \brief */
		std::string _host;
		/** \brief */
		int _port;

	public:
		/**
		 * \Constructor.
		 *
		 */
		RemoteIPCClient(std::string host, int port);

		/**
		 * \brief Destructor.
		 *
		 */
		virtual ~RemoteIPCClient();

		/**
		 * \brief
		 *
		 */
		virtual Response * CallMethod(Method *method);

};

}

#endif
