#include<stack>
using namespace std;

bool isValid(string s) {

	if (s == "")
		return true;
	stack<char> p;
	for (int i = 0; i < s.length(); i++) {
		if (p.empty())
			p.push(s[i]);
		else {
			if (s[i] == '}' && p.top() == '{')
				p.pop();
			else if (s[i] == ']' && p.top() == '[')
				p.pop();
			else if (s[i] == ')' && p.top() == '(')
				p.pop();
			else
				p.push(s[i]);
		}
	}

	if (p.empty())
		return true;
	else
		return false;
}