#include<iostream>
#include<vector>

using namespace std;
bool wordBreak(string s, vector<string>& wordDict) {
	int len = s.length();
	vector<bool> isSplit(len + 1, false);//��Ŵ�0-i�Ƿ�ɷ�

	isSplit[0] = true;
	for(int i = 0;i<len;i++)
		for (int j = i; j < len && isSplit[j]; j++) {
			
		}
}