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
#ifndef LWUIT_SQLITEPARAMETER_H
#define LWUIT_SQLITEPARAMETER_H

#include "sqlitecommand.h"

namespace jlwuit {

class SQLiteCommand;

class SQLiteParameter {

	private:
		const SQLiteCommand& _command;
		bool _isAssigned;

	private:
		virtual void Assigned(void) const;
		virtual void Verify(const int result);

		SQLiteParameter& operator=(const SQLiteParameter& );

	public:
		explicit SQLiteParameter(const SQLiteCommand& command);
		SQLiteParameter(const SQLiteParameter& other);
		~SQLiteParameter(void);

		virtual void Bind(const int index);
		virtual void Bind(const int index, const int& value);
		virtual void Bind(const int index, const long long& value);
		virtual void Bind(const int index, const double& value);
		virtual void Bind(const int index, const std::string& value);
		virtual void Bind(const int index, const std::wstring& value);
		virtual void Bind(const int index, const char* value);
		virtual void Bind(const int index, const wchar_t* value);
		virtual void Bind(const int index, const char* value, int size);
		virtual void Bind(const int index, const void* value, int size);

};

}

#endif
