#include "stdafx.h"
#include "ShopDatabase.h"
#include <iostream>
#include <cstring>

int ShopDatabase::sizeOfFile()
{
	this->fileStoringProducts.seekg(0, std::ios::end);
	int size =(int) this->fileStoringProducts.tellg();
	this->fileStoringProducts.seekg(0, std::ios::beg);
	return size;
}


ShopDatabase::ShopDatabase(const char* file)
{
	this->fileStoringProducts.open(file, std::ios::in | std::ios::out | std::ios::binary);
	strcpy_s(this->fileDirecory, strlen(file) + 1, file);
}

ShopDatabase::~ShopDatabase()
{
	this->fileStoringProducts.close();
}


bool ShopDatabase::fileOpenChecker()
{
	if (!this->fileStoringProducts) {
		std::cerr << "File opening problem!";
		return false;
	}
	return true;
}

void ShopDatabase::add(ShopProducts &product)
{
	//With this checker we are sure that no soft deleted obj. will be added back
	if (fileOpenChecker()) {
		if (product.get_isSoftDeleted()) {
			std::cerr << "This product was soft deleted from the data base or is invalid!" << std::endl;
			return;
		}
		this->fileStoringProducts.seekp(0, std::ios::end);
		this->fileStoringProducts.write((char*)&product, sizeof(ShopProducts));
	}
}

void ShopDatabase::soft_remove(ShopProducts &searchedProduct)
{
	//TODO:Binary search for soft remove in the file?Или няма да работи понеже първо трябва да се сортират 
	//обектите спрямо id-то във възходящ ред и така само се увеличава сложността?
	if (fileOpenChecker()) {
		ShopProducts tmp;
		int size = sizeOfFile();
		while (this->fileStoringProducts.tellg() < size) {
			this->fileStoringProducts.read((char*)&tmp, sizeof(ShopProducts));
			if (tmp == searchedProduct) {
				tmp.set_softDelete(true);
				this->fileStoringProducts.seekp(this->fileStoringProducts.tellg(), std::ios::beg);
				this->fileStoringProducts.write((char*)&tmp, sizeof(ShopProducts));
				this->fileStoringProducts.seekp(0, std::ios::end);
				break;
			}
		}
	}
}
//Copying all products in to a new file without the deleted one and then renaming it
void ShopDatabase::hard_remove(ShopProducts &removedProduct)
{
	if (fileOpenChecker()) {
		std::ofstream tmpFile;
		tmpFile.open("tmp.db", std::ios::out | std::ios::binary | std::ios::trunc);
		int size = sizeOfFile();
		ShopProducts tmp;
		while (this->fileStoringProducts.tellg() < size) {
			this->fileStoringProducts.read((char*)&tmp, sizeof(ShopProducts));
			if (!(tmp == removedProduct)) {
				tmpFile.write((char*)&tmp, sizeof(ShopProducts));
			}
		}
		tmpFile.close();
		this->fileStoringProducts.close();
		remove(this->fileDirecory);
		rename("tmp.db", this->fileDirecory);
		this->fileStoringProducts.open(this->fileDirecory, std::ios::out | std::ios::in | std::ios::binary);
	}
}

ShopProducts ShopDatabase::find(const char *nameOfProdcut)
{
	ShopProducts tmp;
	int size = sizeOfFile();
	while (this->fileStoringProducts.tellg()<size) {
		this->fileStoringProducts.read((char*)&tmp, sizeof(ShopProducts));
		if (strcmp(tmp.get_nameOfProduct(),nameOfProdcut)==0) {
			return tmp;
		}
	}
	return ShopProducts();
}
	
void ShopDatabase::shopInfo()
{
	if (fileOpenChecker()) {
		ShopProducts tmp;
		//Counter which will help us with dispalying 10 products at a time 
		int counterDisplayProducts = 1;
		int size = sizeOfFile();
		std::cout << size / sizeof(ShopProducts) << std::endl;
		while (this->fileStoringProducts.tellg() < size) {
			this->fileStoringProducts.read((char*)&tmp, sizeof(ShopProducts));
			if (!(tmp.get_isSoftDeleted())) {
				std::cout << tmp << std::endl;
				std::cout << std::endl;
			}
			//With this we will load only 10 products at a time and not the whole file;
			if ((counterDisplayProducts % 10) == 0) {
				std::cout << std::endl;
				std::cout << "10 products loaded do you want to load more?(y/n)" << std::endl;
				char userRespond;
				std::cin >> userRespond;
				if (userRespond != 'y') {
					std::cout << "Output of shop products is stoped!" << std::endl;
					return;
				}
			}
			++counterDisplayProducts;
		}
		std::cout << "All products have been printed out!" << std::endl;
	}
}
