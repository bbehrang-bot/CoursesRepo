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
bool isAdmin;
sqlite_db db("test_db");
Basket basket = Basket();
Company company("-1","-1","-1","-1");
void main_page_responser(http_request request) {
	std::vector<std::string> table_names;
	html_generator html_gen("http://localhost:8090");
	http_response response(status_codes::OK);
	response.headers().add(U("Content-Type"), U("text/html; charset=utf-8"));
	response.set_body(html_gen.html_homePage(company));
	request.reply(response);
}
void about_page_responser(http_request request) {
	html_generator html_gen("http://localhost:8090");
	http_response response(status_codes::OK);
	std::wstring html_out = html_gen.html_aboutFull(company);
	std::wstring out = html_gen.html_render_body(html_out, company);
	response.headers().add(U("Content-Type"), U("text/html; charset=utf-8"));
	response.set_body(out);
	request.reply(response);
}
void search_page_responser(http_request request) {
	auto http_get_vars = uri::split_query(request.request_uri().query());
	auto path = uri::split_path(request.request_uri().path());
	//std::wstring req = request.request_uri().to_string();
	//std::string v = std::string(req.begin(), req.end());
	//std::cout << v;
	
	std::wstring html_out;
	std::wstring out;
	html_generator html_gen("http://localhost:8090");
	std::vector<int> recievedIds = db.db_search(http_get_vars);
	if (recievedIds.size() == 0)
	{
		html_out = U("<div class=\"not_found\"><p>No results found</p>");
	}
	else
	{
		for (int i = 0; i < recievedIds.size(); i++)
		{
			Product product = db.db_get_product(recievedIds.at(i));
			html_out += html_gen.html_productPage(product);
		}
	}
	out = html_gen.html_render_body(html_out, company);
	
	http_response response(status_codes::OK);
	response.headers().add(U("Content-Type"), U("text/html; charset=utf-8"));
	response.set_body(out);
	request.reply(response);
}
void contact_page_responser(http_request request) {
	auto postData = uri::split_query(request.extract_string().get());
	auto http_get_vars = uri::split_query(request.request_uri().query());
	auto path = uri::split_path(request.request_uri().path());
	std::wstring html_out;
	std::wstring out;
	html_generator html_gen("http://localhost:8090");
	printf("Path size is %d", path.size());
	if (path.size() > 1)
	{
		int res = db.db_sendMsg(postData);
		if (res == 1)
		{
			html_out = html_gen.html_Alert("Message Sent...");
		}
		else
			html_out = html_gen.html_Alert("Something went wrong , try again later...");
	}
	else
	{
		puts("in Contanct");
		html_out += html_gen.html_ContactPage();
		
		
	}
	out = html_gen.html_render_body(html_out, company);

	http_response response(status_codes::OK);
	response.headers().add(U("Content-Type"), U("text/html; charset=utf-8"));
	response.set_body(out);
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
	
	auto postData = uri::split_query(request.extract_string().get());
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
		if (path.at(2) == U("delete")) {
			std::string id = std::string(path.at(3).begin(), path.at(3).end());
			db.delete_table_row(table_name, id);
		}
		if (path.at(2) == U("edit")) {
			puts("in edit");
			std::string id = std::string(path.at(3).begin(), path.at(3).end());
			db.edit_row_into_table(table_name, id, postData);
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
	if (path.at(1) == U("Orders"))
	{
		response.set_body(html_gen.html_ordersManagment(table_data,db));
	}
	else
		response.set_body(html_gen.table_data_html(table_data, table_name));
	request.reply(response);
}
void product_page_responser(http_request request) {
	auto http_get_vars = uri::split_query(request.request_uri().query());
	auto path = uri::split_path(request.request_uri().path());
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
	std::vector<Product> products = basket.Basket_getItems();
	std::vector<int> counts = basket.Basket_getCounts();
	int basketSize = products.size();	
	std::wstring out;
	std::wstring htmlBody;
	int totalItems =0 ;
	double totalPrice = 0;
	for (int i = 0; i < basketSize; i++)
	{
		Product product = products.at(i);
		int count = counts.at(i);
		totalItems += count;
		totalPrice += product.Product_getPrice() * count;
		htmlBody += html_gen.html_basketPage(product, count);
	}
	
	std::wstring btnPlace = html_gen.html_buyForm(totalPrice,totalItems);
	htmlBody += btnPlace;
	out = html_gen.html_render_body(htmlBody, company);
	http_response response(status_codes::OK);
	response.headers().add(U("Content-Type"), U("text/html; charset=utf-8"));
	response.set_body(out);
	request.reply(response);
}
void order_page_responser(http_request request) {
	auto postData = uri::split_query(request.extract_string().get());
	auto http_get_vars = uri::split_query(request.request_uri().query());
	auto path = uri::split_path(request.request_uri().path());
	html_generator html_gen("http://localhost:8090");
	
	std::wstring out;
	std::vector<Product> products = basket.Basket_getItems();
	std::vector<int> counts = basket.Basket_getCounts();
	int basketSize = products.size();
	std::vector<int> pIds(basketSize);
	std::vector<int> pCounts(basketSize);
	int totalItems = 0;
	double totalPrice = 0;
	for (int i = 0; i < basketSize; i++)
	{
		Product product = products.at(i);
		int count = counts.at(i);
		totalPrice += product.Product_getPrice() * count;
	}
	int rc = db.db_placeOrderTable(postData,totalPrice);
	if (rc != SQLITE_OK || rc != SQLITE_DONE)
	{ 
		out = html_gen.html_Alert("Something went wrong :(");
	}
		
	int orderTableId = db.db_orderTableId();
	if (orderTableId == -1)
	{
		out = html_gen.html_Alert("Something went wrong :(");
	}
		
	for (int i = 0; i < basketSize; i++)
	{
		Product product = products.at(i);
		int count = counts.at(i);
		totalPrice += product.Product_getPrice() * count;
		db.db_placeOrder(product, count, orderTableId);
	}
	if(rc == SQLITE_OK || rc == SQLITE_DONE || orderTableId != -1 || orderTableId != 0)
		 out = html_gen.html_Alert("Order Placed, we will contact you soon");
	
	http_response response(status_codes::OK);
	response.headers().add(U("Content-Type"), U("text/html; charset=utf-8"));
	response.set_body(html_gen.html_render_body(out,company));
	request.reply(response);
	basket.Basket_removeAll();
}
void server_start()
{
	isAdmin = false;
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
			if (path.at(0) == U("About")) {
				about_page_responser(request);
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
					if(path.at(1) == U("Login"))
					{ 
						admin_login_responser();
					}
					else
					{ 
						table_page_responser(request);
						return;
					}
					
				}	
			}
			else if (path.at(0) == U("Contact"))
			{
				contact_page_responser(request);
				return;
			}
			else if (path.at(0) == U("Search"))
			{
				search_page_responser(request);
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
	company = db.db_getCompany();
	server_start();;

	getchar();
	db.close();
	listener.close();
	return 0;
}