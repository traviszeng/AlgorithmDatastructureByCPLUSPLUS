#include<iostream>
#include<string>
#include<vector>
#include<stack>

using namespace std;
/*
中缀表达式先转后缀再求解
*/

/*
如果是操作数，则直接保存到输出string中；
如果是操作符
先判断栈是否为空。
若是，则直接将此运算符压入栈。
若不是，则查看当前栈顶元素。
若栈顶元素优先级大于或等于此操作符级别，则弹出栈顶元素，将栈顶元素添加到后缀表达式中，并继续进行上述判断。
如果不满足上述判断或者栈为空，将这个运算符入栈。要注意的是，经过上述步骤，这个运算符最终一定会入栈。
*/
//比较优先级
int getPriority(char ch)
{
	//获取优先级  
	if (ch == '(') return 1;
	else if (ch == '+' || ch == '-') return 2;
	else if (ch == '*' || ch == '/') return 3;
	else return 4;
}

bool compare(char &a, char &b) {
	return getPriority(a) > getPriority(b);
}


string inorder_to_postorder(string in) {
	
	string post = "";
	int indice = 0;
	stack<char> operators;
	while (indice < in.length()) {
		if (in[indice] <= '9' && in[indice] >= '0')
			while (in[indice] <= '9' && in[indice] >= '0' && indice < in.length())
			{
				post = post + in[indice];
				indice++;
			}
		else if (in[indice] == ' ')
			indice++;
		else {//操作符
			if (operators.size() == 0) {
				operators.push(in[indice]);
				indice++;
			}
			else {
				while (operators.size() != 0 && compare(operators.top(), in[indice])) {
					post =post+ operators.top();
					operators.pop();
				}
				operators.push(in[indice]);
				indice++;
			}
		
		}
		post += " ";
	}

	while (operators.size() != 0)
	{
		post += operators.top();
		operators.pop();
	}
	return post;
}


int calculate(string s) {
	s = inorder_to_postorder(s);
	stack<int> opNum;
	int indice = 0;
	while (indice < s.length()) {
		if (s[indice] <= '9' && s[indice] >= '0') {
			string tempNum = "";
			while (s[indice] <= '9' && s[indice] >= '0' && indice < s.length()) {
				tempNum += s[indice];
				indice++;
			}
			opNum.push(atoi(tempNum.c_str()));
		}
		else if (s[indice] == ' ')
			indice++;
		else {
			int right = opNum.top();
			opNum.pop();
			int left = opNum.top();
			opNum.pop();
			switch (s[indice]) {
			case '+':
				opNum.push(left + right);
				indice++;
				continue;
			case '-':
				opNum.push(left - right);
				indice++;
				continue;
			case '*':
				opNum.push(left * right);
				indice++;
				continue;
			case '/':
				if (left / right == 0 && s[indice + 1] == '/')
					opNum.push(left*right);
				else
					opNum.push(left / right);
				indice++;
				continue;

			}
			
		}
	}


	return opNum.top();
}


void cal(int &ans, char &preopera, int &pre, char &opera, int &digit) {
	int temp;
	if (opera == '*')
		temp = pre*digit;
	else
		temp = pre / digit;
	if (preopera == '+')
		ans += temp;
	else
		ans -= temp;
}
int calculate1(string s) {
	int pre = 1, digit = 0;//initialize as 0+1*0
	char opera = '*', preopera = '+';
	int ans = 0;
	s += '+';
	for (char c : s) {
		if (c == ' ')//ignore space ' '
			continue;
		else if (isdigit(c))//update digit
			digit = digit * 10 - '0' + c;
		else {
			if (c == '+' || c == '-') {//update ans and preopera
				cal(ans, preopera, pre, opera, digit);
				preopera = c;
				pre = 1;//initialize the right part as 1*0
				digit = 0;
				opera = '*';
			}
			else {
				if (opera == '*')//update pre and opera
					pre *= digit;
				else
					pre /= digit;
				opera = c;
				digit = 0;//initialize
			}
		}
	}
	return ans;
}


int main() {

	string S = "123-8*5-57/3+148+1*3/2*14*11*2*5/4*3/3/3+2283";
	cout << inorder_to_postorder(S);
	cout << calculate1(S);
	system("pause");
}