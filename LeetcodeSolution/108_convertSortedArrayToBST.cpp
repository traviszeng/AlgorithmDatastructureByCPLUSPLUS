#include<vector>
#include<queue>
#include<iostream>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* helper(vector<int>& nums, int start, int end) {
	if (start == end) {
		TreeNode* tr = new TreeNode(nums[start]);
		return tr;
	}
	if (start > end)
		return NULL;

	int mid = (start + end) / 2;
	TreeNode* root = new TreeNode(nums[mid]);
	root->left = helper(nums, start, mid - 1);
	root->right = helper(nums, mid + 1, end);

	return root;
}

TreeNode* sortedArrayToBST(vector<int>& nums) {

	return helper(nums, 0, nums.size() - 1);
}