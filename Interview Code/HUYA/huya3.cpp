#include<iostream>
#include<string>
using namespace std;

int main() {
	string s;
	cin >> s;
	int temp = 0;
	int sum = 0;
	bool isMinus = false;

	for (int i = 0; i < s.length(); i++) {
		if (s[i] >= '0'&&s[i] <= '9') {
			temp *= 10;
			temp += s[i] - '0';
		}
		else if (temp != 0 && s[i] != '-' &&s[i] != '+') {
			if (!isMinus)
				sum += temp;
			else
				sum -= temp;
			temp = 0;
			isMinus = false;
		}
		else if (s[i] == '-') {
			
			if (temp != 0) {
				if (!isMinus)
					sum += temp;
				else
					sum -= temp;
			}
			temp = 0;
			isMinus = true;
		}
		else {
			continue;
		}
	}
	if (temp != 0)
	{
		if (!isMinus)
			sum += temp;
		else
			sum -= temp;
	}
	cout << sum;
	system("pause");

}