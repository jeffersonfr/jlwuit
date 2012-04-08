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
#include "appdatabase.h"
#include "preferences.h"
#include "nativeproxy.h"

#include <algorithm>
#include <string>
#include <sstream>

namespace jlwuit {

AppDatabase *AppDatabase::_instance = NULL;

struct ascending_sort {
	
	bool operator()(Attributes * const &a, Attributes * const &b)
	{
		if (a->GetName() < b->GetName()) {
			return true;
		}

		return false;
	}

};

AppDatabase::AppDatabase()
{
}

AppDatabase::~AppDatabase()
{
}

AppDatabase * AppDatabase::GetInstance()
{
	if (_instance == NULL) {
		_instance = new AppDatabase();

		_instance->Initialize();
	}

	return _instance;
}

void AppDatabase::Initialize()
{
	/*
	jlwuit::Document *doc = jlwuit::Preferences::Create("applications");

	std::vector<jlwuit::Element *> nodes = doc->GetElements();

	for (std::vector<jlwuit::Element *>::iterator i=_nodes.begin(); i!=_nodes.end(); i++) {
		jlwuit::Element *e = (*i);
	
		jlwuit::Attributes *attr = new Attributes();
		
		attr->SetLiteralParam("id", e->GetLiteralAttribute("id"));
		attr->SetLiteralParam("type", e->GetLiteralAttribute("type"));
		attr->SetLiteralParam("code", e->GetLiteralAttribute("code"));

		attr->SetLiteralParam("application.name", e->GetLiteralParam("name"));
		attr->SetLiteralParam("application.classpath", e->GetLiteralParam("classpath"));
		attr->SetLiteralParam("application.basedirectory", e->GetLiteralParam("basedirectory"));
		attr->SetLiteralParam("application.maindocument", e->GetLiteralParam("maindocument"));
		attr->SetLiteralParam("application.icon", e->GetLiteralParam("icon"));
		attr->SetLiteralParam("application.information", e->GetLiteralParam("information"));

		AddApplication(attr);
	} while ((psg = psg->NextSiblingElement("application")) != NULL);
	
	std::sort(_applications.begin(), _applications.end(), ascending_sort());
	*/
}

void AppDatabase::Update()
{
	/*
	jlwuit::Document *doc = jlwuit::Preferences::Create("applications");

	doc->RemoveElemens();

	for (std::vector<Attribute *>:iterator i=_applications.begin(); i!=_applications.end(); i++) {
		Element *element = new Element();

		element->Copy(*i);

		doc->AddElement(element);
	}
	
	jlwuit::Preferences::Store(doc);
	*/
}

void AppDatabase::AddApplication(Attributes *attr)
{
	/*
	std::map<std::string, std::string> params = attr->GetParameters();
	
	jlwuit::Attributes *attribute = new Attributes();
	
	attribute->Copy(attr);

	_applications.push_back(attribute);
	*/
}

void AppDatabase::RemoveApplication(Attributes *attr)
{
	/*
	if (attr == NULL) {
		return;
	}

	for (std::vector<Attributes *>::iterator i=_applications.begin(); i!=_applications.end(); i++) {
		Attribute *attribute = (*i);

		if (attr->GetName() == attribute->GetName()) {
			_applications.erase(i);

			delete attribute;

			break;
	}
	*/
}

Attributes * AppDatabase::GetApplication(std::string id)
{
	for (std::vector<Attributes *>::iterator i=_applications.begin(); i!=_applications.end(); i++) {
		if ((*i)->GetIdentifier() == id) {
			return (*i);
		}
	}

	return NULL;
}

std::vector<Attributes *> & AppDatabase::GetApplications()
{
	return _applications;
}

Proxy * AppDatabase::GetProxy(std::string id)
{
	Attributes *attr = GetApplication(id);

	if (attr != NULL) {
		if (attr->GetType() == "native") {
			//return static_cast<Proxy *>(new NativeProxy(attr));
		}
	}

	return NULL;
}

Proxy * AppDatabase::GetProxy(Attributes *attr)
{
	if (attr == NULL) {
		return NULL;
	}

	return GetProxy(attr->GetIdentifier());
}

}
