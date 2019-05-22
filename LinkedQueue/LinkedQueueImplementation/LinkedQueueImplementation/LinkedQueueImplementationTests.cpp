// LinkedQueueImplementation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "LinkedQueueImpl.h"

int main()
{
	LinkedQueueImpl<int> myQueue;
	myQueue.push(5);
	myQueue.push(5);
	myQueue.push(3);
	myQueue.push(2);
	myQueue.showQueue();
	myQueue.pop();
	myQueue.pop();
	myQueue.showQueue();
	std::cout<<myQueue.isEmpty();
	std::cout<<myQueue.frontOfQueue();
	myQueue.pop();
	myQueue.pop();
	myQueue.pop();
	myQueue.pop();
    return 0;
}

