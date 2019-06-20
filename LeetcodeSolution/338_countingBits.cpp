#include<vector>
using namespace std;

vector<int> countBits(int num) {
	vector<int> res(num + 1, 0);
	for (int i = 1; i < num + 1; i++) {
		res[i] = res[i & (i - 1)] + 1;//res[i & (i-1)]将最后一个1消除
		//
	}
	return res;
} 

