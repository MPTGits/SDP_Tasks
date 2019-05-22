#pragma once
#include "ShopProducts.h"
#include <iostream>
#include  <fstream>

class ShopDatabase
{
private:
	std::fstream fileStoringProducts;
	char fileDirecory[100];
	static int numProductsinDB;
	//Function that gives us the file length and sets the get pointer at the beg of the file
	int sizeOfFile();
	bool fileOpenChecker();
	void binarySearch(int element,int start,int end);

public:
	ShopDatabase(const char*);
	//In the destructor we will close the file
	~ShopDatabase();

	
	void add(ShopProducts&);
	void soft_remove(ShopProducts&);
	void hard_remove(ShopProducts&);
	ShopProducts find(const char*);
	void shopInfo();

	int get_numOfProducts() const {
		return numProductsinDB;
	}

};

