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
#include "preferences.h"

#include <iostream>

#include <stdio.h>
#include <strings.h>

void dump_element(jlwuit::Element *element)
{
	std::cout << "  <" << element->GetName();

	std::map<std::string, std::string> attributes = element->GetAttributes()->GetParameters();
	std::map<std::string, std::string> parameters = element->GetParameters();

	for (std::map<std::string, std::string>::iterator j=attributes.begin(); j!=attributes.end(); j++) {
		std::cout << " " << j->first << "=\"" << j->second << "\"";
	}

	if (parameters.size() == 0) {
		std::cout << " />" << std::endl;
	} else {
		std::cout << ">" << std::endl;

		for (std::map<std::string, std::string>::iterator j=parameters.begin(); j!=parameters.end(); j++) {
			std::cout << "    <param key=\"" << j->first << "\" value=\"" << j->second << "\" />" << std::endl;
		}

		std::cout << "  </" << element->GetName() << ">" << std::endl;
	}
}

void dump_document(jlwuit::Document *document)
{
	std::cout << "<" << document->GetName() << ">" << std::endl;

	std::vector<jlwuit::Element *> elements = document->GetElements();

	for (std::vector<jlwuit::Element *>::iterator i=elements.begin(); i!=elements.end(); i++) {
		jlwuit::Element *element = (*i);

		dump_element(element);
	}
	
	std::cout << "</" << document->GetName() << ">" << std::endl;
}

void init_channel(int index)
{
	jlwuit::Document *doc = jlwuit::Preferences::Create("channels");
	jlwuit::Element *e = doc->GetElementByIndex(index);

	dump_element(e);
}

void init_language(std::string id)
{
	jlwuit::Document *doc = jlwuit::Preferences::Create("strings");
	jlwuit::Element *e = doc->GetElementByID(id);

	dump_element(e);
}

int main(int argc, char **argv)
{
	jlwuit::Document *doc = jlwuit::Preferences::Create("system");

	dump_document(doc);

	init_channel(doc->GetElementByIndex(0)->GetIntegerParam("channel"));
	init_language(doc->GetElementByIndex(0)->GetTextParam("language"));

	return 0;
}
