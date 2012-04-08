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
#include "attributes.h"

#include <sstream>

#include <fcntl.h>

namespace jlwuit {

Attributes::Attributes(std::string id, std::string type)
{
	SetLiteralParam("application.id", id);
	SetLiteralParam("application.type", type);
}

Attributes::~Attributes()
{
}

std::string Attributes::GetType()
{
	return GetLiteralParam("application.type");
}

std::string Attributes::GetIdentifier()
{
	return GetLiteralParam("application.id");
}

std::string Attributes::GetName()
{
	return GetLiteralParam("application.name");
}

std::string Attributes::GetClassPath()
{
	return GetLiteralParam("application.classpath");
}

std::string Attributes::GetBaseDirectory()
{
	return GetLiteralParam("application.basedirectory");
}

std::string Attributes::GetMainDocument()
{
	return GetLiteralParam("application.maindocument");
}

std::string Attributes::GetIcon()
{
	return GetLiteralParam("application.icon");
}

std::string Attributes::GetInformation()
{
	return GetLiteralParam("application.information");
}

}
