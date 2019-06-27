/**
 * Definition for a binary tree node.
 */
#include<vector>
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	
};


int getMinimumDifference(TreeNode* root) {
	vector<int> num;
	traversal(root, num);
	int min = 99999;
	for (int i = 1; i < num.size(); i++) {
		if (num[i] - num[i - 1] < min)
			min = num[i] - num[i - 1];

	}
	return min;
}

void traversal(TreeNode* root, vector<int> &num) {
	if (root == nullptr)
		return;
	traversal(root->left, num);
	num.push_back(root->val);
	traversal(root->right, num);

}