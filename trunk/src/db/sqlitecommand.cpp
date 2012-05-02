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
#include "sqlitecommand.h"
#include "sqliteexception.h"
#include "sqliteconnection.h"
#include "sqlitedatareader.h"
#include "sqliteparameter.h"
#include "sqlitedatatable.h"
#include "sqlite3.h"

#include <assert.h>

namespace jlwuit {

SQLiteCommand::SQLiteCommand(const SQLiteConnection& connection): 
	_connection(connection)
{
	_stmt = NULL;
}

SQLiteCommand::SQLiteCommand(const SQLiteConnection& connection, const std::string& commandText): 
	_connection(connection)
{
	_commandText = commandText;
	_stmt = NULL;

	Prepare();
}

SQLiteCommand::SQLiteCommand(const SQLiteCommand& other): 
	_connection(other._connection)
{
	_commandText = other._commandText;
	_stmt = other._stmt; 

	if (!_commandText.empty()) {
		Prepare();
	}
}

SQLiteCommand::~SQLiteCommand(void)
{
	Finalize();
}

void SQLiteCommand::SetCommandText(const std::string& commandText)
{
	Reset();
	
	_commandText.assign(commandText);
	
	Prepare();
}

SQLiteParameter SQLiteCommand::CreateParameter(void)
{
	return SQLiteParameter(*this);
}

int SQLiteCommand::ExecuteNonQuery(void)
{
	Step();

	return sqlite3_changes(_connection._db);
}

int SQLiteCommand::ExecuteScalar(void)
{
	//_ASSERT_EXPR(0, L"The function has not been implementation. It will be return 0.");
	//_wassert(L"The function has not been implementation. It will be return 0.", __FILEW__, __LINE__);
	assert(0);

	return 0;
}

const SQLiteDataReader SQLiteCommand::ExecuteReader(void)
{
	return new SQLiteDataReader(*this);
}

void SQLiteCommand::Fill(SQLiteDataTable& dataTable)
{
	dataTable.Assign(_connection, _commandText);
}

void SQLiteCommand::Prepare(void)
{
	_connection.IsOpened();

	if (sqlite3_prepare(_connection._db, _commandText.c_str(), -1, &_stmt, NULL) != SQLITE_OK) {
		throw SQLiteException(_connection);
	}
}

bool SQLiteCommand::Step(void)
{
	if (_commandText.empty()) {
		throw SQLiteException("The command text has not be assigned.");
	}

	if (!_stmt) {
		throw SQLiteException("The sqlite statement is null.");
	}

	switch(sqlite3_step(_stmt)) {
		case SQLITE_ROW:
			return true;
		case SQLITE_DONE:
			return false;
		default:
			throw SQLiteException(_connection);
	}
}

void SQLiteCommand::Reset(void)
{
	if (sqlite3_reset(_stmt) != SQLITE_OK) {
		throw SQLiteException(_connection);
	}
}

void SQLiteCommand::Finalize(void)
{
	if (_stmt) {
		if (sqlite3_finalize(_stmt) != SQLITE_OK) {
			throw SQLiteException(_connection);
		}

		_stmt = NULL;
	}
}

}
