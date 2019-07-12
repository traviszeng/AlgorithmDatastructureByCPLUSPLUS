#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/**
	�൱��������ָ���������ָ���ȫ����
	��next_permutation
*/


int uniquePathsBrutalForce(int m, int n) { //TLE
	vector<char> dirVec;
	for (int i = 1; i < m; i++) //��������ߵ�ָ��
		dirVec.push_back('1');
	for (int i = 1; i < n; i++)
		dirVec.push_back('2'); //��������ߵ�ָ��
	int count = dirVec.size();

	int num = 1;
	while (next_permutation(dirVec.begin(), dirVec.end())) //����
	{
		num++;
	}
	return num;;

}

int uniquePaths(int m, int n) {
	//�൱�ڴ�m+n-2��λ�������ѡȡm-1��λ�÷�������
	//����C(m-1,m+n-2)
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