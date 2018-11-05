#pragma once
#ifndef PriorityQueue_H
#define PriorityQueue_H
#include "Queue.h"
#include <cassert>
#include <iostream>
using namespace std;

/**
最大优先级队列查找操作用来搜索优先级最大的元素，删除也是删除该元素，插入则是简单地将一个新的元素加入到队列
最小优先级队列同理
*/
const int DefaultPQSize = 50;

template <typename T>class PriorityQueue:public Queue<T> {
public:
	PriorityQueue(int sz = DefaultPQSize);
	~PriorityQueue() {
		delete[] pqelements;
	}
	bool EnQueue(const T &x);
	bool DeQueue(T &x);
	bool getFront(T &x);
	void makeEmpty() {
		count = 0;
	}
	bool isEmpty()const {
		return count == 0;
	}
	bool isFull()const {
		return count == maxSize;
	}
	int getSize()const {
		return count;
	}
	friend ostream& operator<<(ostream & os, PriorityQueue<T> &Q) {
		for (int i = 0; i < Q.count; i++)
			os << "#" << i << ": " << Q.pqelements[i] << endl;
		os << "Queue Size: " << Q.getSize() << endl;
		return os;
	}
protected:
	T *pqelements;
	int count;
	int maxSize;
	void adjust();	// 将队尾元素调整到适当位置
};

template <typename T>PriorityQueue<T>::PriorityQueue(int sz) {
	maxSize = sz;
	count = 0;
	pqelements = new T[maxSize];
	assert(pqelements);//是否成功分配内存
}

template <typename T>bool PriorityQueue<T>::EnQueue(const T &x) {
	if (count == maxSize)	return false;
	pqelements[count] = x;
	count++;
	adjust();
	return true;
}

// 将队尾元素调整到适当位置
template <typename T>void PriorityQueue<T>::adjust() {//原来排好队，新进来一个
	T item = pqelements[count - 1];
	int j;
	for (j = count - 2; j >= 0; j--) {
		if (pqelements[j] <= item) {// 重载：T型判大小
			break;
		}
		else {
			pqelements[j + 1] = pqelements[j];
		}
	}
	pqelements[j + 1] = item;
}

template <typename T>bool PriorityQueue<T>::DeQueue(T& x) {//采用线性表方式，不采用队方式
	if (count == 0)	return false;
	x = pqelements[0];
	for (int i = 1; i < count; i++)
		pqelements[i - 1] = pqelements[i];
	count--;
	return true;
}

template <typename T>bool PriorityQueue<T>::getFront(T &x) {
	if (count == 0)	return false;
	x = pqelements[0];
	return true;
}
#endif