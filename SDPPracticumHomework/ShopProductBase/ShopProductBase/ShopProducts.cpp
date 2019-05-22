#include "stdafx.h"
#include "ShopProducts.h"
#include <iostream>
#include <cstring>
#include <cassert>

int ShopProducts::idGeneratorHleper = 0;

int ShopProducts::incIdGeneratorHelper()
{
	ShopProducts::idGeneratorHleper++;
	return ShopProducts::idGeneratorHleper;
}

ShopProducts::ShopProducts()
{
	strcpy_s(this->nameOfProduct ,strlen("undefined")+1,"undefined");
	this->price = -1;
	this->idOfProduct = -1;
}

ShopProducts::ShopProducts(const char* nameOfProduct,double price)
{
	assert(price > 0);
	strcpy_s(this->nameOfProduct, strlen(nameOfProduct) + 1, nameOfProduct);
	this->price = price;
	this->isDeleted = false;
	this->idOfProduct = this->idGeneratorHleper;
	this->idGeneratorHleper = this->incIdGeneratorHelper();
	
}

void ShopProducts::discountProduct(int discountPercent)
{
	if (discountPercent < 1 || discountPercent>10) {
		std::cerr << "Invalid discount percent!";
		return;
	}
	this->set_price((this->price / 100)*discountPercent);
}

bool ShopProducts::operator==(const ShopProducts & obj)
{
	return (this->get_IdOfProduct() == obj.get_IdOfProduct());
}

std::ostream & operator<<(std::ostream & os, const ShopProducts & obj)
{
	os << "Name of product:" << obj.get_nameOfProduct() << '\n' << "Price:" << obj.get_price() << '\n' << "Id number:" << obj.get_IdOfProduct();
	return os;
}

std::istream & operator>>(std::istream & is, ShopProducts & obj)
{
	std::cout << "Input product name and price:"<<std::endl;
	obj.set_softDelete(false);
	obj.set_idGenerator();
	is >> obj.nameOfProduct >> obj.price;
	return is;
}
