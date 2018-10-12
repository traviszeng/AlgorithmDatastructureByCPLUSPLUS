#include<iostream>
#include<cassert>
using namespace std;
/*
自定义数组类型
*/
/*
下面是第一步所支持操作的集合
1.数组类的实现中有内置的自我意识 首先 它知道自己的大小
2.数组类支持数组之间的赋值 以及两个数组之间的相等和不相等的比较操作
3.数组类应该支持对其所含的值进行下列查询操作 数组中最小值是什么 最大值是什么 某个特殊的值是否在数组中 如果存在 它占的第一个位置的索引是什么
4.数组类支持自排序 为了便于讨论 假定存在一群用户 他们认为数组支持排序的功能很重要 而另外一些人对此却不以为然
除了支持数组操作 还必须支持数组本身的机制 包括
5.能够指定长度 以此来创建数组 这个值无需在编译时刻知道
6.能够用一组值初始化数组
7.能够通过一个索引来访问数组中的单个元素 为便于讨论 假设用户强烈要求用数组
下标操作符来实现这项功能
8.能够截获并指出错误的索引值 假设我们认为这很有必要 所以没有询问用户的想法
我们认为这是一个设计良好的数组所必须实现的
*/
class IntArray {

public :
	explicit IntArray(int sz = DefaultArraySize);
	IntArray(int *array, int array_size);
	IntArray(const IntArray &rhs);

	//重构
	void initData(int sz, int *array);

	bool operator==(const IntArray&) const;
	bool operator!=(const IntArray&) const;
	//通过[]访问下标
	int& operator[](int index);

	IntArray& operator=(const IntArray&);

	int size() const { return _size; }
	void sort();

	int min() const;
	int max() const;

	//如果值在数组中找到，则返回第一次出现的索引
	//否则返回-1
	int find(int value)const;

	~IntArray() {
		delete[]ia;
	}
private:
	//私有代码
	int _size;
	int *ia;

	static const int DefaultArraySize = 12;
};

IntArray::IntArray(int sz) {
	//设置数据成员
	initData(sz, 0);

}

IntArray::IntArray(int *array, int sz) {
	initData(sz, array);
}

IntArray::IntArray(const IntArray &a) {
	initData(a._size, a.ia);
}

void IntArray::initData(int sz,int *array) {
	_size = sz;
	ia = new int[_size];
	for (int i = 0; i < _size; i++)
		if (!array)
			ia[i] = 0;
		else
			ia[i] = array[i];
}

int& IntArray::operator[](int index) {
	assert(index >= 0 && index < _size);
	return ia[index];
}




int main() {
	IntArray myArray();
	IntArray* pArray = new IntArray();

	//类对象访问
	//int max_val = myArray.max();
	//类对象指针访问
	//int min_val = pArray->min();


	int ia[10] = { 0,1,2,3,4,5,6,7,8,9 };
	IntArray iA3(ia, 10);

	IntArray anArray();
	IntArray anotherArray(iA3);


	system("pause");
	return 0;
}
