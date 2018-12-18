#pragma once
#include<queue>
#include <exception>

using namespace std;
/**
尝试使用两个队列来模拟一个栈的操作
*/

template<typename T>
class CStack {
public:
	int flag;
	CStack(void);
	~CStack(void);

	void pushStack(const T& node);

	T popStack();

private:
	
	 queue<T> queue1;
	 queue<T> queue2;

	};
template <typename T> CStack<T>::CStack(void)
{
}

template <typename T> CStack<T>::~CStack(void)
{
}


template<typename T> T CStack<T>::popStack() {
	if (flag == 0) {
		if (queue1.size() == 1) { 
			T data = queue1.front();  
			queue1.pop(); 
			return data;
		}
		//数据在queue1中
		if (queue1.size() == 0) throw new exception("stack is empty!");
		while (queue1.size() > 1) {
			T data = queue1.front();
			queue1.pop();
			queue2.push(data);
		}

		flag = 1;
		T result = queue1.front();
		queue1.pop();
		return result;
	}
	else {
		if (queue2.size() == 1) {
			T data = queue2.front();
			queue2.pop();
			return data;
		}
		if (queue2.size() == 0) throw new exception("stack is empty!");
		while (queue2.size() > 1) {
			T data = queue2.front();
			queue2.pop();
			queue1.push(data);
		}

		flag = 0;
		T result = queue2.front();
		queue2.pop();
		return result;
	}
}

template<typename T> void CStack<T>::pushStack(const T& node) {
	if (flag == 1) {
		queue2.push(node);
	}
	else {
		queue1.push(node);
	}

}

// ====================测试代码====================
void Test(char actual, char expected)
{
	if (actual == expected)
		printf("Test passed.\n");
	else
		printf("Test failed.\n");
}

int main(int argc, char* argv[])
{
	CStack<char> stack;

	stack.pushStack('a');
	stack.pushStack('b');
	stack.pushStack('c');

	char head = stack.popStack();
	Test(head, 'c');

	head = stack.popStack();
	Test(head, 'b');

	stack.pushStack('d');
	head = stack.popStack();
	Test(head, 'd');

	stack.pushStack('e');
	head = stack.popStack();
	Test(head, 'e');

	head = stack.popStack();
	Test(head, 'a');
	system("pause");
	return 0;
}