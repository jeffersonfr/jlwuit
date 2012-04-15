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
#include "httprequest.h"
#include "jautolock.h"

#include <iostream>
#include <sstream>

namespace jlwuit {

HTTPRequest::HTTPRequest()
{
	_header.SetTextParam("Host", "localhost");
	_header.SetTextParam("User-Agent", "jlwuit/0.01-linux");
	_header.SetTextParam("Accept-Language", "pt-br");
	_header.SetTextParam("Connection", "close");
}

HTTPRequest::~HTTPRequest()
{
}

void HTTPRequest::Open(std::string url)
{
	_url = url;
}

void HTTPRequest::SetProtocol(lwuit_http_protocol_t protocol)
{
	_protocol = protocol;
}

ParamMapper * HTTPRequest::GetHeader()
{
	return &_header;
}

ParamMapper * HTTPRequest::GetCookies()
{
	return &_cookies;
}

void HTTPRequest::Send(HTTPStatusChanged *listener)
{
	Send(NULL, listener);
}

void HTTPRequest::Send(jio::InputStream *stream, HTTPStatusChanged *listener)
{
	std::ostringstream o;

	if (_protocol == LHP_GET) {
		o << "GET ";
	} else if (_protocol == LHP_GET) {
		o << "POST ";
	}

	o << _url << " HTTP/1.0\r\n";

	if (stream != NULL) {
		o << "Content-Length: " << stream->GetSize() << "\r\n";
	}

	// TODO:: add parameters
}

}
