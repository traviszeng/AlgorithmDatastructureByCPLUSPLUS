#include<string>
#include<vector>
using namespace std;

string lower(string s) {
	for (int i = 0; i < s.length(); i++) {
		if (s[i] >= 'A'&&s[i] <= 'Z')
			s[i] = 'a' + s[i] - 'A';
	}
	return s;
}


vector<string> findWords(vector<string>& words) {

	string first = "qwertyuiop", second = "asdfghjkl", third = "zxcvbnm";

	vector<string> res;

	for (string word : words)
	{
		string temp = lower(word);
		int first_flag = 0, second_flag = 0, third_flag = 0;
		for (auto letter : temp)
		{
			if (first.find(letter) != string::npos)
				first_flag++;
			else if (second.find(letter) != string::npos)
				second_flag++;
			else
				third_flag++;
		}

		if (first_flag == word.size() || second_flag == word.size() || third_flag == word.size())
			res.push_back(word);

	}

	return res;
}