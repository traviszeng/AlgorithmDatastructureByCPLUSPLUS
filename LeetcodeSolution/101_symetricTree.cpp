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


bool helper(TreeNode* left, TreeNode* right) {
	if (!left && !right)
		return true;
	if (left&&right && left->val == right->val)
		return helper(left->left, right->right) && helper(left->right, right->left);
	return false;
}

bool isSymmetric(TreeNode* root) {
	if (!root)
		return true;
	if (!root->left && !root->right)
		return true;
	if (root->left && root->right) {
		return helper(root->left, root->right);
	}
	return false;
}

int main() {
	TreeNode *root = new TreeNode(3);
	root->left = new TreeNode(2);
	root->right = new TreeNode(2);
	root->left->right = new TreeNode(3);
	root->right->right = new TreeNode(3);
	cout << isSymmetric(root);
	system("pause");
}