#include<iostream>

using namespace std;

int numTrees(int n) {
	//n���ڵ�Ļ��̶����ڵ����������ֱ���k��n-1-k
	//��̬�滮
	int *dp = new int[n+1];
	dp[0] = 1;
	dp[1] = 1;
	dp[2] = 2;
	for (int i = 3; i <= n; i++) {
		dp[i] = 0;
		for (int k = 0; k < i; k++) {
			dp[i] += dp[k] * dp[i-1 - k];
		}
	}
	return dp[n];
}

int main(){
	cout << numTrees(4);
	system("pause");

}