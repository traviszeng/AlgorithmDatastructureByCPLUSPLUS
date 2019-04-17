#include<string>
#include<vector>
using namespace std;
//brutal 
string reverseWords(string s) {
	reverse(s.begin(), s.end());
	vector<string> result;
	string temp = "";
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ' ') {
			//result+=temp;
			result.push_back(temp);
			temp = "";
		}
		else {
			temp += s[i];
		}

	}
	result.push_back(temp);
	string finalR = "";
	for (int i = result.size() - 1; i >= 0; i--)
	{
		finalR += result[i];
		if (i > 0) finalR += " ";
	}
	return finalR;
}

//better solution
string reverseWords(string s) {
	//reverse(s.begin(),s.end());
	int prev = 0;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ' ') {
			reverse(s.begin() + prev, s.begin() + i);
			prev = i + 1;
		}


	}
	reverse(s.begin() + prev, s.end());
	return s;
}
