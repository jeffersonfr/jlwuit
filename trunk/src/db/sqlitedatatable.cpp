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
#include "sqlitedatatable.h"
#include "sqliteconnection.h"
#include "sqliteexception.h"
#include "sqlite3.h"

namespace jlwuit {

SQLiteDataTable::SQLiteDataTable(void)
{
	_rows = 0;
	_columns = 0;
}

SQLiteDataTable::SQLiteDataTable(const SQLiteConnection& connection, const std::string& commandText)
{
	_rows = 0;
	_columns = 0;

	assign(connection, commandText);
}

SQLiteDataTable::SQLiteDataTable(const SQLiteDataTable& other): 
	_data(other._data)
{
	_rows = other._rows;
	_columns = other._columns;
}

SQLiteDataTable& SQLiteDataTable::operator=(const SQLiteDataTable& other)
{
	_rows = other._rows;
	_columns = other._columns;
	_data = other._data;

	return *this;
}

SQLiteDataTable::~SQLiteDataTable(void)
{
	_data.clear();
}

int SQLiteDataTable::rows(void) const
{
	return _rows;
}

int SQLiteDataTable::columns(void) const
{
	return _columns;
}

std::string SQLiteDataTable::getFieldName(const int column)
{
	if (column < 0 || column >= _columns)
	{
		std::out_of_range("Index out of range.");
	}

	return _data[column];
}

std::string SQLiteDataTable::getFieldValue(const int row, const int column)
{
	if (column < 0 || column >= _columns)
	{
		std::out_of_range("Index out of range.");
	}

	if (row < 0 || row >= _rows)
	{
		std::out_of_range("Index out of range.");
	}

	return _data[_columns * (row + 1) + column];
}

void SQLiteDataTable::assign(const SQLiteConnection& connection, const std::string& commandText)
{
	connection.isOpened();

	char** result;
	if (sqlite3_get_table(connection._db, commandText.c_str(), &result, &_rows, &_columns, NULL) != SQLITE_OK)
	{
		throw SQLiteException(connection);
	}

	for (int i = 0; i < _columns * (_rows + 1); i++)
	{
		if (result[i])
		{
			_data.push_back(result[i]);
		}
		else
		{
			_data.push_back("NULL");
		}
	}

	sqlite3_free_table(result);
}

}
