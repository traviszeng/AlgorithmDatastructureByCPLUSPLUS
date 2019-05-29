#include<vector>
#include<algorithm>
using namespace std; 
vector<vector<int>> threeSum(vector<int>& nums) {
	vector<vector<int>> res;
	sort(nums.begin(), nums.end());

	for (int i = 0; i < nums.size(); i++) {
		int target = -nums[i];
		int front = i + 1;
		int back = nums.size() - 1;

		while (front < back) {
			int sum = nums[front] + nums[back];

			if (sum < target)
				front++;
			else if (sum > target)
				back--;
			else {
				vector<int> r{ nums[i],nums[front], nums[back]  };
				res.push_back(r);

				//可能存在重复元素 跳过
				while (front < back && nums[front] == r[1]) front++;
				while (front < back && nums[back] == r[2]) back--;
			}
		}
		//跳过第一个target的元素
		while (i + 1 < nums.size() && nums[i + 1] == nums[i])
			i++;
	}
	return res;
}