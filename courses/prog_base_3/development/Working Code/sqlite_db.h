#pragma once

#include <sqlite3.h>
#include "Company.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "Product.h"
#include <algorithm>
class sqlite_db {
private:
	sqlite3 *db;
	std::string file_name;
	char *zErrMsg = 0;
	static std::vector<std::vector<std::pair<std::string, std::string>>> tmp_sql_results;
	static std::vector<char> f;
	static int callback(void *NotUsed, int argc, char **argv, char **azColName);
public:
	sqlite_db(std::string fname);
	int open();
	void close();
	int get_all_table_names(std::vector<std::string>& table_names);
	int get_table_data(std::string table_name, std::vector<std::vector<std::pair<std::string,std::string>>>& sql_res, int limit, int offset);
	int delete_table_row(std::string table_name, std::string row_id);
	//	int edit_table_row(std::string table_name, std::string row_id);
	int insert_row_into_table(std::string table_name, std::map<std::wstring, std::wstring> row_data);
	int edit_row_into_table(std::string table_name, std::string row_id,std::map<std::wstring, std::wstring> row_data);
	int db_getOrders(std::vector<std::vector<std::pair<std::string, std::string>>>& sql_res, int id);
	//////////////////////////////
	int db_getSize();
	Product db_fillInfo(sqlite3_stmt * stmt);
	Product sqlite_db::db_get_product(int id);
	std::vector<int> db_getIds();
	int db_searchCount(std::map<std::wstring, std::wstring> row_data);
	std::vector<int> db_search(std::map<std::wstring, std::wstring> row_data);
	int  db_sendMsg(std::map<std::wstring, std::wstring> row_data);
	int  db_Admin(std::map<std::wstring, std::wstring> row_data);
	Company db_getCompany(std::vector<std::vector<std::pair<std::string, std::string>>>& table_rows);
	int db_placeOrderTable(std::map<std::wstring, std::wstring> row_data,double totalPrice);
	int db_orderTableId();
	int db_placeOrder(Product product, int count, int orderTableId);
	std::vector<int> db_getNewest();
};