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
#include "sqlite3.h"
#include "sqliteparameter.h"
#include "sqliteexception.h"
#include "sqlitecommand.h"

#include <string.h>

namespace jlwuit {

SQLiteParameter::SQLiteParameter(const SQLiteCommand& command):
	_command(command), _isAssigned(false)
{

}

SQLiteParameter::~SQLiteParameter(void)
{

}

void SQLiteParameter::bind(const int index)
{
	assigned();
	verify(sqlite3_bind_null(_command._stmt, index));
}

void SQLiteParameter::bind(const int index, const int& value)
{
	assigned();
	verify(sqlite3_bind_int(_command._stmt, index, value));
}

void SQLiteParameter::bind(const int index, const long long& value)
{
	assigned();
	verify(sqlite3_bind_int64(_command._stmt, index, value));
}

void SQLiteParameter::bind(const int index, const double& value)
{
	assigned();
	verify(sqlite3_bind_double(_command._stmt, index, value));
}

void SQLiteParameter::bind(const int index, const std::string& value)
{
	assigned();
	verify(sqlite3_bind_text(_command._stmt, index, value.c_str(), int(value.length()), SQLITE_TRANSIENT));
}

void SQLiteParameter::bind(const int index, const std::wstring& value)
{
	assigned();
	verify(sqlite3_bind_text16(_command._stmt, index, value.c_str(), int(value.length()), SQLITE_TRANSIENT));
}

void SQLiteParameter::bind(const int index, const char* value)
{
	assigned();
	verify(sqlite3_bind_text(_command._stmt, index, value, (int)strlen(value), SQLITE_TRANSIENT));
}

void SQLiteParameter::bind(const int index, const wchar_t* value)
{
	assigned();
	verify(sqlite3_bind_text16(_command._stmt, index, value, (int)wcslen(value), SQLITE_TRANSIENT));
}

void SQLiteParameter::bind(const int index, const char* value, int size)
{
	assigned();
	verify(sqlite3_bind_blob(_command._stmt, index, value, size, SQLITE_TRANSIENT));
}

void SQLiteParameter::bind(const int index, const void* value, int size)
{
	assigned();
	verify(sqlite3_bind_blob(_command._stmt, index, value, size, SQLITE_TRANSIENT));
}

inline void SQLiteParameter::assigned(void) const
{
	if (_isAssigned) {
		throw SQLiteException("The parameter has been assigned.");
	}
}

inline void SQLiteParameter::verify(const int result)
{
	if (result != SQLITE_OK) {
		throw SQLiteException(_command._connection);
	}
	
	_isAssigned = true;
}

}
