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
#include "sqlitedatareader.h"
#include "sqliteexception.h"
#include "sqliteconnection.h"
#include "sqlitecommand.h"
#include "sqlite3.h"

namespace jlwuit {

SQLiteDataReader::SQLiteDataReader(SQLiteCommand& command): 
	_command(command)
{
	_fieldCount = sqlite3_column_count(_command._stmt);
}

SQLiteDataReader::~SQLiteDataReader(void)
{
	close();
}

bool SQLiteDataReader::read(void) const
{
	return _command.step();
}

void SQLiteDataReader::close(void)
{
	_command.~SQLiteCommand();
}

int SQLiteDataReader::getFieldCount(void) const
{
	return _fieldCount;
}

std::string SQLiteDataReader::getFieldName(const int index) const
{
	verify(index);

	return sqlite3_column_name(_command._stmt, index);
}

SQLiteDbType SQLiteDataReader::getFieldDbType(const int index) const
{
	verify(index);

	return (SQLiteDbType)sqlite3_column_type(_command._stmt, index);
}

std::string SQLiteDataReader::getDataTypeName(const int index) const
{
	verify(index);

	return sqlite3_column_decltype(_command._stmt, index);
}

bool SQLiteDataReader::isDbNull(const int index) const
{
	return getFieldDbType(index) == DT_NULL;
}

int SQLiteDataReader::getInt32(const int index) const
{
	verify(index);

	return sqlite3_column_int(_command._stmt, index);
}

long long SQLiteDataReader::getInt64(const int index) const
{
	verify(index);

	return sqlite3_column_int64(_command._stmt, index);
}

double SQLiteDataReader::getFloat(const int index) const
{
	verify(index);
	
	return sqlite3_column_double(_command._stmt, index);
}

std::string SQLiteDataReader::getString(const int index) const
{
	verify(index);

	return std::string((const char*)sqlite3_column_text(_command._stmt, index), 
		sqlite3_column_bytes(_command._stmt, index));
}

std::string SQLiteDataReader::getString16(const int index) const
{
	verify(index);

	return std::string((const char*)sqlite3_column_text16(_command._stmt, index), 
		sqlite3_column_bytes(_command._stmt, index));
}

std::string SQLiteDataReader::getBLOB(const int index) const
{
	verify(index);

	const char *column_blob = (const char *)sqlite3_column_blob(_command._stmt, index);
	int column_bytes = sqlite3_column_bytes(_command._stmt, index);
	
	return std::string(column_blob, column_bytes);
}

inline void SQLiteDataReader::verify(const int index) const
{
	if (index < 0 || index >= _fieldCount) {
		throw std::out_of_range("Index out of range");
	}
}

}
