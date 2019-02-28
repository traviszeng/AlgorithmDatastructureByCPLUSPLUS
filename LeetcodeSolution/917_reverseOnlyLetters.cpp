#include<string>
#include<iostream>
using namespace std;

string reverseOnlyLetters(string S) {
	if (S.length() == 0)
		return "";
	int start = 0;
	int end = S.length() - 1;

	while (start < end) {
		while (!((S[start] <= 90 && S[start] >= 65) || (S[start] <= 122 && S[start] >= 97)))
			start++;
		while (!((S[end] <= 90 && S[end] >= 65) || (S[end] <= 122 && S[end] >= 97)))
			end--;
		if (start < end) {
			swap(S[start], S[end]);
			start++;
			end--;
		}

	}
	return S;
}

int main() {
	string s = "he-ell=o";
	cout << reverseOnlyLetters(s);
	system("pause");
	return 0;
}