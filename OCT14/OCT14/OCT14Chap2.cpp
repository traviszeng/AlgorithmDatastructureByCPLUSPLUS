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
	// size Ϊ 8 �� vector 
	// ÿ��Ԫ�ض�����ʼ��Ϊ 0 
	vector<int> vec1(size);
	// size Ϊ 8 �� vector 
	// ÿ��Ԫ�ض�����ʼ��Ϊ 1024 
	vector<int> vec2(size, value);
	// vtc3 �� size Ϊ 4 
	// ����ʼ��Ϊ ia �� 4 ��ֵ
	int iaa[4] = { 0, 1, 1, 2 };
	vector<int> vec3(iaa, iaa + 4);
	// vec4 �� vec2 �Ŀ���
	vector<int> vec4(vec2);


	//sort(ivec.begin(), ivec.end());
	//ֻ��� ivec ������ǰ��һ��������� ��������д
    //sort(ivec.begin(), ivec.begin() + ivec.size() / 2);
	//�����㷨���ܽ���ָ�����������ָ��� ���� ��֪����
	int ia[10] = {
		51, 23, 7, 88, 41, 98, 12, 103, 37, 6 };
	vector< int > vec(ia, ia + 10);

	// ��������
	sort(vec.begin(), vec.end());

	// ��ȡֵ
	int search_value;
	cin >> search_value;

	// ����Ԫ��
	vector<int>::iterator found;
	found = find(vec.begin(), vec.end(), search_value);
	if (found != vec.end())
		cout << "search_value found!\n";
	else cout << "search_value not found!\n";

	// ��ת����
	reverse(vec.begin(), vec.end());
	system("pause");
}