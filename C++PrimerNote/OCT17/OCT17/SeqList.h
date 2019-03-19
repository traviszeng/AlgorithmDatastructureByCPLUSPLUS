#pragma once
/**
顺序表的动态存储表示

typedef struct{
	T *a;
	int maxSize,n;
}SeqList;
*/

#include "LinearList.h"

const int DEFAULTSIZE = 100;

template<class T>
class SeqList :public LinearList<T> {
protected:
	T *data;
	int maxSize;//最大可容纳表项的项数
	int last;//当前已存表项的最后位置（从0开始）
	void reSize(int newSize);//改变data数组空间大小

public:
	SeqList(int sz = DEFAULTSIZE);
	SeqList(SeqList<T> & L);
	~SeqList() { delete[] data };

	int Size()const { return maxSize; }
	int Length()const { return last + 1; }
	int Search(T &x) const;
	int Locate(int i) const;
	bool getData(int i, T&x) const {//改
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
	bool IsEmpty() {
		return (last == -1);
	}
	bool IsFull() {
		return (last == maxSize - 1);
	}
	void Sort();
	void input();
	void output();
	SeqList<T> operator = (SeqList<T> &L);

	friend istream& operator >> (istream &in, SeqList<T> &R) {
		R.last = -1;//先清空
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

