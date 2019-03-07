#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int maxProfit(vector<int>& prices) {
	if (prices.size() == 0)
		return 0;
	//存放从i买入的max
	int *dp = new int[prices.size()];

	for (int i = 0; i<prices.size(); i++) {
		dp[i] = 0;
		for (int j = i + 1; j<prices.size(); j++)
		{
			dp[i] = dp[i]>(prices[j] - prices[i]) ? dp[i] : prices[j] - prices[i];

		}

	}
	int max = dp[0];
	for (int i = 1; i<prices.size(); i++)
		max = max>dp[i] ? max : dp[i];

	return max;
}

int maxProfit(vector<int>& prices) {
	int max_profit = 0;
	int min_price = INT_MAX;
	for (int i = 0; i < prices.size(); i++) {
		int tmp = prices[i] - min_price;
		max_profit = max(max_profit, tmp);
		min_price = min(min_price, prices[i]);
	}
	return max_profit;
}

