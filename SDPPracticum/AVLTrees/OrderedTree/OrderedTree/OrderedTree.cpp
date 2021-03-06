// OrderedTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

struct Node {
	int data;
	Node* left;
	Node* right;
	
	Node(int _data, Node* _left = nullptr, Node* _right = nullptr) {
		data = _data;
		left = _left;
		right = _right;
		}
	};


void findLeafs(Node* tree) {
	if (!tree) {
		return;
	}
	if (tree->left == nullptr&&tree->right == nullptr) {
		std::cout <<"|Leaf " <<tree->data<<"|";
		std::cout << std::endl;
	}
	findLeafs(tree->left);
	findLeafs(tree->right);
	
}

bool isElement(Node* tree, int element) {
	if (!tree) {
		return false;
	}
	if (tree->data == element) {
		return true;
	}
	isElement(tree->left, element);
	isElement(tree->right, element);
}

void traverse(Node* tree) {
	if (!tree) {
		return;
	}
	traverse(tree->right);
	std::cout << tree->data << std::endl;
	traverse(tree->left);
}

//template <typename T=int>
int main()
{
	Node* leaf_3_1 = new Node(5);
	Node* leaf_3_2 = new Node(8);
	Node* leaf_3_3 = new Node(11);
	Node* leaf_3_4 = new Node(13);
	Node* leaf_2_1 = new Node(7, leaf_3_1, leaf_3_2);
	Node* leaf_2_2 = new Node(12, leaf_3_3, leaf_3_4);
	Node* root=new Node(10, leaf_2_1, leaf_2_2);

	//traverse(root);
	//std::cout << std::endl;
	std::cout<<isElement(root, 8);
	//findLeafs(root);
    return 0;
}
