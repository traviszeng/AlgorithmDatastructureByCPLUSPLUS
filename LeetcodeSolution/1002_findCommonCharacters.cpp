#include<vector>
#include<string>

#include<iostream>
using namespace std;


vector<string> commonChars(vector<string>& A) {
	vector<int> charTimes(26, 0);
	for (int i = 0; i < A[0].length(); i++)
		charTimes[A[0][i]-'a']++;

	for (int i = 1; i < A.size(); i++) {
		vector<int> tempCharTimes(26, 0);
		for (int j = 0; j < A[i].length(); j++)
			tempCharTimes[A[i][j] - 'a']++;

		for (int j = 0; j < 26; j++)
			charTimes[j] = (charTimes[j] > tempCharTimes[j]) ? tempCharTimes[j] : charTimes[j];

	}

	vector<string> result;
	for (int i = 0; i < 26; i++) {
		if (charTimes[i] == 0)
			continue;
		for (int j = 0; j < charTimes[i]; j++) {
			string temp = "";
			temp += (i + 'a');
			result.push_back(temp);
		}
	}


	return result;
}

int main() {
	vector<string> s{ "beella","label","roller" };
	commonChars(s);
	system("pause");
}