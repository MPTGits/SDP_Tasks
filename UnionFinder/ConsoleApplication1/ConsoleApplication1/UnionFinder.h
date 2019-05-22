#pragma once
#include  <iostream>
class UnionFinder
{
private:
	int * nodes;
	int * sizes;
	int len;

public:
	UnionFinder(int size=5);
	UnionFinder(const UnionFinder &obj);
	UnionFinder& operator=(const UnionFinder &obj);
	~UnionFinder();
	int getRoot(int element);
	void connect(int a,int b);
	bool checkConnection(int a, int b);
	void printNodesAndSizes(std::ostream& os) const;
	friend std::ostream& operator<<(std::ostream & os, const UnionFinder &obj);
	//Предефинирайте оператора за въвеждане >> за класа UnionFind, така че потребителят да въведе необходимата за обекта информация.
	friend std::istream& operator>>(std::istream& is, UnionFinder &obj);
};

