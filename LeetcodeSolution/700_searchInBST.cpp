#include<iostream>
using namespace std;

struct TreeNode{
	int val;
	TreeNode *left;
	TreeNode *right;
};

TreeNode* searchBST(TreeNode* root, int val) {
	if (root == nullptr)
		return NULL;
	if (root->val == val)
		return root;
	else if (root->val < val)
		return searchBST(root->right, val);
	else return searchBST(root->left, val);
}