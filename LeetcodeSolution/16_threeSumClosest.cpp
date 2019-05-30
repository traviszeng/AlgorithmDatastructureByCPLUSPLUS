#include<vector>
#include<algorithm>
using namespace std;
int threeSumClosest(vector<int>& nums, int target) {
	int SIZE = nums.size();
	if (SIZE < 3)
		return 0;

	int minSum = 0;
	int min = 9999;
	sort(nums.begin(), nums.end());
	for (int i = 0; i < SIZE - 2; i++) {
		int left = i + 1;
		int right = SIZE - 1;

		while (left < right) {
			int sum = nums[i] + nums[left] + nums[right];
			if (sum > target) {
				right--;
				if (min > sum - target) {
					minSum = sum;
					min = sum - target;
				}
			}
			else if (sum < target) {
				left++;
				if (min > target - sum) {
					minSum = sum;
					min = target - sum;
				}
			}
			else {
				min = 0;

				return target;
			}
		}
	}
	return minSum;
}
