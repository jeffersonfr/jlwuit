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
#ifndef LWUIT_SQLITECOMMAND_H
#define LWUIT_SQLITECOMMAND_H

#include "sqliteexception.h"
#include "sqliteconnection.h"

namespace jlwuit {

class SQLiteDataReader;
class SQLiteDataTable;
class SQLiteParameter;

class SQLiteCommand {
	
	friend class SQLiteDataReader;
	friend class SQLiteParameter;

	private:
		struct sqlite3_stmt *_stmt;
		std::string _commandText;

	private:
		virtual void Prepare(void);
		virtual bool Step(void);
		virtual void Reset(void);
		virtual void Finalize(void);

		SQLiteCommand & operator=(const SQLiteCommand& );

	public:
		const SQLiteConnection &_connection;

	public:
		explicit SQLiteCommand(const SQLiteConnection& connection);
		SQLiteCommand(const SQLiteConnection& connection, const std::string& commandText);
		SQLiteCommand(const SQLiteCommand& other);
		~SQLiteCommand(void);

		virtual void SetCommandText(const std::string& commandText);
		virtual SQLiteParameter CreateParameter(void);
		virtual int ExecuteNonQuery(void);
		virtual int ExecuteScalar(void);
		virtual const SQLiteDataReader ExecuteReader(void);
		virtual void Fill(SQLiteDataTable &dataTable);

};

}

#endif
