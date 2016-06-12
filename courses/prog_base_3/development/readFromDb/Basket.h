#pragma once
#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
#include "Product.h"
class Basket
{
private :
	std::vector<Product> items;
	std::vector<int> counts;
public:
	Basket();
	void Basket_addItem(Product product);
	std::vector<Product> Basket_getItems();
	std::vector<int> Basket_getCounts();
	void Basket_remove(Product product);
	void Basket_removeAll();
	~Basket();
};

