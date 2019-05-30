#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<vector<int>> fourSum(vector<int>& nums, int target) {
	vector<vector<int>> res;
	if (nums.size() < 4)
		return res;

	sort(nums.begin(), nums.end());
	for(int i = 0;i<nums.size()-3;i++){
		for (int j = i + 1; j < nums.size() - 2; j++) {
			if (j > i + 1 && nums[j] == nums[j - 1]) continue;
			int left = j + 1;
			int right = nums.size() - 1;
			while (left < right) {
				int sum = nums[left] + nums[right] + nums[i] + nums[j];
				if (sum == target) {
					res.push_back(vector<int>{nums[i], nums[j], nums[left], nums[right]});
				}
				else if (sum < target) {
					
				}
			}
		}
	}

}