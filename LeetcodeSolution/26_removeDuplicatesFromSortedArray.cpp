#include<vector>
#include<iostream>
using namespace std;
int removeDuplicates(vector<int>& nums) {
	if (nums.size() == 0) return 0;
	size_t r = 1;
	for (size_t i = 1; i < nums.size(); ++i) {
		if (nums[i] != nums[i - 1])
			nums[r++] = nums[i];

	}
	//cout<<r;
	nums.resize(r);
	return r;
}