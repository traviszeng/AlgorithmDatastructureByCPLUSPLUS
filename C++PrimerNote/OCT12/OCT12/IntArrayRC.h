#pragma once 
#ifndef IntArrayRC_H
#define IntArrayRC_H
#include "IntArray.h"
#include<cassert>
/**是一个带有范围检查的 IntArray 类*/
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

/**传给基类构造函数来构造*/
inline IntArrayRC::IntArrayRC(int sz):IntArray(sz) {
	
};

inline IntArrayRC::IntArrayRC(int* iar, int sz) : IntArray(iar, sz) {
};//内联函数不加分号会引起（头停止点需要位于全局范围。未生成 IntelliSense PCH 文件）。错误处理
