#include<iostream>
#include<string>
#include<map>
using namespace std;

int main() {
	string a;
	cin >> a;
	bool flag = false;
	map<char,int> dic;
	for (int i = 0; i < a.length(); i++) {
		if (a[i] == ',') continue;
		if (dic.find(a[i]) != dic.end())
		{
			cout << "true";
			flag = true;
			break;
		}
		else {
			dic[a[i]] = 1;
		}
	}
	if(!flag) cout << "false";
	system("pause");
	return 0;
}