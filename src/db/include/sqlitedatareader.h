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
#ifndef LWUIT_SQLITEDATAREADER_H
#define LWUIT_SQLITEDATAREADER_H

#include "sqlitecommand.h"

namespace jlwuit {

enum SQLiteDbType {
	DT_INTERGER	= 1,
	DT_FLOAT	= 2,
	DT_TEXT	= 3,
	DT_BLOB	= 4,
	DT_NULL	= 5,
};

class SQLiteCommand;

class SQLiteDataReader {

	friend class SQLiteCommand;

	private:
		SQLiteCommand &_command;
		int _fieldCount;

	private:
		explicit SQLiteDataReader(SQLiteCommand &command);
		
		void verify(const int index) const;
		SQLiteDataReader & operator=(const SQLiteDataReader &);

	public:
		SQLiteDataReader(const SQLiteDataReader *other);
		~SQLiteDataReader(void);

		bool read(void) const;
		void close();

		int getFieldCount(void) const;
		std::string getFieldName(const int index) const;
		SQLiteDbType getFieldDbType(const int index) const;
		std::string getDataTypeName(const int index) const;
		bool isDbNull(const int index) const;

		int getInt32(const int index) const;
		long long getInt64(const int index) const;
		double getFloat(const int index) const;
		std::string getString(const int index) const;
		std::string getString16(const int index) const;
		std::string getBLOB(const int index) const;

};

}

#endif
