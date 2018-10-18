#pragma once
#ifndef LINEARLIST_H
/**
���Ա�ĳ����ඨ��

*/
template<class T>
class LinearList {
public:

	virtual int Size()const = 0; //���������  //���麯�� const��ʾ�����޸������ݳ�Ա
	virtual int Length()const = 0;//�����
	virtual int Search(T& x) const = 0;//�ڱ�����������ֵx
	virtual bool getData(int i, T&x) const = 0;//�ڱ��ж�λ��i��Ԫ��λ��
	virtual void setData(int i, T& x) = 0;//ȡ��i�������ֵ
	virtual bool Insert(int i, T& x) = 0;//�ڵ�i����������x
	virtual bool Remove(int i, T& x) = 0;//ɾ����i�����ͨ��x����
	virtual bool IsEmpty() const = 0;//�жϱ��Ƿ�Ϊ��
	virtual bool IsFull() const = 0;//�жϱ��Ƿ�����
	virtual void Sort() = 0;//����
	virtual void input() = 0;//����
	virtual void output() = 0;//���
	//virtual LinearList<T> operator=(const LinearList<T>& L)=0;

};


#endif // !LINEARLIST_H

