#include<iostream>
#include "Array.h"
#include<vector>
#include<algorithm>
//namespace MyArray = My_version_of_Array;
//using MyArray::Array;
using namespace std;


int main() {
	//MyArray::Array<int> ia(1024);

	vector<int> veco;
	const int size = 8;
	const int value = 1024;
	// size 为 8 的 vector 
	// 每个元素都被初始化为 0 
	vector<int> vec1(size);
	// size 为 8 的 vector 
	// 每个元素都被动始化为 1024 
	vector<int> vec2(size, value);
	// vtc3 的 size 为 4 
	// 被初始化为 ia 的 4 个值
	int iaa[4] = { 0, 1, 1, 2 };
	vector<int> vec3(iaa, iaa + 4);
	// vec4 是 vec2 的拷贝
	vector<int> vec4(vec2);


	//sort(ivec.begin(), ivec.end());
	//只想对 ivec 向量的前面一半进行排序 可以这样写
    //sort(ivec.begin(), ivec.begin() + ivec.size() / 2);
	//泛型算法还能接受指向内置数组的指针对 例如 已知数组
	int ia[10] = {
		51, 23, 7, 88, 41, 98, 12, 103, 37, 6 };
	vector< int > vec(ia, ia + 10);

	// 排序数组
	sort(vec.begin(), vec.end());

	// 获取值
	int search_value;
	cin >> search_value;

	// 搜索元素
	vector<int>::iterator found;
	found = find(vec.begin(), vec.end(), search_value);
	if (found != vec.end())
		cout << "search_value found!\n";
	else cout << "search_value not found!\n";

	// 反转数组
	reverse(vec.begin(), vec.end());
	system("pause");
}