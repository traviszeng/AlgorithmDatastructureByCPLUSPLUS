#include<math.h>
#include "SeqStack.h"
#include<iostream>

/**
简单计算器，后缀运算表达式
*/
class Calculator {
public:
	Calculator(int sz) :s(sz) {}
	void Run(); //执行表达式计算
	void Clear();



private:
	SeqStack<double> s;

	void AddOperand(double value);//进操作数栈
	bool get2Operands(double &left, double &right); //从栈中退出两个操作数
	void DoOperator(char op); //形成运算指令，进行计算


};


void Calculator::DoOperator(char op) {
	//取两个操作数，根据操作符op形成运算指令并计算
	double left, right, value;
	bool result;
	result = get2Operands(left, right);
	if (result) 
		switch (op)
		{
		case '+':
			value = left + right;
			s.Push(value);
			break;

		case '-':
			value = left - right;
			s.Push(value);
			break;
		case '*':
			value = left*right;
			s.Push(value);
			break;

		case '/':
			if (right == 0.0) {
				cerr << "Divide by 0!" << endl;
				Clear();
			}
			else {
				value = left / right;
				s.Push(value);
			}
			break;
		default:
			Clear();
		}



}

bool Calculator::get2Operands(double &left, double &right) {

	if (s.IsEmpty()) {
		cerr << "缺少右操作数" << endl;
		return false;
	}
	s.Pop(right);
	if (s.IsEmpty()) {
		cerr << "缺少左操作数" << endl;
		return false;
	}

	s.Pop(left);
	return true;


}


void Calculator::AddOperand(double value) {
	//将操作数的值value进操作数栈
	s.Push(value);
}

void Calculator::Run() {

//读字符串并求一个后缀表达式的值，以#结束

	char ch;
	double newOperand;
	while (cin >> ch, ch != '#') {
		switch (ch)
		{
		case '+':case '-':case '*':case '/':
			DoOperator(ch); break;
			

		default:
			cin.putback(ch);
			cin >> newOperand;
			AddOperand(newOperand);
		}
	}
}

void Calculator::Clear() {
	s.MakeEmpty();

}


void main() {

	Calculator c(50);
	c.Run();
}