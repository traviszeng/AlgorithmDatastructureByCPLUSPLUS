/**
* Definition for a binary tree node.
* 
*/
#include<iostream>
#include<queue>
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int getHeight(TreeNode* root);

bool isBalanced(TreeNode* root) {
	if (root == NULL)
		return true;
	int left = getHeight(root->left);
	int right = getHeight(root->right);
	if (abs(left - right) > 1)
		return false;
	else
		return isBalanced(root->left) && isBalanced(root->right);
}

int getHeight(TreeNode* root) {
	if (root == NULL)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return 1;
	int left = getHeight(root->left);
	int right = getHeight(root->right);
	return left > right ? left + 1: right + 1;
}