#include "stdafx.h"
#include "Basket.h"


Basket::Basket()
{
}

void Basket::Basket_addItem(Product product)
{
	bool exists = false;
	int p =items.size();
	for (int i = items.size() - 1; i >=0 ; i--)
	{
		if (items.at(i).Product_getId() == product.Product_getId())
		{
			counts.at(i) = counts.at(i) + 1;
			exists = true;
		}
	}
	if(exists == false)
	{ 
		items.push_back(product);
		counts.push_back(1);
	}
		
	
}
void Basket::Basket_remove(Product product)
{
	int id = product.Product_getId();
	if (items.size() == counts.size())
	{
		for (int i = 0; i < items.size(); i++)
		{
			if (items.at(i).Product_getId() == id)
			{
				items.erase(items.begin() + i);
				counts.erase(counts.begin() + i);
			}
		}
	}
	else
		puts("basket and count size differs");
	
}
std::vector<Product> Basket::Basket_getItems()
{
	return items;
}

std::vector<int> Basket::Basket_getCounts()
{
	return counts;
}




Basket::~Basket()
{
}
