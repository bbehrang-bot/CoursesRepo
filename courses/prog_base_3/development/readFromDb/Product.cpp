#include "stdafx.h"
#include "Product.h"
int Product::Product_getId()
{
	return id;
}
std::string Product::Product_getName()
{
	return name;
}
float Product::Product_getPrice()
{
	return price;
}
std::string Product::Product_getDescription()
{
	return description;
}
std::string Product::Product_getImageUrl()
{
	return imageUrl;
}
int Product::Product_getInStock()
{
	return inStock;
}
void Product::print()
{
	std::cout << id << name << price << description << imageUrl << inStock;
}
