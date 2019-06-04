/**
01��������Ķ�̬�滮
*/


/**
����������

�� n ����������ֵ�ֱ�Ϊ w_i, v_i ����Ʒ��
����Щ��Ʒ��ѡ�������������� W ����Ʒ��ʹ���ܼ�ֵ���

ʾ��
1                // ������
5 10             // ��Ʒ�� �������� N <= 1000 , V <= 1000
1 2 3 4 5
5 4 3 2 1

14
*/

/**
��άDP

���壺dp[i][j] := ��ǰ i ����Ʒ��ѡȡ������������ j ����Ʒʱ�ܼ�ֵ�����ֵ
i �� 1 ��ʼ�ƣ������� i ����Ʒ

��ʼ��
dp[0][j] = 0
״̬ת��
dp[i][j] = dp[i-1][j]            if j < w[i] ����ǰʣ�������������µ� i ����Ʒ��
= max{                  else ��ȡ����������������ֵ��
dp[i-1][j],             // ���õ� i ����Ʒ
dp[i-1][j-w[i]] + w[j]  // �õ� i ����Ʒ
}
*/


#include<iostream>
#include<memory>
#include<vector>
#include<algorithm>
using namespace std;


int twoDDPsolution(int N,int V,vector<int> v,vector<int> w) {
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
}



int main() {
	int T;      // ������
	cin >> T;
	while (T--) {
		int N , V ;                   // N: ��Ʒ������V: ��������
		cin >> N >> V;
		vector<int> v(N + 1, 0);    // ����ÿ����Ʒ�ļ�ֵ
		vector<int> w(N + 1, 0);    // ����ÿ����Ʒ������
		for (int i = 1; i <= N; i++)
			cin >> v[i];
		for (int i = 1; i <= N; i++)
			cin >> w[i];

		int ans = twoDDPsolution(N, V, v, w);

		printf("%d\n", ans);
	}
	system("pause");
	return 0;
}
