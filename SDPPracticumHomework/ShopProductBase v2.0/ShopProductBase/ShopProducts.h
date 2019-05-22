#pragma once
#include <iostream>
#include <cstring>
class ShopProducts
{
private:
	static int idGeneratorHleper;
	char nameOfProduct[200];
	double price;
	bool isDeleted;
	int idOfProduct;
	int incIdGeneratorHelper();

public:
	ShopProducts();
	ShopProducts(const char* name, double price);
	void discountProduct(int discountPercent);
	bool operator==(const ShopProducts& obj);


	const char* get_nameOfProduct() const {
		return nameOfProduct;
	}
	
	double get_price() const {
		return price;
	}
	int get_IdOfProduct() const {
		return idOfProduct;
	}
	bool get_isSoftDeleted() const {
		return isDeleted;
	}
	void set_softDelete(bool stateOfProduct) {
		this->isDeleted = stateOfProduct;
	}
	void set_Name(char* name) {
		strcpy_s(this->nameOfProduct, strlen(name) + 1, name);
	}
	void set_price(double price) {
		this->price = price;
	}
	void set_idGenerator() {
		this->idOfProduct=incIdGeneratorHelper();
	}


	friend std::ostream& operator<<(std::ostream &os, const ShopProducts& obj);
	friend std::istream& operator>>(std::istream &is, ShopProducts& obj);
};

