#include<vector>
#include<iostream>
#include<map>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
	map<int, int> numHash;
	for (int i = 0; i < nums.size(); i++) {
		if (numHash.find(nums[i]) != numHash.end()) {
			vector<int> result;
			result.push_back(nums[i]);
			result.push_back(i);
			return result;
		}
		else {
			
		}
	}
}