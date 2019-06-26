#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
/* brutal force TLE

int nthUglyNumber(int n) {
	int i = 1;
	int num = 2;
	while (i < n) {
		if (isUgly(num)) {

			i++;
		}
		num++;

	}
	return num - 1;
}

bool isUgly(int num) {
	if (num == 0)
		return false;
	if (num == 1)
		return true;
	if (num == -1)
		return false;
	if (num % 2 != 0 && num % 3 != 0 && num % 5 != 0)
		return false;
	else {
		if ((num % 2 == 0 && num / 2 == 1) || (num % 3 == 0 && num / 3 == 1) || (num % 5 == 0 && num / 5 == 1))
			return true;
		if (num % 2 == 0 && num / 2 != 1)
			return isUgly(num / 2);
		if (num % 3 == 0 && num / 3 != 1)
			return isUgly(num / 3);
		if (num % 5 == 0 && num / 5 != 1)
			return isUgly(num / 5);

	}
	return false;
}

*/

int nthUglyNumber(int n) {
	if (n <= 0) return false; // get rid of corner cases 
	if (n == 1) return true; // base case
	int t2 = 0, t3 = 0, t5 = 0; //pointers for 2, 3, 5
	vector<int> k(n);
	k[0] = 1;
	for (int i = 1; i < n; i++)
	{
		k[i] = min(k[t2] * 2, min(k[t3] * 3, k[t5] * 5));
		if (k[i] == k[t2] * 2) t2++;
		if (k[i] == k[t3] * 3) t3++;
		if (k[i] == k[t5] * 5) t5++;
	}
	return k[n - 1];
}

int main() {
	cout << nthUglyNumber(10);
}