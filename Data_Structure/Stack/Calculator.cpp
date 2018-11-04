#include<math.h>
#include "SeqStack.h"
#include<iostream>

/**
�򵥼���������׺������ʽ
*/
class Calculator {
public:
	Calculator(int sz) :s(sz) {}
	void Run(); //ִ�б��ʽ����
	void Clear();



private:
	SeqStack<double> s;

	void AddOperand(double value);//��������ջ
	bool get2Operands(double &left, double &right); //��ջ���˳�����������
	void DoOperator(char op); //�γ�����ָ����м���


};


void Calculator::DoOperator(char op) {
	//ȡ���������������ݲ�����op�γ�����ָ�����
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
		cerr << "ȱ���Ҳ�����" << endl;
		return false;
	}
	s.Pop(right);
	if (s.IsEmpty()) {
		cerr << "ȱ���������" << endl;
		return false;
	}

	s.Pop(left);
	return true;


}


void Calculator::AddOperand(double value) {
	//����������ֵvalue��������ջ
	s.Push(value);
}

void Calculator::Run() {

//���ַ�������һ����׺���ʽ��ֵ����#����

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