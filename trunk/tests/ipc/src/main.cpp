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
#include "localipcclient.h"
#include "localipcserver.h"
#include "method.h"

#include "jstringtokenizer.h"

#include <iostream>

#include <stdio.h>
#include <strings.h>

bool alive = true;

class Callback : public jlwuit::RemoteCallListener {

	public:
		Callback()
		{
		}

		virtual ~Callback()
		{
		}

		virtual jlwuit::Response * ProcessCall(jlwuit::Method *method)
		{
			jlwuit::Response *response = new jlwuit::Response();
			
			response->SetBooleanParam("self", false);

			if (method->GetName() == "quit") {
				alive = false;
			} else if (method->GetName() == "isPlaying") {
				response->SetBooleanParam("self", true);
			}

			std::cout << method->what() << std::endl;

			return response;
		}

};

void usage(char *name)
{
	printf("%s server <id>\n", name);
	printf("%s client <id> <method> <param=value> ... <param=value>\n", name);

	exit(0);
}

void server(std::string id)
{
	jlwuit::LocalIPCServer server(id);
	Callback cb;

	while (alive == true) {
		server.WaitCall(&cb);
	}
				
	std::cout << "bye ..." << std::endl;
}

void client(std::string id, jlwuit::Method *method)
{
	jlwuit::LocalIPCClient client(id);
	
	jlwuit::Response *response = client.CallMethod(method);
	
	std::cout << response->what() << std::endl;
}

int main(int argc, char **argv)
{
	if (argc < 3) {
		usage(argv[0]);
	}

	if (strcasecmp(argv[1], "server") == 0) {
		server(argv[2]);
	} else if (strcasecmp(argv[1], "client") == 0) {
		jlwuit::Method method(argv[3]);

		for (int i=4; i<argc; i++) {
			jcommon::StringTokenizer tokens(std::string(argv[i]), "=", jcommon::JTT_STRING);

			if (tokens.GetSize() > 1) {
				method.SetTextParam(tokens.GetToken(0), tokens.GetToken(1));
			}
		}

		client(argv[2], &method);
	}

	return 0;
}
