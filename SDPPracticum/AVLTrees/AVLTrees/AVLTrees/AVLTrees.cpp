// AVLTrees.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

struct Node {
	int data;
	//int balance;
	Node* left;
	Node* right;
	
	Node(int _data, Node* _left = nullptr, Node* _right = nullptr) {
		data = _data;
		left = _left;
		right = _right;
	}
};

//Adding elements to a AVL tree

void addToAVLtree(Node* &tree,int element) {
	if (!tree) {
		tree = new Node(element);
		return;
	}
	if (element < tree->data) {
		addToAVLtree(tree->left, element);
	}
	else {
		addToAVLtree(tree->right, element);
	}
}

void rightRotation(Node* &tree) {
	Node* tmp = tree;
	tree = tree->left;
	tmp->left = tree->right;
	tree->right = tmp;
}

void leftRotation(Node* &tree) {
	Node* tmp = tree;
	tree = tree->right;
	tmp->right = tree->left;
	tree->left = tmp;
}

int main()
{

    return 0;
}

