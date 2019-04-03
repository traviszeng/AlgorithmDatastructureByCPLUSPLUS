/*
给定两个单词word1和word2,可以通过三种操作将word1变为word2
三种操作如下：
1.添加一个字母
2.删除一个字母
3.替换一个字母
求将word1变成word2所需的最少操作数

sample input:
horse
ros
sample output:
3


sample input:
intention
execution

sample output:
5
*/

#include<string>
#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;


int minDistance(string word1, string word2) {
	int len1 = word1.length();
	int len2 = word2.length();

	vector<vector<int>>dp(len1 + 1, vector<int>(len2 + 1));
	for (int i = 0; i <= len1; i++) {
		for (int j = 0; j <= len2; j++) {
			if (i == 0) {
				dp[i][j] = j;   //如果 i=0 则需要插入j个字符
			}
			else if (j == 0) {
				dp[i][j] = i;    //如果j=0则需要删除i个字符
			}
			else if (word1[i - 1] == word2[j - 1]) {   //如果字符相同则不做变换，等于这个字符之前的步数
				dp[i][j] = dp[i - 1][j - 1];
			}
			else {                          //否则 就从插入，删除，修改中选择最小的 加 1 
				dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
			}
		}
	}
	return dp[len1][len2];
}

int main() {
	string a, b;
	cin >> a >> b;
	cout<<minDistance(a, b);
	system("pause");
}