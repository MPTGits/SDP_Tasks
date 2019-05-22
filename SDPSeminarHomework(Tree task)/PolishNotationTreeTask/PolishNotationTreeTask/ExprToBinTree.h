#pragma once

#include "TNode.h"
#include "BinTree.h"
#include <stack>

bool isDigitOrChar(char x) {
	return (x <= '9'&&x >= '0')||(x>='a'&&x<='z');
}

void pushExpresionToStack(const char* expr, std::stack<char>& resultStack) {
	//We clear the stack in case somone gave us a non empty stack
	while (!resultStack.empty()) {
		resultStack.pop();
	}
	//We add elements to the stack keeping the original straight polish notation 
	for (int i = strlen(expr)-1; i >= 0; --i) {
		resultStack.push(expr[i]);
	}
}
//Main function that makes a binary tree out of our stack expresion
BinTree<char> prefixToBinTree(std::stack<char>& stackExpr) {
	//We take the top value in the stack 
	char currentElement=stackExpr.top();
	stackExpr.pop();
	//If it is a digit we make a node directly and return it
	if (isDigitOrChar(currentElement)) {
		BinTree<char> elementNode;
		elementNode.createWithData(currentElement, BinTree<char>(), BinTree<char>());
		return elementNode;
	}
		//If its not a digit we serch for the next two digits and make a tree with the operation  we took from the stack being the root
		BinTree<char> left = prefixToBinTree(stackExpr);
		BinTree<char> right = prefixToBinTree(stackExpr);
		BinTree<char> exprBinTree;
		exprBinTree.createWithData(currentElement, left, right);
		return exprBinTree;
	

}

void printTreeInReversePolishNotation(BinTree<char> tree) {
	if (tree.isEmpty())
		return;
	
	printTreeInReversePolishNotation(tree.getLeftTree());
	printTreeInReversePolishNotation(tree.getRightTree());
	std::cout << tree.getRootData() << ' ';
}

int calculateExpresionTreeValue(BinTree<char> tree){
	char value1,value2,operation;
	int finalValue;
	if (tree.getRootData() >= '0'&&tree.getRootData() <= '9') {
		return tree.getRootData() - '0';
	}
	else if (tree.getRootData() >= 'a'&&tree.getRootData() <= 'z') {
		int num;
		std::cout << "Input number:";
		std::cin >> num;
		std::cout << std::endl;
		return num;
	}
	operation=tree.getRootData();
	switch (operation) {
	case '+':
		finalValue = calculateExpresionTreeValue(tree.getLeftTree()) + calculateExpresionTreeValue(tree.getRightTree());
		break;
	case '-':
		finalValue = calculateExpresionTreeValue(tree.getLeftTree()) - calculateExpresionTreeValue(tree.getRightTree());
		break;
	case '*':
		finalValue= calculateExpresionTreeValue(tree.getLeftTree()) * calculateExpresionTreeValue(tree.getRightTree());
	}
	return finalValue;
	}

