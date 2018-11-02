#include<iostream>
#include<string>
#include "LinkedStack.h"

const int maxLength = 100;
/**
����ƥ������
*/
void printMatchedPairs(char *expression) {
	LinkedStack<int> s(maxLength);
	int j, length = strlen(expression);
	for (int i = 0; i < length; i++)
	{
		if (expression[i - 1] == '(') s.Push(i);
		else if (expression[i - 1] == ')') {
			if (s.Pop(j) == true)
				cout << j << "��" << i << "ƥ��" << endl;
			else
				cout << "û�����" << i << "��������ƥ��������ţ�" << endl;
		}
		while (s.IsEmpty() == false)
		{
			s.Pop(j);
			cout << "û�����" << j << "����������ƥ��������ţ�" << endl;
		}
	}
}

