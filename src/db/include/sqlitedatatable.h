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
#ifndef LWUIT_SQLITEDATATABLE_H
#define LWUIT_SQLITEDATATABLE_H

#include "sqliteconnection.h"

#include <vector>

namespace jlwuit {

class SQLiteDataTable {

	friend class SQLiteCommand;

	private:
		std::vector<std::string> _data;
		int _rows;
		int _columns;

	public:
		SQLiteDataTable(void);
		SQLiteDataTable(const SQLiteConnection& connection, const std::string& commandText);
		SQLiteDataTable(const SQLiteDataTable& other);
		SQLiteDataTable& operator=(const SQLiteDataTable& other);
		~SQLiteDataTable(void);

		void assign(const SQLiteConnection& connection, const std::string& commandText);

		int rows(void) const;
		int columns(void) const;
		std::string getFieldName(const int column);
		std::string getFieldValue(const int row, const int column);

};

}

#endif
