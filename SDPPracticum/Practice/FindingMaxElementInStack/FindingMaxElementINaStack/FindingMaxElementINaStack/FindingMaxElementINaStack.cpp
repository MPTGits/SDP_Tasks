// FindingMaxElementINaStack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "StackImplByTheGod.h"
//Extracting the maximum element of a stack without changing it(and then sort the stack)
int extractMaxNumOfStack(const LinkedStackImpl<int> &myStack) {
	LinkedStackImpl<int> tmpStack = myStack;
	int value=0;
	tmpStack.pop(value);
	int maxNum = value;
	while (!(tmpStack.isEmpty())) {
		tmpStack.pop(value);
		std::cout << value;
		if (value > maxNum) {
			maxNum = value;
		}
	}
	return maxNum;

}



int main()
{
	LinkedStackImpl<int> myStack;
	for (int i = 0; i < 10; ++i) {
		myStack.push(rand() % 20 + 1);
	}
	//myStack.showStack();
	std::cout<<extractMaxNumOfStack(myStack)<<std::endl;

    return 0;
}

