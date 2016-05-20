#pragma once

#include <string>
#include <cctype>
#include <vector>
#include <map>

class html_generator {
private:
	std::string service_url;
public:
	html_generator(std::string s_url);
	std::wstring table_list_html(const std::vector<std::string>& table_names);
	std::wstring table_data_html(const std::vector<std::vector<std::pair<std::string, std::string>>>& table_data, const std::string table_name);
	std::wstring input_form_html(const std::vector<std::vector<std::pair<std::string, std::string>>>& table_data, const std::string table_name);
	std::wstring input_form_html_edit(const std::vector<std::vector<std::pair<std::string, std::string>>>& table_data, const std::string table_name);
private:
	std::string find_id(std::vector<std::pair<std::string, std::string>> row_data);
};