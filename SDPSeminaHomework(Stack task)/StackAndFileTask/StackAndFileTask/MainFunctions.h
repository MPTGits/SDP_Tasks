#pragma once
#include <iostream>
#include <stack>
#include <stdlib.h> 


std::stack<int> stackForNumbers;
std::stack <char> stackForExpr;

bool isDigit(char x) {
	return ((x - '0') >= 0 && (x - '0') <= 9);
}

int f(int x) {
	return ((x*x) % 100);
}
//Fibonachi function
int memo[100000] = { 0 };

int fib(int n) {
	if (n == 0)
		return 0;
	if (memo[n] != 0)
		return memo[n];

	if (n == 1 || n == 2)
		return 1;
	else
		return memo[n] = fib(n - 1) + fib(n - 2);
}
//


int l(int x) {
	return (fib(x) % 100);
}


int m(int x, int y) {
	if (x > y) return x;
	return y;
}

//Needs to be called so values are pushed into the needed stack 
void inputValuesInStacks(const char* arr) {
	int counter = 0;
		while (arr[counter] != '\0') {
			if (arr[counter] == 'f' || arr[counter] == 'l' || arr[counter] == 'm' || arr[counter] == ',') {
				stackForExpr.push(arr[counter]);
			}
			else if (isDigit(arr[counter])) {
				char tmpStoreNum[10];
				int tmpStoreNumCounter=0;
				while (isDigit(arr[counter])) {
					tmpStoreNum[tmpStoreNumCounter] = arr[counter];
					tmpStoreNumCounter++;
					counter++;
				}
				--counter;
				tmpStoreNum[tmpStoreNumCounter] = '\0';
				stackForNumbers.push(atoi(tmpStoreNum));
			}
			++counter;
		}

}

//Evaluating the final result
int exprEvaluation() {
	std::stack<int> tmpRemoved;
	while (!stackForExpr.empty()) {
		char topExpr = stackForExpr.top();
		int topNumber;
		if (topExpr == 'l') {
			topNumber = stackForNumbers.top();
			stackForNumbers.pop();
			stackForNumbers.push(l(topNumber));
		}
		else if (topExpr == 'f') {
			topNumber = stackForNumbers.top();
			stackForNumbers.pop();
			stackForNumbers.push(f(topNumber));
		}
		else if (topExpr == ',') {
			tmpRemoved.push(stackForNumbers.top());
			stackForNumbers.pop();
		}
		else if (topExpr == 'm') {
			topNumber = stackForNumbers.top();
			stackForNumbers.pop();
			stackForNumbers.push(m(topNumber,tmpRemoved.top()));
			tmpRemoved.pop();
		}
		std::cout << stackForNumbers.top()<<" ";
		stackForExpr.pop();
		std::cout << std::endl;
	}
	int finalResult = stackForNumbers.top();
	stackForNumbers.pop();
	return finalResult;
}
