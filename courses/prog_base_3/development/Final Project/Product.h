#pragma once
#include "stdafx.h"
#include <string>
#include <iostream>

class Product
{
private:
	int id;
	std::string name;
	double price;
	std::string description;
	std::string imageUrl;
public:
	Product(void)
	{
		id = -1;
	}
	Product(int pId, std::string pName, double pPrice, std::string pDescription, std::string pImageUrl)
	{
		id = pId;
		name = pName;
		price = pPrice;
		description = pDescription;
		imageUrl = pImageUrl;
	}
	int Product_getId();
	std::string Product_getName();
	double Product_getPrice();
	std::string Product_getDescription();
	std::string Product_getImageUrl();
};

