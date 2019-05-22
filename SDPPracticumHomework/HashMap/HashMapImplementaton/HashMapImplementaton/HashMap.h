#pragma once
#include "tests.h"
#include <iostream>
#include <vector>
#include <string>

int nextPrime(int a)
{
	int i, j, count, num;
	for (i = a + 1; 1; i++)
	{
		count = 0;
		for (j = 2; j < i; j++)
		{
			if (i%j == 0) // found a devisor
			{
				count++;
				break;  
			}
		}
		if (count == 0)
		{
			return i;
		
		}
	}
}

template <class K, class V>
struct Values {
	K key;
	V value;
};


template <class K, class V>
class HashMap
{
public:
	HashMap(int capacity) {
		hashTable.resize(capacity);
		for (int i = 0; i < capacity; ++i) {
			hashTable.reserve(0);
		}
	
	};

	void add(K key, V value);
	void remove(K key);
	V find(K key);
	int capacity();
	int collisions();
	int size() const;

private:
	std::vector<std::vector<Values<K,V>>> hashTable;
	void resize();
	int hashFunc(int key);
	int hashFunc(std::string key);
};

template <class K, class V>
int HashMap<K,V>::hashFunc(int key) {
	return key % hashTable.size();
}

template <class K, class V>
int HashMap<K,V>::hashFunc(std::string key) {
	int hash = 0;
	for (int i = 0; i<key.length(); ++i) {
		hash += key[i] + pow(17, i);
	}
	return hash % hashTable.size();
}

template <class K, class V>
void HashMap<K,V>::resize() {
	//We find the next prime so that we keep the hash table as much colision free as we can
	int oldSize = hashTable.size();
	int newSize = nextPrime(hashTable.size());
	std::vector<std::vector<Values<K,V>>> newTable(newSize);

	for (int i = 0; i < oldSize;++i) {
		if (hashTable[i].size() > 0) {
			for (int j = 0; j < hashTable[i].size(); ++j) {
				newTable[i][j] = hashTable[i][j];
			}
		}
	}
	this->hashTable = newTable;

}


template <class K ,class V>
void HashMap<K,V>::add(K key, V value) {
	if (this->size() > ((100 / hashTable.size()) * 70)) {
		this->resize();
	}
	Values<K,V> pushValue;
	pushValue.key = key;
	pushValue.value = value;
	if (find(key)!=(V())) {
		this->remove(key);
	}
	hashTable[this->hashFunc(key)].push_back(pushValue);
}

template <class K,class V>
void HashMap<K,V>::remove(K key) {
	int index = this->hashFunc(key);
	int position = 0;
	for (int i = 0; i < hashTable[index].size(); ++i) {
		if (hashTable[index][i].key==key) {
			hashTable[index].erase(hashTable[index].begin()+position);
		}
		++position;
	}
}

template <class K, class V>
V HashMap<K,V>::find(K key) {
	int index = this->hashFunc(key);
	for (int i = 0; i < hashTable[index].size(); ++i) {
		if (hashTable[index][i].key==key) {
			return hashTable[index][i].value;
		}
	}
	return V();
}

template <class K, class V>
int HashMap<K,V>::capacity() {
	return hashTable.size();
}

template <class K, class V>
int HashMap<K,V>::collisions() {
	int collisions = 0;
	for (int i = 0; i < hashTable.size(); ++i) {
		if (hashTable[i].size() > 1) {
			++collisions;
		}
	}
	return collisions;
}
template <class K, class V>
int HashMap<K,V>::size() const{
	int numOfElements=0;
	for (int i = 0; i < hashTable.size(); ++i) {
		numOfElements += hashTable[i].size();
	}
	return numOfElements;
}


//Tests
void hashMap_basic_test() {
	UnitTests suit("Basic tests");

	HashMap<int, std::string> testHashMap(10);

    std::string value = "some";
	testHashMap.add(50, value);
	testHashMap.add(10, value);
	
	suit.AssertEq(2, testHashMap.size());
	
	std::string test = "some";
	suit.AssertEq(test , testHashMap.find(10));
	
	suit.AssertEq(test , testHashMap.find(50));
	
	test = "any";
	value = "any";
	testHashMap.add(50, value);
	testHashMap.add(20, value); 
	
	suit.AssertEq(test, testHashMap.find(50));
	
	suit.AssertEq(3, testHashMap.size());
	
	testHashMap.remove(20);
	suit.AssertEq(2, testHashMap.size());
	
	suit.AssertEq(10, testHashMap.capacity());

	
	HashMap<std::string, std::string> testHashMap2(10);
	testHashMap2.add("Hashin", "shin");
	testHashMap2.add("Thresh", "Support");
	testHashMap2.add("Marto", "God");
	
	suit.AssertEq(10, testHashMap2.capacity());
	
	std::string test2 = "God";
	suit.AssertEq(test2, testHashMap2.find("Marto"));
	
	test2 = "Support";
	suit.AssertEq(test2, testHashMap2.find("Thresh"));
	
	test2 = "shin";
	suit.AssertEq(test2, testHashMap2.find("Hashin"));
	
	suit.AssertEq(3, testHashMap2.size());


	suit.PrintTestsResult();
}


