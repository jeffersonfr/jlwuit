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
#include "preferences.h"
#include "jfileoutputstream.h"
#include "jxmlparser.h"

#include <iostream>
#include <sstream>

#define PREFERENCES_PATH(id) std::string("resources/config/" + id + ".xml");

namespace jlwuit {

Preferences::Preferences()
{
}

Preferences::~Preferences()
{
}

Document * Preferences::Create(std::string prefs)
{
	Document *document = new Document(prefs);

	std::string path = PREFERENCES_PATH(prefs);

	jcommon::XmlDocument doc(path);

	if (!doc.LoadFile()) {
		return NULL;
	}

	jcommon::XmlElement *root = doc.RootElement()->FirstChildElement();
	jcommon::XmlElement *psg;
	jcommon::XmlAttribute *attr;

	while (root != NULL) {
		Element *element = new Element(root->Value());

		attr = root->FirstAttribute();

		while (attr != NULL) {
			const char *key = attr->Name(),
				*value = attr->Value();

			if (key != NULL && value != NULL) {
				element->GetAttributes()->SetTextParam(key, value);
			}

			attr = attr->Next();
		}

		psg = root->FirstChildElement();

		while (psg != NULL) {
			if (strcmp(psg->Value(), "param") == 0) {
				const char *key = psg->Attribute("key"),
					*value = psg->Attribute("value");

				if (key != NULL && value != NULL) {
					element->SetTextParam(key, value);
				}
			}
		
			psg = psg->NextSiblingElement();
		}

		document->AddElement(element);

		root = root->NextSiblingElement();
	}

	return document;
}

void Preferences::Store(Document *document)
{
	if (document == NULL) {
		return;
	}

	std::ostringstream o;

	o << "<" << document->GetName() << ">" << std::endl;

	std::vector<Element *> elements = document->GetElements();

	for (std::vector<Element *>::iterator i=elements.begin(); i!=elements.end(); i++) {
		Element *element = (*i);

		o << "  <" << element->GetName();

		std::map<std::string, std::string> attributes = element->GetAttributes()->GetParameters();
		std::map<std::string, std::string> parameters = element->GetParameters();

		for (std::map<std::string, std::string>::iterator j=attributes.begin(); j!=attributes.end(); j++) {
			o << " " << j->first << "=\"" << j->second << "\"";
		}

		if (parameters.size() == 0) {
			o << " />" << std::endl;
		} else {
			o << ">" << std::endl;

			for (std::map<std::string, std::string>::iterator j=parameters.begin(); j!=parameters.end(); j++) {
				o << "    <param key=\"" << j->first << "\" value=\"" << j->second << "\" />" << std::endl;
			}

			o << "  </" << element->GetName() << ">" << std::endl;
		}
	}
	
	o << "</" << document->GetName() << ">" << std::endl;

	std::string path = PREFERENCES_PATH(document->GetName());

	jio::File *file = jio::File::OpenFile(path);
	
	file->Remove();

	jio::FileOutputStream fos(path);

	fos.Write(o.str().c_str(), o.str().size());
	fos.Flush();
}

}
