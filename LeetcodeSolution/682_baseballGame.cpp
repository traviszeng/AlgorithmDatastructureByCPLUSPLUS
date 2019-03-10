#include<iostream>
#include<string>
#include<stack>
using namespace std;

int calPoints(vector<string>& ops) {
	string DOUBLE = "D";
	string REMOVE = "C";
	string PLUS = "+";
	int sum = 0;

	stack<int> num;
	for (int i = 0; i<ops.size(); i++) {
		if (ops[i] == REMOVE)
			num.pop();
		else if (ops[i] == DOUBLE)
		{
			int number = num.top();
			num.push(number * 2);
		}
		else if (ops[i] == PLUS) {
			int num1 = num.top();
			num.pop();
			int num2 = num.top();
			num.push(num1);
			num.push(num1 + num2);
		}
		else
			num.push(stoi(ops[i]));

	}

	while (num.size() != 0) {
		sum += num.top();
		num.pop();

	}
	return sum;
}