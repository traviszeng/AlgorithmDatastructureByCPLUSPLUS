#include "SeqList.h"
#include <fstream>
#include<iostream>
#include <cassert>
using namespace std;
//��˳�����Ϊ����ʹ�ã�������
void UNION(SeqList<int>& LA, SeqList<int>& LB);
//������
void INTERSECTION(SeqList<int>& LA, SeqList<int>& LB);
int main() {
	SeqList<int> list(5);
	ifstream fin("list.txt");
	assert(fin);
	fin >> list;
	cout << "The initial list in the file is:\n" << list << endl;
	list.Sort();
	cout << "After sorted:\n" << list << endl;

	cout << "========================================\n";
	int i, elem;
	cout << "Test the Insert, Remove and Search function:\n";
	cout << "Each test will terminate by an invaid input.";
	cout << "\n----------------------------------------\n";

	cout << "1. Test the Insert(int i, T &elem):\n";
	while (1) {
		cout << "Input the index i and data elem to insert: ";
		cin >> i >> elem;
		if (!cin) {
			cin.clear();
			cin.ignore(100, '\n');
			break;
		}
		if (i < 0)	break;
		if (list.Insert(i, elem))	cout << "Insert successful!\n";
		else	cout << "Insert failed!\n";
	}
	cout << "\nAfter inserted\n" << list << endl;

	cout << "----------------------------------------\n";
	cout << "2. Test the Remove(int i, T &elem):\n";
	while (1) {
		cout << "Input the index i in which you want to remove: ";
		cin >> i;
		if (!cin) {
			cin.clear();
			cin.ignore(100, '\n');
			break;
		}
		if (i < 0)	break;
		if (list.Remove(i, elem))	cout << "The element " << elem << " has been removed!\n";
		else	cout << "Remove failed!\n";
	}
	cout << "\nAfter removed\n" << list << endl;

	cout << "----------------------------------------\n";
	cout << "3. Test the Search(T &elem):\n";
	while (1) {
		cout << "Input the element you want to search: ";
		cin >> elem;
		if (!cin) {
			cin.clear();
			cin.ignore(100, '\n');
			break;
		}
		if (elem < 0)	break;
		i = list.Search(elem);
		if (i != 0)	cout << "The index of element " << elem << " is " << i << ".\n";
		else	cout << "The element is not exist!\n";
	}
	cout << "\n----------------------------------------\n";
	cout << "End test!" << endl;
	return 0;
}

void UNION(SeqList<int>& LA, SeqList<int>& LB) {//��LA��LB�ϲ����������LA���ظ�Ԫ��ֻ����һ��
	int n = LA.Length, m = LB.Length, i, k, x;
	for (i = 1; i <= m; i++) {
		LB.getData(i, x);//LB��ȡһ��Ԫ��
		k = LA.Search(x);//��LA��������
		if (k == 0)//��LA��δ�ҵ������
		{
			LA.Insert(n, x);
			n++;
		}
	}

}

void INTERSECTION(SeqList<int>& LA, SeqList<int>& LB) {//��LA��LB�еĹ���Ԫ�أ��������LA
	int n = LA.Length, m = LB.Length, i, k, x;
	while (i <= n) {
		LA.getData(i, x);
		if (LB.Search(x) == 0) {
			LA.Remove(i, x);
			n--;
		}
		else
			i++;
	}
}