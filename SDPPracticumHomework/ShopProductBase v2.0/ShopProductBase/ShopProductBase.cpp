// ShopProductBase.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include "ShopProducts.h"
#include "ShopDatabase.h"


//Adding multiply products at a time
void productAdder(ShopDatabase& mainShop) {
	ShopProducts product;
	int numberOfProducts;
	std::cout << "Input the number of objects you want to input in the file:";
	std::cin >> numberOfProducts;
	for (int i = 0; i < numberOfProducts; ++i) {
		std::cin >> product;
		mainShop.add(product);
	}
}
//Searching for multiply products by name at a time
const int maxNumOfProducts=10;
void multiplyProductFinder(char namesOfProducts[][20], ShopProducts foundProducts[maxNumOfProducts], ShopDatabase& mainShop) {
	int i = 0;
	int size = sizeof(namesOfProducts);
	while (i<maxNumOfProducts) {
		foundProducts[i] = mainShop.find(namesOfProducts[i]);
		++i;
	}
}


//TODO:Exceptions when the file fails to read or write?
int main()
{
	ShopProducts prod[maxNumOfProducts];
	ShopProducts product1("domat", 2), product2("krastavica", 4.2),product3("patladjan",2.4),product4("Dinq",6);
	
	ShopDatabase shop("ShopInfo.db");
	
	//Multiply adder function
	//productAdder(shop);

	//Testing finding products by multiplu names
	/*
	char names[10][20] = { "domat","patladjan" };
	multiplyProductFinder(names, prod, shop);
	for (int i = 0; i < 10; ++i) {
		if (prod[i].get_IdOfProduct() != -1) {
			std::cout << prod[i] << std::endl;
		}
	}
	*/

	//Printing shop info
	//shop.shopInfo();
	

	//Това надолу НЕ Е тестване на ръка,което съм правил!!
	///////////////////////////////////////////////////////////////////////////////
	/*
	shop.add(product1);
	shop.add(product2);
	shop.add(product3);
	shop.add(product4);
	char names[10][20] = { "domat","patladjan" };
	multiplyProductFinder(names, prod, shop);
	for (int i = 0; i < 10; ++i) {
		if (prod[i].get_IdOfProduct() != -1) {
			std::cout << prod[i] << std::endl;
		}
	}
	//shop.shopInfo();
	//ShopProducts patladjahn=shop.find("ivan");
	//std::cout << patladjahn;
	//std::cout << std::endl;
	//shop.shopInfo();
	/////////////////////////////////////////////////////////////////////////////////
	*/
    return 0;
}

