#include<vector>
#include<iostream>
using namespace std;

/*
有个数列表示数字0-9可以被使用的次数，另有两个整数AB由这些数字组成，
已知A B的各自的位数，求A和B乘积的最小值
65% passed
*/
int main() {
	int a[10];
	for (int i = 0; i < 10; i++)
		cin >> a[i];

	int x, y;
	cin >> x >> y;

	//先排列位数小的 让位数小的尽可能小

	if (x > y) {
		int sum = 0;
		int endwith;
		for (int i = 0; i < 10; i++) {
			sum += a[i];
			if (sum >= y)
			{//到数字endwith可以分配完位数小的数字
				endwith = i;
				break;
			}
		}
		sum = 0;
		for (int i = 0; i <= endwith; i++) {
			if (a[i] == 0)
				continue;
			while (a[i] != 0 && y != 0) {
				sum *= 10;
				sum += i;
				a[i]--;
				y--;
			}

		}
		int sum2 = 0;
		for (int i = endwith; i < 10; i++) {
			if (x == 0) break;
			if (a[i] == 0)
				continue;
			while (a[i] != 0 && x != 0) {
				sum2 *= 10;
				sum2 += i;
				a[i]--;
				x--;
			}
		}
		cout<<sum * sum2;
	}
	else {
		int sum = 0;
		int endwith;
		for (int i = 0; i < 10; i++) {
			sum += a[i];
			if (sum >= x) {
				//到数字endwith可以分配完位数小的数字
				endwith = i;
				break;
			}
		}
		sum = 0;
		for (int i = 0; i <= endwith; i++) {
			if (a[i] == 0)
				continue;
			while (a[i] != 0 && x != 0) {
				sum *= 10;
				sum += i;
				a[i]--;
				x--;
			}

		}
		int sum2 = 0;
		for (int i = endwith; i < 10; i++) {
			if (y == 0) break;
			if (a[i] == 0)
				continue;
			while (a[i] != 0 && y != 0) {
				sum2 *= 10;
				sum2 += i;
				a[i]--;
				y--;
			}
		}
		cout<<sum * sum2;
	}
	return 0;
}