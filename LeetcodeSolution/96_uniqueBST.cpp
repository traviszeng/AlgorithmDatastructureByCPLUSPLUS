#include<iostream>

using namespace std;

int numTrees(int n) {
	//n个节点的话固定根节点左右子树分别有k和n-1-k
	//动态规划
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