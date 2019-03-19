#include<iostream>
#include<cassert>
#include "IntArray.h"
#include "IntArrayRC.h"
using namespace std;

extern void swap(IntArray&, int, int);

void swap(IntArray &ia, int i, int j)
{
	int tmp = ia[i];
	ia[i] = ia[j];
	ia[j] = tmp;
}

int main()
{
	int array[4] = { 0, 1, 2, 3 };
	IntArray ia1(array, 4);
	IntArrayRC ia2(array, 4);

	// ���� һλƫ�� off-by-one Ӧ���� size-1 
	// IntArray ����׽�����������
	cout << "swap() with IntArray ia1\n";
	swap(ia1, 1, ia1.size());

	// ok: IntArrayRC ������Բ�׽�������Ĵ���
	cout << "swap() with IntArrayRC ia2\n";
	swap(ia2, 1, ia2.size());

	system("pause");
	return 0;
}
