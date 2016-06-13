#include "stdafx.h"
#include "sqlite_db.h"
#include "string.h"
#include <time.h>
#include <ctime>;

std::vector<std::vector<std::pair<std::string, std::string>>> sqlite_db::tmp_sql_results;
bool is_number(const std::string& s)
{
	return(strspn(s.c_str(), "-.0123456789") == s.size());
}
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
std::string replaceAll(std::string const& original, std::string const& from, std::string const& to)
{
	std::string results;
	std::string::const_iterator end = original.end();
	std::string::const_iterator current = original.begin();
	std::string::const_iterator next = std::search(current, end, from.begin(), from.end());
	while (next != end) {
		results.append(current, next);
		results.append(to);
		current = next + from.size();
		next = std::search(current, end, from.begin(), from.end());
	}
	results.append(current, next);
	return results;
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
	rc = sqlite3_exec(db, sql_query.c_str(), sqlite_db::callback, 0, &zErrMsg);
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
	int p = 0;
	for (auto rw : row_data) {
			std::string c = std::string(rw.second.begin(), rw.second.end());
			c = replaceAll(c, "+", " ");
			c = replaceAll(c, "%3A", ":");
			c = replaceAll(c, "%2F", "/");
			c = replaceAll(c, "%2C", ",");
			c = replaceAll(c, "%28", "(");
			c = replaceAll(c, "%29", ")");
			sql_query += "'" + c + "',";
		
	}
	sql_query.pop_back();
	sql_query += ");";

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
	int p = 0;
	for (auto rw : row_data) {
		sql_query += std::string(rw.first.begin(), rw.first.end());
		sql_query += " = ";
		std::string c = std::string(rw.second.begin(), rw.second.end());
		c = replaceAll(c, "+", " ");
		c = replaceAll(c, "%3A", ":");
		c = replaceAll(c, "%2F", "/");
		c = replaceAll(c, "%2C", ",");
		c = replaceAll(c, "%28", "(");
		c = replaceAll(c, "%29", ")");
		std::cout << c;
		puts("");
		sql_query += "'" + c + "',";
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
int sqlite_db::db_getOrders(std::vector<std::vector<std::pair<std::string, std::string>>>& table_rows,int id)
{
	int rc;
	std::string sql_query;
	sqlite_db::tmp_sql_results.clear();
	table_rows.clear();

	sql_query = "SELECT OProductId FROM OrderProductBridge Where OorderId =" + std::to_string(id) + ";";
	rc = sqlite3_exec(db, sql_query.c_str(), sqlite_db::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		printf("SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return -1;
	}
	table_rows = sqlite_db::tmp_sql_results;
	return 0;
}
int sqlite_db::db_getSize()
{
	sqlite3_stmt * stmt = NULL;
	char * sqlQuery = "SELECT  COUNT(*) FROM ProductTable;";
	sqlite3_prepare_v2(db, sqlQuery, strlen(sqlQuery) + 1, &stmt, NULL);
	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR)
	{
		puts("Error : Select Count");
	}
	printf("%d", rc);
	int size = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);
	
	return size;
}
Product sqlite_db::db_fillInfo(sqlite3_stmt * stmt)
{
	std::string name, description, imageUrl;
	int id = sqlite3_column_int(stmt, 0);
	const unsigned char * cName = sqlite3_column_text(stmt, 1);
	const unsigned char * cdescription = sqlite3_column_text(stmt, 3);
	const unsigned char * cimageUrl = sqlite3_column_text(stmt, 4);
	if(cName != NULL)
		name = std::string(reinterpret_cast<const char*>(cName));
	double price = sqlite3_column_double(stmt, 2);
	if (cdescription != NULL)
		description = std::string(reinterpret_cast<const char*>(cdescription));
	if (cimageUrl != NULL)
		imageUrl = std::string(reinterpret_cast<const char*>(cimageUrl));
	Product product(id, name, price, description, imageUrl);
	return product;
	
}
Product sqlite_db::db_get_product(int id)
{
	
	sqlite3_stmt * stmt = NULL;
	char * sqlQuery = "SELECT * FROM ProductTable WHERE ProductTable.id = ?";
	sqlite3_prepare_v2(db, sqlQuery, strlen(sqlQuery) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, id);
	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR)
	{
		printf("SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	Product product = db_fillInfo(stmt);
	sqlite3_finalize(stmt);
	return product;
}

std::vector<int> sqlite_db::db_getIds()
{
	sqlite3_stmt * stmt = NULL;
	int size = db_getSize();
	std::vector<int> arr(size);
	char * sqlQuery = "SELECT Id FROM ProductTable;";
	sqlite3_prepare_v2(db, sqlQuery, strlen(sqlQuery) + 1, &stmt, NULL);
	for (int i = 0; i < size; i++)
	{
		int rc = sqlite3_step(stmt);
		if (rc == SQLITE_ERROR)
		{
			printf("SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		
		arr[i] = sqlite3_column_int(stmt, 0);
	}
	sqlite3_finalize(stmt);
	return arr;
	
}

int sqlite_db::db_searchCount(std::map<std::wstring, std::wstring> row_data)
{
	std::string word;
	int i = 1;
	for (auto rw : row_data) {
		if (i == 1)
		{
			word = std::string(rw.second.begin(), rw.second.end());
			i++;
		}
		else
		{
			break;

		}

	}
	sqlite3_stmt * stmt = NULL;

	std::string qu = "SELECT  COUNT(*) FROM ProductTable WHERE Name LIKE '%" + word + "%'";
	char * sqlQuery = new char[qu.length() + 1];
	std::strcpy(sqlQuery, qu.c_str());
	sqlite3_prepare_v2(db, sqlQuery, strlen(sqlQuery) + 1, &stmt, NULL);
	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR)
	{
		puts("Error : Select Count");
		exit(1);
	}
	int size = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);
	free(sqlQuery);
	return size;
	
}
std::vector<int> sqlite_db::db_search(std::map<std::wstring, std::wstring> row_data)
{
	std::string word;
	int i = 1;
	for (auto rw : row_data) {
		if (i == 1)
		{
			word = std::string(rw.second.begin(), rw.second.end());
			i++;
		}
		else
		{
			break;

		}

	}
	char * wordd = new char[word.length() + 1];
	std::strcpy(wordd, word.c_str());
	int size = db_searchCount(row_data);
	std::vector<int> ids(size);
	sqlite3_stmt * stmt = NULL;
	
	std::string qu = "SELECT  Id FROM ProductTable WHERE Name LIKE '%" + word + "%'";
	char * sqlQuery = new char[qu.length() + 1];
	std::strcpy(sqlQuery, qu.c_str());
	
	sqlite3_bind_text(stmt, 1, wordd, -1, SQLITE_STATIC);
	sqlite3_prepare_v2(db, sqlQuery, strlen(sqlQuery) + 1, &stmt, NULL);
	int rc;
	
	printf("SIZE IS %d", size);
	for (int i = 0; i < size; i++)
	{
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_ERROR)
		{
			printf("SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		ids[i] = (sqlite3_column_int(stmt, 0));
		
	}
	sqlite3_finalize(stmt);
	free(wordd);
	return ids;

}
int sqlite_db::db_sendMsg(std::map<std::wstring, std::wstring> row_data)
{
	int rc;
	std::string sql_query;
	sql_query = "INSERT INTO Messages (";
	for (auto rw : row_data) {
		sql_query += std::string(rw.first.begin(), rw.first.end()) + ",";
	}
	sql_query.pop_back();
	sql_query += ") VALUES (";
	int p = 0;
	for (auto rw : row_data) {
		std::string c = std::string(rw.second.begin(), rw.second.end());
		c = replaceAll(c, "+", " ");
		c = replaceAll(c, "%3A", ":");
		c = replaceAll(c, "%2F", "/");
		c = replaceAll(c, "%2C", ",");
		c = replaceAll(c, "%28", "(");
		c = replaceAll(c, "%29", ")");
		sql_query += "'" + c + "',";

	}
	sql_query.pop_back();
	sql_query += ");";

	rc = sqlite3_exec(db, sql_query.c_str(), sqlite_db::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		printf("SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return -1;
	}

	return 1;
}
int sqlite_db::db_Admin(std::map<std::wstring, std::wstring> row_data)
{
	std::string user, pass;
	int i = 1;
	for (auto rw : row_data) {
		if (i == 2)
		{
			user = std::string(rw.second.begin(), rw.second.end());
			i++;
		}
		else if (i == 1)
		{
			pass = std::string(rw.second.begin(), rw.second.end());
			i++;
		}
		else
			break;
	}
	std::string query = "SELECT COUNT(*) FROM Admins WHERE username='" + user + "' AND password='" + pass +"';";
	sqlite3_stmt * stmt = NULL;
	char * sqlQuery = new char[query.length() + 1];
	std::strcpy(sqlQuery, query.c_str());
	sqlite3_prepare_v2(db, sqlQuery, strlen(sqlQuery) + 1, &stmt, NULL);
	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR)
	{
		puts("Error : Select Count");
		return -1;
	}
	int size = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);
	free(sqlQuery);
	return size;

}
Company sqlite_db::db_getCompany(std::vector<std::vector<std::pair<std::string, std::string>>>& table_rows)
{
	std::string name = "noName";
	std::string telephone = "telephone";
	std::string address = "address";
	std::string about = "about";
	int rc;
	std::string sql_query;
	sqlite_db::tmp_sql_results.clear();
	table_rows.clear();

	sql_query = "SELECT * FROM Company;";
	rc = sqlite3_exec(db, sql_query.c_str(), sqlite_db::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		printf("SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		Company company(name, telephone, about, address);
	}
	table_rows = sqlite_db::tmp_sql_results;
	int i = 1;
	for (auto col : table_rows.at(0))
	{
		if (i == 1)
		{
			name = std::string(col.second.begin(), col.second.end());
			i++;
		}
			
		else if (i == 2)
		{
			telephone = std::string(col.second.begin(), col.second.end());
			i++;
		}
		else if (i == 3)
		{
			address = std::string(col.second.begin(), col.second.end());
			i++;
		}
		else if (i == 4)
		{
			about = std::string(col.second.begin(), col.second.end());
			i++;
		}
		else
			break;
			

	}
	Company company(name, telephone, about, address);

	return company;
}
int  sqlite_db::db_placeOrderTable(std::map<std::wstring, std::wstring> row_data,double totalPrice)
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", timeinfo);
	//
	std::string word;
	int i = 1;
	for (auto rw : row_data) {
		if (i == 1)
		{
			word = std::string(rw.second.begin(), rw.second.end());
			i++;
		}
		else
		{
			break;

		}

	}
	char * tel = new char[word.length() + 1];
	strcpy(tel, word.c_str());
	std::cout << totalPrice;
	sqlite3_stmt * stmt = NULL;
	char * sqlQuery = "INSERT INTO OrderTable ('Date','Telephone','TotalSum') VALUES (?,?,?);";
	puts(sqlQuery);
	sqlite3_prepare_v2(db, sqlQuery, strlen(sqlQuery) + 1, &stmt, NULL);

	sqlite3_bind_text(stmt, 1, buffer, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, tel, -1, SQLITE_STATIC);
	sqlite3_bind_double(stmt, 3, totalPrice);
	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR)
	{
		puts("ERROR : Order");	
		free(tel);
		return -1;
	}
	else
	{
		sqlite3_finalize(stmt);
		return 1;
	}
	free(tel);
	return -1;

}
int sqlite_db::db_orderTableId()
{
	int addedId = -1;
	sqlite3_stmt * stmt = NULL;
	char * sqlQuery = "SELECT * FROM OrderTable ORDER BY ID DESC LIMIT 1;";
	sqlite3_prepare_v2(db, sqlQuery, strlen(sqlQuery) + 1, &stmt, NULL);

	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR)
	{
		puts("ERROR : Order");
		return -1;
	}
	else
	{
		addedId = sqlite3_column_int(stmt, 0);
		sqlite3_finalize(stmt);
		return addedId;
	}
	return addedId;
}
int sqlite_db::db_placeOrder(Product product, int count,int orderTableId)
{
	int rc = -1;
	for (int i = 1; i <= count;i++)
	{
		sqlite3_stmt * stmt = NULL;
		char * sqlQuery = "INSERT INTO OrderProductBridge ('OProductId','OOrderId') VALUES (?,?);";
		int productId = product.Product_getId();
		sqlite3_prepare_v2(db, sqlQuery, strlen(sqlQuery) + 1, &stmt, NULL);
		sqlite3_bind_int(stmt, 1, productId);
		sqlite3_bind_int(stmt, 2, orderTableId);


	     rc = sqlite3_step(stmt);
		if (rc == SQLITE_ERROR)
		{
			puts("ERROR : Order");
			return -1;
		}
		else
		{
			sqlite3_finalize(stmt);
		}
	}
	return rc;
}

std::vector<int> sqlite_db::db_getNewest()
{
	std::vector<int> products(3);
	sqlite3_stmt * stmt = NULL;
	char * sqlQuery = "SELECT * FROM ProductTable ORDER BY Id DESC LIMIT 3;";
	sqlite3_prepare_v2(db, sqlQuery, strlen(sqlQuery) + 1, &stmt, NULL);
	int rc;
	for (int i = 0; i < 3; i++)
	{
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_ERROR)
		{
			printf("SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		printf("Rc is %d\n", rc);
		products[i] = sqlite3_column_int(stmt, 0);
	}
	sqlite3_finalize(stmt);
	return products;
}
