#pragma once
#include <iostream>


template <typename T>
class LinkedQueueImpl
{
private:
	struct Node {
		T data;
		Node* next;
	};
	Node* front;
	Node* end;
	int size;
	void copy(const LinkedQueueImpl& obj);
	void erase();
public:
	LinkedQueueImpl();
	LinkedQueueImpl(const LinkedQueueImpl& obj);
	LinkedQueueImpl& operator=(const LinkedQueueImpl& obj);
	~LinkedQueueImpl();
	void push(T element);
	void pop();
	bool isEmpty();
	T frontOfQueue();
	void showQueue();
};

#include "LinkedQueueImpl.h"


template<typename T>
void LinkedQueueImpl<T>::copy(const LinkedQueueImpl & obj)
{
	this->front = obj.front;
	this->end = obj.end;
	this->size = obj.size;
}

template<typename T>
void LinkedQueueImpl<T>::erase()
{
	Node* tmp=front;
	while (tmp) {
		tmp = front->next;
		delete front;
		front = tmp;
	}
}

template<typename T>
LinkedQueueImpl<T>::LinkedQueueImpl() :front(nullptr), end(nullptr), size(0)
{
}

template<typename T>
LinkedQueueImpl<T>::LinkedQueueImpl(const LinkedQueueImpl & obj)
{
	copy(obj);
}

template<typename T>
LinkedQueueImpl<T> & LinkedQueueImpl<T>::operator=(const LinkedQueueImpl & obj)
{
	if (this != &obj) {
		erase();
		copy(obj);
	}
	return *this;
}

template<typename T>
LinkedQueueImpl<T>::~LinkedQueueImpl()
{
	erase();
}

template<typename T>
void LinkedQueueImpl<T>::push(T element)
{
	Node* tmp = new Node;
	tmp->data = element;
	tmp->next = nullptr;
	if (front == nullptr && end == nullptr) {
		front = tmp;
		end = tmp;
		return;
	}
	end->next = tmp;
	end = tmp;
	++size;
}

template<typename T>
void LinkedQueueImpl<T>::pop()
{
	Node* tmp = front;
	if (front == nullptr) {
		std::cerr << "Can not pop from an empty stack!" << std::endl;
		return ;
	}
	
	else if (front == end) {
		front = end = nullptr;
	}
	else {
		front = front->next;
	}
	delete tmp;
	--size;

}

template<typename T>
bool LinkedQueueImpl<T>::isEmpty()
{
	return size == 0;
}

template<typename T>
T LinkedQueueImpl<T>::frontOfQueue()
{
	return front->data;
}

template<typename T>
void LinkedQueueImpl<T>::showQueue()
{
	Node* tmp = front;
	while (tmp!=nullptr) {
		std::cout << tmp->data << " " << std::endl;
		tmp = tmp->next;
	}
	delete tmp;
}
