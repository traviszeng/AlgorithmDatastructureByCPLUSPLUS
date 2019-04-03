#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;
/*
给定一个长度为偶数的数组arr，将该数组中的数字两两配对并求和，
在这些和中选出最大和最小值，请问该如何两两配对才能让最大最小值得差值最小
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