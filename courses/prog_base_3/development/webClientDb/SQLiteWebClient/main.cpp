#include "stdafx.h"
#include <string>
#include <iostream>

#include <cpprest\http_listener.h>

using namespace web::http::experimental::listener;
using namespace web::http;
using namespace web;

#include "sqlite_db.h"
#include "html_generator.h"

using namespace std;

http_listener listener(L"http://localhost:8090");

sqlite_db db("test_db");

void main_page_responser(http_request request) {
	std::vector<std::string> table_names;
	html_generator html_gen("http://localhost:8090");
	
	db.get_all_table_names(table_names);

	http_response response(status_codes::OK);
	response.headers().add(U("Content-Type"), U("text/html; charset=utf-8"));
	response.set_body(html_gen.table_list_html(table_names));
	request.reply(response);
}

void table_page_responser(http_request request) {
	auto http_get_vars = uri::split_query(request.request_uri().query());
	auto path = uri::split_path(request.request_uri().path());

	std::string table_name = std::string(path.at(1).begin(), path.at(1).end());
	
	if (path.size() == 4) {
		if (path.at(2) == U("delete")) {
			std::string id = std::string(path.at(3).begin(), path.at(3).end());
			db.delete_table_row(table_name, id);
		}
		if (path.at(2) == U("edit")) {
		std:cout << "BAAAM";
			std::string id = std::string(path.at(3).begin(), path.at(3).end());
			db.edit_row_into_table(table_name, id, http_get_vars);
		}
	}
	if (path.size() == 3) {
		if (path.at(2) == U("add")) {
			db.insert_row_into_table(table_name, http_get_vars);
		}
		
		}
	
		
	
	

	
	html_generator html_gen("http://localhost:8090");

	std::vector<std::vector<std::pair<std::string, std::string>>> table_data;
	db.get_table_data(table_name, table_data, 50, 0);

	http_response response(status_codes::OK);
	response.headers().add(U("Content-Type"), U("text/html; charset=utf-8"));
	response.set_body(html_gen.table_data_html(table_data, table_name));
	request.reply(response);
}

void server_start()
{
	
	listener.support(methods::GET, [](http_request request)
	{
		auto http_get_vars = uri::split_query(request.request_uri().query());
		auto path = uri::split_path(request.request_uri().path());

		std::string uri = std::string(request.request_uri().path().begin(), request.request_uri().path().end());

		if (path.size() > 1) {
			if (path.at(0) == U("table")) {
				table_page_responser(request);
				return;
			}
		}

		main_page_responser(request);

	});
	
	listener.open();
}

int main()
{
	if (db.open()) {
		cout << "Can't open database!!!" << endl;
	}

	server_start();;

	getchar();
	db.close();
    return 0;
}
