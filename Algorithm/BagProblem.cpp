
/**
01背包
问题描述：

有 n 个重量个价值分别为 w_i, v_i 的物品。
从这些物品中选出总重量不超过 W 的物品，使其总价值最大。

示例
1                // 用例数
5 10             // 物品数 背包容量 N <= 1000 , V <= 1000
1 2 3 4 5
5 4 3 2 1

14


二维DP

定义：dp[i][j] := 从前 i 个物品中选取总重量不超过 j 的物品时总价值的最大值
i 从 1 开始计，包括第 i 个物品

初始化
dp[0][j] = 0
状态转移
dp[i][j] = dp[i-1][j]            if j < w[i] （当前剩余容量不够放下第 i 个物品）
= max{                  else （取以下两种情况的最大值）
dp[i-1][j],             // 不拿第 i 个物品
dp[i-1][j-w[i]] + w[j]  // 拿第 i 个物品
}
*/


#include<iostream>
#include<memory>
#include<vector>
#include<algorithm>
using namespace std;
/**
	二维数组没有优化
*/

int solution1_01bag(int N,int V,vector<int> v,vector<int> w) {
	/*
	int * dp= new int[(N+1)*(V+1)];
	for (int i = 0; i < (N+1)*(V+1); i++)
		dp[i] = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j <=V; j++) {
			if (w[i] > j)
				dp[i*(V + 1) + j] = dp[(i - 1)*(V + 1) + j];
			else
				dp[i*(V + 1) + j] = std::max(dp[(i - 1)*(V + 1) + j], dp[(i - 1)*(V + 1) + j - w[i]]+v[i]);
		}
	}
	return dp[(N + 1)*(V + 1) - 1];
	
	*/

	vector<vector<int>> dp(N + 1, vector<int>(V + 1, 0));
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j <= V; j++) {
			if (w[i] > j) {
				dp[i][j] = dp[i - 1][j];
			}
			else {
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
			}
		}
	}
	return dp[N][V];
}

/**
	利用滚动数组优化存储空间
	d[i]仅与d[i-1]和d[i]有关
*/
int solution2_01bag(int N, int V, vector<int> v, vector<int> w) {
	vector<vector<int>> dp(2, vector<int>(V + 1, 0));
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j <= V; j++) {
			if (w[i] > j) {
				dp[i &1][j] = dp[(i - 1)&1][j];
			}
			else {
				dp[i&1][j] = max(dp[(i - 1) & 1][j], dp[(i-1) & 1][j - w[i]] + v[i]);
			}
		}
	}
	return dp[N&1][V];
}


//dp[i] 重量不超过i的价值的最大值
int solution3_01bag(int N, int V, vector<int> v, vector<int> w) {
	vector<int> dp(V + 1, 0);
	for (int i = 1; i <= N; i++) {
		for (int j = V; j >= w[i]; j--) {
			dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
		}
	}
	return dp[V];
}

/**
背包问题 是否能装满整个背包
*/
/**
背包中每个物品只有一个，所以只存在选或不选；
完全背包中每个物品可以选取任意件。

注意：本题要求是背包恰好装满背包时，求出最大价值总和是多少。如果不能恰好装满背包，输出 NO

*/


int main() {
	int T;      // 用例数
	cin >> T;
	while (T--) {
		int N , V ;                   // N: 物品数量；V: 背包容量
		cin >> N >> V;
		vector<int> v(N + 1, 0);    // 保存每个物品的价值
		vector<int> w(N + 1, 0);    // 保存每个物品的重量
		for (int i = 1; i <= N; i++)
			cin >> v[i];
		for (int i = 1; i <= N; i++)
			cin >> w[i];

		int ans = solution3_01bag(N, V, v, w);

		printf("%d\n", ans);
	}
	system("pause");
	return 0;
}
