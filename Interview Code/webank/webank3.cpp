#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int my_pow(int a, int b) {
	int result = 1;
	while (b > 0) {
		if (b & 1) result = result * a;
		a *= a;
		b >>= 1;
	
	}
	return result;
}

bool isHuiWen(int n) {
	vector<int> a;
	int nn = n;
	while (nn != 0) {
		a.push_back(nn % 2);
		nn =nn/ 2;
	}
	/*reverse(a.begin(), a.end());

	int sum = 0;
	for (int i = 0; i < a.size(); i++) {
		sum += a[i] * my_pow(2, i);
	}
	if (sum == n) return true;
	else
		return false;*/
	for (int i = 0; i < a.size() / 2; i++)
		if (a[i] != a[a.size() - 1 - i])
			return false;
	return true;
}


int main() {
	int n;
	int sum = 0;
	cin >> n;
	for (int i = 0; i <= n; i++) {
		if (isHuiWen(i))
			sum++;
	}
	cout << sum;
	//system("pause");
}