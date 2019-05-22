#include "stdafx.h"
#include "UnionFinder.h"
#include <iostream>

UnionFinder::UnionFinder(int size)
{
	//Seting all nodes to be connected to themself only at the begining 
	this->nodes = new int[size];
	this->sizes = new int[size];
	this->len = size;
	for (int i = 0; i < size; ++i) {
		nodes[i] = i;
		sizes[i] = 1;
	}

}

UnionFinder::UnionFinder(const UnionFinder & obj)
{
	this->nodes = new int[obj.len];
	this->sizes = new int[obj.len];
	this->len = obj.len;
	
	for (int i = 0; i < len; ++i) {
		nodes[i] = obj.nodes[i];
		sizes[i] = obj.sizes[i];
	}

}

UnionFinder& UnionFinder::operator=(const UnionFinder & obj)
{
	if (this != &obj) {
		delete[] nodes;
		delete[] sizes;
		this->nodes = new int[obj.len];
		this->sizes = new int[obj.len];
		this->len = obj.len;

		for (int i = 0; i < len; ++i) {
			nodes[i] = obj.nodes[i];
			sizes[i] = obj.sizes[i];
		}
	}
	return *this;
}


UnionFinder::~UnionFinder()
{
	delete[] nodes;
	delete[] sizes;
}

int UnionFinder::getRoot(int element)
{
	//Returning the root for every node we entered
	if (element<0 || element>len) {
		std::cerr << "Sorry the entered node is invalid!" << std::endl;
	}
	while (element != nodes[element]) {
		element = nodes[element];
	}
	return element;
}

void UnionFinder::connect(int a, int b)
{
	//Finding the root of the two selected nodes and connecting the one with lesser elements to the one with more( O(logn))
	int aRoot = getRoot(a);
	int bRoot = getRoot(b);
	if (sizes[aRoot] <= sizes[bRoot]) {
		nodes[aRoot] = bRoot;
		sizes[bRoot] += sizes[aRoot];
		return;
	}
	nodes[bRoot] = aRoot;
	sizes[aRoot] += sizes[bRoot];
}

bool UnionFinder::checkConnection(int a, int b)
{
	return getRoot(a)==getRoot(b);
}
//Printing all of the nodes,the connection of each node and the size of the connection
void UnionFinder::printNodesAndSizes(std::ostream & os) const
{
	for (int i = 0; i < len; ++i) {
		os << i<<":"<<nodes[i] << " size:" << sizes[i] << " , ";
	}
	os << '\n';
}

std::ostream & operator<<(std::ostream & os, const UnionFinder & obj)
{
	obj.printNodesAndSizes(os);
	return os;
}

std::istream & operator>>(std::istream & is, UnionFinder & obj)
{
	is>> obj.len;
	return is;
}
