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
		
		virtual void Verify(const int index) const;
		SQLiteDataReader & operator=(const SQLiteDataReader &);

	public:
		SQLiteDataReader(const SQLiteDataReader *other);
		~SQLiteDataReader(void);

		virtual bool Read(void) const;
		virtual void Close();

		virtual int GetFieldCount() const;
		virtual std::string GetFieldName(const int index) const;
		virtual SQLiteDbType GetFieldType(const int index) const;
		virtual std::string GetDataTypeName(const int index) const;
		virtual bool IsNull(const int index) const;

		virtual uint32_t GetInt32(const int index) const;
		virtual uint64_t GetInt64(const int index) const;
		virtual double GetFloat(const int index) const;
		virtual std::string GetString(const int index) const;
		virtual std::string GetString16(const int index) const;
		virtual std::string GetBLOB(const int index) const;

};

}

#endif
