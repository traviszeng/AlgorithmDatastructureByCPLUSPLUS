#pragma once
#ifndef QUEUE_H
#define QUEUE_H

/*
���еĳ�����
**/
const int maxSize = 50;
template<class T>
class Queue {
	//public Queue() {}
	//public ~Queue() {}

	virtual bool EnQueue(const T& x) = 0;
	virtual bool DeQueue(T& x) = 0;
	virtual bool getFront(T& x) = 0;
	virtual bool isEmpty()const = 0;
	virtual bool isFull()const = 0;
	virtual int getSize()const = 0;
};



#endif // !QUEUE_H
