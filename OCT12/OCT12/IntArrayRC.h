#pragma once 
#ifndef IntArrayRC_H
#define IntArrayRC_H
#include "IntArray.h"
#include<cassert>
/**��һ�����з�Χ���� IntArray ��*/
class IntArrayRC :public IntArray {

public :
	IntArrayRC(int sz = DefaultArraySize);
	IntArrayRC(int *array, int size);
	IntArrayRC(const IntArrayRC& rhc);
	virtual int& operator[](int);

private:
	void check_range(int);

};

#endif // !IntArrayRC_H


inline int& IntArrayRC::operator[](int index) {
	check_range(index);
	return ia[index];
};
inline void IntArrayRC::check_range(int index) {
	assert(index >= 0 && index < _size);
};

/**�������๹�캯��������*/
inline IntArrayRC::IntArrayRC(int sz):IntArray(sz) {
	
};

inline IntArrayRC::IntArrayRC(int* iar, int sz) : IntArray(iar, sz) {
};//�����������ӷֺŻ�����ͷֹͣ����Ҫλ��ȫ�ַ�Χ��δ���� IntelliSense PCH �ļ�����������
