#include<vector>
#include<iostream>
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;

};

bool isUnivalTree(TreeNode* root) {
	vector<int> ans;
	traversal(root, ans);
	for (int i = 0; i<ans.size() - 1; i++)
		if (ans[i] != ans[i + 1])
			return false;
	return true;
}

void traversal(TreeNode* root, vector<int> &ans) {
	if (root == NULL)
		return;
	ans.push_back(root->val);
	traversal(root->left, ans);
	traversal(root->right, ans);
}