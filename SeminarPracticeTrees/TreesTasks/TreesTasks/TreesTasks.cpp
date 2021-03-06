// TreesTasks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>


//Tree struct
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
//
//Да се напише функция, която пресмята сумата на положителните елементи на дърво от цели числа.
void sumOfPossitiveElements(Node* tree,int& sum) {
	if (!tree) {
		return;
	}
	if (tree->data > 0) {
		sum += tree->data;
	}
	sumOfPossitiveElements(tree->left,sum);
	sumOfPossitiveElements(tree->right,sum);

}
//Да се напише функция, която извежда листата на дърво, т.е. корените на поддърветата на дървото, които нямат наследници.
void allLeafs(Node* tree) {
	if (tree->left == nullptr&&tree->right == nullptr) {
		std::cout << tree->data << std::endl;
		return;
	}
	allLeafs(tree->left);
	allLeafs(tree->right);
}
//Да се напише функция, която извежда елементите на n-то ниво на дърво.

void nthLevelOfTree(Node* tree,int lvl) {
	if (lvl == 0) {
		std::cout << tree->data << std::endl;
		return;
	}
	if (!tree) {
		return;
	}
	nthLevelOfTree(tree->left, lvl - 1);
	nthLevelOfTree(tree->right, lvl - 1);
}



int main()
{
 //The test tree
	Node* leaf_3_1 = new Node(5);
	Node* leaf_3_2 = new Node(8);
	Node* leaf_3_3 = new Node(11);
	Node* leaf_3_4 = new Node(-13);
	Node* leaf_2_1 = new Node(7, leaf_3_1, leaf_3_2);
	Node* leaf_2_2 = new Node(12, leaf_3_3, leaf_3_4);
	Node* root = new Node(10, leaf_2_1, leaf_2_2);
	
	//int sum = 0;
	//sumOfPossitiveElements(root, sum);
	//std::cout << sum << std::endl;

	//allLeafs(root);

	nthLevelOfTree(root, -1);

    return 0;
}

