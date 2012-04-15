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
#ifndef LWUIT_HTTPREQUEST_H
#define LWUIT_HTTPREQUEST_H

#include "httpstatuschanged.h"
#include "parammapper.h"
#include "jinputstream.h"

namespace jlwuit {

enum lwuit_http_protocol_t {
	LHP_GET,
	LHP_POST
};

class HTTPRequest {

	private:
		/** \brief */
		ParamMapper _header;
		/** \brief */
		ParamMapper _cookies;
		/** \brief */
		std::string _url;
		/** \brief */
		lwuit_http_protocol_t _protocol;

	protected:
		/**
		 * \brief
		 *
		 */
		HTTPRequest();

	public:
		/**
		 * \brief
		 *
		 */
		virtual ~HTTPRequest();
		
		/**
		 * \brief
		 *
		 */
		virtual void Open(std::string url);
		
		/**
		 * \brief
		 *
		 */
		virtual void SetProtocol(lwuit_http_protocol_t protocol);

		/**
		 * \brief
		 *
		 */
		virtual ParamMapper * GetHeader();
		
		/**
		 * \brief
		 *
		 */
		virtual ParamMapper * GetCookies();
		
		/**
		 * \brief
		 *
		 */
		virtual void Send(HTTPStatusChanged *listener);

		/**
		 * \brief
		 *
		 */
		virtual void Send(jio::InputStream *stream, HTTPStatusChanged *listener);

};

}

#endif

