#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/**
	相当于向下走指令和向右走指令的全排列
	用next_permutation
*/


int uniquePathsBrutalForce(int m, int n) { //TLE
	vector<char> dirVec;
	for (int i = 1; i < m; i++) //添加向右走的指令
		dirVec.push_back('1');
	for (int i = 1; i < n; i++)
		dirVec.push_back('2'); //添加向左走的指令
	int count = dirVec.size();

	int num = 1;
	while (next_permutation(dirVec.begin(), dirVec.end())) //计数
	{
		num++;
	}
	return num;;

}

int uniquePaths(int m, int n) {
	//相当于从m+n-2个位置中随机选取m-1个位置放向右走
	//计算C(m-1,m+n-2)
	long long  result = 1;
	for (int i = m + n - 2; i >=(m>n?m:n); i--) {
		result *= i;
	}
	for (int i = 1; i <= (m > n ? n-1 : m-1); i++)
		result /= i;
	return result;

}

int main() {
	cout<<uniquePaths(23, 12);
	system("pause");
}