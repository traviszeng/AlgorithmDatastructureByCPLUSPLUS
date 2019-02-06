#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;
vector<int> findDuplicates(vector<int>& nums) {
	
	vector<int> result;
	if (nums.size() == 0)
		return result;
	sort(nums.begin(), nums.end());
	for (int i = 0; i < nums.size()-1; i++)
	{
		if (nums[i] == nums[i + 1]) {
			result.push_back(nums[i]);
			i++;
		}
	}

	return result;
}
