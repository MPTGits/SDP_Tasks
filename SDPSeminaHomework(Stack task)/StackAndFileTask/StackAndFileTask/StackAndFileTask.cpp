// StackAndFileTask.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "MainFunctions.h"

bool unitTestForStack() {
	const char tmp[100] = "m(l(l(443)),m(l(512),l(64)))";;
	const char resultValue[100] = "l,lm,llm";
	const int numValues[3] = { 64 , 512, 443 };
	char result[100];
	int counter1 = 0,counter2=0;
	bool isStackOfNum = true;
	inputValuesInStacks(tmp);

	while (!stackForExpr.empty()) {
		result[counter1] = stackForExpr.top();
		stackForExpr.pop();
		counter1++;
	}
	result[counter1] = '\0';
	while (!stackForNumbers.empty()) {
		if (numValues[counter2] != stackForNumbers.top()) {
		isStackOfNum = false;
		break;
		}
		stackForNumbers.pop();
		counter2++;
	}
	return ((!(strcmp(result,resultValue))) && isStackOfNum);

}

template <typename T>
void showstack(std::stack<T> s)
{
	while (!s.empty())
	{
		std::cout << s.top() << " ";
		s.pop();
	}
	std::cout << '\n';
}


int main()
{
	//std::cout<<unitTestForStack();
	const char currPath[40] = "Expresions.txt";
	std::ifstream fileWithExpresions;
	fileWithExpresions.open(currPath, std::ios::out);
	char currentExpresion[200];
	fileWithExpresions.getline(currentExpresion, 200);
	int numOfExpr = atoi(currentExpresion);
	int counter = 0;
	while (counter<numOfExpr) {
		fileWithExpresions.getline(currentExpresion,200);
		inputValuesInStacks(currentExpresion);
		std::cout <<"Expr. №"<<counter+1<<" value is " <<exprEvaluation() << std::endl;
		++counter;
	}
    return 0;
}

