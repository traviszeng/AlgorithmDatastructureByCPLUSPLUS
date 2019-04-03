/*
������������word1��word2,����ͨ�����ֲ�����word1��Ϊword2
���ֲ������£�
1.���һ����ĸ
2.ɾ��һ����ĸ
3.�滻һ����ĸ
��word1���word2��������ٲ�����

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
				dp[i][j] = j;   //��� i=0 ����Ҫ����j���ַ�
			}
			else if (j == 0) {
				dp[i][j] = i;    //���j=0����Ҫɾ��i���ַ�
			}
			else if (word1[i - 1] == word2[j - 1]) {   //����ַ���ͬ�����任����������ַ�֮ǰ�Ĳ���
				dp[i][j] = dp[i - 1][j - 1];
			}
			else {                          //���� �ʹӲ��룬ɾ�����޸���ѡ����С�� �� 1 
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