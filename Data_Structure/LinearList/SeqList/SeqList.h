#pragma once
/**
˳���Ķ�̬�洢��ʾ

typedef struct{
	T *a;
	int maxSize,n;
}SeqList;
*/
#ifndef SEQLIST_H
#define SEQLIST_H
#include<cassert>
#include<iostream>
using namespace std;
#include "LinearList.h"


const int DEFAULTSIZE = 100;

template<class T>
class SeqList  :public LinearList<T>{
protected:
	T *data;
	int maxSize;//�������ɱ��������
	int last;//��ǰ�Ѵ��������λ�ã���0��ʼ��
	void reSize(int newSize);//�ı�data����ռ��С

public:
	SeqList(int sz = DEFAULTSIZE);
	SeqList(SeqList<T> & L);
	~SeqList() { delete[] data; }

	int Size()const { return maxSize; }
	int Length()const { return last + 1; }
	int Search(T &x) const;
	int Locate(int i) const;
	bool getData(int i, T&x) const {//��
		if (i>0 && i <= last + 1) {
			x = data[i - 1];
			return true;
		}
		else return false;
	}
	void setData(int i, T &x) {
		if (i>0 && i <= last + 1) {
			data[i - 1] = x;
		}
	}
	bool Insert(int i, T &x);
	bool Remove(int i, T &x);
	bool IsEmpty() const{
		return (last == -1);
	}
	bool IsFull() const{
		return (last == maxSize - 1);
	}
	void Sort();
	void input();
	void output();
	SeqList<T> operator = (const SeqList<T>& L);

	friend istream& operator >> (istream &in, SeqList<T> &R) {
		R.last = -1;//�����
		while (!in.eof()) {
			R.last++;
			if (R.last == R.maxSize) R.reSize(2 * R.maxSize);
			assert(in >> R.data[R.last]);
		}
		return in;
	}
	friend ostream& operator << (ostream &out, SeqList<T> &R) {
		for (int i = 0; i <= R.last; i++) {
			cout << "#" << i + 1 << ":\t" << R.data[i] << endl;
		}
		return out;
	}

};


template<class T>
SeqList<T>::SeqList(int sz) {
	if (sz > 0) {
		maxSize = sz;
		last = -1;
		data = new T[maxSize];
	}
	if (data == NULL) {
		cerr << "Memory allocating error!" << endl;
		exit(1);
	}
}

template <typename T>
SeqList<T>::SeqList(SeqList<T> &L) {
	maxSize = L.Size();
	last = L.Length() - 1;
	data = new T[maxSize];
	if (data == NULL) {
		cerr << "Memory allocating error!" << endl;
		exit(1);
	}
	for (int i = 1; i <= last + 1; i++)
	{
		L.getData(i, value);
		data[i - 1] = value;
	}
}


template<typename T>
void SeqList<T>::reSize(int newSize) {
	if (newSize <= 0) {
		cerr << "Invalid array index!" << endl;
		return;
	}
	if (newSize != maxSize) {
		T *newarray = new T[newSize];
		if (newarray == NULL) {
			cerr << "Memory allocating error!" << endl;
			exit(1);
		}
		int n = last;//��
		T *srcptr = data;
		T *destptr = newarray;
		while (n--)	*destptr++ = *srcptr++;
		delete[]data;
		data = newarray;
		maxSize = newSize;
	}
}

template<typename T>
int SeqList<T>::Search(T &x)const {
	for (int i = 0; i <= last; i++) {
		if (data[i] == x)	
			return i + 1;
	}
	return 0;
}


template<typename T>
int SeqList<T>::Locate(int i)const {
	if (i >= 1 && i <= last + 1)	return i;
	else	return 0;
}


template<typename T>
bool SeqList<T>::Insert(int i, T &x) {
	if (last == maxSize - 1)	return false;
	if (i < 0 || i > last + 1) return false;
	for (int j = last; j >= i; j--)	data[j + 1] = data[j];
	data[i] = x;
	last++;
	return true;
}

template<typename T>
bool SeqList<T>::Remove(int i, T &x) {
	if (last == -1)	return false;
	if (i < 1 || i > last + 1) return false;
	x = data[i - 1];
	for (int j = i; j <= last; j++)	data[j - 1] = data[j];
	last--;
	return true;
}

template<typename T>
void SeqList<T>::Sort() {
	for (int i = 1; i <= last; i++) {
		for (int j = last; j >= i; j--) {
			if (data[j - 1] > data[j]) {
				T tmp = data[j - 1];
				data[j - 1] = data[j];
				data[j] = tmp;
			}
		}
	}
}


template<typename T>void SeqList<T>::input() {
	cout << "Input the size of the list which will be created:";
	while (1) {
		assert(cin >> last);
		last--;
		if (last < 0) {
			cout << "Input error, the size must be positive!\n";
			cout << "Input the size again:";
		}
		else if (last > maxSize - 1) {//��һ�Ŀ�������
			cout << "Input error, the size must be less than maxSize!\n";
			cout << "Input the size again:";
		}
		else	break;
	}
	cout << "\nInput the data for each element to create the list:" << endl;
	for (int i = 0; i <= last; i++) {
		cout << "#" << i + 1 << ":";
		assert(cin >> data[i]);
	}
}

template<typename T>
void SeqList<T>::output() {
	cout << "\nThe size of the list is:" << last + 1 << endl;
	for (int i = 0; i <= last; i++)	cout << "#" << i + 1 << ":\t" << data[i] << endl;
}


template<typename T>
SeqList<T> SeqList<T>::operator = (const SeqList<T> &L) {//��
	maxSize = L.Size();
	last = L.Length() - 1;
	delete[]data;//�����
	data = new T[maxSize];
	if (data == NULL) {
		cerr << "Memory allocating error!" << endl;
		exit(1);
	}
	for (int i = 1; i <= last + 1; i++) data[i - 1] = L.getData(i);
}

#endif // !SEQLIST_H