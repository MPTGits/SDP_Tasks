// IndexedShopDatabase.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Product.h"
#include "Store.h"
#include "IndexedStore.h"
#include <chrono>

int main()
{
	
	IndexedStore store("indexingFile.db", "dbFile.db");
	store.initIndexAndDb();

	Product domat("Domat", 2);
	Product portokal("Portokal", 2);
	Product sol("Sol", 1);
	Product nektarinta("Nektarina", 2);
	Product vafla("Vafla", 0.50);

	store.add(domat);
	store.add(portokal);
	store.add(sol);
	store.add(nektarinta);
	store.add(vafla);

	store.indexingExistingDatabase();

	Product tmp = store.indexedSearchByName("Portokal");
	std::cout << tmp.getName() << " " << tmp.getId() << std::endl;

	Product morkov("Morkov", 0.2);
	Product zele("Zele", 3);

	store.addingAndIndexingProduct(morkov);
	store.addingAndIndexingProduct(zele);
	store.removeIndexingProduct(sol);
	store.print();
	/*
	std::cout << std::endl;
	Product obj=store.indexedSearchByName("Sol");
	/*
	//Mesuring my time in micro and nano seconds
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	store.indexedSearchByName("Sol");
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << std::endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << std::endl;
	//
	*/
	//std::cout << obj.getName() << " " << obj.getPrice()<<std::endl;
    return 0;
}

