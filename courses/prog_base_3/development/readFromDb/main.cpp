#include "stdafx.h"
#include <string>
#include <iostream>
#include "Product.h"
#include "Company.h"
#include <cpprest\http_listener.h>

using namespace web::http::experimental::listener;
using namespace web::http;
using namespace web;

#include "sqlite_db.h"
#include "html_generator.h"
#include "Basket.h"
using namespace std;

http_listener listener(L"http://localhost:8090");

sqlite_db db("test_db");
Basket basket = Basket();

void main_page_responser(http_request request) {
	Company company = db.db_getCompany();
	std::vector<std::string> table_names;
	html_generator html_gen("http://localhost:8090");
	http_response response(status_codes::OK);
	response.headers().add(U("Content-Type"), U("text/html; charset=utf-8"));
	response.set_body(html_gen.html_homePage(company));
	request.reply(response);
}
void admin_page_responser(http_request request) {
	std::vector<std::string> table_names;
	html_generator html_gen("http://localhost:8090");
	http_response response(status_codes::OK);
	response.headers().add(U("Content-Type"), U("text/html; charset=utf-8"));
	response.set_body(html_gen.html_tableListHtml());
	request.reply(response);
}
void table_page_responser(http_request request) {
	auto http_get_vars = uri::split_query(request.request_uri().query());
	auto path = uri::split_path(request.request_uri().path());
	std::string table_name;
	if (path.at(1) == U("Products") || path.at(1) == U("ProductTable"))
	{
		table_name = "ProductTable";
	}
	else if (path.at(1) == U("Orders") || path.at(1) == U("OrderTable"))
	{
		table_name = "OrderTable";
	}
	else if (path.at(1) == U("Company"))
	{
		table_name = "Company";
	}

	

	if (path.size() >= 3) {
		puts("IN PATH 3");
		if (path.at(2) == U("delete")) {
			std::string id = std::string(path.at(3).begin(), path.at(3).end());
			db.delete_table_row(table_name, id);
		}
		if (path.at(2) == U("edit")) {
			puts("in edit");
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
void product_page_responser(http_request request) {
	auto http_get_vars = uri::split_query(request.request_uri().query());
	auto path = uri::split_path(request.request_uri().path());
	Company company = db.db_getCompany();
	html_generator html_gen("http://localhost:8090");
	std::vector<int> pIds = db.db_getIds();
	int vecSize = pIds.size();
	std::wstring out;
	if (path.size() == 1) {
		std::wstring htmlBody;
		for (int i = 0; i < vecSize; i++){
			Product product = db.db_get_product(pIds.at(i));
			htmlBody += html_gen.html_productPage(product);
		}
		out = html_gen.html_render_body(htmlBody, company);
		}
	else if (path.size() == 2)
	{
		std::string productId = std::string(path.at(1).begin(), path.at(1).end());
		std::stringstream pId_s(productId);
		int id;
		pId_s >> id;
		std::wstring htmlBody;
		Product product = db.db_get_product(id);
		htmlBody += html_gen.html_productDetailPage(product);
		out = html_gen.html_render_body(htmlBody, company);
	}
	else if (path.size() == 3)
	{
		std::string pIdStr = std::string(path.at(2).begin(), path.at(2).end());
		int id = atoi(pIdStr.c_str());
		Product prBasket = db.db_get_product(id);
		if (path.at(1) == U("AddToBasket"))
		{
			basket.Basket_addItem(prBasket);
		}
		else if (path.at(1) == U("DeleteFromBasket"))
		{
			basket.Basket_remove(prBasket);
		}
		
	}
	http_response response(status_codes::OK);
	response.headers().add(U("Content-Type"), U("text/html; charset=utf-8"));
	response.set_body(out);
	request.reply(response);
}
void basket_page_responser(http_request request) {
	auto http_get_vars = uri::split_query(request.request_uri().query());
	auto path = uri::split_path(request.request_uri().path());
	html_generator html_gen("http://localhost:8090");
	Company company = db.db_getCompany();
	std::vector<Product> products = basket.Basket_getItems();
	std::vector<int> counts = basket.Basket_getCounts();
	int basketSize = products.size();	
	std::wstring out;
	std::wstring htmlBody;
	for (int i = 0; i < basketSize; i++)
	{
		Product product = products.at(i);
		int count = counts.at(i);
		htmlBody += html_gen.html_basketPage(product, count);
	}
	std::string link = "http://localhost:8090/Basket/PlaceOrder/";
	std::wstring wLink = std::wstring(link.begin(), link.end());
	std::wstring btnPlace;
	btnPlace = U("	<script>");
	btnPlace += U("		function placeOrder(){var xhttp = new XMLHttpRequest();xhttp.open('POST','") + wLink + U("',true);xhttp.send()}");
	btnPlace += U("	</script>");
	btnPlace += U(" <div class=\"ordersPlace\">");
	btnPlace += U("<a  title=\"Place Order\" onclick=\"placeOrder()\">Place Order</a>");
	btnPlace += U(" </div>");
	htmlBody += btnPlace;
	out = html_gen.html_render_body(htmlBody, company);
	http_response response(status_codes::OK);
	response.headers().add(U("Content-Type"), U("text/html; charset=utf-8"));
	response.set_body(out);
	request.reply(response);
}
void order_page_responser(http_request request) {
	puts("IN ORDER");
	auto http_get_vars = uri::split_query(request.request_uri().query());
	auto path = uri::split_path(request.request_uri().path());
	html_generator html_gen("http://localhost:8090");
	Company company = db.db_getCompany();
	std::vector<Product> products = basket.Basket_getItems();
	std::vector<int> counts = basket.Basket_getCounts();
	int basketSize = products.size();
	std::vector<int> pIds(basketSize);
	std::vector<int> pCounts(basketSize);
	int rc = db.db_placeOrderTable();
	if (rc == -1)
		return;
	int orderTableId = db.db_orderTableId();
	if (orderTableId == -1)
		return;
	for (int i = 0; i < basketSize; i++)
	{
		Product product = products.at(i);
		int count = counts.at(i);
		
		db.db_placeOrder(product, count, orderTableId);
	}
	std::wstring out;
	http_response response(status_codes::OK);
	response.headers().add(U("Content-Type"), U("text/html; charset=utf-8"));
	response.set_body(out);
	request.reply(response);
}
void server_start()
{

	listener.support(methods::GET, [](http_request request)
	{
		auto http_get_vars = uri::split_query(request.request_uri().query());
		auto path = uri::split_path(request.request_uri().path());

		std::string uri = std::string(request.request_uri().path().begin(), request.request_uri().path().end());

		if (path.size() >= 1) {
			
			if (path.at(0) == U("table")) {
				table_page_responser(request);
				return;
			}
			else if(path.at(0) == U("Products"))
			{ 
				product_page_responser(request);
				return;
			}
			else if (path.at(0) == U("Basket"))
			{
				basket_page_responser(request);
				return;

			}
			else if (path.at(0) == U("Admin"))
			{
				if (path.size() == 1)
				{
					admin_page_responser(request);
					return;
				}
				else
				{
					table_page_responser(request);
					return;
				}	
			}
			else if (path.at(0) == U("Contact"))
			{
				contact_page_responser(request);
				return;

			}
		}
		main_page_responser(request);
	});
	listener.support(methods::POST, [](http_request request)
	{
		auto http_get_vars = uri::split_query(request.request_uri().query());
		auto path = uri::split_path(request.request_uri().path());
		std::string uri = std::string(request.request_uri().path().begin(), request.request_uri().path().end());

		std::cout << uri;
		if (path.size() >= 1) {

			if (path.at(0) == U("Products"))
			{
				product_page_responser(request);
				return;
			}
			else if (path.at(0) == U("Basket"))
			{
				order_page_responser(request);
				return;

			}

			
		}
		main_page_responser(request);
	});
	listener.support(methods::DEL, [](http_request request)
	{
		auto http_get_vars = uri::split_query(request.request_uri().query());
		auto path = uri::split_path(request.request_uri().path());

		std::string uri = std::string(request.request_uri().path().begin(), request.request_uri().path().end());

		if (path.size() >= 1) {

			if (path.at(0) == U("Products"))
			{
				product_page_responser(request);
				return;
			}
			else if (path.at(0) == U("Admin"))
			{
				if (path.size() == 1)
				{
					admin_page_responser(request);
					return;
				}
				else
				{
					table_page_responser(request);
					return;

				}
			}

		}
		main_page_responser(request);
	});



	listener.open();
}
std::string readFile(std::string fileName)
{

	std::ifstream ifs(fileName);
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
	return content;
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