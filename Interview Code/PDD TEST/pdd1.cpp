#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;
/*
����һ������Ϊż��������arr�����������е�����������Բ���ͣ�
����Щ����ѡ��������Сֵ�����ʸ����������Բ����������Сֵ�ò�ֵ��С
*/
int main() {
	int n;
	cin >> n;
	vector<int> num;
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		num.push_back(temp);
	}

	sort(num.begin(), num.end());
	vector<int> he;
	for (int i = 0; i < n / 2; i++) {
		int temp = num[i] + num[n - 1 - i];
		he.push_back(temp);
	}

	sort(he.begin(), he.end());
	cout<<he[n / 2 - 1] - he[0];
	return 0;



}