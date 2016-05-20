#include "stdafx.h"
#include "html_generator.h"
#include <cpprest\details\basic_types.h>

html_generator::html_generator(std::string s_url) : service_url{ s_url }
{
}

std::wstring html_generator::table_list_html(const std::vector<std::string>& table_names)
{
	std::wstring html_out;
	html_out = U("<!DOCTYPE html>\n"); 
	html_out += U("  <html>\n");
	html_out += U("    <head>\n");
	html_out += U("        <title>SQLite DB Explorer</title>\n");
	html_out += U("    </head>\n");
	html_out += U("    <body>\n");
	html_out += U("      <table border=\"1\" cellpadding=\"5\" cellspacing=\"5\">\n");

	html_out += U("        <tr>\n");
	html_out += U("          <th>Table in DB</th>\n");
	html_out += U("        </tr>\n");

	for (std::string table_name : table_names) {
		html_out += U("        <tr>\n");
		html_out += U("          <td>\n");
		html_out += U("            <a href=\"") + std::wstring(service_url.begin(), service_url.end()) + U("/") + U("table/") + std::wstring(table_name.begin(), table_name.end()) + U("\">");
		html_out += std::wstring(table_name.begin(), table_name.end()) + U("</a>\n");
	    html_out += U("           </td>\n");
		html_out += U("        </tr>\n");
	}

	html_out += U("      </table>\n");
	html_out += U("    </body>\n");
	html_out += U("  </html>\n");
	return html_out;
}

std::wstring html_generator::table_data_html(const std::vector<std::vector<std::pair<std::string, std::string>>>& table_data, const std::string table_name)
{
	std::wstring html_out;
	html_out = U("<!DOCTYPE html>\n");
	html_out += U("  <html>\n");
	html_out += U("    <head>\n");
	html_out += U("        <title>SQLite DB Explorer</title>\n");
	html_out += U("    </head>\n");
	html_out += U("    <body>\n");
	html_out += U("		<h2>Table data:</h2>\n");
	html_out += U("      <table border=\"1\" cellpadding=\"5\" cellspacing=\"5\">\n");
	if (table_data.size() > 0) {
		html_out += U("        <tr>\n");
		for (auto col : table_data.at(0)) {
			html_out += U("          <th>") + std::wstring(col.first.begin(),col.first.end()) + U("</th>\n");
		}
		html_out += U("          <th></th>\n");
		html_out += U("        </tr>\n");
	}
	for (std::vector<std::pair<std::string, std::string>> row_data : table_data) {
		html_out += U("        <tr>\n");
		for (auto col : row_data) {
			html_out += U("          <td>") + std::wstring(col.second.begin(), col.second.end()) + U("</td>\n");
		}
		std::string row_id = find_id(row_data);

		html_out += U("          <td>");
		html_out += U("<form action='") + std::wstring(service_url.begin(), service_url.end()) + U("/table/") + std::wstring(table_name.begin(), table_name.end()) + U("/delete/") + std::wstring(row_id.begin(), row_id.end()) + U("' method='get'>");
		html_out += U("<input type='submit' value='X'>");
		html_out += U("</form>");
		html_out += U("</td>\n");
		html_out += U("        </tr>\n");
	}
	html_out += U("      </table>\n");
	html_out += U("		<h2>Edit the table:</h2>\n");
	html_out += input_form_html_edit(table_data, table_name);
	html_out += U("     </br>\n");

	html_out += U("      </table>\n");
	html_out += U("		<h2>Add to table:</h2>\n");
	html_out += input_form_html(table_data, table_name);
	html_out += U("     </br>\n");
	html_out += U("<a href='") + std::wstring(service_url.begin(), service_url.end()) + U("/'>") + U("BACK TO MAIN PAGE</a>\n");
	html_out += U("    </body>\n");
	html_out += U("  </html>\n");
	return html_out;
}

std::wstring html_generator::input_form_html(const std::vector<std::vector<std::pair<std::string, std::string>>>& table_data, const std::string table_name)
{
	std::wstring html_out;
	html_out = U("<form action='") + std::wstring(service_url.begin(), service_url.end()) + U("/table/") + std::wstring(table_name.begin(), table_name.end()) + U("/add") + U("' method='get'>");
	html_out += U("  <table border=\"1\" cellpadding=\"5\" cellspacing=\"5\">\n");
	if (table_data.size() > 0) {
		for (auto col : table_data.at(0)) {
			if (col.first == "id" || col.first == "Id" || col.first == "iD" || col.first == "ID")
				continue;
			html_out += U("    <tr>\n");
			html_out += U("      <td>") + std::wstring(col.first.begin(), col.first.end()) + U(": <input type='text' name='") + std::wstring(col.first.begin(), col.first.end()) + U("'></td>\n");
			html_out += U("    </tr>\n");
		}
		html_out += U("    <tr>\n");
		html_out += U("      <td><input type='submit' value='Add Records'></td>\n");
		html_out += U("    </tr>\n");
	}
	html_out += U("  </table>\n");
	html_out += U("</form>\n");
	return html_out;

}
std::wstring html_generator::input_form_html_edit(const std::vector<std::vector<std::pair<std::string, std::string>>>& table_data, const std::string table_name)
{
	std::wstring html_out;
	html_out = U("      <table border=\"1\" cellpadding=\"5\" cellspacing=\"5\">\n");
	if (table_data.size() > 0) {
		html_out += U("        <tr>\n");
		for (auto col : table_data.at(0)) {
			//if (col.first == "id" || col.first == "Id" || col.first == "iD" || col.first == "ID")
				html_out += U("          <th>") + std::wstring(col.first.begin(), col.first.end()) + U("</th>\n");
		}
		html_out += U("          <th></th>\n");
		html_out += U("        </tr>\n");
	}
	for (std::vector<std::pair<std::string, std::string>> row_data : table_data) {
		html_out += U("        <tr>\n");
		for (auto col : row_data) {
			//if (col.first == "id" || col.first == "Id" || col.first == "iD" || col.first == "ID")
				html_out += U("          <td>") + std::wstring(col.second.begin(), col.second.end()) + U("</td>\n");
		}
		std::string row_id = find_id(row_data);

		html_out += U("          <td>");
	html_out += U("<form action='") + std::wstring(service_url.begin(), service_url.end()) + U("/table/") + std::wstring(table_name.begin(), table_name.end()) + U("/edit/") + std::wstring(row_id.begin(), row_id.end()) + U("/' method='get'>");
	html_out += U("  <table border=\"0\" cellpadding=\"5\" cellspacing=\"5\">\n");
	if (table_data.size() > 0) {
		for (auto col :row_data) {
			if (col.first == "id" || col.first == "Id" || col.first == "iD" || col.first == "ID")
				continue;
			html_out += U("    <tr>\n");
			html_out += U("      <td>") + std::wstring(col.first.begin(), col.first.end()) + U(": <input type='text' name='") + std::wstring(col.first.begin(), col.first.end())+U("' value='")+ std::wstring(col.second.begin(), col.second.end()) + U("'></td>\n");
			html_out += U("    </tr>\n");
		}
		html_out += U("    <tr>\n");
		html_out += U("      <td><input type='submit' value='SAVE EDIT'></td>\n");
		html_out += U("    </tr>\n");
	}
	html_out += U("  </table>\n");
	html_out += U("</form>\n");
	html_out += U("</td>\n");
	html_out += U("        </tr>\n");
	}
	html_out += U("      </table>\n");
	return html_out;

	
}
std::string html_generator::find_id(std::vector<std::pair<std::string, std::string>> row_data)
{
	for (std::pair<std::string, std::string> col : row_data) {
		if (col.first == "id" || col.first == "Id" || col.first == "iD" || col.first == "ID")
			return col.second;
	}
	return "0";
}