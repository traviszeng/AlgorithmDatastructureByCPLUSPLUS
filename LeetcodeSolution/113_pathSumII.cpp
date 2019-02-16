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

int pathSum(TreeNode* root, int sum, vector<int> &cur, vector<vector<int>> &ans) {
	cur.push_back(root->val);
	if (sum == root->val && !root->left && !root->right) {
		ans.push_back(cur);
		cur.pop_back();
		return 0;
	}

	root->left ? pathSum(root->left, sum - root->val, cur, ans) : 0;
	root->right ? pathSum(root->right, sum - root->val, cur, ans) : 0;
	cur.pop_back();
	return 0;

}

vector<vector<int>> pathSum(TreeNode* root, int sum) {
	vector<int> temp;
	vector<vector<int>> ans;
	if (root == NULL)
		return ans;
	pathSum(root, sum, temp, ans);
	return ans;
}