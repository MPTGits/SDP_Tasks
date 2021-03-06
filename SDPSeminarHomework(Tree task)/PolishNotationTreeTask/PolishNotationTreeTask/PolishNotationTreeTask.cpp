// PolishNotationTreeTask.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "BinTree.h"
#include "TNode.h"
#include "ExprToBinTree.h"
#include <stack>

int main()
{
	
	std::stack<char> test;
	/*
	test.push('2');
	test.push('3');
	test.push('5');
	test.push('4');
	test.push('*');
	test.push('+');
	test.push('+');
	*/
	char expr[20] = "-*+ab3*4c";
	//Pushesh the expresion into a stack
	pushExpresionToStack(expr, test);
	BinTree<char> testTree;
	testTree=prefixToBinTree(test);
	std::cout << "Tree in reverse polish notation:";
	printTreeInReversePolishNotation(testTree);
	std::cout << std::endl;
	std::cout<<"Expresion value is:"<<calculateExpresionTreeValue(testTree)<<std::endl;

    return 0;
}

