#pragma once

template <typename T>
struct TNode {
	T data;
	TNode<T> *left, *right;

	TNode(T _data, TNode<T> *_left = nullptr, TNode<T> *_right = nullptr) : data(_data), left(_left), right(_right) {};
};