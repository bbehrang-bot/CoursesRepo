#pragma once

#include <string>
#include <cctype>
#include <vector>
#include <map>
#include "Company.h"
#include "sqlite_db.h"

class html_generator {
private:
	std::string service_url;
	std::string readFile(std::string fileName);

public:
	std::string index = readFile("index.css");
	std::string normalize = readFile("normalize.css");
	std::string reset = readFile("reset.css");
	std::string stylesheet = readFile("stylesheet.css");
	html_generator(std::string s_url);
	std::wstring table_list_html(const std::vector<std::string>& table_names);
	std::wstring table_data_html(const std::vector<std::vector<std::pair<std::string, std::string>>>& table_data, const std::string table_name);
	std::wstring input_form_html(const std::vector<std::vector<std::pair<std::string, std::string>>>& table_data, const std::string table_name);
	std::wstring input_form_html_edit(const std::vector<std::vector<std::pair<std::string, std::string>>>& table_data, const std::string table_name);
	std::wstring html_render_body(std::wstring body,Company company);
	std::wstring html_homePage(Company company);
	std::wstring html_productPage(Product product);
	std::wstring html_productDetailPage(Product product);
	std::wstring html_basketPage(Product product,int count);
private:
	std::string find_id(std::vector<std::pair<std::string, std::string>> row_data);
};