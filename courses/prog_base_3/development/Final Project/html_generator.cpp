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
	std::string subAbout = companyabout;
	if (companyabout.length() > 800)
	{
		subAbout = companyabout.substr(0, 800);
	}
	std::wstring cAbout = std::wstring(subAbout.begin(), subAbout.end());
	std::wstring jq = std::wstring(jquery.begin(), jquery.end());
	std::wstring validateJs = std::wstring(validation.begin(), validation.end());
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
	html_out += U("<script>");
	html_out += jq;
	html_out += U("</script>");
	html_out += U("<script>");
	html_out += validateJs;
	html_out += U("</script>");
	html_out += U("    </head>\n");
	html_out += U("    <body>\n");
	html_out += U("      <div class=\"wrapper\">");
	html_out += U("          <div class=\"header\">");
	html_out += U("              <div class=\"hashtag\">");
	html_out += U("                 <a href=\"https://twitter.com/hashtag/menclothing\">#MENCLOTHING</a>");
	html_out += U("              </div>");
	html_out += U("              <div class=\"logo\">");
	html_out += U("					 <h1><a href=\"http://localhost:8090/\" title='") + cName + U("'>") + cName + U("</a></h1>");
	html_out += U("              </div>");
	html_out += U("              <div class=\"header_operations\">");
	html_out += U("					 <div class=\"header_basket header_ops\"><a href=\"http://localhost:8090/Basket\" title=\"Basket\"></a></div>");
	html_out += U("					 <div class=\"header_search header_ops\">");
	html_out += U("						 <form class=\"searchForm\" action=\"http://localhost:8090/Search\" method:\"get\">");
	html_out += U("							 <input class=\"searchBox\" type='text' name='productName' placeholder='type product name...'>");
	html_out += U("							 <input class=\"searchBTN\" value='' type='submit'>");
	html_out += U("						 </form>");
	html_out += U("					 </div>");
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
	html_out += U("						<li><a href=\"http://localhost:8090/Products\" title=\"Shop\">Shop</a></li>");
	html_out += U("						<li><a href=\"http://localhost:8090/Contact\" title=\"Contact\">Contact</a></li>");
	html_out += U("						<li><a href=\"http://localhost:8090/About\" title=\"About\">About</a></li>");
	html_out += U("				   </ul>");
	html_out += U("				<div class=\"social-media-container\">");
	html_out += U("					<div class=\"social-inner\">");
	html_out += U("						<div class=\"social-media gp\"><a href=\"https://plus.google.com/+TommyHilfiger/videos\" title=\"Google Plus\"></a></div>");
	html_out += U("						<div class=\"social-media tw\"><a href=\"https://twitter.com/tommyhilfiger\" title=\"Twitter\"></a></div>");
	html_out += U("						<div class=\"social-media fb\"><a href=\"https://www.facebook.com/tommyhilfiger\" title=\"Facebook\"></a></div>");
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

	 double productPrice = product.Product_getPrice();
	 int full = (int)productPrice;
	 double dec = productPrice - full;
	 std::string priceFull = std::to_string(full);
	 std::string dec_str = std::to_string(dec);
	 dec_str = dec_str.substr(1, 3);
	 
	 priceFull += dec_str;
	 std::wstring pPrice = std::wstring(priceFull.begin(), priceFull.end());

	 std::string productDescription = product.Product_getDescription();
	 std::wstring pDes = std::wstring(productDescription.begin(), productDescription.end());

	 std::string productImageUrl = product.Product_getImageUrl();
	 std::wstring pImageUrl = std::wstring(productImageUrl.begin(), productImageUrl.end());


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
	 html_out += U("						<span> €")+ pPrice + U("</span>");
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

	double productPrice = product.Product_getPrice();
	//std::string pPriceStr = std::to_string(productPrice);
	//std::string pPriceStrSub = pPriceStr.substr(0, 6);
	//std::wstring pPrice = std::wstring(pPriceStrSub.begin(), pPriceStrSub.end());
	int full = (int)productPrice;
	double dec = productPrice - full;
	std::string priceFull = std::to_string(full);
	std::string dec_str = std::to_string(dec);
	dec_str = dec_str.substr(1, 3);
	priceFull += dec_str;
	std::wstring pPrice = std::wstring(priceFull.begin(), priceFull.end());


	std::string productDescription = product.Product_getDescription();
	std::wstring pDes = std::wstring(productDescription.begin(), productDescription.end());

	std::string productImageUrl = product.Product_getImageUrl();
	std::wstring pImageUrl = std::wstring(productImageUrl.begin(), productImageUrl.end());


	int id = product.Product_getId();
	std::string id_str = std::to_string(id);
	std::string link = "http://localhost:8090/Products/AddToBasket/";
	std::string link2 = "http://localhost:8090/Products/";
	link2.append(id_str);
	std::wstring wLink2 = std::wstring(link2.begin(), link2.end());
	link.append(id_str);
	std::wstring wLink = std::wstring(link.begin(), link.end());




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
	html_out += U("							<a href='")+ wLink2 + U("'  onclick=\"addToBasket()\" title=\"Add to Basket\">Add To Basket</a>");
	html_out += U("						</div>");

	html_out += U("					</div>");
	html_out += U("				</div>");
	html_out += U("			</div>");
	return html_out;

}
std::wstring html_generator::html_homePagePartial(std::vector<Product> products)
{
	std::string linkUrl = "http://localhost:8090/Products/";
	///////////////////////
	std::string pr1Name = products.at(0).Product_getName();
	std::wstring pr1Name_wString = std::wstring(pr1Name.begin(), pr1Name.end());
	std::string pr1ImageUrl = products.at(0).Product_getImageUrl();
	std::wstring pr1ImageUrl_wString = std::wstring(pr1ImageUrl.begin(), pr1ImageUrl.end());
	std::string p1Id = std::to_string(products.at(0).Product_getId());
	std::wstring p1Id_wString = std::wstring(p1Id.begin(), p1Id.end());
	std::string linkUrl1 = linkUrl;
	linkUrl1.append(p1Id);
	std::wstring link1_ws = std::wstring(linkUrl1.begin(), linkUrl1.end());
	////////////////////////
	std::string pr2Name = products.at(1).Product_getName();
	std::wstring pr2Name_wString = std::wstring(pr2Name.begin(), pr2Name.end());
	std::string pr2ImageUrl = products.at(1).Product_getImageUrl();
	std::wstring pr2ImageUrl_wString = std::wstring(pr2ImageUrl.begin(), pr2ImageUrl.end());
	std::string p2Id = std::to_string(products.at(1).Product_getId());
	std::wstring p2Id_wString = std::wstring(p2Id.begin(), p2Id.end());
	std::string linkUrl2 = linkUrl;
	linkUrl2.append(p2Id);
	std::wstring link2_ws = std::wstring(linkUrl2.begin(), linkUrl2.end());
	////////////////////////////
	std::string pr3Name = products.at(2).Product_getName();
	std::wstring pr3Name_wString = std::wstring(pr3Name.begin(), pr3Name.end());
	std::string pr3ImageUrl = products.at(2).Product_getImageUrl();
	std::wstring pr3ImageUrl_wString = std::wstring(pr3ImageUrl.begin(), pr3ImageUrl.end());
	std::string p3Id = std::to_string(products.at(2).Product_getId());
	std::wstring p3Id_wString = std::wstring(p3Id.begin(), p3Id.end());
	std::string linkUrl3 = linkUrl;
	linkUrl3.append(p3Id);
	std::wstring link3_ws = std::wstring(linkUrl3.begin(), linkUrl3.end());
	////////////////////////////
	std::wstring html_out;
	html_out = U("				<div class=\"futured-product\">");
	html_out += U("					<a href='") + link1_ws + U("' title='") + pr1Name_wString + U("'>");
	html_out += U("						<div class=\"futured-gname\"><h3>") + pr1Name_wString + U("</h3></div>");
	html_out += U("						<div class=\"futured-image\"><img src='") + pr1ImageUrl_wString + U("'/></div>");
	html_out += U("				    </a>");
	html_out += U("             </div>");

	html_out += U("				<div class=\"futured-product-mid\">");
	html_out += U("					<a href='") + link2_ws + U("' title='") + pr2Name_wString + U("'>");
	html_out += U("						<div class=\"futured-gname\"><h3>") + pr2Name_wString + U("</h3></div>");
	html_out += U("						<div class=\"futured-image\"><img src='") + pr2ImageUrl_wString + U("'/></div>");
	html_out += U("				    </a>");
	html_out += U("				    </a>");
	html_out += U("             </div>");

	html_out += U("				<div class=\"futured-product fpLeft\">");
	html_out += U("					<a href='") + link3_ws + U("' title='") + pr3Name_wString + U("'>");
	html_out += U("						<div class=\"futured-gname\"><h3>") + pr3Name_wString + U("</h3></div>");
	html_out += U("						<div class=\"futured-image\"><img src='") + pr3ImageUrl_wString + U("'/></div>");
	html_out += U("				    </a>");
	html_out += U("				    </a>");
	html_out += U("             </div>");
	return html_out;


}
std::wstring html_generator::html_basketPage(Product product,int count)
{
	std::wstring html_out;
	std::string productName = product.Product_getName();
	std::wstring pName = std::wstring(productName.begin(), productName.end());

	double productPrice = product.Product_getPrice();
	int full = (int)productPrice;
	double dec = productPrice - full;
	std::string priceFull = std::to_string(full);
	std::string dec_str = std::to_string(dec);
	dec_str = dec_str.substr(1, 3);
	priceFull += dec_str;
	std::wstring pPrice = std::wstring(priceFull.begin(), priceFull.end());

	double ptimesCount = productPrice * count;
	full = (int)ptimesCount;
    dec = ptimesCount - full;
	priceFull = std::to_string(full);
	dec_str = std::to_string(dec);
	dec_str = dec_str.substr(1, 3);
	priceFull += dec_str;

	std::wstring pPriceCount = std::wstring(priceFull.begin(), priceFull.end());



	std::string productDescription = product.Product_getDescription();
	std::wstring pDes = std::wstring(productDescription.begin(), productDescription.end());

	std::string productImageUrl = product.Product_getImageUrl();
	std::wstring pImageUrl = std::wstring(productImageUrl.begin(), productImageUrl.end());

	std::string countStr = std::to_string(count);
	std::wstring count_wstr = std::wstring(countStr.begin(), countStr.end());

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
	html_out += U("							function deleteFromBasket(){var xhttp = new XMLHttpRequest();xhttp.open('POST','") + wLink + U("',true);xhttp.send()}");
	html_out += U("				</script>");

	html_out += U("				<div class=\"ordersRemove\">");
	html_out += U("					<a href='http://localhost:8090/Basket' onclick=\"deleteFromBasket();\" title=\"Remove\"></a>");
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
std::wstring html_generator::html_buyForm(double price, int count)
{

	std::wstring html_out;
	std::string count_str = std::to_string(count);
	std::wstring count_wstr = std::wstring(count_str.begin(), count_str.end());

	double productPrice = price;
	int full = (int)productPrice;
	double dec = productPrice - full;
	std::string priceFull = std::to_string(full);
	std::string dec_str = std::to_string(dec);
	dec_str = dec_str.substr(1, 3);

	priceFull += dec_str;
	std::wstring pPrice = std::wstring(priceFull.begin(), priceFull.end());

	

	html_out += U("<script>");
	html_out += U("$(\"#contactForm\").validate({rules: {Telephone: {digits : true}}}); ");
	html_out += U("</script>");
	html_out += U(" <form class=\"contact\" id=\"contactForm\" action=\"http://localhost:8090/Basket/PlaceOrder\" method='post'>");
	html_out += U("  <label class=\"contactLables\">Items Ordered :") + count_wstr + U("</label>");
	html_out += U("  <label class=\"contactLables\">Total Price :") + pPrice + U("</label>");
	html_out += U("  <label class=\"contactLables\">Your Telephone</label>");
	html_out += U(" <input  class=\"contactInputs\" id=\"Telephone\"  name=\"Telephone\" type=\"number\" placeholder=\"Enter your Telephone...\" required>");
	html_out += U(" <input class=\"ordersPlace\" type=\"submit\" value=\"Place Order\">");
	html_out += U(" <input  class=\"contactInputs\" name=\"TotalSum\" type=\"text\" style=\"visibility:hidden;\" value='") + pPrice + U("'>");
	return html_out;
}
std::wstring html_generator::html_ContactPage()
{
	std::wstring html_out;
	html_out += U("<script>");
	html_out += U("$(\"#contactForm\").validate();");
	html_out += U("</script>");
	html_out += U("<form class=\"contact\" id=\"contactForm\" action=\"http://localhost:8090/Contact/Submit\" method='post'>");
	html_out += U("<label class=\"contactLables\">Name</label>");
	html_out += U(" <input  class=\"contactInputs\" name=\"Name\"  minlength=\"2\" type=\"text\" placeholder=\"Enter your Name...\" required>");
	html_out += U("<label class=\"contactLables\">Email</label>");
	html_out += U(" <input  class=\"contactInputs\" name=\"Email\" type=\"email\" placeholder=\"Enter your Email...\" required>");
	html_out += U("<label class=\"contactLables\">Message</label>");
	html_out += U("<textarea form=\"contactForm\" wrap=\"physical\" class=\"contactInputs txtBox\" name=\"Content\" type=\"text\" placeholder=\"Enter your Message...\"required ></textarea>");
	html_out += U("<input class=\"submitBTNC\" type=\"submit\" value=\"Send\">");
	html_out += U("</form>");
	return html_out;
}
std::wstring html_generator::html_AdminLoginPage()
{
	std::wstring html_out;
	html_out = U("<form class=\"contact\" id=\"contactForm\" action=\"http://localhost:8090/Admin\" method='post'>");
	html_out += U("<label class=\"contactLables\">Usenrame</label>");
	html_out += U(" <input  class=\"contactInputs\" name=\"username\" type=\"text\" placeholder=\"Enter your Username...\">");
	html_out += U("<label class=\"contactLables\">Password</label>");
	html_out += U(" <input  class=\"contactInputs\" name=\"password\" type=\"text\" placeholder=\"Enter your Email...\">");
	html_out += U("<input class=\"submitBTNC\" type=\"submit\" value=\"Send\">");
	html_out += U("</form>");
	return html_out;
}
std::wstring html_generator::html_searchPage()
{
	
	
}
std::wstring html_generator::html_Alert(std::string body)
{
	std::wstring html_out;
	html_out = U("<div class=\"Alert\"><p>") + std::wstring(body.begin(), body.end()) + U("</p></div>");
	return html_out;
}
std::wstring html_generator::html_aboutFull(Company company)
{
	std::string companyName = company.Company_getName();
	std::wstring cName = std::wstring(companyName.begin(), companyName.end());

	std::string companyAddress = company.Company_getAddress();
	std::wstring cAddress = std::wstring(companyAddress.begin(), companyAddress.end());

	std::string companyTelephone = company.Company_getTelephone();
	std::wstring cTelephone = std::wstring(companyTelephone.begin(), companyTelephone.end());

	std::string companyabout = company.Company_getAbout();
	std::wstring cAbout = std::wstring(companyabout.begin(), companyabout.end());
	std::wstring html_out;
	html_out = U("<div class=\"about\">");
	html_out += U("<p>") + std::wstring(cAbout.begin(), cAbout.end()) + U("</p>");
	html_out += U("</div>");
	return html_out;
}
std::wstring html_generator::html_ordersManagment(const std::vector<std::vector<std::pair<std::string, std::string>>>& table_data, sqlite_db db)
{
	std::wstring html_out;
	std::string link; 
	html_out = U("<!DOCTYPE html>\n");
	html_out += U("  <html>\n");
	html_out += U("    <head>\n");
	html_out += U("        <title>Managment Panel</title>\n");
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
	html_out += U("    <div class=\"table-wrapper\">\n");
	html_out += U("		<h2 class=\"panelMagh2\">Managment Panel</h2>\n");


	html_out += U(" <table class=\"tableIt\">\n");
	if (table_data.size() > 0) {
		html_out += U("        <tr class=\"headerRow\">\n");
		for (auto col : table_data.at(0)) {
			//if (col.first == "id" || col.first == "Id" || col.first == "iD" || col.first == "ID")
			html_out += U("          <th>") + std::wstring(col.first.begin(), col.first.end()) + U("</th>\n");
		}
		html_out += U("<th>Products Ordered</th>\n");

		html_out += U("        </tr>\n");
	}
	for (std::vector<std::pair<std::string, std::string>> row_data : table_data) {
		html_out += U("        <tr>\n");
		for (auto col : row_data) {
			//if (col.first == "id" || col.first == "Id" || col.first == "iD" || col.first == "ID")
			html_out += U("          <td>") + std::wstring(col.second.begin(), col.second.end()) + U("</td>\n");
		}
		std::string row_id = find_id(row_data);
		link.append(row_id);
		
		int myId = atoi(row_id.c_str());
		std::string table_name = "OrderTable";
		std::vector<std::vector<std::pair<std::string, std::string>>> table_data2;
		db.db_getOrders(table_data2, myId);
		html_out += U("          <td>");
		for (std::vector<std::pair<std::string, std::string>> row_data2 : table_data2) {	
			int i = 1;
			for (auto col2 : row_data2) {
				if (i%2 == 1)
				{
					html_out += std::wstring(col2.second.begin(), col2.second.end()) + U("(");
					i++;
				}
				else if (i % 2 == 0)
				{
					html_out += std::wstring(col2.second.begin(), col2.second.end()) + U("x) ");
					i++;
				}
				//if (col.first == "id" || col.first == "Id" || col.first == "iD" || col.first == "ID")
				
			}
			
		}
		html_out += U("</td>\n");

		link = "http://localhost:8090/Admin/Orders/Delete/";
		link.append(row_id);
		std::wstring wRow_id = std::wstring(link.begin(), link.end());
		html_out += U("      <td class=\"lastData2\">");
		html_out += U("<form class=\"deleteFForm\" action='") + std::wstring(service_url.begin(), service_url.end()) + U("/Admin/Orders/")  + U("Delete/") + std::wstring(row_id.begin(), row_id.end()) + U("' method='get'>");
		html_out += U("<input class=\"removeForms\" type='submit' value='Delete'>");
		html_out += U("</form>");
		html_out += U("</td>\n");
		html_out += U("        </tr>\n");
		html_out += U("        </tr>\n");
	}
	html_out += U("      </table>\n");
	html_out += U("    </div>\n");
	html_out += U("    </body>\n");
	html_out += U("  </html>\n");

	return html_out;
}
std::wstring html_generator::html_tableListHtml()
{
	std::wstring html_out;
	html_out = U("<!DOCTYPE html>\n");
	html_out += U("  <html>\n");
	html_out += U("    <head>\n");
	html_out += U("        <title>SQLite DB Explorer</title>\n");
	html_out += U("<style>") + std::wstring(normalize.begin(), normalize.end());
	html_out += U("			</style>");
	html_out += U("			<style>") + std::wstring(reset.begin(), reset.end());
	html_out += U("			</style>");
	html_out += U("<style type = \"text/css\">\n");
	html_out += std::wstring(index.begin(), index.end());
	html_out += U("</style>\n");
	html_out += U("<style>") + std::wstring(stylesheet.begin(), stylesheet.end());
	html_out += U("</style>");
	html_out += U("    </head>\n");
	html_out += U("    <body>\n");
	html_out += U("      <div class=\"listTable\" border=\"1\" cellpadding=\"5\" cellspacing=\"5\">\n");

	html_out += U("        <div class=\"tableTitle\">\n");
	html_out += U("          <th>Managment Panel</th>\n");
	html_out += U("        </div>\n");
	html_out += U("        <div class=\"TableListRows\">\n");
	html_out += U("        <div class=\"tableListRow\">\n");
	html_out += U("            <a class=\"tValues\" href=\"http://localhost:8090/Admin/Products\">Products</a>\n");
	html_out += U("        </div>\n");
	html_out += U("        <div class=\"tableListRow\">\n");
	html_out += U("            <a class=\"tValues\" href=\"http://localhost:8090/Admin/Orders\">Orders</a>\n");
	html_out += U("        </div>\n");
	html_out += U("        <div class=\"tableListRow\">\n");
	html_out += U("            <a class=\"tValues\" href=\"http://localhost:8090/Admin/Company\">Company info</a>\n");
	html_out += U("        </div>\n");
	html_out += U("        <div class=\"tableListRow\">\n");
	html_out += U("            <a class=\"tValues\" href=\"http://localhost:8090/Admin/Messages\">Messages</a>\n");
	html_out += U("        </div>\n");
	html_out += U("        <div class=\"tableListRow\">\n");
	html_out += U("            <a class=\"tValues\" href=\"http://localhost:8090/Admin/Slider\">Slider</a>\n");
	html_out += U("        </div>\n");
	html_out += U("        </div>\n");
	html_out += U("      </div>\n");
	html_out += U("    </body>\n");
	html_out += U("  </html>\n");
	return html_out;
}
std::wstring html_generator::html_homePage(std::wstring bodyPartial, Company company, const std::vector<std::vector<std::pair<std::string, std::string>>>& table_data)
{


	std::string companyName = company.Company_getName();
	std::wstring cName = std::wstring(companyName.begin(), companyName.end());

	std::string companyAddress = company.Company_getAddress();
	std::wstring cAddress = std::wstring(companyAddress.begin(), companyAddress.end());

	std::string companyTelephone = company.Company_getTelephone();
	std::wstring cTelephone = std::wstring(companyTelephone.begin(), companyTelephone.end());

	std::string companyabout = company.Company_getAbout();
	std::string subAbout;
	if (companyabout.length() > 800)
		subAbout = companyabout.substr(0, 800);
	else
		subAbout = companyabout;

	std::wstring cAbout = std::wstring(subAbout.begin(), subAbout.end());

	std::wstring jqueryW = std::wstring(jquery.begin(), jquery.end());

	std::wstring sliderJs = std::wstring(slider.begin(), slider.end());
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
	html_out += U("				<script>");
	html_out += jqueryW;
	html_out += U("				</script>");
	html_out += U("				<script>");
	html_out += sliderJs;
	html_out += U("				</script>");
	html_out += U("				<script>");
	html_out += U("$(function(){$(\"#slides\").slidesjs({effect: {slide: {speed: 1000},fade : {speed: 5000,crossfade : true}}});}); ");
	//html_out += U("$(function(){$(\"#slides\").slidesjs({effect: fade : {speed: 300,crossfade : true}}});}); ");
	html_out += U("				</script>");
	html_out += U("    </head>\n");
	html_out += U("    <body>\n");
	html_out += U("      <div class=\"wrapper\">");
	html_out += U("          <div class=\"header\">");
	html_out += U("              <div class=\"hashtag\">");
	html_out += U("                 <a href=\"https://twitter.com/hashtag/menclothing\">#MENCLOTHING</a>");
	html_out += U("              </div>");
	html_out += U("              <div class=\"logo\">");
	html_out += U("					 <h1><a href=\"http://localhost:8090/\" title='") + cName + U("'>") + cName + U("</a></h1>");
	html_out += U("              </div>");
	html_out += U("              <div class=\"header_operations\">");
	html_out += U("					 <div class=\"header_basket header_ops\"><a href=\"http://localhost:8090/Basket\" title=\"Basket\"></a></div>");
	html_out += U("					 <div class=\"header_search  header_ops\">");
	html_out += U("						 <form class=\"searchForm\" action=\"http://localhost:8090/Search\" method:\"get\">");
	html_out += U("							 <input class=\"searchBox\" type='text' name='productName' placeholder='type product name...'>");
	html_out += U("							 <input class=\"searchBTN\" value='' type='submit'>");
	html_out += U("						 </form>");
	html_out += U("					 </div>");
	html_out += U("              </div>");
	html_out += U("          </div>");
	html_out += U("          <div class=\"navigation\">");
	html_out += U("				<ul class=\"nav-ul\">");
	html_out += U("					 <li><a href=\"http://localhost:8090/Products\" title=\"Shop\">Shop</a></li>");
	html_out += U("					 <li><a href=\"http://localhost:8090/Contact\" title=\"Contact Us\">Contact</a></li>");
	html_out += U("					 <li><a href=\"http://localhost:8090/About\" title=\"About Us\">About</a></li>");
	html_out += U("			    </ul>");
	html_out += U("          </div>");
	html_out += U("          <div class=\"sliderMid\" id=\"slides\">");
	for (std::vector<std::pair<std::string, std::string>> row_data : table_data) {
		int i = 1;
		for (auto col : row_data) {
			if (i % 2 == 0)
			{
				html_out += U("        <img src ='") + std::wstring(col.second.begin(), col.second.end()) + U("'/>\n");
				i++;
			}
			else
				i++;
			
		}
	}
		//html_out += U("				 <img src=\"http://i.imgur.com/E7ShHhE.jpg\">");
		//html_out += U("				 <img src=\"http://i.imgur.com/oYAI5uQ.jpg\">");
		//html_out += U("				 <img src=\"http://i.imgur.com/KlozaiB.jpg\">");
		html_out += U("          </div>");
		html_out += U("          <div class=\"featured\">");
		html_out += U("				<div class=\"titles\"><h2>new arrivals</h2></div>");
		html_out += bodyPartial;
		html_out += U("				<div class=\"futured_slogan\"><p>new is always better :)</p></div>");
		html_out += U("				<div class=\"more-btn\"><a href=\"http://localhost:8090/Products\">more...</a></div>");


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
		html_out += U("						<div class=\"more-btn btn-about\"><a href=\"http://localhost:8090/About\">more...</a></div>");
		html_out += U("			</div>");
		html_out += U("		</div>");
		html_out += U("				<div class=\"footer\">");
		html_out += U("					<ul class=\"footer-ul\">");
		html_out += U("						<li><a href=\"http://localhost:8090/Products\" title=\"Shop\">Shop</a></li>");
		html_out += U("						<li><a href=\"http://localhost:8090/Contact\" title=\"Contact\">Contact</a></li>");
		html_out += U("						<li><a href=\"http://localhost:8090/About\" title=\"About\">About</a></li>");
		html_out += U("				   </ul>");
		html_out += U("				<div class=\"social-media-container\">");
		html_out += U("					<div class=\"social-inner\">");
		html_out += U("						<div class=\"social-media gp\"><a href=\"https://plus.google.com/+TommyHilfiger/videos\" title=\"Google Plus\"></a></div>");
		html_out += U("						<div class=\"social-media tw\"><a href=\"https://twitter.com/tommyhilfiger\" title=\"Twitter\"></a></div>");
		html_out += U("						<div class=\"social-media fb\"><a href=\"https://www.facebook.com/tommyhilfiger\" title=\"Facebook\"></a></div>");
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
	html_out += U(			"<style>") + std::wstring(normalize.begin(), normalize.end());
	html_out += U("			</style>");
	html_out += U("			<style>") + std::wstring(reset.begin(), reset.end());
	html_out += U("			</style>");
	html_out += U(			"<style type = \"text/css\">\n");
	html_out += std::wstring(index.begin(), index.end());
	html_out += U(			"</style>\n");
	html_out += U(			"<style>") + std::wstring(stylesheet.begin(), stylesheet.end());
	html_out += U(			"</style>");
	html_out += U("    </head>\n");
	html_out += U("    <body>\n");
	html_out += U("      <div class=\"listTable\" border=\"1\" cellpadding=\"5\" cellspacing=\"5\">\n");

	html_out += U("        <div class=\"tableTitle\">\n");
	html_out += U("          <th>Managment Panel</th>\n");
	html_out += U("        </div>\n");
	html_out += U("        <div class=\"TableListRows\">\n");
	for (std::string table_name : table_names) {
		html_out += U("        <div class=\"tableListRow\">\n");
		html_out += U("            <a class=\"tValues\" href=\"") + std::wstring(service_url.begin(), service_url.end()) + U("/") + U("Admin/") + std::wstring(table_name.begin(), table_name.end()) + U("\">");
		html_out += std::wstring(table_name.begin(), table_name.end()) + U("</a>\n");
		html_out += U("        </div>\n");
	}
	html_out += U("        </div>\n");
	html_out += U("      </div>\n");
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
	html_out += U("        <title>Managment Panel</title>\n");
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
	html_out += U("    <div class=\"table-wrapper\">\n");
	html_out += U("		<h2 class=\"panelMagh2\">Managment Panel</h2>\n");
	html_out += input_form_html_edit(table_data, table_name);
	html_out += U("		<h2 class=\"addToTable\" >Add:</h2>\n");
	html_out += input_form_html(table_data, table_name);
	html_out += U("    </div>\n");
	html_out += U("    </body>\n");
	html_out += U("  </html>\n");
	return html_out;
}
std::wstring html_generator::input_form_html(const std::vector<std::vector<std::pair<std::string, std::string>>>& table_data, const std::string table_name)
{
	std::wstring html_out;
	html_out = U("<form action='") + std::wstring(service_url.begin(), service_url.end()) + U("/Admin/") + std::wstring(table_name.begin(), table_name.end()) + U("/add") + U("' method='get'>");
	html_out += U("  <table class=\"addDB\" border=\"1\" cellpadding=\"5\" cellspacing=\"5\">\n");
	if (table_data.size() > 0) {
		for (auto col : table_data.at(0)) {
			if (col.first == "id" || col.first == "Id" || col.first == "iD" || col.first == "ID")
				continue;
			html_out += U("    <tr>\n");
			html_out += U("      <td>") + std::wstring(col.first.begin(), col.first.end()) + U(": <input type='text' name='") + std::wstring(col.first.begin(), col.first.end()) + U("'></td>\n");
			html_out += U("    </tr>\n");
		}
		html_out += U("    <tr>\n");
		html_out += U("      <td><input type='submit' value='Add'></td>\n");
		html_out += U("    </tr>\n");
	}
	html_out += U("  </table>\n");
	html_out += U("</form>\n");
	return html_out;

}
std::wstring html_generator::html_companyInfo(const std::vector<std::vector<std::pair<std::string, std::string>>>& table_data, const std::string table_name)
{
	std::wstring html_out;
	html_out = U("<!DOCTYPE html>\n");
	html_out += U("  <html>\n");
	html_out += U("    <head>\n");
	html_out += U("        <title>Managment Panel</title>\n");
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
	html_out += U("    <div class=\"table-wrapper\">\n");
	html_out += U("		<h2 class=\"panelMagh2\">Managment Panel</h2>\n");
	html_out += U("      <table class=\"tableIt\" border=\"1\" cellpadding=\"5\" cellspacing=\"5\">\n");
	if (table_data.size() > 0) {
		html_out += U("        <tr class=\"headerRow\">\n");
		for (auto col : table_data.at(0)) {
			//if (col.first == "id" || col.first == "Id" || col.first == "iD" || col.first == "ID")
			html_out += U("          <th>") + std::wstring(col.first.begin(), col.first.end()) + U("</th>\n");
		}
		html_out += U("          <th></th>\n");
		html_out += U("        </tr>\n");
	}
	for (std::vector<std::pair<std::string, std::string>> row_data : table_data) {
		html_out += U("        <tr class=\"headerRow\">\n");
		for (auto col : row_data) {
			//if (col.first == "id" || col.first == "Id" || col.first == "iD" || col.first == "ID")
			html_out += U("          <td>") + std::wstring(col.second.begin(), col.second.end()) + U("</td>\n");
		}
		std::string row_id = find_id(row_data);

		html_out += U("          <td>");
		html_out += U("<form action='") + std::wstring(service_url.begin(), service_url.end()) + U("/Admin/") + std::wstring(table_name.begin(), table_name.end()) + U("/edit/") + std::wstring(row_id.begin(), row_id.end()) + U("/' method='post'>");
		html_out += U("  <table class=\"tableSub\">\n");
		if (table_data.size() > 0) {
			for (auto col : row_data) {
				if (col.first == "id" || col.first == "Id" || col.first == "iD" || col.first == "ID")
					continue;
				html_out += U("    <tr>\n");
				html_out += U("      <td>") + std::wstring(col.first.begin(), col.first.end()) + U(": <input type='text' name='") + std::wstring(col.first.begin(), col.first.end()) + U("' value='") + std::wstring(col.second.begin(), col.second.end()) + U("'></td>\n");
				html_out += U("    </tr>\n");
			}
			html_out += U("    <tr>\n");
			html_out += U("      <td><input type='submit' value='Save'>");
			html_out += U("</td>\n");

			html_out += U("    </tr>\n");
		}
		html_out += U("  </table>\n");
		html_out += U("</form>\n");
		html_out += U("</td>\n");
		html_out += U("        </tr>\n");
	}
	html_out += U("      </table>\n");
	html_out += U("    </div>\n");
	html_out += U("    </body>\n");
	html_out += U("  </html>\n");
	return html_out;
}
std::wstring html_generator::html_MessagesAdmin(const std::vector<std::vector<std::pair<std::string, std::string>>>& table_data, const std::string table_name)
{
	std::wstring html_out;
	std::string link;
	html_out = U("<!DOCTYPE html>\n");
	html_out += U("  <html>\n");
	html_out += U("    <head>\n");
	html_out += U("        <title>Managment Panel</title>\n");
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
	html_out += U("    <div class=\"table-wrapper\">\n");
	html_out += U("		<h2 class=\"panelMagh2\">Managment Panel</h2>\n");


	html_out += U(" <table class=\"tableIt\">\n");
	if (table_data.size() > 0) {
		html_out += U("        <tr class=\"headerRow\">\n");
		for (auto col : table_data.at(0)) {
			//if (col.first == "id" || col.first == "Id" || col.first == "iD" || col.first == "ID")
			html_out += U("          <th>") + std::wstring(col.first.begin(), col.first.end()) + U("</th>\n");
		}
		html_out += U("<th>Products Ordered</th>\n");

		html_out += U("        </tr>\n");
	}
	for (std::vector<std::pair<std::string, std::string>> row_data : table_data) {
		html_out += U("        <tr>\n");
		for (auto col : row_data) {
			//if (col.first == "id" || col.first == "Id" || col.first == "iD" || col.first == "ID")
			html_out += U("          <td>") + std::wstring(col.second.begin(), col.second.end()) + U("</td>\n");
		}
		std::string row_id = find_id(row_data);
		link.append(row_id);

		int myId = atoi(row_id.c_str());
		std::string table_name = "OrderTable";
		//std::vector<std::vector<std::pair<std::string, std::string>>> table_data2;
		//db.db_getOrders(table_data2, myId);


		link = "http://localhost:8090/Admin/Orders/Delete/";
		link.append(row_id);
		std::wstring wRow_id = std::wstring(link.begin(), link.end());
		html_out += U("      <td class=\"lastData2\">");
		html_out += U("<form class=\"deleteFForm\" action='") + std::wstring(service_url.begin(), service_url.end()) + U("/Admin/Messages/") + U("Delete/") + std::wstring(row_id.begin(), row_id.end()) + U("' method='get'>");
		html_out += U("<input class=\"removeForms\" type='submit' value='Delete'>");
		html_out += U("</form>");
		html_out += U("</td>\n");
		html_out += U("        </tr>\n");
		html_out += U("        </tr>\n");
	}
	html_out += U("      </table>\n");
	html_out += U("    </div>\n");
	html_out += U("    </body>\n");
	html_out += U("  </html>\n");

	return html_out;
}
std::wstring html_generator::input_form_html_edit(const std::vector<std::vector<std::pair<std::string, std::string>>>& table_data, const std::string table_name)
{
	std::wstring html_out;
	html_out = U("      <table class=\"tableIt\" border=\"1\" cellpadding=\"5\" cellspacing=\"5\">\n");
	if (table_data.size() > 0) {
		html_out += U("        <tr class=\"headerRow\">\n");
		for (auto col : table_data.at(0)) {
			//if (col.first == "id" || col.first == "Id" || col.first == "iD" || col.first == "ID")
			html_out += U("          <th>") + std::wstring(col.first.begin(), col.first.end()) + U("</th>\n");
		}
		html_out += U("          <th></th>\n");
		html_out += U("        </tr>\n");
	}
	for (std::vector<std::pair<std::string, std::string>> row_data : table_data) {
		html_out += U("        <tr class=\"headerRow\">\n");
		for (auto col : row_data) {
			//if (col.first == "id" || col.first == "Id" || col.first == "iD" || col.first == "ID")
			html_out += U("          <td>") + std::wstring(col.second.begin(), col.second.end()) + U("</td>\n");
		}
		std::string row_id = find_id(row_data);

		html_out += U("          <td>");
		html_out += U("<form action='") + std::wstring(service_url.begin(), service_url.end()) + U("/Admin/") + std::wstring(table_name.begin(), table_name.end()) + U("/edit/") + std::wstring(row_id.begin(), row_id.end()) + U("/' method='post'>");
		html_out += U("  <table class=\"tableSub\">\n");
		if (table_data.size() > 0) {
			for (auto col : row_data) {
				if (col.first == "id" || col.first == "Id" || col.first == "iD" || col.first == "ID")
					continue;
				html_out += U("    <tr>\n");
				html_out += U("      <td>") + std::wstring(col.first.begin(), col.first.end()) + U(": <input type='text' name='") + std::wstring(col.first.begin(), col.first.end()) + U("' value='") + std::wstring(col.second.begin(), col.second.end()) + U("'></td>\n");
				html_out += U("    </tr>\n");
			}
			html_out += U("    <tr>\n");
			html_out += U("      <td><input type='submit' value='Save'>");
			html_out += U("</td>\n");
		
			html_out += U("    </tr>\n");
		}
		html_out += U("  </table>\n");
		html_out += U("</form>\n");
		html_out += U("</td>\n");
		html_out += U("      <td class=\"lastData\">");
		html_out += U("<form class=\"deleteFForm\" action='") + std::wstring(service_url.begin(), service_url.end()) + U("/Admin/") + std::wstring(table_name.begin(), table_name.end()) + U("/Delete/") + std::wstring(row_id.begin(), row_id.end()) + U("' method='get'>");
		html_out += U("<input class=\"removeForms\" type='submit' value='Delete'>");
		html_out += U("</form>");
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