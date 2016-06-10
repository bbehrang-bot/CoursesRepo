#pragma once
#include "stdafx.h"
#include <string>
#include <iostream>

class Product
{
private:
	int id;
	std::string name;
	float price;
	std::string description;
	std::string imageUrl;
	int inStock;
public:
	Product(void)
	{
		id = -1;
	}
	Product(int pId, std::string pName, float pPrice, std::string pDescription, std::string pImageUrl, int pInStock)
	{
		id = pId;
		name = pName;
		price = pPrice;
		description = pDescription;
		imageUrl = pImageUrl;
		inStock = pInStock;
	}
	int Product_getId();
	std::string Product_getName();
	float Product_getPrice();
	std::string Product_getDescription();
	std::string Product_getImageUrl();
	int Product_getInStock();
	void print();
	
};

