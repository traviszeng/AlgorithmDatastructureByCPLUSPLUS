#include<iostream>
#include<vector>

using namespace std;
bool wordBreak(string s, vector<string>& wordDict) {
	int len = s.length();
	vector<bool> isSplit(len + 1, false);//存放从0-i是否可分

	isSplit[0] = true;
	for(int i = 0;i<len;i++)
		for (int j = i; j < len && isSplit[j]; j++) {
			
		}
}