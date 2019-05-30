#include<vector>
#include<algorithm>
using namespace std;

int triangleNumber(vector<int>& nums) {
	int SIZE = nums.size();
	if (SIZE < 3)
		return 0;

	int num = 0;
	sort(nums.begin(), nums.end());
	for (int i = 0; i < SIZE - 2; i++) {
		for (int j = i + 1; j < SIZE - 1; j++) {
			int maxLine = j + 1;
			while (maxLine <= SIZE - 1)
			{
				if (nums[i] + nums[j] > nums[maxLine]) {
					num++;
				}
				maxLine++;
			}
		}
	}
	return num;
}