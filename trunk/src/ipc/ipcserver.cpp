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
#include "ipcserver.h"
#include "ipchelper.h"
#include "ipcexception.h"
#include "response.h"
#include "jsocketexception.h"

namespace jlwuit {

IPCServer::IPCServer(std::string id)
{
	try {
		_server = new jsocket::LocalServerSocket(std::string("/tmp/") + id + ".socket");
	} catch (jsocket::SocketException &e) {
		throw IPCException("Cannot create ipc server.");
	}
}

IPCServer::~IPCServer()
{
	_server->Close();
	delete _server;
}

void IPCServer::WaitCall(RemoteCallListener *listener)
{
	if (listener == NULL) {
		return;
	}

	jsocket::LocalSocket *client = _server->Accept();

	char buffer[65535];
	int r,
			index = 0;

	try {
		while ((r = client->Receive(buffer+index, 1500, 100)) > 0) {
			index = index + r;

			if (r < 1500) {
				break;
			}
		}
	} catch (jcommon::Exception &e) {
	}

	Method *method = new Method("null");
	
	method->Initialize(buffer);

	Response *response = listener->ProcessCall(method);
	
	if (response != NULL) {
		std::string encoded = IPCHelper::Encode(response->what());
		const char *buffer = encoded.c_str();
		int length = encoded.size();
		int r,
				index = 0,
				size = 1500;

		try {
			while (length > 0) {
				r = client->Send(buffer+index, size);

				if (r <= 0) {
					break;
				}

				length = length - r;
				index = index + r;

				if (length < size) {
					size = length;
				}
			}
		} catch (jcommon::Exception &e) {
		}
	} else {
		response = new Response();

		response->SetIntegerParam("self", 0);
	}

	delete response;
	response = NULL;

	delete method;
	method = NULL;

	client->Close();
	delete client;
	client = NULL;

}

}
