#pragma once
#include <iostream>


template <typename T>
class LinkedStackImpl
{
private:
	struct Node {
		T data;
		Node* next;
	};
	Node * mainStack;
	int size;
	void copy(const LinkedStackImpl& obj);
	void erase();
	bool isEmpty();

public:
	LinkedStackImpl();
	LinkedStackImpl(const LinkedStackImpl& obj);
	LinkedStackImpl& operator=(const LinkedStackImpl& obj);
	~LinkedStackImpl();

	void push(T);
	T pop(T);
	T top();
	void showStack();

};

template<typename T>
void LinkedStackImpl<T>::copy(const LinkedStackImpl & obj)
{
	mainStack->next = obj.mainStack->next;
	mainStack->data = obj.mainStacl->data;
	size = obj.size;
}

template<typename T>
void LinkedStackImpl<T>::erase()
{
	Node* nextStack;
	while (mainStack) {
		nextStack = mainStack->next;
		delete mainStack;
		mainStack = nextStack;
	}
	delete nextStack;
}

template<typename T>
bool LinkedStackImpl<T>::isEmpty()
{
	return size == -1;
}

template<typename T>
LinkedStackImpl<T>::LinkedStackImpl()
{
	this->mainStack = nullptr;
	this->size = -1;
}

template<typename T>
LinkedStackImpl<T>::LinkedStackImpl(const LinkedStackImpl &obj)
{
	copy(obj);
}

template<typename T>
LinkedStackImpl<T>& LinkedStackImpl<T>::operator=(const LinkedStackImpl &obj)
{
	if (this != &obj) {
		erase();
		copy(obj);
	}
	return *this;
}

template<typename T>
LinkedStackImpl<T>::~LinkedStackImpl()
{
	erase();
}

template<typename T>
void LinkedStackImpl<T>::push(T element)
{
	Node* tmp = new Node;
	tmp->data = element;
	tmp->next = nullptr;
	if (mainStack != nullptr) {
		tmp->next = mainStack;
	}
	mainStack = tmp;
	std::cout << "Element " << element << " added to the stack!" << std::endl;
	++size;

}

template<typename T>
T LinkedStackImpl<T>::top()
{
	return mainStack->data;
}

template<typename T>
void LinkedStackImpl<T>::showStack()
{
	Node* ptr = mainStack;
	while (ptr != nullptr) {
		std::cout << ptr->data << std::endl;
		ptr = ptr->next;
	}
	delete[] ptr;
}

template<typename T>
T LinkedStackImpl<T>::pop(T value)
{
	if (isEmpty()) {
		std::cerr << "Cannot pop from an empty stack!" << std::endl;
	}
	else {
		Node* tmp = mainStack;
		mainStack = mainStack->next;
		value = tmp->data;
		delete[] tmp;
		--size;
		return value;

	}
}