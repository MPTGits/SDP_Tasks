#pragma once

#include <iostream>
#include "Store.h"
#include "Product.h"
#include <string>

//Struct that contains the name and  the index in the original db of a product
struct IndexingStruct {
	char name[200];
	int index;

};

//template <typename T>
class IndexedStore :public Store<Product> {
	
private:
		std::fstream indexingFile;
		std::string IndexFilePath;
		int sizeOfIndexingFlie;

protected:
	bool copyMainDb(std::fstream& tmpDb, std::string tmpDbPath) {
		Product tmpItem("undef", 0);
		tmpDb.write((char*)&m_metadata, sizeof(m_metadata));
		bool success = true;
		for (int i = 0; i < m_metadata.m_size&&success; ++i) {
			getAtIdx(i, tmpItem); 
			success = !!tmpDb.write((char*)& tmpItem, sizeof(tmpItem));
		}
		db_ios.seekg(0, std::ios::beg);
		if (!success) {
			std::cout << "Prblem copying db! ";
			remove(tmpDbPath.c_str());
			return false;
		}
		return true;
	}

public:
	//The constructor just calls the constructor of the base class
	IndexedStore(std::string indexingFileName,std::string dbFileName):Store(dbFileName)  {
		this->IndexFilePath = indexingFileName;
		this->sizeOfIndexingFlie = 0;
	};
	
	int getSizeOfFile() const {
		return sizeOfIndexingFlie;
	}
 	
	bool initIndex() {
		//In case the file is open.
		indexingFile.close();
		//If file dosent exist we creat it
		indexingFile.open(IndexFilePath, std::ios::in | std::ios::out | std::ios::binary|std::ios::app);
		// Opening the existing indexing file for names
		return true;
		}

	bool initIndexAndDb() {
		return (this->init() && this->initIndex());
	}


	bool indexingExistingDatabase() {
		//First we check if the index file has any information already in it,
		//if it has we prevent loading it again with a diffrent database
		indexingFile.seekg(0, std::ios::end);
		int lengthOfFile =(int)indexingFile.tellg();
		if (lengthOfFile > 0) {
			std::cout << "Indexing file aready has information in it!" << std::endl;
			//We set the current size of the indexing file and add 1 
			//since operation '/' will round the double to to the lowest int it gets
			this->sizeOfIndexingFlie = lengthOfFile / sizeof(Product)+1;
			return false;
		}
		//We set and copy all the elements from the main db in a temporary

		std::fstream tmpDbSave;
		std::string tmpDbSavePath= "tmpDb.db";
		tmpDbSave.open(tmpDbSavePath, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
		copyMainDb(tmpDbSave, tmpDbSavePath);

		//We creat a tmp object that will be used to take objects from the main db and a current biggest object
		//so that we can store the elements of the db in a descending order based on lexicographical order 
		int originalSize = m_metadata.m_size;
		Product tmp("undefined", 0);
		Product currentBiggestProduct("", 0);
		int biggestElementIndex;
		//Structure that will save a name and a index of the objects that are equivalent to the name and id in orginal db 
		IndexingStruct indexedObj;
		

		while (originalSize>=1) {
			//We skip the metadata every cycle	
			db_ios.seekg(0, std::ios::beg);
			db_ios.read((char*)&m_metadata, sizeof(m_metadata));

			for (int i = 0; i < m_metadata.m_size; ++i) {
				//We go throught the elements and sort them in lexicographical order one by one
				db_ios.read((char*)&tmp, sizeof(Product));
				if (tmp.isDelete() == true) continue;
				if ((strcmp(tmp.getName(),currentBiggestProduct.getName()))>0) {
					currentBiggestProduct = tmp;
					biggestElementIndex = i;
				}
			}
			//Writing longest name to index file
			strcpy_s(indexedObj.name, strlen(currentBiggestProduct.getName()) + 1, currentBiggestProduct.getName());
			indexedObj.index = biggestElementIndex;
			indexingFile.write((char*)&indexedObj, sizeof(IndexingStruct));
			//We soft remove the current element that has the lexicographical biggest name
			this->softRemove(currentBiggestProduct.getId());
			//We reset the current biggest object with a generic object.
			Product refresher("", 0);
			currentBiggestProduct = refresher;
			--originalSize;
			db_ios.clear();
		}
		//We set the size of our indexingFile;
		this->sizeOfIndexingFlie = m_metadata.m_size;

		//We copy our originarl database from our temporary saved file so that our elements don't appear to be 
		//soft removed and are in the state they were before we indexed them in the new file
		db_ios.close();
		tmpDbSave.close();
		remove(this->m_dbFilename.c_str());
		rename(tmpDbSavePath.c_str(), this->m_dbFilename.c_str());
		db_ios.open(m_dbFilename.c_str(), std::ios::in | std::ios::out | std::ios::binary);
		return true;
	}

	void print() {
		std::cout << "Printing function..." << "number of products:" <<sizeOfIndexingFlie << std::endl;
		indexingFile.seekg(0, std::ios::beg);
		IndexingStruct tmp;
		for (int i = 0; i < sizeOfIndexingFlie; ++i) {
			indexingFile.read((char*)&tmp, sizeof(IndexingStruct));
			std::cout <<"Name|index:"<< tmp.name << "|" << tmp.index << std::endl;
		}
		indexingFile.seekg(0, std::ios::beg);
	}

	//Binary search using the order of the names in the file
	Product indexedSearchByName(const char* name) {
		int start = 0;
		int end = sizeOfIndexingFlie;
		IndexingStruct tmp;
		Product productObj("Undefined",0);
		while (start < end) {
			int mid = (start + end) / 2;
			indexingFile.seekg(mid * sizeof(IndexingStruct), std::ios::beg);
			indexingFile.read((char*)&tmp, sizeof(IndexingStruct));
			if (strcmp(name, tmp.name) > 0) {
				end = mid;
			}
			else if (strcmp(name, tmp.name) < 0) {
				start = mid;
			}
			else {
				std::cout << "Object found...returning object!" << std::endl;
				db_ios.seekg(getItemFilePtr(tmp.index), std::ios::beg);
				db_ios.read((char*)&productObj, sizeof(Product));
				return productObj;
			}
		}
		std::cout << "Object not in database or is not indexed,returning a generic object!" << std::endl;
		return productObj;
	}


	void addingAndIndexingProduct(Product addedProduct) {
		//Adding product to database first
		this->add(addedProduct);
		//In case the name is not bigger than any of the others it goes at the back
		int indexToBeInsertedAt = sizeOfIndexingFlie;
		IndexingStruct tmp;
		indexingFile.seekg(0, std::ios::beg);
		//We search for the index where the new object name and index struct will be inserted 
		for (int i = 0; i <= sizeOfIndexingFlie; ++i) {
			indexingFile.read((char*)&tmp, sizeof(IndexingStruct));
			if (strcmp(addedProduct.getName(), tmp.name) > 0) {
				indexToBeInsertedAt = i;
				break;
			}
		}
		
		++this->sizeOfIndexingFlie;
		std::fstream tmpIndexFile;
		std::string path = "tmpIndexFile.db";
		tmpIndexFile.open(path, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
		bool success = true;
		indexingFile.seekg(0, std::ios::beg);

		//We creat a new temp file and we copy all the indexes and insert the new indexed object at the correct position 
		for (int i = 0; i <= sizeOfIndexingFlie&&success; ++i) {
			//In case we got ot the needed position we add the object and continue copying the indexed objects
			//that are  already in the file
			if (i == indexToBeInsertedAt) {
				strcpy_s(tmp.name ,strlen(addedProduct.getName())+1, addedProduct.getName());
				tmp.index = this->findById(addedProduct.getId(),addedProduct);
				success = !!tmpIndexFile.write((char*)& tmp, sizeof(tmp));
				continue;
			}
			indexingFile.read((char*)&tmp, sizeof(IndexingStruct));
			success = !!tmpIndexFile.write((char*)& tmp, sizeof(tmp));
		}
		tmpIndexFile.seekg(0, std::ios::beg);
		
		if (!success) {
			std::cout << "Prblem copying db! ";
			remove(path.c_str());
			return;
		}
		//We rename the tmp file and make it our new original file
		indexingFile.close();
		tmpIndexFile.close();
		remove(IndexFilePath.c_str());
		rename(path.c_str(),IndexFilePath.c_str());
		indexingFile.open(IndexFilePath, std::ios::in | std::ios::out | std::ios::binary);
	}
		

void removeIndexingProduct(Product removedProduct) {
	//If I hard remove the item its index is taken by another object so If i recompile the program twice I may have 2 objects with 
	//the same indexes
	this->softRemove(removedProduct.getId());
	//In case the name is not bigger t
	int indexToBeRemovedAt=-1;
	IndexingStruct tmp;
	indexingFile.seekg(0, std::ios::beg);
	//We search for the product inedx 
	for (int i = 0; i <= sizeOfIndexingFlie; ++i) {
		indexingFile.read((char*)&tmp, sizeof(IndexingStruct));
		if (strcmp(removedProduct.getName(), tmp.name) == 0) {
			indexToBeRemovedAt = i;
			break;
		}
	}

	--this->sizeOfIndexingFlie;
	std::fstream tmpIndexFile;
	std::string path = "tmpIndexFile.db";
	tmpIndexFile.open(path, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
	bool success = true;
	indexingFile.seekg(0, std::ios::beg);

	//We creat a new temp file and we copy all the indexes and skip the indexed object at the correct position 
	for (int i = 0; i <=sizeOfIndexingFlie&&success; ++i) {
		//In case we got ot the needed position we skip the object and continue copying the indexed objects
		//that are  already in the file
		indexingFile.read((char*)&tmp, sizeof(IndexingStruct));
		if (i == indexToBeRemovedAt) {
			continue;
		}
		success = !!tmpIndexFile.write((char*)& tmp, sizeof(tmp));
	}
	tmpIndexFile.seekg(0, std::ios::beg);

	if (!success) {
		std::cout << "Prblem copying db! ";
		remove(path.c_str());
		return;
	}
	//We rename the tmp file and make it our new original file
	indexingFile.close();
	tmpIndexFile.close();
	remove(IndexFilePath.c_str());
	rename(path.c_str(), IndexFilePath.c_str());
	indexingFile.open(IndexFilePath, std::ios::in | std::ios::out | std::ios::binary);
}

};