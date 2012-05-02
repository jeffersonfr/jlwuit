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
#ifndef LWUIT_SQLITECONNECTION_H
#define LWUIT_SQLITECONNECTION_H

#include "sqlite3.h"

#include <string>

namespace jlwuit {

class SQLiteException;
class SQLiteCommand;
class SQLiteTransaction;
class SQLiteDataReader;
class SQLiteDataTable;

class SQLiteConnection {

	friend class SQLiteException;
	friend class SQLiteCommand;
	friend class SQLiteTransaction;
	friend class SQLiteDataReader;
	friend class SQLiteDataTable;

	private:
		struct sqlite3 *_db;
		mutable bool _inTransaction;

	private:
		SQLiteConnection(const SQLiteConnection& );
		SQLiteConnection& operator=(const SQLiteConnection& );

		virtual void Execute(const std::string& sql, int (*callback)(void*, int, char**, char**) = NULL, void* argument = NULL) const;
		virtual void IsOpened(void) const; 

	public:
		std::string _name;
		std::string _version;

	public:
		explicit SQLiteConnection(const std::string &name);
		~SQLiteConnection(void);

		virtual void Open(void);
		virtual void Close(void);

		virtual SQLiteTransaction BeginTransaction(void) const;
		virtual void SetBusyTimeout(const int millisecond) const;

};

}

#endif
