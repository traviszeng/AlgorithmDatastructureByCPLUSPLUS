#include<algorithm>

int climbStairs(int n) {
	int *dp = new int[n + 1];
	if (n <= 0)
		return 0;
	if (n == 1)
		return 1;
	if (n == 2)
		return 2;
	memset(dp, 0, n);
	dp[0] = 0;
	dp[1] = 1;
	dp[2] = 2;
	for (int i = 3; i<n + 1; i++) {
		dp[i] = dp[i - 1] + dp[i - 2];
	}
	int result = dp[n];
	delete[] dp;
	return result;
}