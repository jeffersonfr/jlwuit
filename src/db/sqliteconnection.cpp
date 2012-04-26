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
#include "sqliteconnection.h"
#include "sqliteexception.h"
#include "sqlitecommand.h"
#include "sqlitetransaction.h"
#include "sqlite3.h"

namespace jlwuit {

SQLiteConnection::SQLiteConnection(const std::string &name)
{
	_name = name;
	_version = SQLITE_VERSION;
	_db = NULL;
	_inTransaction = false;
}

SQLiteConnection::SQLiteConnection(const SQLiteConnection& other)
{
	_name = other._name;
	_version = other._version;
	_db = other._db;
	_inTransaction = other._inTransaction;
}

SQLiteConnection::~SQLiteConnection(void)
{
	if (_db) {
		close();
	}
}

void SQLiteConnection::open(void)
{
	if (sqlite3_open(_name.c_str(), &_db) != SQLITE_OK) {
		throw SQLiteException("Unable to open database.");
	}

	setBusyTimeout(3000);
}

void SQLiteConnection::close(void)
{
	sqlite3_close(_db);
	_db = NULL;
}

inline void SQLiteConnection::isOpened(void) const
{
	if (!_db) {
		throw SQLiteException("Not open database connection.");
	}
}

void SQLiteConnection::execute(const std::string& sql, int (*callback)(void*,int,char**,char**), void* argument) const
{
	isOpened();

	if (sqlite3_exec(_db, sql.c_str(), callback, argument, NULL) != SQLITE_OK) {
		throw SQLiteException(*this);
	}
}

void SQLiteConnection::setBusyTimeout(const int millisecond) const
{
	isOpened();

	if (sqlite3_busy_timeout(_db, millisecond) != SQLITE_OK) {
		throw SQLiteException(*this);
	}
}

SQLiteTransaction SQLiteConnection::beginTransaction(void) const
{
	return SQLiteTransaction(*this);
}

}
