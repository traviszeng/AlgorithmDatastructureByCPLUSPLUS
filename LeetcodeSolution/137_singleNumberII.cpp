#include<iostream>
#include<vector>
#include<map>


//linear time with extra map memory
int singleNumber(vector<int>& nums) {
	map<int, int>  numMap;
	for (int i = 0; i < nums.size(); i++) {
		if (numMap.find(nums[i]) != numMap.end())
		{
			numMap[nums[i]] += 1;

		}
		else {
			numMap[nums[i]] = 1;
		}
	}
	map<int, int>::iterator iter;
	for (iter = numMap.begin(); iter != numMap.end(); iter++) {
		if (iter->second == 1)
			return iter->first;
	}
	return 0;
}

//排序后两两比较 without extra memory linear time
int singleNumber(vector<int>& nums) {
	if (nums.size() == 1)
		return nums[0];
	sort(nums.begin(), nums.end());

	if (nums[0] != nums[1])
		return nums[0];

	for (int i = 1; i < nums.size() - 1; i++) {
		if (nums[i] != nums[i - 1] && nums[i] != nums[i + 1])
			return nums[i];

	}
	return nums[nums.size() - 1];

}

