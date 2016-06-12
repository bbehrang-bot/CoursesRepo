#include "stdafx.h"
#include "html_generator.h"
#include <cpprest\details\basic_types.h>

std::string html_generator::readFile(std::string fileName)
{
	std::ifstream ifs(fileName);
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
	return content;
}

html_generator::html_generator(std::string s_url) : service_url{ s_url }
{
}
std::wstring html_generator::html_render_body(std::wstring body,Company company)
{


	std::string companyName = company.Company_getName();
	std::wstring cName = std::wstring(companyName.begin(), companyName.end());

	std::string companyAddress = company.Company_getAddress();
	std::wstring cAddress = std::wstring(companyAddress.begin(), companyAddress.end());

	std::string companyTelephone = company.Company_getTelephone();
	std::wstring cTelephone = std::wstring(companyTelephone.begin(), companyTelephone.end());

	std::string companyabout = company.Company_getAbout();
	std::string subAbout = companyabout.substr(0, 800);
	std::wstring cAbout = std::wstring(subAbout.begin(), subAbout.end());

	std::wstring html_out;
	html_out = U("<!DOCTYPE html>\n");
	html_out += U("    <head>\n");
	html_out += U("        <title>B.B Clothing</title>\n");
	html_out += U("<style>") + std::wstring(normalize.begin(), normalize.end());
	html_out += U("</style>");
	html_out += U("<style>") + std::wstring(reset.begin(), reset.end());
	html_out += U("</style>");
	html_out += U("<style type = \"text/css\">\n");
	html_out += std::wstring(index.begin(), index.end());
	html_out += U("</style>\n");
	html_out += U("<style>") + std::wstring(stylesheet.begin(), stylesheet.end());
	html_out += U("</style>");
	html_out += U("    </head>\n");
	html_out += U("    <body>\n");
	html_out += U("      <div class=\"wrapper\">");
	html_out += U("          <div class=\"header\">");
	html_out += U("              <div class=\"hashtag\">");
	html_out += U("                 <a href=\"#\">#MENCLOTHING</a>");
	html_out += U("              </div>");
	html_out += U("              <div class=\"logo\">");
	html_out += U("					 <h1><a href=\"http://localhost:8090/\" title='") + cName + U("'>") + cName + U("</a></h1>");
	html_out += U("              </div>");
	html_out += U("              <div class=\"header_operations\">");
	html_out += U("					 <div class=\"header_search  header_ops\"><a href=\"#\" title=\"Search\"></a></div>");
	html_out += U("					 <div class=\"header_basket header_ops\"><a href=\"http://localhost:8090/Basket\" title=\"Basket\"></a></div>");
	html_out += U("              </div>");
	html_out += U("          </div>");
	html_out += U("          <div class=\"navigation\">");
	html_out += U("				<ul class=\"nav-ul\">");
	html_out += U("					 <li><a href=\"http://localhost:8090/Products\" title=\"Shop\">Shop</a></li>");
	html_out += U("					 <li><a href=\"http://localhost:8090/Contact\" title=\"Contact Us\">Contact</a></li>");
	html_out += U("					 <li><a href=\"http://localhost:8090/About\" title=\"About Us\">About</a></li>");
	html_out += U("			    </ul>");
	html_out += U("          </div>");
	html_out += U("		<div class=\"product-wrapper\">");
	html_out += body;
	html_out += U("		</div>");
	html_out += U("		</div>");
	html_out += U("				<div class=\"footer\">");
	html_out += U("					<ul class=\"footer-ul\">");
	html_out += U("						<li><a href=\"#\" title=\"Shop\">Shop</a></li>");
	html_out += U("						<li><a href=\"#\" title=\"Contact\">Contact</a></li>");
	html_out += U("						<li><a href=\"#\" title=\"About\">About</a></li>");
	html_out += U("				   </ul>");
	html_out += U("				<div class=\"social-media-container\">");
	html_out += U("					<div class=\"social-inner\">");
	html_out += U("						<div class=\"social-media gp\"><a href=\"#\" title=\"Google Plus\"></a></div>");
	html_out += U("						<div class=\"social-media tw\"><a href=\"#\" title=\"Twitter\"></a></div>");
	html_out += U("						<div class=\"social-media fb\"><a href=\"#\" title=\"Facebook\"></a></div>");
	html_out += U("				    </div>");
	html_out += U("				</div>");
	html_out += U("				<div class=\"dev\">");
	html_out += U("					<p>Designed/Developed by</p>");
	html_out += U("					<h5>Brainiac</h5>");
	html_out += U("				</div>");
	html_out += U("			</div>");
	html_out += U("		</body>");
	html_out += U("	</html>");
	return html_out;

}
std::wstring html_generator::html_productPage(Product product)
{
	
	 std::wstring html_out;
	 std::string productName = product.Product_getName();
	 std::wstring pName = std::wstring(productName.begin(), productName.end());

	 float productPrice = product.Product_getPrice();
	 std::string pPriceStr = std::to_string(productPrice);
	 std::string pPriceStrSub = pPriceStr.substr(0, 6);
	 std::wstring pPrice = std::wstring(pPriceStrSub.begin(), pPriceStrSub.end());

	 std::string productDescription = product.Product_getDescription();
	 std::wstring pDes = std::wstring(productDescription.begin(), productDescription.end());

	 std::string productImageUrl = product.Product_getImageUrl();
	 std::wstring pImageUrl = std::wstring(productImageUrl.begin(), productImageUrl.end());

	 int productInStock = product.Product_getInStock();

	 int id = product.Product_getId();
	 std::string id_str = std::to_string(id);
	 std::string link = "http://localhost:8090/Products/";
	 link.append(id_str);

	 std::wstring wLink = std::wstring(link.begin(), link.end());

	 html_out += U("			<div class=\"product-frame\">");
	 html_out += U("				<a href ='") + wLink + U("'title='") + pName + U("'>");
	 html_out += U("					<div class=\"product-image\">");
	 html_out += U("						<img src='") + pImageUrl + U("'>");
	 html_out += U("					</div>");
	 html_out += U("					<div class=\"product-name\">");	
	 html_out += U("						<span>") + pName + U("</span>");
	 html_out += U("					</div>");
	 html_out += U("					<div class=\"product-price\">");
	 html_out += U("						<span>")+ pPrice + U("</span>");
	 html_out += U("					</div>");
	 html_out += U("				</a>");
	 html_out += U("			</div>");
	 return html_out;
}
std::wstring html_generator::html_productDetailPage(Product product)
{
	std::wstring html_out;
	std::string productName = product.Product_getName();
	std::wstring pName = std::wstring(productName.begin(), productName.end());

	float productPrice = product.Product_getPrice();
	std::string pPriceStr = std::to_string(productPrice);
	std::string pPriceStrSub = pPriceStr.substr(0, 6);
	std::wstring pPrice = std::wstring(pPriceStrSub.begin(), pPriceStrSub.end());

	std::string productDescription = product.Product_getDescription();
	std::wstring pDes = std::wstring(productDescription.begin(), productDescription.end());

	std::string productImageUrl = product.Product_getImageUrl();
	std::wstring pImageUrl = std::wstring(productImageUrl.begin(), productImageUrl.end());


	int id = product.Product_getId();
	std::string id_str = std::to_string(id);
	std::string link = "http://localhost:8090/Products/AddToBasket/";
	link.append(id_str);
	std::wstring wLink = std::wstring(link.begin(), link.end());

	int productInStock = product.Product_getInStock();
	html_out += U("			<div class=\"product-detail-wrapper\">");
	html_out += U("				<div class=\"product-detail-frame\">");
	html_out += U("					<div class=\"product-detail-frame\">");
	html_out += U("						<div class=\"product-detail-image\">");
	html_out += U("							<img src='") + pImageUrl + U("'>");
	html_out += U("						</div>");
	html_out += U("						<div class=\"product-detail-name\">");
	html_out += U("							<span class=\"pdName\">") + pName + U("</span>");
	html_out += U("						</div>");
	html_out += U("						<div class=\"product-detail-price\">");
	html_out += U("							<span class=\"pdPrice\">€ ") + pPrice + U("</span>");
	html_out += U("						</div>");
	html_out += U("						<div class=\"product-detail-info\">");
	html_out += U("							<p>") + pDes + U("</p>");
	html_out += U("						</div>");
	html_out += U("						<script>");
	html_out += U("									function addToBasket(){var xhttp = new XMLHttpRequest();xhttp.open('POST','") + wLink + U("',true);xhttp.send()}");
	html_out += U("						</script>");
	html_out += U("						<div class=\"order\">");
	html_out += U("							<a  onclick=\"addToBasket()\" title=\"Add to Basket\">Add To Basket</a>");
	html_out += U("						</div>");

	html_out += U("					</div>");
	html_out += U("				</div>");
	html_out += U("			</div>");
	return html_out;

}
std::wstring html_generator::html_basketPage(Product product,int count)
{
	std::wstring html_out;
	std::string productName = product.Product_getName();
	std::wstring pName = std::wstring(productName.begin(), productName.end());

	float productPrice = product.Product_getPrice();
	std::string pPriceStr = std::to_string(productPrice);
	std::string pPriceStrSub = pPriceStr.substr(0, 6);
	std::wstring pPrice = std::wstring(pPriceStrSub.begin(), pPriceStrSub.end());

	float ptimesCount = productPrice * count;
	pPriceStr = std::to_string(ptimesCount);
	pPriceStrSub = pPriceStr.substr(0, 6);
	std::wstring pPriceCount = std::wstring(pPriceStrSub.begin(), pPriceStrSub.end());



	std::string productDescription = product.Product_getDescription();
	std::wstring pDes = std::wstring(productDescription.begin(), productDescription.end());

	std::string productImageUrl = product.Product_getImageUrl();
	std::wstring pImageUrl = std::wstring(productImageUrl.begin(), productImageUrl.end());

	std::string countStr = std::to_string(count);
	std::wstring count_wstr = std::wstring(countStr.begin(), countStr.end());
	int productInStock = product.Product_getInStock();

	int id = product.Product_getId();
	std::string id_str = std::to_string(id);
	std::string link = "http://localhost:8090/Products/DeleteFromBasket/";
	link.append(id_str);
	std::wstring wLink = std::wstring(link.begin(), link.end());

	html_out += U("			<div class=\"orders\">");
	html_out += U("				<div class=\"ordersImage\">");
	html_out += U("					<img src='") + pImageUrl + U("'>");
	html_out += U("				</div>");
	html_out += U("				<script>");
	html_out += U("							function deleteFromBasket(){var xhttp = new XMLHttpRequest();xhttp.open('DELETE','") + wLink + U("',true);xhttp.send()}");
	html_out += U("				</script>");
	html_out += U("				<div class=\"ordersRemove\">");
	html_out += U("					<a title=\"Remove\" onclick=\"deleteFromBasket()\"></a>");
	html_out += U("				</div>");
	html_out += U("				<div class=\"orderCount\">");
	html_out += U("					<div class=\"orderInfoframe\">");
	html_out += U("						<span class=\"countLabes\">Total items :</span><span class=\"countValues\">") + count_wstr +U("</span>");
	html_out += U("					</div>");
	html_out += U("					<div class=\"orderInfoframe\">");
	html_out += U("						<span class=\"countLabes\">Total sum :</span><span class=\"countValues\">€ ") + pPriceCount + U("</span>");
	html_out += U("					</div>");
	html_out += U("				</div>");
	html_out += U("				<div class=\"ordersName\">");
	html_out += U("					<span>") + pName + U("</span>");
	html_out += U("				</div>");
	html_out += U("				<div class=\"ordersPrice\">");
	html_out += U("					<span>€ ") + pPrice + U("<span class=\"psubinfo\">for each unit</span></span>");
	html_out += U("				</div>");
	html_out += U("			</div>");
	return html_out;
}
std::wstring html_generator::html_homePage(Company company)
{
	
	
	std::string companyName = company.Company_getName();
	std::wstring cName = std::wstring(companyName.begin(), companyName.end());

	std::string companyAddress = company.Company_getAddress();
	std::wstring cAddress = std::wstring(companyAddress.begin(), companyAddress.end());

	std::string companyTelephone = company.Company_getTelephone();
	std::wstring cTelephone = std::wstring(companyTelephone.begin(), companyTelephone.end());

	std::string companyabout = company.Company_getAbout();
	std::string subAbout = companyabout.substr(0, 800);
	std::wstring cAbout = std::wstring(subAbout.begin(), subAbout.end());


	std::wstring html_out;
	html_out = U("<!DOCTYPE html>\n");
	html_out += U("    <head>\n");
	html_out += U("        <title>B.B Clothing</title>\n");
	html_out += U("<style>") + std::wstring(normalize.begin(), normalize.end());
	html_out += U("</style>");
	html_out += U("<style>") + std::wstring(reset.begin(), reset.end());
	html_out += U("</style>");
	html_out += U("<style type = \"text/css\">\n");
	html_out += std::wstring(index.begin(), index.end());
	html_out += U("</style>\n");
	html_out += U("<style>") + std::wstring(stylesheet.begin(), stylesheet.end());
	html_out += U("</style>");
	html_out += U("    </head>\n");
	html_out += U("    <body>\n");
	html_out += U("      <div class=\"wrapper\">");
	html_out += U("          <div class=\"header\">");
	html_out += U("              <div class=\"hashtag\">");
	html_out += U("                 <a href=\"#\">#MENCLOTHING</a>");
	html_out += U("              </div>");
	html_out += U("              <div class=\"logo\">");
	html_out += U("					 <h1><a href=\"http://localhost:8090/\" title='") + cName + U("'>") + cName + U("</a></h1>");
	html_out += U("              </div>");
	html_out += U("              <div class=\"header_operations\">");
	html_out += U("					 <div class=\"header_search  header_ops\"><a href=\"#\" title=\"Search\"></a></div>");
	html_out += U("					 <div class=\"header_basket header_ops\"><a href=\"http://localhost:8090/Basket\" title=\"Basket\"></a></div>");
	html_out += U("              </div>");
	html_out += U("          </div>");
	html_out += U("          <div class=\"navigation\">");
	html_out += U("				<ul class=\"nav-ul\">");
	html_out += U("					 <li><a href=\"http://localhost:8090/Products\" title=\"Shop\">Shop</a></li>");
	html_out += U("					 <li><a href=\"http://localhost:8090/Contact\" title=\"Contact Us\">Contact</a></li>");
	html_out += U("					 <li><a href=\"http://localhost:8090/About\" title=\"About Us\">About</a></li>");
	html_out += U("			    </ul>");
	html_out += U("          </div>");
	html_out += U("          <div class=\"sliderMid\">");
	html_out += U("				 <img src=\"http://i.imgur.com/U8sFcaJ.jpg\">");
	html_out += U("          </div>");
	html_out += U("          <div class=\"featured\">");
	html_out += U("				<div class=\"titles\"><h2>Featured</h2></div>");
	html_out += U("				<div class=\"futured-product\" >");
	html_out += U("					<a href=\"#\" title=\"Product1\">");
	html_out += U("						<div class=\"futured-gname\"><h3>Jeans</h2></div>");
	html_out += U("						<div class=\"futured-image\"><img src=\"http://i.imgur.com/fXu6xwa.jpg\"/></div>");
	html_out += U("				    </a>");
	html_out += U("             </div>");

	html_out += U("				<div class=\"futured-product-mid\" >");
	html_out += U("					<a href=\"#\" title=\"Product2\">");
	html_out += U("						<div class=\"futured-gname\"><h3>Jeans</h2></div>");
	html_out += U("						<div class=\"futured-image\"><img src=\"http://i.imgur.com/KThfiSM.jpg\"/></div>");
	html_out += U("				    </a>");
	html_out += U("             </div>");

	html_out += U("				<div class=\"futured-product fpLeft\" >");
	html_out += U("					<a href=\"#\" title=\"Product2\">");
	html_out += U("						<div class=\"futured-gname\"><h3>Jeans</h2></div>");
	html_out += U("						<div class=\"futured-image\"><img src=\"http://i.imgur.com/T9EJyRn.jpg\"/></div>");
	html_out += U("				    </a>");
	html_out += U("             </div>");
	html_out += U("				<div class=\"futured_slogan\"><p>new is always better :)</p></div>");
	html_out += U("				<div class=\"more-btn\"><a href=\"#\">more...</a></div>");


	html_out += U("            </div>");
	html_out += U("				<div class=\"onStreets\">");
	html_out += U("				<div class=\"streetSliders\">");
	html_out += U("					<img src=\"http://i.imgur.com/WIwYk2w.jpg\"/>");
	html_out += U("				</div>");
	html_out += U("				<div class=\"streetMid\">");
	html_out += U("					<h4>On</br>The<br>Streets</h4>");
	html_out += U("				</div>");
	html_out += U("				<div class=\"streetSlidersRight\">");
	html_out += U("					<img src=\"http://i.imgur.com/qUFzuMM.jpg\"/>");
	html_out += U("				</div>");
	html_out += U("				</div>");
	html_out += U("				<div class=\"about-brief\">");
	html_out += U("						<div class=\"titles\"><h2>ABOUT US</h2></div>");
	html_out += U("						<div class=\"text\"><p>");
	html_out += cAbout;
	html_out += U("						</p>");
	html_out += U("				</div>");
	html_out += U("						<div class=\"more-btn btn-about\"><a href=\"#\">more...</a></div>");
	html_out += U("			</div>");
	html_out += U("		</div>");
	html_out += U("				<div class=\"footer\">");
	html_out += U("					<ul class=\"footer-ul\">");
	html_out += U("						<li><a href=\"#\" title=\"Shop\">Shop</a></li>");
	html_out += U("						<li><a href=\"#\" title=\"Contact\">Contact</a></li>");
	html_out += U("						<li><a href=\"#\" title=\"About\">About</a></li>");
	html_out += U("				   </ul>");
	html_out += U("				<div class=\"social-media-container\">");
	html_out += U("					<div class=\"social-inner\">");
	html_out += U("						<div class=\"social-media gp\"><a href=\"#\" title=\"Google Plus\"></a></div>");
	html_out += U("						<div class=\"social-media tw\"><a href=\"#\" title=\"Twitter\"></a></div>");
	html_out += U("						<div class=\"social-media fb\"><a href=\"#\" title=\"Facebook\"></a></div>");
	html_out += U("				    </div>");
	html_out += U("				</div>");
	html_out += U("				<div class=\"dev\">");
	html_out += U("					<p>Designed/Developed by</p>");
	html_out += U("					<h5>Brainiac</h5>");
	html_out += U("				</div>");
	html_out += U("			</div>");
	html_out += U("		</body>");
	html_out += U("	</html>");
	return html_out;
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
			html_out += U("          <th>") + std::wstring(col.first.begin(), col.first.end()) + U("</th>\n");
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
			for (auto col : row_data) {
				if (col.first == "id" || col.first == "Id" || col.first == "iD" || col.first == "ID")
					continue;
				html_out += U("    <tr>\n");
				html_out += U("      <td>") + std::wstring(col.first.begin(), col.first.end()) + U(": <input type='text' name='") + std::wstring(col.first.begin(), col.first.end()) + U("' value='") + std::wstring(col.second.begin(), col.second.end()) + U("'></td>\n");
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