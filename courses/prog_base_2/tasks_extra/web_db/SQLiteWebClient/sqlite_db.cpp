#include "stdafx.h"
#include "sqlite_db.h"

std::vector<std::vector<std::pair<std::string, std::string>>> sqlite_db::tmp_sql_results;

int sqlite_db::callback(void * NotUsed, int argc, char ** argv, char ** azColName)
{
	std::vector<std::pair<std::string, std::string>> row;
	for (int i = 0; i < argc; i++) {
		row.push_back(std::make_pair(std::string(azColName[i]), std::string(argv[i] ? argv[i] : "NULL")));
	}
	tmp_sql_results.push_back(row);
	return 0;
}

sqlite_db::sqlite_db(std::string fname) : file_name{ fname }
{
}

int sqlite_db::open()
{
	return sqlite3_open(file_name.c_str(), &db);
}

void sqlite_db::close()
{
	sqlite3_close(db);
}

int sqlite_db::get_all_table_names(std::vector<std::string>& table_names)
{
	int rc;
	sqlite_db::tmp_sql_results.clear();
	table_names.clear();

	rc = sqlite3_exec(db, "SELECT name FROM sqlite_master WHERE type='table' AND name <> 'sqlite_sequence';", sqlite_db::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		printf("SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return -1;
	}
	for (std::vector<std::pair<std::string, std::string>> table_name_row : sqlite_db::tmp_sql_results) {
		for (std::pair<std::string, std::string> tname : table_name_row) {
			table_names.push_back(tname.second);
		}
	}
	return 0;
}

int sqlite_db::get_table_data(std::string table_name, std::vector<std::vector<std::pair<std::string, std::string>>>& table_rows, int limit = 50, int offset = 0)
{
	int rc;
	std::string sql_query;
	sqlite_db::tmp_sql_results.clear();
	table_rows.clear();

	sql_query = "SELECT * FROM " + table_name + " LIMIT " + std::to_string(limit) + " OFFSET " + std::to_string(offset) + ";";
	rc = sqlite3_exec(db, sql_query.c_str() , sqlite_db::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		printf("SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return -1;
	}
	table_rows = sqlite_db::tmp_sql_results;
	return 0;
}

int sqlite_db::delete_table_row(std::string table_name, std::string row_id)
{
	int rc;
	std::string sql_query;

	sqlite_db::tmp_sql_results.clear();

	sql_query = "DELETE FROM " + table_name + " WHERE id = " + row_id + ";";
	rc = sqlite3_exec(db, sql_query.c_str(), sqlite_db::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		printf("SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return -1;
	}
	return 0;
}

int sqlite_db::insert_row_into_table(std::string table_name, std::map<std::wstring, std::wstring> row_data)
{
	int rc;
	std::string sql_query;

	sql_query = "INSERT INTO " + table_name + "(";
	for (auto rw : row_data) {
		sql_query += std::string(rw.first.begin(), rw.first.end()) + ",";
	}
	sql_query.pop_back();
	sql_query += ") VALUES (";
	for (auto rw : row_data) {
		sql_query += "'" + std::string(rw.second.begin(), rw.second.end()) + "',";
	}
	sql_query.pop_back();
	sql_query += ");";
	std::cout << sql_query;
	rc = sqlite3_exec(db, sql_query.c_str(), sqlite_db::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		printf("SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return -1;
	}

	return (int)sqlite3_last_insert_rowid(db);
}

int sqlite_db::edit_row_into_table(std::string table_name, std::string row_id, std::map<std::wstring, std::wstring> row_data)
{
	int rc;
	std::string sql_query;

	sql_query = "UPDATE " + table_name;
	sql_query += " SET ";
	for (auto rw : row_data) {
		sql_query += std::string(rw.first.begin(), rw.first.end());
		sql_query+= " = " + std::string(rw.second.begin(), rw.second.end()) + ",";
	}
	sql_query.pop_back();
	sql_query += " WHERE id = " + row_id + ";";
	
	std::cout << sql_query;
	rc = sqlite3_exec(db, sql_query.c_str(), sqlite_db::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		printf("SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return -1;
	}

	return (int)sqlite3_last_insert_rowid(db);
}

