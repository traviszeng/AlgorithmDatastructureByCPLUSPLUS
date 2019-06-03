#include<vector>

using namespace std;
/**
用双指针从左右两边出发
左指针每次左边的最大值比较，右指针每次和右边的最大值比较，只要当前值小于左右最大值则在当前位置至少有max-height的水量
看成是单边的蓄水池，左边的部分右边的墙无限高，右边的部分左边的墙无限高
水量仅取决于左的左最大，和右的右最大
*/
int trap(vector<int>& height) {
	int result = 0;
	int left = 0;
	int right = height.size()-1;
	int leftMax = 0, rightMax = 0;
	while (left <= right) {
		if (height[left] <= height[right]) {
			if (leftMax < height[left]) {
				leftMax = height[left];
			}
			else {
				result += leftMax - height[left];
			}
			left++;
		}

		else {
			if (rightMax <= height[right]) {
				rightMax = height[right];
			}
			else {
				result += rightMax - height[right];
			}
			right--;
		}
	}
	return result;
}