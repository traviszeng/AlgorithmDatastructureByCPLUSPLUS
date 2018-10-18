#pragma once
#ifndef LINEARLIST_H
/**
线性表的抽象类定义

*/
template<class T>
class LinearList {
public:

	virtual int Size()const = 0; //求表最大体积  //纯虚函数 const表示不能修改其数据成员
	virtual int Length()const = 0;//求表长度
	virtual int Search(T& x) const = 0;//在表中搜索给定值x
	virtual bool getData(int i, T&x) const = 0;//在表中定位第i个元素位置
	virtual void setData(int i, T& x) = 0;//取第i个表项的值
	virtual bool Insert(int i, T& x) = 0;//在第i个表项猴插入x
	virtual bool Remove(int i, T& x) = 0;//删除第i个表项，通过x返回
	virtual bool IsEmpty() const = 0;//判断表是否为空
	virtual bool IsFull() const = 0;//判断表是否已满
	virtual void Sort() = 0;//排序
	virtual void input() = 0;//输入
	virtual void output() = 0;//输出
	//virtual LinearList<T> operator=(const LinearList<T>& L)=0;

};


#endif // !LINEARLIST_H

