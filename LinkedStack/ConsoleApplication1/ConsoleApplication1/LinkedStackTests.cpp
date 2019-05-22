// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "LinkedStackImpl.h"


int main()
{
	LinkedStackImpl<int> test;
	test.push(5);
	test.push(5);
	test.push(3);
	test.push(5);
	test.push(2);
	test.showStack();
	int a = 0;
	test.pop(a);
	test.pop(a);
	std::cout << std::endl;
	test.showStack();
	a=test.top();
	std::cout << a << std::endl;
	test.pop(a);
	test.pop(a); test.pop(a);
	test.pop(a);
    return 0;
}

