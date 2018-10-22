#pragma once
/**链式栈的定义 直接使用linkedlist中的linkednode 的定义*/

#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H
#include <iostream>
#include <cassert>
#include "LinkedList.h"
#include "Stack.h"
using namespace std;


template <typename T>class LinkedStack :public Stack<T>{
private:
	LinkNode<T> *top;
public:
	LinkedStack() :top(NULL) {}
	~LinkedStack() {
		makeEmpty();
	}
	void Push(const T &x);
	bool Pop(T &x);
	bool getTop(T &x);
	int getSize()const;
	bool IsEmpty()const {
		return top == NULL;
	}
	bool IsFull()const {
		return false;
	}
	void makeEmpty();
	friend ostream& operator << (ostream &os, LinkedStack<T> &s) {
		os << "Stack Size: " << s.getSize() << endl;
		LinkNode<T> *p = s.top;
		int i = 0;
		while (p) {
			os << ++i << ": " << p->data << endl;
			p = p->link;
		}
		return os;
	}
};

template <typename T>void LinkedStack<T>::makeEmpty() {
	LinkNode<T> *p;
	while (top) {
		p = top;
		top = top->link;
		delete p;
	}
}

template <typename T>void LinkedStack<T>::Push(const T &x) {
	top = new LinkNode<T>(x, top);
	assert(top);
}

template <typename T>bool LinkedStack<T>::Pop(T &x) {
	if (IsEmpty()) {
		return false;
	}
	LinkNode<T> *p = top;
	top = top->link;
	x = p->data;
	delete p;
	return true;
}

template <typename T>bool LinkedStack<T>::getTop(T &x) {
	if (IsEmpty())	return false;
	x = top->data;
	return true;
}

template <typename T>int LinkedStack<T>::getSize()const {
	LinkNode<T> *p = top;
	int k = 0;
	while (p) {
		p = p->link;
		k++;
	}
	return k;
}
#endif