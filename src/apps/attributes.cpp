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
	SetTextParam("application.id", id);
	SetTextParam("application.type", type);
}

Attributes::~Attributes()
{
}

std::string Attributes::GetType()
{
	return GetTextParam("application.type");
}

std::string Attributes::GetIdentifier()
{
	return GetTextParam("application.id");
}

std::string Attributes::GetName()
{
	return GetTextParam("application.name");
}

std::string Attributes::GetClassPath()
{
	return GetTextParam("application.classpath");
}

std::string Attributes::GetBaseDirectory()
{
	return GetTextParam("application.basedirectory");
}

std::string Attributes::GetMainDocument()
{
	return GetTextParam("application.maindocument");
}

std::string Attributes::GetIcon()
{
	return GetTextParam("application.icon");
}

std::string Attributes::GetInformation()
{
	return GetTextParam("application.information");
}

}
