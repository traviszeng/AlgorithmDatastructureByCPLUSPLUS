#include<iostream>
#include<string>
#include "LinkedStack.h"

const int maxLength = 100;
/**
括号匹配问题
*/
void printMatchedPairs(char *expression) {
	LinkedStack<int> s(maxLength);
	int j, length = strlen(expression);
	for (int i = 0; i < length; i++)
	{
		if (expression[i - 1] == '(') s.Push(i);
		else if (expression[i - 1] == ')') {
			if (s.Pop(j) == true)
				cout << j << "与" << i << "匹配" << endl;
			else
				cout << "没有与第" << i << "个有括号匹配的左括号！" << endl;
		}
		while (s.IsEmpty() == false)
		{
			s.Pop(j);
			cout << "没有与第" << j << "个左括号相匹配的右括号！" << endl;
		}
	}
}

