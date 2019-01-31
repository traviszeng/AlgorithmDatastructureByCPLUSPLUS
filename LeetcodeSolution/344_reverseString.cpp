#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

void reverseString(vector<char>& s) {
	reverse(s.begin(),s.end());
}

int main() {
	vector<char> s;
	s.push_back('h');
	s.push_back('a');
	s.push_back('b');
	s.push_back('1');
	for (int i = 0; i < s.size(); i++)
		cout << s[i];
	reverseString(s);
	for (int i = 0; i < s.size(); i++)
		cout << s[i];
	system("pause");

}