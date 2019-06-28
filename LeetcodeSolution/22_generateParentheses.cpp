#include<vector>
#include<stack>
#include<algorithm>
using namespace std;

vector<string> generateParenthesis(int n) {
	vector<string> result;
	if (n <= 0) {
		result.push_back("");
		return result;
	}
	string start="";
	for (int i = 0; i < n; i++)
		start += '(';
	for (int i = 0; i < n; i++)
		start += ')';
	if (isValid(start))
		result.push_back(start);

	while (next_permutation(start.begin(), start.end())) {
		
		if (isValid(start))
			result.push_back(start);
	}
	return result;
}

bool isValid(string s) {

	if (s == "")
		return true;
	stack<char> p;
	for (int i = 0; i < s.length(); i++) {
		if (p.empty())
			p.push(s[i]);
		else {
			if (s[i] == ')' && p.top() == '(')
				p.pop();
			else if (s[i] == ')' && p.top() != '(')
				return false;
			else
				p.push(s[i]);
		}
	}

	if (p.empty())
		return true;
	else
		return false;
}