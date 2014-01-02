/*
Copyright (C) 2014  Пельмень.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "CMysql.h"
#include <sstream>

typedef void (*logprintf_t)(char* format, ...);
extern logprintf_t logprintf;
CMySQL MySQL;

void CMySQL::Free () {
	mysql_free_result(result);
}

void CMySQL::Query (const char* query) {
	if ((state = mysql_query(connection, query)) != 0) {
		logprintf ("%s", mysql_error (connection));
		return;
	}
}

void CMySQL::Connect () {
	mysql_init(&mysql);
	if (!(connection = mysql_real_connect(&mysql, LOCAL_HOST, "root", "", "db_test", 3306, NULL, 0))) {
		logprintf ("%s", mysql_error (connection));
		return;
	}
}

void CMySQL::Close () {
	mysql_close (connection);
}

void CMySQL::Store () {
	if ((result = mysql_store_result(connection)) == NULL) {
		logprintf ("%s", mysql_error (connection));
		return;
	}
}

my_ulonglong CMySQL::NumRows () {
	return mysql_num_rows(result);
}
